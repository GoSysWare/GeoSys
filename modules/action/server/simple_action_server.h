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
#ifndef ACTIONLIB__SERVER__SIMPLE_ACTION_SERVER_H_
#define ACTIONLIB__SERVER__SIMPLE_ACTION_SERVER_H_

#include "action_server.h"
#include "modules/action/action_definition.h"

#include <string>
namespace apollo {
namespace actionlib
{
/** @class SimpleActionServer @brief The SimpleActionServer
 * implements a single goal policy on top of the ActionServer class. The
 * specification of the policy is as follows: only one goal can have an
 * active status at a time, new goals preempt previous goals based on the
 * stamp in their GoalID field (later goals preempt earlier ones), an
 * explicit preempt goal preempts all goals with timestamps that are less
 * than or equal to the stamp associated with the preempt, accepting a new
 * goal implies successful preemption of any old goal and the status of the
 * old goal will be changed automatically to reflect this.
 */
template<class ActionSpec>
class SimpleActionServer
{
public:
  // generates typedefs that we'll use to make our lives easier
  ACTION_DEFINITION(ActionSpec);

  typedef typename ActionServer<ActionSpec>::GoalHandle GoalHandle;
  typedef std::function<void (const GoalConstPtr &)> ExecuteCallback;


  /**
   * @brief  Constructor for a SimpleActionServer
   * @param n A NodeHandle to create a namespace under
   * @param name A name for the action server
   * @param execute_callback Optional callback that gets called in a separate thread whenever
   *                         a new goal is received, allowing users to have blocking callbacks.
   *                         Adding an execute callback also deactivates the goalCallback.
   * @param  auto_start A boolean value that tells the ActionServer whether or not to start publishing as soon as it comes up. THIS SHOULD ALWAYS BE SET TO FALSE TO AVOID RACE CONDITIONS and start() should be called after construction of the server.
   */
  SimpleActionServer( std::shared_ptr<Node> n, std::string name, ExecuteCallback execute_callback,
    bool auto_start);

  /**
   * @brief  Constructor for a SimpleActionServer
   * @param n A NodeHandle to create a namespace under
   * @param name A name for the action server
   * @param  auto_start A boolean value that tells the ActionServer whether or not to start publishing as soon as it comes up. THIS SHOULD ALWAYS BE SET TO FALSE TO AVOID RACE CONDITIONS and start() should be called after construction of the server.
   */
  SimpleActionServer( std::shared_ptr<Node> n,std::string name, bool auto_start);




  ~SimpleActionServer();

  /**
   * @brief  Accepts a new goal when one is available. The status of this
   * goal is set to active upon acceptance, and the status of any
   * previously active goal is set to preempted. Preempts received for the
   * new goal between checking if isNewGoalAvailable or invocation of a
   * goal callback and the acceptNewGoal call will not trigger a preempt
   * callback.  This means, isPreemptRequested should be called after
   * accepting the goal even for callback-based implementations to make
   * sure the new goal does not have a pending preempt request.
   * @return A shared_ptr to the new goal.
   */
  std::shared_ptr<const Goal> acceptNewGoal();

  /**
   * @brief  Allows polling implementations to query about the availability of a new goal
   * @return True if a new goal is available, false otherwise
   */
  bool isNewGoalAvailable();


  /**
   * @brief  Allows polling implementations to query about preempt requests
   * @return True if a preempt is requested, false otherwise
   */
  bool isPreemptRequested();

  /**
   * @brief  Allows polling implementations to query about the status of the current goal
   * @return True if a goal is active, false otherwise
   */
  bool isActive();

  /**
   * @brief  Sets the status of the active goal to succeeded
   * @param  result An optional result to send back to any clients of the goal
   * @param  result An optional text message to send back to any clients of the goal
   */
  void setSucceeded(const Result & result = Result(), const std::string & text = std::string(""));

  /**
   * @brief  Sets the status of the active goal to aborted
   * @param  result An optional result to send back to any clients of the goal
   * @param  result An optional text message to send back to any clients of the goal
   */
  void setAborted(const Result & result = Result(), const std::string & text = std::string(""));


