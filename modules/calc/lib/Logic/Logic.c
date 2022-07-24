#include <stddef.h>
#include "modules/calc/include/k_functionblock.h"

#include "AND"
#include "AND4"
#include "OR"
#include "OR4"
#include "NOT"
#include "XOR"

static void *fb_table[]={
	&fb_AND,
	&fb_AND4,
	&fb_OR,
	&fb_OR4,
	&fb_NOT,
	&fb_XOR,
	};

static int cursor;

void *logic_first()
{
	cursor = 0;
	return fb_table[0];
}

void *logic_next()
{
	cursor++;
	if(cursor < sizeof(fb_table) / sizeof(void *)){
		return fb_table[cursor];
	}else{
		return ((void*) 0);	//NULL
	}
}
