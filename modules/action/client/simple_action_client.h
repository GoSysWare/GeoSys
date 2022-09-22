
#ifndef ACTIONLIB__CLIENT__SIMPLE_ACTION_CLIENT_H_
#define ACTIONLIB__CLIENT__SIMPLE_ACTION_CLIENT_H_

#include <string>

#include "action_client.h"
#include "simple_client_goal_state.h"
#include "simple_goal_state.h"
#include "terminal_state.h"

namespace apollo {
namespace actionlib {

/**
 * \brief A Simple client implementation of the ActionInterface which supports
 * only one goal at a time
 *
 * The SimpleActionClient wraps the existing ActionClient, and exposes a limited
 * set of easy-to-use hooks for the user. Note that the concept of GoalHandles
 * has been completely hidden from the user, and that they must query the
 * SimplyActionClient directly in order to monitor a goal.
 */
template <class ActionSpec> class SimpleActionClient {
private:
  ACTION_DEFINITION(ActionSpec);
  typedef ClientGoalHandle<ActionSpec> GoalHandleT;
  typedef SimpleActionClient<ActionSpec> SimpleActionClientT;

public:
  typedef std::function<void(const SimpleClientGoalState &state,
                             const ResultConstPtr &result)>
      SimpleDoneCallback;
  typedef std::function<void()> SimpleActiveCallback;
  typedef std::function<void(const FeedbackConstPtr &feedback)>
      SimpleFeedbackCallback;

  /**
   * \brief Constructor with namespacing options
   *
   * Constructs a SingleGoalActionClient and sets up the necessary ros topics
   * for the ActionInterface, and namespaces them according the a specified
   * NodeHandle \param n The node handle on top of which we want to namespace
   * our action \param name The action name. Defines the namespace in which the
   * action communicates \param spin_thread If true, spins up a thread to
   * service this action's subscriptions. If false, then the user has to call
   * ros::spin() themselves. Defaults to True
   */
  SimpleActionClient(std::shared_ptr<Node> n, const std::string &name)
      : cur_simple_state_(SimpleGoalState::PENDING) {
    initSimpleClient(n, name);
  }

  ~SimpleActionClient();

  /**
   * \brief Waits for the ActionServer to connect to this client
   *
   * Often, it can take a second for the action server & client to negotiate
   * a connection, thus, risking the first few goals to be dropped. This call
   * lets the user wait until the network connection to the server is
   * negotiated. NOTE: Using this call in a single threaded ROS application, or
   * any application where the action client's callback queue is not being
   * serviced, will not work. Without a separate thread servicing the queue, or
   * a multi-threaded spinner, there is no way for the client to tell whether
   * or not the server is up because it can't receive a status message.
   * \param timeout Max time to block before returning. A zero timeout is
   * interpreted as an infinite timeout. \return True if the server connected in
   * the allocated time. False on timeout
   */
  bool
  waitForServer(const cyber::Duration &timeout = cyber::Duration(0, 0)) const {
    return ac_->waitForActionServerToStart(timeout);
  }

  /**
   * @brief  Checks if the action client is successfully connected to the action
   * server
   * @return True if the server is connected, false otherwise
   */
  bool isServerConnected() const { return ac_->isServerConnected(); }

  /**
   * \brief Sends a goal to the ActionServer, and also registers callbacks
   *
   * If a previous goal is already active when this is called. We simply forget
   * about that goal and start tracking the new goal. No cancel requests are
   * made. \param done_cb     Callback that gets called on transitions to Done
   * \param active_cb   Callback that gets called on transitions to Active
   * \param feedback_cb Callback that gets called whenever feedback for this
   * goal is received
   */
  void sendGoal(const Goal &goal,
                SimpleDoneCallback done_cb = SimpleDoneCallback(),
                SimpleActiveCallback active_cb = SimpleActiveCallback(),
                SimpleFeedbackCallback feedback_cb = SimpleFeedbackCallback());

  /**
   * \brief Sends a goal to the ActionServer, and waits until the goal completes
   * or a timeout is exceeded
   *
   * If the goal doesn't complete by the execute_timeout, then a preempt message
   * is sent. This call then waits up to the preempt_timeout for the goal to
   * then finish.
   *
   * \param goal             The goal to be sent to the ActionServer
   * \param execute_timeout  Time to wait until a preempt is sent. 0 implies
   * wait forever \param preempt_timeout  Time to wait after a preempt is sent.
   * 0 implies wait forever \return The state of the goal when this call is
   * completed
   */
  SimpleClientGoalState sendGoalAndWait(
      const Goal &goal,
      const cyber::Duration &execute_timeout = cyber::Duration(0, 0),
      const cyber::Duration &preempt_timeout = cyber::Duration(0, 0));

  /**
   * \brief Blocks until this goal finishes
   * \param timeout Max time to block before returning. A zero timeout is
   * interpreted as an infinite timeout. \return True if the goal finished.
   * False if the goal didn't finish within the allocated timeout
   */
  bool waitForResult(const cyber::Duration &timeout = cyber::Duration(0, 0));

  /**
   * \brief Get the Result of the current goal
   * \return shared pointer to the result. Note that this pointer will NEVER be
   * NULL
   */
  ResultConstPtr getResult() const;

  /**
   * \brief Get the state information for this goal
   *
   * Possible States Are: PENDING, ACTIVE, RECALLED, REJECTED, PREEMPTED,
   * ABORTED, SUCCEEDED, LOST. \return The goal's state. Returns LOST if this
   * SimpleActionClient isn't tracking a goal.
   */
  SimpleClientGoalState getState() const;

  /**
   * \brief Cancel all goals currently running on the action server
   *
   * This preempts all goals running on the action server at the point that
   * this message is serviced by the ActionServer.
   */
  void cancelAllGoals();

  /**
   * \brief Cancel all goals that were stamped at and before the specified time
   * \param time All goals stamped at or before `time` will be canceled
   */
  void cancelGoalsAtAndBeforeTime(const cyber::Time &time);

  /**
   * \brief Cancel the goal that we are currently pursuing
   */
  void cancelGoal();

  /**
   * \brief Stops tracking the state of the current goal. Unregisters this
   * goal's callbacks
   *
   * This is useful if we want to make sure we stop calling our callbacks before
   * sending a new goal. Note that this does not cancel the goal, it simply
   * stops looking for status info about this goal.
   */
  void stopTrackingGoal();

private:
  typedef ActionClient<ActionSpec> ActionClientT;
  GoalHandleT gh_;

  SimpleGoalState cur_simple_state_;

  // Signalling Stuff
  std::condition_variable done_condition_;
  std::mutex done_mutex_;

  // User Callbacks
  SimpleDoneCallback done_cb_;
  SimpleActiveCallback active_cb_;
  SimpleFeedbackCallback feedback_cb_;

  // Spin Thread Stuff
  std::mutex terminate_mutex_;
  bool need_to_terminate_;

  std::shared_ptr<ActionClientT>
      ac_; // Action client depends on callback_queue, so it must be destroyed
           // before callback_queue

  // ***** Private Funcs *****
  void initSimpleClient(std::shared_ptr<Node> n, const std::string &name);
  void handleTransition(GoalHandleT gh);
  void handleFeedback(GoalHandleT gh, const FeedbackConstPtr &feedback);
  void setSimpleState(const SimpleGoalState::StateEnum &next_state);
  void setSimpleState(const SimpleGoalState &next_state);
};

template <class ActionSpec>
void SimpleActionClient<ActionSpec>::initSimpleClient(std::shared_ptr<Node> n,
                                                      const std::string &name) {

  ac_.reset(new ActionClientT(n, name));
}

template <class ActionSpec>
SimpleActionClient<ActionSpec>::~SimpleActionClient() {

  gh_.reset();
  ac_.reset();
}

template <class ActionSpec>
void SimpleActionClient<ActionSpec>::setSimpleState(
    const SimpleGoalState::StateEnum &next_state) {
  setSimpleState(SimpleGoalState(next_state));
}

template <class ActionSpec>
void SimpleActionClient<ActionSpec>::setSimpleState(
    const SimpleGoalState &next_state) {
  ADEBUG << "Transitioning SimpleState from " << cur_simple_state_.toString()
         << " to " << next_state.toString();

  cur_simple_state_ = next_state;
}

template <class ActionSpec>
void SimpleActionClient<ActionSpec>::sendGoal(
    const Goal &goal, SimpleDoneCallback done_cb,
    SimpleActiveCallback active_cb, SimpleFeedbackCallback feedback_cb) {
  // Reset the old GoalHandle, so that our callbacks won't get called anymore
  gh_.reset();

  // Store all the callbacks
  done_cb_ = done_cb;
  active_cb_ = active_cb;
  feedback_cb_ = feedback_cb;

  cur_simple_state_ = SimpleGoalState::PENDING;

  // Send the goal to the ActionServer
  gh_ = ac_->sendGoal(goal,
                      std::bind(&SimpleActionClientT::handleTransition, this,
                                std::placeholders::_1),
                      std::bind(&SimpleActionClientT::handleFeedback, this,
                                std::placeholders::_1, std::placeholders::_2));
}

template <class ActionSpec>
SimpleClientGoalState SimpleActionClient<ActionSpec>::getState() const {
  if (gh_.isExpired()) {
    return SimpleClientGoalState(SimpleClientGoalState::LOST);
  }

  CommState comm_state_ = gh_.getCommState();

  switch (comm_state_.state_) {
  case CommState::WAITING_FOR_GOAL_ACK:
  case CommState::PENDING:
  case CommState::RECALLING:
    return SimpleClientGoalState(SimpleClientGoalState::PENDING);
  case CommState::ACTIVE:
  case CommState::PREEMPTING:
    return SimpleClientGoalState(SimpleClientGoalState::ACTIVE);
  case CommState::DONE: {
    switch (gh_.getTerminalState().state_) {
    case TerminalState::RECALLED:
      return SimpleClientGoalState(SimpleClientGoalState::RECALLED,
                                   gh_.getTerminalState().text_);
    case TerminalState::REJECTED:
      return SimpleClientGoalState(SimpleClientGoalState::REJECTED,
                                   gh_.getTerminalState().text_);
    case TerminalState::PREEMPTED:
      return SimpleClientGoalState(SimpleClientGoalState::PREEMPTED,
                                   gh_.getTerminalState().text_);
    case TerminalState::ABORTED:
      return SimpleClientGoalState(SimpleClientGoalState::ABORTED,
                                   gh_.getTerminalState().text_);
    case TerminalState::SUCCEEDED:
      return SimpleClientGoalState(SimpleClientGoalState::SUCCEEDED,
                                   gh_.getTerminalState().text_);
    case TerminalState::LOST:
      return SimpleClientGoalState(SimpleClientGoalState::LOST,
                                   gh_.getTerminalState().text_);
    default:
      AERROR << "Unknown terminal state " << gh_.getTerminalState().state_
             << ". This is a bug in SimpleActionClient";
      return SimpleClientGoalState(SimpleClientGoalState::LOST,
                                   gh_.getTerminalState().text_);
    }
  }
  case CommState::WAITING_FOR_RESULT:
  case CommState::WAITING_FOR_CANCEL_ACK: {
    switch (cur_simple_state_.state_) {
    case SimpleGoalState::PENDING:
      return SimpleClientGoalState(SimpleClientGoalState::PENDING);
    case SimpleGoalState::ACTIVE:
      return SimpleClientGoalState(SimpleClientGoalState::ACTIVE);
    case SimpleGoalState::DONE:
      AERROR << "In WAITING_FOR_RESULT or WAITING_FOR_CANCEL_ACK, yet we are "
                "in SimpleGoalState DONE. This is a bug in SimpleActionClient";
      return SimpleClientGoalState(SimpleClientGoalState::LOST);
    default:
      AERROR << "Got a SimpleGoalState of " << cur_simple_state_.state_
             << ". This is a bug in SimpleActionClient";
    }
  }
  default:
    break;
  }
  AERROR << "Error trying to interpret CommState - " << comm_state_.state_;
  return SimpleClientGoalState(SimpleClientGoalState::LOST);
}

template <class ActionSpec>
typename SimpleActionClient<ActionSpec>::ResultConstPtr
SimpleActionClient<ActionSpec>::getResult() const {
  if (gh_.isExpired()) {
    AERROR << "Trying to getResult() when no goal is running. You are "
              "incorrectly using SimpleActionClient";
  }

  if (gh_.getResult()) {
    return gh_.getResult();
  }

  return ResultConstPtr(new Result);
}

template <class ActionSpec>
void SimpleActionClient<ActionSpec>::cancelAllGoals() {
  ac_->cancelAllGoals();
}

template <class ActionSpec>
void SimpleActionClient<ActionSpec>::cancelGoalsAtAndBeforeTime(
    const cyber::Time &time) {
  ac_->cancelGoalsAtAndBeforeTime(time);
}

template <class ActionSpec> void SimpleActionClient<ActionSpec>::cancelGoal() {
  if (gh_.isExpired()) {
    AERROR << "Trying to cancelGoal() when no goal is running. You are "
              "incorrectly using SimpleActionClient";
  }

  gh_.cancel();
}

template <class ActionSpec>
void SimpleActionClient<ActionSpec>::stopTrackingGoal() {
  if (gh_.isExpired()) {
    AERROR << "Trying to stopTrackingGoal() when no goal is running. You are "
              "incorrectly using SimpleActionClient";
  }
  gh_.reset();
}

template <class ActionSpec>
void SimpleActionClient<ActionSpec>::handleFeedback(
    GoalHandleT gh, const FeedbackConstPtr &feedback) {
  if (gh_ != gh) {
    AERROR << "Got a callback on a goalHandle that we're not tracking.  \
               This is an internal SimpleActionClient/ActionClient bug.  \
               This could also be a GoalID collision";
  }
  if (feedback_cb_) {
    feedback_cb_(feedback);
  }
}

template <class ActionSpec>
void SimpleActionClient<ActionSpec>::handleTransition(GoalHandleT gh) {
  CommState comm_state_ = gh.getCommState();
  switch (comm_state_.state_) {
  case CommState::WAITING_FOR_GOAL_ACK:
    AERROR << "BUG: Shouldn't ever get a transition callback for "
              "WAITING_FOR_GOAL_ACK";
    break;
  case CommState::PENDING:
    AERROR << "BUG: Got a transition to CommState " << comm_state_.toString()
           << " when our in SimpleGoalState " << cur_simple_state_.toString();
    break;
  case CommState::ACTIVE:
    switch (cur_simple_state_.state_) {
    case SimpleGoalState::PENDING:
      setSimpleState(SimpleGoalState::ACTIVE);
      if (active_cb_) {
        active_cb_();
      }
      break;
    case SimpleGoalState::ACTIVE:
      break;
    case SimpleGoalState::DONE:
      AERROR << "BUG: Got a transition to CommState " << comm_state_.toString()
             << " when in SimpleGoalState " << cur_simple_state_.toString();
      break;
    default:
      AFATAL << "Unknown SimpleGoalState " << cur_simple_state_.state_;
      break;
    }
    break;
  case CommState::WAITING_FOR_RESULT:
    break;
  case CommState::WAITING_FOR_CANCEL_ACK:
    break;
  case CommState::RECALLING:
    AERROR << "BUG: Got a transition to CommState " << comm_state_.toString()
           << " when our in SimpleGoalState " << cur_simple_state_.toString();
    break;
  case CommState::PREEMPTING:
    switch (cur_simple_state_.state_) {
    case SimpleGoalState::PENDING:
      setSimpleState(SimpleGoalState::ACTIVE);
      if (active_cb_) {
        active_cb_();
      }
      break;
    case SimpleGoalState::ACTIVE:
      break;
    case SimpleGoalState::DONE:
      AERROR << "BUG: Got a transition to CommState " << comm_state_.toString()
             << " when in SimpleGoalState " << cur_simple_state_.toString();
      break;
    default:
      AFATAL << "Unknown SimpleGoalState " << cur_simple_state_.state_;
      break;
    }
    break;
  case CommState::DONE:
    switch (cur_simple_state_.state_) {
    case SimpleGoalState::PENDING:
    case SimpleGoalState::ACTIVE:
      if (done_cb_) {
        done_cb_(getState(), gh.getResult());
      }

      {
        std::lock_guard<std::mutex> lock(done_mutex_);
        setSimpleState(SimpleGoalState::DONE);
      }

      done_condition_.notify_all();
      break;
    case SimpleGoalState::DONE:
      AERROR << "BUG: Got a second transition to DONE";
      break;
    default:
      AFATAL << "Unknown SimpleGoalState " << cur_simple_state_.state_;
      break;
    }
    break;
  default:
    AERROR << "Unknown CommState received " << comm_state_.state_;
    break;
  }
}

template <class ActionSpec>
bool SimpleActionClient<ActionSpec>::waitForResult(
    const cyber::Duration &timeout) {
  if (gh_.isExpired()) {
    AERROR << "Trying to waitForGoalToFinish() when no goal is running. You "
              "are incorrectly using SimpleActionClient";
    return false;
  }

  if (timeout < cyber::Duration(0, 0)) {
    AWARN << "Timeouts can't be negative. Timeout is " << timeout.ToSecond();
  }

  cyber::Time timeout_time = cyber::Time::Now() + timeout;

  std::unique_lock<std::mutex> lock(done_mutex_);

  // Hardcode how often we check for node.ok()
  cyber::Duration loop_period = cyber::Duration(.1);

  while (cyber::OK()) {
    // Determine how long we should wait
    cyber::Duration time_left = timeout_time - cyber::Time::Now();

    // Check if we're past the timeout time
    if (timeout > cyber::Duration(0, 0) && time_left <= cyber::Duration(0, 0)) {
      break;
    }

    if (cur_simple_state_ == SimpleGoalState::DONE) {
      break;
    }

    // Truncate the time left
    if (time_left > loop_period || timeout == cyber::Duration()) {
      time_left = loop_period;
    }

    done_condition_.wait_for(
        lock, std::chrono::milliseconds(
                  static_cast<int64_t>(time_left.ToSecond() * 1000.0f)));
  }

  return cur_simple_state_ == SimpleGoalState::DONE;
}

template <class ActionSpec>
SimpleClientGoalState SimpleActionClient<ActionSpec>::sendGoalAndWait(
    const Goal &goal, const cyber::Duration &execute_timeout,
    const cyber::Duration &preempt_timeout) {
  sendGoal(goal);

  // See if the goal finishes in time
  if (waitForResult(execute_timeout)) {
    ADEBUG << "Goal finished within specified execute_timeout "
           << execute_timeout.ToSecond();
    return getState();
  }
  ADEBUG << "Goal didn't finish within specified execute_timeout  "
         << execute_timeout.ToSecond();

  // It didn't finish in time, so we need to preempt it
  cancelGoal();

  // Now wait again and see if it finishes
  if (waitForResult(preempt_timeout)) {
    ADEBUG << "Preempt finished within specified preempt_timeout   "
           << preempt_timeout.ToSecond();

  } else {
    ADEBUG << "Preempt didn't finish specified preempt_timeout  "
           << preempt_timeout.ToSecond();
  }
  return getState();
}

} // namespace actionlib
} // namespace apollo
#endif