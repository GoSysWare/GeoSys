

#include "modules/calc/include/k_bus.h"

#include "modules/calc/common/calc_gflags.h"
#include "modules/calc/include/k_command.h"

static int on_bus_connect() {
  AINFO << "on_bus_connect ";

  return 0;
}
static int on_bus_disconnect() {
  AINFO << "on_bus_disconnect ";

  return 0;
}
static int on_bus_reset() {
  AINFO << "on_bus_reset ";
  prj_reset();
  return 0;
}
static int on_bus_run() {
  AINFO << "on_bus_run ";
  prj_run();
  prj_start();
  return 0;
}
static int on_bus_stop() {
  AINFO << "on_bus_stop ";
  prj_stop();
  prj_join();
  prj_exit();
  AINFO << "proj exit";

  return 0;
}
static int on_bus_download(Bus::EditInfos infos) {
  int ret = -1;
  AINFO << "on_bus_download " << infos.ShortDebugString();
  ret = cmds_dispatch(infos);
  // archive logic
  if (ret == 0) {
    AINFO << "on_bus_download succ";
    cmds_append(infos);
  } else {
    AINFO << "on_bus_download error";
  }
  return ret;
}

static int on_bus_upload(Bus::EditInfos *infos) {
  AINFO << "on_bus_upload ";
  return cmds_load(infos);
}

static int on_bus_set_val(Bus::EditInfos infos) {
  AINFO << "on_bus_set_val ";
  return cmds_set_val(infos);
}

static int on_bus_sync() {
  AINFO << "on_bus_sync ";

  return 0;
}
static bool filter_service(std::string host_name, std::string host_ip,
                           std::string process_id, std::string prj_name) {
  return true;
}

std::shared_ptr<
    apollo::cyber::Service<Bus::ProjectInfoReq, Bus::ProjectInfoRsp>>
    prj_info_srv;
std::shared_ptr<
    apollo::cyber::Service<Bus::ProjSnapshotReq, Bus::ProjSnapshotRsp>>
    prj_snapshot_srv;
std::shared_ptr<apollo::cyber::Service<Bus::ProjectCmdReq, Bus::ProjectCmdRsp>>
    prj_cmd_srv;

int bus_init(std::shared_ptr<apollo::cyber::Node> node) {
  prj_info_srv = node->CreateService<Bus::ProjectInfoReq, Bus::ProjectInfoRsp>(
      FLAGS_prj_info_name,
      [](const std::shared_ptr<Bus::ProjectInfoReq> &request,
         std::shared_ptr<Bus::ProjectInfoRsp> &response) {
        // std::cout << "get project info:" << std::endl;
        // std::cout << "request:" << request->DebugString() << std::endl;

        prjinfo_to_snapshot(response.get());

        response->mutable_result()->set_code(Bus::ResultCode::OK);
        response->mutable_result()->set_msg("success");
      });
  prj_snapshot_srv =
      node->CreateService<Bus::ProjSnapshotReq, Bus::ProjSnapshotRsp>(
          FLAGS_prj_snapshot_name,
          [](const std::shared_ptr<Bus::ProjSnapshotReq> &request,
             std::shared_ptr<Bus::ProjSnapshotRsp> &response) {
            // std::cout << "get project snapshot:" << std::endl;
            // std::cout << "request:" << request->DebugString() << std::endl;

            prj_to_snapshot(request.get(), response.get());

            response->mutable_result()->set_code(Bus::ResultCode::OK);
            response->mutable_result()->set_msg("success");
            if (request->evs_size()) {
              response->mutable_ev_id()->CopyFrom(request->evs());
            }
            AINFO << "prj_snapshot_name response size:"
                  << response->ByteSizeLong();
          });
  prj_cmd_srv = node->CreateService<Bus::ProjectCmdReq, Bus::ProjectCmdRsp>(
      FLAGS_prj_cmd_name, [](const std::shared_ptr<Bus::ProjectCmdReq> &request,
                             std::shared_ptr<Bus::ProjectCmdRsp> &response) {
        AINFO << "prject  cmd type" <<  request->cmd_type();
        Bus::EditInfos info;

        switch (request->cmd_type()) {
          case Bus::RunType::ONLINE:
            on_bus_connect();
            response->mutable_result()->set_code((int)Bus::ResultCode::OK);
            break;
          case Bus::RunType::OFFLINE:
            on_bus_disconnect();
            response->mutable_result()->set_code((int)Bus::ResultCode::OK);
            break;
          case Bus::RunType::RUN:
            on_bus_run();
            response->mutable_result()->set_code((int)Bus::ResultCode::OK);
            break;
          case Bus::RunType::STOP:
            on_bus_stop();
            response->mutable_result()->set_code((int)Bus::ResultCode::OK);
            break;
          case Bus::RunType::RESET:
            on_bus_reset();
            response->mutable_result()->set_code((int)Bus::ResultCode::OK);
            break;
          case Bus::RunType::SYNC:
            on_bus_sync();
            response->mutable_result()->set_code((int)Bus::ResultCode::OK);
            break;
          case Bus::RunType::DOWNLOAD:
            if (on_bus_download(request->req_infos()) == 0) {
              response->mutable_result()->set_code((int)Bus::ResultCode::OK);
            } else {
              response->mutable_result()->set_code((int)Bus::ResultCode::FAIL);
            }
            break;
          case Bus::RunType::UPLOAD:
            if (on_bus_upload(response->mutable_rsp_infos()) == 0) {
              response->mutable_result()->set_code((int)Bus::ResultCode::OK);
            } else {
              response->mutable_result()->set_code((int)Bus::ResultCode::FAIL);
            }
          case Bus::RunType::SETVAL:
            if (on_bus_set_val(request->req_infos()) == 0) {
              response->mutable_result()->set_code((int)Bus::ResultCode::OK);
            } else {
              response->mutable_result()->set_code((int)Bus::ResultCode::FAIL);
            }
            break;
          default:
            break;
        }
      });
}

