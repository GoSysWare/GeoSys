/*****************************************************************************
*  GeoSysWare	Basic tool library											 *
*  Copyright (C) 2016 George.Kuo  guooujie@163.com.							 *
*                                                                            *
*  This file is part of GeoSys.  using C++ std::thread                       *
*                                                                            *
*  @file     geoEvent.h                                                     *
*  @brief    事件event类                                                      *
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
#ifndef  GEOSYS_UTILS_EVNET_H__
#define  GEOSYS_UTILS_EVNET_H__



#include"geoBasicType.h"

#include "geoUtils.h"

class GEO_UITLS_API std::mutex;

/**
* @brief GeoEvent类 利用C++11的条件变量 实现Event，
* 
* 与windowsEvent相比 GeoEvent没有手自动，恢复功能
*/
class GEO_UITLS_API GeoEvent
{
public:
	/**
	* @brief 事件句柄
	*/
	typedef geoUInt32 EventHandle;
public:
	GeoEvent(bool  manual_reset = false,
			 bool initial_state = false);
	~GeoEvent();

	int remove(void);

	EventHandle handle(void) const;

	void handle(EventHandle new_handle);

	int wait(void);

	int wait_for(const geoUInt32 msTime);
	int wait_until(const geoUInt32 absTime);
	int signal(void);

	int pulse(void);

	int reset(void);

	void dump(void) const;

private:
	bool Predicate();
	EventHandle handle_;
	bool isRemoved;
	bool isManual;
	mutex mMutex;
	condition_variable  mCondition;
	bool   mPredicate;
protected:
	GeoEvent(const GeoEvent& event) = delete;
	const GeoEvent &operator= (const GeoEvent &rhs) = delete;
	GeoEvent( GeoEvent&& event) = delete;
};



#endif