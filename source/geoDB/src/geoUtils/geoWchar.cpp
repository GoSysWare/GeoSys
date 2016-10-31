#ifndef LIB_UTILS_EXPORTS
#define LIB_UTILS_EXPORTS
#endif // !LIB_UTILS_EXPORTS

#include "geoWchar.h"

#if !defined (_WIN32)
#include<string.h>
#else
#include <windows.h>
#endif


#if defined(__linux__)
iconv_t GeoW2A::W2A_iconv_env = 0;
iconv_t GeoA2W::A2W_iconv_env = 0;
#endif

inline GeoW2A::GeoW2A(const wchar_t *s)
{
#if defined(__linux__)
	if (W2A_iconv_env == 0)
	{
		W2A_iconv_env = iconv_open("", "WCHAR_T");
	}
#endif
	s_ = GeoW2A::convert(s);
}

inline GeoW2A::~GeoW2A(void)
{
	delete[] this->s_;
}

inline char *
GeoW2A::char_rep(void)
{
	return this->s_;
}

inline char *
GeoW2A::convert(const wchar_t *wstr)
{
	// Short circuit null pointer case
	if (wstr == 0)
		return 0;

# if defined (_WIN32)
	UINT const cp = GetACP();  // Codepage
	int const len = ::WideCharToMultiByte(cp,
		0,
		wstr,
		-1,
		0,
		0,
		0,
		0);
	char *str = new char[len];
	::WideCharToMultiByte(cp, 0, wstr, -1, str, len, 0, 0);
# else 
	size_t const len = ::wcslen(wstr) + 1;
	wchar_t * wstri = const_cast<wchar_t*> (wstr);
	size_t lensi = MAX_ICONV_BUFFER;
	size_t lenwi = len * sizeof(wchar_t);
	char buf[MAX_ICONV_BUFFER];
	char *stri = buf;

	size_t hr = iconv(W2A_iconv_env, (char**)&wstri, &lenwi, &stri, &lensi);
	if ((hr == size_t(-1)) || (lensi == MAX_ICONV_BUFFER))
	{
		char *str = new char[len];
		for (size_t i = 0; i < len; i++)
		{
			wchar_t *t = const_cast <wchar_t *> (wstr);
			str[i] = static_cast<char> (*(t + i));
		}

		return str;
	}
	char *str = new char[MAX_ICONV_BUFFER - lensi];
	::memcpy(str, buf, MAX_ICONV_BUFFER - lensi);
#endif

	return str;
}

inline
GeoA2W::GeoA2W(const char *s)
{
#if defined(__linux__)
	if (A2W_iconv_env == 0)
	{
		A2W_iconv_env = iconv_open("WCHAR_T", "");
	}
#endif
	s_ = GeoA2W::convert(s);
}

inline
GeoA2W::~GeoA2W(void)
{
	delete[] this->s_;
}

inline wchar_t *
GeoA2W::wchar_rep(void)
{
	return this->s_;
}

inline wchar_t *
GeoA2W::convert(const char *str)
{
	// Short circuit null pointer case
	if (str == 0)
		return 0;

# if defined (_WIN32)
	UINT const cp = GetACP();  // Codepage
	int const len = ::MultiByteToWideChar(cp, 0, str, -1, 0, 0);
	wchar_t *wstr = new wchar_t[len];
	::MultiByteToWideChar(cp, 0, str, -1, wstr, len);
# else 
	size_t const len = strlen(str) + 1;
	char *stri = const_cast<char*>(str);
	size_t lensi = len;
	size_t lenwi = MAX_ICONV_BUFFER;
	wchar_t buf[MAX_ICONV_BUFFER / sizeof(wchar_t)];
	wchar_t *wstri = buf;

	size_t hr = iconv(A2W_iconv_env, &stri, &lensi, (char**)&wstri, &lenwi);
	if ((hr == size_t(-1)) || (lenwi == MAX_ICONV_BUFFER)) {
		wchar_t *wstr = new wchar_t[len * sizeof(wchar_t)];
		for (size_t i = 0; i < len; i++) {
			char *t = const_cast<char *> (str);
			wstr[i] = static_cast<wchar_t> (*((unsigned char*)t + i));
		}

		return wstr;
	}
	wchar_t *wstr = new wchar_t[(MAX_ICONV_BUFFER - lenwi) / sizeof(wchar_t)];
	::memcpy(wstr, buf, MAX_ICONV_BUFFER - lenwi);
#endif
	return wstr;
}

