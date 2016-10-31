/*****************************************************************************
*  GeoSysWare	Basic tool library											 *
*  Copyright (C) 2016 George.Kuo  guooujie@163.com.							 *
*                                                                            *
*  This file is part of GeoSys.                      *
*                                                                            *
*  @file     geoString.h                                                     *
*  @brief    平台相关的string操作API                                                      *
*																			 *
*  封装 access getpagesize chdir rmdir  close execv 等API
*
*  @author   George.Kuo                                                      *
*  @email    guooujie@163.com												 *
*  @version  1.0.0.1(版本号)                                                 *
*  @date     2016.8															 *
*  @license																	 *
*                                                                            *
*----------------------------------------------------------------------------*
*  Remark         : 必须在支持C++11环境下编译通过                            *
*----------------------------------------------------------------------------*
*  Change History :                                                          *
*  <Date>     | <Version> | <Author>       | <Description>                   *
*----------------------------------------------------------------------------*
*  2016/08/24 | 1.0.0.1   | George.Kuo      | Create file                    *
*----------------------------------------------------------------------------*
*                                                                            *
*****************************************************************************/
#ifndef  GEOSYS_UTILS_STRING_H__
#define  GEOSYS_UTILS_STRING_H__

#include <string>
#include "geoWchar.h"
#include <stdlib.h>

inline
geoChar* geo_strupr(geoChar * str)
{
		char *orign = str;
		for (; *str != '\0 '; str++)
			*str = toupper(*str);
		return orign;
}

inline
char *geo_strcat(char *s, const char *t)
{
	return ::strcat(s, t);
}

inline
wchar_t *geo_strcat(wchar_t *s, const wchar_t *t)
{
	return ::wcscat(s, t);
}
inline
const char *geo_strchr(const char *s, int c)
{
	return const_cast <const char *> (::strchr(s, c));
}
inline
const wchar_t *geo_strchr(const wchar_t *s, wchar_t c)
{
	return const_cast<wchar_t *> (geo_strchr(const_cast<const wchar_t *> (s), c));

}
inline
char *geo_strchr(char *s, int c)
{
	return ::strchr(s, c);
}
inline
wchar_t *geo_strchr(wchar_t *s, wchar_t c)
{
	return ::wcschr(s, c);
}

inline
int geo_strcmp(const char *s, const char *t)
{
	return ::strcmp(s, t);
}
inline
int geo_strcmp(const wchar_t *s, const wchar_t *t)
{
	return ::wcscmp(s, t);
}

inline
char *geo_strcpy(char *s, const char *t)
{
	return ::strcpy(s, t);
}
inline
wchar_t *geo_strcpy(wchar_t *s, const wchar_t *t)
{
	return ::wcscpy(s, t);
}

inline
size_t geo_strcspn(const char *s, const char *reject)
{
	return ::strcspn(s, reject);
}

inline
size_t geo_strcspn(const wchar_t *s, const wchar_t *reject)
{
	return ::wcscspn(s, reject);
}
inline
char *geo_strdup(const char *s)
{
	return ::strdup(s);
}

inline
wchar_t *geo_strdup(const wchar_t *s)
{
	return ::wcsdup(s);
}


inline
char *geo_strecpy(char *des, const char *src)
{
	 char *dscan = des;
	 const char *sscan = des;

	while ((*dscan++ = *sscan++) != '\0')
		continue;

	return dscan;
}
inline
wchar_t *geo_strecpy(wchar_t *s, const wchar_t *t)
{
	 wchar_t *dscan = s;
	 const wchar_t *sscan = t;

	while ((*dscan++ = *sscan++) != GEO_TEXT_WIDE('\0'))
		continue;

	return dscan;

}


inline
size_t geo_strlen(const char *s)
{
	return ::strlen(s);
}
inline
size_t geo_strlen(const wchar_t *s)
{
	return ::wcslen(s);
}

inline
char *geo_strncat(char *s, const char *t, size_t len)
{
	return ::strncat(s, t, len);
}
inline
wchar_t *geo_strncat(wchar_t *s, const wchar_t *t, size_t len)
{
	return ::wcsncat(s, t, len);
}

inline
const char *geo_strnchr(const char *s, int c, size_t len)
{
	for (size_t i = 0; i < len; ++i)
		if (s[i] == c)
			return s + i;

	return 0;
}

inline
const wchar_t *geo_strnchr(const wchar_t *s, wchar_t c, size_t len)
{
	for (size_t i = 0; i < len; ++i)
	{
		if (s[i] == c)
		{
			return s + i;
		}
	}

	return 0;
}

inline
char *geo_strnchr(char *s, int c, size_t len)
{
	return const_cast<char *> (geo_strnchr(static_cast<const char *> (s),
		c,
		len));

}

inline
wchar_t *strnchr(wchar_t *s, wchar_t c, size_t len)
{
	return
		const_cast<wchar_t *> (geo_strnchr(
			const_cast<const wchar_t *> (s),
			c,
			len));
}

inline
int geo_strncmp(const char *s, const char *t, size_t len)
{
	return ::strncmp(s, t, len);
}

