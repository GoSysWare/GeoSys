#include <stddef.h>
#include <math.h>

#include "modules/calc/include/k_functionblock.h"
#include "modules/calc/include/k_util.h"

#include "BALANCE"
#include "DDS"
#include "DIFF"
#include "ES_MA"
#include "FILTER"
#include "FIRST"
#include "HL_ALM"
#include "HL_LMT"
#include "INTEG"
#include "LEADLAG"
#include "LIMV"
#include "PID"
#include "RAT_ALM"
#include "RAT_LMT"
#include "RMP"
#include "SFT_BOOL"
#include "SFT_REAL"
#include "SS_MA"
#include "TOTALIZER"

static void *fb_table[]={
	&fb_BALANCE,
	&fb_DDS,
	&fb_DIFF,
	&fb_ES_MA,
	&fb_FILTER,
	&fb_FIRST,
	&fb_HL_ALM,
	&fb_HL_LMT,
	&fb_INTEG,
	&fb_LEADLAG,
	&fb_LIMV,
	&fb_PID,
	&fb_RAT_ALM,
	&fb_RAT_LMT,
	&fb_RMP,
	&fb_SFT_BOOL,
	&fb_SFT_REAL,
	&fb_SS_MA,	
	&fb_TOTALIZER,
	};

static int cursor;

void *control_first()
{
	cursor = 0;
	return fb_table[0];
}

void *control_next()
{
	cursor++;
	if(cursor < sizeof(fb_table) / sizeof(void *)){
		return fb_table[cursor];
	}else{
		return ((void*) 0);	//NULL
	}
}
