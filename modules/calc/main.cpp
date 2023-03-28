#include "modules/calc/include/k_command.h"
#include "modules/calc/include/k_lib.h"
#include "modules/calc/include/k_project.h"
#include "modules/calc/include/k_bus.h"
#include "modules/calc/ioss/ioss.h"

#include "cyber/cyber.h"
#include "cyber/timer/timer.h"

#include <iostream>
#include <memory>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  std::cout<< "enter" << std::endl;

  apollo::cyber::Init(argv[0]);
  // create talker node
  auto engine_node = apollo::cyber::CreateNode("robot_engine");
  ioss_init();
  prj_init(0);
  lib_init();
  bus_init(std::move(engine_node));
  // Bus::EditInfos edit_infos;
  // apollo::cyber::common::GetProtoFromFile("/home/shuimujie/Works/GeoSys/0327.dlib.logic.cl",&edit_infos);
  // cmds_dispatch(edit_infos);

  
  prj_start();

  
  apollo::cyber::WaitForShutdown();
}