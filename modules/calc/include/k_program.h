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

#pragma  pack (push,1)   
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

/* VNode map a variable to a fb pin */
typedef struct VNode{
	struct VNode *p_prev{0};
	struct VNode *p_next{0};
	int id{0};
	int idev{0};
	int idfb{0};
    pin_t *p_pin{0};//引脚值，参与功能块计算
    vam_t *p_val{0};//临时值，保存初始值或输出值
	int mark{0};
} vnode_t;

typedef struct Program{
	enode_t en_head;
	vnode_t vnin_head;
	vnode_t vnout_head;
	enode_t *p_en_select;
	vnode_t *p_vnin_select;
	vnode_t *p_vnout_select;
} prog_t;
#pragma pack(pop) 

prog_t *prg_new();
void prg_delete(prog_t *p_prg);
int prg_fbadd(prog_t *p_prg, int id, const std::string & libname, const std::string & fcname, const std::string & fbname);
int prg_fbremove(prog_t *p_prg, int id);
int prg_lkadd(prog_t *p_prg, int id, int fbsrc, int pinsrc, int fbtgt, int pintgt);
int prg_lkremove(prog_t *p_prg, int id);
int prg_viadd(prog_t *p_prg, int id, int idev, int idfb, int pin);
int prg_voadd(prog_t *p_prg, int id, int idev, int idfb, int pin);
int prg_viremove(prog_t *p_prg, int id);
int prg_voremove(prog_t *p_prg, int id);
void prg_exec(prog_t *p_prg);
void prg_dump(prog_t *p_prg);
int prg_checkloop(prog_t *p_prg, int idSrc, int idTgt);

fb_t *prg_fbfind(prog_t *p_prg, int id);

// #ifdef __cplusplus
// }
// #endif
#endif
