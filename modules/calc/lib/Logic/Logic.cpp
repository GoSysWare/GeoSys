#include <stddef.h>
#include <math.h>

#include "modules/calc/include/k_functionblock.h"

#include "AND"
#include "AND4"
#include "NOT"
#include "OR"
#include "OR4"
#include "RS"
#include "SCALING"
#include "SIX_SEL_N"
#include "SR"
#include "TWOSEL"
// #include "THRSEL"
#include "XOR"

static void *fb_table[]={
	&fb_AND,
	&fb_AND4,
	&fb_OR,
	&fb_OR4,
	&fb_NOT,
	&fb_XOR,
	&fb_RS,
	&fb_SR,
	&fb_TWOSEL,
	&fb_SCALING,
	// &fb_THRSEL,
	&fb_SIX_SEL_N,
	};

static size_t cursor;

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
		return 0;	//NULL
	}
}
