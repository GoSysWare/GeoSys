/*****************************************************************************
*  GeoSysWare	Basic tool library											 *
*  Copyright (C) 2016 George.Kuo  guooujie@163.com.							 *
*                                                                            *
*  This file is part of GeoSys.  using C++ std::thread                       *
*                                                                            *
*  @file     geoEvent.h                                                     *
*  @brief    �̴߳�����                                                      *
*																			 *
*  ���а������¼���װ
*
*  @author   George.Kuo                                                      *
*  @email    guooujie@163.com												 *
*  @version  1.0.0.1(�汾��)                                                 *
*  @date     2016.8															 *
*  @license																	 *
*                                                                            *
*----------------------------------------------------------------------------*
*  Remark         : ������֧��C++11�����±���ͨ��                            *
*----------------------------------------------------------------------------*
*  Change History :                                                          *
*  <Date>     | <Version> | <Author>       | <Description>                   *
*----------------------------------------------------------------------------*
*  2016/08/24 | 1.0.0.1   | George.Kuo      | Create file                    *
*----------------------------------------------------------------------------*
*                                                                            *
*****************************************************************************/

#ifndef  GEOSYS_UTILS_TIME_H__
#define  GEOSYS_UTILS_TIME_H__


#include <chrono>
#include "geoBasicType.h"
#include "geoTime.h"

using namespace std::chrono;


//ʱ������
 extern   const  geoTimeStamp  geoTime_Zero;


#include "geoUtils.h"
#include "geoStdio.h"
#include "geoUnistd.h"


//�Ժ���Ϊ������λ
//�˼�ʱ��ϵͳ����ʱ��Ϊ��׼��
//��ʱ����Եõ�ϵͳ������CPU��tick��������ʾϵͳ�����˶��ٺ���
//��Ҫ���ڳ����ڲ���ʱ������ϵͳʱ��Գ�����Ӱ��ĵط�
 GEO_UITLS_API geoTime   GEO_CALL geo_get_steady_time();
//�Ժ���Ϊ������λ
//��ʱ����Եõ���ǰϵͳʱ��
//��Ҫ����ʱ�����
GEO_UITLS_API geoTimeStamp  GEO_CALL geo_get_system_time();

//�����geoTimeת��ΪCPU��tickʱ��
//Ϊ��׼������ϵͳ��������
GEO_UITLS_API steady_clock::time_point   GEO_CALL geo_geotime_to_steadytime(geoTime absTime);

// Returns the given timestamp in the form
// "hour:minute:second:microsecond."  The month, day, and year are
// also stored in the beginning of the date_and_time array
// using ISO-8601 format.
// 012345678901234567890123456
// 2010-12-02 12:56:00.123456<nul>

GEO_UITLS_API geoTChar * GEO_CALL geo_timestamp(const geoTimeStamp& time_value,
	geoTChar date_and_time[],
	size_t date_and_timelen,
	bool return_pointer_to_first_digit DEFAULT_PARAM(false));


#endif