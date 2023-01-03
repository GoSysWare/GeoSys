#ifndef k_bus_h
#define k_bus_h

#include "cyber/cyber.h"

#include "modules/calc/proto/cmd.pb.h"
#include "modules/calc/proto/snapshot.pb.h"
#include "k_project.h"

int bus_init(std::shared_ptr<apollo::cyber::Node>  node);
int bus_uninit();


std::shared_ptr<apollo::cyber::Client<Bus::EditInfosReq, Bus::EditInfosRsp>>
bus_init_client_edit(std::shared_ptr<apollo::cyber::Node> node);


std::shared_ptr<apollo::cyber::Client<Bus::ProjectInfoReq, Bus::ProjectInfoRsp>>
bus_init_client_info(std::shared_ptr<apollo::cyber::Node> node);

std::shared_ptr<apollo::cyber::Client<Bus::ProjectCmdReq, Bus::ProjectCmdRsp>>
bus_init_client_cmd(std::shared_ptr<apollo::cyber::Node> node);

#endif