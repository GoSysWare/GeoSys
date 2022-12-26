#include "plcommand.h"
#include "gdefine.h"
#include "modules/calc/include/k_project.h"
#include <QStringList>

PLCommand::PLCommand() {}

PLCommand::~PLCommand() { reset(); }

PLCommand::PLCommand(Bus::EditInfo info) { editInfo = info; }

void PLCommand::reset() {
  editInfo.Clear();
  mark = false;
}

bool PLCommand::dispatch() {

  Bus::EditElement element = editInfo.element();
  Bus::EditType type = editInfo.edit_type();

  if (element == Bus::EditElement::PROJ) {
    if (type == Bus::EditType::ADD) {

    } else if (type == Bus::EditType::RM) {

    } else if (type == Bus::EditType::SET) {
      gMainModel->project.uuid =
          QString::fromStdString(editInfo.proj().proj_uuid());
    } else if (type == Bus::EditType::SHOW) {

    } else if (type == Bus::EditType::MV) {

    } else if (type == Bus::EditType::CP) {

    } else if (type == Bus::EditType::PS) {

    } else {
    }

  }

  else if (element == Bus::EditElement::MOD) {
    if (type == Bus::EditType::ADD) {
      PLModule mod;
      setModule(&mod);
      gMainModel->modList.append(mod);
      if (gMainModel->objID < mod.id) {
        gMainModel->objID = mod.id;
      }
    } else if (type == Bus::EditType::RM) {
      removeModule(editInfo.mod().mod_id());
    } else if (type == Bus::EditType::SET) {
      for (int i = 0; i < gMainModel->modList.size(); i++) {
        if (gMainModel->modList[i].id == editInfo.mod().mod_id()) {
          setModule(&gMainModel->modList[i]);
        }
      }

    } else if (type == Bus::EditType::SHOW) {

    } else if (type == Bus::EditType::MV) {

    } else if (type == Bus::EditType::CP) {

    } else if (type == Bus::EditType::PS) {

    } else {
    }

  }

  else if (element == Bus::EditElement::TASK) {
    if (type == Bus::EditType::ADD) {
      PLProgram prg;
      setProgram(&prg);
      for (int i = 0; i < gMainModel->modList.size(); i++) {
        if (gMainModel->modList[i].id == editInfo.task().mod_id()) {
          gMainModel->modList[i].prgList.append(prg);
        }
      }
      if (gMainModel->objID < prg.id) {
        gMainModel->objID = prg.id;
      }
    } else if (type == Bus::EditType::RM) {
      removeProgram(editInfo.task().mod_id(), editInfo.task().task_id());
    } else if (type == Bus::EditType::SET) {
      for (int i = 0; i < gMainModel->modList.size(); i++) {
        if (gMainModel->modList[i].id == editInfo.task().mod_id()) {
          for (int j = 0; j < gMainModel->modList[i].prgList.size(); j++) {
            if (gMainModel->modList[i].prgList[j].id ==
                editInfo.task().task_id()) {
              setProgram(&gMainModel->modList[i].prgList[j]);
            }
          }
        }
      }
    } else if (type == Bus::EditType::SHOW) {

    } else if (type == Bus::EditType::MV) {

    } else if (type == Bus::EditType::CP) {

    } else if (type == Bus::EditType::PS) {

    } else {
    }

  }

  else if (element == Bus::EditElement::EV) {
    if (type == Bus::EditType::ADD) {
        PLEVData ev;
        setEVData(&ev);
        gMainModel->evList.append(ev);
        if(gMainModel->objID < ev.id){
            gMainModel->objID = ev.id;
        }


    } else if (type == Bus::EditType::RM) {

    } else if (type == Bus::EditType::SET) {
        int id = editInfo.ev().ev_id();
        PLEVData *ev = NULL;
        for(int i=0; i<gMainModel->evList.size(); i++){
            if(gMainModel->evList.at(i).id == id){
                ev = &gMainModel->evList[i];
                break;
            }
        }
        if(ev)
        {
          ev->id = editInfo.ev().ev_id();
          ev->initValue.CopyFrom(editInfo.ev().init_val());
          ev->value.CopyFrom(ev->initValue);
          ev->name = QString::fromStdString(editInfo.ev().ev_name());
          ev->desc = QString::fromStdString(editInfo.ev().ev_desc());   
        }
   

    } else if (type == Bus::EditType::SHOW) {

    } else if (type == Bus::EditType::MV) {

    } else if (type == Bus::EditType::CP) {

    } else if (type == Bus::EditType::PS) {

    } else {
    }
  } else if (element == Bus::EditElement::IO) {
    if (type == Bus::EditType::ADD) {

    } else if (type == Bus::EditType::RM) {

    } else if (type == Bus::EditType::SET) {

    } else if (type == Bus::EditType::SHOW) {

    } else if (type == Bus::EditType::MV) {

    } else if (type == Bus::EditType::CP) {

    } else if (type == Bus::EditType::PS) {

    } else {
    }

  } else if (element == Bus::EditElement::FB) {
    Bus::EditType type = editInfo.edit_type();
    if (type == Bus::EditType::ADD) {
      PLFunctionBlock fb;
      setFunctionBlock(&fb);
      PLModule *mod = getModule(fb.idMod);
      if (mod == NULL) {
        return false;
      }
      PLProgram *prg = getProgram(mod, fb.idPrg);
      if (prg == NULL) {
        return false;
      }

      fb_t *p_fb = prj_fbfind(fb.idMod, fb.idPrg, fb.id);
      unsigned int i;
      PLPin pin;
      int h, w, wi = 0, wo = 0;
      // input
      for (i = 0; i < p_fb->ins.size(); i++) {
        pin.type = p_fb->ins[i].t;
        pin.name = QString::fromStdString(p_fb->ins[i].pinname);
        pin.value = *(p_fb->ins[i].v);
        fb.input.append(pin);
        if (wi < pin.name.size()) {
          wi = pin.name.size();
        }
      }
      // output
      for (i = 0; i < p_fb->outs.size(); i++) {
        pin.name = QString::fromStdString(p_fb->outs[i].pinname);
        pin.value = *(p_fb->outs[i].v);
        fb.output.append(pin);
        if (wo < pin.name.size()) {
          wo = pin.name.size();
        }
      }

      // property
      for (i = 0; i < p_fb->props.size(); i++) {
        pin.name = QString::fromStdString(p_fb->props[i].pinname);
        pin.value = *(p_fb->props[i].v);
        fb.property.append(pin);
      }

      fb.flag = p_fb->h.flag;

      h = std::max(p_fb->ins.size(), p_fb->outs.size());

      w = fb.funName.size() + 1;
      if (w < (wi + wo + 2)) {
        w = wi + wo + 2;
      }
      fb.h = h + 1;
      fb.w = w;

      fb.isSelected = true;
      prg->fbs.append(fb);
      if (gMainModel->objID < fb.id) {
        gMainModel->objID = fb.id;
      }

    } else if (type == Bus::EditType::RM) {

    } else if (type == Bus::EditType::SET) {

    } else if (type == Bus::EditType::SHOW) {

    } else if (type == Bus::EditType::MV) {
      int idMod = editInfo.fb().mod_id();
      int idPrg = editInfo.fb().task_id();
      int idFb = editInfo.fb().fb_id();
      PLModule *mod = getModule(idMod);
      if (mod == NULL) {
        return false;
      }
      PLProgram *prg = getProgram(mod, idPrg);
      if (prg == NULL) {
        return false;
      }
      PLFunctionBlock *fb = getFunctionBlock(prg, idFb);
      if (fb == NULL) {
        return false;
      }

      fb->blkName = QString::fromStdString(editInfo.fb().fb_name());
      fb->x = editInfo.pos(0).x();
      fb->y = editInfo.pos(0).y();
    } else if (type == Bus::EditType::CP) {

    } else if (type == Bus::EditType::PS) {

    } else {
    }

  } else if (element == Bus::EditElement::LK) {
    if (type == Bus::EditType::ADD) {

    } else if (type == Bus::EditType::RM) {

    } else if (type == Bus::EditType::SET) {

    } else if (type == Bus::EditType::SHOW) {

    } else if (type == Bus::EditType::MV) {

      int idMod = editInfo.lk().mod_id();
      int idPrg = editInfo.lk().task_id();
      int idLk = editInfo.lk().lk_id();
      PLModule *mod = getModule(idMod);
      if (mod == NULL) {
        return false;
      }
      PLProgram *prg = getProgram(mod, idPrg);
      if (prg == NULL) {
        return false;
      }
      PLLink *lk = getLink(prg, idLk);
      if (lk == NULL) {
        return false;
      }
      setLink(lk, true);
    } else if (type == Bus::EditType::CP) {

    } else if (type == Bus::EditType::PS) {

    } else {
    }

  } else if (element == Bus::EditElement::PIN) {
    if (type == Bus::EditType::ADD) {

    } else if (type == Bus::EditType::RM) {

    } else if (type == Bus::EditType::SET) {

    } else if (type == Bus::EditType::SHOW) {

    } else if (type == Bus::EditType::MV) {

    } else if (type == Bus::EditType::CP) {

    } else if (type == Bus::EditType::PS) {

    } else {
    }
  }

  return true;
}

