#ifndef k_compress_h
#define k_compress_h
// #ifdef __cplusplus
// extern "C" {
// #endif

#include "k_datatype.h"
#include "k_evdata.h"
#include "k_io.h"

int cmps_zvar(const var_t *p_var, Int type, char *buf);
int cmps_uzvar(const char *buf, var_t *p_var, Int *p_tp);
int cmps_zcell(const iocell_t *p_cell, char *buf);
int cmps_uzcell(const char *buf, iocell_t *p_cell);

// #ifdef __cplusplus
// }
// #endif
#endif
