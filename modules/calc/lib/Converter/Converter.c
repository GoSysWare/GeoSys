#include <stddef.h>
#include "k_functionblock.h"

#include "B2I"
#include "B2R"
#include "B2LR"
#include "B2DT"

#include "I2B"
#include "I2R"
#include "I2LR"
#include "I2DT"

#include "R2B"
#include "R2I"
#include "R2LR"
#include "R2DT"

#include "LR2B"
#include "LR2I"
#include "LR2R"
#include "LR2DT"

#include "DT2B"
#include "DT2I"
#include "DT2R"
#include "DT2LR"

#include "SCALING"

static void *fb_table[]={
	&fb_B2I,
	&fb_B2R,
	&fb_B2LR,
	&fb_B2DT,

	&fb_I2B,
	&fb_I2R,
	&fb_I2LR,
	&fb_I2DT,

	&fb_R2B,
	&fb_R2I,
	&fb_R2LR,	
	&fb_R2DT,

	&fb_LR2B,
	&fb_LR2I,
	&fb_LR2R,
	&fb_LR2DT,

	&fb_DT2B,
	&fb_DT2I,
	&fb_DT2R,
	&fb_DT2LR,

	&fb_SCALING,
	};

static int cursor;

void *converter_first()
{
	cursor = 0;
	return fb_table[0];
}

void *converter_next()
{
	cursor++;
	if(cursor < sizeof(fb_table) / sizeof(void *)){
		return fb_table[cursor];
	}else{
		return ((void*) 0);	//NULL
	}
}
