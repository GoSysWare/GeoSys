#include <stddef.h>
#include "modules/calc/include/k_functionblock.h"
#include "modules/calc/include/k_util.h"

#include "SysState"

static void *fb_table[]={
	&fb_SysState,
	};

static int cursor;

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
