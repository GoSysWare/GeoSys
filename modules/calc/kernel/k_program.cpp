#include <stddef.h>
#include <stdio.h>

#include "modules/calc/include/k_evdata.h"
#include "modules/calc/include/k_lib.h"
#include "modules/calc/include/k_program.h"
#include "modules/calc/include/k_project.h"
#include "modules/calc/include/k_util.h"

static enode_t *en_new() { return new enode_t; }

static void en_delete(enode_t *p_en) { delete p_en; }

static void en_addbefore(enode_t *p_en, enode_t *p_ref) {
  p_en->p_prev = p_ref->p_prev;
  p_en->p_next = p_ref;
  p_ref->p_prev->p_next = p_en;
  p_ref->p_prev = p_en;
}

static void en_addafter(enode_t *p_en, enode_t *p_ref) {
  p_en->p_prev = p_ref;
  p_en->p_next = p_ref->p_next;
  p_ref->p_next->p_prev = p_en;
  p_ref->p_next = p_en;
}

static void en_remove(enode_t *p_en) {
  p_en->p_prev->p_next = p_en->p_next;
  p_en->p_next->p_prev = p_en->p_prev;
}

static void en_movebefore(enode_t *p_en, enode_t *p_ref) {
  en_remove(p_en);
  en_addbefore(p_en, p_ref);
}

static void en_moveafter(enode_t *p_en, enode_t *p_ref) {
  en_remove(p_en);
  en_addafter(p_en, p_ref);
}

void prg_init(MNode *p_mn) {
  enode_t *p_en;
  prog_t *p_prg = p_mn->p_prg;
  proginfo_t *p_prog_info = &p_mn->info;

  /* fb to fb */
  p_en = p_prg->en_head.p_next;
  while (p_en != &p_prg->en_head) {
    // 当是功能块 且是初始化型功能块
    if (p_en->p_fb != 0) {
      //每个功能快记录prg的指针
      p_en->p_fb->h.owner = p_mn;

      if (p_en->p_fb->h.flag == FB_INIT) {
        // 为了方便Timer功能块的计算，把周期间隔给到每个功能块
        p_en->p_fb->h.cycle_time = p_prog_info->cycle_time;
        p_en->p_fb->h.begin_time = apollo::cyber::Time::Now().ToNanosecond();
        // 执行核心主体 执行每个功能块定义的具体run_func
        //
        p_en->p_fb->h.run(p_en->p_fb);
        //
        //
        p_en->p_fb->h.expend_time =
            (apollo::cyber::Time::Now() -
             apollo::cyber::Time(p_en->p_fb->h.begin_time))
                .ToNanosecond();
      }
    }
    p_en = p_en->p_next;
  }
}

void prg_init(prog_t *p_prg, proginfo_t *p_prog_info) {
  enode_t *p_en;
  /* fb to fb */
  p_en = p_prg->en_head.p_next;
  while (p_en != &p_prg->en_head) {
    // 当是功能块 且是初始化型功能块
    if (p_en->p_fb != 0 && p_en->p_fb->h.flag == FB_INIT) {
      // 为了方便Timer功能块的计算，把周期间隔给到每个功能块
      p_en->p_fb->h.cycle_time = p_prog_info->cycle_time;
      p_en->p_fb->h.begin_time = apollo::cyber::Time::Now().ToNanosecond();
      // 执行核心主体 执行每个功能块定义的具体run_func
      //
      p_en->p_fb->h.run(p_en->p_fb);
      //
      //
      p_en->p_fb->h.expend_time =
          (apollo::cyber::Time::Now() -
           apollo::cyber::Time(p_en->p_fb->h.begin_time))
              .ToNanosecond();
    }
    p_en = p_en->p_next;
  }
}

