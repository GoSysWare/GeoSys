#ifndef k_service_h
#define k_service_h

#include "modules/calc/include/k_bus.h"
#include "modules/calc/common/calc_gflags.h"
#include "modules/calc/include/k_command.h"

static int on_bus_connect() {}
static int on_bus_disconnect() {}
static int on_bus_reset() {}
static int on_bus_run() {}
static int on_bus_stop() {}
static int on_bus_download() {}
static int on_bus_upload() {}
static int on_bus_sync() {}
static bool filter_service(std::string host_name, std::string host_ip,
                           std::string process_id, std::string prj_name) {

  return true;
}

int bus_init(std::shared_ptr<apollo::cyber::Node> &node) {

  auto prj_edit_srv = node->CreateService<Bus::EditInfosReq, Bus::EditInfosRsp>(
      FLAGS_prj_edit_name, [](const std::shared_ptr<Bus::EditInfosReq> &request,
                              std::shared_ptr<Bus::EditInfosRsp> &response) {
        std::cout << "cmds_dispatch" << std::endl;

        cmds_dispatch(*request);
      });
  auto prj_info_srv =
      node->CreateService<Bus::ProjectInfoReq, Bus::ProjectInfoRsp>(
          FLAGS_prj_info_name,
          [](const std::shared_ptr<Bus::ProjectInfoReq> &request,
             std::shared_ptr<Bus::ProjectInfoRsp> &response) {
            std::cout << "get project info" << std::endl;
            prjinfo_t *info = prj_info();
            response->set_prj_uuid(info->uuid);
            response->set_cmd_id(info->cmd_id);
          });
  auto prj_cmd_srv =
      node->CreateService<Bus::ProjectCmdReq, Bus::ProjectCmdRsp>(
          FLAGS_prj_cmd_name,
          [](const std::shared_ptr<Bus::ProjectCmdReq> &request,
             std::shared_ptr<Bus::ProjectCmdRsp> &response) {
            std::cout << "prject  cmd" << std::endl;
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
              break;
            case Bus::RunType::STOP:
              on_bus_stop();
              /* code */
              break;
            case Bus::RunType::RESET:
              on_bus_reset();
              /* code */
              break;
            case Bus::RunType::SYNC:
              on_bus_sync();
              /* code */
              break;
            case Bus::RunType::DOWNLOAD:
              on_bus_download();
              /* code */
              break;
            case Bus::RunType::UPLOAD:
              on_bus_upload();
              /* code */
              break;
            default:
              break;
            }
          });
}

int bus_uninit() {}

#endif