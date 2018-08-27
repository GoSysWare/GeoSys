/*****************************************************************************
*  GeoSysWare	Basic tool library											 *
*  Copyright (C) 2016 George.Kuo  guooujie@163.com.							 *
*                                                                            *
*  This file is part of GeoSys.                       *
*                                                                            *
*  @file     preCompile.h                                                     *
*  @brief    模块通用的预编译头文件                                                      *
*																			 *
*  预编译头文件是指把该模块所有可能用到的公共引用头文件放在preCompile.h中
*  各个cpp都包含此头文件，可以少些一些头文件
*  本文件只被别的头文件包含，除了包含系统头文件，不准包含工程中的其他的头文件
*  本文件不存在重包含的问题，无须#ifndef   #endif
*  本模块下的宏定义也可以集中在此头文件中，增加可维护性
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


