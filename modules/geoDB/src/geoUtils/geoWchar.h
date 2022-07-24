/*****************************************************************************
*  GeoSysWare	Basic tool library											 *
*  Copyright (C) 2016 George.Kuo  guooujie@163.com.							 *
*                                                                            *
*  This file is part of GeoSys.  using C++ std::thread                       *
*                                                                            *
*  @file     geoWchar.h                                                     *
*  @brief    宽窄字符处理类                                                      *
*																			 *
*  GeeSys平台默认为ascii编码处理，降低字符串的内存，减少通信字节数
*  在有些文件处理、接口处理、通信处理时，						*
*  如读SQL的接口时有Unicode编码，需要转化为ascii编码			*
*  
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
#ifndef  GEOSYS_UTILS_WCHAR_H__
#define  GEOSYS_UTILS_WCHAR_H__

#include"geoBasicType.h"

#include <cwchar>
#include <cwctype>

#if defined (__linux__)
#  include  <iconv.h>
#    define MAX_ICONV_BUFFER   16*1024
#endif 


#if defined (_UNICODE)
# define GEO_TEXT_ALWAYS_CHAR(STRING) GeoW2A (STRING).char_rep ()
# define GEO_TEXT_ALWAYS_WCHAR(STRING) STRING
# define GEO_TEXT_CHAR_TO_TCHAR(STRING) GeoA2W (STRING).wchar_rep ()
# define GEO_TEXT_WCHAR_TO_TCHAR(STRING) STRING
# define GEO_TEXT_ANTI_TO_TCHAR(STRING) GeoA2W (STRING).wchar_rep ()
#else
# define GEO_TEXT_ALWAYS_CHAR(STRING) STRING
# define GEO_TEXT_ALWAYS_WCHAR(STRING) GeoA2W (STRING).wchar_rep ()
# define GEO_TEXT_CHAR_TO_TCHAR(STRING) STRING
# define GEO_TEXT_WCHAR_TO_TCHAR(STRING) GeoW2A (STRING).char_rep ()
# define GEO_TEXT_ANTI_TO_TCHAR(STRING) GeoW2A (STRING).char_rep ()
#endif 




// Define the Wide character and normal versions of some of the string macros
#if defined (_UNICODE)
#  define DIRECTORY_SEPARATOR_STR_W GEO_TEXT_WIDE(DIRECTORY_SEPARATOR_STR_A)
#  define DIRECTORY_SEPARATOR_CHAR_W GEO_TEXT_WIDE(DIRECTORY_SEPARATOR_CHAR_A)
#endif /* ACE_HAS_WCHAR */

#define DIRECTORY_SEPARATOR_STR GEO_TEXT (DIRECTORY_SEPARATOR_STR_A)
#define DIRECTORY_SEPARATOR_CHAR GEO_TEXT (DIRECTORY_SEPARATOR_CHAR_A)

class GeoW2A
{
public:
	/// Constructor must take a wchar string.
	GeoW2A(const wchar_t *s);

	/// Destructor will free up the memory.
	~GeoW2A(void);

	/// Return the internal char* representation.
	char *char_rep(void);

	/// Converts an wchar_t string to ascii and returns a new string.
	static char *convert(const wchar_t *wstr);

private:
	/// Internal pointer to the converted string.
	char *s_;

	#if defined (__linux__)
		static iconv_t W2A_iconv_env;
	#endif 

	/// Disallow these operation.
	GeoW2A(void) =delete;
	GeoW2A(GeoW2A &) = delete;
	GeoW2A& operator= (GeoW2A &) = delete;
};

class GeoA2W
{
public:
	/// Constructor must take a wchar string.
	GeoA2W(const char *s);

	/// Destructor will free up the memory.
	~GeoA2W(void);

	/// Return the internal wchar* representation.
	wchar_t *wchar_rep(void);

	/// Converts an char string to unicode/wide and returns a new string.
	static wchar_t *convert(const char *str);

private:
	/// Internal pointer to the converted string.
	wchar_t *s_;
#if defined (__linux__)
	static iconv_t A2W_iconv_env;
#endif 

