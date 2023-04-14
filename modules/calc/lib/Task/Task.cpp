#include <stddef.h>
#include <chrono>
#include "modules/calc/include/k_project.h"
#include "modules/calc/include/k_functionblock.h"
#include "modules/calc/include/k_module.h"
#include "modules/calc/proto/cmd.pb.h"
#include "modules/calc/proto/edit.pb.h"

#include "TASK"
// #include "REQUEST"
// #include "RESPONSE"
#include "EVENT"
#include "SLEEP"

static void *fb_table[]={
	&fb_TASK,
	// &fb_REQUEST,
	// &fb_RESPONSE
	&fb_EVENT,
	&fb_SLEEP,

	};

static size_t cursor;

void *task_first()
{
	cursor = 0;
	return fb_table[0];
}

void *task_next()
{
	cursor++;
	if(cursor < sizeof(fb_table) / sizeof(void *)){
		return fb_table[cursor];
	}else{
		return 0;	//NULL
	}
}
