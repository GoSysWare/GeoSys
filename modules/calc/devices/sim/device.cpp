#include "modules/calc/ioss/ddk.h"
#include "expression.h"

#include <ctime>
#include <chrono>
#include <iomanip>
#include <limits>
#include <sstream>

static uint64_t MonoTime() {
  auto now = std::chrono::high_resolution_clock::now();
  auto nano_time_point =
      std::chrono::time_point_cast<std::chrono::nanoseconds>(now);
  auto epoch = nano_time_point.time_since_epoch();
  uint64_t now_nano =
      std::chrono::duration_cast<std::chrono::nanoseconds>(epoch).count();
  return now_nano;
}

bool update_value(device_t *device,std::string tag_name, vam_t value)
{
    double val;
    if(!tag_name.empty()){
      evaluate(tag_name, &val);
      value->mutable_v()->set_d(val);
      value->set_tm(MonoTime());
    }
    return true;
}
