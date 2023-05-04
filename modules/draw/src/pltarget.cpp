#include "pltarget.h"
#include "gdefine.h"
#include "modules/calc/include/k_bus.h"
#include "modules/calc/include/k_command.h"

//定时器中刷新各个引脚和变量的值，并更新画面
void PLTarget::timerEvent(QTimerEvent *e) {

  std::shared_ptr<Bus::ProjectInfoRsp> info_res =
      bus_proj_info_send(gNode, gclient_proj_info);

  if (info_res != nullptr && info_res->has_result() &&
      info_res->result().code() == Bus::ResultCode::OK) {
    idCmdTarget = info_res->cmd_id();
    uuidTarget = QString::fromStdString(info_res->prj_uuid());
    qDebug() << "Target cmd_id:" << idCmdTarget << "uuid" << uuidTarget;
    qDebug() << "HMI cmd_id:" << gMainModel->cmdID << "uuid"
             << gMainModel->project.uuid;

  } else {
    online(false, NULL);
  }

  if (bMonitor) {
    std::shared_ptr<Bus::ProjSnapshotRsp> sp_res =
        bus_proj_snapshot_send(gNode, gclient_proj_snapshot, ev_ids);

    if (sp_res != nullptr && sp_res->has_result() &&
        sp_res->result().code() == Bus::ResultCode::OK) {

      prj_from_snapshot(ev_ids, sp_res.get());
      // prj_dump();
      int i, j, k, n, m;
      // load fbs value
      PLModule *mod;

      PLProgram *prg;
      PLFunctionBlock *fb;
      fb_t *p_fb;
      for (m = 0; m < gMainModel->modList.size(); m++) {
        mod = &gMainModel->modList[m];

        for (i = 0; i < mod->prgList.size(); i++) {
          prg = &mod->prgList[i];
          for (j = 0; j < prg->fbs.size(); j++) {
            fb = &prg->fbs[j];
            p_fb = prj_fbfind(fb->idMod, fb->idPrg, fb->id);
            // header
            fb->flag = p_fb->h.flag;
            fb->cycle_time = p_fb->h.cycle_time;
            fb->begin_time = p_fb->h.begin_time;
            fb->expend_time = p_fb->h.expend_time;

            // input
            for (k = 0; k < fb->input.size(); k++) {
              fb->input[k].value = *(p_fb->ins[k].v);
            }
            // output
            for (k = 0; k < fb->output.size(); k++) {
              fb->output[k].value = *(p_fb->outs[k].v);
              // qDebug() << "fb" << fb->id << "pin" << k << "val"
              //          << fb->output[k].value.v().i();
            }
            // // property
            // for (k = 0; k < fb->property.size(); k++) {
            //   fb->property[k].value = *(p_fb->props[k].v);
            // }
          }
        }
      }
      // load evs value
      PLEVData *ev;
      value_tm *p_ev;
      for (int i = 0; i < gMainModel->evList.size(); i++) {
        ev = &gMainModel->evList[i];
        p_ev = ev_find_v(ev->id)->get();
        ev->value = *p_ev;
      }
      gMainFrame->updateCadView();
    } else {
      online(false, NULL);
    }
  }
}

