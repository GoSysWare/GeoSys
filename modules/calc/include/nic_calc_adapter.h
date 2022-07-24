#ifndef NIC_CALC_ADAPTER_H
#define NIC_CALC_ADAPTER_H

#include "precomp.h"
#include "nic_calc_tag.h"
#include <map>
using namespace std;
//ACE_Task拥有一个svc线程，并且有一个消息队列，可以把服务器收到的消息存入消息队列中。
//两个线程之间的数据交互依赖消息队列
class CalcAdapter : public ACE_Task<ACE_MT_SYNCH>
{
public:
    CalcAdapter();
    virtual ~CalcAdapter();

public:
    virtual nicInt32 open (nicVoid *args = 0);
    virtual nicInt32 close (nicUInt32 flags = 0);
    virtual nicInt32 handle_timeout(const ACE_Time_Value &current_time, const void *act=0);

    nicInt32 putMsgQueueEx(ACE_Message_Block *msg);

    nicInt32 add_tag(nicUInt32 pnNewTagId, nicIN nicPropValueList* propValueList);
    nicInt32 RegNotifyFuncRealData(CalcResultNotifyFunc func);

//    void IO_Loop(void* sth);

private:
    //此线程用来收取实时库传送过来的数据
    virtual nicInt32 svc();

public:
    ACE_RW_Thread_Mutex  idMutex_;
    ACE_Event *pStopHandle_;
    CalcResultNotifyFunc resultFunc_;
    CALCTag* calcTag;
private:
    bool bIsStarted;
    ACE_thread_t thr_id_for_refleshID;
    ACE_thread_t thr_id_for_notify;


};



#endif // NIC_CALC_ADAPTER_H
