/*****************************************************************************
*  GeoSysWare	Basic tool library											 *
*  Copyright (C) 2016 George.Kuo  guooujie@163.com.							 *
*                                                                            *
*  This file is part of GeoSys.  using C++ std::thread                       *
*                                                                            *
*  @file     geoNet.h														 *
*  @brief    GeoSys�����紦��ģ��                                            *
*																			 *
*  ����TCP UDPͨ�����紦��
*   TCP	 ֧�ֲ���libeventʵ��ͬ��Reactorģʽ ������ģ��
*        ֧����asioʵ���첽ģʽ��������ģ��
*   UDP  ֧����asioʵ�����������첽ģʽ��������ģ��
		 ֧����asioʵ��������ͬ��ģʽ��������ģ��	
*   �ಥ ֧����asioʵ�����������첽ģʽ��������ģ��
*		 ֧����asioʵ����������ͬ��ģʽ��������ģ��
*  ����ͨ��  ֧��ͬ������
*			 ֧���첽����
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
#ifndef  GEOSYS_DB_NET_H__
#define  GEOSYS_DB_NET_H__


#include"geoConfig.h"

#include "geoBasicType.h"




#if defined(GEO_HEADER_INLINE)
#	define GEO_NET_API inline
#else 
#	if defined(_MSC_VER) || defined(__BORLANDC__) || defined(__CODEGEARC__)
#		ifdef LIB_NET_EXPORTS
#			define GEO_NET_API      __declspec(dllexport)
#		else
#			define GEO_NET_API      __declspec(dllimport)
#		endif
#	else
#define GEO_NET_API
#	endif

#endif



#endif