#include "modules/calc/include/k_functionblock.h"
#include "modules/calc/include/k_lib.h"
#include "modules/calc/include/k_program.h"
#include "modules/calc/include/k_module.h"
#include "modules/calc/include/k_evdata.h"
#include "modules/calc/proto/cmd.pb.h"

#include "cyber/timer/timer.h"
#include "cyber/cyber.h"


#include <stdlib.h>
#include <stdio.h>
#include <memory>
#include <iostream>


int main(int argc, char *argv[])
{
 	 apollo::cyber::Init(argv[0]);
	std::shared_ptr<apollo::cyber::Node>  node =  apollo::cyber::CreateNode("TestMode");

	lib_init();
	value_tm vtm;
	vtm
	value_t *vt = vtm.mutable_v();
	vt->set_t(v_type::T_INT32);
	vt->set_i(1);
	vtm.set_tm(111);
	std::string str = vtm.SerializeAsString();
	int len = str.length();
	value_tm vtm2;
	vtm2.ParseFromString(str);

	ev_add(1,vtm.SerializeAsString(),"T1");
	vt->set_i(2);
	ev_add(2,vtm.SerializeAsString(),"T2");
	vt->set_i(3);
	ev_add(3,vtm.SerializeAsString(),"T3");
	vt->set_i(4);
	ev_add(4,vtm.SerializeAsString(),"T4");
	vt->set_i(5);
	ev_add(5,vtm.SerializeAsString(),"T5");
	ev_dump();

	vt->set_i(2);
	ev_add(6,vtm.SerializeAsString(),"FSM_STATE");

	vt->set_i(7);
	ev_add(7,vtm.SerializeAsString(),"T7");
	vt->set_i(8);
	ev_add(8,vtm.SerializeAsString(),"T8");
	ev_dump();



	std::string lib_name = "Arithmetic";
	std::string fc_name = "ADD_INT";
	std::string fb_name_1 = "add_1";
	std::string fb_name_2 = "add_2";

	mod_t * mod =  mod_new();

	mod_prgadd(mod, 1, "PRG_1", Cmd::TaskType::PERIODIC);
	mod_prgadd(mod, 2, "Task_1", Cmd::TaskType::ASYNC);




	prog_t *prg = mod_prgfind(mod,1);
	prog_t *prg2 = mod_prgfind(mod,2);

	prg_fbadd(prg,1,lib_name,fc_name,fb_name_1);
	prg_fbadd(prg,2,lib_name,fc_name,fb_name_2);
	 lib_name = "Counter";
	 fc_name = "CTUD_INT";
	 fb_name_1 = "ctud1";

	prg_fbadd(prg,3,lib_name,fc_name,fb_name_1);

	 lib_name = "Task";
	 fc_name = "TASK";
	 fb_name_1 = "add_task";

	prg_fbadd(prg,4,lib_name,fc_name,fb_name_1);

	prg_dump(prg);

	prg_viadd(prg,1,1,1);
	prg_viadd(prg,3,2,2);


	//设定第1个add块的2号输入管脚
	fb_t * p_fb = prg_fbfind(prg, 1);
	vt->set_i(10);
    fb_setpin(p_fb, PININPUT, 2, vtm);

	//设定第三个块ctud的5号输入管脚
 	p_fb = prg_fbfind(prg, 3);
	vt->set_i(100);
    fb_setpin(p_fb, PININPUT, 5, vtm);	

	//设定第三个块ctud的1号输入管脚
 	p_fb = prg_fbfind(prg, 3);
	vt->set_b(true);
    fb_setpin(p_fb, PININPUT, 1, vtm);	

	//设定第四个块task的1号输入管脚
 	p_fb = prg_fbfind(prg, 4);
	vt->set_b(true);
    fb_setpin(p_fb, PININPUT, 1, vtm);	
	//设定第四个块task的2号输入管脚
	vt->set_str("Task_1");
    fb_setpin(p_fb, PININPUT, 2, vtm);	
	//设定第四个块task的3号输入管脚
	vt->set_tm(3);
    fb_setpin(p_fb, PININPUT, 3, vtm);



	//T2 连接 add 的 输出pin
	prg_voadd(prg,2,1,1);
	//T4 连接 add 的 输出pin
	prg_voadd(prg,4,2,1);
	//T5 连接 ctud 的 输出pin
	prg_voadd(prg,5,3,3);
	//T8 连接 task 的 输出response
	prg_voadd(prg,8,4,3);	

	//add1 的输出连接add2 的输入
	prg_lkadd(prg,1,1,1,2,1);

	//add1 的输出连接add2 的输入
	prg_lkadd(prg,2,2,1,4,4);

	//ctud 的输出连接task的req
	prg_lkadd(prg,3,3,3,4,4);

	prg_dump(prg);


	//添加task的fb
	 lib_name = "Task";
	 fc_name = "REQUEST";
	 fb_name_1 = "task_1_req";

	prg_fbadd(prg2,6,lib_name,fc_name,fb_name_1);	
	 lib_name = "Task";
	 fc_name = "RESPONSE";
	 fb_name_1 = "task_1_rsp";
	prg_fbadd(prg2,7,lib_name,fc_name,fb_name_1);

	 lib_name = "Arithmetic";
	 fc_name = "ADD_INT";
	fb_name_1 = "add_1";	
	prg_fbadd(prg2,8,lib_name,fc_name,fb_name_1);


 	p_fb = prg_fbfind(prg2, 8);
	//设定第四个块task的3号输入管脚
	vt->set_i(3);
    fb_setpin(p_fb, PININPUT, 2, vtm);

	//add1 的输出连接add2 的输入
	prg_lkadd(prg2,4,6,2,8,1);

	//T7 连接 add 的 输出pin
	prg_voadd(prg2,7,8,1);

	//add1 的输出连接add2 的输入
	prg_lkadd(prg2,5,8,1,7,2);


	mod_exec(mod,node);


  apollo::cyber::WaitForShutdown();


	return 0;
	//prj_main_loop();
}