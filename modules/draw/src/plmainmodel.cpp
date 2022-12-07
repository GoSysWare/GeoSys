#include "plmainmodel.h"
#include "modules/calc/include/k_command.h"
#include "modules/calc/include/k_functionblock.h"
#include "modules/calc/include/k_lib.h"
#include "modules/calc/include/k_project.h"
#include <QFile>
#include <QTextStream>

PLMainModel::PLMainModel() {
  cmdID = 0;
  objID = 0;
  prgCurrent = NULL;

  initLibrary();
  updateFuncList(0);

  prj_init(0);

  isModified = false;
}

void PLMainModel::initLibrary() {
  lib_init();
  lib_t *lib = lib_first();

  QStringList list;
  while (lib != NULL) {
    list << lib->libname.c_str();
    lib = lib_next();
  }
  modelLibrary.setStringList(list);
}

void PLMainModel::updateFuncList(int libIndex) {
  lib_t *lib = lib_first();
  for (int i = 0; i < libIndex; i++) {
    lib = lib_next();
  }

  QStringList list;
  void *fb = lib->first();
  while (fb != ((void *)0)) {
    list << ((fb_t *)fb)->h.fcname.c_str();
    fb = lib->next();
  }
  modelFunction.setStringList(list);
}

void PLMainModel::clear() {
  cmdID = 0;
  objID = 0;
  prgCurrent = NULL;
  modList.clear();
  cmdList.clear();
  modelEVData.beginReset();
  evList.clear();
  modelEVData.endReset();
  prj_reset();
  project.clear();

  prj_reset();
}
void PLMainModel::updateModuleList() {
  QStringList list;

  for (int i = 0; i < modList.size(); i++) {
    PLModule mod = modList.at(i);
    list << mod.name;
  }

  modelModule.setStringList(list);
}

void PLMainModel::updateProgList(int modIndex) {
  QStringList list;
  if (modIndex > modList.size())
    return;

  PLModule mod = modList.at(modIndex);
  for (int i = 0; i < mod.prgList.size(); i++) {
    PLProgram prg = mod.prgList.at(i);
    list << prg.name;
  }
  modelProgram.setStringList(list);
}

bool PLMainModel::exeCommand(PLCommand &cmd) {
  if (cmdID < cmd.editInfo.cmd_id()) {
    cmdID = cmd.editInfo.cmd_id();
    qDebug() << "command id:" << cmdID;
  }

  cmd_dispatch(cmd.editInfo);

  if (!cmd.dispatch()) {
    return false;
  }

  if (cmd.editInfo.element() != Bus::EditElement::PROJ &&
      cmd.editInfo.edit_type() != Bus::EditType::SET) {
    cmdList.append(cmd);
  }

  return true;
}

void PLMainModel::makeLkNewCmd(PLCommand &cmd, PLLink &lk, bool newId) {
  cmdID++;
  cmd.editInfo.set_cmd_id(cmdID);
  cmd.editInfo.set_element(Bus::EditElement::LK);
  cmd.editInfo.set_edit_type(Bus::EditType::ADD);
  if (newId) {
    objID++;
    lk.id = objID;
  }
  cmd.editInfo.mutable_lk()->set_mod_id(lk.idMod);
  cmd.editInfo.mutable_lk()->set_task_id(lk.idPrg);
  cmd.editInfo.mutable_lk()->set_lk_id(lk.id);
  cmd.editInfo.mutable_lk()->set_src_fb_id(lk.idFbSrc);
  cmd.editInfo.mutable_lk()->set_src_pin_index(lk.pinSrc);
  cmd.editInfo.mutable_lk()->set_target_fb_id(lk.idFbTgt);
  cmd.editInfo.mutable_lk()->set_target_pin_index(lk.pinTgt);

  lk.removeDualPoints();

  for (int i = 0; i < lk.pts.size(); i++) {
    auto pos = cmd.editInfo.add_pos();
    pos->set_x(lk.pts.at(i).x);
    pos->set_y(lk.pts.at(i).y);
  }
}

void PLMainModel::makeLkRemoveCmd(PLCommand &cmd, PLLink &lk) {
  cmdID++;
  cmd.editInfo.set_cmd_id(cmdID);
  cmd.editInfo.set_element(Bus::EditElement::LK);
  cmd.editInfo.set_edit_type(Bus::EditType::RM);
  cmd.editInfo.mutable_lk()->set_mod_id(lk.idMod);
  cmd.editInfo.mutable_lk()->set_task_id(lk.idPrg);
  cmd.editInfo.mutable_lk()->set_lk_id(lk.id);
}

