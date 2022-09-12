#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>

#include "modules/calc/include/k_compress.h"
#include "modules/calc/include/k_module.h"
#include "modules/calc/include/k_process.h"
#include "modules/calc/include/k_state.h"
#include "modules/calc/include/k_util.h"

#include "modules/calc/proto/cmd.pb.h"

static mnode_t *mn_new(int type) {
  if (type == Cmd::TaskType::PERIODIC) {
    return new period_node_t;
  } else if (type == Cmd::TaskType::SERVICE) {
    return new service_node_t;
  } else if (type == Cmd::TaskType::FSM) {
    return new fsm_node_t;
  } else if (type == Cmd::TaskType::ACTION) {
    return new action_node_t;
  } else if (type == Cmd::TaskType::ASYNC) {
    return new task_node_t;
  } else if (type == Cmd::TaskType::TIMER) {
    return new timer_node_t;
  } else {
    return 0;
  }
}
static void mn_delete(mnode_t *p) { delete p; }

static void mn_addbefore(mnode_t *p, mnode_t *p_ref) {
  p->p_prev = p_ref->p_prev;
  p->p_next = p_ref;
  p_ref->p_prev->p_next = p;
  p_ref->p_prev = p;
}

static void mn_addafter(mnode_t *p, mnode_t *p_ref) {
  p->p_prev = p_ref;
  p->p_next = p_ref->p_next;
  p_ref->p_next->p_prev = p;
  p_ref->p_next = p;
}

static void mn_remove(mnode_t *p) {
  p->p_prev->p_next = p->p_next;
  p->p_next->p_prev = p->p_prev;
}

void mod_stop(mod_t *p_mod) {
  mnode_t *p_mn;

  p_mn = p_mod->mn_head.p_next;
  while (p_mn != &p_mod->mn_head) {
    // if(p_mn->type == Cmd::TaskType::PERIODIC)
    // {
    //     p_mn->timer.Stop();

    // } else if (p_mn->type == Cmd::TaskType::SERVICE)
    // {

    //   /* code */
    // } else if (p_mn->type == Cmd::TaskType::FSM)
    // {
    //     p_mn->timer.Stop();

    // } else if (p_mn->type == Cmd::TaskType::ACTION)
    // {
    //   /* code */
    // }
    p_mn = p_mn->p_next;
  }
}
void mod_init(mod_t *p_mod) {}
void mod_uninit(mod_t *p_mod) {}

void mod_reset(mod_t *p_mod) {
  mnode_t *p_mn, *p_del;
  p_mod->p_mn_select = &p_mod->mn_head;
  p_mn = p_mod->mn_head.p_next;
  while (p_mn != &p_mod->mn_head) {
    p_del = p_mn;
    p_mn = p_mn->p_next;
    mn_remove(p_del);
    prg_delete(p_del->p_prg);
    mn_delete(p_del);
  }
  ev_reset();
}

static int mod_prgselect(mod_t *p_mod, int id) {
  mnode_t *p_mn;
  if (id == 0) {
    p_mod->p_mn_select = &p_mod->mn_head;
    return -1;
  }

  if (p_mod->p_mn_select->id == id) {
    return 0;
  }

  p_mn = p_mod->mn_head.p_next;
  while (p_mn != &p_mod->mn_head) {
    if (p_mn->id == id) {
      p_mod->p_mn_select = p_mn;
      return 0;
    }
    p_mn = p_mn->p_next;
  }

  return -1;
}

static int mod_prgselect(mod_t *p_mod, std::string prog_name) {
  mnode_t *p_mn;

  if (prog_name.size() == 0) {
    p_mod->p_mn_select = &p_mod->mn_head;
    return -1;
  }

  if (p_mod->p_mn_select->name == prog_name) {
    return 0;
  }

  p_mn = p_mod->mn_head.p_next;
  while (p_mn != &p_mod->mn_head) {
    if (p_mn->name == prog_name) {
      p_mod->p_mn_select = p_mn;
      return 0;
    }
    p_mn = p_mn->p_next;
  }

  return -1;
}

