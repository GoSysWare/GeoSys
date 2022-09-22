#include <string>
#include <mutex>
#include <iostream>
#include <sstream>

#include "goal_id_generator.h"
#include "cyber/binary.h"
#include "cyber/time/time.h"


static std::mutex s_goalcount_mutex_;
static unsigned int s_goalcount_ = 0;

namespace apollo {

actionlib::GoalIDGenerator::GoalIDGenerator()
{
  setName(apollo::cyber::Binary::GetName());
}

actionlib::GoalIDGenerator::GoalIDGenerator(const std::string & name)
{
  setName(name);
}

void actionlib::GoalIDGenerator::setName(const std::string & name)
{
  name_ = name;
}

GoalID actionlib::GoalIDGenerator::generateID()
{
  GoalID id;
  apollo::cyber::Time cur_time = apollo::cyber::Time::Now();
  std::stringstream ss;

  ss << name_ << "-";

  {
    std::lock_guard<std::mutex> lock(s_goalcount_mutex_);
    s_goalcount_++;
    ss << s_goalcount_ << "-";
  }

  ss << cur_time;
  id.set_id(ss.str());
  id.set_timestamp(cur_time.ToNanosecond());
  return id;
}


}
