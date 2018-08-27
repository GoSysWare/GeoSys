#include <stddef.h>
#include "k_functionblock.h"

#include "RG_BOOL"
#include "RG_INT"
#include "RG_REAL"
#include "WG_BOOL"
#include "WG_INT"
#include "WG_REAL"

static void *fb_table[]={
	&fb_RG_BOOL,
	&fb_RG_INT,
	&fb_RG_REAL,
	&fb_WG_BOOL,
	&fb_WG_INT,
	&fb_WG_REAL,
	};

static int cursor;

void *comm_first()
{
	cursor = 0;
	return fb_table[0];
}

void *comm_next()
{
	cursor++;
	if(cursor < sizeof(fb_table) / sizeof(void *)){
		return fb_table[cursor];
	}else{
		return ((void*) 0);	//NULL
	}
}
