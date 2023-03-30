#include "modules/calc/ioss/ddk.h"
#include "expression.h"

#include <ctime>
#include <chrono>
#include <iomanip>
#include <limits>
#include <sstream>

static uint64_t MonoTime() {
  auto now = std::chrono::steady_clock::now();
  auto nano_time_point =
      std::chrono::time_point_cast<std::chrono::nanoseconds>(now);
  auto epoch = nano_time_point.time_since_epoch();
  uint64_t now_nano =
      std::chrono::duration_cast<std::chrono::nanoseconds>(epoch).count();
  return now_nano;
}


std::string ToString(uint64_t nanoseconds)  {
  auto nano = std::chrono::nanoseconds(nanoseconds);
  std::chrono::system_clock::time_point tp(nano);
  auto time = std::chrono::system_clock::to_time_t(tp);
  struct tm stm;
  auto ret = localtime_r(&time, &stm);
  if (ret == nullptr) {
    return std::to_string(static_cast<double>(nanoseconds) / 1000000000.0);
  }

  std::stringstream ss;
#if __GNUC__ >= 5
  ss << std::put_time(ret, "%F %T");
  ss << "." << std::setw(9) << std::setfill('0') << nanoseconds % 1000000000UL;
#else
  char date_time[128];
  std::strftime(date_time, sizeof(date_time), "%F %T", ret);
  ss << std::string(date_time) << "." << std::setw(9) << std::setfill('0')
     << nanoseconds % 1000000000UL;
#endif
  return ss.str();
}

bool update_value(device_t *device,std::string tag_name, vam_t value)
{
    double val;
    std::string sim_exp;
    if(tag_name == "OUT1"){
        sim_exp = "RANDOM(100)";
    }else if(tag_name == "OUT2"){
        sim_exp = "$SECOND";
    }else if(tag_name == "OUT3"){
        sim_exp = "$NOW";
    }else if(tag_name == "OUT4"){
        sim_exp = ToString(MonoTime());
        value->mutable_v()->set_str(sim_exp);
        value->set_tm(MonoTime());
        return true; 
    }
	evaluate(sim_exp, &val);
    value->mutable_v()->set_d(val);
    value->set_tm(MonoTime());
    return true;

}