void PLMainModel::makeLkMoveCmd(PLCommand &cmd, PLLink &lk) {
  cmdID++;
  cmd.editInfo.set_cmd_id(cmdID);
  cmd.editInfo.set_element(Bus::EditElement::LK);
  cmd.editInfo.set_edit_type(Bus::EditType::MV);
  cmd.editInfo.mutable_lk()->set_mod_id(lk.idMod);
  cmd.editInfo.mutable_lk()->set_task_id(lk.idPrg);
  cmd.editInfo.mutable_lk()->set_lk_id(lk.id);
  lk.removeDualPoints();

  for (int i = 0; i < lk.pts.size(); i++) {
    auto pos = cmd.editInfo.add_pos();
    pos->set_x(lk.pts.at(i).x);
    pos->set_y(lk.pts.at(i).y);
  }
}

void PLMainModel::makeFbNewCmd(PLCommand &cmd, PLFunctionBlock &fb, bool newId,
                               bool newName) {
  cmdID++;
  cmd.editInfo.set_cmd_id(cmdID);
  cmd.editInfo.set_element(Bus::EditElement::FB);
  cmd.editInfo.set_edit_type(Bus::EditType::ADD);
  if (newId) {
    objID++;
    fb.id = objID;
  }
  cmd.editInfo.mutable_fb()->set_mod_id(fb.idMod);
  cmd.editInfo.mutable_fb()->set_task_id(fb.idPrg);
  cmd.editInfo.mutable_fb()->set_fb_id(fb.id);
  cmd.editInfo.mutable_fb()->set_flib_name(fb.libName.toStdString());
  cmd.editInfo.mutable_fb()->set_fc_name(fb.funName.toStdString());
  cmd.editInfo.mutable_fb()->set_fb_name(fb.blkName.toStdString());

  auto pos = cmd.editInfo.add_pos();
  pos->set_x(fb.x);
  pos->set_y(fb.y);
}

void PLMainModel::makeFbRemoveCmd(PLCommand &cmd, PLFunctionBlock &fb) {
  cmdID++;
  cmd.editInfo.set_cmd_id(cmdID);
  cmd.editInfo.set_element(Bus::EditElement::LK);
  cmd.editInfo.set_edit_type(Bus::EditType::RM);
  cmd.editInfo.mutable_fb()->set_mod_id(fb.idMod);
  cmd.editInfo.mutable_fb()->set_task_id(fb.idPrg);
  cmd.editInfo.mutable_fb()->set_fb_id(fb.id);
}

void PLMainModel::makeFbMoveCmd(PLCommand &cmd, PLFunctionBlock &fb) {
  cmdID++;
  cmd.editInfo.set_cmd_id(cmdID);
  cmd.editInfo.set_element(Bus::EditElement::FB);
  cmd.editInfo.set_edit_type(Bus::EditType::MV);
  cmd.editInfo.mutable_fb()->set_mod_id(fb.idMod);
  cmd.editInfo.mutable_fb()->set_task_id(fb.idPrg);
  cmd.editInfo.mutable_fb()->set_fb_id(fb.id);
  cmd.editInfo.mutable_fb()->set_fb_name(fb.blkName.toStdString());

  lk.removeDualPoints();

  auto pos = cmd.editInfo.add_pos();
  pos->set_x(fb.x);
  pos->set_y(fb.y);
}

void PLMainModel::makeViNewCmd(PLCommand &cmd, PLVLink &vlk, bool newId) {
  cmdID++;
  cmd.editInfo.set_cmd_id(cmdID);
  cmd.editInfo.set_element(Bus::EditElement::VI);
  cmd.editInfo.set_edit_type(Bus::EditType::ADD);
  if (newId) {
    objID++;
    vlk.id = objID;
  }
  cmd.editInfo.mutable_vi()->set_vi_id(vlk.id);
  cmd.editInfo.mutable_vi()->set_mod_id(vlk.idMod);
  cmd.editInfo.mutable_vi()->set_task_id(vlk.idPrg);
  cmd.editInfo.mutable_vi()->set_fb_id(vlk.idFb);
  cmd.editInfo.mutable_vi()->set_pin_index(vlk.idPin);
  cmd.editInfo.mutable_vi()->set_ev_id(vlk.idEv);
}

void PLMainModel::makeViRemoveCmd(PLCommand &cmd, PLVLink &vlk) {
  cmdID++;
  cmd.editInfo.set_cmd_id(cmdID);
  cmd.editInfo.set_element(Bus::EditElement::VI);
  cmd.editInfo.set_edit_type(Bus::EditType::RM);
  cmd.editInfo.mutable_vi()->set_vi_id(vlk.id);
  cmd.editInfo.mutable_vi()->set_mod_id(vlk.idMod);
  cmd.editInfo.mutable_vi()->set_task_id(vlk.idPrg);
}

