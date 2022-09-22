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

#ifndef ACTIONLIB__CLIENT__CLIENT_HELPERS_H_
#define ACTIONLIB__CLIENT__CLIENT_HELPERS_H_


#include <vector>

#include "cyber/common/log.h"
#include "cyber/time/time.h"
#include "cyber/node/node.h"

#include "modules/action/action_definition.h"
#include "modules/action/managed_list.h"
#include "modules/action/enclosure_deleter.h"
#include "modules/action/goal_id_generator.h"
#include "modules/action/destruction_guard.h"

#include "comm_state.h"

#include "terminal_state.h"


// msgs
#include "modules/common/proto/action.pb.h"

using apollo::cyber::Node;
using apollo::cyber::Writer;
using apollo::cyber::Reader;

using apollo::common::proto::GoalID;
using apollo::common::proto::GoalStatus;
using apollo::common::proto::GoalStatusType;
using apollo::common::proto::GoalStatusArray;

using GoalStatusArrayConstPtr = std::shared_ptr< const GoalStatusArray >;
using GoalStatusArrayPtr = std::shared_ptr<  GoalStatusArray >;


namespace apollo {
namespace actionlib
{

template<class ActionSpec>
class ClientGoalHandle;

template<class ActionSpec>
class CommStateMachine;

template<class ActionSpec>
class GoalManager
{
public:
  ACTION_DEFINITION(ActionSpec);
  typedef GoalManager<ActionSpec> GoalManagerT;
  typedef ClientGoalHandle<ActionSpec> GoalHandleT;
  typedef std::function<void (GoalHandleT)> TransitionCallback;
  typedef std::function<void (GoalHandleT, const FeedbackConstPtr &)> FeedbackCallback;
  typedef std::function<void ( ActionGoalPtr)> SendGoalFunc;
  typedef std::function<void ( std::shared_ptr<GoalID> )> CancelFunc;

  GoalManager(const std::shared_ptr<DestructionGuard> & guard)
  : guard_(guard) {}

  void registerSendGoalFunc(SendGoalFunc send_goal_func);
  void registerCancelFunc(CancelFunc cancel_func);

  GoalHandleT initGoal(const Goal & goal,
    TransitionCallback transition_cb = TransitionCallback(),
    FeedbackCallback feedback_cb = FeedbackCallback() );

  void updateStatuses(const  GoalStatusArrayConstPtr & status_array);
  void updateFeedbacks(const ActionFeedbackConstPtr & action_feedback);
  void updateResults(const ActionResultConstPtr & action_result);

  friend class ClientGoalHandle<ActionSpec>;

  // should be private
  typedef ManagedList<std::shared_ptr<CommStateMachine<ActionSpec> > > ManagedListT;
  ManagedListT list_;

private:
  SendGoalFunc send_goal_func_;
  CancelFunc cancel_func_;

  std::shared_ptr<DestructionGuard> guard_;

  std::recursive_mutex list_mutex_;

  GoalIDGenerator id_generator_;

  void listElemDeleter(typename ManagedListT::iterator it);
};

/**
 * \brief Client side handle to monitor goal progress
 *
 * A ClientGoalHandle is a reference counted object that is used to manipulate and monitor the progress
 * of an already dispatched goal. Once all the goal handles go out of scope (or are reset), an
 * ActionClient stops maintaining state for that goal.
 */
template<class ActionSpec>
class ClientGoalHandle
{
private:
  ACTION_DEFINITION(ActionSpec);

public:
  /**
   * \brief Create an empty goal handle
   *
   * Constructs a goal handle that doesn't track any goal. Calling any method on an empty goal
   * handle other than operator= will trigger an assertion.
   */
  ClientGoalHandle();

  ~ClientGoalHandle();

  /**
   * \brief Stops goal handle from tracking a goal
   *
   * Useful if you want to stop tracking the progress of a goal, but it is inconvenient to force
   * the goal handle to go out of scope. Has pretty much the same semantics as std::shared_ptr::reset()
   */
  void reset();

  /**
   * \brief Checks if this goal handle is tracking a goal
   *
   * Has pretty much the same semantics as std::shared_ptr::expired()
   * \return True if this goal handle is not tracking a goal
   */
  inline bool isExpired() const;

  /**
   * \brief Get the state of this goal's communication state machine from interaction with the server
   *
   * Possible States are: WAITING_FOR_GOAL_ACK, PENDING, ACTIVE, WAITING_FOR_RESULT,
   *                      WAITING_FOR_CANCEL_ACK, RECALLING, PREEMPTING, DONE
   * \return The current goal's communication state with the server
   */
  CommState getCommState() const;