// bool PLCommand::dispatch()
// {
//     if(fun == "addprg"){
//         PLProgram prg;
//         setProgram(&prg);
//         gMainModel->prgList.append(prg);
//         if(gMainModel->objID < prg.id){
//             gMainModel->objID = prg.id;
//         }
//     }else if(fun == "setprg"){
//         int id = para.toInt();
//         for(int i=0; i<gMainModel->prgList.size(); i++){
//             if(gMainModel->prgList.at(i).id == id){
//                 gMainModel->prgList[i].name = res;
//             }
//         }
//     }else if(fun == "rmprg"){
//         int id = para.toInt();
//         return removeProgram(id);
//     }else if(fun == "addfb"){
//         PLFunctionBlock fb;
//         setFunctionBlock(&fb);
//         PLProgram *prg = getProgram(fb.idPrg);
//         if(prg == NULL){
//             return false;
//         }

//         fb_t *p_fb = prj_fbfind(fb.idPrg, fb.id);
//         unsigned int i;
//         PLPin pin;
//         int h, w, wi=0, wo=0;
//         // input
//         for(i = 0; i < p_fb->ins.size(); i++){
//             pin.type = p_fb->ins[i].t;
//             pin.name = QString::fromStdString( p_fb->ins[i].pinname);
//             pin.value =  *(p_fb->ins[i].v);
//             fb.input.append(pin);
//             if(wi < pin.name.size()){
//                 wi = pin.name.size();
//             }
//         }
//         // output
//         for(i = 0; i < p_fb->outs.size(); i++){
//             pin.name = QString::fromStdString( p_fb->outs[i].pinname);
//             pin.value =  *(p_fb->outs[i].v);
//             fb.output.append(pin);
//             if(wo < pin.name.size()){
//                 wo = pin.name.size();
//             }
//         }

