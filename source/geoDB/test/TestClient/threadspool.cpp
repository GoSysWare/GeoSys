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
	// 工作线程组
	std::vector< std::thread > workers;
	// 任务队列
	std::queue< std::function<void()> > tasks;

	// synchronization 异步
	std::mutex queue_mutex; // 队列互斥锁
	std::condition_variable condition;  // 条件变量
	bool stop;  // 停止标志
};


// the constructor just launches some amount of workers
// 构造函数仅启动一些工作线程
GeoThreadPool::GeoThreadPool(size_t threads)
	: stop(false)
{
	for (size_t i = 0; i<threads; ++i)
		// 添加线程到工作线程组
		workers.emplace_back(   // 与push_back类型，但性能更好(与此类似的还有emplace/emlace_front)
			[this]
	{   // 线程内不断的从任务队列取任务执行
		for (;;)
		{
			std::function<void()> task;

			{
				// 拿锁(独占所有权式)
				std::unique_lock<std::mutex> lock(this->queue_mutex);
				// 等待条件成立
				this->condition.wait(lock,
					[this] { return this->stop || !this->tasks.empty(); });
				// 执行条件变量等待的时候，已经拿到了锁(即lock已经拿到锁，没有阻塞)
				// 这里将会unlock释放锁，其他线程可以继续拿锁，但此处任然阻塞，等待条件成立
				// 一旦收到其他线程notify_*唤醒，则再次lock，然后进行条件判断
				// 当[return this->stop || !this->tasks.empty()]的结果为false将阻塞
				// 条件为true时候解除阻塞。此时lock依然为锁住状态


				// 如果线程池停止或者任务队列为空，结束返回
				if (this->stop && this->tasks.empty()) {
					return;
				}
				// 取得任务队首任务(注意此处的std::move)
				task = std::move(this->tasks.front());
				// 从队列移除
				this->tasks.pop();
			}
			// 执行任务
			task();
		}
	}
	);
}

// add new work item to the pool
// 添加一个新的工作任务到线程池
template<class F, class... Args>
auto GeoThreadPool::enqueue(F&& f, Args&&... args)-> std::future<typename std::result_of<F(Args...)>::type>
{
	using return_type = typename std::result_of<F(Args...)>::type;

	// 将任务函数和其参数绑定，构建一个packaged_task
	auto task = std::make_shared< std::packaged_task<return_type()> >(
		std::bind(std::forward<F>(f), std::forward<Args>(args)...)
		);
	// 获取任务的future
	std::future<return_type> res = task->get_future();
	{
		// 独占拿锁
		std::unique_lock<std::mutex> lock(queue_mutex);

		// don't allow enqueueing after stopping the pool
		// 不允许入队到已经停止的线程池
		if (stop) {
			throw std::runtime_error("enqueue on stopped ThreadPool");
		}
		// 将任务添加到任务队列
		tasks.emplace([task]() { (*task)(); });
	}
	// 发送通知，唤醒某一个工作线程取执行任务
	condition.notify_one();
	return res;
}

// the destructor joins all threads
GeoThreadPool::~GeoThreadPool()
{
	{
		// 拿锁
		std::unique_lock<std::mutex> lock(queue_mutex);
		// 停止标志置true
		stop = true;
	}
	// 通知所有工作线程，唤醒后因为stop为true了，所以都会结束
	condition.notify_all();
	// 等待所有工作线程结束
	for (std::thread &worker : workers) {
		worker.join();
	}
}


boost::asio::io_service io_service_;


// 创建一个能够并发执行四个线程的线程池
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



	// 启动八个需要执行的线程任务
	for (int i = 0; i < 4; ++i) {
		// 将并发执行任务的返回值添加到结果列表中
		pool.enqueue(std::bind((std::size_t(io_service::*)())&io_service::run, &ioservice[i]));
		//	results.emplace_back();
	}



	system("pause");

	return 0;
}


//int main()
//{
//	// 创建一个能够并发执行四个线程的线程池
//	ThreadPool pool(4);
//	// 创建并发执行线程的结果列表
//	std::vector< std::future<std::string> > results;
//
//	// 启动八个需要执行的线程任务
//	for (int i = 0; i < 8; ++i) {
//		// 将并发执行任务的返回值添加到结果列表中
//		results.emplace_back(
//			// 将下面的打印任务添加到线程池中并发执行
//			pool.enqueue([i] {
//			std::cout << "hello " << i << std::endl;
//			// 上一行输出后, 该线程会等待1秒钟
//			std::this_thread::sleep_for(std::chrono::seconds(1));
//			// 然后再继续输出并返回执行情况
//			std::cout << "world " << i << std::endl;
//			return std::string("---thread ") + std::to_string(i) + std::string(" finished.---");
//		})
//		);
//	}
//
//	// 输出线程任务的结果
//	for (auto && result : results)
//		std::cout << result.get() << ' ';
//	std::cout << std::endl;
//
//	return 0;
//}