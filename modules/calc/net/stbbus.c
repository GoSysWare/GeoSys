#include <stdio.h>
#include "modules/calc/include/vnet.h"
#include "modules/calc/include/vtcp.h"
#include "modules/calc/include/stbbus.h"
#include "modules/calc/include/k_project.h"
#include "modules/calc/include/k_state.h"
#include "modules/calc/include/k_util.h"
#include "modules/calc/include/k_process.h"
#include "modules/calc/include/k_command.h"

#define FRMTIMEOUT 1000
#ifdef _WIN32
	#define SLEEPTIME 10
#elif defined(_LINUX)
	#define SLEEPTIME 1
#endif

static cfgframe_t stbfrm_answer;
static cfgframe_t stbfrm_send;
static int connected;
static int answer;

static void onstbinfo()
{
	memcpy(stbfrm_answer.d,prj_info(),sizeof(prjinfo_t));
	stbfrm_answer.h.len=sizeof(prjinfo_t);
}

static void onstbimg(char *p)
{
	prj_from_img((prjimg_t*)p);
	stbfrm_answer.h.len=0;
}

static void onstbcmd(int len, char *p)
{
	*(p+len-1)=0;
	if(cmds_dispatch(p)!=0){
		stbfrm_answer.h.function |= FUNCFAIL;
	}else{
		cmds_append(p,len-1);
	}
	stbfrm_answer.h.len=0;
}

/* server side functiong */
static void stb_onserver(int income, int len, char *p)
{
	cfgframe_t *p_frm;

	if(len < sizeof(cfghead_t)){
		return;
	}
	
	p_frm = (cfgframe_t*)p;
	if(p_frm->h.magic != STBMAGIC){
		return;
	}
	if(p_frm->h.len > (int)(len-sizeof(cfghead_t))){
		return;
	}

	stbfrm_answer.h.magic = p_frm->h.magic;
	stbfrm_answer.h.function = p_frm->h.function|FUNCACK;

	switch(p_frm->h.function){
	case FUNCSTBIMG:
		onstbimg(p_frm->d);
		vtcp_srvsend(STANDBYPORT, income, sizeof(cfghead_t)+stbfrm_answer.h.len, (char *)&stbfrm_answer);
		break;
	case FUNCSTBINFO:
		onstbinfo();
		vtcp_srvsend(STANDBYPORT, income, sizeof(cfghead_t)+stbfrm_answer.h.len, (char *)&stbfrm_answer);
		break;
	case FUNCSTBCMD:
		onstbcmd(p_frm->h.len,p_frm->d);
		vtcp_srvsend(STANDBYPORT, income, sizeof(cfghead_t)+stbfrm_answer.h.len, (char *)&stbfrm_answer);
		break;
	default:
		;
	}	
}

static int stbbus_cltsend(cfgframe_t *p_frm)
{
	int i;
	
	answer = ANSWERNO;
	if(0 == vtcp_cltsend(STANDBYPORT, p_frm->h.len+sizeof(cfghead_t), (char*)p_frm)){
		return answer;
	}
	for(i=0; i<FRMTIMEOUT/SLEEPTIME; i++){
		k_sleep(SLEEPTIME);
		if(answer != ANSWERNO){
			break;
		}
	}

	return answer;
}

static int send_info()
{
	stbfrm_send.h.len = 0;
	stbfrm_send.h.function = FUNCSTBINFO;
	stbfrm_send.h.magic = STBMAGIC;
	return stbbus_cltsend(&stbfrm_send);
}

static int send_img()
{
	prjimg_t *pimg=(prjimg_t*)stbfrm_send.d;
	prj_to_img(pimg);
	stbfrm_send.h.len=sizeof(prjimg_t)+pimg->bufsize;
	stbfrm_send.h.function=FUNCSTBIMG;
	stbfrm_send.h.magic=STBMAGIC;
	return stbbus_cltsend(&stbfrm_send);
}

static void onclient(int income, int len, char *p)
{
	cfgframe_t *p_frm;
	
	if(len<sizeof(cfghead_t)){
		return;
	}
	
	p_frm=(cfgframe_t*)p;
	if(p_frm->h.magic!=STBMAGIC){
		return;
	}
	if(p_frm->h.len>(int)(len-sizeof(cfghead_t))){
		return;
	}
	
	if(p_frm->h.function & FUNCFAIL){
		answer=ANSWERFAIL;
		return;
	}

	if(p_frm->h.function & FUNCACK){		
		if((p_frm->h.function & 0x00ffffff)==FUNCSTBINFO){
			memcpy(prj_info_p(),p_frm->d,sizeof(prjinfo_t));
			state_full_peer_life();
		}
		answer=ANSWEROK;
	}
}

static void stb_connect()
{
	int res;

	//printf("connecting...\n");

	if(prj_info()->id_stb==0xa){
		res=vtcp_cltcreate(STANDBYPORT, onclient, IPB);
	}else if(prj_info()->id_stb==0xb){
		res=vtcp_cltcreate(STANDBYPORT, onclient, IPA);
	}

	if(res==0){
		printf("connect succeed.\n");
		connected=1;
	}else{
		printf("connect failed.\n");
		connected=0;
	}
}

static void stb_disconnect()
{
	vtcp_cltclose(STANDBYPORT);

	connected=0;
}

static void standby_thread(void *p)
{
	int answer;

	while(1){
		state_decrease_peer_life();
		if(connected == 0){
			stb_connect();
		}else{
			answer = send_info();
			//printf("answer=%d\n",answer);
			if(answer != ANSWEROK){
				//printf("answer fail!\n");
				stb_disconnect();
			}
		}

		k_sleep(STBPOLLTIME);
	}
}

void stbbus_init()
{
	connected=0;

	if(prj_info()->id_stb!=0xa && prj_info()->id_stb!=0xb){
		return;
	}

	//cfglock=k_rwlock_create();
	if(0 == vtcp_srvcreate(STANDBYPORT, stb_onserver)){
		k_thread_start(standby_thread, 0);
	}
}

void stbbus_uninit()
{
	vtcp_srvclose(STANDBYPORT);

	//k_rwlock_destory(cfglock);
}

void stbbus_sync_data()
{
	if(connected){
		if(prj_info()->stat!=S_PRIMARY && prj_info_p()->stat!=S_STANDBY){
			return;
		}
		if(memcmp(prj_info()->uuid,prj_info_p()->uuid,UUIDSIZE)!=0){
			return;
		}
		if(prj_info()->id_cmd!=prj_info_p()->id_cmd){
			return;
		}
		if(send_img()!=ANSWEROK){
			stb_disconnect();
		}	
	}
}

void stbbus_sync_prog(cfgframe_t *p_frm)
{
	if(connected){
		//printf("ks=%d, ps=%d\n",prj_info()->stat,prj_info_p()->stat);
		if(prj_info()->stat==S_PRIMARY && prj_info_p()->stat==S_STANDBY){
			p_frm->h.function=FUNCSTBCMD;
			p_frm->h.magic=STBMAGIC;
			if(stbbus_cltsend(p_frm)!=ANSWEROK){
				stb_disconnect();
			}
		}
	}
}
