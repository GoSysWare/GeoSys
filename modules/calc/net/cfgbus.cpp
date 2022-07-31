#include <stdio.h>

#include "modules/calc/include/vnet.h"
#include "modules/calc/include/vtcp.h"
#include "modules/calc/include/cfgbus.h"
#include "modules/calc/include/stbbus.h"
#include "modules/calc/include/k_util.h"
#include "modules/calc/include/k_command.h"
#include "modules/calc/include/k_process.h"

#define FRMTIMEOUT 1000

static cfgframe_t frm_answer;
static cfgframe_t frm_send;
static rwlock_t *cfglock;

static void oncommand(int len, char *p)
{
	//printf("oncmds:%s\n", p);
	*(p+len-1)=0;
	if(cmds_dispatch(p)!=0){
		frm_answer.h.function |= FUNCFAIL;
	}else{
		cmds_append(p, len-1);
	}
	frm_answer.h.len=0;
}

static void onimg()
{
	prjimg_t *pimg=(prjimg_t*)frm_answer.d;

	prj_to_img(pimg);
	frm_answer.h.len=sizeof(prjimg_t)+pimg->bufsize;
}

static void onprjinfo()
{
	memcpy(frm_answer.d,prj_info(),sizeof(prjinfo_t));
	frm_answer.h.len=sizeof(prjinfo_t);
}

static void onreset()
{
	prj_reset();
	cmds_reset();
}

static void onrun()
{
	prj_run();
}

static void onstop()
{
        //printf("on stop\n");
	prj_stop();
}

static void onuploadcmds()
{
	frm_answer.h.len=cmds_load(frm_answer.d,MAXFRMDATASIZE);
}

/* server side functiong */
static void onserver(int income, int len, char *p)
{
	cfgframe_t *p_frm;

	if(len < sizeof(cfghead_t)){
		return;
	}
	
	p_frm = (cfgframe_t*)p;
	if(p_frm->h.magic != CFGMAGIC){
		return;
	}
	if(p_frm->h.len > (int)(len-sizeof(cfghead_t))){
		return;
	}

	frm_answer.h.magic = p_frm->h.magic;
	frm_answer.h.function = p_frm->h.function|FUNCACK;

	switch(p_frm->h.function){
	case FUNCCMD:
		stbbus_sync_prog(p_frm);
		oncommand(p_frm->h.len,p_frm->d);
		vtcp_srvsend(CONFIGPORT, income, sizeof(cfghead_t)+frm_answer.h.len, (char *)&frm_answer);
		break;
	case FUNCIMG:
		onimg();
		vtcp_srvsend(CONFIGPORT, income, sizeof(cfghead_t)+frm_answer.h.len, (char *)&frm_answer);
		break;
	case FUNCPRJINFO:
		onprjinfo();
		vtcp_srvsend(CONFIGPORT, income, sizeof(cfghead_t)+frm_answer.h.len, (char *)&frm_answer);
		break;
	case FUNCRESET:
		onreset();
		vtcp_srvsend(CONFIGPORT, income, sizeof(cfghead_t)+frm_answer.h.len, (char *)&frm_answer);
		break;
	case FUNCRUN:
		onrun();
		vtcp_srvsend(CONFIGPORT, income, sizeof(cfghead_t)+frm_answer.h.len, (char *)&frm_answer);
		break;
        case FUNCSTOP:
		onstop();
		vtcp_srvsend(CONFIGPORT, income, sizeof(cfghead_t)+frm_answer.h.len, (char *)&frm_answer);
		break;
	case FUNCUCMD:
		onuploadcmds();
		vtcp_srvsend(CONFIGPORT, income, sizeof(cfghead_t)+frm_answer.h.len, (char *)&frm_answer);
	default:
		;
	}
}

void cfgbus_init(int server)
{
	int res;

	cfglock = k_rwlock_create();

	if(server){
		res = vtcp_srvcreate(CONFIGPORT, onserver);
	}
    printf("tcp server for cfg start.\n");
}

void cfgbus_uninit()
{
	vtcp_srvclose(CONFIGPORT);

	//k_rwlock_destory(cfglock);
}

/* client side functiong */
static prjinfo_t info;
static char cmdsbuf[MAXFRMDATASIZE];
static int answer=ANSWERNO;

static void onclient(int income, int len, char *p)
{
	cfgframe_t *p_frm;
	
	if(len<sizeof(cfghead_t)){
		return;
	}
	
	p_frm=(cfgframe_t*)p;
	if(p_frm->h.magic!=CFGMAGIC){
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
		if((p_frm->h.function & 0x00ffffff)==FUNCIMG){                    
			prj_from_img((prjimg_t*)p_frm->d);
		}else if((p_frm->h.function & 0x00ffffff)==FUNCPRJINFO){
			memcpy(&info,p_frm->d,sizeof(prjinfo_t));
		}else if((p_frm->h.function & 0x00ffffff)==FUNCUCMD){
			memcpy(cmdsbuf,p_frm->d,p_frm->h.len);
			if(p_frm->h.len==0){
				cmdsbuf[0]=0;
			}else{
				cmdsbuf[p_frm->h.len]=0;
			}
		}

		answer=ANSWEROK;
	}
}

prjinfo_t *cfgbus_prjinfo()
{
	return &info;
}

char *cfgbus_cmdsbuf()
{
	return cmdsbuf;
}

int cfgbus_connect(char *srvaddr)
{
	return vtcp_cltcreate(CONFIGPORT, onclient, srvaddr);
}

#define SLEEPTIME 1
static int cfgbus_cltsend(cfgframe_t *p_frm)
{
	int i;
	
	answer = ANSWERNO;
	if(0==vtcp_cltsend(CONFIGPORT, p_frm->h.len+sizeof(cfghead_t), (char*)p_frm)){
		return answer;
	}
	for(i=0;i<FRMTIMEOUT/SLEEPTIME;i++){
		k_sleep(SLEEPTIME);
		if(answer != ANSWERNO){
			break;
		}
	}

	return answer;
}

int cfgbus_send(int fun, int len, char *p)
{
	int res;
	k_wlock(cfglock);
	frm_send.h.magic=CFGMAGIC;
	frm_send.h.function=fun;
	frm_send.h.len=len;
	memcpy(frm_send.d,p,len);
	res=cfgbus_cltsend(&frm_send);
	k_wunlock(cfglock);
	return res;
}

void cfgbus_disconnect()
{
	vtcp_cltclose(CONFIGPORT);
}
