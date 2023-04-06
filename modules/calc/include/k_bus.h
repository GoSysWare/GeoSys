#ifndef k_bus_h
#define k_bus_h

#include "cyber/cyber.h"

#include "modules/calc/proto/cmd.pb.h"
#include "modules/calc/proto/snapshot.pb.h"
#include "k_project.h"

int bus_init(std::shared_ptr<apollo::cyber::Node>  node);
int bus_uninit();





std::shared_ptr<apollo::cyber::Client<Bus::ProjectInfoReq, Bus::ProjectInfoRsp>>
bus_init_client_info(std::shared_ptr<apollo::cyber::Node> node);

std::shared_ptr<apollo::cyber::Client<Bus::ProjectCmdReq, Bus::ProjectCmdRsp>>
bus_init_client_cmd(std::shared_ptr<apollo::cyber::Node> node);

std::shared_ptr<apollo::cyber::Client<Bus::ProjSnapshotReq, Bus::ProjSnapshotRsp>>
bus_init_client_snapshot(std::shared_ptr<apollo::cyber::Node> node);

std::shared_ptr<Bus::ProjectCmdRsp> bus_online_send(
    std::shared_ptr<apollo::cyber::Node> node,
    std::shared_ptr<apollo::cyber::Client<Bus::ProjectCmdReq, Bus::ProjectCmdRsp>> bus_cmd);

std::shared_ptr<Bus::ProjectCmdRsp> bus_disconnect_send(
    std::shared_ptr<apollo::cyber::Node> node,
    std::shared_ptr<apollo::cyber::Client<Bus::ProjectCmdReq, Bus::ProjectCmdRsp>> bus_cmd);

std::shared_ptr<Bus::ProjectCmdRsp> bus_run_send(
    std::shared_ptr<apollo::cyber::Node> node,
    std::shared_ptr<apollo::cyber::Client<Bus::ProjectCmdReq, Bus::ProjectCmdRsp>> bus_cmd);

std::shared_ptr<Bus::ProjectCmdRsp> bus_stop_send(
    std::shared_ptr<apollo::cyber::Node> node,
    std::shared_ptr<apollo::cyber::Client<Bus::ProjectCmdReq, Bus::ProjectCmdRsp>> bus_cmd);

std::shared_ptr<Bus::ProjectCmdRsp> bus_reset_send(
    std::shared_ptr<apollo::cyber::Node> node,
    std::shared_ptr<apollo::cyber::Client<Bus::ProjectCmdReq, Bus::ProjectCmdRsp>> bus_cmd);

std::shared_ptr<Bus::ProjectCmdRsp> bus_sync_send(
    std::shared_ptr<apollo::cyber::Node> node,
    std::shared_ptr<apollo::cyber::Client<Bus::ProjectCmdReq, Bus::ProjectCmdRsp>> bus_cmd);

std::shared_ptr<Bus::ProjectCmdRsp> bus_download_send(
    std::shared_ptr<apollo::cyber::Node> node,
    std::shared_ptr<apollo::cyber::Client<Bus::ProjectCmdReq, Bus::ProjectCmdRsp>> bus_cmd,
    Bus::EditInfos edit_infos);

std::shared_ptr<Bus::ProjectCmdRsp> bus_set_val_send(
    std::shared_ptr<apollo::cyber::Node> node,
    std::shared_ptr<apollo::cyber::Client<Bus::ProjectCmdReq, Bus::ProjectCmdRsp>> bus_cmd,
    Bus::EditInfos edit_infos);

std::shared_ptr<Bus::ProjectCmdRsp> bus_upload_send(
    std::shared_ptr<apollo::cyber::Node> node,
    std::shared_ptr<apollo::cyber::Client<Bus::ProjectCmdReq, Bus::ProjectCmdRsp>> bus_cmd);


std::shared_ptr<Bus::ProjSnapshotRsp> bus_proj_snapshot_send(
    std::shared_ptr<apollo::cyber::Node> node,
    std::shared_ptr<apollo::cyber::Client<Bus::ProjSnapshotReq, Bus::ProjSnapshotRsp>> bus_cmd);


std::shared_ptr<Bus::ProjectInfoRsp> bus_proj_info_send(
    std::shared_ptr<apollo::cyber::Node> node,
    std::shared_ptr<apollo::cyber::Client<Bus::ProjectInfoReq, Bus::ProjectInfoRsp>> bus_cmd);



#endif