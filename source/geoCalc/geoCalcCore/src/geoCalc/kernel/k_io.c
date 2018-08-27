#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include "k_io.h"
#include "k_util.h"
#include "k_compress.h"
#include "k_config.h"
#include "k_process.h"
#include "k_project.h"
#include "k_state.h"
#include "cfgbus.h"

#ifdef IONETUDP
#define IOPORT 7
#define IOMASK 8
#include "vudp.h"
#endif

#define IOFRMTIMEOUT 20
#ifdef _WIN32
	#define SLEEPTIME 10
#elif defined(_LINUX)
	#define SLEEPTIME 1
#endif

#define IOMAGIC (MAGICBASE+10)
#define FUNCIOINFO 0x11
#define FUNCIOREAD 0x12
#define FUNCIOWRITE	0x13

typedef struct IOHead{
	Int magic;
	Int id;
	Int function;
	Int src;
	Int tgt;
	Int len;
}iohead_t;

#define MAXIOFRMEDATASIZE 1024

typedef struct IOFrame{
	iohead_t h;
	char d[MAXIOFRMEDATASIZE];
}ioframe_t;

static iostation_t ios[IOSTATIONCOUNT];
static int ioack = 0;

static int sendframe(ioframe_t *frm)
{
	frm->h.magic = IOMAGIC;
	frm->h.id++;

#ifdef IONETUDP
        if(vudp_send(IOPORT, (char*)frm, frm->h.len+sizeof(iohead_t)) != 0){
		return -1;
	}else{
		return 0;
	}
#else
	return -1;
#endif
}

static void oninfo(ioframe_t *f)
{
	ioframe_t frm;

	frm.h.tgt = f->h.src;
	frm.h.src = f->h.tgt;
	frm.h.function = f->h.function|FUNCACK;
	frm.h.len = sizeof(prjinfo_t);
	memcpy(frm.d, prj_info(), sizeof(prjinfo_t));
	sendframe(&frm);
}

static void onackinfo(ioframe_t *f)
{
	//printf("onackinfo!\n");
	memcpy(prj_info_p(), f->d, sizeof(prjinfo_t));
	state_full_peer_life();
}

static void onackioread(ioframe_t *f)
{
	if(f->h.tgt==prj_info()->id_stb*0x10){
		if(f->h.src<0 || f->h.src>=IOSTATIONCOUNT){
			return;
		}
		
		//printf("READ!! onackio, id is %d\n\n", f->h.src);	

		ioack=1;
		memcpy(ios[f->h.src].in, f->d, sizeof(iocell_t)*IOCELLCOUNT);
		ios[f->h.src].h.rf = IORETRYTIME;
		ios[f->h.src].h.rcs++;
	}
}

static void onackiowrite(ioframe_t *f)
{
	if(f->h.tgt == prj_info()->id_stb*0x10){
		if(f->h.src<0 || f->h.src>=IOSTATIONCOUNT){
			return;
		}
		
		//printf("WRITE!! onackio, id is %d\n\n", f->h.src);
		
		memcpy(ios[f->h.src].in, f->d, sizeof(iocell_t)*IOCELLCOUNT);

		ioack = 1;
		ios[f->h.src].h.wcs++;
	}
}

static void oniodata(int len, char *p)
{
	ioframe_t *f;

	//printf("onudpdata ok\n");

	if(len < sizeof(iohead_t)){
		return;
	}
	f = (ioframe_t*)p;
	
	//test
	if((f->h.function == (FUNCIOREAD|FUNCACK)) || (f->h.function == (FUNCIOWRITE|FUNCACK))){
		//printf("src is %d, tgt is %d, function is %d, length is %d\n", f->h.src, f->h.tgt, f->h.function, f->h.len);
	}

	if(prj_info()->id_stb*16 != f->h.tgt){
		return;
	}
	
	if((f->h.len + (int)sizeof(iohead_t)) != len){
		return;
	}
	if(f->h.magic != IOMAGIC){
		return;
	}
	
	//printf("iodata ok!\n");	
	
	if(f->h.function & FUNCACK){
		switch(f->h.function & 0x00ffffff){
			case FUNCIOINFO:
				onackinfo(f);
				break;
			case FUNCIOREAD:
				onackioread(f);
				break;
			case FUNCIOWRITE:
				onackiowrite(f);
				break;
			default:
				;
		}
	}else{
		switch(f->h.function){
			case FUNCIOINFO:
				oninfo(f);
				break;
			default:
				;
		}
	}
}

static void io_peer_thread(void *p)
{
	ioframe_t frmsend;
	frmsend.h.function = FUNCIOINFO;
	if(prj_info()->id_stb == 0xa){
		frmsend.h.src = 0xa0;
		frmsend.h.tgt = 0xb0;
	}else{
		frmsend.h.src = 0xb0;
		frmsend.h.tgt = 0xa0;
	}
	frmsend.h.len = 0;
	while(1){
		k_sleep(PEERPOLLTIME);
		state_decrease_peer_life();
		sendframe(&frmsend);
		//printf("send io_peer data OK!\n");
	}
}