void PLMainModel::makeVoNewCmd(PLCommand &cmd, PLVLink &vlk, bool newId) {
  cmdID++;
  cmd.editInfo.set_cmd_id(cmdID);
  cmd.editInfo.set_element(Bus::EditElement::VO);
  cmd.editInfo.set_edit_type(Bus::EditType::ADD);
  if (newId) {
    objID++;
    vlk.id = objID;
  }
  cmd.editInfo.mutable_vo()->set_vo_id(vlk.id);
  cmd.editInfo.mutable_vo()->set_mod_id(vlk.idMod);
  cmd.editInfo.mutable_vo()->set_task_id(vlk.idPrg);
  cmd.editInfo.mutable_vo()->set_fb_id(vlk.idFb);
  cmd.editInfo.mutable_vo()->set_pin_index(vlk.idPin);
  cmd.editInfo.mutable_vo()->set_ev_id(vlk.idEv);
}

void PLMainModel::makeVoRemoveCmd(PLCommand &cmd, PLVLink &vlk) {
  cmdID++;
  cmd.editInfo.set_cmd_id(cmdID);
  cmd.editInfo.set_element(Bus::EditElement::VO);
  cmd.editInfo.set_edit_type(Bus::EditType::RM);
  cmd.editInfo.mutable_vo()->set_vo_id(vlk.id);
  cmd.editInfo.mutable_vo()->set_mod_id(vlk.idMod);
  cmd.editInfo.mutable_vo()->set_task_id(vlk.idPrg);
}

void PLMainModel::makeEvNewCmd(PLCommand &cmd, PLEVData &ev, bool newId) {
  cmdID++;
  cmd.editInfo.set_cmd_id(cmdID);
  cmd.editInfo.set_element(Bus::EditElement::EV);
  cmd.editInfo.set_edit_type(Bus::EditType::ADD);
  if (newId) {
    objID++;
    ev.id = objID;
  }
  cmd.editInfo.mutable_ev()->set_ev_id(ev.id);
  cmd.editInfo.mutable_ev()->set_ev_name(ev.name.toStdString());
  cmd.editInfo.mutable_ev()->set_ev_type(ev.type);
  cmd.editInfo.mutable_ev()->set_ev_desc(ev.desc.toStdString());
  cmd.editInfo.mutable_ev()->mutable_init_val()->CopyFrom(ev.initValue);
}

void PLMainModel::makeEvSetCmd(PLCommand &cmd, PLEVData &ev) {
  cmdID++;
  cmd.editInfo.set_cmd_id(cmdID);
  cmd.editInfo.set_element(Bus::EditElement::EV);
  cmd.editInfo.set_edit_type(Bus::EditType::SET);
  cmd.editInfo.mutable_ev()->set_ev_id(ev.id);
  cmd.editInfo.mutable_ev()->set_ev_name(ev.name.toStdString());
  cmd.editInfo.mutable_ev()->set_ev_type(ev.type);
  cmd.editInfo.mutable_ev()->set_ev_desc(ev.desc.toStdString());
  cmd.editInfo.mutable_ev()->mutable_init_val()->CopyFrom(ev.value);

}

void PLMainModel::makeEvRemoveCmd(PLCommand &cmd, PLEVData &ev) {
  cmdID++;
  cmd.editInfo.set_cmd_id(cmdID);
  cmd.editInfo.set_element(Bus::EditElement::EV);
  cmd.editInfo.set_edit_type(Bus::EditType::RM);
  cmd.editInfo.mutable_ev()->set_ev_id(ev.id);
}

void PLMainModel::makePrgNewCmd(PLCommand &cmd, PLProgram &prg, bool newId) {

  cmdID++;
  cmd.editInfo.set_cmd_id(cmdID);
  cmd.editInfo.set_element(Bus::EditElement::TASK);
  cmd.editInfo.set_edit_type(Bus::EditType::ADD);
  if (newId) {
    objID++;
    prg.id = objID;
  }
  cmd.editInfo.mutable_task()->set_mod_id(prg.idMod);
  cmd.editInfo.mutable_task()->set_task_id(prg.id);
  cmd.editInfo.mutable_task()->set_task_name(prg.name.toStdString());
  cmd.editInfo.mutable_task()->set_task_type((Bus::TaskType)prg.type);
  cmd.editInfo.mutable_task()->set_task_desc(prg.desc.toStdString());
}

