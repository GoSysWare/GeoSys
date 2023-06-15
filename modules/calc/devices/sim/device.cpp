#include <chrono>
#include <ctime>
#include <iomanip>
#include <limits>
#include <sstream>
#include "cyber/cyber.h"
#include "expression.h"
#include "modules/calc/ioss/ddk.h"

static uint64_t MonoTime() {
  auto now = std::chrono::high_resolution_clock::now();
  auto nano_time_point =
      std::chrono::time_point_cast<std::chrono::nanoseconds>(now);
  auto epoch = nano_time_point.time_since_epoch();
  uint64_t now_nano =
      std::chrono::duration_cast<std::chrono::nanoseconds>(epoch).count();
  return now_nano;
}

IO_EVENT_HANDLER t_handler;

bool start_device(device_t *device) {
  std::thread([] {
    while (1) {
      usleep(1000 * 1000);
      if (t_handler)
      {
        AINFO << "handler";
        t_handler();
      } 

    };
  }).detach();
  return true;
}
bool stop_device(device_t *device) { return true; }
bool update_value(device_t *device, std::string tag_name, vam_t value) {
  double val;
  if (!tag_name.empty()) {
    evaluate(tag_name, &val);
    value->mutable_v()->set_d(val);
    value->set_tm(MonoTime());
  }
  return true;
}

bool install_event_handler(device_t *device, std::string event_name,
                           IO_EVENT_HANDLER handler) {
  t_handler = handler;
  return true;
}