	/// Disallow these operation.
	GeoA2W(void) = delete;
	GeoA2W(GeoA2W &) = delete;
	GeoA2W operator= (GeoA2W &) = delete;
};


#if defined (_WIN32)
#if defined (_UNICODE)
#define GEO_LPSTR                                LPWSTR
#define GEO_SERVICE_TABLE_ENTRY             SERVICE_TABLE_ENTRYW
#define GEO_STARTUPINFO                     STARTUPINFOW
#define GEO_WIN32_FIND_DATA                 WIN32_FIND_DATAW
#define GEO_OSVERSIONINFO                   OSVERSIONINFOW
#define GEO_EXPLICIT_ACCESS                 EXPLICIT_ACCESS_W

#define GEO_CreateEvent                     ::CreateEventW
#define GEO_CreateFile                      ::CreateFileW
#define GEO_CreateFileMapping               ::CreateFileMappingW
#define GEO_CreateMutex                     ::CreateMutexW
#define GEO_CreateProcess                   ::CreateProcessW
#define GEO_CreateSemaphore                 ::CreateSemaphoreW
#define GEO_CreateService                   ::CreateServiceW
#define GEO_ExpandEnvironmentStrings        ::ExpandEnvironmentStringsW
#define GEO_FindFirstChangeNotification     ::FindFirstChangeNotificationW
#define GEO_FindFirstFile                   ::FindFirstFileW
#define GEO_FindNextFile                    ::FindNextFileW
#define GEO_FormatMessage                   ::FormatMessageW
#define GEO_FreeEnvironmentStrings          ::FreeEnvironmentStringsW
#define GEO_GetComputerName                 ::GetComputerNameW
#define GEO_GetEnvironmentStrings           ::GetEnvironmentStringsW
#define GEO_GetFileAttributes               ::GetFileAttributesW
#define GEO_GetModuleFileName               ::GetModuleFileNameW
#define GEO_GetTempPath                     ::GetTempPathW
#define GEO_GetUserName                     ::GetUserNameW
#define GEO_GetUserNameEx                   ::GetUserNameExW
#define GEO_GetVersionEx                    ::GetVersionExW
#define GEO_LoadLibrary                     ::LoadLibraryW
#define GEO_MoveFileEx                      ::MoveFileExW
#define GEO_WaitNamedPipe                   ::WaitNamedPipeW
#define GEO_OpenFileMapping                 ::OpenFileMappingW
#define GEO_OpenSCManager                   ::OpenSCManagerW
#define GEO_OpenService                     ::OpenServiceW
#define GEO_OutputDebugString               ::OutputDebugStringW
#define GEO_RegisterEventSource             ::RegisterEventSourceW
#define GEO_RegisterServiceCtrlHandler      ::RegisterServiceCtrlHandlerW
#define GEO_RegConnectRegistry              ::RegConnectRegistryW
#define GEO_RegCreateKeyEx                  ::RegCreateKeyExW
#define GEO_RegDeleteKey                    ::RegDeleteKeyW
#define GEO_RegDeleteValue                  ::RegDeleteValueW
#define GEO_RegEnumKeyEx                    ::RegEnumKeyExW
#define GEO_RegEnumValue                    ::RegEnumValueW
#define GEO_RegCreateKey                    ::RegCreateKeyW
#define GEO_RegOpenKey                      ::RegOpenKeyW
#define GEO_RegOpenKeyEx                    ::RegOpenKeyExW
#define GEO_RegQueryValueEx                 ::RegQueryValueExW
#define GEO_RegSetValueEx                   ::RegSetValueExW
#define GEO_ReportEvent                     ::ReportEventW
#define GEO_SearchPath                      ::SearchPathW
#define GEO_StartService                    ::StartServiceW
#define GEO_StartServiceCtrlDispatcher      ::StartServiceCtrlDispatcherW
#define GEO_SetFileSecurity                 ::SetFileSecurityW
#define GEO_SetEntriesInAcl                 ::SetEntriesInAclW
#define GEO_PdhExpandCounterPath            ::PdhExpandCounterPathW
#define GEO_PdhOpenQuery                    ::PdhOpenQueryW
#define GEO_PdhAddCounter                   ::PdhAddCounterW
#define GEO_gai_strerror                    ::gai_strerrorW

