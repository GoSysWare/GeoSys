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
	struct ENode *p_prev;
	struct ENode *p_next;

	int id;
	/* function block */
	char fbname[FBNAMESIZE];
	fb_t *p_fb;
	/* link */
	int idsrc;
	struct ENode *p_ensrc;
	pin_t *p_vsrc;	/* source value */
	int idtgt;
	struct ENode *p_entgt;
	pin_t *p_vtgt;	/* target value */ 
	int rank;
	int mark;
} enode_t;

/* VNode map a variable to a fb pin */
typedef struct VNode{
	struct VNode *p_prev;
	struct VNode *p_next;
	int id;
	int idev;
	int idfb;
    pin_t *p_pin;//引脚值，参与功能块计算
    val_t *p_val;//临时值，保存初始值或输出值
	int mark;
} vnode_t;

typedef struct Program{
	enode_t en_head;
	vnode_t vnin_head;
	vnode_t vnout_head;
	enode_t *p_en_select;
	vnode_t *p_vnin_select;
	vnode_t *p_vnout_select;
} prog_t;

prog_t *prg_new();
void prg_delete(prog_t *p_prg);
int prg_fbadd(prog_t *p_prg, int id, char *libname, char *fcname, char *fbname);
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
