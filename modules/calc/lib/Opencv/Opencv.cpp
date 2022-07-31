#include <stddef.h>
#include "modules/calc/include/k_functionblock.h"

#include "IMG_OPEN"


static void *fb_table[]={
	&opencv_Open,
	
	};

static int cursor;

void *opencv_first()
{
	cursor = 0;
	return fb_table[0];
}

void *opencv_next()
{
	cursor++;
	if(cursor < sizeof(fb_table) / sizeof(void *)){
		return fb_table[cursor];
	}else{
		return 0;	//NULL
	}
}