void PLMainModel::makePrgRemoveCmd(PLCommand &cmd, PLProgram &prg) {
  cmdID++;
  cmd.editInfo.set_cmd_id(cmdID);
  cmd.editInfo.set_element(Bus::EditElement::TASK);
  cmd.editInfo.set_edit_type(Bus::EditType::ADD);
  cmd.editInfo.mutable_task()->set_mod_id(prg.idMod);
  cmd.editInfo.mutable_task()->set_task_id(prg.id);
}

void PLMainModel::makePrgRenameCmd(PLCommand &cmd, PLProgram &prg) {
  cmdID++;
  cmd.editInfo.set_cmd_id(cmdID);
  cmd.editInfo.set_element(Bus::EditElement::TASK);
  cmd.editInfo.set_edit_type(Bus::EditType::SET);
  cmd.editInfo.mutable_task()->set_mod_id(prg.idMod);
  cmd.editInfo.mutable_task()->set_task_id(prg.id);
  cmd.editInfo.mutable_task()->set_task_name(prg.name.toStdString());
  cmd.editInfo.mutable_task()->set_task_type((Bus::TaskType)prg.type);
  cmd.editInfo.mutable_task()->set_task_desc(prg.desc.toStdString());
}
void PLMainModel::makeModNewCmd(PLCommand &cmd, PLModule &mod, bool newId) {
  cmdID++;
  cmd.editInfo.set_cmd_id(cmdID);
  cmd.editInfo.set_element(Bus::EditElement::MOD);
  cmd.editInfo.set_edit_type(Bus::EditType::ADD);
  if (newId) {
    objID++;
    mod.id = objID;
  }
  cmd.editInfo.mutable_mod()->set_mod_id(mod.id);
  cmd.editInfo.mutable_mod()->set_mod_name(mod.name.toStdString());
  cmd.editInfo.mutable_mod()->set_mod_desc(mod.desc.toStdString());
}
void PLMainModel::makeModRemoveCmd(PLCommand &cmd, PLModule &mod) {
  cmdID++;
  cmd.editInfo.set_cmd_id(cmdID);
  cmd.editInfo.set_element(Bus::EditElement::MOD);
  cmd.editInfo.set_edit_type(Bus::EditType::RM);
  cmd.editInfo.mutable_task()->set_mod_id(mod.id);
}
void PLMainModel::makeModRenameCmd(PLCommand &cmd, PLModule &mod) {
  cmdID++;
  cmd.editInfo.set_cmd_id(cmdID);
  cmd.editInfo.set_element(Bus::EditElement::MOD);
  cmd.editInfo.set_edit_type(Bus::EditType::SET);
  cmd.editInfo.mutable_mod()->set_mod_id(mod.id);
  cmd.editInfo.mutable_mod()->set_mod_name(mod.name.toStdString());
  cmd.editInfo.mutable_mod()->set_mod_desc(mod.desc.toStdString());
}
void PLMainModel::makePinSetCmd(PLCommand &cmd, int idMod, int idPrg, int idFb,
                                int idPin, vaule_tm val) {
  cmdID++;
  cmd.editInfo.set_cmd_id(cmdID);
  cmd.editInfo.set_element(Bus::EditElement::PIN);
  cmd.editInfo.set_edit_type(Bus::EditType::SET) cmd.editInfo.mutable_pin()
      ->set_mod_id(idMod);
  cmd.editInfo.mutable_pin()->set_task_id(idPrg);
  cmd.editInfo.mutable_pin()->set_fb_id(idFb);
  cmd.editInfo.mutable_pin()->set_pin_index(idPin);
  cmd.editInfo.mutable_pin()->set_pin_val(val);
}

void PLMainModel::makeLkCopyCmd(PLCommand &cmd, PLLink &lk) {

  cmd.editInfo.set_cmd_id(-1);
  cmd.editInfo.set_element(Bus::EditElement::LK);
  cmd.editInfo.set_edit_type(Bus::EditType::CP) if (newId) {
    objID++;
    lk.id = objID;
  }
  cmd.editInfo.mutable_lk()->set_mod_id(lk.idMod);
  cmd.editInfo.mutable_lk()->set_task_id(lk.idPrg);
  cmd.editInfo.mutable_lk()->set_lk_id(lk.id);
  cmd.editInfo.mutable_lk()->set_src_fb_id(lk.idFbSrc);
  cmd.editInfo.mutable_lk()->set_src_pin_index(lk.pinSrc);
  cmd.editInfo.mutable_lk()->set_target_fb_id(lk.idFbTgt);
  cmd.editInfo.mutable_lk()->set_target_pin_index(lk.pinTgt);

  lk.removeDualPoints();

  for (int i = 0; i < lk.pts.size(); i++) {
    auto pos = cmd.editInfo.add_pos();
    pos->x = lk.pts.at(i).x;
    pos->y = lk.pts.at(i).y;
  }
}