  /**
   * \brief Get the terminal state information for this goal
   *
   * Possible States Are: RECALLED, REJECTED, PREEMPTED, ABORTED, SUCCEEDED, LOST
   * This call only makes sense if CommState==DONE. This will send ROS_WARNs if we're not in DONE
   * \return The terminal state
   */
  TerminalState getTerminalState() const;

  /**
   * \brief Get result associated with this goal
   *
   * \return NULL if no result received.  Otherwise returns shared_ptr to result.
   */
  ResultConstPtr getResult() const;

  /**
   * \brief Resends this goal [with the same GoalID] to the ActionServer
   *
   * Useful if the user thinks that the goal may have gotten lost in transit
   */
  void resend();

  /**
   * \brief Sends a cancel message for this specific goal to the ActionServer
   *
   * Also transitions the Communication State Machine to WAITING_FOR_CANCEL_ACK
   */
  void cancel();

  /**
   * \brief Check if two goal handles point to the same goal
   * \return TRUE if both point to the same goal. Also returns TRUE if both handles are inactive.
   */
  bool operator==(const ClientGoalHandle<ActionSpec> & rhs) const;

  /**
   * \brief !(operator==())
   */
  bool operator!=(const ClientGoalHandle<ActionSpec> & rhs) const;

  friend class GoalManager<ActionSpec>;

private:
  typedef GoalManager<ActionSpec> GoalManagerT;
  typedef ManagedList<std::shared_ptr<CommStateMachine<ActionSpec> > > ManagedListT;

  ClientGoalHandle(GoalManagerT * gm, typename ManagedListT::Handle handle,
    const std::shared_ptr<DestructionGuard> & guard);

  GoalManagerT * gm_;
  bool active_;
  // typename ManagedListT::iterator it_;
  std::shared_ptr<DestructionGuard> guard_;  // Guard must still exist when the list_handle_ is destroyed
  typename ManagedListT::Handle list_handle_;
};

template<class ActionSpec>
class CommStateMachine
{
private:
  // generates typedefs that we'll use to make our lives easier
  ACTION_DEFINITION(ActionSpec);

public:
  typedef std::function<void (const ClientGoalHandle<ActionSpec> &)> TransitionCallback;
  typedef std::function<void (const ClientGoalHandle<ActionSpec> &,
    const FeedbackConstPtr &)> FeedbackCallback;
  typedef ClientGoalHandle<ActionSpec> GoalHandleT;

  CommStateMachine(const ActionGoalPtr & action_goal,
    TransitionCallback transition_cb,
    FeedbackCallback feedback_cb);

  ActionGoalPtr getActionGoal() const;
  CommState getCommState() const;
  GoalStatus getGoalStatus() const;
  ResultConstPtr getResult() const;

  // Transitions caused by messages
  void updateStatus(GoalHandleT & gh, const  GoalStatusArrayConstPtr & status_array);
  void updateFeedback(GoalHandleT & gh, const ActionFeedbackConstPtr & action_feedback);
  void updateResult(GoalHandleT & gh, const ActionResultConstPtr & action_result);

  // Forced transitions
  void transitionToState(GoalHandleT & gh, const CommState::StateEnum & next_state);
  void transitionToState(GoalHandleT & gh, const CommState & next_state);
  void processLost(GoalHandleT & gh);

private:
  CommStateMachine();

  // State
  CommState state_;
  ActionGoalPtr action_goal_;
  GoalStatus latest_goal_status_;
  ActionResultConstPtr latest_result_;

  // Callbacks
  TransitionCallback transition_cb_;
  FeedbackCallback feedback_cb_;

