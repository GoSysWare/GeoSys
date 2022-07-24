#ifndef LIB_UTILS_EXPORTS
#define LIB_UTILS_EXPORTS
#endif // !1
#include "geoStdio.h"
#include <stdarg.h>

// The following *printf functions aren't inline because
// they use varargs.
int GEO_CALL geo_fprintf(FILE *fp, const char *format, ...)
{
	va_list ap;
	va_start(ap, format);
	int const result = ::vfprintf(fp, format, ap);
	va_end(ap);
	return result;
}

int GEO_CALL geo_fprintf(FILE *fp, const wchar_t *format, ...)
{

	va_list ap;
	va_start(ap, format);
	int const result = ::vfwprintf(fp, format, ap);
	va_end(ap);
	return result;
}



int GEO_CALL geo_printf(const char *format, ...)
{

	va_list ap;
	va_start(ap, format);
	int const result = ::vprintf(format, ap);
	va_end(ap);
	return result;
}


int GEO_CALL geo_printf(const wchar_t *format, ...)
{
	va_list ap;
	va_start(ap, format);
	int const result = ::vwprintf(format, ap);
	va_end(ap);
	return result;
}



int GEO_CALL geo_snprintf(char *buf, size_t maxlen, const char *format, ...)
{

	va_list ap;
	va_start(ap, format);
	int const result = ::vsnprintf(buf, maxlen, format, ap);
	va_end(ap);
	return result;

}



int GEO_CALL geo_snprintf(wchar_t *buf, size_t maxlen, const wchar_t *format, ...)
{

	va_list ap;
	va_start(ap, format);
	int const result = ::geo_vsnprintf(buf, maxlen, format, ap);
	va_end(ap);
	return result;

}


int GEO_CALL geo_sprintf(char *buf, const char *format, ...)
{

	va_list ap;
	va_start(ap, format);
	int const result = ::vsprintf(buf, format, ap);
	va_end(ap);
	return result;

}


int GEO_CALL geo_sprintf(wchar_t *buf, const wchar_t *format, ...)
{

	va_list ap;
	va_start(ap, format);
	int const result = ::vswprintf(buf, format, ap);
	va_end(ap);
	return result;

}



 int GEO_CALL geo_vprintf(const char *format, va_list argptr)
{
	return ::vprintf(format, argptr);
}


 int GEO_CALL geo_vprintf(const wchar_t *format, va_list argptr)
{
	return ::vwprintf(format, argptr);
}


 int GEO_CALL  geo_vfprintf(FILE *fp, const char *format, va_list argptr)
{

	return ::vfprintf(fp, format, argptr);
}


 int GEO_CALL geo_vfprintf(FILE *fp, const wchar_t *format, va_list argptr)
{
	return ::vfwprintf(fp, format, argptr);
}


 int  GEO_CALL geo_vsprintf(char *buffer, const char *format, va_list argptr)
{
	return ::vsprintf(buffer, format, argptr);
}

 int GEO_CALL geo_vsprintf(wchar_t *buffer, const wchar_t *format, va_list argptr)
{
	return vswprintf(buffer, format, argptr);
}


 int GEO_CALL geo_vsnprintf(char *buffer, size_t maxlen, const char *format, va_list ap)
{
	int result;
	result = ::vsnprintf(buffer, maxlen, format, ap);
	if (result == -1)
	{
		result = static_cast <int> (maxlen + 1);
	}
	return result;
}


 int GEO_CALL geo_vsnprintf(wchar_t *buffer, size_t maxlen, const wchar_t *format, va_list ap)
{
	int result;
# if defined (_WIN32) 
	result = ::_vsnwprintf(buffer, maxlen, format, ap);
	if (result == static_cast<int> (maxlen) && maxlen > 0)
		buffer[maxlen - 1] = '\0';

	if (result == -1 && maxlen > 0)
		buffer[maxlen - 1] = '\0';
# else
	result = vswprintf(buffer, maxlen, format, ap);
#endif
	return result;
}

#if defined (_WIN32)
 LPSECURITY_ATTRIBUTES GEO_CALL geo_default_win32_sa(LPSECURITY_ATTRIBUTES sa)
 {
	 if (sa == 0)
	 {
		 // @@ This is a good place to use pthread_once.
		 static SECURITY_ATTRIBUTES default_sa;
		 static SECURITY_DESCRIPTOR sd;
		 InitializeSecurityDescriptor(&sd, SECURITY_DESCRIPTOR_REVISION);
		 SetSecurityDescriptorDacl(&sd, TRUE, 0, FALSE);
		 default_sa.nLength = sizeof(SECURITY_ATTRIBUTES);
		 default_sa.lpSecurityDescriptor = &sd;
		 default_sa.bInheritHandle = TRUE;
		 sa = &default_sa;
	 }
	 return sa;
 }

 LPSECURITY_ATTRIBUTES GEO_CALL geo_default_win32_sa_r(LPSECURITY_ATTRIBUTES sa,
		 LPSECURITY_ATTRIBUTES sa_buffer,
		 SECURITY_DESCRIPTOR* sd_buffer)
 {
	 if (sa == 0)
	 {
		 if (sa_buffer != 0 && sd_buffer != 0)
		 {
			 InitializeSecurityDescriptor
			 (sd_buffer, SECURITY_DESCRIPTOR_REVISION);
			 SetSecurityDescriptorDacl(sd_buffer, TRUE, 0, FALSE);
			 sa_buffer->nLength = sizeof(SECURITY_ATTRIBUTES);
			 sa_buffer->lpSecurityDescriptor = sd_buffer;
			 sa_buffer->bInheritHandle = TRUE;
			 sa = sa_buffer;
		 }
	 }
	 return sa;
 }
#endif