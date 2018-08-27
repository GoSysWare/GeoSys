#ifndef LIB_UTILS_EXPORTS
#define LIB_UTILS_EXPORTS
#endif // !LIB_UTILS_EXPORTS
#include"geoAssert.h"
#include"geoLogMsg.h"

void __geo_assert(const char *file, int line, const geoTChar *expression)
{
	int error = GeoLog::last_error_adapter();
	GEO_LOG->set(file, line, error);

	GEO_LOG->log (LM_ERROR, GEO_TEXT("GEO_ASSERT: file %N, line %l assertion failed for '%s'.%a\n"), expression, -1);
}