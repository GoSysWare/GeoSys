#include <stddef.h>
#include "modules/calc/include/k_functionblock.h"

#include "EQ_INT"
#include "EQ_REAL"
#include "EQ_LREAL"

#include "GE_INT"
#include "GE_REAL"
#include "GE_LREAL"

#include "GT_INT"
#include "GT_REAL"
#include "GT_LREAL"

#include "LE_INT"
#include "LE_REAL"
#include "LE_LREAL"

#include "LT_INT"
#include "LT_REAL"
#include "LT_LREAL"

#include "NE_INT"
#include "NE_REAL"
#include "NE_LREAL"

static void *fb_table[]={
	&fb_EQ_INT,
	&fb_EQ_REAL,
	&fb_EQ_LREAL,

	&fb_GE_INT,
	&fb_GE_REAL,
	&fb_GE_LREAL,

	&fb_GT_INT,
	&fb_GT_REAL,
	&fb_GT_LREAL,

	&fb_LE_INT,
	&fb_LE_REAL,
	&fb_LE_LREAL,

	&fb_LT_INT,
	&fb_LT_REAL,
	&fb_LT_LREAL,

	&fb_NE_INT,
	&fb_NE_REAL,
	&fb_NE_LREAL,
	};

static int cursor;

void *comparison_first()
{
	cursor = 0;
	return fb_table[0];
}

void *comparison_next()
{
	cursor++;
	if(cursor < sizeof(fb_table) / sizeof(void *)){
		return fb_table[cursor];
	}else{
		return ((void*) 0);	//NULL
	}
}
