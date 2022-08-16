#include "modules/calc/include/k_functionblock.h"
#include "modules/calc/include/k_lib.h"
#include "modules/calc/include/k_program.h"
#include "modules/calc/include/k_evdata.h"

#include "cyber/timer/timer.h"
#include "cyber/cyber.h"


#include <stdlib.h>
#include <stdio.h>
#include <memory>
#include <iostream>

static void TestStringCopyCase1() {
    std::string a = "Hello World";
    std::string b = a;
    printf("pointer of a: %p\n", a.c_str());
    printf("pointer of b: %p\n", b.c_str());
}

// copy on write
static void TestStringCopyCase2() {
    std::string a = "Hello World";
    std::string b = a;
	std::string c (a);

    printf("pointer of a: %p\n", a.c_str());
    printf("pointer of b: %p\n", b.c_str());
    printf("pointer of c: %p\n", c.c_str());

    b[0] = 'h';
    // b += "!";
    printf("pointer of a: %p\n", a.c_str());
    printf("pointer of b: %p\n", b.c_str());
    std::cout << a << std::endl;
    std::cout << b << std::endl;
}


int main(int argc, char *argv[])
{
 	 apollo::cyber::Init(argv[0]);

	int size = sizeof(EVNode);
	int llf = sizeof(std::string);
	TestStringCopyCase1();
	TestStringCopyCase2();


	lib_init();
	value_tm vtm;

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

	std::string lib_name = "Arithmetic";
	std::string fc_name = "ADD_INT";
	std::string fb_name_1 = "add_1";
	std::string fb_name_2 = "add_2";

	prog_t *prg = prg_new();

	prg_fbadd(prg,1,lib_name,fc_name,fb_name_1);
	prg_fbadd(prg,2,lib_name,fc_name,fb_name_2);
	 lib_name = "Counter";
	 fc_name = "CTUD_INT";
	 fb_name_1 = "ctud1";

	prg_fbadd(prg,3,lib_name,fc_name,fb_name_1);

	prg_dump(prg);

	prg_viadd(prg,1,1,1);
	prg_viadd(prg,3,2,2);

	prg_voadd(prg,3,1,1);
	prg_voadd(prg,4,2,1);
	
	prg_voadd(prg,5,3,3);

	prg_lkadd(prg,1,1,1,2,1);

	// prg_lkadd(prg,2,2,1,3,5);

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


	prg_dump(prg);

	uint64_t interval_ = 10;
  	std::unique_ptr<apollo::cyber::Timer> timer_;
	auto func = [prg]() { 	
		prg_exec(prg);
		ev_dump();
		};
	timer_.reset(new apollo::cyber::Timer(interval_, func, false));
	timer_->Start();


  apollo::cyber::WaitForShutdown();


	return 0;
	//prj_main_loop();
}