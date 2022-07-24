#ifndef k_lib_h
#define k_lib_h

#ifdef __cplusplus
extern "C" {
#endif

#include "k_config.h"
#include "k_functionblock.h"

typedef void *(*fbget)();

typedef struct Lib{
	char libname[LIBNAMESIZE];
	fbget first;
	fbget next;
}lib_t;

void lib_init();
lib_t *lib_first();
lib_t *lib_next();
fb_t *lib_find(char *libname, char *fbname);

#ifdef __cplusplus
}
#endif
#endif
