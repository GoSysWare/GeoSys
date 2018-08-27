


#ifndef vudp_h
#define vudp_h

#include "k_config.h"
#include "vnet.h"

#ifdef __cplusplus
extern "C" {
#endif


int vudp_init();
void vudp_uninit();

//typedef void (*frecv)(int, char *);
int vudp_send(int port, char *p, int len);
int vudp_hook(int port, frecv hook);
void vudp_unhook(int port);

void vudp_set_mask(int port, unsigned char mask);
int vudp_set_loop(int port, int loop);
int vudp_set_ttl(int port, int ttl);
unsigned char vudp_get_mask(int port);
int vudp_get_loop(int port);
int vudp_get_ttl(int port);

#ifdef __cplusplus
}
#endif
#endif
