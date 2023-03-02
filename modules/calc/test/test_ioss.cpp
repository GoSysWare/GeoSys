
#include <stdlib.h>
#include <stdio.h>
#include <memory>
#include <iostream>


#include "modules/calc/ioss/ioss.h"
#include <iostream>
#include <vector>
using namespace std;
int main(int argc, char *argv[])
{
  apollo::cyber::Init(argv[0]);


    ioss_init();
    vam_t v = std::make_shared<value_tm>();

    v->mutable_v()->set_t(v_type::T_FLOAT64);
    io_update_tag("SIM","OUT1",v);

  apollo::cyber::WaitForShutdown();

    return 0;
}