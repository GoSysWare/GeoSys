/*****************************************************************************
*  GeoSysWare	Basic tool library											 *
*  Copyright (C) 2016 George.Kuo  guooujie@163.com.							 *
*                                                                            *
*  This file is part of GeoSys.  using C++ std::thread                       *
*                                                                            *
*  @file     geoAssert.h                                                     *
*  @brief                                                         *
*																			 *
*  
*
*  @author   George.Kuo                                                      *
*  @email    guooujie@163.com												 *
*  @version  1.0.0.1(°æ±¾ºÅ)                                                 *
*  @date     2016.8															 *
*  @license																	 *
*                                                                            *
*----------------------------------------------------------------------------*
*  Remark         :									                         *
*----------------------------------------------------------------------------*
*  Change History :                                                          *
*  <Date>     | <Version> | <Author>       | <Description>                   *
*----------------------------------------------------------------------------*
*  2016/10/30 | 1.0.0.1   | George.Kuo      | Create file                    *
*----------------------------------------------------------------------------*
*                                                                            *
*****************************************************************************/

#ifndef  GEOSYS_UTILS_ASSERT_H__
#define  GEOSYS_UTILS_ASSERT_H__

#include"geoBasicType.h"
#include"geoUtils.h"


GEO_UITLS_API void __geo_assert(const char *file, int line, const geoTChar *expression);


#define GEO_TEST_ASSERT(X) \
  ((X)                      \
   ? static_cast<void>(0)   \
   : __geo_assert(__FILE__, __LINE__, GEO_TEXT_CHAR_TO_TCHAR (#X)))

#if defined (NDEBUG) || defined(_NDEBUG)
#define GEO_ASSERT(x) \
  (static_cast<void>(0))
#else
#define GEO_ASSERT(X) GEO_TEST_ASSERT(X)
#endif /* ACE_NDEBUG */


#endif