mod_t *mod_new() {
  mod_t *p_new;

  p_new = new mod_t;
  if (p_new != 0) {
    p_new->mn_head.p_prev = &p_new->mn_head;
    p_new->mn_head.p_next = &p_new->mn_head;
    p_new->p_mn_select = &p_new->mn_head;

    p_new->mn_task_head.p_prev = &p_new->mn_task_head;
    p_new->mn_task_head.p_next = &p_new->mn_task_head;
    p_new->p_mn_task = &p_new->mn_task_head;

    p_new->mn_serivce_head.p_prev = &p_new->mn_serivce_head;
    p_new->mn_serivce_head.p_next = &p_new->mn_serivce_head;
    p_new->p_mn_service = &p_new->mn_serivce_head;

    p_new->mn_period_head.p_prev = &p_new->mn_period_head;
    p_new->mn_period_head.p_next = &p_new->mn_period_head;
    p_new->p_mn_period = &p_new->mn_period_head;

    p_new->mn_action_head.p_prev = &p_new->mn_action_head;
    p_new->mn_action_head.p_next = &p_new->mn_action_head;
    p_new->p_mn_action = &p_new->mn_action_head;

    p_new->mn_fsm_head.p_prev = &p_new->mn_fsm_head;
    p_new->mn_fsm_head.p_next = &p_new->mn_fsm_head;
    p_new->p_mn_fsm = &p_new->mn_fsm_head;

    p_new->mn_timer_head.p_prev = &p_new->mn_timer_head;
    p_new->mn_timer_head.p_next = &p_new->mn_timer_head;
    p_new->p_mn_timer = &p_new->mn_timer_head;
  }

  return p_new;
}

void mod_delete(mod_t *p_mod) {
  mnode_t *p_mn, *p_erm;

  /* clear enode list */
  p_mn = p_mod->mn_head.p_next;
  while (p_mn != &p_mod->mn_head) {
    p_erm = p_mn;
    p_mn = p_mn->p_next;
    if (p_erm->p_prg != 0) {
      prg_delete(p_erm->p_prg);
    }
    mn_remove(p_erm);
    mn_delete(p_erm);
  }
  delete p_mod;
}
int mod_prgadd(mod_t *p_mod, int id, std::string name, int type) {
  prog_t *p_prg;
  mnode_t *p_pn;

  p_prg = prg_new();
  if (p_prg == ((void *)0)) {
    return -1;
  }
  p_pn = mn_new(type);
  if (p_pn == ((void *)0)) {
    prg_delete(p_prg);
    return -1;
  }

  p_pn->p_prg = p_prg;
  p_pn->id = id;
  p_pn->name = name;
  p_pn->type = type;

  mn_addbefore(p_pn, &p_mod->mn_head);

  return 0;
}

int mod_prgremove(mod_t *p_mod, int id) {
  mod_prgselect(p_mod, id);

  if (p_mod->p_mn_select == &p_mod->mn_head) {
    return -1;
  }

  prg_delete(p_mod->p_mn_select->p_prg);
  mn_remove(p_mod->p_mn_select);
  mn_delete(p_mod->p_mn_select);

  p_mod->p_mn_select = &p_mod->mn_head;

  return 0;
}