//         // property
//         for(i = 0; i < p_fb->props.size(); i++){
//             pin.name = QString::fromStdString( p_fb->props[i].pinname);
//             pin.value =  *(p_fb->props[i].v);
//             fb.property.append(pin);
//         }

//         fb.flag = p_fb->h.flag;

//         h = std::max(p_fb->ins.size(),p_fb->outs.size());

//         w = fb.funName.size() + 1;
//         if(w < (wi + wo + 2)){
//             w = wi + wo + 2;
//         }
//         fb.h = h + 1;
//         fb.w = w;

//         fb.isSelected = true;
//         prg->fbs.append(fb);
//         if(gMainModel->objID < fb.id){
//             gMainModel->objID = fb.id;
//         }
//     }else if(fun == "mvfb"){
//         QStringList list = para.split(",");
//         int idPrg = list.at(0).toInt();
//         int idFb = list.at(1).toInt();
//         PLProgram *prg = getProgram(idPrg);
//         if(prg == NULL){
//             return false;
//         }
//         PLFunctionBlock *fb = getFunctionBlock(prg, idFb);
//         if(fb == NULL){
//             return false;
//         }
//         list = res.split(",");
//         fb->blkName = list.at(0);
//         fb->x = list.at(1).toInt();
//         fb->y = list.at(2).toInt();
//     }else if(fun == "rmfb"){
//         QStringList list = para.split(",");
//         int idPrg = list.at(0).toInt();
//         int idFb = list.at(1).toInt();
//         PLProgram *prg = getProgram(idPrg);
//         if(prg == NULL){
//             return false;
//         }
//         return removeFunctionBlock(prg, idFb);
//     }else if(fun == "addlk"){
//         PLLink lk;
//         setLink(&lk, false);
//         PLProgram *prg = getProgram(lk.idPrg);
//         if(prg==NULL){
//             return false;
//         }
//         lk.isSelected = true;
//         if(!addLink(prg, &lk)){
//             return false;
//         }
//         if(gMainModel->objID < lk.id){
//             gMainModel->objID = lk.id;
//         }
//     }else if(fun == "mvlk"){
//         QStringList list = para.split(",");
//         int idPrg = list.at(0).toInt();
//         int idLk = list.at(1).toInt();
//         PLProgram *prg = getProgram(idPrg);
//         if(prg == NULL){
//             return false;
//         }
//         PLLink *lk = getLink(prg, idLk);
//         if(lk == NULL){
//             return false;
//         }
//         setLink(lk, true);
//     }else if(fun == "rmlk"){
//         QStringList list = para.split(",");
//         int idPrg = list.at(0).toInt();
//         int idLk = list.at(1).toInt();
//         PLProgram *prg = getProgram(idPrg);
//         if(prg == NULL){
//             return false;
//         }
//         return removeLink(prg, idLk);
//     }else if(fun == "addev"){
//         PLEVData ev;
//         setEVData(&ev);
//         gMainModel->evList.append(ev);
//         if(gMainModel->objID < ev.id){
//             gMainModel->objID = ev.id;
//         }
//     }else if(fun == "rmev"){
//         QStringList list = para.split(",");
//         int id = list.at(0).toInt();
//         return removeEVData(id);
//     }else if(fun == "addvi"){
//         PLVLink vi;
//         setVLink(&vi);
//         PLProgram *prg = getProgram(vi.idPrg);
//         if(prg == NULL){
//             return false;
//         }
//         if(!addVLinkInput(prg, &vi)){
//             return false;
//         }
//         if(gMainModel->objID < vi.id){
//             gMainModel->objID = vi.id;
//         }
//     }else if(fun == "rmvi"){
//         QStringList list = para.split(",");
//         int idPrg = list.at(0).toInt();
//         int idVi = list.at(1).toInt();
//         PLProgram *prg = getProgram(idPrg);
//         if(prg == NULL){
//             return false;
//         }
//         return removeVLinkInput(prg, idVi);
//     }else if(fun == "addvo"){
//         PLVLink vo;
//         setVLink(&vo);
//         PLProgram *prg = getProgram(vo.idPrg);
//         if(prg == NULL){
//             return false;
//         }
//         if(!addVLinkOutput(prg, &vo)){
//             return false;
//         }
//         if(gMainModel->objID < vo.id){
//             gMainModel->objID = vo.id;
//         }
//     }else if(fun == "rmvo"){
//         QStringList list = para.split(",");
//         int idPrg = list.at(0).toInt();
//         int idVo = list.at(1).toInt();
//         PLProgram *prg = getProgram(idPrg);
//         if(prg == NULL){
//             return false;
//         }
//         return removeVLinkOutput(prg, idVo);
//     }else if(fun == "setpin"){
//         QStringList list = para.split(",");
//         int idPrg = list.at(0).toInt();
//         int idFb = list.at(1).toInt();
//         int pin = list.at(2).toInt();
//         QString val = list.at(3);
//         PLProgram *prg = getProgram(idPrg);
//         if(prg == NULL){
//             return false;
//         }
//         PLFunctionBlock *fb = getFunctionBlock(prg, idFb);
//         if(fb == NULL){
//             return false;
//         }

