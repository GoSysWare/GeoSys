#include "modules/calc/ioss/ddk.h"
#include "expression.h"

static uint64_t MonoTime() {
  auto now = std::chrono::steady_clock::now();
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
    std::string sim_exp;
    if(tag_name == "OUT1"){
        sim_exp = "RANDOM(100)";
    }else if(tag_name == "OUT2"){
        sim_exp = "$SECOND";
    }else if(tag_name == "OUT3"){
        sim_exp = "$NOW";
    }
	evaluate(sim_exp, &val);
    value->mutable_v()->set_d(val);
    value->set_tm(MonoTime());

}
