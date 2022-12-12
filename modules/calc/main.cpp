#include "modules/calc/include/k_command.h"
#include "modules/calc/include/k_lib.h"
#include "modules/calc/include/k_project.h"

#include "cyber/cyber.h"
#include "cyber/timer/timer.h"
#include "modules/calc/kernel/include/k_project.h"

#include <iostream>
#include <memory>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  apollo::cyber::Init(argv[0]);
  // create talker node
  auto engine_node = apollo::cyber::CreateNode("robot_engine");
  proj_ini()
 
  apollo::cyber::WaitForShutdown();
}