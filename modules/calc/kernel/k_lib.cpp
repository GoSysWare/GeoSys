#include <stddef.h>
#include <string.h>
#include "modules/calc/include/k_lib.h"
#include "modules/calc/include/lib/Arithmetic.h"
#include "modules/calc/include/lib/Bistable.h"
#include "modules/calc/include/lib/Comm.h"
#include "modules/calc/include/lib/Comparison.h"
#include "modules/calc/include/lib/Converter.h"
#include "modules/calc/include/lib/Control.h"
#include "modules/calc/include/lib/Counter.h"
#include "modules/calc/include/lib/Driver.h"
#include "modules/calc/include/lib/Fsm.h"
#include "modules/calc/include/lib/IO.h"
#include "modules/calc/include/lib/Logic.h"
#include "modules/calc/include/lib/Maths.h"
#include "modules/calc/include/lib/Opencv.h"
#include "modules/calc/include/lib/Selection.h"
#include "modules/calc/include/lib/System.h"
#include "modules/calc/include/lib/Trigger.h"
#include "modules/calc/include/lib/Timer.h"
#include "modules/calc/include/lib/Task.h"
#include "modules/calc/include/lib/Geometry.h"
#define NLIBCOUNT 32
static size_t cursor;
static lib_t lib_table[NLIBCOUNT]; 

static void lib_set_table(unsigned int id,  std::string  name, fbget first, fbget next)
{
	if(id >= NLIBCOUNT){
		return;
	}
	lib_table[id].libname = name;
	lib_table[id].first = first;
	lib_table[id].next = next;
}

void lib_init()
{
	lib_set_table(0, "Arithmetic", arithmetic_first, arithmetic_next);
// 	// lib_set_table(1, "Bistable", bistable_first, bistable_next);
// 	// lib_set_table(2, "Comm", comm_first, comm_next);
// 	lib_set_table(3, "Comparison", comparison_first, comparison_next);
// 	// lib_set_table(4, "Converter", converter_first, converter_next);
// 	// lib_set_table(5, "Control", control_first, control_next);
// 	lib_set_table(6, "Counter", counter_first, counter_next);
// 	// lib_set_table(7, "Driver", driver_first, driver_next);
// 	// lib_set_table(8, "IO", io_first, io_next);
// 	// lib_set_table(9, "Logic", logic_first, logic_next);
// 	// lib_set_table(10, "Maths", maths_first, maths_next);
// 	// lib_set_table(11, "Selection", selection_first, selection_next);
// 	// lib_set_table(12, "System", system_first, system_next);
// 	lib_set_table(13, "Trigger", trigger_first, trigger_next);
// 	lib_set_table(14, "Timer", timer_first, timer_next);
//    // lib_set_table(15, "Opencv", opencv_first, opencv_next);
//     lib_set_table(16, "Fsm", fsm_first, fsm_next);
// 	lib_set_table(17, "Task", task_first, task_next);
	lib_set_table(18, "Geometry", geometry_first, geometry_next);


	cursor = 0;
}

lib_t *lib_first()
{
	cursor = 0;
	return &lib_table[0];
}

lib_t *lib_next()
{
	cursor++;
	if(cursor < NLIBCOUNT){
		return &lib_table[cursor];
	}else{
        return 0;	//NULL
	}
}

fb_t *lib_find(const std::string &libname , const std::string &fcname)
{
	lib_t *p_lib;
	fb_t *p_fb;
	
	p_lib = lib_first();
	while(p_lib != ((void*) 0)){

		if(libname == p_lib->libname){
            p_fb = (fb_t *)p_lib->first();
			while(p_fb != ((void*) 0)){
				if(fcname == p_fb->h.fcname){
					return p_fb;
				}
                p_fb = (fb_t *)p_lib->next();
			}

            return 0;
		}

		p_lib = lib_next();
	}
	
    return 0;
}
