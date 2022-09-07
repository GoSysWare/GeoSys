#include "modules/calc/include/k_project.h"
#include "modules/calc/include/k_command.h"
#include "modules/calc/include/k_process.h"
#include "modules/calc/include/k_lib.h"


#include "cyber/cyber.h"
#include "cyber/timer/timer.h"

#include <iostream>
#include <memory>
#include <stdio.h>
#include <stdlib.h>



int main(int argc, char *argv[])
{
 apollo::cyber::Init(argv[0]);
  // create talker node
  auto engine_node = apollo::cyber::CreateNode("robot_engine");

  // create talker
  auto talker = talker_node->CreateWriter<Chatter>("channel/chatter");

  lib_init();
  prj_init(1);

  uint64_t interval_ = 1000;
  std::unique_ptr<apollo::cyber::Timer> timer_;
  auto func = []() {
    prj_exec();
    ev_dump();
  };
  timer_.reset(new apollo::cyber::Timer(interval_, func, false));
  timer_->Start();

  apollo::cyber::WaitForShutdown();	
	
	
}