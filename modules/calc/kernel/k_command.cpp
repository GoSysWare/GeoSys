#include "modules/calc/include/k_command.h"
#include "modules/calc/include/k_evdata.h"
#include "modules/calc/include/k_lib.h"
#include "modules/calc/include/k_project.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cmd_dispatch(const Bus::EditInfo &edit_info) {
  std::cout << edit_info.DebugString() << std::endl;
  int ret = -1;
  prjinfo_t *info;
  info = prj_info();
  if (info->cmd_id < edit_info.cmd_id()) {
    info->cmd_id = edit_info.cmd_id();
  }

  Bus::EditElement element = edit_info.element();
  Bus::EditType type = edit_info.edit_type();

  if (element == Bus::EditElement::PROJ) {
    if (type == Bus::EditType::ADD) {

    } else if (type == Bus::EditType::RM) {

    } else if (type == Bus::EditType::SET) {
      prjinfo_t *info;
      info = prj_info();
      info->uuid = edit_info.proj().proj_uuid();
      ret = 0;
    } else if (type == Bus::EditType::SHOW) {
      ret = 0;

    } else {
      ret = 0;
    }

  } else if (element == Bus::EditElement::MOD) {
    if (type == Bus::EditType::ADD) {
      ret = prj_modadd(edit_info.mod().mod_id(), edit_info.mod().mod_name(),
                       edit_info.mod().mod_desc());

    } else if (type == Bus::EditType::RM) {
      ret = prj_modremove(edit_info.mod().mod_id());

    } else if (type == Bus::EditType::SET) {
      ret = 0;

    } else if (type == Bus::EditType::SHOW) {
      ret = 0;

    } else {
      ret = 0;
    }
  } else if (element == Bus::EditElement::TASK) {
    if (type == Bus::EditType::ADD) {

      ret =
          prj_prgadd(edit_info.task().mod_id(), edit_info.task().task_id(),
                     edit_info.task().task_name(), edit_info.task().task_type(),
                     edit_info.task().task_desc(), edit_info.task().interval());

    } else if (type == Bus::EditType::RM) {
      ret =
          prj_prgremove(edit_info.task().mod_id(), edit_info.task().task_id());
    } else if (type == Bus::EditType::SET) {
      ret = 0;

    } else if (type == Bus::EditType::SHOW) {
      ret = 0;

    } else {
      ret = 0;
    }
  } else if (element == Bus::EditElement::EV) {
    if (type == Bus::EditType::ADD) {
      ret = ev_add(edit_info.ev().ev_id(), edit_info.ev().ev_name(),
                   edit_info.ev().init_val());

    } else if (type == Bus::EditType::RM) {
      ret = ev_remove(edit_info.ev().ev_id());

    } else if (type == Bus::EditType::SET) {

      vam_t *p_val = ev_find_v(edit_info.ev().ev_id());
      if (p_val) {
        p_val->get()->CopyFrom(edit_info.ev().real_val());
        ret = 0;
      } else {
        ret = -1;
      }

    } else if (type == Bus::EditType::SHOW) {
      ret = 0;

    } else {
      ret = 0;
    }
  } else if (element == Bus::EditElement::IO) {
    if (type == Bus::EditType::ADD) {
      ret = 0;

    } else if (type == Bus::EditType::RM) {
      ret = 0;

    } else if (type == Bus::EditType::SET) {
      ret = 0;

    } else if (type == Bus::EditType::SHOW) {
      ret = 0;

    } else {
      ret = 0;
    }
  } else if (element == Bus::EditElement::FB) {
    if (type == Bus::EditType::ADD) {
      ret = prj_fbadd(edit_info.fb().mod_id(), edit_info.fb().task_id(),
                      edit_info.fb().fb_id(), edit_info.fb().flib_name(),
                      edit_info.fb().fc_name(), edit_info.fb().fb_name());

    } else if (type == Bus::EditType::RM) {
      ret = prj_fbremove(edit_info.fb().mod_id(), edit_info.fb().task_id(),
                         edit_info.fb().fb_id());
    } else if (type == Bus::EditType::SET) {
      ret = 0;

    } else if (type == Bus::EditType::SHOW) {
      ret = 0;

    } else {
      ret = 0;
    }
  } else if (element == Bus::EditElement::LK) {
    if (type == Bus::EditType::ADD) {
      ret = prj_lkadd(edit_info.lk().mod_id(), edit_info.lk().task_id(),
                      edit_info.lk().lk_id(), edit_info.lk().src_fb_id(),
                      edit_info.lk().src_pin_index(),
                      edit_info.lk().target_fb_id(),
                      edit_info.lk().target_pin_index());
    } else if (type == Bus::EditType::RM) {
      ret = prj_lkremove(edit_info.lk().mod_id(), edit_info.lk().task_id(),
                         edit_info.lk().lk_id());
    } else if (type == Bus::EditType::SET) {
      ret = 0;

    } else if (type == Bus::EditType::SHOW) {
      ret = 0;

    } else if (type == Bus::EditType::MV) {
      ret = 0;

    } else {
      ret = 0;
    }
  } else if (element == Bus::EditElement::PIN) {
    if (type == Bus::EditType::ADD) {
      ret = 0;

    } else if (type == Bus::EditType::RM) {
      ret = 0;

    } else if (type == Bus::EditType::SET) {

      fb_t *p_fb;
      p_fb = prj_fbfind(edit_info.pin().mod_id(), edit_info.pin().task_id(),
                        edit_info.pin().fb_id());
      if (p_fb) {
        ret = fb_setpin(p_fb, PININPUT, edit_info.pin().pin_index(),
                        edit_info.pin().pin_val());
      } else {
        ret = -1;
      }

    } else if (type == Bus::EditType::SHOW) {
      ret = 0;

    } else {
      ret = 0;
    }
  } else if (element == Bus::EditElement::VI) {
    if (type == Bus::EditType::ADD) {

      ret = prj_viadd(edit_info.vi().mod_id(), edit_info.vi().task_id(),
                      edit_info.vi().ev_id(), edit_info.vi().fb_id(),
                      edit_info.vi().pin_index());

    } else if (type == Bus::EditType::RM) {
      ret = prj_viremove(edit_info.vi().mod_id(), edit_info.vi().task_id(),
                         edit_info.vi().fb_id(), edit_info.vi().pin_index());

    } else if (type == Bus::EditType::SET) {
      ret = 0;

    } else if (type == Bus::EditType::SHOW) {
      ret = 0;

    } else {
      ret = 0;
    }
  } else if (element == Bus::EditElement::VO) {
    if (type == Bus::EditType::ADD) {
      ret = prj_voadd(edit_info.vo().mod_id(), edit_info.vo().task_id(),
                      edit_info.vo().ev_id(), edit_info.vo().fb_id(),
                      edit_info.vo().pin_index());

    } else if (type == Bus::EditType::RM) {
      ret = prj_viremove(edit_info.vo().mod_id(), edit_info.vo().task_id(),
                         edit_info.vo().fb_id(), edit_info.vo().pin_index());

    } else if (type == Bus::EditType::SET) {
      ret = 0;

    } else if (type == Bus::EditType::SHOW) {
      ret = 0;

    } else {
      ret = 0;
    }
  }

  return ret;
}

int cmds_dispatch(const Bus::EditInfos &edit_infos) {

  int info_size = edit_infos.infos_size();
  for (auto i = 0; i < info_size; i++) {
    prjinfo_t *info = prj_info();
    if (info->cmd_id < edit_infos.infos(i).cmd_id()) {
      info->cmd_id = edit_infos.infos(i).cmd_id();
    }
    if (cmd_dispatch(edit_infos.infos(i)) != 0) {
      return -1;
    }
  }

  return 0;
}

int cmds_load(Bus::EditInfos *infos) {
  return apollo::cyber::common::GetProtoFromFile(DEFCTRLFILE, infos) ? 0 : -1;
}

int cmds_reset() {
  FILE *f;
  f = fopen(DEFCTRLFILE, "w");
  if (f == 0) {
    return -1;
  }
  fclose(f);
  return 0;
}

int cmds_append(Bus::EditInfos &infos) {

  return apollo::cyber::common::SetProtoToASCIIFile(infos, DEFCTRLFILE) ? 0
                                                                        : -1;
}
