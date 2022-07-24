/*****************************************************************************
*  GeoSysWare	Basic tool library											 *
*  Copyright (C) 2016 George.Kuo  guooujie@163.com.							 *
*                                                                            *
*  This file is part of GeoSys.                       *
*                                                                            *
*  @file     preCompile.h                                                     *
*  @brief    ģ��ͨ�õ�Ԥ����ͷ�ļ�                                                      *
*																			 *
*  Ԥ����ͷ�ļ���ָ�Ѹ�ģ�����п����õ��Ĺ�������ͷ�ļ�����preCompile.h��
*  ����cpp��������ͷ�ļ���������ЩһЩͷ�ļ�
*  ���ļ�ֻ�����ͷ�ļ����������˰���ϵͳͷ�ļ�����׼���������е�������ͷ�ļ�
*  ���ļ��������ذ��������⣬����#ifndef   #endif
*  ��ģ���µĺ궨��Ҳ���Լ����ڴ�ͷ�ļ��У����ӿ�ά����
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

#include<thread>
#include<mutex>
#include<condition_variable>
#include<atomic>
#include<future>
#include<iostream>


#include <vector>
#include <queue>
#include <memory>
#include <functional>
#include <stdexcept>


#include <sys/types.h>
#include"geoBasicType.h"
using namespace std;
using namespace std::chrono;