void prg_exec(MNode *p_mn)
{
  //发出停止命令
        if (p_mn->stop.load()) {
          p_mn->info.status.store(TaskStatus::ABORT);
          return;
        }
        p_mn->info.status.store(TaskStatus::START);

        p_mn->info.status = p_mn->info.begin_time =
            apollo::cyber::Time::Now().ToNanosecond();
        p_mn->info.cycle_time =
            apollo::cyber::Duration(
                int64_t(p_mn->info.begin_time - p_mn->info.prev_time))
                .ToNanosecond();
        p_mn->info.prev_time = p_mn->info.begin_time;

        {
          apollo::cyber::base::WriteLockGuard<apollo::cyber::base::AtomicRWLock>
              lg(p_mn->mutex);

          prg_exec(p_mn->p_prg, &p_mn->info);
        }

        // prg_dump(p_mn->p_prg);
        p_mn->info.expend_time = (apollo::cyber::Time::Now() -
                                  apollo::cyber::Time(p_mn->info.begin_time))
                                     .ToNanosecond();
        // task完成一次运算周期
        p_mn->info.status.store(TaskStatus::FINISH);

        AINFO << "Async task name:" << p_mn->name
               << " begin_time:" << p_mn->info.begin_time
               << " cycle_time:" << p_mn->info.cycle_time
               << " expend_time:" << p_mn->info.expend_time;
               return;
}


void prg_exec(prog_t *p_prg, proginfo_t *p_prog_info) {
  enode_t *p_en;
  /* fb to fb */
  p_en = p_prg->en_head.p_next;
  while (p_en != &p_prg->en_head) {
    // 当是功能块时
    if (p_en->p_fb != 0) {
      if (p_en->p_fb->h.flag == FB_EXEC || p_en->p_fb->h.flag == FB_IO) {
        // 为了方便Timer功能块的计算，把周期间隔给到每个功能块
        p_en->p_fb->h.cycle_time = p_prog_info->cycle_time;
        p_en->p_fb->h.begin_time = apollo::cyber::Time::Now().ToNanosecond();
        // 执行核心主体 执行每个功能块定义的具体run_func
        //
        p_en->p_fb->h.run(p_en->p_fb);
        //
        //
        p_en->p_fb->h.expend_time =
            (apollo::cyber::Time::Now() -
             apollo::cyber::Time(p_en->p_fb->h.begin_time))
                .ToNanosecond();
      }
    }
     else {
      // 当是pin之间link链接时
      //
      // if (p_en->p_vsrc->s == PIN_HAS_LOCK) {
      //   apollo::cyber::base::ReadLockGuard<apollo::cyber::base::ReentrantRWLock>
      //       lg(*(p_en->p_vsrc->l));
      //   if (p_en->p_vtgt->s == PIN_HAS_LOCK) {
      //     apollo::cyber::base::WriteLockGuard<
      //         apollo::cyber::base::ReentrantRWLock>
      //         lg(*(p_en->p_vtgt->l));
      //     p_en->p_vtgt->v = p_en->p_vsrc->v;

      //   } else {
      //     p_en->p_vtgt->v = p_en->p_vsrc->v;
      //   }
      // } else {
      //   p_en->p_vtgt->v = p_en->p_vsrc->v;
      // }
      // p_en = p_en->p_next;
    p_en->p_vtgt->s = p_en->p_vsrc->s;
    p_en->p_vtgt->l = p_en->p_vsrc->l;
    p_en->p_vtgt->v = p_en->p_vsrc->v;   
    }
  p_en = p_en->p_next;
  }
}

prog_t *prg_new() {
  prog_t *p_new;

  p_new = new prog_t;
  if (p_new != 0) {
    p_new->en_head.p_prev = &p_new->en_head;
    p_new->en_head.p_next = &p_new->en_head;
    p_new->p_en_select = &p_new->en_head;
  }

  return p_new;
}

void prg_delete(prog_t *p_prg) {
  enode_t *p_en, *p_erm;

  /* clear enode list */
  p_en = p_prg->en_head.p_next;
  while (p_en != &p_prg->en_head) {
    p_erm = p_en;
    p_en = p_en->p_next;
    if (p_erm->p_fb != 0) {
      fb_delete(p_erm->p_fb);
    }
    en_remove(p_erm);
    en_delete(p_erm);
  }
  delete p_prg;
}