//         value_tm *v = &fb->input[pin].value;
//         *v = str2var(std::string(val.toLatin1()));

//     }else if(fun == "setev"){
//         QStringList list = para.split(",");
//         int id = list.at(0).toInt();
//         QString val = list.at(1);
//         PLEVData *ev = NULL;
//         for(int i=0; i<gMainModel->evList.size(); i++){
//             if(gMainModel->evList.at(i).id == id){
//                 ev = &gMainModel->evList[i];
//                 break;
//             }
//         }
//         ev->initValue  = str2var(std::string(val.toLatin1()));
//         ev->value = ev->initValue;
//         list = res.split(",");
//         ev->name = list.at(0);
//         ev->comment = list.at(1);
//     }else if(fun == "setprj"){
//         gMainModel->project.uuid = para;
//     }

//     gMainModel->isModified = true;

//     return true;
// }

void PLCommand::setModule(PLModule *mod) {
  mod->id = editInfo.mod().mod_id();
  mod->name = QString::fromStdString(editInfo.mod().mod_name());
  mod->desc = QString::fromStdString(editInfo.mod().mod_desc());
  mod->uuid = QString::fromStdString(editInfo.mod().mod_uuid());
}

void PLCommand::setProgram(PLProgram *prg) {
  prg->type = editInfo.task().task_type();
  prg->idMod = editInfo.task().mod_id();
  prg->nameMod = QString::fromStdString(editInfo.task().mod_name());
  prg->id = editInfo.task().task_id();
  prg->name = QString::fromStdString(editInfo.task().task_name());
  prg->desc = QString::fromStdString(editInfo.task().task_desc());
  prg->interval = editInfo.task().interval();
}

