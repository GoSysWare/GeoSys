
#ifndef LIB_UTILS_EXPORTS
#define LIB_UTILS_EXPORTS
#endif // !LIB_UTILS_EXPORTS
#include"geoErrno.h"
#include<errno.h> 
#ifdef _WIN32
#include <windows.h>
#pragma comment(lib, "ws2_32.lib")
#else

#endif // 
 int GEO_CALL last_error(void)
{

#if defined (_WIN32)
	// ACE_OS::last_error() prefers errnor since started out as a way to
	// avoid directly accessing errno in ACE code - particularly the ACE
	// C++ socket wrapper facades.  On Windows, some things that would
	// use errno on UNIX require ::GetLastError(), so this method tries
	// to shield the rest of ACE from having to know about this.
	int const lerror = ::GetLastError();
	int const lerrno = errno;
	return lerrno == 0 ? lerror : lerrno;
#else
	return errno;
#endif /* ACE_WIN32 */
}


 void GEO_CALL set_last_error(int error)
{
#if defined (_WIN32)
	::SetLastError(error);
#endif 
	errno = error;
}

 int GEO_CALL set_errno_to_last_error(void)
{
# if defined (_WIN32)
	return errno = ::GetLastError();
#else
	return errno;
# endif 
}

 int GEO_CALL set_errno_to_wsa_last_error(void)
{
# if defined (_WIN32)
	return errno = ::WSAGetLastError();
#else
	return errno;
# endif 
}