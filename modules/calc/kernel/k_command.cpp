#include "modules/calc/include/k_command.h"
#include "modules/calc/include/k_evdata.h"
#include "modules/calc/include/k_lib.h"
#include "modules/calc/include/k_project.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int cmd_dispatch(Cmd::EditInfo edit_info) {

  if (edit_info.element() == Cmd::EditElement::PROJ) {
    if (edit_info.mutable_proj()->edit_type() == Cmd::EditType::ADD) {

    } else if (edit_info.mutable_proj()->edit_type() == Cmd::EditType::RM) {

    } else if (edit_info.mutable_proj()->edit_type() == Cmd::EditType::SET) {

    } else if (edit_info.mutable_proj()->edit_type() == Cmd::EditType::SHOW) {

    } else {
    }

  } else if (edit_info.element() == Cmd::EditElement::MOD) {
    if (edit_info.mutable_mod()->edit_type() == Cmd::EditType::ADD) {
      prj_modadd(edit_info.mutable_mod()->mod_id(),
                 edit_info.mutable_mod()->mod_name(),
                 edit_info.mutable_mod()->mod_desc());

    } else if (edit_info.mutable_mod()->edit_type() == Cmd::EditType::RM) {
      prj_modremove(edit_info.mutable_mod()->mod_id());

    } else if (edit_info.mutable_mod()->edit_type() == Cmd::EditType::SET) {

    } else if (edit_info.mutable_mod()->edit_type() == Cmd::EditType::SHOW) {

    } else {
    }
  } else if (edit_info.element() == Cmd::EditElement::TASK) {
    if (edit_info.mutable_task()->edit_type() == Cmd::EditType::ADD) {

      prj_prgadd(edit_info.mutable_task()->mod_id(),
                 edit_info.mutable_task()->task_id(),
                 edit_info.mutable_task()->task_name(),
                 edit_info.mutable_task()->task_type(),
                 edit_info.mutable_task()->task_desc(),
                 edit_info.mutable_task()->interval());

    } else if (edit_info.mutable_task()->edit_type() == Cmd::EditType::RM) {
      prj_prgremove(edit_info.mutable_task()->mod_id(),
                    edit_info.mutable_task()->task_id());
    } else if (edit_info.mutable_task()->edit_type() == Cmd::EditType::SET) {

    } else if (edit_info.mutable_task()->edit_type() == Cmd::EditType::SHOW) {

    } else {
    }
  } else if (edit_info.element() == Cmd::EditElement::EV) {
    if (edit_info.mutable_ev()->edit_type() == Cmd::EditType::ADD) {
      ev_add(edit_info.mutable_ev()->ev_id(), edit_info.mutable_ev()->ev_name(),
             edit_info.mutable_ev()->val());

    } else if (edit_info.mutable_ev()->edit_type() == Cmd::EditType::RM) {
      ev_remove(edit_info.mutable_ev()->ev_id());

    } else if (edit_info.mutable_ev()->edit_type() == Cmd::EditType::SET) {

    } else if (edit_info.mutable_ev()->edit_type() == Cmd::EditType::SHOW) {

    } else {
    }
  } else if (edit_info.element() == Cmd::EditElement::IO) {
    if (edit_info.mutable_io()->edit_type() == Cmd::EditType::ADD) {

    } else if (edit_info.mutable_io()->edit_type() == Cmd::EditType::RM) {

    } else if (edit_info.mutable_io()->edit_type() == Cmd::EditType::SET) {

    } else if (edit_info.mutable_io()->edit_type() == Cmd::EditType::SHOW) {

    } else {
    }
  } else if (edit_info.element() == Cmd::EditElement::FB) {
    if (edit_info.mutable_fb()->edit_type() == Cmd::EditType::ADD) {
      prj_fbadd(
          edit_info.mutable_fb()->mod_id(), edit_info.mutable_fb()->task_id(),
          edit_info.mutable_fb()->fb_id(), edit_info.mutable_fb()->flib_name(),
          edit_info.mutable_fb()->fc_name(), edit_info.mutable_fb()->fb_name());

    } else if (edit_info.mutable_fb()->edit_type() == Cmd::EditType::RM) {
      prj_fbremove(edit_info.mutable_fb()->mod_id(),
                   edit_info.mutable_fb()->task_id(),
                   edit_info.mutable_fb()->fb_id());
    } else if (edit_info.mutable_fb()->edit_type() == Cmd::EditType::SET) {

    } else if (edit_info.mutable_fb()->edit_type() == Cmd::EditType::SHOW) {

    } else {
    }
  } else if (edit_info.element() == Cmd::EditElement::LK) {
    if (edit_info.mutable_lk()->edit_type() == Cmd::EditType::ADD) {
      prj_lkadd(
          edit_info.mutable_lk()->mod_id(), edit_info.mutable_lk()->task_id(),
          edit_info.mutable_lk()->lk_id(), edit_info.mutable_lk()->src_fb_id(),
          edit_info.mutable_lk()->src_pin_index(),
          edit_info.mutable_lk()->target_fb_id(),
          edit_info.mutable_lk()->target_pin_index());
    } else if (edit_info.mutable_lk()->edit_type() == Cmd::EditType::RM) {

    } else if (edit_info.mutable_lk()->edit_type() == Cmd::EditType::SET) {

    } else if (edit_info.mutable_lk()->edit_type() == Cmd::EditType::SHOW) {

    } else {
    }
  } else if (edit_info.element() == Cmd::EditElement::PIN) {
    if (edit_info.mutable_pin()->edit_type() == Cmd::EditType::ADD) {

    } else if (edit_info.mutable_pin()->edit_type() == Cmd::EditType::RM) {

    } else if (edit_info.mutable_pin()->edit_type() == Cmd::EditType::SET) {

      fb_t *p_fb;
      p_fb = prj_fbfind(edit_info.mutable_pin()->mod_id(),
                        edit_info.mutable_pin()->task_id(),
                        edit_info.mutable_pin()->fb_id());

      fb_setpin(p_fb, PININPUT, edit_info.mutable_pin()->pin_index(),
                edit_info.mutable_pin()->pin_val());

    } else if (edit_info.mutable_pin()->edit_type() == Cmd::EditType::SHOW) {

    } else {
    }
  }

  return 0;
}

int cmds_dispatch(Cmd::EditInfos edit_infos) {

  int info_size = edit_infos.infos_size();
  for(auto i =0; i < info_size; i++)
  {
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