bool PLCommand::removeModule(int modId) {
  for (int i = 0; i < gMainModel->modList.size(); i++) {
    if (gMainModel->modList[i].id == modId) {
      gMainModel->modList.removeAt(i);
      return true;
    }
  }
  return false;
}
bool PLCommand::removeProgram(int modId, int prgId) {
  for (int i = 0; i < gMainModel->modList.size(); i++) {
    if (gMainModel->modList[i].id == modId) {
      PLModule *mod = &gMainModel->modList[i];
      for (int j = 0; i < mod->prgList.size(); j++) {
        if (mod->prgList[i].id == prgId) {
          mod->prgList.removeAt(i);
          return true;
        }
      }
    }
  }
  return false;
}

PLEVData *PLCommand::getEv(int id) {
  for (int i = 0; i < gMainModel->evList.size(); i++) {
    if (gMainModel->evList[i].id == id) {
      return &gMainModel->evList[i];
    }
  }

  return NULL;
}

PLProgram *PLCommand::getProgram(PLModule *mod, int idPrg) {
  for (int i = 0; i < mod->prgList.size(); i++) {
    if (mod->prgList[i].id == idPrg) {
      return &mod->prgList[i];
    }
  }
  return NULL;
}
PLModule *PLCommand::getModule(int idMod) {
  for (int i = 0; i < gMainModel->modList.size(); i++) {
    if (gMainModel->modList[i].id == idMod) {
      return &gMainModel->modList[i];
    }
  }
  return NULL;
}
PLVLink *PLCommand::getVi(PLProgram *prg, int idVi) { return NULL; }
PLVLink *PLCommand::getVo(PLProgram *prg, int idVo) { return NULL; }
void PLCommand::setFunctionBlock(PLFunctionBlock *fb) {

  fb->idMod = editInfo.fb().mod_id();
  fb->idPrg = editInfo.fb().task_id();
  fb->id = editInfo.fb().fb_id();

  fb->libName = QString::fromStdString(editInfo.fb().flib_name());
  fb->funName = QString::fromStdString(editInfo.fb().fc_name());
  fb->blkName = QString::fromStdString(editInfo.fb().fb_name());
  fb->x = editInfo.pos(0).x();
  fb->y = editInfo.pos(0).y();
}

