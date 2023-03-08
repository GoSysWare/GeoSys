#include "plmainmodel.h"
#include "modules/calc/include/k_command.h"
#include "modules/calc/include/k_functionblock.h"
#include "modules/calc/include/k_lib.h"
#include "modules/calc/include/k_project.h"
#include <QFile>
#include <QTextStream>

#include <google/protobuf/util/message_differencer.h>

using namespace google::protobuf::util;

PLMainModel::PLMainModel() {
  cmdID = 0;
  objID = 0;
  prgCurrent = NULL;
  modCurrent = NULL;

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
  modCurrent = NULL;

  modList.clear();
  cmdList.clear();
  modelEVData.beginReset();
  evList.clear();
  modelEVData.endReset();
  project.clear();

  prj_reset();
}
void PLMainModel::updateModuleList() {
  QStringList list;

  for (int i = 0; i < modList.size(); i++) {
    PLModule mod = modList[i];
    list << mod.name;
  }

  modelModule.setStringList(list);
}

void PLMainModel::updateProgList(int modIndex) {
  QStringList list;

  for (int i = 0; i < modList.size(); i++) {
    if (modList[i].id == modIndex) {
      PLModule mod = modList[i];
      for (int j = 0; j < mod.prgList.size(); j++) {
        PLProgram prg = mod.prgList[j];
        list << prg.name;
      }
    }
  }
  modelProgram.setStringList(list);
}

bool PLMainModel::exeCommand(PLCommand &cmd) {
  if (cmdID < cmd.editInfo.cmd_id()) {
    cmdID = cmd.editInfo.cmd_id();
    // qDebug() << "command id:" << cmdID;
  }

  cmd_dispatch(cmd.editInfo);

  if (!cmd.dispatch()) {
    return false;
  }

  // SET PROJ 不进入cmd列表
  if (!(cmd.editInfo.element() == Bus::EditElement::PROJ &&
        cmd.editInfo.edit_type() == Bus::EditType::SET)) {
    cmdList.append(cmd);
  }

  return true;
}

void PLMainModel::makeLkNewCmd(PLCommand &cmd, PLLink &lk, bool newId) {
  cmd.reset();

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
  cmd.reset();

  cmdID++;
  cmd.editInfo.set_cmd_id(cmdID);
  cmd.editInfo.set_element(Bus::EditElement::LK);
  cmd.editInfo.set_edit_type(Bus::EditType::RM);
  cmd.editInfo.mutable_lk()->set_mod_id(lk.idMod);
  cmd.editInfo.mutable_lk()->set_task_id(lk.idPrg);
  cmd.editInfo.mutable_lk()->set_lk_id(lk.id);
}

void PLMainModel::makeLkMoveCmd(PLCommand &cmd, PLLink &lk) {
  cmd.reset();

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
  cmd.reset();

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
  cmd.reset();

  cmdID++;
  cmd.editInfo.set_cmd_id(cmdID);
  cmd.editInfo.set_element(Bus::EditElement::FB);
  cmd.editInfo.set_edit_type(Bus::EditType::RM);
  cmd.editInfo.mutable_fb()->set_mod_id(fb.idMod);
  cmd.editInfo.mutable_fb()->set_task_id(fb.idPrg);
  cmd.editInfo.mutable_fb()->set_fb_id(fb.id);
}

void PLMainModel::makeFbMoveCmd(PLCommand &cmd, PLFunctionBlock &fb) {
  cmd.reset();

  cmdID++;
  cmd.editInfo.set_cmd_id(cmdID);
  cmd.editInfo.set_element(Bus::EditElement::FB);
  cmd.editInfo.set_edit_type(Bus::EditType::MV);
  cmd.editInfo.mutable_fb()->set_mod_id(fb.idMod);
  cmd.editInfo.mutable_fb()->set_task_id(fb.idPrg);
  cmd.editInfo.mutable_fb()->set_fb_id(fb.id);
  cmd.editInfo.mutable_fb()->set_fb_name(fb.blkName.toStdString());

  auto pos = cmd.editInfo.add_pos();
  pos->set_x(fb.x);
  pos->set_y(fb.y);
}

