#include "modules/calc/include/k_functionblock.h"
#include "modules/calc/include/k_lib.h"
#include "modules/calc/include/k_program.h"
#include "modules/calc/include/k_evdata.h"


#include <stdlib.h>
#include <stdio.h>
#include <memory>
#include <iostream>


int main(int argc, char *argv[])
{



	lib_init();
	value_tm vtm_open_file;
	vtm_open_file.mutable_v()->set_str("/home/shuimujie/Pictures/pic_1.png");
	value_tm vtm_save_file;
	vtm_save_file.mutable_v()->set_str("/home/shuimujie/Pictures/pic_2.png");


	ev_add(1,vtm_open_file.SerializeAsString(),"T1");
	ev_add(2,vtm_save_file.SerializeAsString(),"T2");

	ev_dump();

	std::string lib_name = "Opencv";
	std::string fc_name1 = "OPENCV_READ";
	std::string fc_name2 = "OPENCV_WRITE";

	std::string fb_name_1 = "read";
	std::string fb_name_2 = "write";

	prog_t *prg = prg_new();

	prg_fbadd(prg,1,lib_name,fc_name1,fb_name_1);
	prg_fbadd(prg,2,lib_name,fc_name2,fb_name_2);

	prg_dump(prg);

	prg_viadd(prg,1,1,1,0);
	prg_viadd(prg,2,2,2,1);
	prg_lkadd(prg,1,1,0,2,0);


	prg_dump(prg);

	prg_exec(prg);




	return 0;
	//prj_main_loop();
}