#ifndef k_service_h
#define k_service_h

#include "modules/calc/include/k_bus.h"
#include "modules/calc/common/calc_gflags.h"
#include "modules/calc/include/k_command.h"

// apollo::cyber::Service engine_info_srv;
// apollo::cyber::Service prj_info_srv;
// apollo::cyber::Service snapshot_srv;
// apollo::cyber::Service io_table_srv;
// apollo::cyber::Service ev_table_srv;
// apollo::cyber::Service<Bus::EditInfos,Bus::EditInfosRsq> prj_edit_srv;

int bus_init(std::shared_ptr<apollo::cyber::Node> &node) {

  auto prj_edit_srv = node->CreateService<Bus::EditInfos, Bus::EditInfosRsp>(
      FLAGS_edit_cmd_name, [](const std::shared_ptr<Bus::EditInfos> &request,
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
}

int bus_uninit() {}

#endif