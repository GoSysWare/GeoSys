
#include "geoGetOpt.hh"

#pragma comment(lib,"geoUtils.lib")



#include <stdio.h>

char *l_opt_arg;
char* const short_options = "nbl:";
struct option long_options[] = {
	{ "name", 0, NULL, 'n' },
	{ "bf_name", 0, NULL, 'b' },
	{ "love", 1, NULL, 'l' },
	{ 0, 0, 0, 0 },
};

int run_main(int argc, char** argv)
{
	int c;
	int index = 0;
	while ((c = getopt_long(argc, argv, short_options, long_options, NULL)) != -1)
	{
		switch (c)
		{
		case 'n':
			printf("My name is XL.\n");
			break;
		case 'b':
			printf("His name is ST.\n");
			break;
		case 'l':
			l_opt_arg = optarg;
			printf("Our love is %s!\n", l_opt_arg);
			break;
		}
	}

	//最后检测命令行给的选项是否已经解析完
	//optind是当前解析到选项的索引
	//判断依据是如果解析的个数小于argc，那么就是没有解析完
	for (index = optind; index < argc; index++)
	{
		printf("未定义的参数： %s\n", argv[index]);
	}



	return 0;

}
int main(int argc, char** argv)
{
	run_main(argc, argv);

	return 0;
}