int bus_uninit() {}

std::shared_ptr<apollo::cyber::Client<Bus::ProjectInfoReq, Bus::ProjectInfoRsp>>
bus_init_client_info(std::shared_ptr<apollo::cyber::Node> node) {
  return node->CreateClient<Bus::ProjectInfoReq, Bus::ProjectInfoRsp>(
      FLAGS_prj_info_name);
}
std::shared_ptr<apollo::cyber::Client<Bus::ProjectCmdReq, Bus::ProjectCmdRsp>>
bus_init_client_cmd(std::shared_ptr<apollo::cyber::Node> node) {
  return node->CreateClient<Bus::ProjectCmdReq, Bus::ProjectCmdRsp>(
      FLAGS_prj_cmd_name);
}
std::shared_ptr<
    apollo::cyber::Client<Bus::ProjSnapshotReq, Bus::ProjSnapshotRsp>>
bus_init_client_snapshot(std::shared_ptr<apollo::cyber::Node> node) {
  return node->CreateClient<Bus::ProjSnapshotReq, Bus::ProjSnapshotRsp>(
      FLAGS_prj_snapshot_name);
}
std::shared_ptr<Bus::ProjectCmdRsp> bus_online_send(
    std::shared_ptr<apollo::cyber::Node> node,
    std::shared_ptr<
        apollo::cyber::Client<Bus::ProjectCmdReq, Bus::ProjectCmdRsp>>
        bus_cmd) {
  std::shared_ptr<Bus::ProjectCmdReq> req =
      std::make_shared<Bus::ProjectCmdReq>();
  req->set_cmd_type(Bus::RunType::ONLINE);
  req->set_host_name("test host name");
  req->set_host_ip("test host ip");
  req->set_process_id("test process id");
  req->set_prj_name("test proj name");
  return bus_cmd->SendRequest(req);
}
std::shared_ptr<Bus::ProjectCmdRsp> bus_disconnect_send(
    std::shared_ptr<apollo::cyber::Node> node,
    std::shared_ptr<
        apollo::cyber::Client<Bus::ProjectCmdReq, Bus::ProjectCmdRsp>>
        bus_cmd) {
  std::shared_ptr<Bus::ProjectCmdReq> req =
      std::make_shared<Bus::ProjectCmdReq>();
  req->set_cmd_type(Bus::RunType::OFFLINE);
  req->set_host_name("test host name");
  req->set_host_ip("test host ip");
  req->set_process_id("test process id");
  req->set_prj_name("test proj name");
  return bus_cmd->SendRequest(req);
}
std::shared_ptr<Bus::ProjectCmdRsp> bus_run_send(
    std::shared_ptr<apollo::cyber::Node> node,
    std::shared_ptr<
        apollo::cyber::Client<Bus::ProjectCmdReq, Bus::ProjectCmdRsp>>
        bus_cmd) {
  std::shared_ptr<Bus::ProjectCmdReq> req =
      std::make_shared<Bus::ProjectCmdReq>();
  req->set_cmd_type(Bus::RunType::RUN);
  req->set_host_name("test host name");
  req->set_host_ip("test host ip");
  req->set_process_id("test process id");
  req->set_prj_name("test proj name");
  return bus_cmd->SendRequest(req);
}

std::shared_ptr<Bus::ProjectCmdRsp> bus_stop_send(
    std::shared_ptr<apollo::cyber::Node> node,
    std::shared_ptr<
        apollo::cyber::Client<Bus::ProjectCmdReq, Bus::ProjectCmdRsp>>
        bus_cmd) {
  std::shared_ptr<Bus::ProjectCmdReq> req =
      std::make_shared<Bus::ProjectCmdReq>();
  req->set_cmd_type(Bus::RunType::STOP);
  req->set_host_name("test host name");
  req->set_host_ip("test host ip");
  req->set_process_id("test process id");
  req->set_prj_name("test proj name");
  return bus_cmd->SendRequest(req, std::chrono::seconds(20));
}

std::shared_ptr<Bus::ProjectCmdRsp> bus_reset_send(
    std::shared_ptr<apollo::cyber::Node> node,
    std::shared_ptr<
        apollo::cyber::Client<Bus::ProjectCmdReq, Bus::ProjectCmdRsp>>
        bus_cmd) {
  std::shared_ptr<Bus::ProjectCmdReq> req =
      std::make_shared<Bus::ProjectCmdReq>();
  req->set_cmd_type(Bus::RunType::RESET);
  req->set_host_name("test host name");
  req->set_host_ip("test host ip");
  req->set_process_id("test process id");
  req->set_prj_name("test proj name");
  return bus_cmd->SendRequest(req);
}

