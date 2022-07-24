
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

	//Ĭ���ǳ�ʱ
	int ret = -1;
	unique_lock<mutex> lock(mMutex);

	//mPredicate = falseʱ������tureʱ�Ž������
	//ΪʲôҪ��������Ϊ�߳���Դ������wait_forʱ���ܱ����⻽�ѣ���������ζ������������ı�֪ͨ��
	bool ret_status = mCondition.wait_for(lock,
										milliseconds(druetime),
										bind(&GeoEvent::Predicate, this));
	//��Ȼ���е������������ˣ��Ǿ�Ҫ�ָ���������һ������
	mPredicate = false;
	return ret = ret_status == true ? 0 : -1;
}
int GeoEvent::wait_until(const geoUInt32 absTime)
{

	int ret = -1;
	unique_lock<mutex> lock(mMutex);

	//mPredicate = falseʱ������tureʱ�Ž������
	//ΪʲôҪ��������Ϊ�߳���Դ������wait_untilʱ���ܱ����⻽�ѣ���������ζ������������ı�֪ͨ��
	bool ret_status = mCondition.wait_until(lock,
											geo_geotime_to_steadytime(absTime),
											bind(&GeoEvent::Predicate, this));
	//��Ȼ���е������������ˣ��Ǿ�Ҫ�ָ���������һ������
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