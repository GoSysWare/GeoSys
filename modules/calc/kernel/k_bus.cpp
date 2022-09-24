#ifndef k_service_h
#define k_service_h

#include "modules/calc/include/k_bus.h"
#include "modules/calc/common/calc_gflags.h"
#include "modules/calc/include/k_command.h"


// case FUNCCMD:
// 		stbbus_sync_prog(p_frm);
// 		oncommand(p_frm->h.len,p_frm->d);
// 		vtcp_srvsend(CONFIGPORT, income, sizeof(cfghead_t)+frm_answer.h.len, (char *)&frm_answer);
// 		break;
// 	case FUNCIMG:
// 		onimg();
// 		vtcp_srvsend(CONFIGPORT, income, sizeof(cfghead_t)+frm_answer.h.len, (char *)&frm_answer);
// 		break;
// 	case FUNCPRJINFO:
// 		onprjinfo();
// 		vtcp_srvsend(CONFIGPORT, income, sizeof(cfghead_t)+frm_answer.h.len, (char *)&frm_answer);
// 		break;
// 	case FUNCRESET:
// 		onreset();
// 		vtcp_srvsend(CONFIGPORT, income, sizeof(cfghead_t)+frm_answer.h.len, (char *)&frm_answer);
// 		break;
// 	case FUNCRUN:
// 		onrun();
// 		vtcp_srvsend(CONFIGPORT, income, sizeof(cfghead_t)+frm_answer.h.len, (char *)&frm_answer);
// 		break;
//         case FUNCSTOP:
// 		onstop();
// 		vtcp_srvsend(CONFIGPORT, income, sizeof(cfghead_t)+frm_answer.h.len, (char *)&frm_answer);
// 		break;
// 	case FUNCUCMD:
// 		c();
// 		vtcp_srvsend(CONFIGPORT, income, sizeof(cfghead_t)+frm_answer.h.len, (char *)&frm_answer);
// 	default:

static int on_bus_connect()
{

}
static int on_bus_disconnect()
{

}

static int on_bus_reset()
{

}
static int on_bus_run()
{
  
}
static int on_bus_stop()
{
  
}
static int on_bus_upload()
{
  
}
static bool filter_service(std::string host_name, std::string host_ip,
                           std::string process_id, std::string prj_name) {

return true;
}

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
  auto prj_cmd_srv =
      node->CreateService<Bus::ProjectCmdReq, Bus::ProjectCmdRsp>(
          FLAGS_prj_cmd_name,
          [](const std::shared_ptr<Bus::ProjectCmdReq> &request,
             std::shared_ptr<Bus::ProjectCmdRsp> &response) {
            std::cout << "prject  cmd" << std::endl;


          });
}



int bus_uninit() {}

#endif