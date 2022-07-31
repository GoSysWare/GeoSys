#ifndef k_util_h
#define k_util_h

// #ifdef __cplusplus
// extern "C" {
// #endif

#include <string.h>
#include "k_datatype.h"

void *k_malloc(size_t s);
void k_free(void *p);
void k_clk_init();
void k_clk_do();

Time clk_now();
Time clk_cycle();
//Int clk_cycle_us();
Int clk_cycle_ms();

// #ifdef __cplusplus
// }
// #endif
#endif
