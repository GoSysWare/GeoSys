#ifndef GDEFINE_H
#define GDEFINE_H

#include "plmainframe.h"
#include "plmainmodel.h"
#include "pltarget.h"
#include "cyber/cyber.h"

extern PLMainFrame *gMainFrame;
extern PLMainModel *gMainModel;
extern PLTarget *gTarget;
extern std::shared_ptr<apollo::cyber::Node> gNode;
extern std::shared_ptr<apollo::cyber::Client<Bus::EditInfosReq, Bus::EditInfosRsp>> gclient_proj_eidt;

extern std::shared_ptr<apollo::cyber::Client<Bus::ProjectInfoReq, Bus::ProjectInfoRsp>> gclient_proj_info;
extern std::shared_ptr<apollo::cyber::Client<Bus::ProjectCmdReq, Bus::ProjectCmdRsp>> gclient_proj_cmd;


#endif // GDEFINE_H