void PLMainModel::makeViNewCmd(PLCommand &cmd, PLVLink &vlk, bool newId) {
  cmd.reset();

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
  cmd.reset();

  cmdID++;
  cmd.editInfo.set_cmd_id(cmdID);
  cmd.editInfo.set_element(Bus::EditElement::VI);
  cmd.editInfo.set_edit_type(Bus::EditType::RM);
  cmd.editInfo.mutable_vi()->set_vi_id(vlk.id);
  cmd.editInfo.mutable_vi()->set_mod_id(vlk.idMod);
  cmd.editInfo.mutable_vi()->set_task_id(vlk.idPrg);
}

void PLMainModel::makeVoNewCmd(PLCommand &cmd, PLVLink &vlk, bool newId) {
  cmd.reset();

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
  cmd.reset();

  cmdID++;
  cmd.editInfo.set_cmd_id(cmdID);
  cmd.editInfo.set_element(Bus::EditElement::VO);
  cmd.editInfo.set_edit_type(Bus::EditType::RM);
  cmd.editInfo.mutable_vo()->set_vo_id(vlk.id);
  cmd.editInfo.mutable_vo()->set_mod_id(vlk.idMod);
  cmd.editInfo.mutable_vo()->set_task_id(vlk.idPrg);
}

void PLMainModel::makeEvNewCmd(PLCommand &cmd, PLEVData &ev, bool newId) {
  cmd.reset();

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
  cmd.reset();

  cmdID++;
  cmd.editInfo.set_cmd_id(cmdID);
  cmd.editInfo.set_element(Bus::EditElement::EV);
  cmd.editInfo.set_edit_type(Bus::EditType::SET);
  cmd.editInfo.mutable_ev()->set_ev_id(ev.id);
  cmd.editInfo.mutable_ev()->set_ev_name(ev.name.toStdString());
  cmd.editInfo.mutable_ev()->set_ev_type(ev.type);
  cmd.editInfo.mutable_ev()->set_ev_desc(ev.desc.toStdString());
  cmd.editInfo.mutable_ev()->mutable_init_val()->CopyFrom(ev.initValue);
}

void PLMainModel::makeEvRemoveCmd(PLCommand &cmd, PLEVData &ev) {
  cmd.reset();

  cmdID++;
  cmd.editInfo.set_cmd_id(cmdID);
  cmd.editInfo.set_element(Bus::EditElement::EV);
  cmd.editInfo.set_edit_type(Bus::EditType::RM);
  cmd.editInfo.mutable_ev()->set_ev_id(ev.id);
}

void PLMainModel::makePrgNewCmd(PLCommand &cmd, PLProgram &prg, bool newId) {
  cmd.reset();

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
  cmd.editInfo.mutable_task()->set_interval(prg.interval);
}

void PLMainModel::makePrgRemoveCmd(PLCommand &cmd, PLProgram &prg) {
  cmd.reset();

  cmdID++;
  cmd.editInfo.set_cmd_id(cmdID);
  cmd.editInfo.set_element(Bus::EditElement::TASK);
  cmd.editInfo.set_edit_type(Bus::EditType::RM);
  cmd.editInfo.mutable_task()->set_mod_id(prg.idMod);
  cmd.editInfo.mutable_task()->set_task_id(prg.id);
}

