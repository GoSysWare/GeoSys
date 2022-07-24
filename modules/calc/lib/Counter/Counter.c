#include <stddef.h>
#include "modules/calc/include/k_functionblock.h"

#include "CTUD_INT"

static void *fb_table[]={
	&fb_CTUD_INT,
	};

static int cursor;

void *counter_first()
{
	cursor = 0;
	return fb_table[0];
}

void *counter_next()
{
	cursor++;
	if(cursor < sizeof(fb_table) / sizeof(void *)){
		return fb_table[cursor];
	}else{
		return ((void*) 0);	//NULL
	}
}
