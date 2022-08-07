#include <stddef.h>
#include "modules/calc/include/k_functionblock.h"

#include "ADD_INT"
// #include "ADD_REAL"
// #include "ADD_LREAL"

// #include "SUB_INT"
// #include "SUB_REAL"
// #include "SUB_LREAL"

// #include "MUL_INT"
// #include "MUL_REAL"
// #include "MUL_LREAL"

// #include "DIV_INT"
// #include "DIV_REAL"
// #include "DIV_LREAL"

// #include "MOVE_BOOL"
// #include "MOVE_INT"
// #include "MOVE_REAL"
// #include "MOVE_LREAL"

static void *fb_table[]={
	&fb_ADD_INT,
	// &fb_ADD_REAL,
	// &fb_ADD_LREAL,
	
	// &fb_SUB_INT,
	// &fb_SUB_REAL,
	// &fb_SUB_LREAL,

	// &fb_MUL_INT,
	// &fb_MUL_REAL,
	// &fb_MUL_LREAL,

	// &fb_DIV_INT,
	// &fb_DIV_REAL,
	// &fb_DIV_LREAL,
	
	// &fb_MOVE_BOOL,
	// &fb_MOVE_INT,
	// &fb_MOVE_REAL,
	// &fb_MOVE_LREAL,
	};

static int cursor;

void *arithmetic_first()
{
	cursor = 0;
	return fb_table[0];
}

void *arithmetic_next()
{
	cursor++;
	if(cursor < sizeof(fb_table) / sizeof(void *)){
		return fb_table[cursor];
	}else{
		return 0;	//NULL
	}
}
