#include <stddef.h>
#include "modules/calc/include/k_functionblock.h"
#include "modules/calc/include/k_project.h"
#include "modules/calc/include/k_module.h"
#include "modules/calc/ioss/ioss.h"

#include "SIM_READ"
#include "CAMERA"
#include "CAMERA_INIT"
static void *fb_table[]={
	&fb_SIM_READ,
	&fb_CAMERA,
	&fb_CAMERA_INIT,

	};

static size_t cursor;

void *devices_first()
{
	cursor = 0;
	return fb_table[0];
}

void *devices_next()
{
	cursor++;
	if(cursor < sizeof(fb_table) / sizeof(void *)){
		return fb_table[cursor];
	}else{
		return 0;	//NULL
	}
}