static void prg_setrank(prog_t *p_prg) {
  int i;
  enode_t *p_en;

  i = 0;
  p_en = p_prg->en_head.p_next;
  while (p_en != &p_prg->en_head) {
    p_en->rank = i;
    i++;
    p_en = p_en->p_next;
  }
}

static void prg_clearmark(prog_t *p_prg) {
  enode_t *p_en;

  p_en = p_prg->en_head.p_next;
  while (p_en != &p_prg->en_head) {
    p_en->mark = 0;
    p_en = p_en->p_next;
  }
}

static void prg_markfbchild(prog_t *p_prg, enode_t *p_en) {
  p_en->mark = 1;
  while (p_en != &p_prg->en_head) {
    if (p_en->p_fb == 0) {
      p_en->mark = p_en->p_prev->mark;
      if (p_en->mark) {
        p_en->p_entgt->mark = 1;
      }
    }
    p_en = p_en->p_next;
  }
}

static void prg_markfblink(prog_t *p_prg, enode_t *p_enfb) {
  enode_t *p_en;

  p_enfb->mark = 1;

  p_en = p_prg->en_head.p_next;
  while (p_en != &p_prg->en_head) {
    if (p_en->p_fb == 0) {
      if (p_en->idsrc == p_enfb->id || p_en->idtgt == p_enfb->id) {
        p_en->mark = 1;
      }
    }
    p_en = p_en->p_next;
  }
}

int prg_fbadd(prog_t *p_prg, int id, const std::string &libname,
              const std::string &fcname, const std::string &fbname) {
  fb_t *p_fb;
  enode_t *p_en;
  //根据库名和功能块名找到功能块
  p_fb = lib_find(libname, fcname);
  if (0 == p_fb) {
    return -1;
  }
  //根据功能块的预定义的生成一个新的功能块
  p_fb = fb_new(p_fb);
  if (0 == p_fb) {
    return -1;
  }

  p_en = en_new();
  if (0 == p_en) {
    fb_delete(p_fb);
    return -1;
  }
  p_fb->h.fbname = fbname;
  p_en->id = id;
  p_en->p_fb = p_fb;
  p_en->fbname = fbname;

  en_addbefore(p_en, &p_prg->en_head);

  return 0;
}

static int prg_enselect(prog_t *p_prg, int id) {
  enode_t *p_en;

  if (id == 0) {
    p_prg->p_en_select = &p_prg->en_head;
    return -1;
  }

  if (p_prg->p_en_select->id == id) {
    return 0;
  }

  p_en = p_prg->en_head.p_next;
  while (p_en != &p_prg->en_head) {
    if (p_en->id == id) {
      p_prg->p_en_select = p_en;
      return 0;
    }
    p_en = p_en->p_next;
  }

  return -1;
}

static int prg_enselect_by_lib(prog_t *p_prg, std::string libname,
                               std::string fcname) {
  enode_t *p_en;

  if (libname.length() == 0 || fcname.length() == 0) {
    p_prg->p_en_select = &p_prg->en_head;
    return -1;
  }

  if (p_prg->p_en_select->p_fb) {
    if (p_prg->p_en_select->p_fb->h.libname == libname &&
        p_prg->p_en_select->p_fb->h.fcname == fcname)
      return 0;
  }

  p_en = p_prg->en_head.p_next;
  while (p_en != &p_prg->en_head) {
    if (p_en->p_fb) {
      if (p_en->p_fb->h.libname == libname && p_en->p_fb->h.fcname == fcname) {
        p_prg->p_en_select = p_en;
        return 0;
      }
    }
    p_en = p_en->p_next;
  }
  return -1;
}

