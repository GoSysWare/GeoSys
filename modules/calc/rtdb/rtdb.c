#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "modules/calc/include/evbus.h" 
#include "modules/calc/include/k_util.h"
#include "modules/calc/include/k_evdata.h"
#include "station.h"
#include "rtdb.h"
#define STATIONCOUNT 256
static station_t stations[STATIONCOUNT];

static void rtdb_ondata(evframe_t *frm)
{
	int i;
	tag_t *ptag;

	if(frm->station<0 || frm->station>=STATIONCOUNT){
		return;
	}
	
	for(i=0;i<frm->count;i++){
		ptag=sta_findtag(&stations[frm->station],frm->val[i].id);
		if(ptag!=NULL){
			ptag->val=frm->val[i].v;
		}
	}
}

int rtdb_init()
{
	int i;
	
	for(i=0;i<STATIONCOUNT;i++){
		sta_init(&stations[i]);
	}

	evbus_init();
	evbus_hook(rtdb_ondata);

	return 0;
}

void rtdb_uninit()
{
	int i;
	
	for(i=0;i<STATIONCOUNT;i++){
		sta_uninit(&stations[i]);
	}

	evbus_uninit();
}

void rtdb_loadcfg()
{	
	int i;
	for(i=0;i<STATIONCOUNT;i++){
		sta_loadcfg(i,&stations[i]);
	}
}

void rtdb_savecfg()
{
	int i;
	for(i=0;i<STATIONCOUNT;i++){
		sta_savecfg(i,&stations[i]);
	}
}