PLTarget::PLTarget(QObject *parent) {

  bOnline = false;
  bMonitor = false;

  apollo::cyber::TimerOption opt;
  opt.oneshot = false;
  opt.callback = [this]() {
    std::shared_ptr<Bus::ProjectInfoRsp> info_res =
        bus_proj_info_send(gNode, gclient_proj_info);

    if (info_res != nullptr && info_res->has_result() &&
        info_res->result().code() == Bus::ResultCode::OK) {
      this->idCmdTarget = info_res->cmd_id();
      this->uuidTarget = QString::fromStdString(info_res->prj_uuid());
      qDebug() << "Target cmd_id:" << this->idCmdTarget << "uuid"
               << this->uuidTarget;
      qDebug() << "HMI cmd_id:" << gMainModel->cmdID << "uuid"
               << gMainModel->project.uuid;

    } else {
      this->online(false, NULL);
    }

    if (this->bMonitor) {

      std::shared_ptr<Bus::ProjSnapshotRsp> sp_res =
          bus_proj_snapshot_send(gNode, gclient_proj_snapshot, this->ev_ids);

      if (sp_res != nullptr && sp_res->has_result() &&
          sp_res->result().code() == Bus::ResultCode::OK) {

        prj_from_snapshot(this->ev_ids, sp_res.get());
        // prj_dump();
        int i, j, k, n, m;
        // load fbs value
        PLModule *mod;

        PLProgram *prg;
        PLFunctionBlock *fb;
        fb_t *p_fb;
        for (m = 0; m < gMainModel->modList.size(); m++) {
          mod = &gMainModel->modList[m];

          for (i = 0; i < mod->prgList.size(); i++) {
            prg = &mod->prgList[i];
            for (j = 0; j < prg->fbs.size(); j++) {
              fb = &prg->fbs[j];
              p_fb = prj_fbfind(fb->idMod, fb->idPrg, fb->id);
              // header
              fb->flag = p_fb->h.flag;
              fb->cycle_time = p_fb->h.cycle_time;
              fb->begin_time = p_fb->h.begin_time;
              fb->expend_time = p_fb->h.expend_time;

              // input
              for (k = 0; k < fb->input.size(); k++) {
                fb->input[k].value = *(p_fb->ins[k].v);
              }
              // output
              for (k = 0; k < fb->output.size(); k++) {
                fb->output[k].value = *(p_fb->outs[k].v);
                // qDebug() << "fb" << fb->id << "pin" << k << "val"
                //          << fb->output[k].value.v().i();
              }
              // // property
              // for (k = 0; k < fb->property.size(); k++) {
              //   fb->property[k].value = *(p_fb->props[k].v);
              // }
            }
          }
        }
        // load evs value
        PLEVData *ev;
        value_tm *p_ev;
        for (int i = 0; i < gMainModel->evList.size(); i++) {
          ev = &gMainModel->evList[i];
          p_ev = ev_find_v(ev->id)->get();
          ev->value = *p_ev;
        }
        gMainFrame->updateCadView();
      } else {
        this->online(false, NULL);
      }
    }
  };
  opt.period = 200;
  timer.SetTimerOption(opt);
}

PLTarget::~PLTarget() { timer.Stop(); }

bool PLTarget::online(bool mode, char *ip) {
  if (mode == bOnline) {
    return false;
  }

  if (mode) {

    std::shared_ptr<Bus::ProjectCmdRsp> res =
        bus_online_send(gNode, gclient_proj_cmd);

    if (res != nullptr && res->has_result() &&
        res->result().code() == Bus::ResultCode::OK) {
      bOnline = true;
      timer.Start();
    }
  } else {
    timer.Stop();
    bus_disconnect_send(gNode, gclient_proj_cmd);
    bOnline = false;
    bMonitor = false;
    idCmdTarget = 0;
    uuidTarget.clear();
    gMainFrame->updateCadView();
  }

  return bOnline;
}
void PLTarget::setOnlineValueSlot(int idMod, int idPrg, int idFb, int idPin,
                                  value_tm val) {
  qDebug() << "set value mod:" << idMod << " prg:" << idPrg << " fb:" << idFb
           << " input pin:" << idPin
           << " val:" << QString::fromStdString(val.ShortDebugString());
  if (!bOnline) {
    return;
  }
  if (!bMonitor) {
    return;
  }
  Bus::EditInfos edit_infos;

  Bus::EditInfo *set_pin_val_info = edit_infos.add_infos();
  set_pin_val_info->set_element(Bus::PIN);
  set_pin_val_info->set_edit_type(Bus::SET);
  set_pin_val_info->mutable_pin()->set_mod_id(idMod);
  set_pin_val_info->mutable_pin()->set_task_id(idPrg);
  set_pin_val_info->mutable_pin()->set_fb_id(idFb);
  set_pin_val_info->mutable_pin()->set_pin_index(idPin);
  set_pin_val_info->mutable_pin()->mutable_pin_val()->CopyFrom(val);

  std::shared_ptr<Bus::ProjectCmdRsp> set_val_res =
      bus_set_val_send(gNode, gclient_proj_cmd, edit_infos);

  if (set_val_res != nullptr && set_val_res->has_result() == true &&
      set_val_res->result().code() == Bus::ResultCode::OK) {
    qDebug() << "set value succ";

  } else {
    qDebug() << "set value fail";
  }
}

