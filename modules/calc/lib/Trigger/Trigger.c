#include <stddef.h>
#include "modules/calc/include/k_functionblock.h"

#include "U_TRIG"
#include "D_TRIG"

static void *fb_table[]={
	&fb_U_TRIG,
	&fb_D_TRIG,
	};

static int cursor;

void *trigger_first()
{
	cursor = 0;
	return fb_table[0];
}

void *trigger_next()
{
	cursor++;
	if(cursor < sizeof(fb_table) / sizeof(void *)){
		return fb_table[cursor];
	}else{
		return ((void*) 0);	//NULL
	}
}
