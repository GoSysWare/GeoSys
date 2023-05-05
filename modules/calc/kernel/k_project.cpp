#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>

#include "modules/calc/include/k_project.h"
#include "modules/calc/include/k_util.h"

static prjinfo_t info;
static pnode_t pn_head = {
    &pn_head, &pn_head, 0, "", "", true, "{00000000-0000-0000-0000-00000000}",
    nullptr};
static pnode_t *p_pn_select = &pn_head;

static int is_run;

pnode_t *prj_gethead() { return &pn_head; }

prjinfo_t *prj_info() { return &info; }

static pnode_t *pn_new() { return new pnode_t; }

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

static void clear_prjinfo() {}

void prj_init(int mode) { clear_prjinfo(); }

void prj_uninit() {}

static int prj_modselect(int id) {
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
static int prj_modselect(std::string name) {
  pnode_t *p_pn;

  if (name.length() == 0) {
    p_pn_select = &pn_head;
    return -1;
  }

  if (p_pn_select->name == name) {
    return 0;
  }

  p_pn = pn_head.p_next;
  while (p_pn != &pn_head) {
    if (p_pn->name == name) {
      p_pn_select = p_pn;
      return 0;
    }
    p_pn = p_pn->p_next;
  }

  return -1;
}

int prj_modadd(int id, std::string name, std::string desc) {
  mod_t *p_mod;
  pnode_t *p_pn;

  p_mod = mod_new();
  if (p_mod == ((void *)0)) {
    return -1;
  }

  p_pn = pn_new();
  if (p_pn == ((void *)0)) {
    mod_delete(p_mod);
    return -1;
  }

  p_pn->p_mod = p_mod;
  p_pn->id = id;
  p_pn->name = name;
  p_pn->desc = desc;
  p_pn->enable = true;

  pn_addbefore(p_pn, &pn_head);

  return 0;
}

int prj_modremove(int idmod) {
  prj_modselect(idmod);

  if (p_pn_select == &pn_head) {
    return -1;
  }
  mod_delete(p_pn_select->p_mod);
  pn_remove(p_pn_select);
  pn_delete(p_pn_select);

  p_pn_select = &pn_head;

  return 0;
}
int prj_prgadd(int idmod, int idprg, std::string name, int type,
               std::string desc, int period) {
  prj_modselect(idmod);
  if (p_pn_select == &pn_head) {
    return -1;
  }
  return mod_prgadd(p_pn_select->p_mod, idprg, name, type, desc, period);
}
int prj_prgremove(int idmod, int idprg) {
  prj_modselect(idmod);
  if (p_pn_select == &pn_head) {
    return -1;
  }
  return mod_prgremove(p_pn_select->p_mod, idprg);
}

void prj_start() {
  pnode_t *p_pn;
  p_pn = pn_head.p_next;
  while (p_pn != &pn_head) {
    if (p_pn->enable) {
      mod_start(p_pn, p_pn->p_mod);
    }
    p_pn = p_pn->p_next;
  }
}

void prj_run() {
  pnode_t *p_pn;
  p_pn = pn_head.p_next;
  while (p_pn != &pn_head) {
    if (p_pn->enable) {
      mod_run(p_pn->p_mod);
    }
    p_pn = p_pn->p_next;
  }
}
void prj_stop() {
  pnode_t *p_pn;
  p_pn = pn_head.p_next;
  while (p_pn != &pn_head) {
    if (p_pn->enable) {
      mod_stop(p_pn->p_mod);
    }
    p_pn = p_pn->p_next;
  }
}

bool prj_check_stop() {
  pnode_t *p_pn;
  p_pn = pn_head.p_next;
  while (p_pn != &pn_head) {
    if (p_pn->enable) {
      if (mod_check_stop(p_pn->p_mod) == false) {
        return false;
      }
    }
    p_pn = p_pn->p_next;
  }
  return true;
}
void prj_join() {
  while (!prj_check_stop()) {
    apollo::cyber::USleep(10 * 1000);
  }
}

void prj_exit() {
  pnode_t *p_pn;
  p_pn = pn_head.p_next;
  while (p_pn != &pn_head) {
    if (p_pn->enable) {
      mod_exit(p_pn, p_pn->p_mod);
    }
    p_pn = p_pn->p_next;
  }
}

void prj_reset() {
  pnode_t *p_pn, *p_del;

  p_pn_select = &pn_head;
  p_pn = pn_head.p_next;
  while (p_pn != &pn_head) {
    p_del = p_pn;
    p_pn = p_pn->p_next;
    pn_remove(p_del);
    mod_delete(p_del->p_mod);
    pn_delete(p_del);
  }
  ev_reset();
  clear_prjinfo();
}

int prj_fbadd(int idmod, int idprg, int id, std::string libname,
              std::string fcname, std::string fbname) {
  if (prj_modselect(idmod) != 0) {
    return -1;
  }
  return mod_fbadd(p_pn_select->p_mod, idprg, id, libname, fcname, fbname);
}

int prj_fbremove(int idmod, int idprg, int id) {
  if (prj_modselect(idmod) != 0) {
    return -1;
  }
  return mod_fbremove(p_pn_select->p_mod, idprg, id);
}

int prj_lkadd(int idmod, int idprg, int id, int fbsrc, int pinsrc, int fbtgt,
              int pintgt) {
  if (prj_modselect(idmod) != 0) {
    return -1;
  }
  return mod_lkadd(p_pn_select->p_mod, idprg, id, fbsrc, pinsrc, fbtgt, pintgt);
}

int prj_lkremove(int idmod, int idprg, int id) {
  if (prj_modselect(idmod) != 0) {
    return -1;
  }
  return mod_lkremove(p_pn_select->p_mod, idprg, id);
}

int prj_viadd(int idmod, int idprg, int idev, int idfb, int pin) {
  if (prj_modselect(idmod) != 0) {
    return -1;
  }
  return mod_viadd(p_pn_select->p_mod, idprg, idev, idfb, pin);
}

int prj_viremove(int idmod, int idprg, int idfb, int pin) {
  if (prj_modselect(idmod) != 0) {
    return -1;
  }
  return mod_viremove(p_pn_select->p_mod, idprg, idfb, pin);
}

int prj_voadd(int idmod, int idprg, int idev, int idfb, int pin) {
  if (prj_modselect(idmod) != 0) {
    return -1;
  }
  return mod_voadd(p_pn_select->p_mod, idprg, idev, idfb, pin);
}

int prj_voremove(int idmod, int idprg, int idfb, int pin) {
  if (prj_modselect(idmod) != 0) {
    return -1;
  }
  return mod_voremove(p_pn_select->p_mod, idprg, idfb, pin);
}

int prj_checkloop(int idmod, int idprg, int idsrc, int idtgt) {
  if (prj_modselect(idmod) != 0) {
    return -1;
  }
  return mod_checkloop(p_pn_select->p_mod, idprg, idsrc, idtgt);
}

void prj_dump() {
  pnode_t *p_pn = 0;
  printf("Project: uuid:%s\ncmd:%d\nstat:%d\n", info.uuid.c_str(), info.cmd_id);
  p_pn = pn_head.p_next;
  while (p_pn != &pn_head) {
    printf(
        "Modules: [id]:%d - [name]:%s - [desc]:%s - [enabel]:%d - [uuid]:%s\n",
        p_pn->id, p_pn->name.c_str(), p_pn->desc.c_str(), p_pn->enable,
        p_pn->uuid.c_str());
    prj_moddump(p_pn->id);
    p_pn = p_pn->p_next;
  }
}

int prj_moddump(int idmod) {
  if (prj_modselect(idmod) != 0) {
    return -1;
  }
  mod_dump(p_pn_select->p_mod);
  return 0;
}

int prj_prgdump(int idmod, int idprg) {
  prog_t *p_prg = 0;
  if (prj_modselect(idmod) != 0) {
    return -1;
  }
  p_prg = mod_prgfind(p_pn_select->p_mod, idprg);
  if (p_prg == ((void *)0)) {
    return -1;
  }
  prg_dump(p_prg);
  return 0;
}

int prj_fbdump(int idmod, int idprg, int idfb) {
  fb_t *p_fb = 0;
  if (prj_modselect(idmod) != 0) {
    return -1;
  }
  p_fb = mod_fbfind(p_pn_select->p_mod, idprg, idfb);
  if (p_fb == ((void *)0)) {
    return -1;
  }
  fb_dump(p_fb);
  return 0;
}

fb_t *prj_fbfind(int idmod, int idprg, int idfb) {
  if (prj_modselect(idmod) != 0) {
    return 0;
  }
  return mod_fbfind(p_pn_select->p_mod, idprg, idfb);
}

prog_t *prj_prgfind(int idmod, int idprg) {
  if (prj_modselect(idmod) != 0) {
    return 0;
  }
  return mod_prgfind(p_pn_select->p_mod, idprg);
}
prog_t *prj_prgfind(int idmod, std::string prog_name) {
  if (prj_modselect(idmod) != 0) {
    return 0;
  }
  return mod_prgfind(p_pn_select->p_mod, prog_name);
}

prog_t *prj_prgfind(std::string mod_name, std::string prog_name) {
  if (prj_modselect(mod_name) != 0) {
    return 0;
  }
  return mod_prgfind(p_pn_select->p_mod, prog_name);
}

mnode_t *prj_prg_info_find(std::string mod_name, std::string prog_name) {
  if (prj_modselect(mod_name) != 0) {
    return 0;
  }
  if (p_pn_select == &pn_head) {
    return 0;
  }
  return mod_prg_info_find(p_pn_select->p_mod, prog_name);
}
mnode_t *prj_prg_info_find(int idmod, int idprg) {
  if (prj_modselect(idmod) != 0) {
    return 0;
  }
  if (p_pn_select == &pn_head) {
    return 0;
  }
  return mod_prg_info_find(p_pn_select->p_mod, idprg);
}

mod_t *prj_modfind(int idmod) {
  if (prj_modselect(idmod) != 0) {
    return 0;
  }
  return p_pn_select->p_mod;
}

mod_t *prj_modfind(std::string mod_name) {
  if (prj_modselect(mod_name) != 0) {
    return 0;
  }
  return p_pn_select->p_mod;
}

pnode_t *prj_mod_info_find(std::string mod_name) {
  if (prj_modselect(mod_name) != 0) {
    return 0;
  }
  if (p_pn_select == &pn_head) {
    return 0;
  }
  return p_pn_select;
}
pnode_t *prj_mod_info_find(int idmod) {
  if (prj_modselect(idmod) != 0) {
    return 0;
  }
  if (p_pn_select == &pn_head) {
    return 0;
  }
  return p_pn_select;
}

int prj_to_snapshot(Bus::ProjSnapshotReq * snapshot_req,
                    Bus::ProjSnapshotRsp *snapshot) {
  pnode_t *p_pn = 0;
  mnode_t *p_mn = 0;
  enode_t *p_en = 0;
  fb_t *p_fb = 0;
  unsigned int i = 0;

  snapshot->mutable_proj_info()->set_prj_uuid(prj_info()->uuid);
  snapshot->mutable_proj_info()->set_cmd_id(prj_info()->cmd_id);

  p_pn = pn_head.p_next;
  while (p_pn != &pn_head) {
    Bus::ModSnapshot *mod_sp = snapshot->add_mods();
    mod_sp->set_mod_id(p_pn->id);
    p_mn = p_pn->p_mod->mn_head.p_next;
    while (p_mn != &p_pn->p_mod->mn_head) {
      apollo::cyber::base::ReadLockGuard<apollo::cyber::base::AtomicRWLock> lg(
          p_mn->mutex);
      Bus::TaskSnapshot *task_sp = mod_sp->add_tasks();
      task_sp->set_mod_id(p_pn->id);
      task_sp->set_task_id(p_mn->id);
      p_en = p_mn->p_prg->en_head.p_next;
      while (p_en != &p_mn->p_prg->en_head) {
        if (p_en->p_fb != ((void *)0)) {
          p_fb = p_en->p_fb;
          // 解析fb的header
          value_tm *val_sp = task_sp->add_vals();
          val_sp->mutable_v()->set_t(v_type::T_UINT64);
          val_sp->mutable_v()->set_ull(p_fb->h.cycle_time);
          val_sp = task_sp->add_vals();
          val_sp->mutable_v()->set_t(v_type::T_UINT64);
          val_sp->mutable_v()->set_ull(p_fb->h.begin_time);
          val_sp = task_sp->add_vals();
          val_sp->mutable_v()->set_t(v_type::T_UINT64);
          val_sp->mutable_v()->set_ull(p_fb->h.expend_time);
          val_sp = task_sp->add_vals();
          val_sp->mutable_v()->set_t(v_type::T_INT32);
          val_sp->mutable_v()->set_i(p_fb->h.flag);

          for (i = 0; i < p_fb->ins.size(); i++) {
            if (IS_NOT_UPLOAD_TYPE(p_fb->ins[i].t))
              continue;
            val_sp = task_sp->add_vals();
            if (p_fb->ins[i].s == PIN_HAS_LOCK) {
              apollo::cyber::base::ReadLockGuard<
                  apollo::cyber::base::ReentrantRWLock>
                  lg(*(p_fb->ins[i].l));
              val_sp->CopyFrom(*(p_fb->ins[i].v));
            } else {
              val_sp->CopyFrom(*(p_fb->ins[i].v));
            }
          }
          for (i = 0; i < p_fb->outs.size(); i++) {
            if (IS_NOT_UPLOAD_TYPE(p_fb->outs[i].t))
              continue;
            val_sp = task_sp->add_vals();
            if (p_fb->outs[i].s == PIN_HAS_LOCK) {
              apollo::cyber::base::ReadLockGuard<
                  apollo::cyber::base::ReentrantRWLock>
                  lg(*(p_fb->outs[i].l));
              val_sp->CopyFrom(*(p_fb->outs[i].v));
            } else {

              val_sp->CopyFrom(*(p_fb->outs[i].v));
            }
          }
        }
        p_en = p_en->p_next;
      }
      p_mn = p_mn->p_next;
    }
    p_pn = p_pn->p_next;
  }

  ev_to_snapshot(snapshot_req, snapshot);
  return 0;
}

int info_cmp(prjinfo_t *info, Bus::ProjectInfoRsp *bus_proj_info) {
  if (info->uuid != bus_proj_info->prj_uuid()) {
    return -1;
  }
  if (info->cmd_id != bus_proj_info->cmd_id()) {
    return -2;
  }
  return 0;
}

int prj_from_snapshot(
                      Bus::ProjSnapshotRsp *snapshot) {
  pnode_t *p_pn = 0;
  mnode_t *p_mn = 0;
  enode_t *p_en = 0;
  fb_t *p_fb = 0;
  unsigned int i = 0;
  unsigned int m = 0;
  unsigned int n = 0;
  unsigned int k = 0;

  if (info_cmp(&info, snapshot->mutable_proj_info()) != 0) {
    return 1;
  }
  p_pn = pn_head.p_next;
  while (p_pn != &pn_head) {
    p_mn = p_pn->p_mod->mn_head.p_next;
    Bus::ModSnapshot mod_sp = snapshot->mods(m++);
    assert(mod_sp.mod_id() == p_pn->id);
    n = 0;
    while (p_mn != &p_pn->p_mod->mn_head) {
      apollo::cyber::base::WriteLockGuard<apollo::cyber::base::AtomicRWLock> lg(
          p_mn->mutex);

      p_en = p_mn->p_prg->en_head.p_next;
      Bus::TaskSnapshot task_sp = mod_sp.tasks(n++);
      assert(task_sp.task_id() == p_mn->id);
      k = 0;
      while (p_en != &p_mn->p_prg->en_head) {
        if (p_en->p_fb != ((void *)0)) {
          p_fb = p_en->p_fb;
          p_fb->h.cycle_time = task_sp.vals(k++).v().ull();
          p_fb->h.begin_time = task_sp.vals(k++).v().ull();
          p_fb->h.expend_time = task_sp.vals(k++).v().ull();
          p_fb->h.flag = task_sp.vals(k++).v().i();
          for (i = 0; i < p_fb->ins.size(); i++) {
            if (IS_NOT_UPLOAD_TYPE(p_fb->ins[i].t))
              continue;

            if (p_fb->ins[i].s == PIN_HAS_LOCK) {
              apollo::cyber::base::WriteLockGuard<
                  apollo::cyber::base::ReentrantRWLock>
                  lg(*(p_fb->ins[i].l));
              p_fb->ins[i].v->CopyFrom(task_sp.vals(k++));
            } else {
              p_fb->ins[i].v->CopyFrom(task_sp.vals(k++));
            }
          }
          for (i = 0; i < p_fb->outs.size(); i++) {
            if (IS_NOT_UPLOAD_TYPE(p_fb->outs[i].t))
              continue;
            if (p_fb->outs[i].s == PIN_HAS_LOCK) {
              apollo::cyber::base::WriteLockGuard<
                  apollo::cyber::base::ReentrantRWLock>
                  lg(*(p_fb->outs[i].l));
              p_fb->outs[i].v->CopyFrom(task_sp.vals(k++));
            } else {
              p_fb->outs[i].v->CopyFrom(task_sp.vals(k++));
            }
          }
        }
        p_en = p_en->p_next;
      }
      p_mn = p_mn->p_next;
    }
    p_pn = p_pn->p_next;
  }

  ev_from_snapshot(snapshot);

  return 0;
}
