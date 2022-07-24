#ifndef k_command_h
#define k_command_h
#ifdef __cplusplus
extern "C" {
#endif

int cmd_dispatch(char *line);
int cmds_dispatch(char *buf);

int cmds_reset();
int cmds_load(char *buf, int len);
int cmds_append(char *buf, int len);

#ifdef __cplusplus
}
#endif
#endif


