

#include "geoBasicType.h"
#pragma comment(lib,"geoUtils.lib")
#include "../src/geoRtdbKernel/geoTagMap.h"
#include "../src/geoRtdbKernel/geoTagBaseProp.h"
int run_main(int argc, char** argv);

int run_main(int argc, char** argv)
{

	GeoTagMap names;
	GeoBaseTagProp tags(&names);
	tags.Init();
	geoPropValueList *list = geoNULL;
	geoAPIStatus *status = (geoAPIStatus *)malloc(sizeof(geoAPIStatus) * 5);
	memset(status, 0, sizeof(geoAPIStatus) * 5);
	geoUInt32 tagid;
	NewPropValueListEx(&list, 5);
	list->PropValueList[0].PropId = geoProp_TagType;
	list->PropValueList[0].Value.varType = geoVarTypeEnum::vTypeUInt8;
	list->PropValueList[0].Value.vUInt8 = TagType_Comm;

	list->PropValueList[1].PropId = geoProp_Name;
	list->PropValueList[1].Value.varType = geoVarTypeEnum::vTypeString;
	list->PropValueList[1].Value.vString.Length = strlen("Tag3");
	//字符串类型的Variant要注意内存的释放者是谁
	NewAndCopyStr(&list->PropValueList[1].Value.vString.Data, "Tag3");

	list->PropValueList[2].PropId = geoProp_DataType;
	list->PropValueList[2].Value.varType = geoVarTypeEnum::vTypeUInt8;
	list->PropValueList[2].Value.vUInt8 = (geoUInt8)geoVarTypeEnum::vTypeInt32;

	list->PropValueList[3].PropId = geoProp_Unit;
	list->PropValueList[3].Value.varType = geoVarTypeEnum::vTypeUInt8;
	list->PropValueList[3].Value.vUInt8 = (geoUInt8)23;

	list->PropValueList[4].PropId = geoProp_InitValue;
	list->PropValueList[4].Value.varType = geoVarTypeEnum::vTypeDouble;
	list->PropValueList[4].Value.vDouble = 45.00;

	tags.AddTag(list, &tagid, status);
	FreePropValueList(&list);
	tags.UnInit();
	return 0;

}
int main(int argc, char** argv)
{
	run_main(argc, argv);

	return 0;
}