fb_t *prg_fbfind(prog_t *p_prg, int id) {
  enode_t *p_en;

  prg_enselect(p_prg, id);
  p_en = p_prg->p_en_select;

  if (p_en == &p_prg->en_head) {
    return 0;
  }

  return p_en->p_fb;
}
fb_t *prg_fbfind_by_lib(prog_t *p_prg, std::string libname,
                        std::string fcname) {
  enode_t *p_en;
  prg_enselect_by_lib(p_prg, libname, fcname);
  p_en = p_prg->p_en_select;
  if (p_en == &p_prg->en_head) {
    return 0;
  }
  return p_en->p_fb;
}
int prg_fbremove(prog_t *p_prg, int id) {
  enode_t *p_en, *p_rm;

  prg_enselect(p_prg, id);
  p_en = p_prg->p_en_select;
  p_prg->p_en_select = &p_prg->en_head;
  if (p_en == &p_prg->en_head) {
    return -1;
  }

  prg_clearmark(p_prg);
  prg_markfblink(p_prg, p_en);

  p_en = p_prg->en_head.p_next;
  while (p_en != &p_prg->en_head) {
    p_rm = p_en;
    p_en = p_en->p_next;
    if (p_rm->mark) {
      if (p_rm->p_fb != 0) {
        fb_delete(p_rm->p_fb);
      }
      en_remove(p_rm);
      en_delete(p_rm);
    }
  }
  return 0;
}

int prg_viadd(prog_t *p_prg, int idev, int idfb, int pin) {
  fb_t *p_fb;
  pin_t *p_pin;
  evnode_t *p_ev;

  p_ev = ev_find_n(idev);
  if (p_ev == 0) {
    return -1;
  }
  p_fb = prg_fbfind(p_prg, idfb);
  if (p_fb == 0) {
    return -1;
  }
  p_pin = fb_getpin(p_fb, PININPUT, pin);
  if (p_pin == 0) {
    return -1;
  }

  p_pin->s = PIN_HAS_LOCK;
  p_pin->v = p_ev->v;
  p_pin->l = &p_ev->mutex;

  return 0;
}
int prg_viremove(prog_t *p_prg, int idfb, int pin) {
  fb_t *p_fb;
  pin_t *p_pin;

  p_fb = prg_fbfind(p_prg, idfb);
  if (p_fb == 0) {
    return -1;
  }
 
  p_pin = fb_getpin(p_fb, PININPUT, pin);
  if (p_pin == 0) {
    return -1;
  }

  fb_init_pin(p_pin);

  return 0;
}

int prg_voadd(prog_t *p_prg, int idev, int idfb, int pin) {
  fb_t *p_fb;
  pin_t *p_pin;
  evnode_t *p_ev;

  p_ev = ev_find_n(idev);
  if (p_ev == nullptr) {
    return -1;
  }
  p_fb = prg_fbfind(p_prg, idfb);
  if (p_fb == 0) {
    return -1;
  }
  p_pin = fb_getpin(p_fb, PINOUTPUT, pin);
  if (p_pin == 0) {
    return -1;
  }

  p_pin->s = PIN_HAS_LOCK;
  p_pin->v = p_ev->v;
  p_pin->l = &p_ev->mutex;

  return 0;
}

