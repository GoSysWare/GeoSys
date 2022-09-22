
#ifndef ACTIONLIB__SERVER__SERVER_GOAL_HANDLE_H_
#define ACTIONLIB__SERVER__SERVER_GOAL_HANDLE_H_




#include <list>
#include <string>

#include "cyber/common/log.h"

#include "modules/common/proto/action.pb.h"
#include "modules/action/action_definition.h"
#include "modules/action/destruction_guard.h"
#include "modules/action/enclosure_deleter.h"

#include "status_tracker.h"




using apollo::common::proto::GoalID;
using apollo::common::proto::GoalStatus;
using apollo::common::proto::GoalStatusType;

namespace apollo {
namespace actionlib
{

// forward declaration of ActionServerBase
template<class ActionSpec>
class ActionServerBase;

/**
 * @class ServerGoalHandle
 * @brief Encapsulates a state machine for a given goal that the user can
 * trigger transitions on. All ROS interfaces for the goal are managed by
 * the ActionServer to lessen the burden on the user.
 */
template<class ActionSpec>
class ServerGoalHandle
{
private:
  // generates typedefs that we'll use to make our lives easier
  ACTION_DEFINITION(ActionSpec);

public:
  /**
   * @brief  Default constructor for a ServerGoalHandle
   */
  ServerGoalHandle();

  /**
   * @brief  Copy constructor for a ServerGoalHandle
   * @param gh The goal handle to copy
   */
  ServerGoalHandle(const ServerGoalHandle & gh);

  /** @brief  Accept the goal referenced by the goal handle. This will
   * transition to the ACTIVE state or the PREEMPTING state depending
   * on whether a cancel request has been received for the goal
   * @param text Optionally, any text message about the status change being made that should be passed to the client
   */
  void setAccepted(const std::string & text = std::string(""));

  /**
   * @brief  Set the status of the goal associated with the ServerGoalHandle to RECALLED or PREEMPTED
   * depending on what the current status of the goal is
   * @param  result Optionally, the user can pass in a result to be sent to any clients of the goal
   * @param text Optionally, any text message about the status change being made that should be passed to the client
   */
  void setCanceled(const Result & result = Result(), const std::string & text = std::string(""));

  /**
   * @brief  Set the status of the goal associated with the ServerGoalHandle to rejected
   * @param  result Optionally, the user can pass in a result to be sent to any clients of the goal
   * @param text Optionally, any text message about the status change being made that should be passed to the client
   */
  void setRejected(const Result & result = Result(), const std::string & text = std::string(""));

  /**
   * @brief  Set the status of the goal associated with the ServerGoalHandle to aborted
   * @param  result Optionally, the user can pass in a result to be sent to any clients of the goal
   * @param text Optionally, any text message about the status change being made that should be passed to the client
   */
  void setAborted(const Result & result = Result(), const std::string & text = std::string(""));

  /**
   * @brief  Set the status of the goal associated with the ServerGoalHandle to succeeded
   * @param  result Optionally, the user can pass in a result to be sent to any clients of the goal
   * @param text Optionally, any text message about the status change being made that should be passed to the client
   */
  void setSucceeded(const Result & result = Result(), const std::string & text = std::string(""));

  /**
   * @brief  Send feedback to any clients of the goal associated with this ServerGoalHandle
   * @param feedback The feedback to send to the client
   */
  void publishFeedback(const Feedback & feedback);

  /**
   * @brief Determine if the goal handle is valid (tracking a valid goal,
   * and associated with a valid action server). If the handle is valid, it
   * means that the accessors \ref getGoal, \ref getGoalID, etc, can be
   * called without generating errors.
   *
   * @return True if valid, False if invalid
   */
  bool isValid() const;

  /**
   * @brief  Accessor for the goal associated with the ServerGoalHandle
   * @return A shared_ptr to the goal object
   */
  std::shared_ptr<const Goal> getGoal() const;

  /**
   * @brief  Accessor for the goal id associated with the ServerGoalHandle
   * @return The goal id
   */
  GoalID getGoalID() const;

  /**
   * @brief  Accessor for the status associated with the ServerGoalHandle
   * @return The goal status
   */
  GoalStatus getGoalStatus() const;

  /**
   * @brief  Equals operator for a ServerGoalHandle
   * @param gh The goal handle to copy
   */
  ServerGoalHandle & operator=(const ServerGoalHandle & gh);

  /**
   * @brief  Equals operator for ServerGoalHandles
   * @param other The ServerGoalHandle to compare to
   * @return True if the ServerGoalHandles refer to the same goal, false otherwise
   */
  bool operator==(const ServerGoalHandle & other) const;