  // **** Implementation ****
  //! Change the state, as well as print out ROS_DEBUG info
  void setCommState(const CommState & state);
  void setCommState(const CommState::StateEnum & state);
  const GoalStatus * findGoalStatus(
    const GoalStatusArrayConstPtr & status_vec) const;
};





template<class ActionSpec>
ClientGoalHandle<ActionSpec>::ClientGoalHandle()
{
  gm_ = NULL;
  active_ = false;
}

template<class ActionSpec>
ClientGoalHandle<ActionSpec>::~ClientGoalHandle()
{
  reset();
}

template<class ActionSpec>
ClientGoalHandle<ActionSpec>::ClientGoalHandle(GoalManagerT * gm,
  typename ManagedListT::Handle handle,
  const std::shared_ptr<DestructionGuard> & guard)
{
  gm_ = gm;
  active_ = true;
  list_handle_ = handle;
  guard_ = guard;
}

template<class ActionSpec>
void ClientGoalHandle<ActionSpec>::reset()
{
  if (active_) {
    DestructionGuard::ScopedProtector protector(*guard_);
    if (!protector.isProtected()) {
      AERROR << 
        "This action client associated with the goal handle has already been destructed. Ignoring this reset() call";
      return;
    }

    std::lock_guard<std::recursive_mutex> lock(gm_->list_mutex_);
    list_handle_.reset();
    active_ = false;
    gm_ = NULL;
  }
}

template<class ActionSpec>
bool ClientGoalHandle<ActionSpec>::isExpired() const
{
  return !active_;
}


template<class ActionSpec>
CommState ClientGoalHandle<ActionSpec>::getCommState() const
{
  assert(gm_);
  if (!gm_) {
    AERROR <<  "Client should have valid GoalManager";
    return CommState(CommState::DONE);
  }

    std::lock_guard<std::recursive_mutex> lock(gm_->list_mutex_);
  if (!active_) {
    AERROR << 
      "Trying to getCommState on an inactive ClientGoalHandle. You are incorrectly using a ClientGoalHandle";
    return CommState(CommState::DONE);
  }

  DestructionGuard::ScopedProtector protector(*guard_);
  if (!protector.isProtected()) {
    AERROR << 
      "This action client associated with the goal handle has already been destructed. Ignoring this getCommState() call";
    return CommState(CommState::DONE);
  }

  return list_handle_.getElem()->getCommState();
}

template<class ActionSpec>
TerminalState ClientGoalHandle<ActionSpec>::getTerminalState() const
{
  if (!active_) {
    AERROR << 
      "Trying to getTerminalState on an inactive ClientGoalHandle. You are incorrectly using a ClientGoalHandle";
    return TerminalState(TerminalState::LOST);
  }

  DestructionGuard::ScopedProtector protector(*guard_);
  if (!protector.isProtected()) {
    AERROR << 
      "This action client associated with the goal handle has already been destructed. Ignoring this getTerminalState() call";
    return TerminalState(TerminalState::LOST);
  }

  assert(gm_);
  if (!gm_)
  {
    AERROR <<  "Client should have valid GoalManager";
    return TerminalState(TerminalState::LOST);
  }

    std::lock_guard<std::recursive_mutex> lock(gm_->list_mutex_);
  CommState comm_state_ = list_handle_.getElem()->getCommState();
  if (comm_state_ != CommState::DONE) {
    AWARN << "Asking for the terminal state when we're in " << comm_state_.toString();
  }

  GoalStatus goal_status = list_handle_.getElem()->getGoalStatus();

  switch (goal_status.status()) {
    case GoalStatusType::PENDING:
    case GoalStatusType::ACTIVE:
    case GoalStatusType::PREEMPTING:
    case GoalStatusType::RECALLING:
      AERROR <<  "Asking for terminal state, but latest goal status is " << (int)goal_status.status(); 
        return TerminalState(TerminalState::LOST,
               goal_status.text());
    case GoalStatusType::PREEMPTED: return TerminalState(TerminalState::PREEMPTED,
               goal_status.text());
    case GoalStatusType::SUCCEEDED: return TerminalState(TerminalState::SUCCEEDED,
               goal_status.text());
    case GoalStatusType::ABORTED:   return TerminalState(TerminalState::ABORTED,
               goal_status.text());
    case GoalStatusType::REJECTED:  return TerminalState(TerminalState::REJECTED,
               goal_status.text());
    case GoalStatusType::RECALLED:  return TerminalState(TerminalState::RECALLED,
               goal_status.text());
    case GoalStatusType::LOST:      return TerminalState(TerminalState::LOST,
               goal_status.text());
    default:
      AERROR <<  "Unknown goal status: " << goal_status.status(); break;
  }

  AERROR <<  "Bug in determining terminal state";
  return TerminalState(TerminalState::LOST, goal_status.text());
}

template<class ActionSpec>
typename ClientGoalHandle<ActionSpec>::ResultConstPtr ClientGoalHandle<ActionSpec>::getResult()
const
{
  if (!active_) {
    AERROR << 
      "Trying to getResult on an inactive ClientGoalHandle. You are incorrectly using a ClientGoalHandle";
  }
  assert(gm_);
  if (!gm_) {
    AERROR <<  "Client should have valid GoalManager";
    return typename ClientGoalHandle<ActionSpec>::ResultConstPtr() ;
  }

  DestructionGuard::ScopedProtector protector(*guard_);
  if (!protector.isProtected()) {
    AERROR << 
      "This action client associated with the goal handle has already been destructed. Ignoring this getResult() call";
    return typename ClientGoalHandle<ActionSpec>::ResultConstPtr();
  }

  std::lock_guard<std::recursive_mutex> lock(gm_->list_mutex_);
  return list_handle_.getElem()->getResult();
}

template<class ActionSpec>
void ClientGoalHandle<ActionSpec>::resend()
{
  if (!active_) {
    AERROR << 
      "Trying to resend() on an inactive ClientGoalHandle. You are incorrectly using a ClientGoalHandle";
  }

  DestructionGuard::ScopedProtector protector(*guard_);
  if (!protector.isProtected()) {
    AERROR << 
      "This action client associated with the goal handle has already been destructed. Ignoring this resend() call";
    return;
  }

  assert(gm_);
  if (!gm_)
  {
    AERROR <<  "Client should have valid GoalManager";
    return;
  }

  std::lock_guard<std::recursive_mutex> lock(gm_->list_mutex_);

  ActionGoalPtr action_goal = list_handle_.getElem()->getActionGoal();

  if (!action_goal) {
    AERROR <<  "BUG: Got a NULL action_goal";
  }

  if (gm_->send_goal_func_) {
    gm_->send_goal_func_(action_goal);
  }
}

template<class ActionSpec>
void ClientGoalHandle<ActionSpec>::cancel()
{
  if (!active_) {
    AERROR << 
      "Trying to cancel() on an inactive ClientGoalHandle. You are incorrectly using a ClientGoalHandle";
    return;
  }

  assert(gm_);
  if (!gm_)
  {
    AERROR <<  "Client should have valid GoalManager";
    return;
  }

  DestructionGuard::ScopedProtector protector(*guard_);
  if (!protector.isProtected()) {
    AERROR << 
      "This action client associated with the goal handle has already been destructed. Ignoring this call";
    return;
  }

    std::lock_guard<std::recursive_mutex> lock(gm_->list_mutex_);

  switch (list_handle_.getElem()->getCommState().state_) {
    case CommState::WAITING_FOR_GOAL_ACK:
    case CommState::PENDING:
    case CommState::ACTIVE:
    case CommState::WAITING_FOR_CANCEL_ACK:
      break;  // Continue standard processing
    case CommState::WAITING_FOR_RESULT:
    case CommState::RECALLING:
    case CommState::PREEMPTING:
    case CommState::DONE:
      ADEBUG <<  "Got a cancel() request while in state "<<list_handle_.getElem()->getCommState().toString()<<", so ignoring it";
      return;
    default:
      AERROR <<  "BUG: Unhandled CommState: " <<
        list_handle_.getElem()->getCommState().state_;
      return;
  }

  ActionGoalConstPtr action_goal = list_handle_.getElem()->getActionGoal();

  auto cancel_msg = std::make_shared<GoalID>();
  cancel_msg->set_timestamp(cyber::Time(0, 0).ToNanosecond());
  cancel_msg->set_id(list_handle_.getElem()->getActionGoal()->goal_id().id());

  if (gm_->cancel_func_) {
    gm_->cancel_func_(cancel_msg);
  }

  list_handle_.getElem()->transitionToState(*this, CommState::WAITING_FOR_CANCEL_ACK);
}

template<class ActionSpec>
bool ClientGoalHandle<ActionSpec>::operator==(const ClientGoalHandle<ActionSpec> & rhs) const
{
  // Check if both are inactive
  if (!active_ && !rhs.active_) {
    return true;
  }

  // Check if one or the other is inactive
  if (!active_ || !rhs.active_) {
    return false;
  }

  DestructionGuard::ScopedProtector protector(*guard_);
  if (!protector.isProtected()) {
    AERROR << 
      "This action client associated with the goal handle has already been destructed. Ignoring this operator==() call";
    return false;
  }

  return list_handle_ == rhs.list_handle_;
}

template<class ActionSpec>
bool ClientGoalHandle<ActionSpec>::operator!=(const ClientGoalHandle<ActionSpec> & rhs) const
{
  return !(*this == rhs);
}





template<class ActionSpec>
CommStateMachine<ActionSpec>::CommStateMachine(const ActionGoalPtr & action_goal,
  TransitionCallback transition_cb,
  FeedbackCallback feedback_cb)
: state_(CommState::WAITING_FOR_GOAL_ACK)
{
  assert(action_goal);
  action_goal_ = action_goal;
  transition_cb_ = transition_cb;
  feedback_cb_ = feedback_cb;
  // transitionToState( CommState::WAITING_FOR_GOAL_ACK );
}

template<class ActionSpec>
typename CommStateMachine<ActionSpec>::ActionGoalPtr CommStateMachine<ActionSpec>::
getActionGoal() const
{
  return action_goal_;
}

template<class ActionSpec>
CommState CommStateMachine<ActionSpec>::getCommState() const
{
  return state_;
}

template<class ActionSpec>
GoalStatus CommStateMachine<ActionSpec>::getGoalStatus() const
{
  return latest_goal_status_;
}

template<class ActionSpec>
typename CommStateMachine<ActionSpec>::ResultConstPtr CommStateMachine<ActionSpec>::getResult()
const
{
  ResultConstPtr result;
  if (latest_result_) {
    EnclosureDeleter<const ActionResult> d(latest_result_);
    result = ResultConstPtr(&(latest_result_->result()), d);
  }
  return result;
}

template<class ActionSpec>
void CommStateMachine<ActionSpec>::setCommState(const CommState::StateEnum & state)
{
  setCommState(CommState(state));
}

template<class ActionSpec>
void CommStateMachine<ActionSpec>::setCommState(const CommState & state)
{
  ADEBUG <<  "Transitioning CommState from " << state_.toString() << " to " << state.toString();
  state_ = state;
}

template<class ActionSpec>
const GoalStatus * CommStateMachine<ActionSpec>::findGoalStatus(
  const GoalStatusArrayConstPtr & status_vec) const
{
  for ( int i = 0; i < status_vec->status_list_size(); i++) {
    if (status_vec->status_list(i).goal_id().id() == action_goal_->goal_id().id()) {
      return &status_vec->status_list(i);
    }
  }
  return NULL;
}

template<class ActionSpec>
void CommStateMachine<ActionSpec>::updateFeedback(GoalHandleT & gh,
  const ActionFeedbackConstPtr & action_feedback)
{
  // Check if this feedback is for us
  if (action_goal_->goal_id().id() != action_feedback->status().goal_id().id()) {
    return;
  }

  if (feedback_cb_) {
    EnclosureDeleter<const ActionFeedback> d(action_feedback);
    FeedbackConstPtr feedback(&(action_feedback->feedback()), d);
    feedback_cb_(gh, feedback);
  }
}

template<class ActionSpec>
void CommStateMachine<ActionSpec>::updateResult(GoalHandleT & gh,
  const ActionResultConstPtr & action_result)
{
  // Check if this feedback is for us
  if (action_goal_->goal_id().id() != action_result->status().goal_id().id()) {
    return;
  }
  latest_goal_status_ = action_result->status();
  latest_result_ = action_result;
  switch (state_.state_) {
    case CommState::WAITING_FOR_GOAL_ACK:
    case CommState::PENDING:
    case CommState::ACTIVE:
    case CommState::WAITING_FOR_RESULT:
    case CommState::WAITING_FOR_CANCEL_ACK:
    case CommState::RECALLING:
    case CommState::PREEMPTING:
      {
        // A little bit of hackery to call all the right state transitions before processing result
        GoalStatusArrayPtr status_array(new GoalStatusArray());
        GoalStatus * status = status_array->add_status_list();
        * status = action_result->status();

        updateStatus(gh, status_array);

        transitionToState(gh, CommState::DONE);
        break;
      }
    case CommState::DONE:
      AERROR << "Got a result when we were already in the DONE state"; break;
    default:
      AERROR << "In a funny comm state:" << state_.state_; break;
  }
}

template<class ActionSpec>
void CommStateMachine<ActionSpec>::updateStatus(GoalHandleT & gh,
  const GoalStatusArrayConstPtr & status_array)
{
  const GoalStatus * goal_status = findGoalStatus(status_array);

  // It's possible to receive old GoalStatus messages over the wire, even after receiving Result with a terminal state.
  //   Thus, we want to ignore all status that we get after we're done, because it is irrelevant. (See trac #2721)
  if (state_ == CommState::DONE) {
    return;
  }

  if (goal_status) {
    latest_goal_status_ = *goal_status;
  } else {
    if (state_ != CommState::WAITING_FOR_GOAL_ACK &&
      state_ != CommState::WAITING_FOR_RESULT &&
      state_ != CommState::DONE)
    {
      processLost(gh);
    }
    return;
  }

  switch (state_.state_) {
    case CommState::WAITING_FOR_GOAL_ACK:
      {
        if (goal_status) {
          switch (goal_status->status()) {
            case GoalStatusType::PENDING:
              transitionToState(gh, CommState::PENDING);
              break;
            case GoalStatusType::ACTIVE:
              transitionToState(gh, CommState::ACTIVE);
              break;
            case GoalStatusType::PREEMPTED:
              transitionToState(gh, CommState::ACTIVE);
              transitionToState(gh, CommState::PREEMPTING);
              transitionToState(gh, CommState::WAITING_FOR_RESULT);
              break;
            case GoalStatusType::SUCCEEDED:
              transitionToState(gh, CommState::ACTIVE);
              transitionToState(gh, CommState::WAITING_FOR_RESULT);
              break;
            case GoalStatusType::ABORTED:
              transitionToState(gh, CommState::ACTIVE);
              transitionToState(gh, CommState::WAITING_FOR_RESULT);
              break;
            case GoalStatusType::REJECTED:
              transitionToState(gh, CommState::PENDING);
              transitionToState(gh, CommState::WAITING_FOR_RESULT);
              break;
            case GoalStatusType::RECALLED:
              transitionToState(gh, CommState::PENDING);
              transitionToState(gh, CommState::WAITING_FOR_RESULT);
              break;
            case GoalStatusType::PREEMPTING:
              transitionToState(gh, CommState::ACTIVE);
              transitionToState(gh, CommState::PREEMPTING);
              break;
            case GoalStatusType::RECALLING:
              transitionToState(gh, CommState::PENDING);
              transitionToState(gh, CommState::RECALLING);
              break;
            default:
              AERROR << 
                "BUG: Got an unknown status from the ActionServer. status = " << 
                (int)goal_status->status();
              break;
          }
        }
        break;
      }
    case CommState::PENDING:
      {
        switch (goal_status->status()) {
          case GoalStatusType::PENDING:
            break;
          case GoalStatusType::ACTIVE:
            transitionToState(gh, CommState::ACTIVE);
            break;
          case GoalStatusType::PREEMPTED:
            transitionToState(gh, CommState::ACTIVE);
            transitionToState(gh, CommState::PREEMPTING);
            transitionToState(gh, CommState::WAITING_FOR_RESULT);
            break;
          case GoalStatusType::SUCCEEDED:
            transitionToState(gh, CommState::ACTIVE);
            transitionToState(gh, CommState::WAITING_FOR_RESULT);
            break;
          case GoalStatusType::ABORTED:
            transitionToState(gh, CommState::ACTIVE);
            transitionToState(gh, CommState::WAITING_FOR_RESULT);
            break;
          case GoalStatusType::REJECTED:
            transitionToState(gh, CommState::WAITING_FOR_RESULT);
            break;
          case GoalStatusType::RECALLED:
            transitionToState(gh, CommState::RECALLING);
            transitionToState(gh, CommState::WAITING_FOR_RESULT);
            break;
          case GoalStatusType::PREEMPTING:
            transitionToState(gh, CommState::ACTIVE);
            transitionToState(gh, CommState::PREEMPTING);
            break;
          case GoalStatusType::RECALLING:
            transitionToState(gh, CommState::RECALLING);
            break;
          default:
          AERROR << 
                "BUG: Got an unknown status from the ActionServer. status = " << 
                (int)goal_status->status();
            break;
        }
        break;
      }
    case CommState::ACTIVE:
      {
        switch (goal_status->status()) {
          case GoalStatusType::PENDING:
            AERROR << "Invalid transition from ACTIVE to PENDING"; break;
          case GoalStatusType::ACTIVE:
            break;
          case GoalStatusType::REJECTED:
            AERROR << "Invalid transition from ACTIVE to REJECTED"; break;
          case GoalStatusType::RECALLING:
            AERROR <<  "Invalid transition from ACTIVE to RECALLING"; break;
          case GoalStatusType::RECALLED:
            AERROR << "Invalid transition from ACTIVE to RECALLED"; break;
          case GoalStatusType::PREEMPTED:
            transitionToState(gh, CommState::PREEMPTING);
            transitionToState(gh, CommState::WAITING_FOR_RESULT);
            break;
          case GoalStatusType::SUCCEEDED:
          case GoalStatusType::ABORTED:
            transitionToState(gh, CommState::WAITING_FOR_RESULT); break;
          case GoalStatusType::PREEMPTING:
            transitionToState(gh, CommState::PREEMPTING); break;
          default:
             AERROR << 
                "BUG: Got an unknown status from the ActionServer. status = " << 
                (int)goal_status->status();
            break;
        }
        break;
      }
    case CommState::WAITING_FOR_RESULT:
      {
        switch (goal_status->status()) {
          case GoalStatusType::PENDING:
            AERROR <<  "Invalid Transition from WAITING_FOR_RESUT to PENDING";
            break;
          case GoalStatusType::PREEMPTING:
            AERROR <<  "Invalid Transition from WAITING_FOR_RESUT to PREEMPTING";
            break;
          case GoalStatusType::RECALLING:
            AERROR <<  "Invalid Transition from WAITING_FOR_RESUT to RECALLING";
            break;
          case GoalStatusType::ACTIVE:
          case GoalStatusType::PREEMPTED:
          case GoalStatusType::SUCCEEDED:
          case GoalStatusType::ABORTED:
          case GoalStatusType::REJECTED:
          case GoalStatusType::RECALLED:
            break;
          default:
            AERROR << 
                "BUG: Got an unknown status from the ActionServer. status = " << 
                (int)goal_status->status();
            break;
        }
        break;
      }
    case CommState::WAITING_FOR_CANCEL_ACK:
      {
        switch (goal_status->status()) {
          case GoalStatusType::PENDING:
            break;
          case GoalStatusType::ACTIVE:
            break;
          case GoalStatusType::SUCCEEDED:
          case GoalStatusType::ABORTED:
          case GoalStatusType::PREEMPTED:
            transitionToState(gh, CommState::PREEMPTING);
            transitionToState(gh, CommState::WAITING_FOR_RESULT);
            break;
          case GoalStatusType::RECALLED:
            transitionToState(gh, CommState::RECALLING);
            transitionToState(gh, CommState::WAITING_FOR_RESULT);
            break;
          case GoalStatusType::REJECTED:
            transitionToState(gh, CommState::WAITING_FOR_RESULT); break;
          case GoalStatusType::PREEMPTING:
            transitionToState(gh, CommState::PREEMPTING); break;
          case GoalStatusType::RECALLING:
            transitionToState(gh, CommState::RECALLING); break;
          default:
         AERROR << 
                "BUG: Got an unknown status from the ActionServer. status = " << 
                (int)goal_status->status();
            break;
        }
        break;
      }
    case CommState::RECALLING:
      {
        switch (goal_status->status()) {
          case GoalStatusType::PENDING:
            AERROR <<  "Invalid Transition from RECALLING to PENDING"; break;
          case GoalStatusType::ACTIVE:
            AERROR <<  "Invalid Transition from RECALLING to ACTIVE"; break;
          case GoalStatusType::SUCCEEDED:
          case GoalStatusType::ABORTED:
          case GoalStatusType::PREEMPTED:
            transitionToState(gh, CommState::PREEMPTING);
            transitionToState(gh, CommState::WAITING_FOR_RESULT);
            break;
          case GoalStatusType::RECALLED:
            transitionToState(gh, CommState::WAITING_FOR_RESULT);
            break;
          case GoalStatusType::REJECTED:
            transitionToState(gh, CommState::WAITING_FOR_RESULT); break;
          case GoalStatusType::PREEMPTING:
            transitionToState(gh, CommState::PREEMPTING); break;
          case GoalStatusType::RECALLING:
            break;
          default:
                AERROR << 
                "BUG: Got an unknown status from the ActionServer. status = " << 
                (int)goal_status->status();
            break;
        }
        break;
      }
    case CommState::PREEMPTING:
      {
        switch (goal_status->status()) {
          case GoalStatusType::PENDING:
            AERROR <<  "Invalid Transition from PREEMPTING to PENDING"; break;
          case GoalStatusType::ACTIVE:
            AERROR <<   "Invalid Transition from PREEMPTING to ACTIVE"; break;
          case GoalStatusType::REJECTED:
            AERROR <<   "Invalid Transition from PREEMPTING to REJECTED"; break;
          case GoalStatusType::RECALLING:
            AERROR <<   "Invalid Transition from PREEMPTING to RECALLING"; break;
          case GoalStatusType::RECALLED:
            AERROR <<  "Invalid Transition from PREEMPTING to RECALLED"; break;
            break;
          case GoalStatusType::PREEMPTED:
          case GoalStatusType::SUCCEEDED:
          case GoalStatusType::ABORTED:
            transitionToState(gh, CommState::WAITING_FOR_RESULT); break;
          case GoalStatusType::PREEMPTING:
            break;
          default:
             AERROR << 
                "BUG: Got an unknown status from the ActionServer. status = " << 
                (int)goal_status->status();
            break;
        }
        break;
      }
    case CommState::DONE:
      {
        switch (goal_status->status()) {
          case GoalStatusType::PENDING:
            AERROR <<  "Invalid Transition from DONE to PENDING"; break;
          case GoalStatusType::ACTIVE:
            AERROR <<   "Invalid Transition from DONE to ACTIVE"; break;
          case GoalStatusType::RECALLING:
            AERROR <<   "Invalid Transition from DONE to RECALLING"; break;
          case GoalStatusType::PREEMPTING:
            AERROR <<  "Invalid Transition from DONE to PREEMPTING"; break;
          case GoalStatusType::PREEMPTED:
          case GoalStatusType::SUCCEEDED:
          case GoalStatusType::ABORTED:
          case GoalStatusType::RECALLED:
          case GoalStatusType::REJECTED:
            break;
          default:
        AERROR << 
                "BUG: Got an unknown status from the ActionServer. status = " << 
                (int)goal_status->status();
            break;
        }
        break;
      }
    default:
      AERROR <<  "In a funny comm state: " << state_.state_;
      break;
  }
}


template<class ActionSpec>
void CommStateMachine<ActionSpec>::processLost(GoalHandleT & gh)
{
  AERROR << "Transitioning goal to LOST";
  latest_goal_status_.set_status(GoalStatusType::LOST);
  transitionToState(gh, CommState::DONE);
}

template<class ActionSpec>
void CommStateMachine<ActionSpec>::transitionToState(GoalHandleT & gh,
  const CommState::StateEnum & next_state)
{
  transitionToState(gh, CommState(next_state));
}

template<class ActionSpec>
void CommStateMachine<ActionSpec>::transitionToState(GoalHandleT & gh, const CommState & next_state)
{
  ADEBUG << "Trying to transition to " << next_state.toString();
  setCommState(next_state);
  if (transition_cb_) {
    transition_cb_(gh);
  }
}





template<class ActionSpec>
void GoalManager<ActionSpec>::registerSendGoalFunc(SendGoalFunc send_goal_func)
{
  send_goal_func_ = send_goal_func;
}

template<class ActionSpec>
void GoalManager<ActionSpec>::registerCancelFunc(CancelFunc cancel_func)
{
  cancel_func_ = cancel_func;
}


template<class ActionSpec>
ClientGoalHandle<ActionSpec> GoalManager<ActionSpec>::initGoal(const Goal & goal,
  TransitionCallback transition_cb,
  FeedbackCallback feedback_cb)
{
  ActionGoalPtr action_goal(new ActionGoal);
  action_goal->mutable_header()->set_timestamp(cyber::Time::Now().ToNanosecond());
  *action_goal->mutable_goal_id() = id_generator_.generateID();
  *action_goal->mutable_goal() = goal;

  typedef CommStateMachine<ActionSpec> CommStateMachineT;
  std::shared_ptr<CommStateMachineT> comm_state_machine(new CommStateMachineT(action_goal,
    transition_cb,
    feedback_cb));
  std::lock_guard<std::recursive_mutex> lock(list_mutex_);

  typename ManagedListT::Handle list_handle =
    list_.add(comm_state_machine, std::bind(&GoalManagerT::listElemDeleter, this, std::placeholders::_1), guard_);

  if (send_goal_func_) {
    send_goal_func_(action_goal);
  } else {
    AWARN <<
      "Possible coding error: send_goal_func_ set to NULL. Not going to send goal";
  }

  return GoalHandleT(this, list_handle, guard_);
}

template<class ActionSpec>
void GoalManager<ActionSpec>::listElemDeleter(typename ManagedListT::iterator it)
{
  assert(guard_);
  if (!guard_)
  {
    AERROR << "Goal manager deleter should not see invalid guards";
    return;
  }
  DestructionGuard::ScopedProtector protector(*guard_);
  if (!protector.isProtected()) {
    AERROR <<
      "This action client associated with the goal handle has already been destructed. Not going to try delete the CommStateMachine associated with this goal";
    return;
  }

  ADEBUG<< "About to erase CommStateMachine";
  std::lock_guard<std::recursive_mutex> lock(list_mutex_);
  list_.erase(it);
  ADEBUG<<"Done erasing CommStateMachine";
}

template<class ActionSpec>
void GoalManager<ActionSpec>::updateStatuses(
  const GoalStatusArrayConstPtr & status_array)
{
  std::lock_guard<std::recursive_mutex> lock(list_mutex_);
  typename ManagedListT::iterator it = list_.begin();

  while (it != list_.end()) {
    GoalHandleT gh(this, it.createHandle(), guard_);
    (*it)->updateStatus(gh, status_array);
    ++it;
  }
}

template<class ActionSpec>
void GoalManager<ActionSpec>::updateFeedbacks(const ActionFeedbackConstPtr & action_feedback)
{
  std::lock_guard<std::recursive_mutex> lock(list_mutex_);
  typename ManagedListT::iterator it = list_.begin();

  while (it != list_.end()) {
    GoalHandleT gh(this, it.createHandle(), guard_);
    (*it)->updateFeedback(gh, action_feedback);
    ++it;
  }
}

template<class ActionSpec>
void GoalManager<ActionSpec>::updateResults(const ActionResultConstPtr & action_result)
{
  std::lock_guard<std::recursive_mutex> lock(list_mutex_);
  typename ManagedListT::iterator it = list_.begin();

  while (it != list_.end()) {
    GoalHandleT gh(this, it.createHandle(), guard_);
    (*it)->updateResult(gh, action_result);
    ++it;
  }
}

}  // namespace actionlib
}

#endif  // ACTIONLIB__CLIENT__CLIENT_HELPERS_H_