void io_init()
{
#ifdef IONETUDP
	int res;
	
	vudp_set_mask(IOPORT, IOMASK);
	vudp_set_loop(IOPORT, 0);

        res = vudp_hook(IOPORT, oniodata);
        //printf("udp_hook return %d\n", res);
#endif
	
	memset(ios, 0, sizeof(ios));

	if(prj_info()->id_stb == 0xa || prj_info()->id_stb == 0xb){
        k_thread_start(io_peer_thread, 0);
        printf("io_peer_thread start.\n");
	}
}

void io_input()
{
	static int pp=0;
	int i, j;

	//test	
	int time;
	
	ioframe_t frm;
	frm.h.len = 0;
	frm.h.function = FUNCIOREAD;

	// read rf!=0
	for(i=0; i<IOSTATIONCOUNT; i++){
		if(ios[i].h.rf != 0){
			frm.h.src = prj_info()->id_stb*0x10;
			frm.h.tgt = i;
			
			if(ios[i].h.rf > 0){
				ios[i].h.rf--;
			}
			
			ios[i].h.rc++;
			if(ios[i].h.rc == 0){
				ios[i].h.rcs = 0;
			}
			
			ioack = 0;
			sendframe(&frm);
			
			k_clk_init();
			
			for(j=0; j<IOTIMEOUT; j++){
				//k_clk_init();
				k_sleep(1);
				//k_clk_do();
				//time = clk_cycle_ms();
				//printf("Station:%d -- j is %d, time is %d ms", i, j, time);
				//printf(", ioack is %d\n", ioack);

				if(ioack != 0){
					k_clk_do();
					time = clk_cycle_ms();
                                        //printf("Station:%d -- j is %d, time is %d ms, ioack is %d, ", i, j, time, ioack);
                                        //printf("rcs is %d, rc is %d, rate is %f\n",ios[i].h.rcs,ios[i].h.rc,(float)ios[i].h.rcs/(float)ios[i].h.rc);
					break;
				}
			}
		}
	}

        // read rf==0
        pp = (pp+1)%IOSTATIONCOUNT;
        if(ios[pp].h.rf == 0){
                frm.h.src = prj_info()->id_stb*0x10;
                frm.h.tgt = pp;

                ios[pp].h.rc++;
                if(ios[pp].h.rc == 0){
                        ios[pp].h.rcs = 0;
                }

                ioack = 0;
                sendframe(&frm);
                for(j=0; j<IOTIMEOUT; j++){
                        k_sleep(1);
                        if(ioack != 0){
                                break;
                        }
                }
        }

	//printf("send ask_input OK!\n");	
}

void io_output()
{
	int i,j;
	ioframe_t frm;
	frm.h.len = sizeof(iocell_t)*IOCELLCOUNT;
	frm.h.function = FUNCIOWRITE;

	for(i=0; i<IOSTATIONCOUNT; i++){
		if(ios[i].h.wf != 0){
			ios[i].h.wf = 0;

			frm.h.src = prj_info()->id_stb*0x10;
			frm.h.tgt = i;
			memcpy(frm.d, ios[i].out, sizeof(iocell_t)*IOCELLCOUNT);			
			ios[i].h.wc++;
			if(ios[i].h.wc == 0){
				ios[i].h.wcs = 0;
			}
			ioack = 0;
            sendframe(&frm);
			for(j=0; j<IOTIMEOUT; j++){
				k_sleep(1);
				if(ioack != 0){
					break;
				}
			}
		}
	}
}

iostation_t *io_getstation(int s)
{
	if(s < 0 || s >= IOSTATIONCOUNT){
		return NULL;
	}
	return &ios[s];
}

iocell_t *io_getcellin(int s, int c)
{
	if(s < 0 || s >= IOSTATIONCOUNT){
		return NULL;
	}
	if(c < 0 || c >= IOCELLCOUNT){
		return NULL;
	}

	return &ios[s].in[c];
}

iocell_t *io_getcellout(int s, int c)
{
	if(s < 0 || s >= IOSTATIONCOUNT){
		return NULL;
	}
	if(c < 0 || c >= IOCELLCOUNT){
		return NULL;
	}

	return &ios[s].out[c];
}

/*
	value[0]=0;
	for(i=0,pval=(char*)cell;i<sizeof(iocell_t);i++,pval++){
		*pval=0xff;
		sprintf(word,"%4x",*pval);
		pval++;
		strcat(value,word);
		//strcat(value,",");
	}
	printf("%s\n",value);
	fflush(stdout);
*/

