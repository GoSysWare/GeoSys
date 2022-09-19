#include "modules/calc/include/k_command.h"
#include "modules/calc/include/k_evdata.h"
#include "modules/calc/include/k_lib.h"
#include "modules/calc/include/k_project.h"
#include "modules/calc/proto/cmd.pb.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int addprg(char *line, int *cursor) {
  char word[NWORD];
  int idprg;
  char name[PRGNAMESIZE];
  get_word(line, word, cursor);
  idprg = atoi(word);
  get_word(line, word, cursor);
  strncpy(name, word, PRGNAMESIZE);
  return prj_progadd(idprg, name);
}

static int rmprg(char *line, int *cursor) {
  char word[NWORD];
  int idprg;

  get_word(line, word, cursor);
  idprg = atoi(word);
  return prj_progremove(idprg);
}

static int addfb(char *line, int *cursor) {
  char word[NWORD];
  int idprg;
  int idfb;
  char libname[LIBNAMESIZE];
  char fcname[FCNAMESIZE];
  char fbname[FBNAMESIZE];

  get_word(line, word, cursor);
  idprg = atoi(word);
  get_word(line, word, cursor);
  idfb = atoi(word);
  get_word(line, word, cursor);
  strncpy(libname, word, LIBNAMESIZE);
  get_word(line, word, cursor);
  strncpy(fcname, word, FCNAMESIZE);
  get_word(line, word, cursor);
  strncpy(fbname, word, FBNAMESIZE);

  return prj_fbadd(idprg, idfb, libname, fcname, fbname);
}

static int rmfb(char *line, int *cursor) {
  char word[NWORD];
  int idprg;
  int idfb;

  get_word(line, word, cursor);
  idprg = atoi(word);
  get_word(line, word, cursor);
  idfb = atoi(word);

  return prj_fbremove(idprg, idfb);
}

static int addlk(char *line, int *cursor) {
  char word[NWORD];
  int idprg;
  int idlk, fbsrc, pinsrc, fbtgt, pintgt;

  get_word(line, word, cursor);
  idprg = atoi(word);
  get_word(line, word, cursor);
  idlk = atoi(word);
  get_word(line, word, cursor);
  fbsrc = atoi(word);
  get_word(line, word, cursor);
  pinsrc = atoi(word);
  get_word(line, word, cursor);
  fbtgt = atoi(word);
  get_word(line, word, cursor);
  pintgt = atoi(word);

  return prj_lkadd(idprg, idlk, fbsrc, pinsrc, fbtgt, pintgt);
}

static int rmlk(char *line, int *cursor) {
  char word[NWORD];
  int idprg;
  int idlk;

  get_word(line, word, cursor);
  idprg = atoi(word);
  get_word(line, word, cursor);
  idlk = atoi(word);

  return prj_lkremove(idprg, idlk);
}

static int addvi(char *line, int *cursor) {
  char word[NWORD];
  int idprg;
  int idvi, ev, fb, pin;

  get_word(line, word, cursor);
  idprg = atoi(word);
  get_word(line, word, cursor);
  idvi = atoi(word);
  get_word(line, word, cursor);
  ev = atoi(word);
  get_word(line, word, cursor);
  fb = atoi(word);
  get_word(line, word, cursor);
  pin = atoi(word);

  return prj_viadd(idprg, ev, fb, pin);
}

static int rmvi(char *line, int *cursor) {
  char word[NWORD];
  int idprg;
  int idvi;

  get_word(line, word, cursor);
  idprg = atoi(word);
  get_word(line, word, cursor);
  idvi = atoi(word);
  return 0;

  // return prj_viremove(idprg, idvi);
}

static int addvo(char *line, int *cursor) {
  char word[NWORD];
  int idprg;
  int idvo, ev, fb, pin;

  get_word(line, word, cursor);
  idprg = atoi(word);
  get_word(line, word, cursor);
  idvo = atoi(word);
  get_word(line, word, cursor);
  ev = atoi(word);
  get_word(line, word, cursor);
  fb = atoi(word);
  get_word(line, word, cursor);
  pin = atoi(word);

  return prj_voadd(idprg, ev, fb, pin);
}

static int rmvo(char *line, int *cursor) {
  char word[NWORD];
  int idprg;
  int idvo;

  get_word(line, word, cursor);
  idprg = atoi(word);
  get_word(line, word, cursor);
  idvo = atoi(word);
  return 0;

  // return prj_voremove(idprg, idvo);
}

static int addev(char *line, int *cursor) {
  char word[NWORD];
  int id;
  char type[32];
  char value[128];
  char name[EVNAMESIZE];

  get_word(line, word, cursor);
  id = atoi(word);
  get_word(line, word, cursor);
  strncpy(type, word, sizeof(type));
  get_word(line, word, cursor);
  strncpy(value, word, sizeof(value));
  get_word(line, word, cursor);
  strncpy(name, word, EVNAMESIZE);

  return ev_add(id, value, name);
}

