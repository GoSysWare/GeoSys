#ifndef k_project_h
#define k_project_h
// #ifdef __cplusplus
// extern "C" {
// #endif

#include "k_config.h"
#include "k_program.h"
#include "k_io.h"

typedef struct PrjInfo{
        //char name[PRJNAMESIZE];
	char uuid[UUIDSIZE];
	int id_cmd;
	int id_stb;
	int stat;
	int peerlife;
	int imgsize;
	int zimgsize;
}prjinfo_t;

typedef struct PrjImg{
	prjinfo_t info;
	int bufsize;
	char imgbuf[IMAGSIZE];
}prjimg_t;


typedef struct PNode{
    struct PNode *p_prev;
    struct PNode *p_next;
    int id;
    std::string  name;
    prog_t *p_prg;
}pnode_t;


void *prj_main_loop(void* sth);

void prj_run();
void prj_stop();
void prj_init(int server);
void prj_uninit();
void prj_reset();
int prj_progadd(int id, char *name);
int prj_progremove(int id);
void prj_exec();
prjinfo_t *prj_info();
prjinfo_t *prj_info_p();

int prj_fbadd(int idprg, int id, char *libname, char *fcname, char *fbname);
int prj_fbremove(int idprg, int id);
int prj_lkadd(int idprg, int id, int fbsrc, int pinsrc, int fbtgt, int pintgt);
int prj_lkremove(int idprg, int id);
int prj_viadd(int idprg, int id, int idev, int idfb, int pin);
int prj_voadd(int idprg, int id, int idev, int idfb, int pin);
int prj_viremove(int idprg, int id);
int prj_voremove(int idprg, int id);
int prj_checkloop(int idprg, int idsrc, int idtgt);

pnode_t* prj_gethead();
void prj_dump();
int prj_prgdump(int idprg);
int prj_fbdump(int idprg, int idfb);

fb_t *prj_fbfind(int idprg, int idfb);
prog_t *prj_progfind(int idprg);
prog_t *prj_progfind(std::string prog_name);

int prj_img_size();
int prj_to_img(prjimg_t *img);
int prj_from_img(prjimg_t *pimg);

// #ifdef __cplusplus
// }
// #endif
#endif
