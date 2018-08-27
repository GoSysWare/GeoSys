
#ifndef LIB_UTILS_EXPORTS
#define LIB_UTILS_EXPORTS
#endif // !LIB_UTILS_EXPORTS

#include "preCompile.h"

#include "geoEvent.h"
#include "geoTime.h"

GeoEvent::GeoEvent(bool  manual_reset, bool initial_state)
{
	isManual = manual_reset;
	mPredicate = false;
}

GeoEvent::~GeoEvent()
{
}

int GeoEvent::remove(void)
{
	return 0;
}

GeoEvent::EventHandle GeoEvent::handle(void) const
{
	return 1;
}

void GeoEvent::handle(EventHandle new_handle)
{

}
bool GeoEvent::Predicate()
{
	return mPredicate;
}

int GeoEvent::wait(void)
{

	unique_lock<mutex> lock(mMutex);
	mCondition.wait(lock,bind(&GeoEvent::Predicate,this));

	mPredicate = false;

	return 0;

}

int GeoEvent::wait_for(const geoUInt32 druetime)
{

	//默认是超时
	int ret = -1;
	unique_lock<mutex> lock(mMutex);

	//mPredicate = false时阻塞，ture时才解除阻塞
	//为什么要这样，因为线程资源在阻塞wait_for时可能被意外唤醒，但并不意味着条件变量真的被通知了
	bool ret_status = mCondition.wait_for(lock,
										milliseconds(druetime),
										bind(&GeoEvent::Predicate, this));
	//既然运行到这里解除阻塞了，那就要恢复，允许下一次阻塞
	mPredicate = false;
	return ret = ret_status == true ? 0 : -1;
}
int GeoEvent::wait_until(const geoUInt32 absTime)
{

	int ret = -1;
	unique_lock<mutex> lock(mMutex);

	//mPredicate = false时阻塞，ture时才解除阻塞
	//为什么要这样，因为线程资源在阻塞wait_until时可能被意外唤醒，但并不意味着条件变量真的被通知了
	bool ret_status = mCondition.wait_until(lock,
											geo_geotime_to_steadytime(absTime),
											bind(&GeoEvent::Predicate, this));
	//既然运行到这里解除阻塞了，那就要恢复，允许下一次阻塞
	mPredicate = false;
	return ret = ret_status == true ? 0 : -1;


}
int GeoEvent::signal(void)
{
	unique_lock<mutex> lock(mMutex);
	mCondition.notify_all();
	mPredicate = true;

	return 0;
}

int GeoEvent::pulse(void)
{
	return 0;

}

int GeoEvent::reset(void)
{
	return 0;
}

void GeoEvent::dump(void) const
{

}