void mod_exec(mod_t *p_mod, std::shared_ptr<apollo::cyber::Node> node) {
  mnode_t *p_mn;

  p_mn = p_mod->mn_head.p_next;
  while (p_mn != &p_mod->mn_head) {
    if (p_mn->type == Cmd::TaskType::PERIODIC) {
      apollo::cyber::TimerOption opt;
      opt.oneshot = false;
      opt.callback = [p_mn]() { prg_exec(p_mn->p_prg); };
      opt.period = ((period_node_t *)p_mn)->interval;
      ((period_node_t *)p_mn)->timer.SetTimerOption(opt);
      ((period_node_t *)p_mn)->timer.Start();
    } else if (p_mn->type == Cmd::TaskType::SERVICE) {  
      auto f = [p_mn]( const vam_t &request, vam_t &response) { 
        fb_t * pqfb, *ppfb; 
        pqfb = prg_fbfind_by_lib(p_mn->p_prg,"Task","REQUEST");
        if(pqfb){
            fb_reset(pqfb);
            fb_setpin(pqfb, PININPUT, 1, request);
        }
        ppfb = prg_fbfind_by_lib(p_mn->p_prg,"Task","RESPONSE");
        if(ppfb){
            fb_reset(pqfb);
            fb_setpin(ppfb, PINOUTPUT, 1, response);
        }
        prg_exec(p_mn->p_prg); 

      };
      auto service_ = node->CreateService<value_tm, value_tm>(p_mn->name, f);
    } else if (p_mn->type == Cmd::TaskType::FSM) {
      apollo::cyber::TimerOption opt;
      opt.oneshot = false;
      opt.callback = [p_mn]() { prg_exec(p_mn->p_prg); };
      opt.period = ((fsm_node_t *)p_mn)->interval;
      ((fsm_node_t *)p_mn)->timer.SetTimerOption(opt);
      ((fsm_node_t *)p_mn)->timer.Start();
    } else if (p_mn->type == Cmd::TaskType::ACTION) {

    }
     else if (p_mn->type == Cmd::TaskType::ASYNC) {
      
      auto f = [p_mn]( const vam_t &request, vam_t &response) { 
        fb_t * pqfb, *ppfb; 
        pqfb = prg_fbfind_by_lib(p_mn->p_prg,"Task","REQUEST");
        if(pqfb){
            fb_reset(pqfb);
            fb_setpin(pqfb, PININPUT, 1, request);
        }
        ppfb = prg_fbfind_by_lib(p_mn->p_prg,"Task","RESPONSE");
        if(ppfb){
            fb_reset(pqfb);
            fb_setpin(ppfb, PINOUTPUT, 1, response);
        }
        prg_exec(p_mn->p_prg); 

      };
      auto service_ = node->CreateAsyncTask<value_tm, value_tm>(p_mn->name, f);  
    }
    p_mn = p_mn->p_next;
  }
}

void mod_dump(mod_t *p_mod) {
  mnode_t *p_mn;
  p_mn = p_mod->mn_head.p_next;
  while (p_mn != &p_mod->mn_head) {
    printf("prg:%d - %s\n", p_mn->id, p_mn->name.c_str());
    p_mn = p_mn->p_next;
  }
}

int mod_fbadd(mod_t *p_mod, int idprg, int id, char *libname, char *fcname,
              char *fbname) {
  if (mod_prgselect(p_mod, idprg) != 0) {
    return -1;
  }
  return prg_fbadd(p_mod->p_mn_select->p_prg, id, libname, fcname, fbname);
}

int mod_fbremove(mod_t *p_mod, int idprg, int id) {
  if (mod_prgselect(p_mod, idprg) != 0) {
    return -1;
  }

  return prg_fbremove(p_mod->p_mn_select->p_prg, id);
}

int mod_lkadd(mod_t *p_mod, int idprg, int id, int fbsrc, int pinsrc, int fbtgt,
              int pintgt) {
  if (mod_prgselect(p_mod, idprg) != 0) {
    return -1;
  }

  return prg_lkadd(p_mod->p_mn_select->p_prg, id, fbsrc, pinsrc, fbtgt, pintgt);
}

int mod_lkremove(mod_t *p_mod, int idprg, int id) {
  if (mod_prgselect(p_mod, idprg) != 0) {
    return -1;
  }

  return prg_lkremove(p_mod->p_mn_select->p_prg, id);
}

int mod_checkloop(mod_t *p_mod, int idprg, int idsrc, int idtgt) {
  if (mod_prgselect(p_mod, idprg) != 0) {
    return -1;
  }

  return prg_checkloop(p_mod->p_mn_select->p_prg, idsrc, idtgt);
}

int mod_prgdump(mod_t *p_mod, int idprg) {
  if (mod_prgselect(p_mod, idprg) != 0) {
    return -1;
  }

  prg_dump(p_mod->p_mn_select->p_prg);
  return 0;
}

int mod_fbdump(mod_t *p_mod, int idprg, int idfb) {
  fb_t *p_fb;

  if (mod_prgselect(p_mod, idprg) != 0) {
    return -1;
  }

  p_fb = prg_fbfind(p_mod->p_mn_select->p_prg, idfb);
  if (p_fb == ((void *)0)) {
    return -1;
  }

  fb_dump(p_fb);
  return 0;
}

fb_t *mod_fbfind(mod_t *p_mod, int idprg, int idfb) {
  if (mod_prgselect(p_mod, idprg) != 0) {
    return 0;
  }

  return prg_fbfind(p_mod->p_mn_select->p_prg, idfb);
}
prog_t *mod_prgfind(mod_t *p_mod, int idprg) {
  if (mod_prgselect(p_mod, idprg) != 0) {
    return 0;
  }
  return p_mod->p_mn_select->p_prg;
}
prog_t *mod_prgfind(mod_t *p_mod, std::string prog_name) {
  if (mod_prgselect(p_mod, prog_name) != 0) {
    return 0;
  }
  return p_mod->p_mn_select->p_prg;
}

