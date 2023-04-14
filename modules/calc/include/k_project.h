#ifndef k_project_h
#define k_project_h

#include "cyber/cyber.h"

#include "modules/calc/proto/snapshot.pb.h"

#include "k_config.h"
#include "k_module.h"

typedef struct PrjInfo {
  std::string uuid;
  unsigned int cmd_id;
} prjinfo_t;

typedef struct PNode {
  struct PNode *p_prev;
  struct PNode *p_next;
  int id;
  std::string name;
  std::string desc;
  bool enable;
  std::string uuid;
  mod_t *p_mod;
} pnode_t;

void prj_init(int server);
void prj_uninit();
void prj_reset();

int prj_modadd(int idmod, std::string name, std::string desc);
int prj_modremove(int idmod);

int prj_prgadd(int idmod, int idprg, std::string name, int type,
               std::string desc = "", int period = 50);
int prj_prgremove(int idmod, int idprg);

void prj_start();
void prj_stop();

prjinfo_t *prj_info();

int prj_fbadd(int idmod, int idprg, int id, std::string libname,
              std::string fcname, std::string fbname);
int prj_fbremove(int idmod, int idprg, int id);
int prj_lkadd(int idmod, int idprg, int id, int fbsrc, int pinsrc, int fbtgt,
              int pintgt);
int prj_lkremove(int idmod, int idprg, int id);

int prj_viadd(int idmod, int idprg, int idev, int idfb, int pin);
int prj_viremove(int idmod, int idprg, int idfb, int pin);
int prj_voadd(int idmod, int idprg, int idev, int idfb, int pin);
int prj_voremove(int idmod, int idprg, int idfb, int pin);

int prj_checkloop(int idmod, int idprg, int idsrc, int idtgt);

pnode_t *prj_gethead();

void prj_dump();
int prj_moddump(int idmod);
int prj_prgdump(int idmod, int idprg);
int prj_fbdump(int idmod, int idprg, int idfb);

fb_t *prj_fbfind(int idmod, int idprg, int idfb);
prog_t *prj_prgfind(int idmod, int idprg);
prog_t *prj_prgfind(int idmod, std::string prog_name);
prog_t *prj_prgfind(std::string mod_name, std::string prog_name);
mnode_t *prj_prg_info_find(std::string mod_name, std::string prog_name);
mnode_t *prj_prg_info_find(int idmod, int idprg);

mod_t *prj_modfind(int idmod);
mod_t *prj_modfind(std::string mod_name);
pnode_t *prj_mod_info_find(std::string mod_name);
pnode_t *prj_mod_info_find(int idmod);

int prj_to_snapshot(Bus::ProjSnapshotRsp *snapshot);
int prj_from_snapshot(Bus::ProjSnapshotRsp *snapshot);

// int prj_img_size();
// int prj_to_img(prjimg_t *img);
// int prj_from_img(prjimg_t *pimg);

#endif
