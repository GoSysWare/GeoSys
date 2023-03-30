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
    // qDebug() << "Target cmd_id:" << idCmdTarget << "uuid" << uuidTarget;
  } else {
    online(false, NULL);
  }

  if (bMonitor) {

    std::shared_ptr<Bus::ProjSnapshotRsp> sp_res =
        bus_proj_snapshot_send(gNode, gclient_proj_snapshot);

    if (sp_res != nullptr && sp_res->has_result() &&
        sp_res->result().code() == Bus::ResultCode::OK) {

      prj_from_snapshot(sp_res.get());
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
            //header
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
            // property
            for (k = 0; k < fb->property.size(); k++) {
              fb->property[k].value = *(p_fb->props[k].v);
            }
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

PLTarget::PLTarget(QObject *parent) : QTimer(parent) {

  bOnline = false;
  bMonitor = false;

  setInterval(200);
}

PLTarget::~PLTarget() {}

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
      start();
    }
  } else {
    stop();
    bus_disconnect_send(gNode, gclient_proj_cmd);
    bOnline = false;
    bMonitor = false;
    idCmdTarget = 0;
    uuidTarget.clear();
    gMainFrame->updateCadView();
  }

  return bOnline;
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

  stop();
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
    start();
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
  stop();
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
      start();
      return true;
    }

  } else {
    online(false, NULL);
    return false;
  }
  return false;
}

bool PLTarget::upload(Bus::EditInfos &edit) {
  std::shared_ptr<Bus::ProjectCmdRsp> online_res =
      bus_upload_send(gNode, gclient_proj_cmd);

  if (online_res == nullptr || online_res->has_result() == false ||
      online_res->result().code() != Bus::ResultCode::OK) {
    online(false, NULL);
    return false;
  }
  // edit 需要赋值

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
    if (idCmdTarget == gMainModel->cmdID) {
      return true;
    }
  }
  return false;
}
