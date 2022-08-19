/*****************************************************
 *   read this code to understand basic data stuct.
 *
******************************************************/

#ifndef k_task_h
#define k_task_h
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


typedef struct Program{
	pnode_t * prj;     //属于哪个proj
	vam_t   input;		// 异步任务/服务的请求参数
	vam_t   result;		// 异步任务/服务的返回参数
	int prog_type;     //程序类型  timer task service ...
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

// #ifdef __cplusplus
// }
// #endif
#endif
