#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "modules/calc/include/k_compress.h"
#include "modules/calc/include/k_process.h"
#include "modules/calc/include/k_project.h"
#include "modules/calc/include/k_state.h"
#include "modules/calc/include/k_util.h"

static prjinfo_t info;
static prjinfo_t info_p;
static pnode_t pn_head = {&pn_head, &pn_head, 0, "", ((prog_t *)0)};
static pnode_t *p_pn_select = &pn_head;

static int is_run;
static rwlock_t *prjlock = 0;

pnode_t *prj_gethead() { return &pn_head; }

prjinfo_t *prj_info() { return &info; }

prjinfo_t *prj_info_p() { return &info_p; }

static pnode_t *pn_new() { return (pnode_t *)k_malloc(sizeof(pnode_t)); }

static void pn_delete(pnode_t *p) { delete p; }

static void pn_addbefore(pnode_t *p, pnode_t *p_ref) {
  p->p_prev = p_ref->p_prev;
  p->p_next = p_ref;
  p_ref->p_prev->p_next = p;
  p_ref->p_prev = p;
}

static void pn_addafter(pnode_t *p, pnode_t *p_ref) {
  p->p_prev = p_ref;
  p->p_next = p_ref->p_next;
  p_ref->p_next->p_prev = p;
  p_ref->p_next = p;
}

static void pn_remove(pnode_t *p) {
  p->p_prev->p_next = p->p_next;
  p->p_next->p_prev = p->p_prev;
}

static void clear_prjinfo() {
  // strcpy(info.name,"empty");
  strcpy(info.uuid, "{00000000-0000-0000-0000-00000000}");
  info.id_cmd = 0;
  // info.stat=0;
}

void *prj_main_loop(void *sth) {
  while (1) {
    if (is_run) {
      // printf("prj lock\n");
#ifdef SIMULATOR
      //下面代码根据nicsys2000更改：

      k_sleep(INPUTCYCLE);
      io_input();
      k_rlock(prjlock);
      prj_exec();
      k_runlock(prjlock);
      k_sleep(OUTPUTCYCLE);
      io_output();
#else
      if (info.stat == S_PRIMARY) {
        io_input();
        k_rlock(prjlock);
        prj_exec();
        k_runlock(prjlock);
      } else {
        k_sleep(EMPTYCYClE);
      }

      state_check();
      if (info.stat == S_PRIMARY) {
        io_output();
      }
#endif
      // printf("prj unlock\n");
    } else {
      k_sleep(10);
    }
  }
}

void prj_run() { is_run = 1; }

void prj_stop() {
  // printf("begin lock\n");
  k_wlock(prjlock);
  // printf("end lock\n");
  is_run = 0;
  k_wunlock(prjlock);
}

void prj_init(int mode) {
  prjlock = k_rwlock_create();
  prj_info()->stat = S_UNKNOWN;
  prj_info_p()->stat = S_UNKNOWN;
  clear_prjinfo();
  k_clk_init();
  state_init();
  prj_run();
}

void prj_uninit() { k_rwlock_destory(prjlock); }

int prj_progadd(int id, char *name) {
  prog_t *p_prg;
  pnode_t *p_pn;

  p_prg = prg_new();
  if (p_prg == ((void *)0)) {
    return -1;
  }

  p_pn = pn_new();
  if (p_pn == ((void *)0)) {
    prg_delete(p_prg);
    return -1;
  }

  p_pn->p_prg = p_prg;
  p_pn->id = id;
  strncpy(p_pn->name, name, PRGNAMESIZE);
  pn_addbefore(p_pn, &pn_head);

  return 0;
}

static int prj_progselect(int id) {
  pnode_t *p_pn;

  if (id == 0) {
    p_pn_select = &pn_head;
    return -1;
  }

  if (p_pn_select->id == id) {
    return 0;
  }

  p_pn = pn_head.p_next;
  while (p_pn != &pn_head) {
    if (p_pn->id == id) {
      p_pn_select = p_pn;
      return 0;
    }
    p_pn = p_pn->p_next;
  }

  return -1;
}

int prj_progremove(int id) {
  prj_progselect(id);

  if (p_pn_select == &pn_head) {
    return -1;
  }

  prg_delete(p_pn_select->p_prg);
  pn_remove(p_pn_select);
  pn_delete(p_pn_select);

  p_pn_select = &pn_head;

  return 0;
}

