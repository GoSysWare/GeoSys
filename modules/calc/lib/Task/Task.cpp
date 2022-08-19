#include <stddef.h>
#include <chrono>
#include "modules/calc/include/k_functionblock.h"
#include "modules/calc/include/k_project.h"
#include "modules/calc/include/k_program.h"

#include "cyber/task/task.h"

#include "TASK"

static void *fb_table[]={
	&fb_TASK,
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
