
/*****************************************************************************
*  GeoSysWare	Basic tool library											 *
*  Copyright (C) 2016 George.Kuo  guooujie@163.com.							 *
*                                                                            *
*  This file is part of GeoSys.  using C++ std::thread                       *
*                                                                            *
*  @file     geoMacro.h                                                     *
*  @brief    全局宏定义                                                      *
*																			 *
*  其中包含了事件封装
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

#ifndef  GEOSYS_OS_MACRO_H__
#define  GEOSYS_OS_MACRO_H__

#include "geoVersion.h"



#define  GEOSYS_DEFAULT_LOG_NAME GEO_TEXT("geoLogFile.txt")

//根据__cplusplus来处理是否支持C++11 C++14 
//注：VS2015的__cplusplus依然是199711L，不知道为啥。
//个人觉得应该是VS2015还没有完全支持C++11标准，没法更新__cplusplus值
#if (__GNUC__ >= 5 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 7))
# if __cplusplus > 199711L
#  define GEO_HAS_CPP11
# endif
# if __cplusplus > 201103L
#  define GEO_HAS_CPP14
# endif
#endif

//定义全局的输入输出dllexport/dllimport导出标识
//GEO_HEADER_INLINE内联函数的导出处理要不一样，需要如下处理
//#define GEO_HEADER_INLINE
//  GEO_API func1
//  GEO_API func2
//#undef GEO_HEADER_INLINE
#if defined(GEO_HEADER_INLINE)
#	define GEO_API inline
#else 
#	if defined(_MSC_VER) ||  defined(__BORLANDC__) || defined(__MINGW32__)
#		ifdef LIB_GEO_EXPORTS
#			define GEO_API      __declspec(dllexport)
#		else
#			define GEO_API      __declspec(dllimport)
#		endif
#	else
#define GEO_API
#	endif
#endif

#define geoNULL			nullptr	
#define geoRET_SUCC		0
#define geoRET_FAIL		(-1)
#define	geoFALSE		0 							// geoBool false值
#define	geoTRUE			1 							// geoBool true值
// 
#define geoOk(ret)	(!((geoAPIStatus)(ret)))	/// 判断返回值是否正确
#define geoErr(ret)	(((geoAPIStatus)(ret)))		/// 判断返回值是否错误

///	判断指针是否为空
#define IsNull(s) (!(s))

///	判断指针是否非空
#define IsNotNull(s) (s)


///	如果返回结果不是nicRET_OK，则返回
#define RET_ERR(s)				\
do{	\
	nRet = (s);					\
	if (geoErr(nRet))			\
	{							\
	return nRet;				\
	}							\
}while(0)




//参数输入描述符
#define PIN
//参数输出描述符
#define POUT

#ifdef _WIN32
#define GEO_CALL _stdcall
#else
#define GEO_CALL
#endif

//设定标准C++的调用
#ifdef __cplusplus
#define CDECL_BEGIN	extern "C" {
#define CDECL_END	}
#define DEFAULT_PARAM(val)	= val
#else
#define CDECL_BEGIN
#define CDECL_END
#define DEFAULT_PARAM(val)
#endif

//宽字符串处理宏
#define GEO_TEXT_WIDE(STRING) L##STRING
#if defined (_UNICODE)
# define GEO_TEXT(STRING) GEO_TEXT_WIDE (STRING)
#else
# define GEO_TEXT(STRING) STRING
#endif

// 
#ifdef CPPUNIT_ENABLE_NAKED_ASSERT
#include <cppunit/TestAssert.h>
#ifdef GEO_ASSERT
#undef  	GEO_ASSERT
#define  GEO_ASSERT   CPPUNIT_ASSERT 
#endif
#endif // CPPUNIT_ENABLE_NAKED_ASSERT=1


//不同平台下的环境变量与文件前后缀
#if defined (_WIN32)
#  define DIRECTORY_SEPARATOR_STR_A "\\"
#  define DIRECTORY_SEPARATOR_CHAR_A '\\'
#  define GEO_LD_SEARCH_PATH GEO_TEXT ("PATH")
#  define GEO_LD_SEARCH_PATH_SEPARATOR_STR GEO_TEXT (";")
#  define GEO_DLL_SUFFIX GEO_TEXT (".dll")
#  define GEO_DLL_PREFIX GEO_TEXT ("")

#else 
#  define DIRECTORY_SEPARATOR_STR_A "/"
#  define DIRECTORY_SEPARATOR_CHAR_A '/'
#  define GEO_LD_SEARCH_PATH GEO_TEXT ("LD_LIBRARY_PATH")
#  define GEO_LD_SEARCH_PATH_SEPARATOR_STR GEO_TEXT (":")
#  define GEO_DLL_SUFFIX GEO_TEXT (".so")
#  define GEO_DLL_PREFIX GEO_TEXT ("lib")
#endif 



//定义无用arg参数宏
#if !defined (GEO_UNUSED_ARG)
# if defined (__GNUC__) && ((__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 2))) || (defined (__BORLANDC__) && defined (__clang__))
#   define GEO_UNUSED_ARG(a) (void) (a)
# elif defined (__GNUC__) || defined (ghs) || defined (__hpux) || defined (__DECCXX) || defined (__rational__) || defined (__USLC__) || defined (ACE_RM544) || defined (__DCC__) || defined (__PGI) || defined (__TANDEM)
#  define GEO_UNUSED_ARG(a) do {/* null */} while (&a == 0)
# elif defined (__DMC__)
#define GEO_UNUSED_ID(identifier)
template <class T>
inline void GEO_UNUSED_ARG(const T& GEO_UNUSED_ID(t)) { }
# else /* ghs || __GNUC__ || ..... */
#  define GEO_UNUSED_ARG(a) (a)
# endif /* ghs || __GNUC__ || ..... */
#endif /* !GEO_UNUSED_ARG */

