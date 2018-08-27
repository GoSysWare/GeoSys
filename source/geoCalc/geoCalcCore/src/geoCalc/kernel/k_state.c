#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "k_process.h"
#include "k_config.h"
#include "k_state.h"
#include "k_io.h"
#include "stbbus.h"

//只有三种状态：unknown(状态0)；primary(状态1)；standby(状态2)
//三种状态的条件分别由以下四组条件决定：
//	stop/run
//	connect/disconnect
//	????	sync/async
//	IO collision/not collision

#define WAITA 5
#define WAITB 10
static int wait;

static void reset_wait()
{
	if(prj_info()->id_stb==0xa){
		wait=WAITA;
	}else if(prj_info()->id_stb==0xb){
		wait=WAITB;
	}else{
		wait=0;
	}
}

//主站状态
static void primary_phase()
{
	stbbus_sync_data();
}
static void primary2standby()
{
	prj_info()->stat=S_STANDBY;
}
static void primary2unknown()
{
	prj_info()->stat=S_UNKNOWN;
	reset_wait();
}

//备站状态
static void standby_phase()
{
}
static void standby2primary()
{
	prj_info()->stat=S_PRIMARY;
}

static void standby2unknown()
{
    prj_info()->stat=S_UNKNOWN;
    reset_wait();
}

//未知状态
static void unknown_phase()
{
	if(wait>0){
		wait--;
	}
}
static void unknown2primary()
{
	prj_info()->stat=S_PRIMARY;
}
static void unknown2standby()
{
	prj_info()->stat=S_STANDBY;
}

static int is_run()
{
#ifdef SIMULATOR
	return 1;
#else
	return 0;
#endif
}

static int is_sync()
{
	prjinfo_t *p1, *p2;

	p1=prj_info();
	p2=prj_info_p();
	if(memcmp(p1->uuid,p2->uuid,UUIDSIZE)!=0){
		return 0;
	}
	if(p1->id_cmd!=p2->id_cmd){
		return 0;
	}
	return 1;
}

static int get_peer_state()
{
	if(prj_info()->peerlife==0){
		prj_info_p()->stat=S_UNKNOWN;
	}

	return prj_info_p()->stat;
}

void state_decrease_peer_life()
{
	if(prj_info()->peerlife>0){
		prj_info()->peerlife--;
	}
}

void state_full_peer_life()
{
	prj_info()->peerlife=MAXPEERLIFE;
}

void state_init()
{
	prj_info()->peerlife = 0;
	reset_wait();
}

//以上共16种情况，组合为若干条件
//主站条件；
//备站条件；
//未知条件。

//主程序，不停扫描
void state_check()
{
	prjinfo_t *k,*p;
	k=prj_info();
	p=prj_info_p();
        //printf("kern id=%d sta=%d, uuid=%s, cmd=%d, plife=%d\n",k->id_stb,k->stat,k->uuid,k->id_cmd,k->peerlife);
        //printf("peer id=%d sta=%d, uuid=%s, cmd=%d, plife=%d\n",p->id_stb,p->stat,p->uuid,p->id_cmd,p->peerlife);

	switch(prj_info()->stat){
	case S_PRIMARY:
		if(!is_run()){
			primary2standby();
		}else if(get_peer_state()==S_PRIMARY){
			primary2unknown();
		}else{
			primary_phase();
		}
		break;
	case S_STANDBY:
		if(is_run() && is_sync() && (get_peer_state()!=S_PRIMARY)){
			standby2primary();
		}else{
			standby_phase();
		}
		break;
	default:
		if(!is_run() || get_peer_state()==S_PRIMARY){
			unknown2standby();	
		}else if(wait==0 || get_peer_state()==S_STANDBY){
			unknown2primary();
		}else{
			unknown_phase();
		}
	}	
}
