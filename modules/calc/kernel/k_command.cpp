#include "modules/calc/include/k_command.h"
#include "modules/calc/include/k_evdata.h"
#include "modules/calc/include/k_lib.h"
#include "modules/calc/include/k_project.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int cmd_dispatch(const Bus::EditInfo &edit_info) {
  std::cout << edit_info.DebugString()<<std::endl;

  Bus::EditElement element = edit_info.element();
  Bus::EditType type = edit_info.edit_type();

  if (element == Bus::EditElement::PROJ) {
    if (type == Bus::EditType::ADD) {

    } else if (type == Bus::EditType::RM) {

    } else if (type == Bus::EditType::SET) {
      prjinfo_t *info;
      info = prj_info();
      info->uuid = edit_info.proj().proj_uuid();
    } else if (type == Bus::EditType::SHOW) {

    } else {
    }

  } else if (element == Bus::EditElement::MOD) {
    if (type == Bus::EditType::ADD) {
      prj_modadd(edit_info.mod().mod_id(), edit_info.mod().mod_name(),
                 edit_info.mod().mod_desc());

    } else if (type == Bus::EditType::RM) {
      prj_modremove(edit_info.mod().mod_id());

    } else if (type == Bus::EditType::SET) {

    } else if (type == Bus::EditType::SHOW) {

    } else {
    }
  } else if (element == Bus::EditElement::TASK) {
    if (type == Bus::EditType::ADD) {

      prj_prgadd(edit_info.task().mod_id(), edit_info.task().task_id(),
                 edit_info.task().task_name(), edit_info.task().task_type(),
                 edit_info.task().task_desc(), edit_info.task().interval());

    } else if (type == Bus::EditType::RM) {
      prj_prgremove(edit_info.task().mod_id(), edit_info.task().task_id());
    } else if (type == Bus::EditType::SET) {

    } else if (type == Bus::EditType::SHOW) {

    } else {
    }
  } else if (element == Bus::EditElement::EV) {
    if (type == Bus::EditType::ADD) {
      ev_add(edit_info.ev().ev_id(), edit_info.ev().ev_name(),
             edit_info.ev().init_val());

    } else if (type == Bus::EditType::RM) {
      ev_remove(edit_info.ev().ev_id());

    } else if (type == Bus::EditType::SET) {

      vam_t * p_val = ev_find_v(edit_info.ev().ev_id());
      p_val->get()->CopyFrom(edit_info.ev().real_val());

    } else if (type == Bus::EditType::SHOW) {

    } else {
    }
  } else if (element == Bus::EditElement::IO) {
    if (type == Bus::EditType::ADD) {

    } else if (type == Bus::EditType::RM) {

    } else if (type == Bus::EditType::SET) {

    } else if (type == Bus::EditType::SHOW) {

    } else {
    }
  } else if (element == Bus::EditElement::FB) {
    if (type == Bus::EditType::ADD) {
      prj_fbadd(edit_info.fb().mod_id(), edit_info.fb().task_id(),
                edit_info.fb().fb_id(), edit_info.fb().flib_name(),
                edit_info.fb().fc_name(), edit_info.fb().fb_name());

    } else if (type == Bus::EditType::RM) {
      prj_fbremove(edit_info.fb().mod_id(), edit_info.fb().task_id(),
                   edit_info.fb().fb_id());
    } else if (type == Bus::EditType::SET) {

    } else if (type == Bus::EditType::SHOW) {

    } else {
    }
  } else if (element == Bus::EditElement::LK) {
    if (type == Bus::EditType::ADD) {
      prj_lkadd(edit_info.lk().mod_id(), edit_info.lk().task_id(),
                edit_info.lk().lk_id(), edit_info.lk().src_fb_id(),
                edit_info.lk().src_pin_index(), edit_info.lk().target_fb_id(),
                edit_info.lk().target_pin_index());
    } else if (type == Bus::EditType::RM) {
      prj_lkremove(edit_info.lk().mod_id(), edit_info.lk().task_id(),
                   edit_info.lk().lk_id());
    } else if (type == Bus::EditType::SET) {

    } else if (type == Bus::EditType::SHOW) {

    } else {
    }
  } else if (element == Bus::EditElement::PIN) {
    if (type == Bus::EditType::ADD) {

    } else if (type == Bus::EditType::RM) {

    } else if (type == Bus::EditType::SET) {

      fb_t *p_fb;
      p_fb = prj_fbfind(edit_info.pin().mod_id(), edit_info.pin().task_id(),
                        edit_info.pin().fb_id());

      fb_setpin(p_fb, PININPUT, edit_info.pin().pin_index(),
                edit_info.pin().pin_val());

    } else if (type == Bus::EditType::SHOW) {

    } else {
    }
  }else if (element == Bus::EditElement::VI) {
    if (type == Bus::EditType::ADD) {

       prj_viadd(edit_info.vi().mod_id(),edit_info.vi().task_id(),edit_info.vi().ev_id(),edit_info.vi().fb_id(),edit_info.vi().pin_index());


    } else if (type == Bus::EditType::RM) {
       prj_viremove(edit_info.vi().mod_id(),edit_info.vi().task_id(),edit_info.vi().fb_id(),edit_info.vi().pin_index());

    } else if (type == Bus::EditType::SET) {


    } else if (type == Bus::EditType::SHOW) {

    } else {
    }
  }else if (element == Bus::EditElement::VO) {
    if (type == Bus::EditType::ADD) {
       prj_voadd(edit_info.vo().mod_id(),edit_info.vo().task_id(),edit_info.vo().ev_id(),edit_info.vo().fb_id(),edit_info.vo().pin_index());

    } else if (type == Bus::EditType::RM) {
       prj_viremove(edit_info.vo().mod_id(),edit_info.vo().task_id(),edit_info.vo().fb_id(),edit_info.vo().pin_index());

    } else if (type == Bus::EditType::SET) {


    } else if (type == Bus::EditType::SHOW) {

    } else {
    }
  }

  return 0;
}

int cmds_dispatch(const Bus::EditInfos &edit_infos) {

  int info_size = edit_infos.infos_size();
  for (auto i = 0; i < info_size; i++) {
    prjinfo_t *info = prj_info();
    if (info->cmd_id < edit_infos.infos(i).cmd_id()) {
      info->cmd_id = edit_infos.infos(i).cmd_id();
    }
    cmd_dispatch(edit_infos.infos(i));
  }

  return 0;
}

int cmds_load(char *buf, int len) {
  FILE *f;
  int l;
  f = fopen(DEFCTRLFILE, "rb");
  if (f == NULL) {
    return -1;
  }

  l = fread(buf, 1, len, f);
  buf += l;
  *buf = 0;

  fclose(f);
  return l + 1;
}

int cmds_reset() {
  FILE *f;
  f = fopen(DEFCTRLFILE, "wb");
  if (f == 0) {
    return -1;
  }

  fclose(f);

  return 0;
}

int cmds_append(char *buf, int len) {
  FILE *f;
  f = fopen(DEFCTRLFILE, "ab");
  if (f == 0) {
    return -1;
  }

  fwrite(buf, 1, len, f);
  fclose(f);

  return 0;
}