void PLMainModel::makeFbCopyCmd(PLCommand &cmd, PLFunctionBlock &fb) {
  cmd.editInfo.set_cmd_id(-1);
  cmd.editInfo.set_element(Bus::EditElement::FB);
  cmd.editInfo.set_edit_type(Bus::EditType::CP) if (newId) {
    objID++;
    fb.id = objID;
  }
  cmd.editInfo.mutable_fb()->set_mod_id(fb.idMod);
  cmd.editInfo.mutable_fb()->set_task_id(fb.idPrg);
  cmd.editInfo.mutable_fb()->set_fb_id(fb.id);
  cmd.editInfo.mutable_fb()->set_flib_name(fb.libName.toStdString());
  cmd.editInfo.mutable_fb()->set_fc_name(fb.funName.toStdString());
  cmd.editInfo.mutable_fb()->set_fb_name(fb.blkName.toStdString());

  auto pos = cmd.editInfo.add_pos();
  pos->x = fb.x;
  pos->y = fb.y;
}

bool PLMainModel::isCmdObjRemoved(PLCommand *cmd) {

  if (cmd->editInfo.element() == Bus::EditElement::MOD &&
      (cmd->editInfdit_type() == Bus::EditType::ADD ||
       cmd->editInfo.edit_type() == Bus::EditType::RM)) {
    if (NULL == PLCommand::getModule(cmd->editInfo.mod().mod_id())) {
      return true;
    }
  } else if (cmd->editInfo.element() == Bus::EditElement::TASK &&
             (cmd->editInfdit_type() == Bus::EditType::ADD ||
              cmd->editInfo.edit_type() == Bus::EditType::RM)) {
    PLModule *mod = PLCommand::getModule(cmd->editInfo.task().mod_id());
    if (NULL == mod) {
      return true;
    } else {
      if (NULL == PLCommand::getProgram(mod, cmd->editInfo.task().task_id())) {
        return true;
      }
    }
  } else if (cmd->editInfo.element() == Bus::EditElement::EV &&
             (cmd->editInfdit_type() == Bus::EditType::ADD ||
              cmd->editInfo.edit_type() == Bus::EditType::RM ||
              cmd->editInfo.edit_type() == Bus::EditType::SET)) {
    if (NULL == PLCommand::getEv(cmd->editInfo.ev().ev_id())) {
      return true;
    }
  } else if (cmd->editInfo.element() == Bus::EditElement::FB &&
             (cmd->editInfdit_type() == Bus::EditType::ADD ||
              cmd->editInfo.edit_type() == Bus::EditType::RM ||
              cmd->editInfo.edit_type() == Bus::EditType::MV)) {
    PLModule *mod = PLCommand::getModule(cmd->editInfo.fb().mod_id());
    if (NULL == mod) {
      return true;
    } else {
      PLProgram *prg = PLCommand::getProgram(mod, cmd->editInfo.fb().task_id());
      if (NULL == prg) {
        return true;
      } else {
        if (NULL ==
            PLCommand::getFunctionBlock(prg, cmd->editInfo.fb().fb_id())) {
          return true;
        }
      }
    }
  } else if (cmd->editInfo.element() == Bus::EditElement::PIN &&
             cmd->editInfo.edit_type() == Bus::EditType::SET) {
    PLModule *mod = PLCommand::getModule(cmd->editInfo.pin().mod_id());
    if (NULL == mod) {
      return true;
    } else {
      PLProgram *prg =
          PLCommand::getProgram(mod, cmd->editInfo.pin().task_id());
      if (NULL == prg) {
        return true;
      } else {
        if (NULL ==
            PLCommand::getFunctionBlock(prg, cmd->editInfo.pin().fb_id())) {
          return true;
        }
      }
    }
  } else if (cmd->editInfo.element() == Bus::EditElement::LK &&
             (cmd->editInfdit_type() == Bus::EditType::ADD ||
              cmd->editInfo.edit_type() == Bus::EditType::RM ||
              cmd->editInfo.edit_type() == Bus::EditType::MV)) {
    PLModule *mod = PLCommand::getModule(cmd->editInfo.lk().mod_id());
    if (NULL == mod) {
      return true;
    } else {
      PLProgram *prg = PLCommand::getProgram(mod, cmd->editInfo.lk().task_id());
      if (NULL == prg) {
        return true;
      } else {
        if (NULL == PLCommand::getLink(prg, cmd->editInfo.lk().lk_id())) {
          return true;
        }
      }
    }
  } else if (cmd->editInfo.element() == Bus::EditElement::VI &&
             (cmd->editInfdit_type() == Bus::EditType::ADD ||
              cmd->editInfo.edit_type() == Bus::EditType::RM)) {
    PLModule *mod = PLCommand::getModule(cmd->editInfo.vi().mod_id());
    if (NULL == mod) {
      return true;
    } else {
      PLProgram *prg = PLCommand::getProgram(mod, cmd->editInfo.vi().task_id());
      if (NULL == prg) {
        return true;
      } else {
        if (NULL == PLCommand::getVi(prg, cmd->editInfo.vi().vi_id())) {
          return true;
        }
      }
    }
  } else if (cmd->editInfo.element() == Bus::EditElement::VO &&
             (cmd->editInfdit_type() == Bus::EditType::ADD ||
              cmd->editInfo.edit_type() == Bus::EditType::RM)) {
    PLModule *mod = PLCommand::getModule(cmd->editInfo.vo().mod_id());
    if (NULL == mod) {
      return true;
    } else {
      PLProgram *prg = PLCommand::getProgram(mod, cmd->editInfo.vo().task_id());
      if (NULL == prg) {
        return true;
      } else {
        if (NULL == PLCommand::getVo(prg, cmd->editInfo.vo().vo_id())) {
          return true;
        }
      }
    }
  }
  return false;
}

