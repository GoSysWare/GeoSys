#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>

#include "modules/calc/include/k_compress.h"
#include "modules/calc/include/k_process.h"
#include "modules/calc/include/k_project.h"
#include "modules/calc/include/k_state.h"
#include "modules/calc/include/k_util.h"

static prjinfo_t info;
static prjinfo_t info_p;
static pnode_t pn_head = {
    &pn_head, &pn_head, 0, "", "", true, "{00000000-0000-0000-0000-00000000}",
    nullptr,  0};
static pnode_t *p_pn_select = &pn_head;

static int is_run;

pnode_t *prj_gethead() { return &pn_head; }

prjinfo_t *prj_info() { return &info; }

prjinfo_t *prj_info_p() { return &info_p; }

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

void prj_run() {}

void prj_stop() { is_run = 0; }

void prj_init(int mode) {

  clear_prjinfo();
  prj_run();
}

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
  p_pn->cyber_node = std::move(apollo::cyber::CreateNode(p_pn->name));
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

void prj_exec() {
  pnode_t *p_pn;
  p_pn = pn_head.p_next;
  while (p_pn != &pn_head) {
    if (p_pn->enable) {
      mod_exec(p_pn->p_mod, p_pn->cyber_node);
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

int prj_checkloop(int idmod, int idprg, int idsrc, int idtgt) {
  if (prj_modselect(idmod) != 0) {
    return -1;
  }

  return mod_checkloop(p_pn_select->p_mod, idprg, idsrc, idtgt);
}

void prj_dump() {
  pnode_t *p_pn;

  printf("Project: uuid:%s\ncmd:%d\nstat:%d\n", info.uuid.c_str(), info.id_cmd);
  p_pn = pn_head.p_next;
  while (p_pn != &pn_head) {
    printf(
        "Modules: [id]:%d - [name]:%s - [desc]%s - [enabel]:%d - [uuid]:%s\n",
        p_pn->id, p_pn->name.c_str(), p_pn->desc.c_str(),p_pn->enable,p_pn->uuid.c_str());
    p_pn = p_pn->p_next;
  }
}

int prj_moddump(int idmod) {
  prog_t *p_prg;

  if (prj_modselect(idmod) != 0) {
    return -1;
  }

  mod_dump(p_pn_select->p_mod);
  return 0;
}
int prj_prgdump(int idmod, int idprg) {
  prog_t *p_prg;

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
  fb_t *p_fb;

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

prog_t *prj_prgfind(std::string prog_name) {
  if (prj_modselect(prog_name) != 0) {
    return 0;
  }
  return mod_prgfind(p_pn_select->p_mod, prog_name);
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


int prj_to_snapshot(ProjectSnapshot snapshot)
{
  std::string buf;
  pin_t *ppin;
  pnode_t *p_pn;
  enode_t *p_en;
  fb_t *p_fb;
  unsigned int i;
  int s;
  int v_len;

  p_pn = pn_head.p_next;
  while (p_pn != &pn_head)
  {
    p_en = p_pn->p_prg->en_head.p_next;
    while (p_en != &p_pn->p_prg->en_head)
    {
      if (p_en->p_fb != ((void *)0))
      {
        p_fb = p_en->p_fb;
        for (i = 0; i < p_fb->ins.size(); i++)
        {
          v_len = p_fb->ins[i].v->ByteSize();
          memcpy(buf, &v_len, sizeof(int));
          buf += sizeof(int);
          p_fb->ins[i].v->SerializeToArray(buf, v_len);
          buf += v_len;
          s++;
        }
        for (i = 0; i < p_fb->outs.size(); i++)
        {
          v_len = p_fb->outs[i].v->ByteSize();
          memcpy(buf, &v_len, sizeof(int));
          buf += sizeof(int);
          p_fb->outs[i].v->SerializeToArray(buf, v_len);
          buf += v_len;
          s++;
        }
        for (i = 0; i < p_fb->props.size(); i++)
        {
          v_len = p_fb->props[i].v->ByteSize();
          memcpy(buf, &v_len, sizeof(int));
          buf += sizeof(int);
          p_fb->props[i].v->SerializeToArray(buf, v_len);
          buf += v_len;
          s++;
        }
      }
      p_en = p_en->p_next;
    }
    p_pn = p_pn->p_next;
  }

  buf = ev_to_img(buf);
  // buf = io_to_img(buf);

  pimg->bufsize = buf - pimg->imgbuf;
  info.zimgsize = pimg->bufsize;
  // info.imgsize = s * sizeof(var_t) + sizeof(iostation_t) * IOSTATIONCOUNT;

  // printf("imgsize=%d, zimgsize=%d\n", info.imgsize, info.zimgsize);
  k_runlock(prjlock);

  return 0;
}

// int prj_to_img(prjimg_t *pimg)
// {
//   std::string buf;
//   pin_t *ppin;
//   pnode_t *p_pn;
//   enode_t *p_en;
//   fb_t *p_fb;
//   unsigned int i;
//   int s;
//   int v_len;

//   k_rlock(prjlock);

//   memcpy(&pimg->info, &info, sizeof(prjinfo_t));
//   buf = pimg->imgbuf;

//   s = 0;
//   p_pn = pn_head.p_next;
//   while (p_pn != &pn_head)
//   {
//     p_en = p_pn->p_prg->en_head.p_next;
//     while (p_en != &p_pn->p_prg->en_head)
//     {
//       if (p_en->p_fb != ((void *)0))
//       {
//         p_fb = p_en->p_fb;
//         for (i = 0; i < p_fb->ins.size(); i++)
//         {
//           v_len = p_fb->ins[i].v->ByteSize();
//           memcpy(buf, &v_len, sizeof(int));
//           buf += sizeof(int);
//           p_fb->ins[i].v->SerializeToArray(buf, v_len);
//           buf += v_len;
//           s++;
//         }
//         for (i = 0; i < p_fb->outs.size(); i++)
//         {
//           v_len = p_fb->outs[i].v->ByteSize();
//           memcpy(buf, &v_len, sizeof(int));
//           buf += sizeof(int);
//           p_fb->outs[i].v->SerializeToArray(buf, v_len);
//           buf += v_len;
//           s++;
//         }
//         for (i = 0; i < p_fb->props.size(); i++)
//         {
//           v_len = p_fb->props[i].v->ByteSize();
//           memcpy(buf, &v_len, sizeof(int));
//           buf += sizeof(int);
//           p_fb->props[i].v->SerializeToArray(buf, v_len);
//           buf += v_len;
//           s++;
//         }
//       }
//       p_en = p_en->p_next;
//     }
//     p_pn = p_pn->p_next;
//   }

//   buf = ev_to_img(buf);
//   // buf = io_to_img(buf);

//   pimg->bufsize = buf - pimg->imgbuf;
//   info.zimgsize = pimg->bufsize;
//   // info.imgsize = s * sizeof(var_t) + sizeof(iostation_t) * IOSTATIONCOUNT;

//   // printf("imgsize=%d, zimgsize=%d\n", info.imgsize, info.zimgsize);
//   k_runlock(prjlock);

//   return 0;
// }

// static int info_cmp(prjinfo_t *info1, prjinfo_t *info2)
// {
//   if (strncmp(info1->uuid, info2->uuid, UUIDSIZE) != 0)
//   {
//     return 1;
//   }
//   if (info1->id_cmd != info2->id_cmd)
//   {
//     return 1;
//   }
//   //   // if(strncmp(info1->name, info2->name, PRJNAMESIZE)!=0){
//   //   //	return 1;
//   //   //}

//   return 0;
// }

// int prj_from_img(prjimg_t *pimg)
// {
//   std::string buf;
//   pin_t *ppin;
//   Int t;
//   pnode_t *p_pn;
//   enode_t *p_en;
//   fb_t *p_fb;
//   unsigned int i;
//   int v_len;

//   if (info_cmp(&info, &pimg->info) != 0)
//   {
//     return 1;
//   }

//   buf = pimg->imgbuf;
//   p_pn = pn_head.p_next;
//   while (p_pn != &pn_head)
//   {
//     p_en = p_pn->p_mod->mn_head.p_next;
//     while (p_en != &p_pn->p_mod->mn_head)
//     {
//       if (p_en->p_fb != ((void *)0))
//       {
//         p_fb = p_en->p_fb;
//         for (i = 0; i < p_fb->ins.size(); i++)
//         {
//           v_len = *(int *)buf;
//           buf += sizeof(int);
//           p_fb->ins[i].v->ParseFromArray(buf, v_len);
//           buf += v_len;
//         }
//         for (i = 0; i < p_fb->outs.size(); i++)
//         {
//           v_len = *(int *)buf;
//           buf += sizeof(int);
//           p_fb->outs[i].v->ParseFromArray(buf, v_len);
//           buf += v_len;
//         }
//         for (i = 0; i < p_fb->props.size(); i++)
//         {
//           v_len = *(int *)buf;
//           buf += sizeof(int);
//           p_fb->props[i].v->ParseFromArray(buf, v_len);
//           buf += v_len;
//         }
//       }
//       p_en = p_en->p_next;
//     }
//     p_pn = p_pn->p_next;
//   }

//   buf = ev_from_img(buf);
//   //   buf = io_from_img(buf);

//   if (pimg->bufsize != buf - pimg->imgbuf)
//   {
//     return 1;
//     printf("uz form img error!\n");
//     fflush(stdout);
//   }

//   printf("get imgbuf size=%d\n", pimg->bufsize);
//   return 0;
// }
