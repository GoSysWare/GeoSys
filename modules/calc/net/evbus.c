#include <assert.h>
#include <stdlib.h>
#include "vnet.h"
#include "vudp.h"
#include "evbus.h"

static evframeproc on_evframe=NULL;

void evbus_init()
{
	vudp_init();
}

void evbus_uninit()
{

}

static void on_udpdata(int len, char *data)
{
	evframe_t *p_frm;
	
	if(len<sizeof(evframe_t)){
		return;
	}
	p_frm=(evframe_t*)data;

	if(p_frm->magic != EVMAGIC){
		return;
	}

	if((unsigned int)len != (p_frm->count*sizeof(tagvalue_t)+sizeof(evframe_t))){
		return;
	}

	on_evframe(p_frm);
}

void evbus_hook(evframeproc proc)
{
	on_evframe=proc;
	vudp_hook(EVDATAPORT, on_udpdata);
}