#else 
#define GEO_LPSTR                                LPSTR
#define GEO_SERVICE_TABLE_ENTRY             SERVICE_TABLE_ENTRYA
#define GEO_STARTUPINFO                     STARTUPINFOA
#define GEO_WIN32_FIND_DATA                 WIN32_FIND_DATAA
#define GEO_OSVERSIONINFO                   OSVERSIONINFOA
#define GEO_EXPLICIT_ACCESS                 EXPLICIT_ACCESS_A

#define GEO_CreateEvent                     ::CreateEventA
#define GEO_CreateFile                      ::CreateFileA
#define GEO_CreateFileMapping               ::CreateFileMappingA
#define GEO_CreateMutex                     ::CreateMutexA
#define GEO_CreateProcess                   ::CreateProcessA
#define GEO_CreateSemaphore                 ::CreateSemaphoreA
#define GEO_CreateService                   ::CreateServiceA
#define GEO_ExpandEnvironmentStrings        ::ExpandEnvironmentStringsA
#define GEO_FindFirstChangeNotification     ::FindFirstChangeNotificationA
#define GEO_FindFirstFile                   ::FindFirstFileA
#define GEO_FindNextFile                    ::FindNextFileA
#define GEO_FormatMessage                   ::FormatMessageA
#define GEO_FreeEnvironmentStrings          ::FreeEnvironmentStringsA
#define GEO_GetComputerName                 ::GetComputerNameA
#define GEO_GetEnvironmentStrings           ::GetEnvironmentStringsA
#define GEO_GetFileAttributes               ::GetFileAttributesA
#define GEO_GetModuleFileName               ::GetModuleFileNameA
#define GEO_GetTempPath                     ::GetTempPathA
#define GEO_GetUserName                     ::GetUserNameA
#define GEO_GetUserNameEx                   ::GetUserNameExA
#define GEO_GetVersionEx                    ::GetVersionExA
#define GEO_LoadLibrary                     ::LoadLibraryA
#define GEO_MoveFileEx                      ::MoveFileExA
#define GEO_WaitNamedPipe                   ::WaitNamedPipeA
#define GEO_OpenFileMapping                 ::OpenFileMappingA
#define GEO_OpenSCManager                   ::OpenSCManagerA
#define GEO_OpenService                     ::OpenServiceA
#define GEO_OutputDebugString               ::OutputDebugStringA
#define GEO_RegisterEventSource             ::RegisterEventSourceA
#define GEO_RegisterServiceCtrlHandler      ::RegisterServiceCtrlHandlerA
#define GEO_RegConnectRegistry              ::RegConnectRegistryA
#define GEO_RegCreateKeyEx                  ::RegCreateKeyExA
#define GEO_RegDeleteKey                    ::RegDeleteKeyA
#define GEO_RegDeleteValue                  ::RegDeleteValueA
#define GEO_RegEnumKeyEx                    ::RegEnumKeyExA
#define GEO_RegEnumValue                    ::RegEnumValueA
#define GEO_RegCreateKey                    ::RegCreateKeyA
#define GEO_RegOpenKey                      ::RegOpenKeyA
#define GEO_RegOpenKeyEx                    ::RegOpenKeyExA
#define GEO_RegQueryValueEx                 ::RegQueryValueExA
#define GEO_RegSetValueEx                   ::RegSetValueExA
#define GEO_ReportEvent                     ::ReportEventA
#define GEO_SearchPath                      ::SearchPathA
#define GEO_StartService                    ::StartServiceA
#define GEO_StartServiceCtrlDispatcher      ::StartServiceCtrlDispatcherA
#define GEO_SetFileSecurity                 ::SetFileSecurityA
#define GEO_SetEntriesInAcl                 ::SetEntriesInAclA
#define GEO_PdhExpandCounterPath            ::PdhExpandCounterPathA
#define GEO_PdhOpenQuery                    ::PdhOpenQueryA
#define GEO_PdhAddCounter                   ::PdhAddCounterA
#define GEO_gai_strerror                    ::gai_strerrorA
#endif 
#endif 

#endif
