
#include "geoStdio.h"
#include <stdarg.h>

// The following *printf functions aren't inline because
// they use varargs.
int geo_fprintf(FILE *fp, const char *format, ...)
{
	va_list ap;
	va_start(ap, format);
	int const result = ::vfprintf(fp, format, ap);
	va_end(ap);
	return result;
}

int geo_fprintf(FILE *fp, const wchar_t *format, ...)
{

	va_list ap;
	va_start(ap, format);
	int const result = ::vfwprintf(fp, format, ap);
	va_end(ap);
	return result;
}



int geo_printf(const char *format, ...)
{

	va_list ap;
	va_start(ap, format);
	int const result = ::vprintf(format, ap);
	va_end(ap);
	return result;
}


int geo_printf(const wchar_t *format, ...)
{
	va_list ap;
	va_start(ap, format);
	int const result = ::vwprintf(format, ap);
	va_end(ap);
	return result;
}



int geo_snprintf(char *buf, size_t maxlen, const char *format, ...)
{

	va_list ap;
	va_start(ap, format);
	int const result = ::vsnprintf(buf, maxlen, format, ap);
	va_end(ap);
	return result;

}



int geo_snprintf(wchar_t *buf, size_t maxlen, const wchar_t *format, ...)
{

	va_list ap;
	va_start(ap, format);
	int const result = ::geo_vsnprintf(buf, maxlen, format, ap);
	va_end(ap);
	return result;

}


int geo_sprintf(char *buf, const char *format, ...)
{

	va_list ap;
	va_start(ap, format);
	int const result = ::vsprintf(buf, format, ap);
	va_end(ap);
	return result;

}


int geo_sprintf(wchar_t *buf, const wchar_t *format, ...)
{

	va_list ap;
	va_start(ap, format);
	int const result = ::vswprintf(buf, format, ap);
	va_end(ap);
	return result;

}



 int geo_vprintf(const char *format, va_list argptr)
{
	return ::vprintf(format, argptr);
}


 int geo_vprintf(const wchar_t *format, va_list argptr)
{
	return ::vwprintf(format, argptr);
}


 int geo_vfprintf(FILE *fp, const char *format, va_list argptr)
{

	return ::vfprintf(fp, format, argptr);
}


 int geo_vfprintf(FILE *fp, const wchar_t *format, va_list argptr)
{
	return ::vfwprintf(fp, format, argptr);
}


 int  geo_vsprintf(char *buffer, const char *format, va_list argptr)
{
	return ::vsprintf(buffer, format, argptr);
}

 int geo_vsprintf(wchar_t *buffer, const wchar_t *format, va_list argptr)
{
	return vswprintf(buffer, format, argptr);
}


 int geo_vsnprintf(char *buffer, size_t maxlen, const char *format, va_list ap)
{
	int result;
	result = ::vsnprintf(buffer, maxlen, format, ap);
	if (result == -1)
	{
		result = static_cast <int> (maxlen + 1);
	}
	return result;
}


 int geo_vsnprintf(wchar_t *buffer, size_t maxlen, const wchar_t *format, va_list ap)
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
