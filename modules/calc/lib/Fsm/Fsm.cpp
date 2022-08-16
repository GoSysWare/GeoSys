#include <stddef.h>
#include "modules/calc/include/k_functionblock.h"

#include "STATE"
#include "TRANS"
#include "CONDITION"

static void *fb_table[]={
	&fb_RS,
	&fb_SR,
	};

static size_t cursor;

void *fsmtable_first()
{
	cursor = 0;
	return fb_table[0];
}

void *fsmtable_next()
{
	cursor++;
	if(cursor < sizeof(fb_table) / sizeof(void *)){
		return fb_table[cursor];
	}else{
		return 0;	//NULL
	}
}