bool PLTarget::sync() {
  if (!bOnline) {
    return false;
  }
  if (bMonitor) {
    return false;
  }
  if (!isMatch()) {
    return false;
  }
  if (isSync()) {
    return false;
  }

  timer.Stop();
  std::shared_ptr<Bus::ProjectCmdRsp> online_res =
      bus_stop_send(gNode, gclient_proj_cmd);

  if (online_res == nullptr || online_res->has_result() == false ||
      online_res->result().code() != Bus::ResultCode::OK) {
    online(false, NULL);
    return false;
  }

  std::shared_ptr<Bus::ProjectCmdRsp> run_res =
      bus_run_send(gNode, gclient_proj_cmd);

  if (run_res == nullptr || run_res->has_result() == false ||
      run_res->result().code() != Bus::ResultCode::OK) {
    timer.Start();
    return true;
  } else {
    online(false, NULL);
    return false;
  }

  return false;
}

void PLTarget::monitor(bool mode) {
  if (mode) {
    if (!bOnline) {
      return;
    }
    if (!isSync()) {
      return;
    }
    bMonitor = true;
  } else {
    bMonitor = false;
  }
}

bool PLTarget::download() {
  if (!bOnline) {
    return false;
  }
  if (bMonitor) {
    return false;
  }
  if (isSync()) {
    return false;
  }
  //重新生成uuid
  gMainModel->project.renewUuid();

  Bus::EditInfos edit_infos;

  Bus::EditInfo *proj_info = edit_infos.add_infos();
  proj_info->set_element(Bus::PROJ);
  proj_info->set_edit_type(Bus::SET);
  proj_info->set_cmd_id(gMainModel->cmdID);
  proj_info->mutable_proj()->set_proj_uuid(
      gMainModel->project.uuid.toStdString());
  proj_info->mutable_proj()->set_proj_name(
      gMainModel->project.name.toStdString());
  proj_info->mutable_proj()->set_proj_desc(
      gMainModel->project.desc.toStdString());

  cmd_dispatch(*proj_info);

  for (auto i = 0; i < gMainModel->cmdList.size(); i++) {
    Bus::EditInfo *info = edit_infos.add_infos();
    info->CopyFrom(gMainModel->cmdList.at(i).editInfo);
  }

  // 停掉hmi的本地逻辑
  timer.Stop();
  // 停掉remote的引擎
  std::shared_ptr<Bus::ProjectCmdRsp> stop_res =
      bus_stop_send(gNode, gclient_proj_cmd);

  if (stop_res == nullptr || stop_res->has_result() == false ||
      stop_res->result().code() != Bus::ResultCode::OK) {
    online(false, NULL);
    return false;
  }
  // 重启remote的引擎
  std::shared_ptr<Bus::ProjectCmdRsp> reset_res =
      bus_reset_send(gNode, gclient_proj_cmd);

  if (reset_res == nullptr || reset_res->has_result() == false ||
      reset_res->result().code() != Bus::ResultCode::OK) {
    online(false, NULL);
    return false;
  }

  // 下载到remote的引擎
  std::shared_ptr<Bus::ProjectCmdRsp> download_res =
      bus_download_send(gNode, gclient_proj_cmd, edit_infos);

  if (download_res != nullptr && download_res->has_result() == true &&
      download_res->result().code() == Bus::ResultCode::OK) {
    //启动remote的引擎
    std::shared_ptr<Bus::ProjectCmdRsp> start_res =
        bus_run_send(gNode, gclient_proj_cmd);

    if (start_res == nullptr || start_res->has_result() == false ||
        start_res->result().code() != Bus::ResultCode::OK) {
      online(false, NULL);
      return false;
    } else {
      //启动draw的逻辑
      timer.Start();
      return true;
    }

  } else {
    online(false, NULL);
    return false;
  }
  return false;
}

bool PLTarget::upload(Bus::EditInfos &edit) {
  std::shared_ptr<Bus::ProjectCmdRsp> upload_res =
      bus_upload_send(gNode, gclient_proj_cmd);

  if (upload_res == nullptr || upload_res->has_result() == false ||
      upload_res->result().code() != Bus::ResultCode::OK) {
    online(false, NULL);
    return false;
  }
  // edit 需要赋值
  edit = upload_res->rsp_infos();

  return true;
}

bool PLTarget::isOnline() { return bOnline; }

bool PLTarget::isMonitor() { return bMonitor; }

bool PLTarget::isMatch() {
  if (uuidTarget == gMainModel->project.uuid) {
    if (idCmdTarget <= gMainModel->cmdID) {
      return true;
    } else {
      return false;
    }
  } else {
    return false;
  }

  return false;
}

bool PLTarget::isSync() {
  if (isMatch()) {
    if (idCmdTarget == gMainModel->cmdID &&
        uuidTarget == gMainModel->project.uuid) {
      return true;
    }
  }
  return false;
}
