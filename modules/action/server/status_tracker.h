/*********************************************************************
 *
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
 *   * Neither the name of Willow Garage, Inc. nor the names of its
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
 *
 * Author: Eitan Marder-Eppstein
 *********************************************************************/
#ifndef ACTIONLIB__SERVER__STATUS_TRACKER_H_
#define ACTIONLIB__SERVER__STATUS_TRACKER_H_

#include<mutex>

#include "cyber/time/time.h"

#include "modules/common/proto/action.pb.h"
#include "modules/action/action_definition.h"
#include "modules/action/goal_id_generator.h"



using apollo::common::proto::GoalID;
using apollo::common::proto::GoalStatus;
using apollo::common::proto::GoalStatusType;
using apollo::cyber::Time;

namespace apollo {
namespace actionlib
{

/**
 * @class StatusTracker
 * @brief A class for storing the status of each goal the action server
 * is currently working on
 */
template<class ActionSpec>
class StatusTracker
{
private:
  // generates typedefs that we'll use to make our lives easier
  ACTION_DEFINITION(ActionSpec);

public:
  StatusTracker(const GoalID & goal_id, unsigned int status);

  StatusTracker(const std::shared_ptr<const ActionGoal> & goal);

  std::shared_ptr< const ActionGoal> goal_;
  std::weak_ptr<void> handle_tracker_;
  GoalStatus status_;
  Time handle_destruction_time_;

private:
  GoalIDGenerator id_generator_;
};

template<class ActionSpec>
StatusTracker<ActionSpec>::StatusTracker(const GoalID & goal_id,
  unsigned int status)
{
  // set the goal id and status appropriately
  *status_.mutable_goal_id() = goal_id;
  status_.set_status((GoalStatusType)status);
}

template<class ActionSpec>
StatusTracker<ActionSpec>::StatusTracker(const std::shared_ptr<const ActionGoal> & goal)
: goal_(goal)
{
  // set the goal_id from the message
  *status_.mutable_goal_id() = goal_->goal_id();

  // initialize the status of the goal to pending
  status_.set_status (GoalStatusType::PENDING);

  // if the goal id is zero, then we need to make up an id for the goal
  if (status_.goal_id().id() == "") {
    *(status_.mutable_goal_id()) = id_generator_.generateID();
  }

  // if the timestamp of the goal is zero, then we'll set it to now()
  if (status_.goal_id().timestamp() == Time().ToNanosecond()) {
    status_.mutable_goal_id()->set_timestamp(Time::Now().ToNanosecond());
  }
}


}  // namespace actionlib

}


#endif