inline
int geo_strncmp(const wchar_t *s, const wchar_t *t, size_t len)
{
	return ::wcsncmp(s, t, len);
}

inline
char *geo_strncpy(char *s, const char *t, size_t len)
{
	return ::strncpy(s, t, len);
}
inline
wchar_t *geo_strncpy(wchar_t *s, const wchar_t *t, size_t len)
{
	return ::wcsncpy(s, t, len);
}

inline
size_t geo_strnlen(const char *s, size_t maxlen)
{
	return ::strnlen(s, maxlen);
}

inline
size_t geo_strnlen(const wchar_t *s, size_t maxlen)
{
	return ::wcsnlen(s, maxlen);
}

inline
const char *geo_strnstr(const char *s1, const char *s2, size_t len2)
{

	size_t const len1 = geo_strlen(s1);

	if (len2 > len1)
		return 0;

	size_t const len = len1 - len2;

	for (size_t i = 0; i <= len; i++)
	{
		if (::memcmp(s1 + i, s2, len2) == 0)
		{
			return s1 + i;
		}
	}

	return 0;

}

inline
const wchar_t *geo_strnstr(const wchar_t *s1,
	const wchar_t *s2,
	size_t len2)
{


	size_t const len1 = geo_strlen(s1);
	if (len2 > len1)
		return 0;

	size_t const len = len1 - len2;

	for (size_t i = 0; i <= len; i++)
	{
		if (::memcmp(s1 + i, s2, len2 * sizeof(wchar_t)) == 0)
		{
			return s1 + i;
		}
	}

	return 0;

}

inline
char *geo_strnstr(char *s, const char *t, size_t len)
{
	return  const_cast <char *> (geo_strnstr(const_cast <const char *> (s), t, len));
}

inline
wchar_t *geo_strnstr(wchar_t *s, const wchar_t *t, size_t len)
{
	return
		const_cast<wchar_t *> (geo_strnstr(
			static_cast<const wchar_t *> (s),
			t,
			len));
}

inline
const char *geo_strpbrk(const char *s1, const char *s2)
{
	return ::strpbrk(s1, s2);
}

inline
const wchar_t *geo_strpbrk(const wchar_t *s1, const wchar_t *s2)
{
	return ::wcspbrk(s1, s2);
}

inline
char *geo_strpbrk(char *s1, const char *s2)
{
	return ::strpbrk(s1, s2);
}
inline
wchar_t *geo_strpbrk(wchar_t *s1, const wchar_t *s2)
{
	return const_cast<wchar_t *> (geo_strpbrk(
		const_cast<const wchar_t *> (s1), s2));
}


inline
const char *geo_strrchr(const char *s, int c)
{
	return (const char *) ::strrchr(s, c);
}

inline
const wchar_t *geo_strrchr(const wchar_t *s, wchar_t c)
{
	return const_cast <const wchar_t *> (::wcsrchr(s, c));
}

inline
char *geo_strrchr(char *s, int c)
{
	return ::strrchr(s, c);
}

inline
wchar_t *geo_strrchr(wchar_t *s, wchar_t c)
{
	return const_cast<wchar_t *> (geo_strrchr(
		const_cast<const wchar_t *> (s), c));
}



inline
char *geo_strsncpy(char *dst,
	const char *src,
	size_t maxlen)
{
	return ::strncpy(dst, src, maxlen);
}

inline
wchar_t *geo_strsncpy(wchar_t *dst,
	const wchar_t *src,
	size_t maxlen)
{
	return ::wcsncpy(dst, src, maxlen);
}

inline
size_t geo_strspn(const char *s1, const char *s2)
{
	return ::strspn(s1, s2);
}

inline
size_t geo_strspn(const wchar_t *s1, const wchar_t *s2)
{
	return ::wcsspn(s1, s2);
}


inline
const char *geo_strstr(const char *s, const char *t)
{
	return (const char *) ::strstr(s, t);
}
inline
const wchar_t *geo_strstr(const wchar_t *s, const wchar_t *t)
{
	return const_cast <const wchar_t *> (::wcsstr(s, t));
}


inline
char *geo_strstr(char *s, const char *t)
{
	return ::strstr(s, t);
}

inline
wchar_t *geo_strstr(wchar_t *s, const wchar_t *t)
{
	return ::wcsstr(s, t);
}


inline
char *geo_strtok(char *s, const char *tokens)
{
	return ::strtok(s, tokens);
}

inline
wchar_t *geo_strtok(wchar_t *s, const wchar_t *tokens)
{
	static wchar_t *lasts = 0;
	return ::wcstok(s, tokens, &lasts);
}
inline
char *geo_strtok_r(char *s, const char *tokens, char **lasts)
{
#ifdef _WIN32
	return ::strtok_s(s, tokens, lasts);
#else
	return ::strtok_r(s, tokens, lasts);
#endif // _WIN32

}
inline
wchar_t *geo_strtok_r(wchar_t *s, const wchar_t *tokens, wchar_t **lasts)
{
	return ::wcstok(s, tokens, lasts);
}



#endif
