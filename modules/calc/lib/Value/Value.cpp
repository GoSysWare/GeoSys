#include <stddef.h>
#include "modules/calc/include/k_functionblock.h"


#include "V_GET_ANY"
#include "V_GET_DOUBLE"
static void *fb_table[]={
	&fb_V_GET_ANY,
	&fb_V_GET_DOUBLE,
	};

static size_t cursor;

void *value_first()
{
	cursor = 0;
	return fb_table[0];
}

void *value_next()
{
	cursor++;
	if(cursor < sizeof(fb_table) / sizeof(void *)){
		return fb_table[cursor];
	}else{
		return 0;	//NULL
	}
}
