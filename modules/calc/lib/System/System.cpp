#include <stddef.h>
#include <thread>
#include <sstream>
#include "cyber/cyber.h"
#include "modules/calc/include/k_functionblock.h"
#include "modules/calc/include/k_util.h"

#include "SYSSTATE"
#include "FILE_READ_ONCE"

static void *fb_table[]={
	&fb_SYSSTATE,
	&fb_FILE_OPEN_ONCE,
	};

static size_t cursor;

void *system_first()
{
	cursor = 0;
	return fb_table[0];
}

void *system_next()
{
	cursor++;
	if(cursor < sizeof(fb_table) / sizeof(void *)){
		return fb_table[cursor];
	}else{
		return 0;	//NULL
	}
}
