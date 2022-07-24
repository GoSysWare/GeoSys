//=============================================================================
/**
* COPYRIGHT NOTICE
* Copyright(c) 2012, CNCS All rights reserved. 
* @file GEOError.h
* @date 2014-03-03
* @author CNCS-0136
* @version 2.0.1
* @brief GEOSys2000的类的命名空间
*
*  对类加上带有版本号的命名空间，这个主要是解决对同一个类名在不同的开发版本冲突问题
* @warning  
*/
//=============================================================================
/*****************************************************************************
*  GeoSysWare	Basic tool library											 *
*  Copyright (C) 2016 George.Kuo  guooujie@163.com.							 *
*                                                                            *
*  This file is part of GeoSys.							                     *
*                                                                            *
*  @file     geoVersionNameSpace.h                                           *
*  @brief    类的命名空间                                                    *
*																			 *
*  对类加上带有版本号的命名空间，这个主要是解决对同一个类名在不同的开发版本冲突问题
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
#ifndef GEOSYS_VERSIONED_NAMESPACE_H
#define GEOSYS_VERSIONED_NAMESPACE_H


#if defined (GEOSYS_HAS_VERSIONED_NAMESPACE) && GEOSYS_HAS_VERSIONED_NAMESPACE == 1

# ifndef GEOSYS_VERSIONED_NAMESPACE_NAME
#  include "geoVersion.h"

// Preprocessor symbols will not be expanded if they are
// concatenated.  Force the preprocessor to expand them during the
// argument prescan by calling a macro that itself calls another that
// performs the actual concatenation.
#  define GEOSYS_MAKE_VERSIONED_NAMESPACE_NAME_IMPL(MAJOR,MINOR,BETA) GEOSYS_ ## MAJOR ## _ ## MINOR ## _ ## BETA
#  define GEOSYS_MAKE_VERSIONED_NAMESPACE_NAME(MAJOR,MINOR,BETA) GEOSYS_MAKE_VERSIONED_NAMESPACE_NAME_IMPL(MAJOR,MINOR,BETA)
#  define GEOSYS_VERSIONED_NAMESPACE_NAME GEOSYS_MAKE_VERSIONED_NAMESPACE_NAME(GEOSYS_MAJOR_VERSION,GEOSYS_MINOR_VERSION,GEOSYS_BETA_VERSION)
# endif  /* !GEOSYS_VERSIONED_NAMESPACE_NAME */

# define GEOSYS_BEGIN_VERSIONED_NAMESPACE_DECL namespace GEOSYS_VERSIONED_NAMESPACE_NAME {
# define GEOSYS_END_VERSIONED_NAMESPACE_DECL } \
	using namespace GEOSYS_VERSIONED_NAMESPACE_NAME;

#else

# define GEOSYS_VERSIONED_NAMESPACE_NAME
# define GEOSYS_BEGIN_VERSIONED_NAMESPACE_DECL
# define GEOSYS_END_VERSIONED_NAMESPACE_DECL

#endif  /* GEOSYS_HAS_VERSIONED_NAMESPACE */

#endif  /* !GEOSYS_VERSIONED_NAMESPACE_H */