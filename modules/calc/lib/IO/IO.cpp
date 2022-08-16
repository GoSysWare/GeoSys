#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "modules/calc/include/k_functionblock.h"
#include "modules/calc/include/k_io.h"

#include "DM1x1"
#include "DM2x1"
#include "DM3x1"
#include "DM4x1"

static void *fb_table[]={
	&fb_DM1x1,
	&fb_DM2x1,
	&fb_DM3x1,
	&fb_DM4x1,
	};

static size_t cursor;

void *io_first()
{
	cursor = 0;
	return fb_table[0];
}

void *io_next()
{
	cursor++;
	if(cursor < sizeof(fb_table) / sizeof(void *)){
		return fb_table[cursor];
	}else{
		return 0;	//NULL
	}
}
