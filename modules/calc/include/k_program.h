/*****************************************************
 *   read this code to understand basic data stuct.
 *
******************************************************/

#ifndef k_program_h
#define k_program_h
// #ifdef __cplusplus
// extern "C" {
// #endif

#include "k_functionblock.h"

/* this kind of Node map to a fb or lk */
typedef struct ENode{
	struct ENode *p_prev{0};
	struct ENode *p_next{0};

	int id{0};
	/* function block */
	std::string fbname;
	fb_t *p_fb{0};
	/* link */
	int idsrc{0};
	struct ENode *p_ensrc{0};
	pin_t *p_vsrc{0};	/* source value */
	int idtgt{0};
	struct ENode *p_entgt{0};
	pin_t *p_vtgt{0};	/* target value */ 
	int rank{0};
	int mark{0};
} enode_t;

// prg的动态运行信息
typedef struct ProgramInfo{
	int status;
	unsigned int thread_id;
	u_int64_t begin_time;
	u_int64_t expend_time;
} proginfo_t;


typedef struct Program{
	enode_t en_head;
	enode_t *p_en_select;
} prog_t;

prog_t *prg_new();
void prg_delete(prog_t *p_prg);
int prg_fbadd(prog_t *p_prg, int id, const std::string & libname, const std::string & fcname, const std::string & fbname);
int prg_fbremove(prog_t *p_prg, int id);
int prg_lkadd(prog_t *p_prg, int id, int fbsrc, int pinsrc, int fbtgt, int pintgt);
int prg_lkremove(prog_t *p_prg, int id);
int prg_viadd(prog_t *p_prg, int idev, int idfb, int pin);
int prg_voadd(prog_t *p_prg, int idev, int idfb, int pin);

void prg_exec(prog_t *p_prg);
void prg_dump(prog_t *p_prg);
int prg_checkloop(prog_t *p_prg, int idSrc, int idTgt);

fb_t *prg_fbfind(prog_t *p_prg, int id);
fb_t *prg_fbfind_by_lib(prog_t *p_prg, std::string libname,std::string fcname);
// #ifdef __cplusplus
// }
// #endif
#endif
