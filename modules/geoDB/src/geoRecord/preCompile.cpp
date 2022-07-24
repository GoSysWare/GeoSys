#include "preCompile.h"


#ifdef _WIN32
#if defined _DEBUG
#pragma comment(lib,"libdb53d.lib")
#pragma comment(lib,"geoUtils.lib")
#else
#pragma comment(lib,"libdb53.lib")
#pragma comment(lib,"geoUtils.lib")
#endif

#endif // _WIN32
