#ifndef k_lib_h
#define k_lib_h

// #ifdef __cplusplus
// extern "C" {
// #endif

#include "k_config.h"
#include "k_functionblock.h"

// typedef void *(*fbget)();
using fbget = std::function<void* (void)>;

typedef struct Lib{
	std::string libname;
	fbget first;
	fbget next;
}lib_t;

void lib_init();
lib_t *lib_first();
lib_t *lib_next();
fb_t *lib_find(const std::string &libname , const std::string &fcname);

// #ifdef __cplusplus
// }
// #endif
#endif
