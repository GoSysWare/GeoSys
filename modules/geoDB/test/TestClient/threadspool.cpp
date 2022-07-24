#include <vector>
#include <queue>
#include <memory>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include <stdexcept>

#include <iostream> // std::cout, std::endl

#include <vector>   // std::vector
#include <string>   // std::string
#include <future>   // std::future
#include <thread>   // std::this_thread::sleep_for
#include <chrono>   // std::chrono::seconds


#include "output_asio\boost\asio.hpp"
#include "output_asio\boost\bind.hpp"
#include "output_asio\boost\algorithm\string.hpp"
#include "output_asio\boost\filesystem.hpp"


using namespace std;
using namespace std::chrono;
using namespace boost::asio;

class GeoThreadPool {
public:
	GeoThreadPool(size_t);
	template<class F, class... Args>
	auto enqueue(F&& f, Args&&... args)->std::future<typename std::result_of<F(Args...)>::type>;
	~GeoThreadPool();
private:
private:
	// need to keep track of threads so we can join them
	// �����߳���
	std::vector< std::thread > workers;
	// �������
	std::queue< std::function<void()> > tasks;

	// synchronization �첽
	std::mutex queue_mutex; // ���л�����
	std::condition_variable condition;  // ��������
	bool stop;  // ֹͣ��־
};


// the constructor just launches some amount of workers
// ���캯��������һЩ�����߳�
GeoThreadPool::GeoThreadPool(size_t threads)
	: stop(false)
{
	for (size_t i = 0; i<threads; ++i)
		// ����̵߳������߳���
		workers.emplace_back(   // ��push_back���ͣ������ܸ���(������ƵĻ���emplace/emlace_front)
			[this]
	{   // �߳��ڲ��ϵĴ��������ȡ����ִ��
		for (;;)
		{
			std::function<void()> task;

			{
				// ����(��ռ����Ȩʽ)
				std::unique_lock<std::mutex> lock(this->queue_mutex);
				// �ȴ���������
				this->condition.wait(lock,
					[this] { return this->stop || !this->tasks.empty(); });
				// ִ�����������ȴ���ʱ���Ѿ��õ�����(��lock�Ѿ��õ�����û������)
				// ���ｫ��unlock�ͷ����������߳̿��Լ������������˴���Ȼ�������ȴ���������
				// һ���յ������߳�notify_*���ѣ����ٴ�lock��Ȼ����������ж�
				// ��[return this->stop || !this->tasks.empty()]�Ľ��Ϊfalse������
				// ����Ϊtrueʱ������������ʱlock��ȻΪ��ס״̬


				// ����̳߳�ֹͣ�����������Ϊ�գ���������
				if (this->stop && this->tasks.empty()) {
					return;
				}
				// ȡ�������������(ע��˴���std::move)
				task = std::move(this->tasks.front());
				// �Ӷ����Ƴ�
				this->tasks.pop();
			}
			// ִ������
			task();
		}
	}
	);
}

// add new work item to the pool
// ���һ���µĹ��������̳߳�
template<class F, class... Args>
auto GeoThreadPool::enqueue(F&& f, Args&&... args)-> std::future<typename std::result_of<F(Args...)>::type>
{
	using return_type = typename std::result_of<F(Args...)>::type;

	// ����������������󶨣�����һ��packaged_task
	auto task = std::make_shared< std::packaged_task<return_type()> >(
		std::bind(std::forward<F>(f), std::forward<Args>(args)...)
		);
	// ��ȡ�����future
	std::future<return_type> res = task->get_future();
	{
		// ��ռ����
		std::unique_lock<std::mutex> lock(queue_mutex);

		// don't allow enqueueing after stopping the pool
		// ��������ӵ��Ѿ�ֹͣ���̳߳�
		if (stop) {
			throw std::runtime_error("enqueue on stopped ThreadPool");
		}
		// ��������ӵ��������
		tasks.emplace([task]() { (*task)(); });
	}
	// ����֪ͨ������ĳһ�������߳�ȡִ������
	condition.notify_one();
	return res;
}