// int mod_to_img(prjimg_t *pimg) {
//   char *buf;
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
//   while (p_pn != &pn_head) {
//     p_en = p_pn->p_prg->en_head.p_next;
//     while (p_en != &p_pn->p_prg->en_head) {
//       if (p_en->p_fb != ((void *)0)) {
//         p_fb = p_en->p_fb;
//         for (i = 0; i < p_fb->ins.size(); i++) {
//           v_len = p_fb->ins[i].v->ByteSize();
//           memcpy(buf,&v_len,sizeof(int));
//           buf += sizeof(int);
//           p_fb->ins[i].v->SerializeToArray(buf,v_len);
//           buf +=  v_len;
//           s++;
//         }
//         for (i = 0; i < p_fb->outs.size(); i++) {
//           v_len = p_fb->outs[i].v->ByteSize();
//           memcpy(buf,&v_len,sizeof(int));
//           buf += sizeof(int);
//           p_fb->outs[i].v->SerializeToArray(buf,v_len);
//           buf +=  v_len;
//           s++;
//         }
//        for (i = 0; i < p_fb->props.size(); i++) {
//           v_len = p_fb->props[i].v->ByteSize();
//           memcpy(buf,&v_len,sizeof(int));
//           buf += sizeof(int);
//           p_fb->props[i].v->SerializeToArray(buf,v_len);
//           buf +=  v_len;
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
//   // info.imgsize = s * sizeof(var_t) + sizeof(iostation_t) *
//   IOSTATIONCOUNT;

//   // printf("imgsize=%d, zimgsize=%d\n", info.imgsize, info.zimgsize);
//   k_runlock(prjlock);

//   return 0;
// }

// static int info_cmp(prjinfo_t *info1, prjinfo_t *info2) {
//   if (strncmp(info1->uuid, info2->uuid, UUIDSIZE) != 0) {
//     return 1;
//   }
//   if (info1->id_cmd != info2->id_cmd) {
//     return 1;
//   }
// //   // if(strncmp(info1->name, info2->name, PRJNAMESIZE)!=0){
// //   //	return 1;
// //   //}

//   return 0;
// }

// int mod_from_img(prjimg_t *pimg) {
//   char *buf;
//   pin_t *ppin;
//   Int t;
//   pnode_t *p_pn;
//   enode_t *p_en;
//   fb_t *p_fb;
//   unsigned int i;
//   int v_len;

//   if (info_cmp(&info, &pimg->info) != 0) {
//     return 1;
//   }

//   buf = pimg->imgbuf;
//   p_pn = pn_head.p_next;
//   while (p_pn != &pn_head) {
//     p_en = p_pn->p_prg->en_head.p_next;
//     while (p_en != &p_pn->p_prg->en_head) {
//       if (p_en->p_fb != ((void *)0)) {
//         p_fb = p_en->p_fb;
//         for (i = 0; i < p_fb->ins.size(); i++) {
//           v_len = *(int*)buf;
//           buf += sizeof(int);
//           p_fb->ins[i].v->ParseFromArray(buf,v_len);
//           buf +=  v_len;

//         }
//       for (i = 0; i < p_fb->outs.size(); i++) {
//           v_len = *(int*)buf;
//           buf += sizeof(int);
//           p_fb->outs[i].v->ParseFromArray(buf,v_len);
//           buf +=  v_len;
//         }
//         for (i = 0; i < p_fb->props.size(); i++) {
//           v_len = *(int*)buf;
//           buf += sizeof(int);
//           p_fb->props[i].v->ParseFromArray(buf,v_len);
//           buf +=  v_len;
//         }
//       }
//       p_en = p_en->p_next;
//     }
//     p_pn = p_pn->p_next;
//   }

//   buf = ev_from_img(buf);
// //   buf = io_from_img(buf);

//   if (pimg->bufsize != buf - pimg->imgbuf) {
//     return 1;
//     printf("uz form img error!\n");
//     fflush(stdout);
//   }

//   printf("get imgbuf size=%d\n",pimg->bufsize);
//   return 0;
// }
