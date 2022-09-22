/*********************************************************************
* Software License Agreement (BSD License)
*
*  Copyright (c) 2008, Willow Garage, Inc.
*  All rights reserved.
*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions
*  are met:
*
*   * Redistributions of source code must retain the above copyright
*     notice, this list of conditions and the following disclaimer.
*   * Redistributions in binary form must reproduce the above
*     copyright notice, this list of conditions and the following
*     disclaimer in the documentation and/or other materials provided
*     with the distribution.
*   * Neither the name of the Willow Garage nor the names of its
*     contributors may be used to endorse or promote products derived
*     from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
*  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
*  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
*  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
*  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
*  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
*  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
*  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
*  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
*  POSSIBILITY OF SUCH DAMAGE.
*********************************************************************/

#ifndef ACTIONLIB__CLIENT__CONNECTION_MONITOR_H_
#define ACTIONLIB__CLIENT__CONNECTION_MONITOR_H_


#include "cyber/cyber.h"

#include "client_helpers.h"
#include "cyber/proto/role_attributes.pb.h"
#include "modules/common/proto/action.pb.h"

#include "modules/action/action_definition.h"

#include <set>
#include <string>
#include <map>

using apollo::cyber::proto::RoleAttributes;

namespace apollo {
namespace actionlib
{
    
template<class ActionSpec>
class  ConnectionMonitor
{
public:
  ACTION_DEFINITION(ActionSpec);

  ConnectionMonitor( std::shared_ptr<Reader<ActionFeedback>>   feedback_sub, std::shared_ptr<Reader<ActionResult>>  result_sub);

  void goalConnectCallback(const RoleAttributes & sub);

  void goalDisconnectCallback(const RoleAttributes & sub);

  void cancelConnectCallback(const RoleAttributes & sub);

  void cancelDisconnectCallback(const RoleAttributes & sub);

  void processStatus(const GoalStatusArrayConstPtr & status,
    const RoleAttributes  & pub);

  bool waitForActionServerToStart(const cyber::Duration & timeout,
  const std::shared_ptr<Node> nh );
  
  bool isServerConnected();
private:
  // status stuff
  std::string status_caller_id_;
  bool status_received_;
  cyber::Time latest_status_time_;

  std::condition_variable_any check_connection_condition_;

  std::recursive_mutex data_mutex_;
  std::map<std::string, size_t> goalSubscribers_;
  std::map<std::string, size_t> cancelSubscribers_;

  std::string goalSubscribersString();
  std::string cancelSubscribersString();

