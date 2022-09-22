
#ifndef ACTIONLIB__SERVER__ACTION_SERVER_BASE_H_
#define ACTIONLIB__SERVER__ACTION_SERVER_BASE_H_

#include <list>
#include <mutex>

#include "cyber/time/time.h"

#include "modules/common/proto/action.pb.h"
#include "modules/action/goal_id_generator.h"
#include "modules/action/action_definition.h"
#include "server_goal_handle.h"
#include "handle_tracker_deleter.h"


using apollo::common::proto::GoalID;
using apollo::common::proto::GoalStatus;
using apollo::common::proto::GoalStatusType;

namespace apollo {
namespace actionlib
{
/**
 * @class ActionServerBase
 * @brief The ActionServerBase implements the logic for an ActionServer.
 */
template<class ActionSpec>
class ActionServerBase
{
public:
  // for convenience when referring to ServerGoalHandles
  typedef ServerGoalHandle<ActionSpec> GoalHandle;

  // generates typedefs that we'll use to make our lives easier
  ACTION_DEFINITION(ActionSpec);

  /**
   * @brief  Constructor for an ActionServer
   * @param  goal_cb A goal callback to be called when the ActionServer receives a new goal over the wire
   * @param  cancel_cb A cancel callback to be called when the ActionServer receives a new cancel request over the wire
   * @param  auto_start A boolean value that tells the ActionServer whether or not to start publishing as soon as it comes up. THIS SHOULD ALWAYS BE SET TO FALSE TO AVOID RACE CONDITIONS and start() should be called after construction of the server.
   */
  ActionServerBase(
    std::function<void(GoalHandle)> goal_cb,
    std::function<void(GoalHandle)> cancel_cb,
    bool auto_start = false);


  /**
   * @brief  Destructor for the ActionServerBase
   */
  virtual ~ActionServerBase();

  /**
   * @brief  Register a callback to be invoked when a new goal is received, this will replace any  previously registered callback
   * @param  cb The callback to invoke
   */
  void registerGoalCallback(std::function<void(GoalHandle)> cb);

  /**
   * @brief  Register a callback to be invoked when a new cancel is received, this will replace any  previously registered callback
   * @param  cb The callback to invoke
   */
  void registerCancelCallback(std::function<void(GoalHandle)> cb);

  /**
   * @brief  Explicitly start the action server, used it auto_start is set to false
   */
  void start();


  /**
   * @brief  The ROS callback for goals coming into the ActionServerBase
   */
  void goalCallback(const std::shared_ptr<const ActionGoal> & goal);

  /**
   * @brief  The ROS callback for cancel requests coming into the ActionServerBase
   */
  void cancelCallback(const std::shared_ptr<const GoalID> & goal_id);

protected:
  // Allow access to protected fields for helper classes
  friend class ServerGoalHandle<ActionSpec>;
  friend class HandleTrackerDeleter<ActionSpec>;

  /**
   * @brief  Initialize all ROS connections and setup timers
   */
  virtual void initialize() = 0;

  /**
   * @brief  Publishes a result for a given goal
   * @param status The status of the goal with which the result is associated
   * @param result The result to publish
   */
  virtual void publishResult(const GoalStatus & status, const Result & result) = 0;

  /**
   * @brief  Publishes feedback for a given goal
   * @param status The status of the goal with which the feedback is associated
   * @param feedback The feedback to publish
   */
  virtual void publishFeedback(const GoalStatus & status,
    const Feedback & feedback) = 0;

  /**
   * @brief  Explicitly publish status
   */
  virtual void publishStatus() = 0;

  std::recursive_mutex lock_;

  std::list<StatusTracker<ActionSpec> > status_list_;

  std::function<void(GoalHandle)> goal_callback_;
  std::function<void(GoalHandle)> cancel_callback_;

  apollo::cyber::Time last_cancel_;
  apollo::cyber::Duration status_list_timeout_;

