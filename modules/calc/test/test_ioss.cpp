
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


    apollo::cyber::Timer timer(200, [] {

      vam_t v = std::make_shared<value_tm>();
      v->mutable_v()->set_t(v_type::T_FLOAT64);
      io_update_tag("SIM","OUT1",v);
      vam_t v_img = std::make_shared<value_tm>();
      v_img->mutable_v()->set_t(v_type::T_IMAGE);
      io_update_tag("front camera","IMG",v_img);



    }, false);

  timer.Start();

  apollo::cyber::WaitForShutdown();

    return 0;
}