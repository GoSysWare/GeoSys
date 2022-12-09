#ifndef k_command_h
#define k_command_h

#include "modules/calc/proto/cmd.pb.h"
#include "modules/calc/proto/edit.pb.h"

int cmd_dispatch(const Bus::EditInfo &edit_info);
int cmds_dispatch(const Bus::EditInfosReq &edit_infos);

int cmds_reset();
int cmds_load(char *buf, int len);
int cmds_append(char *buf, int len);




#endif


