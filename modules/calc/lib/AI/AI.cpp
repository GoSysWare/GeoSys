#include <stddef.h>
#include "modules/calc/include/k_functionblock.h"

#include "modules/calc/ioss/ioss.h"

#include "DLIB_FACE_DETECT"

static void *fb_table[]={
	&fb_DLIB_FACE_DETECT,

	};

static size_t cursor;

void *ai_first()
{
	cursor = 0;
	return fb_table[0];
}

void *ai_next()
{
	cursor++;
	if(cursor < sizeof(fb_table) / sizeof(void *)){
		return fb_table[cursor];
	}else{
		return 0;	//NULL
	}
}
