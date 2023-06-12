#ifndef k_lib_h
#define k_lib_h


#include "k_config.h"
#include "k_functionblock.h"

using fbget = std::function<void* (void)>;
using fbinit = std::function<void (void)>;

typedef struct Lib{
	std::string libname;
	fbget first;
	fbget next;
}lib_t;

void lib_init();
lib_t *lib_first();
lib_t *lib_next();
fb_t *lib_find(const std::string &libname , const std::string &fcname);


#endif