  /**
  * @brief  Publishes feedback for a given goal
  * @param  feedback Shared pointer to the feedback to publish
  */
  void publishFeedback(const FeedbackConstPtr & feedback);

  /**
  * @brief  Publishes feedback for a given goal
  * @param  feedback The feedback to publish
  */
  void publishFeedback(const Feedback & feedback);

  /**
   * @brief  Sets the status of the active goal to preempted
   * @param  result An optional result to send back to any clients of the goal
   * @param  result An optional text message to send back to any clients of the goal
   */
  void setPreempted(const Result & result = Result(), const std::string & text = std::string(""));

  /**
   * @brief  Allows users to register a callback to be invoked when a new goal is available
   * @param cb The callback to be invoked
   */
  void registerGoalCallback(std::function<void()> cb);

  /**
   * @brief  Allows users to register a callback to be invoked when a new preempt request is available
   * @param cb The callback to be invoked
   */
  void registerPreemptCallback(std::function<void()> cb);

  /**
   * @brief  Explicitly start the action server, used it auto_start is set to false
   */
  void start();

  /**
   * @brief  Explicitly shutdown the action server
   */
  void shutdown();

private:
  /**
   * @brief  Callback for when the ActionServer receives a new goal and passes it on
   */
  void goalCallback(GoalHandle goal);

  /**
   * @brief  Callback for when the ActionServer receives a new preempt and passes it on
   */
  void preemptCallback(GoalHandle preempt);

  /**
   * @brief  Called from a separate thread to call blocking execute calls
   */
  void executeLoop();

  std::shared_ptr<Node> n_;

  std::shared_ptr<ActionServer<ActionSpec> > as_;

  GoalHandle current_goal_, next_goal_;

  bool new_goal_, preempt_request_, new_goal_preempt_request_;

  std::recursive_mutex lock_;

  std::function<void()> goal_callback_;
  std::function<void()> preempt_callback_;
  ExecuteCallback execute_callback_;

  std::condition_variable_any execute_condition_;
  std::thread * execute_thread_;

