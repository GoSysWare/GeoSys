#ifndef stbbus_h
#define stbbus_h
// #ifdef __cplusplus
// extern "C" {
// #endif

#include "cfgbus.h"

#define STBMAGIC (CFGMAGIC+1)
#define STANDBYPORT	(CONFIGPORT+1)
#define FUNCSTBINFO 0x08
#define FUNCSTBIMG	0x09
#define FUNCSTBCMD	0x10

void stbbus_init();
void stbbus_uninit();
void stbbus_sync_data();
void stbbus_sync_prog(cfgframe_t *p_frm);

// #ifdef __cplusplus
// }
// #endif
#endif
