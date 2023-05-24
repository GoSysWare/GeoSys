#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>

#include "modules/calc/include/k_module.h"
#include "modules/calc/include/k_project.h"
#include "modules/calc/include/k_util.h"

static mnode_t *mn_new(int type) {
  if (type == Bus::TaskType::PERIODIC) {
    return new period_node_t;
  } else if (type == Bus::TaskType::SERVICE) {
    return new service_node_t;
  } else if (type == Bus::TaskType::FSM) {
    return new fsm_node_t;
  } else if (type == Bus::TaskType::ACTION) {
    return new action_node_t;
  } else if (type == Bus::TaskType::ASYNC) {
    return new task_node_t;
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

static void mod_init(mnode_t *p_mnode, int id, std::string name, int type,
                     std::string desc, int interval) {

  if (type == Bus::TaskType::PERIODIC) {
    ((period_node_t *)p_mnode)->interval = interval;
  } else if (type == Bus::TaskType::SERVICE) {
  } else if (type == Bus::TaskType::FSM) {
    ((fsm_node_t *)p_mnode)->interval = interval;
  } else if (type == Bus::TaskType::ACTION) {
  } else if (type == Bus::TaskType::ASYNC) {
  } else {
    return;
  }
  p_mnode->id = id;
  p_mnode->name = name;
  p_mnode->type = type;
  p_mnode->desc = desc;
  p_mnode->enable = true;
  p_mnode->stop.store(true);
}
static void mod_uninit(mnode_t *p_mnode) {}

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

void mod_run(PNode *p_pn, mod_t *p_mod) {
  mnode_t *p_mn;

  p_mn = p_mod->mn_head.p_next;
  while (p_mn != &p_mod->mn_head) {

    // task的使能
    if (!p_mn->enable)
      continue;
    // task 初始化
    p_mn->info.status.store(TaskStatus::READY);

    prg_init(p_mn->p_prg, &p_mn->info);

    // task 分类型处理
    if (p_mn->type == Bus::TaskType::PERIODIC) {
      apollo::cyber::TimerOption opt;
      opt.oneshot = false;
      opt.callback = [p_mn]() {
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
          // apollo::cyber::base::WriteLockGuard<apollo::cyber::base::AtomicRWLock>
          //     lg(p_mn->mutex);

          prg_exec(p_mn->p_prg, &p_mn->info);
        }

        // prg_dump(p_mn->p_prg);
        p_mn->info.expend_time = (apollo::cyber::Time::Now() -
                                  apollo::cyber::Time(p_mn->info.begin_time))
                                     .ToNanosecond();
        // task完成一次运算周期
        p_mn->info.status.store(TaskStatus::FINISH);

        AERROR << "Async task name:" << p_mn->name
               << " begin_time:" << p_mn->info.begin_time
               << " cycle_time:" << p_mn->info.cycle_time
               << " expend_time:" << p_mn->info.expend_time;
      };
      opt.period = ((period_node_t *)p_mn)->interval;
      ((period_node_t *)p_mn)->timer.SetTimerOption(opt);
      ((period_node_t *)p_mn)->timer.Start();
      p_mn->info.prev_time = apollo::cyber::Time::Now().ToNanosecond();

    } else if (p_mn->type == Bus::TaskType::SERVICE) {
      auto f = [p_mn](const vam_t &request, vam_t &response) {
        // to do
      };
      auto service_ =
          apollo::cyber::GlobalNode()->CreateService<value_tm, value_tm>(
              p_mn->name, f);
    } else if (p_mn->type == Bus::TaskType::FSM) {
      apollo::cyber::TimerOption opt;
      opt.oneshot = false;
      opt.callback = [p_mn]() { prg_exec(p_mn->p_prg, &p_mn->info); };
      opt.period = ((fsm_node_t *)p_mn)->interval;
      ((fsm_node_t *)p_mn)->timer.SetTimerOption(opt);
      ((fsm_node_t *)p_mn)->timer.Start();
    } else if (p_mn->type == Bus::TaskType::ACTION) {
      // to do
    } else if (p_mn->type == Bus::TaskType::ASYNC) {

      auto f = [p_mn](const std::shared_ptr<TaskReqParam> &request,
                      std::shared_ptr<TaskRspParam> &response) {
        //发出停止命令
        if (p_mn->stop.load()) {
          p_mn->info.status.store(TaskStatus::ABORT);
          return;
        }
        p_mn->info.status.store(TaskStatus::START);
        ((task_node_t *)p_mn)->client = request->client();
        p_mn->info.begin_time = apollo::cyber::Time::Now().ToNanosecond();
        p_mn->info.cycle_time =
            apollo::cyber::Duration(
                int64_t(p_mn->info.begin_time - p_mn->info.prev_time))
                .ToNanosecond();
        p_mn->info.prev_time = p_mn->info.begin_time;
        {
          // apollo::cyber::base::WriteLockGuard<apollo::cyber::base::AtomicRWLock>
          //     lg(p_mn->mutex);

          prg_exec(p_mn->p_prg, &p_mn->info);
        }

        p_mn->info.expend_time = (apollo::cyber::Time::Now() -
                                  apollo::cyber::Time(p_mn->info.begin_time))
                                     .ToNanosecond();
        response->set_timestamp(apollo::cyber::Time::Now().ToNanosecond());

        p_mn->info.status.store(TaskStatus::FINISH);

        // AERROR << "Async task name:" << p_mn->name
        //        << " client:" << request->client()
        //        << " begin_time:" << p_mn->info.begin_time
        //        << " cycle_time:" << p_mn->info.cycle_time
        //        << " expend_time:" << p_mn->info.expend_time;
      };
      ((task_node_t *)p_mn)->task_server =
          apollo::cyber::GlobalNode()
              ->CreateAsyncTask<TaskReqParam, TaskRspParam>(
                  p_pn->name + "." + p_mn->name, f);
    }
    p_mn = p_mn->p_next;
  }
}

void mod_start(mod_t *p_mod) {
  mnode_t *p_mn;
  p_mn = p_mod->mn_head.p_next;
  while (p_mn != &p_mod->mn_head) {
    p_mn->stop.store(false);
    p_mn = p_mn->p_next;
  }
}

void mod_stop(mod_t *p_mod) {
  mnode_t *p_mn;
  p_mn = p_mod->mn_head.p_next;
  while (p_mn != &p_mod->mn_head) {
    p_mn->stop.store(true);
    p_mn = p_mn->p_next;
  }
}
// 判断module下所有的task 是否都是终止或者完成状态
bool mod_check_stop(mod_t *p_mod) {
  mnode_t *p_mn;
  p_mn = p_mod->mn_head.p_next;
  while (p_mn != &p_mod->mn_head) {
    // task的使能
    if (p_mn->info.status.load() != TaskStatus::READY &&
        p_mn->info.status.load() != TaskStatus::ABORT &&
        p_mn->info.status.load() != TaskStatus::FINISH) {
      return false;
    }
    p_mn = p_mn->p_next;
  }
  return true;
}

void mod_exit(PNode *p_pn, mod_t *p_mod) {
  mnode_t *p_mn;
  p_mn = p_mod->mn_head.p_next;
  while (p_mn != &p_mod->mn_head) {
    // task的使能
    if (!p_mn->enable)
      continue;
    if (p_mn->type == Bus::TaskType::PERIODIC) {
      ((period_node_t *)p_mn)->timer.Stop();
    } else if (p_mn->type == Bus::TaskType::SERVICE) {
      /* code */
    } else if (p_mn->type == Bus::TaskType::FSM) {
      ((fsm_node_t *)p_mn)->timer.Stop();
    } else if (p_mn->type == Bus::TaskType::ACTION) {
      /* code */
    } else if (p_mn->type == Bus::TaskType::ASYNC) {
      apollo::cyber::GlobalNode()->RemoveAsyncTask(p_pn->name + "." +
                                                   p_mn->name);
    }
    p_mn = p_mn->p_next;
  }
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

int mod_prgadd(mod_t *p_mod, int id, std::string name, int type,
               std::string desc, int interval) {
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

  mod_init(p_pn, id, name, type, desc, interval);

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

int mod_fbadd(mod_t *p_mod, int idprg, int id, std::string libname,
              std::string fcname, std::string fbname) {
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

int mod_viadd(mod_t *p_mod, int idprg, int idev, int idfb, int pin) {
  if (mod_prgselect(p_mod, idprg) != 0) {
    return -1;
  }

  return prg_viadd(p_mod->p_mn_select->p_prg, idev, idfb, pin);
}
int mod_viremove(mod_t *p_mod, int idprg, int idfb, int pin) {
  if (mod_prgselect(p_mod, idprg) != 0) {
    return -1;
  }

  return prg_viremove(p_mod->p_mn_select->p_prg, idfb, pin);
}
int mod_voadd(mod_t *p_mod, int idprg, int idev, int idfb, int pin) {
  if (mod_prgselect(p_mod, idprg) != 0) {
    return -1;
  }

  return prg_voadd(p_mod->p_mn_select->p_prg, idev, idfb, pin);
}
int mod_voremove(mod_t *p_mod, int idprg, int idfb, int pin) {
  if (mod_prgselect(p_mod, idprg) != 0) {
    return -1;
  }

  return prg_voremove(p_mod->p_mn_select->p_prg, idfb, pin);
}
int mod_checkloop(mod_t *p_mod, int idprg, int idsrc, int idtgt) {
  if (mod_prgselect(p_mod, idprg) != 0) {
    return -1;
  }

  return prg_checkloop(p_mod->p_mn_select->p_prg, idsrc, idtgt);
}

void mod_dump(mod_t *p_mod) {
  mnode_t *p_mn;
  p_mn = p_mod->mn_head.p_next;
  while (p_mn != &p_mod->mn_head) {
    printf("\tTask: [id]:%d - [name]:%s - [type]:%d - [enable]:%d\n", p_mn->id,
           p_mn->name.c_str(), p_mn->type, p_mn->enable);
    mod_prgdump(p_mod, p_mn->id);
    p_mn = p_mn->p_next;
  }
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

mnode_t *mod_prg_info_find(mod_t *p_mod, int idprg) {
  if (mod_prgselect(p_mod, idprg) != 0) {
    return 0;
  }
  if (p_mod->p_mn_select == &p_mod->mn_head) {
    return 0;
  }
  return p_mod->p_mn_select;
}
mnode_t *mod_prg_info_find(mod_t *p_mod, std::string prog_name) {
  if (mod_prgselect(p_mod, prog_name) != 0) {
    return 0;
  }
  if (p_mod->p_mn_select == &p_mod->mn_head) {
    return 0;
  }
  return p_mod->p_mn_select;
}

// int mod_to_img(prjimg_t *pimg) {
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
//   std::string buf;
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
