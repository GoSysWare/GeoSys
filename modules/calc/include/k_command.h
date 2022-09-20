#ifndef k_command_h
#define k_command_h

#include "modules/calc/proto/cmd.pb.h"

int cmd_dispatch(Cmd::EditInfo &edit_info);
int cmds_dispatch(Cmd::EditInfos &edit_infos);

int cmds_reset();
int cmds_load(char *buf, int len);
int cmds_append(char *buf, int len);



//  if (strcasecmp(word, "addprg") == 0) {
//     return addprg(line, &cursor);
//   } else if (strcasecmp(word, "rmprg") == 0) {
//     return rmprg(line, &cursor);
//   } else if (strcasecmp(word, "addev") == 0) {
//     return addev(line, &cursor);
//   } else if (strcasecmp(word, "rmev") == 0) {
//     return rmev(line, &cursor);
//   } else if (strcasecmp(word, "addfb") == 0) {
//     return addfb(line, &cursor);
//   } else if (strcasecmp(word, "rmfb") == 0) {
//     return rmfb(line, &cursor);
//   } else if (strcasecmp(word, "addlk") == 0) {
//     return addlk(line, &cursor);
//   } else if (strcasecmp(word, "rmlk") == 0) {
//     return rmlk(line, &cursor);
//   } else if (strcasecmp(word, "addvi") == 0) {
//     return addvi(line, &cursor);
//   } else if (strcasecmp(word, "rmvi") == 0) {
//     return rmvi(line, &cursor);
//   } else if (strcasecmp(word, "addvo") == 0) {
//     return addvo(line, &cursor);
//   } else if (strcasecmp(word, "rmvo") == 0) {
//     return rmvo(line, &cursor);
//   } else if (strcasecmp(word, "setpin") == 0) {
//     return setpin(line, &cursor);
//   } else if (strcasecmp(word, "setev") == 0) {
//     return setev(line, &cursor);
//   } else if (strcasecmp(word, "showprj") == 0) {
//     return showprj();
//   } else if (strcasecmp(word, "showlib") == 0) {
//     return showlib();
//   } else if (strcasecmp(word, "showev") == 0) {
//     return showevlist();
//   } else if (strcasecmp(word, "showprg") == 0) {
//     return showprg(line, &cursor);
//   } else if (strcasecmp(word, "showfb") == 0) {
//     return showfb(line, &cursor);
//   } else if (strcasecmp(word, "run") == 0) {
//     return run();
//   } else if (strcasecmp(word, "stop") == 0) {
//     return stop();
//   } else if (strcasecmp(word, "help") == 0) {
//     return help();
//   } else if (strcasecmp(word, "setprj") == 0) {
//     return setprj(line, &cursor);
//   } else if (strcasecmp(word, "dumpimg") == 0) {
//     return dumpimg();
//   }

#endif


