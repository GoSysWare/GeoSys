#include "modules/calc/include/k_evdata.h"


#include <stdlib.h>
#include <stdio.h>
#include <memory>
#include <iostream>



int main(int argc, char *argv[])
{
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

	ev_dump();

	std::cout<< vtm.SerializeAsString()<<std::endl;
	return 0;
	//prj_main_loop();
}