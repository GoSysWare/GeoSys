/*****************************************************************************
*  GeoSysWare	Basic tool library											 *
*  Copyright (C) 2016 George.Kuo  guooujie@163.com.							 *
*                                                                            *
*  This file is part of GeoSys.  using C++ std::thread                       *
*                                                                            *
*  @file     geoThread.h                                                     *
*  @brief    线程处理类                                                      *
*																			 *
*  其中包含了基本线程、周期线程、线程池
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

#ifndef  GEOSYS_UTILS_THREAD_H__
#define  GEOSYS_UTILS_THREAD_H__

#include "preCompile.h"
#include "geoEvent.h"


/**
* @brief 基本类 \n(换行)
*   
*   封装线程的启、停等基本操作
*/

class GEO_UITLS_API GeoThread
{
	typedef std::condition_variable ThreadEvent;
	typedef std::unique_ptr<std::thread>  ThreadInerPtr;
	typedef thread::id  ThreadId;
	typedef thread::native_handle_type  ThreadHandle;

	enum class GoeThreadEvent : int 
	{
		THREAD_INIT_COMPLETE = 0,
		THREAD_EXIT_COMPLETE =1,
	};
public:
	GeoThread();
	~GeoThread();
	int start();
	void stop();
	void detach();
	virtual void run();
private:
	void cleanup();
	ThreadId mThreadId;
	ThreadInerPtr mThread;
	ThreadHandle mThreadHandle;
public:
	std::atomic<bool> mStopRequestPending;
	GeoEvent mEvent;
};
//周期线程，可以保证以ms来周期运行task
class  GEO_UITLS_API GeoPeriodicThread : public GeoThread
{
public:
	GeoPeriodicThread(
		geoUInt32 dwPeriod = 1000,
		bool bProcessMessages = false
	);
protected:
	virtual void pre_run() {};
	virtual void post_run() {};
	virtual void task() = 0;
	virtual int on_msg(
		int msg,
		int wparam,
		int lparam
	)
	{
		return 0;
	}
private:
	virtual void run() override;
public:
	geoTime	mPeriod;
	bool mIsMsgLoops;

};

class GeoThreadPool {
public:
	GeoThreadPool(size_t);
	template<class F, class... Args>
	auto enqueue(F&& f, Args&&... args)->std::future<typename std::result_of<F(Args...)>::type>;
	~GeoThreadPool();
private:
	// need to keep track of threads so we can join them
	std::vector< std::thread > workers;
	// the task queue
	std::queue< std::function<void()> > tasks;

	// synchronization
	std::mutex queue_mutex;
	std::condition_variable condition;
	bool stop;
};



#endif