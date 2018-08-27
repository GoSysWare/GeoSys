

#include "k_project.h"
#include "k_command.h"
#include <k_process.h>

#include "stdlib.h"


static char line[80];
static int parse_line(char *line)
{
	char line1[80];
	if (strcmp(line, "quit") == 0) {
		return 0;
	}

	sprintf(line1, "0;%s", line);
	cmd_dispatch(line1);
	return 1;
}


int main(int argc, char *argv[])
{
	int i;
	for (i = 1; i < argc; i++) {
		if (strcmp(argv[i], "-a") == 0) {
			prj_info()->id_stb = 0xa;
		}
		else if (strcmp(argv[i], "-b") == 0) {
			prj_info()->id_stb = 0xb;
		}
		else {
			prj_info()->id_stb = 0xc;
		}
		if (strcmp(argv[i], "-dn") == 0) {
			vnet_init();
			vnet_dump_ifs();
			return 0;
		}
	}

	vnet_init();
	vtcp_init();
	cfgbus_init(1);
	stbbus_init();
	vudp_init();
	io_init();
	lib_init();
	prj_init(1);

	//if (-1 != cmds_load(cmdsbuf, sizeof(cmdsbuf) - 1)) {
		//cmds_dispatch(cmdsbuf);
	//}
	//else {
		//cmds_dispatch("0;setprj;{00000000-0000-0000-0000-00000000};");
	//}
	//String cmdLine="0;dumpimg;,;,";
	///cmd_dispatch(":0;dumpimg;,;,");
	//        while(1){
	//	k_sleep(1000);
	//}
	printf("prj_main_loop start.\n");

	k_thread_start(prj_main_loop, 0);

	//do {
	//	printf("-");
	//	gets(line);
	//} while (parse_line(line));

	while (!_kbhit())
	{
		k_sleep(3000);
	}
	//prj_main_loop();
}