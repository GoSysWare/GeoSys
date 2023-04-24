#include <stddef.h>
#include "modules/calc/include/k_functionblock.h"

#include "modules/calc/proto/geo.pb.h"
#include "modules/calc/proto/nav.pb.h"

#include "PATH_MERGE"

#include "PATH_SPLIT"
#include "PATH_CREATE"


static void *fb_table[]={
	&fb_PATH_SPLIT,
	&fb_PATH_MERGE,
	&fb_PATH_CREATE,

};

static size_t cursor;

void *geometry_first()
{
	cursor = 0;
	return fb_table[0];
}

void *geometry_next()
{
	cursor++;
	if(cursor < sizeof(fb_table) / sizeof(void *)){
		return fb_table[cursor];
	}else{
		return 0;	//NULL
	}
}
