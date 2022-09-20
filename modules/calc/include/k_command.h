#ifndef k_command_h
#define k_command_h

#include "modules/calc/proto/cmd.pb.h"

int cmd_dispatch(Cmd::EditInfo &edit_info);
int cmds_dispatch(Cmd::EditInfos &edit_infos);

int cmds_reset();
int cmds_load(char *buf, int len);
int cmds_append(char *buf, int len);


#endif