void PLMainModel::removeDualCommands(QList<PLCommand> &list, bool all) {
  QList<PLCommand *> moveFb;
  QList<PLCommand *> moveLk;
  QList<PLCommand *> setPin;
  QList<PLCommand *> setEv;
  QList<PLCommand *> setPrg;
  QList<PLCommand *> setMod;

  int i, j;
  PLCommand *cmd;
  for (i = list.size() - 1; i >= 0; i--) {
    cmd = &list[i];
    cmd->mark = false;
    if (all) {
      if (isCmdObjRemoved(cmd)) {
        cmd->mark = true;
      }
    }
    if (cmd->editInfo.element() == Bus::EditElement::FB &&
        cmd->editInfo.edit_type() == Bus::EditType::MV) {
      for (j = 0; j < moveFb.size(); j++) {
        if (cmd->editInfo.fb().mod_id() == moveFb.at(j)->editInfo.fb().mod_id() &&
        cmd->editInfo.fb().task_id() == moveFb.at(j)->editInfo.fb().task_id() &&
        cmd->editInfo.fb().fb_id() == moveFb.at(j)->editInfo.fb().fb_id()) {
          cmd->mark = true;
          break;
        }
      }
      if (!cmd->mark) {
        moveFb.append(cmd);
      }
    } else if (cmd->editInfo.element() == Bus::EditElement::LK &&
               cmd->editInfo.edit_type() == Bus::EditType::MV) {
      for (j = 0; j < moveLk.size(); j++) {
        if (cmd->editInfo.lk().mod_id() == moveLk.at(j)->editInfo.lk().mod_id() &&
        cmd->editInfo.lk().task_id() == moveLk.at(j)->editInfo.lk().task_id() &&
        cmd->editInfo.lk().lk_id() == moveLk.at(j)->editInfo.lk().lk_id()) {
          cmd->mark = true;
          break;
        }
      }
      if (!cmd->mark) {
        moveLk.append(cmd);
      }
    } else if (cmd->editInfo.element() == Bus::EditElement::PIN &&
               cmd->editInfo.edit_type() == Bus::EditType::SET) {
      for (j = 0; j < setPin.size(); j++) {
        if (cmd->editInfo.pin().mod_id() == setPin.at(j)->editInfo.pin().mod_id() &&
        cmd->editInfo.pin().task_id() == setPin.at(j)->editInfo.pin().task_id()  &&
        cmd->editInfo.pin().fb_id() == setPin.at(j)->editInfo.pin().fb_id()  &&
        cmd->editInfo.pin().pin_index() == setPin.at(j)->editInfo.pin().pin_index()  ) {
          cmd->mark = true;
          break;
        }
      }
      if (!cmd->mark) {
        setPin.append(cmd);
      }
    } else if (cmd->editInfo.element() == Bus::EditElement::EV &&
               cmd->editInfo.edit_type() == Bus::EditType::SET) {
      for (j = 0; j < setEv.size(); j++) {
        if (cmd->editInfo.ev().ev_id() == setEv.at(j)->editInfo.ev().ev_id()) {
          cmd->mark = true;
          break;
        }
      }
      if (!cmd->mark) {
        setEv.append(cmd);
      }
    } else if (cmd->editInfo.element() == Bus::EditElement::TASK &&
               cmd->editInfo.edit_type() == Bus::EditType::SET) {
      for (j = 0; j < setPrg.size(); j++) {
        if (cmd->editInfo.task().proj_id() == setPrg.at(j)->editInfo.task().proj_id() &&
        cmd->editInfo.task().mod_id() == setPrg.at(j)->editInfo.task().mod_id() &&
        cmd->editInfo.task().task_id() == setPrg.at(j)->editInfo.task().task_id()) {
          cmd->mark = true;
          break;
        }
      }
      if (!cmd->mark) {
        setPrg.append(cmd);
      }
    } else if (cmd->editInfo.element() == Bus::EditElement::MOD &&
               cmd->editInfo.edit_type() == Bus::EditType::SET) {
      for (j = 0; j < setMod.size(); j++) {
        if (cmd->editInfo.mod().proj_id() == setMod.at(j)->editInfo.mod().proj_id() && cmd->editInfo.mod().mod_id() == setMod.at(j)->editInfo.mod().mod_id()) {
          cmd->mark = true;
          break;
        }
      }
      if (!cmd->mark) {
        setMod.append(cmd);
      }
    }
  }

  for (i = list.size() - 1; i >= 0; i--) {
    if (list.at(i).mark) {
      qDebug() << "remove cmd_id:" << list.at(i).editInfo.cmd_id() 
      <<" element:" << list.at(i).editInfo.element() 
      <<" edit_type:" << list.at(i).editInfo.edit_type() ;
      list.removeAt(i);
    }
  }
}

