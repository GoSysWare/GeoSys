/*****************************************************************************
*  GeoSysWare	Basic tool library											 *
*  Copyright (C) 2016 George.Kuo  guooujie@163.com.							 *
*                                                                            *
*  This file is part of GeoSys.  using C++ std::thread                       *
*                                                                            *
*  @file     geoMutex.h                                                     *
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
	try_lock()��������ס������������������������߳�ռ�У���ǰ�߳�Ҳ���ᱻ������
	�̵߳��øú���Ҳ��������� 3 �������
	(1). �����ǰ������û�б������߳�ռ�У�����߳���ס��������ֱ�����̵߳��� unlock �ͷŻ�������
	(2). �����ǰ�������������߳���ס����ǰ�����̷߳��� false���������ᱻ��������
	(3). �����ǰ����������ǰ�����߳���ס������������(deadlock)��
	*/
	virtual geoInt32 try_lock() = 0;
	/*
	try_lock_for ��������һ��ʱ�䷶Χ����ʾ����һ��ʱ�䷶Χ֮���߳����û�л����������ס
	����  try_lock() ��ͬ��try_lock ���������ʱû�л������ֱ�ӷ��� false����
	����ڴ��ڼ������߳��ͷ�����������߳̿��Ի�öԻ�����������
	�����ʱ������ָ��ʱ���ڻ���û�л���������򷵻� false��
	*/
	virtual geoInt32 try_lock_for(geoUInt32 msTime) = 0;
	/*
	try_lock_until ���������һ��ʱ�����Ϊ������
	��ָ��ʱ���δ����֮ǰ�߳����û�л����������ס��
	����ڴ��ڼ������߳��ͷ�����������߳̿��Ի�öԻ�����������
	�����ʱ������ָ��ʱ���ڻ���û�л���������򷵻� false��
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