  std::shared_ptr<Reader<ActionFeedback>>   feedback_sub_;
  std::shared_ptr<Reader<ActionResult>>  result_sub_;

};




#define CONNECTION_DEBUG \
  ADEBUG_MODULE("ConnectionMonitor")

#define CONNECTION_WARN  \
  ALOG_MODULE("ConnectionMonitor", WARN)


template<class ActionSpec>
ConnectionMonitor<ActionSpec>::ConnectionMonitor(std::shared_ptr<Reader<ActionFeedback>> feedback_sub,
  std::shared_ptr<Reader<ActionResult>> result_sub)
: feedback_sub_(feedback_sub), result_sub_(result_sub)
{
  status_received_ = false;
}

// ********* Goal Connections *********
template<class ActionSpec>
void ConnectionMonitor<ActionSpec>::goalConnectCallback(const RoleAttributes & sub)
{
  std::lock_guard<std::recursive_mutex> lock(data_mutex_);
  std::string sub_name =   sub.host_name() + "_" + std::to_string(sub.process_id() ) + "_" + sub.node_name();
  // Check if it's not in the list
  if (goalSubscribers_.find(sub_name) == goalSubscribers_.end()) {
    CONNECTION_DEBUG << "goalConnectCallback: Adding "<<  sub_name <<"to goalSubscribers";
    goalSubscribers_[sub_name] = 1;
  } else {
    CONNECTION_WARN << 
      "goalConnectCallback: Trying to add " << sub_name << "to goalSubscribers, but it is already in the goalSubscribers list";
    goalSubscribers_[sub_name]++;
  }
  CONNECTION_DEBUG << goalSubscribersString();

  check_connection_condition_.notify_all();
}

template<class ActionSpec>
void ConnectionMonitor<ActionSpec>::goalDisconnectCallback(const RoleAttributes & sub)
{
  std::lock_guard<std::recursive_mutex> lock(data_mutex_);
  std::string sub_name =   sub.host_name() + "_" + std::to_string(sub.process_id() ) + "_" + sub.node_name();


  std::map<std::string, size_t>::iterator it;

  it = goalSubscribers_.find(sub_name);

  if (it == goalSubscribers_.end()) {
    CONNECTION_WARN << 
      "goalDisconnectCallback: Trying to remove "<< sub_name <<" to goalSubscribers, but it is not in the goalSubscribers list";
  } else {
    CONNECTION_DEBUG << "goalDisconnectCallback: Removing "<< sub_name <<" from goalSubscribers";
    goalSubscribers_[sub_name]--;
    if (goalSubscribers_[sub_name] == 0) {
      goalSubscribers_.erase(it);
    }
  }
  CONNECTION_DEBUG << goalSubscribersString();
}

template<class ActionSpec>
std::string ConnectionMonitor<ActionSpec>::goalSubscribersString()
{
  std::lock_guard<std::recursive_mutex> lock(data_mutex_);
  std::ostringstream ss;
  ss << "Goal Subscribers (" << goalSubscribers_.size() << " total)";
  for (std::map<std::string, size_t>::iterator it = goalSubscribers_.begin();
    it != goalSubscribers_.end(); it++)
  {
    ss << "\n   - " << it->first;
  }
  return ss.str();
}

// ********* Cancel Connections *********

template<class ActionSpec>
void ConnectionMonitor<ActionSpec>::cancelConnectCallback(const RoleAttributes  & sub)
{
  std::lock_guard<std::recursive_mutex> lock(data_mutex_);
  std::string sub_name =   sub.host_name() + "_" + std::to_string(sub.process_id() ) + "_" + sub.node_name();

  // Check if it's not in the list
  if (cancelSubscribers_.find(sub_name) == cancelSubscribers_.end()) {
    CONNECTION_DEBUG << "cancelConnectCallback: Adding "<<  sub_name <<" to cancelSubscribers";
    cancelSubscribers_[sub_name] = 1;
  } else {
    CONNECTION_WARN << 
      "cancelConnectCallback: Trying to add "<<  sub_name <<" to cancelSubscribers, but it is already in the cancelSubscribers list";
    cancelSubscribers_[sub_name]++;
  }
  CONNECTION_DEBUG << cancelSubscribersString();

  check_connection_condition_.notify_all();
}

template<class ActionSpec>
void ConnectionMonitor<ActionSpec>::cancelDisconnectCallback(
  const RoleAttributes & sub)
{
  std::lock_guard<std::recursive_mutex> lock(data_mutex_);
  std::string sub_name =   sub.host_name() + "_" + std::to_string(sub.process_id() ) + "_" + sub.node_name();

  std::map<std::string, size_t>::iterator it;
  it = cancelSubscribers_.find(sub_name);

  if (it == cancelSubscribers_.end()) {
    CONNECTION_WARN << 
      "cancelDisconnectCallback: Trying to remove "<<  sub_name <<" to cancelSubscribers, but it is not in the cancelSubscribers list";
  } else {
    CONNECTION_DEBUG << "cancelDisconnectCallback: Removing  "<<  sub_name <<" from cancelSubscribers";
    cancelSubscribers_[sub_name]--;
    if (cancelSubscribers_[sub_name] == 0) {
      cancelSubscribers_.erase(it);
    }
  }
  CONNECTION_DEBUG << cancelSubscribersString();
}

template<class ActionSpec>
std::string ConnectionMonitor<ActionSpec>::cancelSubscribersString()
{
  std::lock_guard<std::recursive_mutex> lock(data_mutex_);

  std::ostringstream ss;
  ss << "cancel Subscribers (" << cancelSubscribers_.size() << " total)";
  for (std::map<std::string, size_t>::iterator it = cancelSubscribers_.begin();
    it != cancelSubscribers_.end(); it++)
  {
    ss << "\n   - " << it->first;
  }
  return ss.str();
}

// ********* GoalStatus Connections *********
template<class ActionSpec>
void ConnectionMonitor<ActionSpec>::processStatus(
  const GoalStatusArrayConstPtr & status, const RoleAttributes  & pub)
{
  std::lock_guard<std::recursive_mutex> lock(data_mutex_);

  std::string cur_status_caller_id =   pub.host_name() + "_" + std::to_string(pub.process_id() ) + "_" + pub.node_name();

  if (status_received_) {
    if (status_caller_id_ != cur_status_caller_id) {
      CONNECTION_WARN << 
        "processStatus: Previously received status from "<< status_caller_id_ <<", but we now received status from  "<< cur_status_caller_id <<". Did the ActionServer change?";
      status_caller_id_ = cur_status_caller_id;
    }
    latest_status_time_ = cyber::Time(status->header().timestamp());
  } else {
    CONNECTION_DEBUG << 
      "processStatus: Just got our first status message from the ActionServer at node " <<cur_status_caller_id;
    status_received_ = true;
    status_caller_id_ = cur_status_caller_id;
    latest_status_time_ = cyber::Time(status->header().timestamp());
  }

  check_connection_condition_.notify_all();
}

// ********* Connection logic *********


template<class ActionSpec>
bool ConnectionMonitor<ActionSpec>::isServerConnected()
{
  std::lock_guard<std::recursive_mutex> lock(data_mutex_);

  if (!status_received_) {
    CONNECTION_DEBUG << "isServerConnected: Didn't receive status yet, so not connected yet";
    return false;
  }

  if (goalSubscribers_.find(status_caller_id_) == goalSubscribers_.end()) {
    CONNECTION_DEBUG << 
      "isServerConnected: Server "<<status_caller_id_ <<" has not yet subscribed to the goal topic, so not connected yet";
    CONNECTION_DEBUG << goalSubscribersString();
    return false;
  }

  if (cancelSubscribers_.find(status_caller_id_) == cancelSubscribers_.end()) {
    CONNECTION_DEBUG << 
      "isServerConnected: Server "<<status_caller_id_ <<"  has not yet subscribed to the cancel topic, so not connected yet";
    CONNECTION_DEBUG <<  cancelSubscribersString();
    return false;
  }

  if (!feedback_sub_->HasWriter()) {
    CONNECTION_DEBUG <<
      "isServerConnected: Client has not yet connected to feedback topic of server " << status_caller_id_;
    return false;
  }

  if (!result_sub_->HasWriter()) {
    CONNECTION_DEBUG << 
      "isServerConnected: Client has not yet connected to result topic of server " << status_caller_id_;
    return false;
  }

  CONNECTION_DEBUG << "isServerConnected: Server  "<< status_caller_id_<<" is fully connected";
  return true;
}
template<class ActionSpec>
bool ConnectionMonitor<ActionSpec>::waitForActionServerToStart(const cyber::Duration & timeout,
  const std::shared_ptr<Node> nh )
{
  if (timeout < cyber::Duration(0, 0)) {
    AERROR <<  "Timeouts can't be negative. Timeout is  " <<  timeout.ToSecond();
  }

  cyber::Time timeout_time = cyber::Time::Now() + timeout;

  std::unique_lock<std::recursive_mutex> lock(data_mutex_);

  if (isServerConnected()) {
    return true;
  }

  // Hardcode how often we check for node.ok()
  cyber::Duration loop_period = cyber::Duration(.5);

  while ( !isServerConnected()) {
    // Determine how long we should wait
    cyber::Duration time_left = timeout_time - cyber::Time::Now();

    // Check if we're past the timeout time
    if (timeout != cyber::Duration(0, 0) && time_left <= cyber::Duration(0, 0) ) {
      break;
    }

    // Truncate the time left
    if (time_left > loop_period || timeout == cyber::Duration()) {
      time_left = loop_period;
    }

    check_connection_condition_.wait_for(lock,
      std::chrono::milliseconds(static_cast<int64_t>(time_left.ToSecond() * 1000.0f)));
  }

  return isServerConnected();
}



}  // namespace actionlib
}

#endif  // ACTIONLIB__CLIENT__CONNECTION_MONITOR_H_