void prj_exec() {
  pnode_t *p_pn;

  k_clk_do();

  p_pn = pn_head.p_next;
  while (p_pn != &pn_head) {
    prg_exec(p_pn->p_prg);
    p_pn = p_pn->p_next;
  }
}

void prj_dump() {
  pnode_t *p_pn;

  printf("prj: uuid:%s\ncmd:%d\nstat:%d\n", info.uuid, info.id_cmd, info.stat);
  p_pn = pn_head.p_next;
  while (p_pn != &pn_head) {
    printf("prg:%d - %s\n", p_pn->id, p_pn->name);
    p_pn = p_pn->p_next;
  }
}

void prj_reset() {
  pnode_t *p_pn, *p_del;

  k_wlock(prjlock);

  p_pn_select = &pn_head;
  p_pn = pn_head.p_next;
  while (p_pn != &pn_head) {
    p_del = p_pn;
    p_pn = p_pn->p_next;
    pn_remove(p_del);
    prg_delete(p_del->p_prg);
    pn_delete(p_del);
  }
  ev_reset();
  clear_prjinfo();

  k_wunlock(prjlock);
}

int prj_fbadd(int idprg, int id, char *libname, char *fcname, char *fbname) {
  if (prj_progselect(idprg) != 0) {
    return -1;
  }

  return prg_fbadd(p_pn_select->p_prg, id, libname, fcname, fbname);
}

int prj_fbremove(int idprg, int id) {
  if (prj_progselect(idprg) != 0) {
    return -1;
  }

  return prg_fbremove(p_pn_select->p_prg, id);
}

int prj_lkadd(int idprg, int id, int fbsrc, int pinsrc, int fbtgt, int pintgt) {
  if (prj_progselect(idprg) != 0) {
    return -1;
  }

  return prg_lkadd(p_pn_select->p_prg, id, fbsrc, pinsrc, fbtgt, pintgt);
}

int prj_lkremove(int idprg, int id) {
  if (prj_progselect(idprg) != 0) {
    return -1;
  }

  return prg_lkremove(p_pn_select->p_prg, id);
}

int prj_viadd(int idprg, int id, int idev, int idfb, int pin) {
  if (prj_progselect(idprg) != 0) {
    return -1;
  }

  return prg_viadd(p_pn_select->p_prg, id, idev, idfb, pin);
}

int prj_voadd(int idprg, int id, int idev, int idfb, int pin) {
  if (prj_progselect(idprg) != 0) {
    return -1;
  }

  return prg_voadd(p_pn_select->p_prg, id, idev, idfb, pin);
}

int prj_viremove(int idprg, int id) {
  if (prj_progselect(idprg) != 0) {
    return -1;
  }

  return prg_viremove(p_pn_select->p_prg, id);
}

int prj_voremove(int idprg, int id) {
  if (prj_progselect(idprg) != 0) {
    return -1;
  }

  return prg_voremove(p_pn_select->p_prg, id);
}

int prj_checkloop(int idprg, int idsrc, int idtgt) {
  if (prj_progselect(idprg) != 0) {
    return -1;
  }

  return prg_checkloop(p_pn_select->p_prg, idsrc, idtgt);
}

int prj_prgdump(int idprg) {
  if (prj_progselect(idprg) != 0) {
    return -1;
  }

  prg_dump(p_pn_select->p_prg);
  return 0;
}

int prj_fbdump(int idprg, int idfb) {
  fb_t *p_fb;

  if (prj_progselect(idprg) != 0) {
    return -1;
  }

  p_fb = prg_fbfind(p_pn_select->p_prg, idfb);
  if (p_fb == ((void *)0)) {
    return -1;
  }

  fb_dump(p_fb);
  return 0;
}

fb_t *prj_fbfind(int idprg, int idfb) {
  if (prj_progselect(idprg) != 0) {
    return 0;
  }

  return prg_fbfind(p_pn_select->p_prg, idfb);
}

int prj_img_size() {
  pnode_t *p_pn;
  enode_t *p_en;
  fb_t *p_fb;
  int s;

  k_rlock(prjlock);
  s = 0;
  p_pn = pn_head.p_next;
  while (p_pn != &pn_head) {
    p_en = p_pn->p_prg->en_head.p_next;
    while (p_en != &p_pn->p_prg->en_head) {
      if (p_en->p_fb != ((void *)0)) {
        p_fb = p_en->p_fb;
        s += p_fb->h.ni + p_fb->h.no + p_fb->h.np;
      }
      p_en = p_en->p_next;
    }
    p_pn = p_pn->p_next;
  }
  s += ev_img_size();

  k_runlock(prjlock);

  // return sizeof(prjimg_t)+sizeof(var_t)*s;
  return sizeof(var_t) * s;
}