std::shared_ptr<Bus::ProjectCmdRsp> bus_sync_send(
    std::shared_ptr<apollo::cyber::Node> node,
    std::shared_ptr<
        apollo::cyber::Client<Bus::ProjectCmdReq, Bus::ProjectCmdRsp>>
        bus_cmd) {
  std::shared_ptr<Bus::ProjectCmdReq> req =
      std::make_shared<Bus::ProjectCmdReq>();
  req->set_cmd_type(Bus::RunType::SYNC);
  req->set_host_name("test host name");
  req->set_host_ip("test host ip");
  req->set_process_id("test process id");
  req->set_prj_name("test proj name");
  return bus_cmd->SendRequest(req);
}

std::shared_ptr<Bus::ProjectCmdRsp> bus_download_send(
    std::shared_ptr<apollo::cyber::Node> node,
    std::shared_ptr<
        apollo::cyber::Client<Bus::ProjectCmdReq, Bus::ProjectCmdRsp>>
        bus_cmd,
    Bus::EditInfos edit_infos) {
  std::shared_ptr<Bus::ProjectCmdReq> req =
      std::make_shared<Bus::ProjectCmdReq>();
  req->set_cmd_type(Bus::RunType::DOWNLOAD);
  req->set_host_name("test host name");
  req->set_host_ip("test host ip");
  req->set_process_id("test process id");
  req->set_prj_name("test proj name");
  req->mutable_req_infos()->CopyFrom(edit_infos);
  return bus_cmd->SendRequest(req);
}
std::shared_ptr<Bus::ProjectCmdRsp> bus_set_val_send(
    std::shared_ptr<apollo::cyber::Node> node,
    std::shared_ptr<
        apollo::cyber::Client<Bus::ProjectCmdReq, Bus::ProjectCmdRsp>>
        bus_cmd,
    Bus::EditInfos edit_infos) {
  std::shared_ptr<Bus::ProjectCmdReq> req =
      std::make_shared<Bus::ProjectCmdReq>();
  req->set_cmd_type(Bus::RunType::SETVAL);
  req->set_host_name("test host name");
  req->set_host_ip("test host ip");
  req->set_process_id("test process id");
  req->set_prj_name("test proj name");
  req->mutable_req_infos()->CopyFrom(edit_infos);
  return bus_cmd->SendRequest(req);
}

std::shared_ptr<Bus::ProjectCmdRsp> bus_upload_send(
    std::shared_ptr<apollo::cyber::Node> node,
    std::shared_ptr<
        apollo::cyber::Client<Bus::ProjectCmdReq, Bus::ProjectCmdRsp>>
        bus_cmd) {
  std::shared_ptr<Bus::ProjectCmdReq> req =
      std::make_shared<Bus::ProjectCmdReq>();
  req->set_cmd_type(Bus::RunType::UPLOAD);
  req->set_host_name("test host name");
  req->set_host_ip("test host ip");
  req->set_process_id("test process id");
  req->set_prj_name("test proj name");
  return bus_cmd->SendRequest(req);
}

std::shared_ptr<Bus::ProjSnapshotRsp> bus_proj_snapshot_send(
    std::shared_ptr<apollo::cyber::Node> node,
    std::shared_ptr<
        apollo::cyber::Client<Bus::ProjSnapshotReq, Bus::ProjSnapshotRsp>>
        bus_cmd,
    std::vector<int> ev_ids, std::vector<Bus::TaskInfo> task_infos) {
  std::shared_ptr<Bus::ProjSnapshotReq> proj_sp_req =
      std::make_shared<Bus::ProjSnapshotReq>();
  proj_sp_req->set_host_name("test host name");
  proj_sp_req->set_host_ip("test host ip");
  proj_sp_req->set_process_id("test process id");
  proj_sp_req->set_prj_name("test proj name");

  proj_sp_req->mutable_evs()->CopyFrom({ev_ids.begin(), ev_ids.end()});
  proj_sp_req->mutable_tasks()->CopyFrom(
      {task_infos.begin(), task_infos.end()});

  return bus_cmd->SendRequest(proj_sp_req);
}

std::shared_ptr<Bus::ProjectInfoRsp> bus_proj_info_send(
    std::shared_ptr<apollo::cyber::Node> node,
    std::shared_ptr<
        apollo::cyber::Client<Bus::ProjectInfoReq, Bus::ProjectInfoRsp>>
        bus_cmd) {
  std::shared_ptr<Bus::ProjectInfoReq> proj_info_req =
      std::make_shared<Bus::ProjectInfoReq>();
  proj_info_req->set_host_name("test host name");
  proj_info_req->set_host_ip("test host ip");
  proj_info_req->set_process_id("test process id");
  proj_info_req->set_prj_name("test proj name");
  return bus_cmd->SendRequest(proj_info_req);
}
