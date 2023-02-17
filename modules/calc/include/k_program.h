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


/* VNode map a variable to a fb pin */
typedef struct VNode{
	struct VNode *p_prev;
	struct VNode *p_next;
	int id;
	int idev;
	int idfb;
    pin_t *p_pin;//引脚值，参与功能块计算
    vam_t *p_val;//临时值，保存初始值或输出值
	int mark;
} vnode_t;

/*  
* Perioid Time  定时器耗时 
* T1 功能块1耗时
* T2 功能块2耗时
* T3 功能块3耗时
*   Perioid Time   T1    T2    T3  Perioid Time   T1    T2    T3  Perioid Time   T1    T2    T3
* |---------------|----|-----|---|---------------|----|-----|---|---------------|----|-----|---|
*				  |
* 				  |begin_time
*				  |      |
*				  |		 |		
*				  |------|escaped_time	
*				  |              |
*				  |              |
*				  |--------------|expend_time
*				  |								 |
*				  |								 |
*				  |------------------------------|cycle_time
*/

// prg的动态运行信息
typedef struct ProgramInfo{
	int status;					// 状态
	unsigned int thread_id;  	// 线程id
	u_int64_t prev_time;		// 上次开始执行时间 = begin_time
	u_int64_t cycle_time;		// 上次执行周期总时长 = timer + expend_time = begin_time - prev_time
	u_int64_t begin_time;		// 本次开始执行时间 = now
	u_int64_t escaped_time;		// 已执行时间      = now - begin_time
	u_int64_t expend_time;		// 任务执行消耗时长 = T1 + T2 + T3
} proginfo_t;


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
int prg_fbadd(prog_t *p_prg, int id, const std::string & libname, const std::string & fcname, const std::string & fbname);
int prg_fbremove(prog_t *p_prg, int id);
int prg_lkadd(prog_t *p_prg, int id, int fbsrc, int pinsrc, int fbtgt, int pintgt);
int prg_lkremove(prog_t *p_prg, int id);
int prg_viadd(prog_t *p_prg, int idev, int idfb, int pin);
int prg_viremove(prog_t *p_prg, int idfb, int pin);
int prg_voadd(prog_t *p_prg, int idev, int idfb, int pin);
int prg_voremove(prog_t *p_prg, int idfb, int pin);

void prg_exec(prog_t *p_prg, proginfo_t * p_prog_info);
void prg_dump(prog_t *p_prg);
int prg_checkloop(prog_t *p_prg, int idSrc, int idTgt);

fb_t *prg_fbfind(prog_t *p_prg, int id);
fb_t *prg_fbfind_by_lib(prog_t *p_prg, std::string libname,std::string fcname);
// #ifdef __cplusplus
// }
// #endif
#endif