void PLMainModel::extractObjsId(int &idObj, QList<PLEVData> &evs) {
  for (int i = 0; i < evs.size(); i++) {
    evs[i].id = idObj;
    idObj++;
  }
}

bool PLMainModel::extractObjsId(int &idObj, QList<PLFunctionBlock> &fbs,
                                QList<PLLink> &lks) {
  int i, j;
  for (i = 0; i < fbs.size(); i++) {
    fbs[i].idLog = idObj;
    idObj++;
  }
  int step;
  PLLink *lk;
  PLFunctionBlock *fb;
  for (i = 0; i < lks.size(); i++) {
    lk = &lks[i];
    lk->id = idObj;
    idObj++;
    step = 0;
    for (j = 0; j < fbs.size(); j++) {
      fb = &fbs[j];
      if (lk->idFbSrc == fb->id) {
        lk->idFbSrc = fb->idLog;
        step++;
        if (step == 2) {
          break;
        }
      }
      if (lk->idFbTgt == fb->id) {
        lk->idFbTgt = fb->idLog;
        step++;
        if (step == 2) {
          break;
        }
      }
    }
    if (step < 2) {
      return false;
    }
  }
  for (int i = 0; i < fbs.size(); i++) {
    fbs[i].id = fbs[i].idLog;
  }

  return true;
}