  GoalIDGenerator id_generator_;
  bool started_;
  std::shared_ptr<DestructionGuard> guard_;
};

template<class ActionSpec>
ActionServerBase<ActionSpec>::ActionServerBase(
  std::function<void(GoalHandle)> goal_cb,
  std::function<void(GoalHandle)> cancel_cb,
  bool auto_start)
: goal_callback_(goal_cb),
  cancel_callback_(cancel_cb),
  started_(auto_start),
  guard_(new DestructionGuard)
{
}

template<class ActionSpec>
ActionServerBase<ActionSpec>::~ActionServerBase()
{
  // Block until we can safely destruct
  guard_->destruct();
}

template<class ActionSpec>
void ActionServerBase<ActionSpec>::registerGoalCallback(std::function<void(GoalHandle)> cb)
{
  goal_callback_ = cb;
}

template<class ActionSpec>
void ActionServerBase<ActionSpec>::registerCancelCallback(std::function<void(GoalHandle)> cb)
{
  cancel_callback_ = cb;
}

template<class ActionSpec>
void ActionServerBase<ActionSpec>::start()
{
  initialize();
  started_ = true;
  publishStatus();
}


template<class ActionSpec>
void ActionServerBase<ActionSpec>::goalCallback(const std::shared_ptr<const ActionGoal> & goal)
{
  std::unique_lock<std::recursive_mutex> lock(lock_,std::try_to_lock);

  // if we're not started... then we're not actually going to do anything
  if (!started_) {
    return;
  }

  ADEBUG << "The action server has received a new goal request";

  // we need to check if this goal already lives in the status list
  for (typename std::list<StatusTracker<ActionSpec> >::iterator it = status_list_.begin();
    it != status_list_.end(); ++it)
  {
    if (goal->goal_id().id() == (*it).status_.goal_id().id()) {
      // The goal could already be in a recalling state if a cancel came in before the goal
      if ( (*it).status_.status() == GoalStatusType::RECALLING) {
        (*it).status_.set_status(GoalStatusType::RECALLED) ;
        publishResult((*it).status_, Result());
      }

      // if this is a request for a goal that has no active handles left,
      // we'll bump how long it stays in the list
      if ((*it).handle_tracker_.expired()) {
        (*it).handle_destruction_time_ = cyber::Time(goal->goal_id().timestamp());
      }

      // make sure not to call any user callbacks or add duplicate status onto the list
      return;
    }
  }

  // if the goal is not in our list, we need to create a StatusTracker associated with this goal and push it on
  typename std::list<StatusTracker<ActionSpec> >::iterator it = status_list_.insert(
    status_list_.end(), StatusTracker<ActionSpec>(goal));

  // we need to create a handle tracker for the incoming goal and update the StatusTracker
  HandleTrackerDeleter<ActionSpec> d(this, it, guard_);
  std::shared_ptr<void> handle_tracker((void *)NULL, d);
  (*it).handle_tracker_ = handle_tracker;

  // check if this goal has already been canceled based on its timestamp
  if (goal->goal_id().timestamp() != cyber::Time::Now().ToNanosecond() && goal->goal_id().timestamp() <= last_cancel_.ToNanosecond()) {
    // if it has... just create a GoalHandle for it and setCanceled
    GoalHandle gh(it, this, handle_tracker, guard_);

    gh.setCanceled(
      Result(),
      "This goal handle was canceled by the action server because its timestamp is before the timestamp of the last cancel request");
  } else {
    GoalHandle gh = GoalHandle(it, this, handle_tracker, guard_);

    // make sure that we unlock before calling the users callback
    lock.unlock();

    // now, we need to create a goal handle and call the user's callback
    goal_callback_(gh);
  }
}

template<class ActionSpec>
void ActionServerBase<ActionSpec>::cancelCallback(
  const std::shared_ptr<const GoalID> & goal_id)
{
  std::unique_lock<std::recursive_mutex> lock(lock_,std::try_to_lock);

  // if we're not started... then we're not actually going to do anything
  if (!started_) {
    return;
  }

  // we need to handle a cancel for the user
  ADEBUG << "The action server has received a new cancel request";
  bool goal_id_found = false;
  for (typename std::list<StatusTracker<ActionSpec> >::iterator it = status_list_.begin();
    it != status_list_.end(); ++it)
  {
    // check if the goal id is zero or if it is equal to the goal id of
    // the iterator or if the time of the iterator warrants a cancel
    if (
      (goal_id->id() == "" && goal_id->timestamp() == apollo::cyber::Time(0,0).ToNanosecond() ) ||  // id and stamp 0 --> cancel everything
      goal_id->id() == (*it).status_.goal_id().id() ||    // ids match... cancel that goal
      (goal_id->timestamp() !=  apollo::cyber::Time(0,0).ToNanosecond() && (*it).status_.goal_id().timestamp() <= goal_id->timestamp())       // stamp != 0 --> cancel everything before stamp
    )
    {
      // we need to check if we need to store this cancel request for later
      if (goal_id->id() == (*it).status_.goal_id().id()) {
        goal_id_found = true;
      }

      // attempt to get the handle_tracker for the list item if it exists
      std::shared_ptr<void> handle_tracker = (*it).handle_tracker_.lock();

      if ((*it).handle_tracker_.expired()) {
        // if the handle tracker is expired, then we need to create a new one
        HandleTrackerDeleter<ActionSpec> d(this, it, guard_);
        handle_tracker = std::shared_ptr<void>((void *)NULL, d);
        (*it).handle_tracker_ = handle_tracker;

        // we also need to reset the time that the status is supposed to be removed from the list
        (*it).handle_destruction_time_ = cyber::Time();
      }

      // set the status of the goal to PREEMPTING or RECALLING as appropriate
      // and check if the request should be passed on to the user
      GoalHandle gh(it, this, handle_tracker, guard_);
      if (gh.setCancelRequested()) {
        // make sure that we're unlocked before we call the users callback
        lock.unlock();

        // call the user's cancel callback on the relevant goal
        cancel_callback_(gh);
      }
    }
  }

  // if the requested goal_id was not found, and it is non-zero, then we need to store the cancel request
  if (goal_id->id() != "" && !goal_id_found) {
    typename std::list<StatusTracker<ActionSpec> >::iterator it = status_list_.insert(
      status_list_.end(),
      StatusTracker<ActionSpec>(*goal_id, GoalStatusType::RECALLING));
    // start the timer for how long the status will live in the list without a goal handle to it
    (*it).handle_destruction_time_ = cyber::Time(goal_id->timestamp());
  }

  // make sure to set last_cancel_ based on the stamp associated with this cancel request
  if (goal_id->timestamp() > last_cancel_.ToNanosecond()) {
    last_cancel_= cyber::Time(goal_id->timestamp());
  }
}

}  // namespace actionlib
}
#endif  // ACTIONLIB__SERVER__ACTION_SERVER_BASE_H_
