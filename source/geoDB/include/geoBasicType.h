/*****************************************************************************
*  GeoSysWare	Basic tool library											 *
*  Copyright (C) 2016 George.Kuo  guooujie@163.com.							 *
*                                                                            *
*  This file is part of GeoSys.												*
*                                                                            *
*  @file     geoBaseType.h                                                   *
*  @brief    整个GeoSys的基本类型头文件                                       *
*																			 *
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
#ifndef  GEOSYS_OS_BASICTYPE_H__
#define  GEOSYS_OS_BASICTYPE_H__

#include <cstddef>
#include <string>
#include "geoConfig.h"
#include "geoMacro.h"


#include "pshpack1.h"

//基本数据类型
typedef std::nullptr_t		geoNull;
typedef bool				geoBool;
typedef signed char			geoInt8;
typedef unsigned char		geoUInt8;
typedef signed short		geoInt16;
typedef unsigned short		geoUInt16;
typedef signed int			geoInt32;
typedef unsigned int		geoUInt32;
typedef signed long long	geoInt64;
typedef unsigned long long	geoUInt64;
typedef float				geoFloat;
typedef double				geoDouble;
typedef char				geoChar;
typedef wchar_t				geoWChar;
typedef unsigned char		geoByte;
typedef void				geoVoid;
typedef int					geoAPIStatus;

typedef geoUInt64			geoTime;		//做系统运行时的实时处理时间

typedef geoUInt64			geoTimeStamp;	//做数据信息里的时间戳


typedef struct  __tag_GEO_Blob
{
	geoUInt32	Length;
	geoByte*	Data;
} geoBlob;

//带长度的ASCII c格式的字符串，做存储、通信用
typedef struct  __tag_GEO_String
{
	geoUInt32	Length;
	geoChar*	Data;
} geoString;
//带长度的ASCII c格式的字符串，做存储、通信用
typedef struct  __tag_GEO_AString
{
	geoUInt32	Length;
	geoChar*	Data;
} geoAString;
//带长度的UNICODE c格式的字符串，做存储、通信用
typedef struct  __tag_GEO_WString
{
	geoUInt32	Length;
	geoWChar*	Data;
} geoWString;


typedef	geoChar*			geoStr;			//C 格式ASCII c格式的字符串，做存储、通信用
typedef	geoWChar*			geoWStr;		//C 格式UNICODE格式的字符串，做存储、通信用
typedef std::string			geoStdString;	//C++格式的ASCII字符串，做函数调用处理用
typedef std::wstring		geoStdWString;	//C++格式的UNICODE字符串，做函数调用处理用

											//带长度的ASCII c格式的字符串，做存储、通信用
typedef struct  __tag_GEO_StringList
{
	geoUInt32	Count;
	geoStr*		List;
} geoStringList;							//ASCII c格式的字符串列表，做存储、通信用

#ifdef _UNICODE
typedef geoWStr 		geoTStr;			//UNICODE字符串	 C
typedef wchar_t			geoTChar;			//UNICODE字符
typedef geoStdWString	geoStdTString;		//UNICODE字符串  C++
#else
typedef geoStr			geoSTtr;			//ASCII字符串	 C
typedef char			geoTChar;			//ASCII字符
typedef geoStdString geoStdTString;			//ASCII字符串
#endif // __UNICODE




typedef enum  __tag_GEO_VARTYPE : geoUInt8
{
	vTypeEmpty = 0,
	vTypeBool,
	vTypeInt8,
	vTypeUInt8,
	vTypeInt16,
	vTypeUInt16,
	vTypeInt32,
	vTypeUInt32,
	vTypeInt64,
	vTypeUInt64,
	vTypeFloat,
	vTypeDouble,
	vTypeChar,
	vTypeWChar,
	vTypeByte,
	vTypeTimeStamp,
	vTypeBlob,
	vTypeString,
	vTypeAString,
	vTypeWString,
	vTypeMax
}geoVarTypeEunm;


typedef struct  __tag_GEO_Variant
{
	geoVarTypeEunm		vType;
	union
	{
		geoBool			vBool;
		geoInt8			vInt8;
		geoUInt8		vUInt8;
		geoInt16		vInt16;
		geoUInt16		vUInt16;
		geoInt32		vInt32;
		geoUInt32		vUInt32;
		geoInt64		vInt64;
		geoUInt64		vUInt64;
		geoFloat		vFloat;
		geoDouble		vDouble;
		geoChar			vChar;
		geoWChar		vWChar;
		geoByte			vByte;
		geoString		vString;
		geoAString		vAString;
		geoWString		vWString;
		geoTimeStamp	vTimeStamp;
		geoBlob			vBlob;
	};
}geoVariant;



#include"poppack.h"

#endif