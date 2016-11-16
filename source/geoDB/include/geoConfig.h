/*****************************************************************************
*  GeoSysWare	Basic tool library											 *
*  Copyright (C) 2016 George.Kuo  guooujie@163.com.							 *
*                                                                            *
*  This file is part of GeoSys.												*
*                                                                            *
*  @file     geoConfig.h                                                   *
*  @brief		GeoSys��һЩϵͳҵ����ص����ú����ö��ڴ�					                                      *
*																			 *
*
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

#ifndef  GEOSYS_OS_CONFIG_H__
#define  GEOSYS_OS_CONFIG_H__




#include "geoVersion.h"
#include "geoVersionNameSpace.h"

#define rtkm_node_key_length   16


////�����������֧��C++11�����Զ�ʧ��
//#if __cplusplus < 20131103L  
//#error "should use C++ 11 implementation"  
//#endif  


#ifdef _WIN32
#pragma warning(disable:4996) //ȫ���ص�
#endif // _WIN32


#endif