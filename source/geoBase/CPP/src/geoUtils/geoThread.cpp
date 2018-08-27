#ifndef LIB_UTILS_EXPORTS
#define LIB_UTILS_EXPORTS
#endif // !LIB_UTILS_EXPORTS

#include"preCompile.h"
#include "geoThread.h"




GeoThread::GeoThread()
{
	mStopRequestPending = false;
}
GeoThread::~GeoThread()
{

}
void GeoThread::cleanup()
{
	if (mThreadHandle) mThreadHandle = nullptr;
	
}
int GeoThread::start()
{
	if (mThreadHandle != nullptr) 
		return -1;

	mThread.reset(new std::thread(bind(&GeoThread::run, this)));
	mThreadHandle = mThread->native_handle();
	mThreadId = mThread->get_id();
	return 0;
}
void GeoThread::stop()
{	
	cout << "GeoThread::stop" << endl;
	mStopRequestPending = true;
	mEvent.signal();
	if (mThread->joinable())
	{
		mThread->join();
	}
	cleanup();
}
void GeoThread::run()
{
}

void GeoThread::detach()
{
	mThread->detach();
}
GeoPeriodicThread::GeoPeriodicThread(
	geoUInt32 dwPeriod,
	bool bProcessMessages
)
{
	mPeriod = dwPeriod;
	mIsMsgLoops = bProcessMessages;
}

void GeoPeriodicThread::run()
{
	pre_run();
	while (!mStopRequestPending)
	{
		geoAPIStatus  status = mEvent.wait_for(mPeriod);
		switch (status)
		{
		case 0:
			mStopRequestPending = true;
			break;
		case -1:
			task();
			break;
		default:
			break;
		}
	}
	post_run();
}



// the constructor just launches some amount of workers
GeoThreadPool::GeoThreadPool(size_t threads)
	: stop(false)
{
	for (size_t i = 0; i<threads; ++i)
		workers.emplace_back(
			[this]
	{
		for (;;)
		{
			std::function<void()> task;

			{
				std::unique_lock<std::mutex> lock(this->queue_mutex);
				this->condition.wait(lock,
					[this] { return this->stop || !this->tasks.empty(); });
				if (this->stop && this->tasks.empty())
					return;
				task = std::move(this->tasks.front());
				this->tasks.pop();
			}

			task();
		}
	}
	);
}

// add new work item to the pool
template<class F, class... Args>
auto GeoThreadPool::enqueue(F&& f, Args&&... args)-> std::future<typename std::result_of<F(Args...)>::type>
{
	using return_type = typename std::result_of<F(Args...)>::type;

	auto task = std::make_shared< std::packaged_task<return_type()> >(
		std::bind(std::forward<F>(f), std::forward<Args>(args)...)
		);

	std::future<return_type> res = task->get_future();
	{
		std::unique_lock<std::mutex> lock(queue_mutex);

		// don't allow enqueueing after stopping the pool
		if (stop)
			throw std::runtime_error("enqueue on stopped ThreadPool");

		tasks.emplace([task]() { (*task)(); });
	}
	condition.notify_one();
	return res;
}

// the destructor joins all threads
GeoThreadPool::~GeoThreadPool()
{
	{
		std::unique_lock<std::mutex> lock(queue_mutex);
		stop = true;
	}
	condition.notify_all();
	for (std::thread &worker : workers)
		worker.join();
}