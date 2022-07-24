#include <math.h>
#include <stddef.h>
#include "modules/calc/include/k_functionblock.h"

#include "ABS"
#include "MOD"

#include "SIN"
#include "COS"
#include "TAN"

#include "ASIN"
#include "ACOS"
#include "ATAN"

#include "SQRT"
#include "EXP"
#include "LN"
#include "LOG"

#include "FUN12"
#include "POLYNOM"
#include "AVE4W"

static void *fb_table[]={
	&fb_ABS,
	&fb_MOD,

	&fb_SIN,
	&fb_COS,
	&fb_TAN,

	&fb_ASIN,
	&fb_ACOS,
	&fb_ATAN,

	&fb_SQRT,
	&fb_EXP,
	&fb_LN,
	&fb_LOG,

	&fb_FUN12,
	&fb_POLYNOM,
	&fb_AVE4W,
	};

static int cursor;

void *maths_first()
{
	cursor = 0;
	return fb_table[0];
}

void *maths_next()
{
	cursor++;
	if(cursor < sizeof(fb_table) / sizeof(void *)){
		return fb_table[cursor];
	}else{
		return ((void*) 0);	//NULL
	}
}
