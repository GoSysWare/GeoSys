#ifndef k_service_h
#define k_service_h

#include "cyber/cyber.h"

#include "modules/calc/proto/cmd.pb.h"

#include "modules/calc/common/calc_gflags.h"
#include "bus.h"


// apollo::cyber::Service engine_info_srv;
// apollo::cyber::Service prj_info_srv;
// apollo::cyber::Service snapshot_srv;
// apollo::cyber::Service io_table_srv;
// apollo::cyber::Service ev_table_srv;
// apollo::cyber::Service<Cmd::EditInfos,Cmd::EditInfosRsq> prj_edit_srv;



int rbus_init(std::shared_ptr<apollo::cyber::Node> & node)
{

    auto prj_edit_srv = node->CreateService<Cmd::EditInfos,Cmd::EditInfosRsq>(
      FLAG_calc_edit_cmd_name, [](const std::shared_ptr<Cmd::EditInfos>& request,
                        std::shared_ptr<Cmd::EditInfosRsq>& response) {
        AINFO << "cmd edit ";
        cmds_dispatch(*request);
      });  

}

int rbus_uninit()
{

}


#endif