PLFunctionBlock *PLCommand::getFunctionBlock(PLProgram *prg, int id) {
  for (int i = 0; i < prg->fbs.size(); i++) {
    if (prg->fbs[i].id == id) {
      return &prg->fbs[i];
    }
  }

  return NULL;
}

bool PLCommand::removeFunctionBlock(PLProgram *prg, int id) {
  for (int i = 0; i < prg->fbs.size(); i++) {
    if (prg->fbs[i].id == id) {
      prg->fbs.removeAt(i);
      return true;
    }
  }

  return false;
}

void PLCommand::setLink(PLLink *lk, bool onlyRes) {
  if (!onlyRes) {
    lk->idMod = editInfo.lk().mod_id();
    lk->idPrg = editInfo.lk().task_id();
    lk->id = editInfo.lk().lk_id();
    lk->idFbSrc = editInfo.lk().src_fb_id();
    lk->pinSrc = editInfo.lk().src_pin_index();
    lk->idFbTgt = editInfo.lk().target_fb_id();
    lk->pinTgt = editInfo.lk().target_pin_index();
  }

  lk->pts.clear();

  for (int i = 0; i < editInfo.pos().size(); i++) {
    PLPoint pt(editInfo.pos(i).x(), editInfo.pos(i).y());
    lk->pts.append(pt);
  }
}

PLLink *PLCommand::getLink(PLProgram *prg, int id) {
  for (int i = 0; i < prg->lks.size(); i++) {
    if (prg->lks.at(i).id == id) {
      return &prg->lks[i];
    }
  }

  return NULL;
}

bool PLCommand::removeLink(PLProgram *prg, int id) {
  for (int i = 0; i < prg->lks.size(); i++) {
    if (prg->lks.at(i).id == id) {
      PLFunctionBlock *fb = getFunctionBlock(prg, prg->lks[i].idFbTgt);
      fb->input[prg->lks[i].pinTgt].hasInputLink = false;

      prg->lks.removeAt(i);
      return true;
    }
  }

  return false;
}

bool PLCommand::addLink(PLProgram *prg, PLLink *lk) {
  PLFunctionBlock *fb;
  fb = getFunctionBlock(prg, lk->idFbSrc);
  if (fb == NULL) {
    return false;
  }
  if (lk->pinSrc >= fb->output.size()) {
    return false;
  }
  lk->pin = &fb->output[lk->pinSrc];

  fb = getFunctionBlock(prg, lk->idFbTgt);
  if (fb == NULL) {
    return false;
  }
  if (lk->pinTgt >= fb->input.size()) {
    return false;
  }
  fb->input[lk->pinTgt].hasInputLink = true;

  prg->lks.append(*lk);
  return true;
}

void PLCommand::setEVData(PLEVData *ev) {
  ev->id = editInfo.ev().ev_id();
  ev->id = editInfo.ev().ev_type();
  ev->name = QString::fromStdString(editInfo.ev().ev_name());
  ev->desc = QString::fromStdString(editInfo.ev().ev_desc());
  ev->refIn = 0;
  ev->refOut = 0;
  ev->initValue.CopyFrom(editInfo.ev().init_val());
  ev->value.CopyFrom(ev->initValue);
}