#if defined (_MSC_VER) || defined (ghs) || defined (__DECCXX) || defined(__BORLANDC__) || defined (ACE_RM544) || defined (__USLC__) || defined (__DCC__) || defined (__PGI) || defined (__TANDEM) || (defined (__HP_aCC) && (__HP_aCC < 39000 || __HP_aCC >= 60500))
# define GEO_NOTREACHED(a)
#else  /* ghs || ..... */
# define GEO_NOTREACHED(a) a
#endif /* ghs || ..... */


//带异常抛出的New
#define GEO_NEW_RETURN(POINTER,CONSTRUCTOR,RET_VAL) \
   do { POINTER = new (::std::nothrow) CONSTRUCTOR; \
     if (POINTER == 0) { errno = ENOMEM; return RET_VAL; } \
   } while (0)
#define GEO_NEW(POINTER,CONSTRUCTOR) \
   do { POINTER = new(::std::nothrow) CONSTRUCTOR; \
     if (POINTER == 0) { errno = ENOMEM; return; } \
   } while (0)
#define GEO_NEW_NORETURN(POINTER,CONSTRUCTOR) \
   do { POINTER = new(::std::nothrow) CONSTRUCTOR; \
     if (POINTER == 0) { errno = ENOMEM; } \
   } while (0)
#if !defined (GEO_DEFAULT_LOG_STREAM)
#   define GEO_DEFAULT_LOG_STREAM (&cerr)
#endif 



#if !defined (_WIN32)			//linux
typedef void * HANDLE
typedef SOCKET  HANDLE
#define INVALID_HANDLE_VALUE -1

#define LPSECURITY_ATTRIBUTES int
typedef struct stat Geo_stat;
#define GEO_STAT_FUNC_NAME ::stat
#define GEO_WSTAT_FUNC_NAME GEO_STAT_FUNC_NAME
#else						// windows
typedef unsigned short mode_t;
typedef int pid_t;

#    if !defined (S_IRWXU)
#      define S_IRWXU 00700         /* read, write, execute: owner. */
#    endif /* !S_IRWXU */
#    if !defined (S_IRUSR)
#      define S_IRUSR 00400         /* read permission: owner. */
#    endif /* !S_IRUSR */
#    if !defined (S_IWUSR)
#      define S_IWUSR 00200         /* write permission: owner. */
#    endif /* !S_IWUSR */
#    if !defined (S_IXUSR)
#      define S_IXUSR 00100         /* execute permission: owner. */
#    endif /* !S_IXUSR */

#  if !defined (S_IRWXG)
#    define S_IRWXG 00070
#  endif /* S_IRWXG */
#  if !defined (S_IRGRP)
#    define S_IRGRP 00040
#  endif /* S_IRGRP */
#  if !defined (S_IWGRP)
#    define S_IWGRP 00020
#  endif /* S_IWGRP */
#  if !defined (S_IXGRP)
#    define S_IXGRP 00010
#  endif /* S_IXGRP */
#  if !defined (S_IRWXO)
#    define S_IRWXO 00007
#  endif /* S_IRWXO */
#  if !defined (S_IROTH)
#    define S_IROTH 00004
#  endif /* S_IROTH */
#  if !defined (S_IWOTH)
#    define S_IWOTH 00002
#  endif /* S_IWOTH */
#  if !defined (S_IXOTH)
#    define S_IXOTH 00001
#  endif /* S_IXOTH */

