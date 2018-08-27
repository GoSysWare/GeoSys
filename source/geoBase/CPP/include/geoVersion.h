

/*****************************************************************************
*  GeoSysWare	Basic tool library											 *
*  Copyright (C) 2016 George.Kuo  guooujie@163.com.							 *
*                                                                            *
*  This file is part of GeoSys.							                   *
*                                                                            *
*  @file     geoVersion.h                                                     *
*  @brief    �̴߳�����                                                      *
*																			 *
*  GeoSys�ı���汾
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
#ifndef GEOSYS_VERSIONED_H
#define GEOSYS_VERSIONED_H


///ƽ̨�汾������汾������ƽ̨�İ汾��
///����ĸ�����ϵͳ�и��Եİ汾����������ά��
///
#define GEOSYS_MAJOR_VERSION 1
#define GEOSYS_MINOR_VERSION 0
#define GEOSYS_BETA_VERSION  1
#define GEOSYS_VERSION_STR "1.0.1"
#define GEOSYS_VERSION 0x010001

#define GEOSYS_DEFAULT_NAME		"GeoSysWare"
#define GEOSYS_AUTHOR			"George Kuo"
#define GEOSYS_BUILD_TIME		"2016/06/01"
#define GEOSYS_OEM				"G.O.G"

/**
*@brief NICSYS��ǰ�İ汾�Ƚ�
���Բ����� #if (GEOSYS_VERSION >= GEOSYS_VERSION_CHECK(4, 4, 0))
*/
#define GEOSYS_VERSION_CHECK(major, minor, patch) ((major<<16)|(minor<<8)|(patch))


/**
*@brief GEOSYS��ʵʱ��汾
*/
#define GEOSYS_RTDB_VERSION_STR "1.0.1"
#define GEOSYS_RTDB_VERSION 0x010001
#define GEOSYS_RTDB_MAJOR_VERSION 1
#define GEOSYS_RTDB_MINOR_VERSION 0
#define GEOSYS_RTDB_BETA_VERSION  1




/**
*@brief GEOSYS������ʵʱ�ಥ���߰汾
*/
#define GEOSYS_VBUS_VERSION 0x010101
#define GEOSYS_VBUS_VERSION_STR "1.0.1"
#define GEOSYS_VBUS_MAJOR_VERSION 1
#define GEOSYS_VBUS_MINOR_VERSION 0
#define GEOSYS_VBUS_BETA_VERSION  1

/**
*@brief GEOSYS����ʷ��汾
*/
#define GEOSYS_HISD_VERSION 0x010101
#define GEOSYS_HISD_VERSION_STR "1.0.1"
#define GEOSYS_HISD_MAJOR_VERSION 1
#define GEOSYS_HISD_MINOR_VERSION 0
#define GEOSYS_HISD_BETA_VERSION  1


/**
*@brief GEOSYS�Ķ��μ�������汾
*/
#define GEOSYS_CALC_VERSION 0x010101
#define GEOSYS_CALC_VERSION_STR "1.0.1"
#define GEOSYS_CALC_MAJOR_VERSION 1
#define GEOSYS_CALC_MINOR_VERSION 0
#define GEOSYS_CALC_BETA_VERSION  1



#endif