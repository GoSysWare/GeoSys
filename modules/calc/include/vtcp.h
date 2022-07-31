

#ifndef vtcp_h
#define vtcp_h

#include "k_config.h"
#include "vnet.h"

// #ifdef __cplusplus
// extern "C" {
// #endif


void vtcp_init();
void vtcp_uninit();
int vtcp_srvcreate(int port, frecvfrom ondata);
int vtcp_srvsend(int port, int income, int len, char *data);
void vtcp_srvclose(int port);
int vtcp_cltcreate(int port, frecvfrom ondata, char *srvaddr);
int vtcp_cltsend(int port, int len, char *data);
void vtcp_cltclose(int port);

// #ifdef __cplusplus
// }
// #endif
#endif