  std::mutex terminate_mutex_;
  bool need_to_terminate_;
};




template<class ActionSpec>
SimpleActionServer<ActionSpec>::SimpleActionServer( std::shared_ptr<Node> n, std::string name,
  ExecuteCallback execute_callback,
  bool auto_start)
: n_(n), new_goal_(false), preempt_request_(false), new_goal_preempt_request_(false),
  execute_callback_(execute_callback), execute_thread_(NULL), need_to_terminate_(false)
{
  // create the action server
  as_ = std::shared_ptr<ActionServer<ActionSpec> >(new ActionServer<ActionSpec>(n, name,
      std::bind(&SimpleActionServer::goalCallback, this, std::placeholders::_1),
      std::bind(&SimpleActionServer::preemptCallback, this, std::placeholders::_1),
      auto_start));

  if (execute_callback_ != NULL) {
    execute_thread_ = new std::thread(std::bind(&SimpleActionServer::executeLoop, this));
  }
}

template<class ActionSpec>
SimpleActionServer<ActionSpec>::SimpleActionServer( std::shared_ptr<Node> n,std::string name,
  bool auto_start)
: n_(n), new_goal_(false), preempt_request_(false), new_goal_preempt_request_(false),
  execute_callback_(NULL), execute_thread_(NULL), need_to_terminate_(false)
{
  // create the action server
  as_ = std::shared_ptr<ActionServer<ActionSpec> >(new ActionServer<ActionSpec>(n, name,
      std::bind(&SimpleActionServer::goalCallback, this, std::placeholders::_1),
      std::bind(&SimpleActionServer::preemptCallback, this, std::placeholders::_1),
      auto_start));

  if (execute_callback_ != NULL) {
    execute_thread_ = new std::thread(std::bind(&SimpleActionServer::executeLoop, this));
  }
}




template<class ActionSpec>
SimpleActionServer<ActionSpec>::~SimpleActionServer()
{
  if (execute_thread_) {
    shutdown();
  }
}

template<class ActionSpec>
void SimpleActionServer<ActionSpec>::shutdown()
{
  if (execute_callback_) {
    {
        std::lock_guard<std::mutex> lock(this->terminate_mutex_);

      need_to_terminate_ = true;
    }

    assert(execute_thread_);
    if (execute_thread_) {
      execute_thread_->join();
      delete execute_thread_;
      execute_thread_ = NULL;
    }
  }
}

template<class ActionSpec>
std::shared_ptr<const typename SimpleActionServer<ActionSpec>::Goal> SimpleActionServer<ActionSpec>
::acceptNewGoal()
{
  std::lock_guard<std::recursive_mutex> lock(this->lock_);

  if (!new_goal_ || !next_goal_.getGoal()) {
    AERROR << 
      "Attempting to accept the next goal when a new goal is not available";
    return std::shared_ptr<const Goal>();
  }

  // check if we need to send a preempted message for the goal that we're currently pursuing
  if (isActive() &&
    current_goal_.getGoal() &&
    current_goal_ != next_goal_)
  {
    current_goal_.setCanceled(
      Result(),
      "This goal was canceled because another goal was recieved by the simple action server");
  }

  ADEBUG << "Accepting a new goal";

  // accept the next goal
  current_goal_ = next_goal_;
  new_goal_ = false;

  // set preempt to request to equal the preempt state of the new goal
  preempt_request_ = new_goal_preempt_request_;
  new_goal_preempt_request_ = false;

  // set the status of the current goal to be active
  current_goal_.setAccepted("This goal has been accepted by the simple action server");

  return current_goal_.getGoal();
}

template<class ActionSpec>
bool SimpleActionServer<ActionSpec>::isNewGoalAvailable()
{
  return new_goal_;
}


template<class ActionSpec>
bool SimpleActionServer<ActionSpec>::isPreemptRequested()
{
  return preempt_request_;
}

template<class ActionSpec>
bool SimpleActionServer<ActionSpec>::isActive()
{
  if (!current_goal_.getGoal()) {
    return false;
  }
  unsigned int status = current_goal_.getGoalStatus().status();
  return status == GoalStatusType::ACTIVE ||
         status == GoalStatusType::PREEMPTING;
}

template<class ActionSpec>
void SimpleActionServer<ActionSpec>::setSucceeded(const Result & result, const std::string & text)
{
  std::lock_guard<std::recursive_mutex> lock(this->lock_);
  ADEBUG << 
  "Setting the current goal as succeeded";
  current_goal_.setSucceeded(result, text);
}

template<class ActionSpec>
void SimpleActionServer<ActionSpec>::setAborted(const Result & result, const std::string & text)
{
  std::lock_guard<std::recursive_mutex> lock(this->lock_);
  ADEBUG << 
  "Setting the current goal as aborted";
  current_goal_.setAborted(result, text);
}

template<class ActionSpec>
void SimpleActionServer<ActionSpec>::setPreempted(const Result & result, const std::string & text)
{
  std::lock_guard<std::recursive_mutex> lock(this->lock_);
  ADEBUG << 
  "Setting the current goal as canceled";
  current_goal_.setCanceled(result, text);
}

template<class ActionSpec>
void SimpleActionServer<ActionSpec>::registerGoalCallback(std::function<void()> cb)
{
  // Cannot register a goal callback if an execute callback exists
  if (execute_callback_) {
  ADEBUG << 
      "Cannot call SimpleActionServer::registerGoalCallback() because an executeCallback exists. Not going to register it.";
  } else {
    goal_callback_ = cb;
  }
}

template<class ActionSpec>
void SimpleActionServer<ActionSpec>::registerPreemptCallback(std::function<void()> cb)
{
  preempt_callback_ = cb;
}

template<class ActionSpec>
void SimpleActionServer<ActionSpec>::publishFeedback(const FeedbackConstPtr & feedback)
{
  current_goal_.publishFeedback(*feedback);
}

template<class ActionSpec>
void SimpleActionServer<ActionSpec>::publishFeedback(const Feedback & feedback)
{
  current_goal_.publishFeedback(feedback);
}

template<class ActionSpec>
void SimpleActionServer<ActionSpec>::goalCallback(GoalHandle goal)
{
  std::lock_guard<std::recursive_mutex> lock(this->lock_);
  ADEBUG << 
   "A new goal has been recieved by the single goal action server";

  // check that the timestamp is past or equal to that of the current goal and the next goal
  if ((!current_goal_.getGoal() || goal.getGoalID().timestamp() >= current_goal_.getGoalID().timestamp()) &&
    (!next_goal_.getGoal() || goal.getGoalID().timestamp() >= next_goal_.getGoalID().timestamp()))
  {
    // if next_goal has not been accepted already... its going to get bumped, but we need to let the client know we're preempting
    if (next_goal_.getGoal() && (!current_goal_.getGoal() || next_goal_ != current_goal_)) {
      next_goal_.setCanceled(
        Result(),
        "This goal was canceled because another goal was recieved by the simple action server");
    }

    next_goal_ = goal;
    new_goal_ = true;
    new_goal_preempt_request_ = false;

    // if the server is active, we'll want to call the preempt callback for the current goal
    if (isActive()) {
      preempt_request_ = true;
      // if the user has registered a preempt callback, we'll call it now
      if (preempt_callback_) {
        preempt_callback_();
      }
    }

    // if the user has defined a goal callback, we'll call it now
    if (goal_callback_) {
      goal_callback_();
    }

    // Trigger runLoop to call execute()
    execute_condition_.notify_all();
  } else {
    // the goal requested has already been preempted by a different goal, so we're not going to execute it
    goal.setCanceled(
      Result(),
      "This goal was canceled because another goal was recieved by the simple action server");
  }
}

template<class ActionSpec>
void SimpleActionServer<ActionSpec>::preemptCallback(GoalHandle preempt)
{
  std::lock_guard<std::recursive_mutex> lock(this->lock_);
  
  ADEBUG <<
  "A preempt has been received by the SimpleActionServer";

  // if the preempt is for the current goal, then we'll set the preemptRequest flag and call the user's preempt callback
  if (preempt == current_goal_) {
     ADEBUG <<
      "Setting preempt_request bit for the current goal to TRUE and invoking callback";
    preempt_request_ = true;

    // if the user has registered a preempt callback, we'll call it now
    if (preempt_callback_) {
      preempt_callback_();
    }
  } else if (preempt == next_goal_) {
    // if the preempt applies to the next goal, we'll set the preempt bit for that
    ADEBUG <<
    "Setting preempt request bit for the next goal to TRUE";
    new_goal_preempt_request_ = true;
  }
}

template<class ActionSpec>
void SimpleActionServer<ActionSpec>::executeLoop()
{
  cyber::Duration loop_duration = cyber::Duration(0.1);

  while (apollo::cyber::OK()) {
    {
      std::lock_guard<std::mutex> terminate_lock(this->terminate_mutex_);

      if (need_to_terminate_) {
        break;
      }
    } 
    std::unique_lock<std::recursive_mutex>lock(lock_,std::try_to_lock);
    if (isActive()) {
      AERROR <<
       "Should never reach this code with an active goal";
    } 
    else if (isNewGoalAvailable()) {
      GoalConstPtr goal = acceptNewGoal();

      if(!execute_callback_)
      {
      AFATAL << 
        "execute_callback_ must exist. This is a bug in SimpleActionServer";
      }
      else
      {
        // Make sure we're not locked when we call execute
        lock.unlock();
        execute_callback_(goal);
      }
      if (isActive()) {

        AWARN  << "Your executeCallback did not set the goal to a terminal status.\n"
          "This is a bug in your ActionServer implementation. Fix your code!\n"
          "For now, the ActionServer will set this goal to aborted";
        setAborted(
          Result(),
          "This goal was aborted by the simple action server. The user should have set a terminal status on this goal and did not");
      }
    } else {

      execute_condition_.wait_for(lock,std::chrono::milliseconds(loop_duration.ToNanosecond() / (1000*1000)));
    }
  }
}

template<class ActionSpec>
void SimpleActionServer<ActionSpec>::start()
{
  as_->start();
}

}  // namespace actionlib
}


#endif  // ACTIONLIB__SERVER__SIMPLE_ACTION_SERVER_H_
