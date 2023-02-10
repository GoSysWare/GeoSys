#ifndef k_module_h
#define k_module_h
// #ifdef __cplusplus
// extern "C" {
// #endif

#include "cyber/cyber.h"
#include "k_config.h"
#include "k_program.h"
#include "modules/calc/proto/task_def.pb.h"
#include "modules/calc/proto/cmd.pb.h"
#include "modules/calc/proto/edit.pb.h"


typedef struct ModInfo {
  std::string uuid;
  int id_cmd;
} modinfo_t;

typedef struct MNode {
  struct MNode *p_prev;
  struct MNode *p_next;
  int id;
  std::string name;
  int type;
  std::string desc;
  bool enable;
  proginfo_t info;
  prog_t *p_prg;
} mnode_t;

// typedef struct MNode{
//     struct MNode *p_prev;
//     struct MNode *p_next;
//     int id;
//     std::string  name;
//     int type;
//     bool enable;
//     std::string creator;
// 	apollo::cyber::Timer timer;
//     int interval;
//     std::vector<std::string> topic;
//     proginfo_t info;
//     prog_t *p_prg;
// }mnode_t;

typedef struct MTaskNode : MNode {
  std::string client;
  std::shared_ptr<apollo::cyber::AsyncTask<TaskReqParam, TaskRspParam>>
      task_server;
} task_node_t;

typedef struct MPeriodNode : MNode {
  std::string client;
  int interval{50};
  apollo::cyber::Timer timer;
} period_node_t;

typedef struct MServiceNode : MNode {
  vam_t requese;
  vam_t respone;
} service_node_t;

typedef struct MActionNode : MNode {
  std::string client;
  vam_t requese;
  vam_t respone;
} action_node_t;

typedef struct MFsmNode : MNode {
  std::string client;
  int interval;
  apollo::cyber::Timer timer;
} fsm_node_t;

typedef struct MTimerNode : MNode {
  std::string client;
  int interval;
  apollo::cyber::Timer timer;
} timer_node_t;

typedef struct Module {
  mnode_t mn_head;
  task_node_t mn_task_head;
  service_node_t mn_serivce_head;
  period_node_t mn_period_head;
  action_node_t mn_action_head;
  fsm_node_t mn_fsm_head;
  timer_node_t mn_timer_head;
  mnode_t *p_mn_select;
  task_node_t *p_mn_task;
  service_node_t *p_mn_service;
  period_node_t *p_mn_period;
  action_node_t *p_mn_action;
  fsm_node_t *p_mn_fsm;
  timer_node_t *p_mn_timer;
} mod_t;

void *mod_main_loop(void *sth);

void mod_run(mod_t *p_mod);
void mod_stop(mod_t *p_mod);
void mod_reset(mod_t *p_mod);

mod_t *mod_new();
void mod_delete(mod_t *p_mod);

int mod_prgadd(mod_t *p_mod, int id, std::string name, int type,
               std::string desc, int interval);
               
int mod_prgremove(mod_t *p_mod, int id);
void mod_start(mod_t *p_mod);
void mod_stop(mod_t *p_mod);

int mod_fbadd(mod_t *p_mod, int idprg, int id, std::string libname,
              std::string fcname, std::string fbname);
int mod_fbremove(mod_t *p_mod, int idprg, int id);
int mod_lkadd(mod_t *p_mod, int idprg, int id, int fbsrc, int pinsrc, int fbtgt,
              int pintgt);
int mod_lkremove(mod_t *p_mod, int idprg, int id);

int mod_viadd(mod_t *p_mod, int idprg,int idev, int idfb, int pin);
int mod_viremove(mod_t *p_mod, int idprg, int idfb, int pin);
int mod_voadd(mod_t *p_mod, int idprg, int idev, int idfb, int pin);
int mod_voremove(mod_t *p_mod, int idprg, int idfb, int pin);

int mod_checkloop(mod_t *p_mod, int idprg, int idsrc, int idtgt);

void mod_dump(mod_t *p_mod);

int mod_prgdump(mod_t *p_mod, int idprg);
int mod_fbdump(mod_t *p_mod, int idprg, int idfb);

fb_t *mod_fbfind(mod_t *p_mod, int idprg, int idfb);

prog_t *mod_prgfind(mod_t *p_mod, int idprg);
prog_t *mod_prgfind(mod_t *p_mod, std::string prog_name);

#endif
