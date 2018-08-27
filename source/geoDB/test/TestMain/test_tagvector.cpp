
#include "../src/geoRTDBkernel/geoTagVector.h"
#pragma comment(lib,"geoUtils.lib")
int run_main(int argc, char** argv)
{
	GeoTagVector tagbase(0,500000);
	tagbase.Init();
	geoUInt32 tagId = geoTagId_Unused;
	for (geoUInt32 i = 0; i < 500000; i++)
	{
		tagbase.AddTag(&tagId);
	}
	tagbase.UnInit();



	return 0;

}
int main(int argc, char** argv)
{
	run_main(argc, argv);

	return 0;
}