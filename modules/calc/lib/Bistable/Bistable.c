#include <stddef.h>
#include "k_functionblock.h"

#include "RS"
#include "SR"

static void *fb_table[]={
	&fb_RS,
	&fb_SR,
	};

static int cursor;

void *bistable_first()
{
	cursor = 0;
	return fb_table[0];
}

void *bistable_next()
{
	cursor++;
	if(cursor < sizeof(fb_table) / sizeof(void *)){
		return fb_table[cursor];
	}else{
		return ((void*) 0);	//NULL
	}
}