static int rmev(char *line, int *cursor) {
  char word[NWORD];
  int id;

  get_word(line, word, cursor);
  id = atoi(word);

  return ev_remove(id);
}

static int showlib() {
  lib_t *p_lib;
  fb_t *p_fb;

  p_lib = lib_first();
  do {
    printf("lib - %s\n", p_lib->libname.c_str());
    p_fb = (fb_t *)p_lib->first();
    do {
      printf("  %s\n", p_fb->h.fcname.c_str());
      p_fb = (fb_t *)p_lib->next();
    } while (p_fb != 0);

    p_lib = lib_next();
  } while (p_lib != 0);

  return 0;
}

static int showprj() {
  prj_dump();

  return 0;
}

static int showevlist() {
  ev_dump();

  return 0;
}

static int showprg(char *line, int *cursor) {
  char word[NWORD];
  int idprg;

  get_word(line, word, cursor);
  idprg = atoi(word);

  return prj_prgdump(idprg);
}

static int showfb(char *line, int *cursor) {
  char word[NWORD];
  int idprg;
  int idfb;

  get_word(line, word, cursor);
  idprg = atoi(word);
  get_word(line, word, cursor);
  idfb = atoi(word);

  return prj_fbdump(idprg, idfb);
}

static int showev(char *line, int *cursor) {
  char word[NWORD];
  int idev;
  vam_t *p_ev;

  get_word(line, word, cursor);
  idev = atoi(word);
  p_ev = ev_find_v(idev);
  if (p_ev == 0) {
    return -1;
  }

  std::cout << (*p_ev)->ShortDebugString() << std::endl;

  return 0;
}

static int setev(char *line, int *cursor) {
  char word[NWORD];
  int idev;
  vam_t *p_val;

  get_word(line, word, cursor);
  idev = atoi(word);
  p_val = ev_find_v(idev);
  if (p_val == 0) {
    return -1;
  }
  get_word(line, word, cursor);

  return 0;
}

static int setpin(char *line, int *cursor) {
  char word[NWORD];
  int idprg;
  int idfb, pin;
  value_tm v;
  fb_t *p_fb;

  get_word(line, word, cursor);
  idprg = atoi(word);
  get_word(line, word, cursor);
  idfb = atoi(word);

  p_fb = prj_fbfind(idprg, idfb);
  if (p_fb == 0) {
    return -1;
  }

  get_word(line, word, cursor);
  pin = atoi(word);
  get_word(line, word, cursor);

  return fb_setpin(p_fb, PININPUT, pin, str2var(word));
}

static int help() {
  printf("Usage:\n");
  /* config command */
  printf("addprg	idprg name\n");
  printf("rmprg	idprg\n");
  printf("addfb	idprg idfb libname fcname fbname\n");
  printf("rmfb	idprg idfb\n");
  printf("addlk	idprg idlk fbsrc pinsrc fbtgt pintgt\n");
  printf("rmlk	idprg idlk\n");
  printf("addvi	idprg idvi idev idfb pin\n");
  printf("rmvi	idprg idvi\n");
  printf("addvo	idprg idvo idev idfb pi\n");
  printf("rmvo	idprg idvo\n");
  printf("addev	idev type value name\n");
  printf("rmev	idev\n");
  /* set data command */
  printf("setpin	idprg idfb pin val\n");
  printf("setev	idev val\n");
  /* dump command */
  printf("showprj\n");
  printf("showlib\n");
  printf("showev\n");
  printf("showprg	idprg\n");
  printf("showfb	idprg idfb\n");
  /* run command */
  printf("run\n");
  printf("stop\n");

  return 0;
}

static int run() {
  prj_exec();

  return 0;
}

static int stop() { return 0; }

static int setprj(char *line, int *cursor) {
  char word[NWORD];

  prjinfo_t *info;
  info = prj_info();

  get_word(line, word, cursor);
  strncpy(info->uuid, word, sizeof(info->uuid));

  printf("-------------------------load prj-----------------\n");
  // qss for clac:清空tag_list
  // tag_ev_reset();
  // tag_in_reset();
  // tag_out_reset();
  return 0;
}

static char imgbuf[TCPBUFSIZE];
static int dumpimg() {
  FILE *f;
  f = fopen("img.dat", "wb");
  if (f == NULL) {
    return -1;
  }

  prj_to_img((prjimg_t *)imgbuf);
  fwrite(imgbuf, 1, TCPBUFSIZE, f);

  fclose(f);

  return 0;
}

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
                edit_info.mutable_pin()->pin_val())

    } else if (edit_info.mutable_pin()->edit_type() == Cmd::EditType::SHOW) {

    } else {
    }
  }

  return 0;
}

int cmds_dispatch(Cmd::EditInfos edit_infos) {
  int cursor;
  char line[NLINE];
  int len;

  cursor = 0;
  while ((len = get_line(buf, line, &cursor)) != 0) {
    if (cmd_dispatch(line) != 0) {
      return -1;
    }
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
