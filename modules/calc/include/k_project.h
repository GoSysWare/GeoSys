#ifndef k_project_h
#define k_project_h

#include "cyber/cyber.h"
#include "k_config.h"
#include "k_io.h"
#include "k_module.h"

typedef struct PrjInfo {
  std::string uuid;
  int id_cmd;
  int id_stb;
  int stat;
  int peerlife;
  int imgsize;
  int zimgsize;
} prjinfo_t;

typedef struct PrjImg {
  prjinfo_t info;
  int bufsize;
  char imgbuf[IMAGSIZE];
} prjimg_t;

typedef struct PNode {
  struct PNode *p_prev;
  struct PNode *p_next;
  int id;
  std::string name;
  std::string desc;
  bool enable;
  std::string uuid;
  std::unique_ptr<apollo::cyber::Node> cyber_node;
  mod_t *p_mod;
} pnode_t;

void prj_run();
void prj_stop();
void prj_init(int server);
void prj_uninit();
void prj_reset();

int prj_modadd(int idmod, std::string name, std::string desc);
int prj_modremove(int idmod);

int prj_prgadd(int idmod, int idprg, std::string name,int type,std::string desc, int period);
int prj_prgremove(int idmod, int idprg);

void prj_exec();

prjinfo_t *prj_info();
prjinfo_t *prj_info_p();

int prj_fbadd(int idmod, int idprg, int id, std::string libname,
              std::string fcname, std::string fbname);
int prj_fbremove(int idmod, int idprg, int id);
int prj_lkadd(int idmod, int idprg, int id, int fbsrc, int pinsrc, int fbtgt,
              int pintgt);
int prj_lkremove(int idmod, int idprg, int id);
int prj_checkloop(int idmod, int idprg, int idsrc, int idtgt);

pnode_t *prj_gethead();
void prj_dump();

int prj_moddump(int idmod);
int prj_prgdump(int idmod, int idprg);
int prj_fbdump(int idmod, int idprg, int idfb);

fb_t *prj_fbfind(int idmod, int idprg, int idfb);
prog_t *prj_prgfind(int idmod, int idprg);
prog_t *prj_prgfind(int idmod, std::string prog_name);
mod_t *prj_modfind(int idmod);
mod_t *mod_modfind(std::string mod_name);

// int prj_img_size();
// int prj_to_img(prjimg_t *img);
// int prj_from_img(prjimg_t *pimg);

#endif
