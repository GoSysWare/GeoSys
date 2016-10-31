#ifndef LIB_UTILS_EXPORTS
#define LIB_UTILS_EXPORTS
#endif // !LIB_UTILS_EXPORTS

#include"geoUnistd.h"

#if !defined (_WIN32)
#include <unistd.h>
#else

#endif

//R_OK 4 /* Test for read permission. */
//W_OK 2 /* Test for write permission. */
//X_OK 1 /* Test for execute permission. */
//F_OK 0 /* Test for existence. */

int GEO_CALL geo_access(const char *path, int amode)
{

#if defined(_WIN32)
	return ::_access(path, amode & 6);
#else
	return ::access(path, amode);

#endif 
}


#if defined (_UNICODE)
int GEO_CALL geo_access(const wchar_t *path, int amode)
{
#if defined(_WIN32)
	return ::_waccess(path, amode & 6);
#else
	return ::access(GeoW2A(path).char_rep(), amode);
#endif
}
#endif 


struct tm * GEO_CALL geo_localtime_r(const time_t *t, struct tm *res)
{
#if defined _WIN32
	errno_t ___ = localtime_s(res, t);
	if (___ != 0) {
		errno = ___;
		res = 0;
	}
	return res;
#else
	return(struct tm *)::localtime_r(t, res);
#endif 
}

 pid_t GEO_CALL  geo_getpid(void)
{
#if defined (_WIN32)
	return ::GetCurrentProcessId();
#else
	return ::getpid()
#endif
}