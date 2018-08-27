

#ifndef k_evbus_h
#define k_evbus_h

#include "k_datatype.h"
#include "k_evdata.h"

#ifdef __cplusplus
extern "C" {
#endif

#define EVMAGIC 0x52566662
#define EVDATAPORT 0

typedef struct TagValue{
	Int id;
	var_t v;
}tagvalue_t;

typedef struct EVFrame{
	Int magic;
	Int station;
	Int count;
	tagvalue_t val[];
}evframe_t;

typedef void (*evframeproc)(evframe_t *frm);

void evbus_init();
void evbus_uninit();
void evbus_hook(evframeproc proc);

//val_t *evbus_evfind(int id);
//int evbus_allocbool(int cid);
//int evbus_allocreal(int cid);
//int evbus_freebool(int i);
//int evbus_freereal(int i);
//void evbus_sendev();

#ifdef __cplusplus
}
#endif
#endif
