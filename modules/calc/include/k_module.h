#ifndef k_module_h
#define k_module_h
// #ifdef __cplusplus
// extern "C" {
// #endif

#include "k_config.h"
#include "k_program.h"
#include "k_io.h"

typedef struct ModInfo{
	std::string uuid;
	int id_cmd;
	int id_stb;
	int stat;
	int peerlife;
	int imgsize;
	int zimgsize;
}modinfo_t;


typedef struct MNode{
    struct MNode *p_prev;
    struct MNode *p_next;
    int id;
    std::string  name;
    int type;
    bool enable;
    uint64_t period;
    std::vector<std::string> topic;
    proginfo_t info;
    prog_t *p_prg;
}mnode_t;

typedef struct Module{
	mnode_t mn_head;
	mnode_t *p_mn_select;
}mod_t;

void *mod_main_loop(void* sth);

void mod_run(mod_t *p_mod);
void mod_stop(mod_t *p_mod);
void mod_init(mod_t *p_mod);
void mod_uninit(mod_t *p_mod);
void mod_reset(mod_t *p_mod);

mod_t *mod_new();
void mod_delete(mod_t *p_mod);

int mod_prgadd(mod_t *p_mod,int id, std::string name);
int mod_prgremove(mod_t *p_mod,int id);
void mod_exec(mod_t *p_mod);
modinfo_t *mod_info(mod_t *p_mod);
modinfo_t *mod_info_p(mod_t *p_mod);

int mod_fbadd(mod_t *p_mod,int idprg, int id, char *libname, char *fcname, char *fbname);
int mod_fbremove(mod_t *p_mod,int idprg, int id);
int mod_lkadd(mod_t *p_mod,int idprg, int id, int fbsrc, int pinsrc, int fbtgt, int pintgt);
int mod_lkremove(mod_t *p_mod,int idprg, int id);

int mod_checkloop(mod_t *p_mod,int idprg, int idsrc, int idtgt);

void mod_dump(mod_t *p_mod);
int mod_prgdump(mod_t *p_mod,int idprg);
int mod_fbdump(mod_t *p_mod,int idprg, int idfb);

fb_t *mod_fbfind(mod_t *p_mod,int idprg, int idfb);
prog_t *mod_prgfind(mod_t *p_mod,int idprg);
prog_t *mod_prgfind(mod_t *p_mod,std::string prog_name);




#endif
