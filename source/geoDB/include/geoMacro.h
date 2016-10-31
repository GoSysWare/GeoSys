
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


#define  GEOSYS_DEFAULT_NAME GEO_TEXT("GeoSysWare" )


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



#if !defined (_WIN32)
typedef void * HANDLE
#else
typedef int pid_t;
#endif 


# define GEO_POW(X) (((X) == 0)?1:(X-=1,X|=X>>1,X|=X>>2,X|=X>>4,X|=X>>8,X|=X>>16,(++X)))
# define GEO_EVEN(NUM) (((NUM) & 1) == 0)
# define GEO_ODD(NUM) (((NUM) & 1) == 1)
# define GEO_BIT_ENABLED(WORD, BIT) (((WORD) & (BIT)) != 0)
# define GEO_BIT_DISABLED(WORD, BIT) (((WORD) & (BIT)) == 0)
# define GEO_BIT_CMP_MASK(WORD, BIT, MASK) (((WORD) & (BIT)) == MASK)
# define GEO_SET_BITS(WORD, BITS) (WORD |= (BITS))
# define GEO_CLR_BITS(WORD, BITS) (WORD &= ~(BITS))


#ifndef _MAX_PATH
#define _MAX_PATH    1024
#endif

# if !defined (MAXLOGMSGLEN)
#   define MAXLOGMSGLEN (4 * 1024)
# endif 

#endif