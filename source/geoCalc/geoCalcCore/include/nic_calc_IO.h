
/*
 * 此段代码主要用于衔接外部通信数据与内部计算数据的交互和缓冲。
 *  在代码表现上，分别使用nicsys数据类型和此内核数据类型，代码平台无关且不使用ACE
*/

#ifndef NIC_CALC_IO_H
#define NIC_CALC_IO_H

#include "nicDefs.h"
#include "k_evdata.h"

#ifdef __cplusplus
extern "C" {
#endif
typedef struct TagNode{
    struct TagNode *p_prev;
    struct TagNode *p_next;
    int idev;//作为key
    int idex;
    char name[32];
} TagNode_t;

typedef struct TagIONode{
    struct TagNode *p_prev;
    struct TagNode *p_next;
    int idio;//作为key
    int idev;
    val_t v;
} TagIONode_t;

int tag_ev_add(int idev, char* name);
int tag_ev_rm(int idev);
void tag_ev_reset();

int tag_set_idex(int idev, int idex);
int tag_get_idex(int idev, int* idex);
int tag_get_idev(int idex, int* idev);
TagNode_t* tag_gethead();


int tag_in_add(int idio, int idev);
int tag_in_rm(int idio);
void tag_in_reset();
TagIONode_t* tag_get_inhead();

int tag_out_add(int idio, int idev);
int tag_out_rm(int idio);
void tag_out_reset();
TagIONode_t* tag_get_outhead();

//数据从实时库到输入暂存区
void calc_io_pre_in(nicRealDataList *realList);

//数据从输入暂存区到赋值到vin
void calc_io_input();

//数据从vout到输出暂存区
void calc_io_output();

//数据从输出暂存区到发送
void calc_io_after_out(nicRealDataList* realList);

#ifdef __cplusplus
}
#endif
#endif // NIC_CALC_IO_H