#if !defined (S_IFLNK) 
#define S_IFLNK 0200000
#endif 
#if !defined (S_ISLNK)
# if defined (S_IFLNK)
#   define S_ISLNK(mode) (((mode)&S_IFLNK) == S_IFLNK)
# else
#   define S_ISLNK(mode) 0
# endif /* S_IFLNK */
#endif /* S_ISLNK */
#if !defined (S_ISDIR)
# define S_ISDIR(mode)   ((mode&S_IFMT) == S_IFDIR)
#endif



#endif 


#if !defined (DEFAULT_FILE_PERMS)
#  define DEFAULT_FILE_PERMS (FILE_SHARE_READ | FILE_SHARE_WRITE |  FILE_SHARE_DELETE)
#endif 

//64位windows系统下
#ifdef _WIN32
#if defined (_WIN64) || defined (WIN64)
#  ifndef _FILE_OFFSET_BITS
#    define _FILE_OFFSET_BITS 64
#  endif  /* !_FILE_OFFSET_BITS */

typedef __int64 off_t
typedef SSIZE_T ssize_t;

#    define GEO_LOW_PART(X) static_cast<DWORD>(X)
LONG inline GEO_High_Part(off_t value)
{
	LARGE_INTEGER new_value;
	new_value.QuadPart = value;
	return new_value.HighPart;
}
#    define GEO_HIGH_PART(X) GEO_High_Part(X)


LONGLONG inline GEO_Combine_Parts(LONG high, DWORD low)
{
	LARGE_INTEGER value;
	value.LowPart = low;    // DWORD
	value.HighPart = high;  // LONG
	return value.QuadPart;
}
#    define GEO_COMBINE_PARTS(X,Y) GEO_Combine_Parts(X,Y)

typedef struct __stat64 Geo_stat;
#define GEO_STAT_FUNC_NAME ::_stat64
#define GEO_WSTAT_FUNC_NAME ::_wstat64
#else

#    define GEO_LOW_PART(X) X
#    define GEO_HIGH_PART(X) 0
#    define GEO_COMBINE_PARTS(X,Y) X
typedef int ssize_t;

typedef struct _stat Geo_stat;
#     define GEO_STAT_FUNC_NAME ::_stat
#     define GEO_WSTAT_FUNC_NAME ::_wstat
#endif 

#endif // _WIN32




# define GEO_POW(X) (((X) == 0)?1:(X-=1,X|=X>>1,X|=X>>2,X|=X>>4,X|=X>>8,X|=X>>16,(++X)))
# define GEO_EVEN(NUM) (((NUM) & 1) == 0)
# define GEO_ODD(NUM) (((NUM) & 1) == 1)
# define GEO_BIT_ENABLED(WORD, BIT) (((WORD) & (BIT)) != 0)
# define GEO_BIT_DISABLED(WORD, BIT) (((WORD) & (BIT)) == 0)
# define GEO_BIT_CMP_MASK(WORD, BIT, MASK) (((WORD) & (BIT)) == MASK)
# define GEO_SET_BITS(WORD, BITS) (WORD |= (BITS))
# define GEO_CLR_BITS(WORD, BITS) (WORD &= ~(BITS))


//文件名长度
#if !defined (NAME_MAX)
#  if defined (MAXNAMLEN)
#    define NAME_MAX MAXNAMLEN
#  elif defined (MAXNAMELEN)
#    define NAME_MAX MAXNAMELEN
#  elif defined (FILENAME_MAX)
#    define NAME_MAX FILENAME_MAX
#  elif defined (_MAX_FNAME)
#    define NAME_MAX _MAX_FNAME
#  else /* _MAX_FNAME */
#    define NAME_MAX 256
#  endif /* MAXNAMLEN */
#endif /* !NAME_MAX */

//主机名长度
#if !defined (HOST_NAME_MAX)
#  define HOST_NAME_MAX 256
#endif /* !HOST_NAME_MAX */

//路径名长度
#if !defined (PATH_MAX)
#  if defined (_MAX_PATH)
#    define PATH_MAX _MAX_PATH
#  elif defined (MAX_PATH)
#    define PATH_MAX MAX_PATH
#  else /* !_MAX_PATH */
#    define PATH_MAX 1024
#  endif /* _MAX_PATH */
#endif /* !PATH_MAX */

# if !defined (MAXLOGMSGLEN)
#   define MAXLOGMSGLEN (4 * 1024)
# endif 

#endif