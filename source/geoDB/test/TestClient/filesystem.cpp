//
//
//#include <vector>
//#include <queue>
//#include <memory>
//#include <mutex>
//#include <condition_variable>
//#include <future>
//#include <functional>
//#include <stdexcept>
//
//#include <iostream> // std::cout, std::endl
//
//#include <vector>   // std::vector
//#include <string>   // std::string
//#include <future>   // std::future
//#include <thread>   // std::this_thread::sleep_for
//#include <chrono>   // std::chrono::seconds
//
//
//#include "output_asio\boost\asio.hpp"
//#include "output_asio\boost\bind.hpp"
//#include "output_asio\boost\algorithm\string.hpp"
//#include "output_asio\boost\filesystem.hpp"
//
//
//
//using namespace std;
//using namespace std::chrono;
//using namespace boost::asio;
//using namespace boost::filesystem;
//
//
//int main(int argc, char**argv)
//{
//
//	char * filepath = "C:\\Works\\41.FTP\\00.server\\I_AUTO.CSV";
//
//
//
//
//	bool bs = windows_name(filepath);
//
//	boost::filesystem::path p = filepath;
//	
//	if (boost::filesystem::exists(p))
//	{
//		boost::filesystem::ifstream   filestream(p);
//		if (filestream.is_open())
//		{
//			// get pointer to associated buffer object
//			std::filebuf* pbuf = filestream.rdbuf();
//
//			// get file size using buffer's members
//			std::size_t size = pbuf->pubseekoff(0, filestream.end, filestream.in);
//			pbuf->pubseekpos(0, filestream.in);
//
//			// allocate memory to contain file data
//			char* buffer = new char[size];
//
//			// get file data
//			pbuf->sgetn(buffer, size);
//
//			string str(buffer);
//
//		   std::vector<string> vec;
//
//
//			boost::split(vec, str, boost::is_any_of("\n"));
//
//			std::vector<std::vector<string>> values(vec.size());
//			for (auto i = 0;i <vec.size();i++)
//			{
//				boost::split(values.at(i), vec.at(i), boost::is_any_of(","));
//				boost::split(values.at(i), vec.at(i), boost::is_any_of(","));
//			}
//
//
//
//
//
//			
//
//
//			delete[] buffer;
//		}
//		
//	}
//
//
//
//	return 0;
//}