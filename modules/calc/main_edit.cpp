#include "modules/calc/include/k_command.h"
#include "modules/calc/include/k_lib.h"
#include "modules/calc/include/k_project.h"

#include "cyber/cyber.h"
#include "cyber/timer/timer.h"
#include "modules/calc/proto/cmd.pb.h"

#include <iostream>
#include <memory>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  apollo::cyber::Init(argv[0]);
  // create talker node
  auto engine_node = apollo::cyber::CreateNode("robot_engine");
  Bus::EditInfos edit_infos;
  Bus::EditInfo *info_ptr;
  // apollo::cyber::common::GetProtoFromFile("/home/shuimujie/Works/GeoSys/modules/calc/logic.ce",&edit_infos);
  info_ptr = edit_infos.add_infos();
  info_ptr->set_cmd_id(1);
  info_ptr->set_element(Bus::EditElement::PROJ);
  info_ptr->set_edit_type(Bus::EditType::ADD);
  info_ptr->mutable_proj()->set_proj_id(1);
  info_ptr->mutable_proj()->set_proj_name("P1");

  info_ptr = edit_infos.add_infos();
  info_ptr->set_cmd_id(2);
  info_ptr->set_element(Bus::EditElement::MOD);
  info_ptr->set_edit_type(Bus::EditType::ADD);
  info_ptr->mutable_mod()->set_proj_id(1);
  info_ptr->mutable_mod()->set_proj_name("P1");
  info_ptr->mutable_mod()->set_mod_id(1);
  info_ptr->mutable_mod()->set_mod_name("M1");
  info_ptr->mutable_mod()->set_mod_uuid("xxxxx-xxxx-xxxx-xx-xxxxx");

  info_ptr = edit_infos.add_infos();
  info_ptr->set_cmd_id(3);
  info_ptr->set_element(Bus::EditElement::TASK);
  info_ptr->set_edit_type(Bus::EditType::ADD);
  info_ptr->mutable_task()->set_task_type(Bus::TaskType::SERVICE);
  info_ptr->mutable_task()->set_mod_id(1);
  info_ptr->mutable_task()->set_mod_name("M1");
  info_ptr->mutable_task()->set_task_id(1);
  info_ptr->mutable_task()->set_task_name("T1");

  info_ptr = edit_infos.add_infos();
  info_ptr->set_cmd_id(4);
  info_ptr->set_element(Bus::EditElement::TASK);
  info_ptr->set_edit_type(Bus::EditType::ADD);
  info_ptr->mutable_task()->set_task_type(Bus::TaskType::TIMER);
  info_ptr->mutable_task()->set_mod_id(1);
  info_ptr->mutable_task()->set_mod_name("M1");
  info_ptr->mutable_task()->set_task_id(2);
  info_ptr->mutable_task()->set_task_name("T2");

  info_ptr = edit_infos.add_infos();
  info_ptr->set_cmd_id(5);
  info_ptr->set_element(Bus::EditElement::TASK);
  info_ptr->set_edit_type(Bus::EditType::RM);
  info_ptr->mutable_task()->set_task_type(Bus::TaskType::FSM);
  info_ptr->mutable_task()->set_mod_id(2);
  info_ptr->mutable_task()->set_mod_name("M1");
  info_ptr->mutable_task()->set_task_id(3);
  info_ptr->mutable_task()->set_task_name("T2");

  info_ptr = edit_infos.add_infos();
  info_ptr->set_cmd_id(6);
  info_ptr->set_element(Bus::EditElement::EV);
  info_ptr->set_edit_type(Bus::EditType::SET);
  info_ptr->mutable_ev()->set_ev_id(2);
  info_ptr->mutable_ev()->set_ev_name("M1");
  info_ptr->mutable_ev()->mutable_init_val()->set_tm(
      apollo::cyber::Time::Now().ToNanosecond());
  info_ptr->mutable_ev()->mutable_init_val()->mutable_v()->set_t(T_FLOAT32);
  info_ptr->mutable_ev()->mutable_init_val()->mutable_v()->set_f(1.223f);


  cmds_dispatch(edit_infos);

  std::string file = "/home/shuimujie/Works/GeoSys/modules/calc/logic_out.ce";
  apollo::cyber::common::SetProtoToASCIIFile(edit_infos, file);

  apollo::cyber::WaitForShutdown();
}