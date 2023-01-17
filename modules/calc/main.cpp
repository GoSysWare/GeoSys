#include "modules/calc/include/k_command.h"
#include "modules/calc/include/k_lib.h"
#include "modules/calc/include/k_project.h"
#include "modules/calc/include/k_bus.h"

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
  prj_init(0);
  lib_init();
  bus_init(std::move(engine_node));
  // Bus::EditInfosReq edit_infos;

  // std::string file = "/home/shuimujie/Works/save_mod_3_lk.cl";
  // apollo::cyber::common::GetProtoFromASCIIFile(file,&edit_infos);
  // cmds_dispatch(edit_infos);
  // std::cout<< "++++++++++++++++++++++" << std::endl;

  // ev_dump();
  // prj_dump();
  // std::cout<< "++++++++++++++++++++++" << std::endl;

  // Bus::ProjSnapshotRsp snapshot;
  // prj_to_snapshot(&snapshot);

  // std::cout<< "snapshot:" << std::endl;
  // std::cout<< snapshot.DebugString() << std::endl;
  // std::cout<< "++++++++++++++++++++++" << std::endl;

  // prj_from_snapshot(&snapshot);





  // std::cout<< "snapshot:" << std::endl;
  // std::cout<< snapshot.DebugString() << std::endl;

  // std::cout<< "++++++++++++++++++++++" << std::endl;

  // ev_dump();
  // prj_dump();
  apollo::cyber::WaitForShutdown();
}