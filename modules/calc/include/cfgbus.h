#ifndef cfgbus_h
#define cfgbus_h
// #ifdef __cplusplus
// extern "C" {
// #endif

#include "k_config.h"
#include "k_evdata.h"
#include "k_project.h"

#define CFGMAGIC	MAGICBASE
#define CONFIGPORT	0
#define FUNCOK		0x00000000
#define FUNCFAIL	0x80000000
#define FUNCACK		0x10000000
#define FUNCCMD		0x01
#define FUNCIMG		0x02
#define FUNCPRJINFO	0x03
#define FUNCRESET	0x04
#define FUNCRUN		0x05
#define FUNCSTOP	0x06
#define FUNCUCMD	0x07

typedef struct CFGHead{
	Int magic;
	Int function;
	Int len;
}cfghead_t;

#define ANSWEROK 0
#define ANSWERNO -1
#define ANSWERFAIL -2

#define MAXFRMDATASIZE (TCPBUFSIZE-sizeof(cfghead_t))
typedef struct CFGFrame{
	cfghead_t h;
	char d[MAXFRMDATASIZE];
}cfgframe_t;

void cfgbus_init(int server);
void cfgbus_uninit();
int cfgbus_connect(char *srvaddr);
void cfgbus_disconnect();
int cfgbus_send(int fun, int len, char *p);
prjinfo_t *cfgbus_prjinfo();
char *cfgbus_cmdsbuf();

// #ifdef __cplusplus
// }
// #endif
#endif