  /**
   * @brief  != operator for ServerGoalHandles
   * @param other The ServerGoalHandle to compare to
   * @return True if the ServerGoalHandles refer to different goals, false otherwise
   */
  bool operator!=(const ServerGoalHandle & other) const;

private:
  /**
   * @brief  A private constructor used by the ActionServer to initialize a ServerGoalHandle
   */
  ServerGoalHandle(typename std::list<StatusTracker<ActionSpec> >::iterator status_it,
    ActionServerBase<ActionSpec> * as, std::shared_ptr<void> handle_tracker,
    std::shared_ptr<DestructionGuard> guard);


  /**
   * @brief  A private method to set status to PENDING or RECALLING
   * @return True if the cancel request should be passed on to the user, false otherwise
   */
  bool setCancelRequested();

  typename std::list<StatusTracker<ActionSpec> >::iterator status_it_;
  std::shared_ptr< const ActionGoal> goal_;
  ActionServerBase<ActionSpec> * as_;
  std::shared_ptr<void> handle_tracker_;
  std::shared_ptr<DestructionGuard> guard_;
  friend class ActionServerBase<ActionSpec>;
};
template <class ActionSpec>
ServerGoalHandle<ActionSpec>::ServerGoalHandle() : as_(NULL) {}

template <class ActionSpec>
ServerGoalHandle<ActionSpec>::ServerGoalHandle(const ServerGoalHandle &gh)
    : status_it_(gh.status_it_), goal_(gh.goal_), as_(gh.as_),
      handle_tracker_(gh.handle_tracker_), guard_(gh.guard_) {}

template <class ActionSpec>
void ServerGoalHandle<ActionSpec>::setAccepted(const std::string &text) {
  if (as_ == NULL) {
    AERROR
        << "You are attempting to call methods on an uninitialized goal handle";
    return;
  }

  // check to see if we can use the action server
  DestructionGuard::ScopedProtector protector(*guard_);
  if (!protector.isProtected()) {
    AERROR << "The ActionServer associated with this GoalHandle is invalid. "
              "Did you delete the ActionServer before the GoalHandle?";
    return;
  }

  ADEBUG << "Accepting goal, id:  " << getGoalID().id()
         << "stamp: " << getGoalID().timestamp();
  if (goal_) {
    std::lock_guard<std::recursive_mutex> lock(as_->lock_);
    unsigned int status = (*status_it_).status_.status();

    // if we were pending before, then we'll go active
    if (status == GoalStatusType::PENDING) {
      (*status_it_).status_.set_status (GoalStatusType::ACTIVE) ;
      (*status_it_).status_.set_text(text);
      as_->publishStatus();
    } else if (status == GoalStatusType::RECALLING) {
      // if we were recalling before, now we'll go to preempting
      (*status_it_).status_.set_status (GoalStatusType::PREEMPTING);
      (*status_it_).status_.set_text(text);
      as_->publishStatus();
    } else {
      AERROR << "To transition to an active state, the goal must be in a "
                "pending or recalling state, it is currently in state: "
             << (int)(*status_it_).status_.status();
    }
  } else {
    AERROR << "Attempt to set status on an uninitialized ServerGoalHandle";
  }
}


template <class ActionSpec>
void ServerGoalHandle<ActionSpec>::setCanceled(const Result &result,
                                               const std::string &text) {
  if (as_ == NULL) {
    AERROR
        << "You are attempting to call methods on an uninitialized goal handle";
    return;
  }

  // check to see if we can use the action server
  DestructionGuard::ScopedProtector protector(*guard_);
  if (!protector.isProtected()) {
    AERROR << "The ActionServer associated with this GoalHandle is invalid. "
              "Did you delete the ActionServer before the GoalHandle?";
    return;
  }
  ADEBUG << "Setting status to canceled on goal, id: " << getGoalID().id()
         << "stamp: " << getGoalID().timestamp();
  if (goal_) {
    std::lock_guard<std::recursive_mutex> lock(as_->lock_);
    unsigned int status = (*status_it_).status_.status();
    if (status == GoalStatusType::PENDING ||
        status == GoalStatusType::RECALLING) {
      (*status_it_).status_.set_status (GoalStatusType::RECALLED);
      (*status_it_).status_.set_text( text);
      as_->publishResult((*status_it_).status_, result);
    } else if (status == GoalStatusType::ACTIVE ||
               status == GoalStatusType::PREEMPTING) {
      (*status_it_).status_.set_status(GoalStatusType::PREEMPTED);
      (*status_it_).status_.set_text(text);
      as_->publishResult((*status_it_).status_, result);
    } else {
      AERROR << "To transition to a cancelled state, the goal must be in a "
                "pending, recalling, active, or preempting state, it is "
                "currently in state: "
             << (int)(*status_it_).status_.status();
    }
  } else {
    AERROR << "Attempt to set status on an uninitialized ServerGoalHandle";
  }
}

template <class ActionSpec>
void ServerGoalHandle<ActionSpec>::setRejected(const Result &result,
                                               const std::string &text) {
  if (as_ == NULL) {
    AERROR
        << "You are attempting to call methods on an uninitialized goal handle";
    return;
  }

  // check to see if we can use the action server
  DestructionGuard::ScopedProtector protector(*guard_);
  if (!protector.isProtected()) {
    AERROR << "The ActionServer associated with this GoalHandle is invalid. "
              "Did you delete the ActionServer before the GoalHandle?";
    return;
  }

  ADEBUG << "Setting status to rejected on goal, id:  "
         << getGoalID().id.c_str() << "stamp: " << getGoalID().stamp.toSec();

  if (goal_) {
    std::lock_guard<std::recursive_mutex> lock(as_->lock_);
    unsigned int status = (*status_it_).status_.status;
    if (status == GoalStatusType::PENDING ||
        status == GoalStatusType::RECALLING) {
      (*status_it_).status_.status = GoalStatusType::REJECTED;
      (*status_it_).status_.text = text;
      as_->publishResult((*status_it_).status_, result);
    } else {
      AERROR << "To transition to a rejected state, the goal must be in a "
                "pending or recalling state, it is currently in state: "
             << (*status_it_).status_.status;
    }
  } else {
    AERROR << "Attempt to set status on an uninitialized ServerGoalHandle";
  }
}

template <class ActionSpec>
void ServerGoalHandle<ActionSpec>::setAborted(const Result &result,
                                              const std::string &text) {
  if (as_ == NULL) {
    AERROR
        << "You are attempting to call methods on an uninitialized goal handle";
    return;
  }

  // check to see if we can use the action server
  DestructionGuard::ScopedProtector protector(*guard_);
  if (!protector.isProtected()) {
    AERROR << "The ActionServer associated with this GoalHandle is invalid. "
              "Did you delete the ActionServer before the GoalHandle?";
    return;
  }

  ADEBUG << "Setting status to aborted on goal, id:  " << getGoalID().id()
         << "stamp: " << getGoalID().timestamp();
  if (goal_) {
    std::lock_guard<std::recursive_mutex> lock(as_->lock_);
    unsigned int status = (*status_it_).status_.status();
    if (status == GoalStatusType::PREEMPTING ||
        status == GoalStatusType::ACTIVE) {
      (*status_it_).status_.set_status(GoalStatusType::ABORTED);
      (*status_it_).status_.set_text(text);
      as_->publishResult((*status_it_).status_, result);
    } else {
      AERROR << "To transition to an aborted state, the goal must be in a "
                "preempting or active state, it is currently in state:"
             << status;
    }
  } else {
    AERROR << "Attempt to set status on an uninitialized ServerGoalHandle";
  }
}

template <class ActionSpec>
void ServerGoalHandle<ActionSpec>::setSucceeded(const Result &result,
                                                const std::string &text) {
  if (as_ == NULL) {
    AERROR
        << "You are attempting to call methods on an uninitialized goal handle";
    return;
  }

  // check to see if we can use the action server
  DestructionGuard::ScopedProtector protector(*guard_);
  if (!protector.isProtected()) {
    AERROR << "The ActionServer associated with this GoalHandle is invalid. "
              "Did you delete the ActionServer before the GoalHandle?";
    return;
  }

  ADEBUG << "Setting status to succeeded on goal, id:  "
         << getGoalID().id()<< "stamp: " << getGoalID().timestamp();
  if (goal_) {
    std::lock_guard<std::recursive_mutex> lock(as_->lock_);
    unsigned int status = (*status_it_).status_.status();
    if (status == GoalStatusType::PREEMPTING ||
        status == GoalStatusType::ACTIVE) {
      (*status_it_).status_.set_status(GoalStatusType::SUCCEEDED);
      (*status_it_).status_.set_text(text);
      as_->publishResult((*status_it_).status_, result);
    } else {
      AERROR << "To transition to an succeeded state, the goal must be in a "
                "preempting or active state, it is currently in state:"
             << status;
    }
  } else {
    AERROR << "Attempt to set status on an uninitialized ServerGoalHandle";
  }
}

template <class ActionSpec>
void ServerGoalHandle<ActionSpec>::publishFeedback(const Feedback &feedback) {
  if (as_ == NULL) {
    AERROR
        << "You are attempting to call methods on an uninitialized goal handle";
    return;
  }

  // check to see if we can use the action server
  DestructionGuard::ScopedProtector protector(*guard_);
  if (!protector.isProtected()) {
    AERROR << "The ActionServer associated with this GoalHandle is invalid. "
              "Did you delete the ActionServer before the GoalHandle?";
    return;
  }
  ADEBUG << "Publishing feedback for goal, id:  " << getGoalID().id()
         << " stamp: " << getGoalID().timestamp();
  if (goal_) {
    std::lock_guard<std::recursive_mutex> lock(as_->lock_);
    as_->publishFeedback((*status_it_).status_, feedback);
  } else {
    AERROR
        << "Attempt to publish feedback on an uninitialized ServerGoalHandle";
  }
}

template <class ActionSpec> bool ServerGoalHandle<ActionSpec>::isValid() const {
  return goal_ && as_ != NULL;
}

template <class ActionSpec>
std::shared_ptr<const typename ServerGoalHandle<ActionSpec>::Goal>
ServerGoalHandle<ActionSpec>::getGoal() const {
  // if we have a goal that is non-null
  if (goal_) {
    // create the deleter for our goal subtype
    EnclosureDeleter<const ActionGoal> d(goal_);


    return std::shared_ptr< const Goal >(&goal_->goal(), d);
  }
  return std::shared_ptr<const Goal>();
}

template <class ActionSpec>
GoalID ServerGoalHandle<ActionSpec>::getGoalID() const {
  if (goal_ && as_ != NULL) {
    DestructionGuard::ScopedProtector protector(*guard_);
    if (protector.isProtected()) {
      std::lock_guard<std::recursive_mutex> lock(as_->lock_);
      return (*status_it_).status_.goal_id();
    } else {
      return GoalID();
    }
  } else {
    AERROR << "Attempt to get a goal id on an uninitialized ServerGoalHandle "
              "or one that has no ActionServer associated with it.";
    return GoalID();
  }
}

template <class ActionSpec>
GoalStatus ServerGoalHandle<ActionSpec>::getGoalStatus() const {
  if (goal_ && as_ != NULL) {
    DestructionGuard::ScopedProtector protector(*guard_);
    if (protector.isProtected()) {
      std::lock_guard<std::recursive_mutex> lock(as_->lock_);
      return (*status_it_).status_;
    } else {
      return GoalStatus();
    }
  } else {
    AERROR << "Attempt to get goal status on an uninitialized ServerGoalHandle "
              "or one that has no ActionServer associated with it.";
    return GoalStatus();
  }
}

template <class ActionSpec>
ServerGoalHandle<ActionSpec> &
ServerGoalHandle<ActionSpec>::operator=(const ServerGoalHandle &gh) {
  status_it_ = gh.status_it_;
  goal_ = gh.goal_;
  as_ = gh.as_;
  handle_tracker_ = gh.handle_tracker_;
  guard_ = gh.guard_;
  return *this;
}

template <class ActionSpec>
bool ServerGoalHandle<ActionSpec>::operator==(
    const ServerGoalHandle &other) const {
  if (!goal_ && !other.goal_) {
    return true;
  }

  if (!goal_ || !other.goal_) {
    return false;
  }

  GoalID my_id = getGoalID();
  GoalID their_id = other.getGoalID();
  return my_id.id() == their_id.id();
}

template <class ActionSpec>
bool ServerGoalHandle<ActionSpec>::operator!=(
    const ServerGoalHandle &other) const {
  return !(*this == other);
}

template <class ActionSpec>
ServerGoalHandle<ActionSpec>::ServerGoalHandle(
    typename std::list<StatusTracker<ActionSpec>>::iterator status_it,
    ActionServerBase<ActionSpec> *as, std::shared_ptr<void> handle_tracker,
    std::shared_ptr<DestructionGuard> guard)
    : status_it_(status_it), goal_((*status_it).goal_), as_(as),
      handle_tracker_(handle_tracker), guard_(guard) {}



template <class ActionSpec>
bool ServerGoalHandle<ActionSpec>::setCancelRequested() {
  if (as_ == NULL) {
    AERROR
        << "You are attempting to call methods on an uninitialized goal handle";
    return false;
  }

  // check to see if we can use the action server
  DestructionGuard::ScopedProtector protector(*guard_);
  if (!protector.isProtected()) {
    AERROR << "The ActionServer associated with this GoalHandle is invalid. "
              "Did you delete the ActionServer before the GoalHandle?";
    return false;
  }
  ADEBUG << "Transitioning to a cancel requested state on goal id:  "
         << getGoalID().id() << "stamp: " << getGoalID().timestamp();

  if (goal_) {
    std::lock_guard<std::recursive_mutex> lock(as_->lock_);
    unsigned int status = (*status_it_).status_.status();
    if (status == GoalStatusType::PENDING) {
      (*status_it_).status_.set_status(GoalStatusType::RECALLING);
      as_->publishStatus();
      return true;
    }

    if (status == GoalStatusType::ACTIVE) {
      (*status_it_).status_.set_status(GoalStatusType::PREEMPTING);
      as_->publishStatus();
      return true;
    }
  }
  return false;
}
}
}


#endif  // ACTIONLIB__SERVER__SERVER_GOAL_HANDLE_H_