static void char2str(unsigned char *c, char *str)
{
	switch((*c>>4) & 0x0f){
	case 0x00:
		*str='0';
		break;
	case 0x01:
		*str='1';
		break;
	case 0x02:
		*str='2';
		break;
	case 0x03:
		*str='3';
		break;
	case 0x04:
		*str='4';
		break;
	case 0x05:
		*str='5';
		break;
	case 0x06:
		*str='6';
		break;
	case 0x07:
		*str='7';
		break;
	case 0x08:
		*str='8';
		break;
	case 0x09:
		*str='9';
		break;
	case 0x0a:
		*str='A';
		break;
	case 0x0b:
		*str='B';
		break;
	case 0x0c:
		*str='C';
		break;
	case 0x0d:
		*str='D';
		break;
	case 0x0e:
		*str='E';
		break;
	case 0x0f:
		*str='F';
		break;
	}

	str++;
	switch(*c & 0x0f){
	case 0x00:
		*str='0';
		break;
	case 0x01:
		*str='1';
		break;
	case 0x02:
		*str='2';
		break;
	case 0x03:
		*str='3';
		break;
	case 0x04:
		*str='4';
		break;
	case 0x05:
		*str='5';
		break;
	case 0x06:
		*str='6';
		break;
	case 0x07:
		*str='7';
		break;
	case 0x08:
		*str='8';
		break;
	case 0x09:
		*str='9';
		break;
	case 0x0a:
		*str='A';
		break;
	case 0x0b:
		*str='B';
		break;
	case 0x0c:
		*str='C';
		break;
	case 0x0d:
		*str='D';
		break;
	case 0x0e:
		*str='E';
		break;
	case 0x0f:
		*str='F';
		break;
	}
}

static void str2char(unsigned char *c, char *str)
{
	char t;
	switch(*str){
	case '0':
		t=0x00;
		break;
	case '1':
		t=0x01;
		break;
	case '2':
		t=0x02;
		break;
	case '3':
		t=0x03;
		break;
	case '4':
		t=0x04;
		break;
	case '5':
		t=0x05;
		break;
	case '6':
		t=0x06;
		break;
	case '7':
		t=0x07;
		break;
	case '8':
		t=0x08;
		break;
	case '9':
		t=0x09;
		break;
	case 'a':
	case 'A':
		t=0x0a;
		break;
	case 'b':
	case 'B':
		t=0x0b;
		break;
	case 'c':
	case 'C':
		t=0x0c;
		break;
	case 'd':
	case 'D':
		t=0x0d;
		break;
	case 'e':
	case 'E':
		t=0x0e;
		break;
	case 'f':
	case 'F':
		t=0x0f;
		break;
	}
	*c = t<<4;
	str++;
	switch(*str){
	case '0':
		t=0x00;
		break;
	case '1':
		t=0x01;
		break;
	case '2':
		t=0x02;
		break;
	case '3':
		t=0x03;
		break;
	case '4':
		t=0x04;
		break;
	case '5':
		t=0x05;
		break;
	case '6':
		t=0x06;
		break;
	case '7':
		t=0x07;
		break;
	case '8':
		t=0x08;
		break;
	case '9':
		t=0x09;
		break;
	case 'a':
	case 'A':
		t=0x0a;
		break;
	case 'b':
	case 'B':
		t=0x0b;
		break;
	case 'c':
	case 'C':
		t=0x0c;
		break;
	case 'd':
	case 'D':
		t=0x0d;
		break;
	case 'e':
	case 'E':
		t=0x0e;
		break;
	case 'f':
	case 'F':
		t=0x0f;
		break;
	}
	*c = *c + t;
}

void cell2str(iocell_t *cell, char *str)
{
	int i;
        unsigned char *pc = (unsigned char*)cell;
	for(i=0; i < sizeof(iocell_t); i++){
		char2str(pc, str);
		pc++;
		str+=2;
	}
	*str=0;
}

void str2cell(iocell_t *cell, char *str)
{
	int i;
        unsigned char *pc=(unsigned char*)cell;
	for(i=0;i<sizeof(iocell_t);i++){
		str2char(pc,str);
		pc++;
		str+=2;
	}
}

void word_invert(Word *w)
{
	unsigned char h,l;
	
	h = (*w & 0xff00) >> 8;
	l = *w & 0xff;

	*w = (l << 8) + h;
}

char *io_to_img(char *buf)
{
	int i,j;
	for(i=0;i<IOSTATIONCOUNT;i++){
		memcpy(buf,&ios[i].h,sizeof(shead_t));
		buf+=sizeof(shead_t);
		for(j=0;j<IOCELLCOUNT;j++){
			buf+=cmps_zcell(&ios[i].in[j],buf);
			buf+=cmps_zcell(&ios[i].out[j],buf);
		}
	}
	return buf;
}

char *io_from_img(char *buf)
{
	int i,j;

	for(i=0;i<IOSTATIONCOUNT;i++){
		memcpy(&ios[i].h,buf,sizeof(shead_t));
		buf+=sizeof(shead_t);
		for(j=0;j<IOCELLCOUNT;j++){
			buf+=cmps_uzcell(buf,&ios[i].in[j]);
			buf+=cmps_uzcell(buf,&ios[i].out[j]);
		}
	}
	return buf;
}

