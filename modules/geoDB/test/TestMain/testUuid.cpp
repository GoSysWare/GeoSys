

#include <stdio.h>

#pragma comment(lib,"geoUuid.lib")
#include"../../src/geoUuid/uuid.h"


int to_string(char * buffer,uuid_t * data)
{
	unsigned int * l = (unsigned int*)data;
	unsigned int i;
	i = sprintf(buffer, "%08x-", *l);
	l++;
	unsigned short * s = (unsigned short *)l;
	i += sprintf(buffer + i, "%04x-", *s);
	s++;
	i += sprintf(buffer + i, "%04x-", *s);
	s++;
	unsigned char *c = (unsigned char*)s;
	i += sprintf(buffer + i, "%02x", *c);
	c++;
	for (int j = 1; j<8; j++, c++) {
		i += sprintf(buffer + i, "%02x", *c);
	}
	return i;
}

extern int run_main(int argc, char** argv)
{
	uuid_t out, out1, out2; 
	char buff[32] = { 0 },buff1[32] = { 0 }, buff2[32] = { 0 };
	uuid_generate(out);
	to_string(buff, &out);

	uuid_generate_random( out1);
	to_string(buff1, &out1);
	uuid_generate_time(out2);
	to_string(buff2, &out2);
	return 0;
}
int main(int argc, char** argv)
{
	run_main(argc, argv);

	return 0;
}