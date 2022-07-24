/*****************************************************************************
*  GeoSysWare	Basic tool library											 *
*  Copyright (C) 2016 George.Kuo  guooujie@163.com.							 *
*                                                                            *
*  This file is part of GeoSys.  using C++ std::thread                       *
*                                                                            *
*  @file     geoMutex.h                                                     *
*  @brief    线程处理类                                                      *
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


#ifndef  GEOSYS_MUTEX_H__
#define  GEOSYS_MUTEX_H__

#include "geoObject.h"
#include <mutex>

class GeoMutexBase : public GeoObject
{
public:
	GeoMutexBase() {};
	virtual ~GeoMutexBase() =0 {};
	virtual geoInt32 lock() = 0;
	virtual geoInt32 unlock() = 0;
	/*
	try_lock()，尝试锁住互斥量，如果互斥量被其他线程占有，则当前线程也不会被阻塞。
	线程调用该函数也会出现下面 3 种情况，
	(1). 如果当前互斥量没有被其他线程占有，则该线程锁住互斥量，直到该线程调用 unlock 释放互斥量。
	(2). 如果当前互斥量被其他线程锁住，则当前调用线程返回 false，而并不会被阻塞掉。
	(3). 如果当前互斥量被当前调用线程锁住，则会产生死锁(deadlock)。
	*/
	virtual geoInt32 try_lock() = 0;
	/*
	try_lock_for 函数接受一个时间范围，表示在这一段时间范围之内线程如果没有获得锁则被阻塞住
	（与  try_lock() 不同，try_lock 如果被调用时没有获得锁则直接返回 false），
	如果在此期间其他线程释放了锁，则该线程可以获得对互斥量的锁，
	如果超时（即在指定时间内还是没有获得锁），则返回 false。
	*/
	virtual geoInt32 try_lock_for(geoUInt32 msTime) = 0;
	/*
	try_lock_until 函数则接受一个时间点作为参数，
	在指定时间点未到来之前线程如果没有获得锁则被阻塞住，
	如果在此期间其他线程释放了锁，则该线程可以获得对互斥量的锁，
	如果超时（即在指定时间内还是没有获得锁），则返回 false。
	*/
	virtual geoInt32 try_lock_until(geoTime abTime) = 0;
};

class GeoMutex : public GeoMutexBase
{

public:
	typedef std::mutex type;
	GeoMutex();
	~GeoMutex();
	geoInt32 lock();
	geoInt32 unlock();
	geoInt32 try_lock();
	geoInt32 try_lock_for(geoUInt32 msTime);
	geoInt32 try_lock_until(geoTime abTime);
public:
	type mMutex;
};


class GeoRecursiveMutex : public GeoMutexBase
{
	typedef std::recursive_mutex type;
public:
	GeoRecursiveMutex();
	~GeoRecursiveMutex();
	geoInt32 lock();
	geoInt32 unlock();
	geoInt32 try_lock_for(geoUInt32 msTime);
	geoInt32 try_lock();
	geoInt32 try_lock_until(geoTime abTime);
private:
	type mMutex;
};
class GeoTimeMutex : public GeoMutexBase
{
	typedef std::timed_mutex type;
public:
	GeoTimeMutex();
	~GeoTimeMutex();
	geoInt32 lock();
	geoInt32 unlock();
	geoInt32 try_lock_for(geoUInt32 msTime);
	geoInt32 try_lock();
	geoInt32 try_lock_until(geoTime abTime);
private:
	type mMutex;
};
class GeoTimeRecursiveMutex : public GeoMutexBase
{
	typedef std::recursive_timed_mutex type;
public:
	GeoTimeRecursiveMutex();
	~GeoTimeRecursiveMutex();
	geoInt32 lock();
	geoInt32 unlock();
	geoInt32 try_lock_for(geoUInt32 msTime);
	geoInt32 try_lock();
	geoInt32 try_lock_until(geoTime abTime);
private:
	type mMutex;
};

template<class Mutex>
class GeoLock
{
	GeoLock(Mutex* mutex);


};



#endif