#ifndef k_service_h
#define k_service_h

#include "modules/calc/include/k_command.h"
#include "modules/calc/include/k_bus.h"
#include "modules/calc/common/calc_gflags.h"



// apollo::cyber::Service engine_info_srv;
// apollo::cyber::Service prj_info_srv;
// apollo::cyber::Service snapshot_srv;
// apollo::cyber::Service io_table_srv;
// apollo::cyber::Service ev_table_srv;
// apollo::cyber::Service<Cmd::EditInfos,Cmd::EditInfosRsq> prj_edit_srv;



int bus_init(std::shared_ptr<apollo::cyber::Node> & node)
{

    auto prj_edit_srv = node->CreateService<Cmd::EditInfos,Cmd::EditInfosRsp>(
      FLAGS_edit_cmd_name, [](const std::shared_ptr<Cmd::EditInfos>& request,
                        std::shared_ptr<Cmd::EditInfosRsp>& response) {
        AINFO << "cmd edit ";
        cmds_dispatch(*request);
      });  
    auto prj_info_srv = node->CreateService<Cmd::EditInfos,Cmd::EditInfosRsp>(
      FLAGS_prj_info_name, [](const std::shared_ptr<Cmd::EditInfos>& request,
                        std::shared_ptr<Cmd::EditInfosRsp>& response) {
        AINFO << "cmd edit ";
        cmds_dispatch(*request);
      });  
}

int bus_uninit()
{

}


#endif