// the destructor joins all threads
GeoThreadPool::~GeoThreadPool()
{
	{
		// ����
		std::unique_lock<std::mutex> lock(queue_mutex);
		// ֹͣ��־��true
		stop = true;
	}
	// ֪ͨ���й����̣߳����Ѻ���ΪstopΪtrue�ˣ����Զ������
	condition.notify_all();
	// �ȴ����й����߳̽���
	for (std::thread &worker : workers) {
		worker.join();
	}
}


boost::asio::io_service io_service_;


// ����һ���ܹ�����ִ���ĸ��̵߳��̳߳�
GeoThreadPool pool(4);


int count = 0;
void handle_wait(const boost::system::error_code& error, boost::asio::deadline_timer& t,
	int& count)
{
	if (!error)
	{

		std::cout << count++ << "\n";

			t.expires_from_now(boost::posix_time::seconds(2));
			t.async_wait(boost::bind(handle_wait, boost::asio::placeholders::error,
				boost::ref(t), boost::ref(count)));
	}
}


int main(int argc, char* argv[])
{
	

	io_service ioservice[4];





	deadline_timer t(ioservice[0]);
	deadline_timer t1(ioservice[0]);
	deadline_timer t2(ioservice[0]);
	deadline_timer t3(ioservice[0]);
	t.expires_from_now(boost::posix_time::seconds(1));
	t1.expires_from_now(boost::posix_time::seconds(1));
	t2.expires_from_now(boost::posix_time::seconds(1));
	t3.expires_from_now(boost::posix_time::seconds(1));

	int count = 0;
	t.async_wait(boost::bind(handle_wait,
		boost::asio::placeholders::error,
		boost::ref(t),
		boost::ref(count)));

	int count1 = 100;
	t1.async_wait(boost::bind(handle_wait,
		boost::asio::placeholders::error,
		boost::ref(t1),
		boost::ref(count1)));
	int count2 = 200;
	t2.async_wait(boost::bind(handle_wait,
		boost::asio::placeholders::error,
		boost::ref(t2),
		boost::ref(count2)));

	int count3= 300;
	t3.async_wait(boost::bind(handle_wait,
		boost::asio::placeholders::error,
		boost::ref(t3),
		boost::ref(count3)));



	// �����˸���Ҫִ�е��߳�����
	for (int i = 0; i < 4; ++i) {
		// ������ִ������ķ���ֵ��ӵ�����б���
		pool.enqueue(std::bind((std::size_t(io_service::*)())&io_service::run, &ioservice[i]));
		//	results.emplace_back();
	}



	system("pause");

	return 0;
}


//int main()
//{
//	// ����һ���ܹ�����ִ���ĸ��̵߳��̳߳�
//	ThreadPool pool(4);
//	// ��������ִ���̵߳Ľ���б�
//	std::vector< std::future<std::string> > results;
//
//	// �����˸���Ҫִ�е��߳�����
//	for (int i = 0; i < 8; ++i) {
//		// ������ִ������ķ���ֵ��ӵ�����б���
//		results.emplace_back(
//			// ������Ĵ�ӡ������ӵ��̳߳��в���ִ��
//			pool.enqueue([i] {
//			std::cout << "hello " << i << std::endl;
//			// ��һ�������, ���̻߳�ȴ�1����
//			std::this_thread::sleep_for(std::chrono::seconds(1));
//			// Ȼ���ټ������������ִ�����
//			std::cout << "world " << i << std::endl;
//			return std::string("---thread ") + std::to_string(i) + std::string(" finished.---");
//		})
//		);
//	}
//
//	// ����߳�����Ľ��
//	for (auto && result : results)
//		std::cout << result.get() << ' ';
//	std::cout << std::endl;
//
//	return 0;
//}