void PLMainModel::makePrgRenameCmd(PLCommand &cmd, PLProgram &prg) {
  cmd.reset();

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
  cmd.reset();
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
  cmd.reset();

  cmdID++;
  cmd.editInfo.set_cmd_id(cmdID);
  cmd.editInfo.set_element(Bus::EditElement::MOD);
  cmd.editInfo.set_edit_type(Bus::EditType::RM);
  cmd.editInfo.mutable_mod()->set_mod_id(mod.id);
}
void PLMainModel::makeModRenameCmd(PLCommand &cmd, PLModule &mod) {
  cmd.reset();

  cmdID++;
  cmd.editInfo.set_cmd_id(cmdID);
  cmd.editInfo.set_element(Bus::EditElement::MOD);
  cmd.editInfo.set_edit_type(Bus::EditType::SET);
  cmd.editInfo.mutable_mod()->set_mod_id(mod.id);
  cmd.editInfo.mutable_mod()->set_mod_name(mod.name.toStdString());
  cmd.editInfo.mutable_mod()->set_mod_desc(mod.desc.toStdString());
}
void PLMainModel::makePinSetCmd(PLCommand &cmd, int idMod, int idPrg, int idFb,
                                int idPin, value_tm val) {
  cmd.reset();

  cmdID++;
  cmd.editInfo.set_cmd_id(cmdID);
  cmd.editInfo.set_element(Bus::EditElement::PIN);
  cmd.editInfo.set_edit_type(Bus::EditType::SET);
  cmd.editInfo.mutable_pin()->set_mod_id(idMod);
  cmd.editInfo.mutable_pin()->set_task_id(idPrg);
  cmd.editInfo.mutable_pin()->set_fb_id(idFb);
  cmd.editInfo.mutable_pin()->set_pin_index(idPin);
  cmd.editInfo.mutable_pin()->mutable_pin_val()->CopyFrom(val);
}

void PLMainModel::makeLkCopyCmd(PLCommand &cmd, PLLink &lk) {
  cmd.reset();

  cmd.editInfo.set_cmd_id(-1);
  cmd.editInfo.set_element(Bus::EditElement::LK);
  cmd.editInfo.set_edit_type(Bus::EditType::CP);
  cmd.editInfo.mutable_lk()->set_mod_id(lk.idMod);
  cmd.editInfo.mutable_lk()->set_task_id(lk.idPrg);
  cmd.editInfo.mutable_lk()->set_lk_id(lk.id);
  cmd.editInfo.mutable_lk()->set_src_fb_id(lk.idFbSrc);
  cmd.editInfo.mutable_lk()->set_src_pin_index(lk.pinSrc);
  cmd.editInfo.mutable_lk()->set_target_fb_id(lk.idFbTgt);
  cmd.editInfo.mutable_lk()->set_target_pin_index(lk.pinTgt);

  for (int i = 0; i < lk.pts.size(); i++) {
    auto pos = cmd.editInfo.add_pos();
    pos->set_x(lk.pts.at(i).x);
    pos->set_y(lk.pts.at(i).y);
  }
}