int prg_voremove(prog_t *p_prg, int idfb, int pin) {
  fb_t *p_fb;
  pin_t *p_pin;

  p_fb = prg_fbfind(p_prg, idfb);
  if (p_fb == 0) {
    return -1;
  }
  p_pin = fb_getpin(p_fb, PINOUTPUT, pin);
  if (p_pin == 0) {
    return -1;
  }

  fb_init_pin(p_pin);


  return 0;
}
int prg_lkadd(prog_t *p_prg, int id, int fbsrc, int pinsrc, int fbtgt,
              int pintgt) {
  enode_t *p_en,*p_mv;
  enode_t *p_src, *p_tgt;
  pin_t * pin_src,*pin_tgt;

  /* get link map */
  prg_enselect(p_prg, fbsrc);
  p_src = p_prg->p_en_select;
  if (p_src == &p_prg->en_head) {
    return -1;
  }
  if (p_src->p_fb == 0) {
    return -1;
  }
  pin_src = fb_getpin(p_src->p_fb, PINOUTPUT, pinsrc);
  if (pin_src == 0) {
    return -1;
  }

  prg_enselect(p_prg, fbtgt);
  p_tgt = p_prg->p_en_select;
  if (p_tgt == &p_prg->en_head) {
    return -1;
  }
  if (p_tgt->p_fb == 0) {
    return -1;
  }
  pin_tgt = fb_getpin(p_tgt->p_fb, PININPUT, pintgt);
  if (pin_tgt == 0) {
    return -1;
  }

  if (pin_src->t != pin_tgt->t) {
    return -1;
  }



  p_en = en_new();
  if (p_en == 0) {
    return -1;
  }
  p_en->id = id;
  p_en->idsrc = fbsrc;
  p_en->p_ensrc = p_src;
  p_en->idtgt = fbtgt;
  p_en->p_entgt = p_tgt;
  p_en->p_fb = 0;
  p_en->p_vsrc = pin_src;
  p_en->p_vtgt = pin_tgt;
  p_en->p_vtgt->s = p_en->p_vsrc->s;
  p_en->p_vtgt->l = p_en->p_vsrc->l;
  p_en->p_vtgt->v = p_en->p_vsrc->v;

  en_addafter(p_en, p_src);

  prg_setrank(p_prg);
  //
  if (p_src->rank > p_tgt->rank) {
    p_en = p_src->p_next;
    en_movebefore(p_src, p_tgt);
    while (p_en->p_fb == 0 && p_en != &p_prg->en_head) {
      p_mv = p_en;
      p_en = p_en->p_next;
      en_moveafter(p_mv, p_src);
    }
  }

  return 0;
}

int prg_lkremove(prog_t *p_prg, int id) {
  enode_t *p_rm;

  prg_enselect(p_prg, id);
  p_rm = p_prg->p_en_select;
  p_prg->p_en_select = &p_prg->en_head;
  if (p_rm == &p_prg->en_head) {
    return -1;
  }

  if (p_rm->p_fb != 0) {
    fb_delete(p_rm->p_fb);
  } else {
    fb_init_pin(p_rm->p_vtgt);
  }
  en_remove(p_rm);
  en_delete(p_rm);

  return 0;
}

void prg_dump(prog_t *p_prg) {
  // vnode_t *p_vn;
  enode_t *p_en;
  std::cout << "\t\tprogram:" << std::endl;

  std::cout << "\t\ten:" << std::endl;
  p_en = p_prg->en_head.p_next;
  while (p_en != &p_prg->en_head) {
    if (p_en->p_fb != 0) {
      std::cout << "  \t\tfb: " << p_en->id << " - " << p_en->fbname
                << ", fc: " << p_en->p_fb->h.fcname << std::endl;
      fb_dump(p_en->p_fb);
    } else {
      std::cout << "  \t\tlk: " << p_en->id << ", From.pin: " << p_en->idsrc
                << "." << p_en->p_vsrc->pinname << " --> "
                << " To.pin: " << p_en->idtgt << "." << p_en->p_vtgt->pinname
                << std::endl;
    }
    p_en = p_en->p_next;
  }
}

int prg_checkloop(prog_t *p_prg, int idSrc, int idTgt) {
  enode_t *p_src, *p_tgt;

  if (idSrc == idTgt) {
    return -1;
  }

  prg_enselect(p_prg, idSrc);
  p_src = p_prg->p_en_select;
  prg_enselect(p_prg, idTgt);
  p_tgt = p_prg->p_en_select;
  if (p_src == &p_prg->en_head || p_tgt == &p_prg->en_head) {
    return -1;
  }

  prg_setrank(p_prg);
  if (p_src->rank > p_tgt->rank) {
    prg_clearmark(p_prg);
    prg_markfbchild(p_prg, p_tgt);
    if (p_src->mark) {
      /* have loop */
      return -1;
    }
  }

  /* no loop */
  return 0;
}