int prj_to_img(prjimg_t *pimg) {
  char *buf;
  pin_t *ppin;
  pnode_t *p_pn;
  enode_t *p_en;
  fb_t *p_fb;
  unsigned int i;
  int s;

  k_rlock(prjlock);

  memcpy(&pimg->info, &info, sizeof(prjinfo_t));
  buf = pimg->imgbuf;

  s = 0;
  p_pn = pn_head.p_next;
  while (p_pn != &pn_head) {
    p_en = p_pn->p_prg->en_head.p_next;
    while (p_en != &p_pn->p_prg->en_head) {
      if (p_en->p_fb != ((void *)0)) {
        p_fb = p_en->p_fb;
        for (i = 0; i < p_fb->h.ni; i++) {
          ppin = &p_fb->d[i];
          buf += cmps_zvar(&ppin->v.v, ppin->t, buf);
          s++;
        }
        for (i = 0; i < p_fb->h.no; i++) {
          ppin = &p_fb->d[i + p_fb->h.ni];
          buf += cmps_zvar(&ppin->v.v, ppin->t, buf);
          s++;
        }
        for (i = 0; i < p_fb->h.np; i++) {
          ppin = &p_fb->d[i + p_fb->h.ni + p_fb->h.no];
          buf += cmps_zvar(&ppin->v.v, ppin->t, buf);
          s++;
        }
      }
      p_en = p_en->p_next;
    }
    p_pn = p_pn->p_next;
  }

  buf = ev_to_img(buf);
  buf = io_to_img(buf);

  pimg->bufsize = buf - pimg->imgbuf;
  info.zimgsize = pimg->bufsize;
  info.imgsize = s * sizeof(var_t) + sizeof(iostation_t) * IOSTATIONCOUNT;

  // printf("imgsize=%d, zimgsize=%d\n", info.imgsize, info.zimgsize);
  k_runlock(prjlock);

  return 0;
}

static int info_cmp(prjinfo_t *info1, prjinfo_t *info2) {
  if (strncmp(info1->uuid, info2->uuid, UUIDSIZE) != 0) {
    return 1;
  }
  if (info1->id_cmd != info2->id_cmd) {
    return 1;
  }
  // if(strncmp(info1->name, info2->name, PRJNAMESIZE)!=0){
  //	return 1;
  //}

  return 0;
}

int prj_from_img(prjimg_t *pimg) {
  char *buf;
  pin_t *ppin;
  Int t;
  pnode_t *p_pn;
  enode_t *p_en;
  fb_t *p_fb;
  unsigned int i;

  if (info_cmp(&info, &pimg->info) != 0) {
    return 1;
  }

  buf = pimg->imgbuf;
  p_pn = pn_head.p_next;
  while (p_pn != &pn_head) {
    p_en = p_pn->p_prg->en_head.p_next;
    while (p_en != &p_pn->p_prg->en_head) {
      if (p_en->p_fb != ((void *)0)) {
        p_fb = p_en->p_fb;
        for (i = 0; i < p_fb->h.ni; i++) {
          ppin = &p_fb->d[i];
          buf += cmps_uzvar(buf, &ppin->v.v, &t);
        }
        for (i = 0; i < p_fb->h.no; i++) {
          ppin = &p_fb->d[i + p_fb->h.ni];
          buf += cmps_uzvar(buf, &ppin->v.v, &t);
        }
        for (i = 0; i < p_fb->h.np; i++) {
          ppin = &p_fb->d[i + p_fb->h.ni + p_fb->h.no];
          buf += cmps_uzvar(buf, &ppin->v.v, &t);
        }
      }
      p_en = p_en->p_next;
    }
    p_pn = p_pn->p_next;
  }

  buf = ev_from_img(buf);
  buf = io_from_img(buf);

  if (pimg->bufsize != buf - pimg->imgbuf) {
    return 1;
    printf("uz form img error!\n");
    fflush(stdout);
  }

  // printf("get imgbuf size=%d\n",pimg->bufsize);
  return 0;
}