bool PLCommand::removeEVData(int id) {
  for (int i = 0; i < gMainModel->evList.size(); i++) {
    if (gMainModel->evList[i].id == id) {
      gMainModel->evList.removeAt(i);
      return true;
    }
  }

  return false;
}

void PLCommand::setVLink(PLVLink *vlk) {
  //   QStringList list;
  //   list = para.split(",");
  //   vlk->idPrg = list.at(0).toInt();
  //   vlk->id = list.at(1).toInt();
  //   vlk->idEv = list.at(2).toInt();
  //   vlk->idFb = list.at(3).toInt();
  //   vlk->idPin = list.at(4).toInt();
  //   ;
}

bool PLCommand::addVLinkInput(PLProgram *prg, PLVLink *vlk) {
  //   bool b1 = false, b2 = false;
  //   int i;
  //   for (i = 0; i < prg->fbs.size(); i++) {
  //     if (vlk->idFb == prg->fbs.at(i).id) {
  //       vlk->fb = &prg->fbs[i];
  //       if (prg->fbs.at(i).input.size() <= vlk->idPin) {
  //         return false;
  //       }
  //       vlk->pin = &prg->fbs[i].input[vlk->idPin];
  //       vlk->pin->hasVariable = true;
  //       b1 = true;
  //       break;
  //     }
  //   }

  //   for (i = 0; i < gMainModel->evList.size(); i++) {
  //     if (vlk->idEv == gMainModel->evList.at(i).id) {
  //       vlk->ev = &gMainModel->evList[i];
  //       gMainModel->evList[i].refIn++;
  //       b2 = true;
  //       break;
  //     }
  //   }

  //   if (b1 && b2) {
  //     vlk->isInput = true;
  //     prg->vis.append(*vlk);
  //     return true;
  //   } else {
  //     return false;
  //   }
  return false;
}

bool PLCommand::removeVLinkInput(PLProgram *prg, int id) {
  //   for (int i = 0; i < prg->vis.size(); i++) {
  //     if (prg->vis.at(i).id == id) {
  //       prg->vis[i].ev->refIn--;
  //       prg->vis[i].pin->hasVariable = false;
  //       prg->vis.removeAt(i);
  //       return true;
  //     }
  //   }

  // qDebug() << "remove vi";
  return false;
}

bool PLCommand::addVLinkOutput(PLProgram *prg, PLVLink *vlk) {
  //   bool b1 = false, b2 = false;
  //   int i;
  //   for (i = 0; i < prg->fbs.size(); i++) {
  //     if (vlk->idFb == prg->fbs.at(i).id) {
  //       vlk->fb = &prg->fbs[i];
  //       if (prg->fbs.at(i).output.size() <= vlk->idPin) {
  //         return false;
  //       }
  //       vlk->pin = &prg->fbs[i].output[vlk->idPin];
  //       vlk->pin->hasVariable = true;
  //       b1 = true;
  //       break;
  //     }
  //   }

  //   for (i = 0; i < gMainModel->evList.size(); i++) {
  //     if (vlk->idEv == gMainModel->evList.at(i).id) {
  //       vlk->ev = &gMainModel->evList[i];
  //       gMainModel->evList[i].refOut++;
  //       b2 = true;
  //       break;
  //     }
  //   }

  //   if (b1 && b2) {
  //     vlk->isInput = false;
  //     prg->vos.append(*vlk);
  //     return true;
  //   } else {
  //     return false;
  //   }
  return false;
}

bool PLCommand::removeVLinkOutput(PLProgram *prg, int id) {
  //   for (int i = 0; i < prg->vos.size(); i++) {
  //     if (prg->vos.at(i).id == id) {
  //       prg->vos[i].ev->refOut--;
  //       prg->vos[i].pin->hasVariable = false;
  //       prg->vos.removeAt(i);
  //       return true;
  //     }
  //   }

  // qDebug() << "remove vo";
  return false;
}