bool PLMainModel::extractObjsId(int &idObj, QList<PLProgram> &prgs,
                                QList<PLEVData> &evs,
                                QList<PLCommand> &setpins) {
  PLProgram *prg;
  PLFunctionBlock *fb;
  PLLink *lk;
  PLVLink *vlk;
  int i, j, k, step;

  for (i = 0; i < evs.size(); i++) {
    evs[i].idLog = idObj;
    idObj++;
  }

  for (i = 0; i < prgs.size(); i++) {
    prg = &prgs[i];
    prg->idLog = idObj;
    idObj++;
  }

  for (i = 0; i < prgs.size(); i++) {
    prg = &prgs[i];

    for (j = 0; j < prg->fbs.size(); j++) {
      fb = &prg->fbs[j];
      fb->idLog = idObj;
      idObj++;
      fb->idPrg = prg->idLog;
    }

    for (j = 0; j < prg->lks.size(); j++) {
      lk = &prg->lks[j];
      lk->id = idObj;
      idObj++;
      lk->idPrg = prg->idLog;
      step = 0;
      for (k = 0; k < prg->fbs.size(); k++) {
        fb = &prg->fbs[k];
        if (lk->idFbSrc == fb->id) {
          lk->idFbSrc = fb->idLog;
          step++;
          break;
        }
      }
      if (step < 1) {
        return false;
      }
      step = 0;
      for (k = 0; k < prg->fbs.size(); k++) {
        fb = &prg->fbs[k];
        if (lk->idFbTgt == fb->id) {
          lk->idFbTgt = fb->idLog;
          step++;
          break;
        }
      }
      if (step < 1) {
        return false;
      }
    }

    for (j = 0; j < prg->vis.size(); j++) {
      vlk = &prg->vis[j];
      vlk->id = idObj;
      idObj++;
      step = 0;
      vlk->idPrg = prg->idLog;
      for (k = 0; k < prg->fbs.size(); k++) {
        fb = &prg->fbs[k];
        if (vlk->idFb == fb->id) {
          vlk->idFb = fb->idLog;
          step++;
          break;
        }
      }
      if (step < 1) {
        return false;
      }
      step = 0;
      for (k = 0; k < evs.size(); k++) {
        if (vlk->idEv == evs[k].id) {
          vlk->idEv = evs[k].idLog;
          step++;
          break;
        }
      }
      if (step < 1) {
        return false;
      }
    }

    for (j = 0; j < prg->vos.size(); j++) {
      vlk = &prg->vos[j];
      vlk->id = idObj;
      idObj++;
      step = 0;
      vlk->idPrg = prg->idLog;
      for (k = 0; k < prg->fbs.size(); k++) {
        fb = &prg->fbs[k];
        if (vlk->idFb == fb->id) {
          vlk->idFb = fb->idLog;
          step++;
          break;
        }
      }
      if (step < 1) {
        return false;
      }
      step = 0;
      for (k = 0; k < evs.size(); k++) {
        if (vlk->idEv == evs[k].id) {
          vlk->idEv = evs[k].idLog;
          step++;
          break;
        }
      }
      if (step < 1) {
        return false;
      }
    }
  }

  PLCommand *cmd;
  int idPrg, idFb, pin;
  QStringList list;
  QString value;
  for (i = setpins.size() - 1; i >= 0; i--) {
    cmd = &setpins[i];
    list = cmd->para.split(",");
    idPrg = list.at(0).toInt();
    idFb = list.at(1).toInt();
    pin = list.at(2).toInt();
    value = list.at(3);
    step = 0;
    for (j = 0; j < prgs.size(); j++) {
      prg = &prgs[j];
      if (idPrg == prg->id) {
        idPrg = prg->idLog;
        step++;
        for (k = 0; k < prg->fbs.size(); k++) {
          fb = &prg->fbs[k];
          if (idFb == fb->id) {
            idFb = fb->idLog;
            step++;
            break;
          }
        }
        break;
      }
    }
    if (step < 2) {
      // prg or fb may be deleted!
      setpins.removeAt(i);
    } else {
      cmd->para = QString::asprintf("%d,%d,%d,%s", idPrg, idFb, pin,
                                    value.toLatin1().data());
      cmd->makeCmdLine();
    }
  }

  for (i = 0; i < evs.size(); i++) {
    evs[i].id = evs[i].idLog;
  }

  for (i = 0; i < prgs.size(); i++) {
    prg = &prgs[i];
    prg->id = prg->idLog;
    for (j = 0; j < prg->fbs.size(); j++) {
      fb = &prg->fbs[j];
      fb->id = fb->idLog;
    }
  }

  return true;
}

void PLMainModel::extract() {
  removeDualCommands(cmdList, true);

  int i, j;
  QList<PLCommand> setpins;


  for (i = 0; i < cmdList.size(); i++) {
    if(cmdList.at(i).editInfo.element() == Bus::EditElement::PIN &&
               cmdList.at(i).editInfdit_type() == Bus::EditTyp::SET) 
      setpins.append(cmdList.at(i));
  }
  // int idBase = 1;
  objID = 1;
  extractObjsId(objID, prgList, evList, setpins);

  project.renewUuid();

  cmdList.clear();

  cmdID = 0;
  PLCommand cmd;
  for (i = 0; i < evList.size(); i++) {
    makeEvNewCmd(cmd, evList[i], false);
    cmdList.append(cmd);
  }
  for (i = 0; i < prgList.size(); i++) {
    makePrgNewCmd(cmd, prgList[i], false);
    cmdList.append(cmd);
  }
  PLProgram *prg;
  for (i = 0; i < prgList.size(); i++) {
    prg = &prgList[i];
    for (j = 0; j < prg->fbs.size(); j++) {
      makeFbNewCmd(cmd, prg->fbs[j], false, false);
      cmdList.append(cmd);
    }
    for (j = 0; j < prg->lks.size(); j++) {
      makeLkNewCmd(cmd, prg->lks[j], false);
      cmdList.append(cmd);
    }
    for (j = 0; j < prg->vis.size(); j++) {
      makeViNewCmd(cmd, prg->vis[j], false);
      cmdList.append(cmd);
    }
    for (j = 0; j < prg->vos.size(); j++) {
      makeVoNewCmd(cmd, prg->vos[j], false);
      cmdList.append(cmd);
    }
  }

  for (i = 0; i < setpins.size(); i++) {
    cmd = setpins.at(i);
    cmdID++;
    cmd.id = cmdID;
    cmdList.append(cmd);
  }
}
