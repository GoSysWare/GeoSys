
#ifndef LIB_UTILS_EXPORTS
#define LIB_UTILS_EXPORTS
#endif // !LIB_UTILS_EXPORTS
#include "geoUtils.h"

geoUInt32 geo_log2(geoUInt32 num)
{
	geoUInt32 log = 0;

	for (; num > 1; ++log)
		num >>= 1;

	return log;
}