void PLMainModel::makeFbCopyCmd(PLCommand &cmd, PLFunctionBlock &fb) {
  cmd.reset();

  cmd.editInfo.set_cmd_id(-1);
  cmd.editInfo.set_element(Bus::EditElement::FB);
  cmd.editInfo.set_edit_type(Bus::EditType::CP);
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

bool PLMainModel::isCmdObjRemoved(PLCommand *cmd) {

  if (cmd->editInfo.element() == Bus::EditElement::MOD &&
      (cmd->editInfo.edit_type() == Bus::EditType::ADD ||
       cmd->editInfo.edit_type() == Bus::EditType::RM)) {
    if (NULL == PLCommand::getModule(cmd->editInfo.mod().mod_id())) {
      return true;
    }
  } else if (cmd->editInfo.element() == Bus::EditElement::TASK &&
             (cmd->editInfo.edit_type() == Bus::EditType::ADD ||
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
             (cmd->editInfo.edit_type() == Bus::EditType::ADD ||
              cmd->editInfo.edit_type() == Bus::EditType::RM ||
              cmd->editInfo.edit_type() == Bus::EditType::SET)) {
    if (NULL == PLCommand::getEv(cmd->editInfo.ev().ev_id())) {
      return true;
    }
  } else if (cmd->editInfo.element() == Bus::EditElement::FB &&
             (cmd->editInfo.edit_type() == Bus::EditType::ADD ||
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
             (cmd->editInfo.edit_type() == Bus::EditType::ADD ||
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
             (cmd->editInfo.edit_type() == Bus::EditType::ADD ||
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
             (cmd->editInfo.edit_type() == Bus::EditType::ADD ||
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

void PLMainModel::removeDualCommands(QList<PLCommand> &cmdList, bool all) {
  QList<PLCommand *> moveFbCmdList;
  QList<PLCommand *> moveLkCmdList;
  QList<PLCommand *> setPinCmdList;
  QList<PLCommand *> setEvCmdList;
  QList<PLCommand *> setPrgCmdList;
  QList<PLCommand *> setModCmdList;

  int i, j;
  PLCommand *cmd;
  for (i = cmdList.size() - 1; i >= 0; i--) {
    cmd = &cmdList[i];
    cmd->mark = false;
    if (all) {
      if (isCmdObjRemoved(cmd)) {
        cmd->mark = true;
      }
    }
    if (cmd->editInfo.element() == Bus::EditElement::FB &&
        cmd->editInfo.edit_type() == Bus::EditType::MV) {

      for (j = 0; j < moveFbCmdList.size(); j++) {
        if (MessageDifferencer::Equivalent(
                cmd->editInfo.fb(), moveFbCmdList.at(j)->editInfo.fb())) {
          cmd->mark = true;
          break;
        }
      }
      if (!cmd->mark) {
        moveFbCmdList.append(cmd);
      }
    } else if (cmd->editInfo.element() == Bus::EditElement::LK &&
               cmd->editInfo.edit_type() == Bus::EditType::MV) {
      for (j = 0; j < moveLkCmdList.size(); j++) {
        if (MessageDifferencer::Equivalent(
                cmd->editInfo.lk(), moveLkCmdList.at(j)->editInfo.lk())) {
          cmd->mark = true;
          break;
        }
      }
      if (!cmd->mark) {
        moveLkCmdList.append(cmd);
      }
    } else if (cmd->editInfo.element() == Bus::EditElement::PIN &&
               cmd->editInfo.edit_type() == Bus::EditType::SET) {
      for (j = 0; j < setPinCmdList.size(); j++) {
        if (MessageDifferencer::Equivalent(
                cmd->editInfo.pin(), setPinCmdList.at(j)->editInfo.pin())) {
          cmd->mark = true;
          break;
        }
      }
      if (!cmd->mark) {
        setPinCmdList.append(cmd);
      }
    } else if (cmd->editInfo.element() == Bus::EditElement::EV &&
               cmd->editInfo.edit_type() == Bus::EditType::SET) {
      for (j = 0; j < setEvCmdList.size(); j++) {
        if (MessageDifferencer::Equivalent(cmd->editInfo.ev(),
                                           setEvCmdList.at(j)->editInfo.ev())) {
          cmd->mark = true;
          break;
        }
      }
      if (!cmd->mark) {
        setEvCmdList.append(cmd);
      }
    } else if (cmd->editInfo.element() == Bus::EditElement::TASK &&
               cmd->editInfo.edit_type() == Bus::EditType::SET) {
      for (j = 0; j < setPrgCmdList.size(); j++) {
        if (MessageDifferencer::Equivalent(
                cmd->editInfo.task(), setPrgCmdList.at(j)->editInfo.task())) {
          cmd->mark = true;
          break;
        }
      }
      if (!cmd->mark) {
        setPrgCmdList.append(cmd);
      }
    } else if (cmd->editInfo.element() == Bus::EditElement::MOD &&
               cmd->editInfo.edit_type() == Bus::EditType::SET) {
      for (j = 0; j < setModCmdList.size(); j++) {
        if (MessageDifferencer::Equivalent(
                cmd->editInfo.mod(), setModCmdList.at(j)->editInfo.mod())) {
          cmd->mark = true;
          break;
        }
      }
      if (!cmd->mark) {
        setModCmdList.append(cmd);
      }
    }
  }

  for (i = cmdList.size() - 1; i >= 0; i--) {
    if (cmdList.at(i).mark) {
      // qDebug() << "remove cmd_id:"
      //          << QString::fromStdString(cmdList.at(i).editInfo.DebugString());
      cmdList.removeAt(i);
    }
  }
}

void PLMainModel::extractObjsId(int &idObj, QList<PLEVData> &evs) {
  for (int i = 0; i < evs.size(); i++) {
    evs[i].id = idObj;
    idObj++;
  }
}
// 在复制粘贴的过程中，重新关联cmdid
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

bool PLMainModel::extractObjsId(int &idObj, QList<PLModule> &mods,
                                QList<PLEVData> &evs,
                                QList<PLCommand> &setpins) {
  PLModule *mod;
  PLProgram *prg;
  PLFunctionBlock *fb;
  PLLink *lk;
  PLVLink *vlk;
  int i, j, k, m, step;

  // idLog是重新排序后的cmd_id,所有子项按顺序计数
  // ev在前
  for (i = 0; i < evs.size(); i++) {
    evs[i].idLog = idObj;
    idObj++;
  }

  for (m = 0; m < mods.size(); m++) {
    mod = &mods[m];
    // 记录module的新id
    // 注意旧的id还有用，此时旧id不能被修改
    mod->idLog = idObj;
    idObj++;
    for (i = 0; i < mod->prgList.size(); i++) {
      prg = &mod->prgList[i];
      prg->idLog = idObj;
      idObj++;

      // 需要提前把所有的fb的新id算出来，因为后面几个子项都是关联它的
      for (j = 0; j < prg->fbs.size(); j++) {
        fb = &prg->fbs[j];
        fb->idLog = idObj;
        idObj++;
      }

      for (j = 0; j < prg->lks.size(); j++) {
        lk = &prg->lks[j];
        lk->idLog = idObj;
        idObj++;
        step = 0;
        for (k = 0; k < prg->fbs.size(); k++) {
          fb = &prg->fbs[k];
          //如果找到，则把新的fb的id赋给lk的源id
          if (lk->idFbSrc == fb->id) {
            lk->idFbSrc = fb->idLog;
            step++;
            break;
          }
        }
        // 没有找到lk的关联的源fb
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
        // 没有找到lk的关联的目标fb
        if (step < 1) {
          return false;
        }
      }

      for (j = 0; j < prg->vis.size(); j++) {
        vlk = &prg->vis[j];
        vlk->idLog = idObj;
        idObj++;
        step = 0;
        for (k = 0; k < prg->fbs.size(); k++) {
          fb = &prg->fbs[k];
          if (vlk->idFb == fb->id) {
            vlk->idFb = fb->idLog;
            step++;
            break;
          }
        }
        // 没有找到vi的关联的源fb
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
        // 没有找到vi的关联的EV
        if (step < 1) {
          return false;
        }
      }

      for (j = 0; j < prg->vos.size(); j++) {
        vlk = &prg->vos[j];
        vlk->idLog = idObj;
        idObj++;
        step = 0;
        for (k = 0; k < prg->fbs.size(); k++) {
          fb = &prg->fbs[k];
          if (vlk->idFb == fb->id) {
            vlk->idFb = fb->idLog;
            step++;
            break;
          }
        }
        // 没有找到vo的关联的源fb
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
        // 没有找到vo的关联的EV
        if (step < 1) {
          return false;
        }
      }
    }
  }

  PLCommand *cmd;
  int idMod, idPrg, idFb, pin;
  QStringList list;
  value_tm value;
  for (i = setpins.size() - 1; i >= 0; i--) {
    cmd = &setpins[i];
    idMod = cmd->editInfo.mutable_pin()->mod_id();
    idPrg = cmd->editInfo.mutable_pin()->task_id();
    idFb = cmd->editInfo.mutable_pin()->fb_id();
    pin = cmd->editInfo.mutable_pin()->pin_index();
    step = 0;
    for (m = 0; m < mods.size(); m++) {
      mod = &mods[m];
      if (idMod == mod->id) {
        idMod = mod->idLog;
        step++;
        for (j = 0; j < mod->prgList.size(); j++) {
          prg = &mod->prgList[j];
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
      }
    }
    //如果一个setpin指令中没有同时满足有modid、progid和fbid，则说明此命令无效
    if (step < 3) {
      // prg or fb may be deleted!
      setpins.removeAt(i);
    } else {
      // 满足则重新封装id
      cmd->editInfo.mutable_pin()->set_mod_id(idMod);
      cmd->editInfo.mutable_pin()->set_task_id(idPrg);
      cmd->editInfo.mutable_pin()->set_fb_id(idFb);
      cmd->editInfo.mutable_pin()->set_pin_index(pin);
    }
  }

  for (i = 0; i < evs.size(); i++) {
    evs[i].id = evs[i].idLog;
  }

  //  更新各个子项的cmdid 都赋值新id
  for (m = 0; m < mods.size(); m++) {
    mod = &mods[m];
    mod->id = mod->idLog;
    for (i = 0; i < mod->prgList.size(); i++) {
      prg = &mod->prgList[i];
      prg->idMod = mod->id;
      prg->id = prg->idLog;
      for (j = 0; j < prg->fbs.size(); j++) {
        fb = &prg->fbs[j];
        fb->idMod = mod->id;
        fb->idPrg = prg->id;
        fb->id = fb->idLog;
      }
      for (j = 0; j < prg->lks.size(); j++) {
        lk = &prg->lks[j];
        lk->idMod = mod->id;
        lk->idPrg = prg->id;
        lk->id = lk->idLog;
      }
      for (j = 0; j < prg->vis.size(); j++) {
        vlk = &prg->vis[j];
        vlk->idMod = mod->id;
        vlk->idPrg = prg->id;
        vlk->id = vlk->idLog;
      }
      for (j = 0; j < prg->vos.size(); j++) {
        vlk = &prg->vos[j];
        vlk->idMod = mod->id;
        vlk->idPrg = prg->id;
        vlk->id = vlk->idLog;
      }
    }
  }

  return true;
}

void PLMainModel::extract() {
  removeDualCommands(cmdList, true);

  int i, j, m;
  QList<PLCommand> setpins;
  PLModule *mod;
  PLProgram *prg;
  for (i = 0; i < cmdList.size(); i++) {
    if (cmdList.at(i).editInfo.element() == Bus::EditElement::PIN &&
        cmdList.at(i).editInfo.edit_type() == Bus::EditType::SET)
      setpins.append(cmdList.at(i));
  }
  // int idBase = 1;
  objID = 1;
  //根据命令重新整理所有的id
  extractObjsId(objID, modList, evList, setpins);

  project.renewUuid();

  cmdList.clear();

  cmdID = 0;
  PLCommand cmd;
  for (i = 0; i < evList.size(); i++) {
    makeEvNewCmd(cmd, evList[i], false);
    cmdList.append(cmd);
  }

  for (m = 0; m < modList.size(); m++) {
    mod = &modList[m];

    mod->renewUuid();
    makeModNewCmd(cmd, *mod, false);
    cmdList.append(cmd);

    for (i = 0; i < mod->prgList.size(); i++) {
      prg = &mod->prgList[i];

      makePrgNewCmd(cmd, *prg, false);
      cmdList.append(cmd);

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
  }

  for (i = 0; i < setpins.size(); i++) {
    cmd = setpins.at(i);
    cmdID++;
    cmd.editInfo.set_cmd_id(cmdID);
    cmdList.append(cmd);
  }
}
