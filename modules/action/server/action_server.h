#ifndef ACTIONLIB__SERVER__ACTION_SERVER_H_
#define ACTIONLIB__SERVER__ACTION_SERVER_H_


#include <list>
#include <string>

#include "modules/common/proto/action.pb.h"
#include "cyber/node/node.h"
#include "cyber/node/writer.h"
#include "cyber/node/reader.h"
#include "cyber/timer/timer.h"

#include "action_server_base.h"


using apollo::cyber::Node;
using apollo::cyber::Writer;
using apollo::cyber::Reader;

using apollo::common::proto::GoalID;
using apollo::common::proto::GoalStatus;
using apollo::common::proto::GoalStatusType;
using apollo::common::proto::GoalStatusArray;

namespace apollo {
namespace actionlib
{
/**
 * @class ActionServer
 * @brief The ActionServer is a helpful tool for managing goal requests to a
 * node. It allows the user to specify callbacks that are invoked when goal
 * or cancel requests come over the wire, and passes back GoalHandles that
 * can be used to track the state of a given goal request. The ActionServer
 * makes no assumptions about the policy used to service these goals, and
 * sends status for each goal over the wire until the last GoalHandle
 * associated with a goal request is destroyed.
 */
template<class ActionSpec>
class ActionServer : public ActionServerBase<ActionSpec>
{
public:
  // for convenience when referring to ServerGoalHandles
  typedef ServerGoalHandle<ActionSpec> GoalHandle;


  // generates typedefs that we'll use to make our lives easier
  ACTION_DEFINITION(ActionSpec);

  /**
   * @brief  Constructor for an ActionServer
   * @param  n A NodeHandle to create a namespace under
   * @param  name The name of the action
   * @param  goal_cb A goal callback to be called when the ActionServer receives a new goal over the wire
   * @param  cancel_cb A cancel callback to be called when the ActionServer receives a new cancel request over the wire
   * @param  auto_start A boolean value that tells the ActionServer whether or not to start publishing as soon as it comes up. THIS SHOULD ALWAYS BE SET TO FALSE TO AVOID RACE CONDITIONS and start() should be called after construction of the server.
   */
  ActionServer(std::shared_ptr<Node>n, std::string name,
    std::function<void(GoalHandle)> goal_cb,
    std::function<void(GoalHandle)> cancel_cb,
    bool auto_start);

  /**
   * @brief  Constructor for an ActionServer
   * @param  n A NodeHandle to create a namespace under
   * @param  name The name of the action
   * @param  goal_cb A goal callback to be called when the ActionServer receives a new goal over the wire
   * @param  auto_start A boolean value that tells the ActionServer whether or not to start publishing as soon as it comes up. THIS SHOULD ALWAYS BE SET TO FALSE TO AVOID RACE CONDITIONS and start() should be called after construction of the server.
   */
  ActionServer(std::shared_ptr<Node>n, std::string name,
    std::function<void(GoalHandle)> goal_cb,
    bool auto_start);



  /**
   * @brief  Constructor for an ActionServer
   * @param  n A NodeHandle to create a namespace under
   * @param  name The name of the action
   * @param  auto_start A boolean value that tells the ActionServer whether or not to start publishing as soon as it comes up. THIS SHOULD ALWAYS BE SET TO FALSE TO AVOID RACE CONDITIONS and start() should be called after construction of the server.
   */
  ActionServer(std::shared_ptr<Node>n, std::string name,
    bool auto_start);



  /**
   * @brief  Destructor for the ActionServer
   */
  virtual ~ActionServer();

private:
  /**
   * @brief  Initialize all ROS connections and setup timers
   */
  virtual void initialize();

  /**
   * @brief  Publishes a result for a given goal
   * @param status The status of the goal with which the result is associated
   * @param result The result to publish
   */
  virtual void publishResult(const GoalStatus & status, const Result & result);

  /**
   * @brief  Publishes feedback for a given goal
   * @param status The status of the goal with which the feedback is associated
   * @param feedback The feedback to publish
   */
  virtual void publishFeedback(const GoalStatus & status,
    const Feedback & feedback);

  /**
   * @brief  Explicitly publish status
   */
  virtual void publishStatus();

  /**
   * @brief  Publish status for all goals on a timer event
   */
  void publishStatusTimerCB();

  std::shared_ptr<Node> node_;
  std::string topic_prefix_;

  std::shared_ptr<Reader<ActionGoal>> goal_sub_;
  std::shared_ptr<Reader<GoalID>>  cancel_sub_;

  std::shared_ptr<Writer<GoalStatusArray>>   status_pub_;
  std::shared_ptr<Writer<ActionResult>> result_pub_;
  std::shared_ptr<Writer<ActionFeedback>> feedback_pub_;

  std::shared_ptr<cyber::Timer> status_timer_;
};


template<class ActionSpec>
ActionServer<ActionSpec>::ActionServer(
  std::shared_ptr<Node> n,
  std::string name,
  bool auto_start)
: ActionServerBase<ActionSpec>(
    std::function<void(GoalHandle)>(), std::function<void(GoalHandle)>(), auto_start),
  node_(n),
  topic_prefix_(name)
{
  // if we're to autostart... then we'll initialize things
  if (this->started_) {
    AWARN << 
    "You've passed in true for auto_start for the C++ action server at " << node_->Name()<<". You should always pass in false to avoid race conditions.";

  }
}



template<class ActionSpec>
ActionServer<ActionSpec>::ActionServer(std::shared_ptr<Node>n,  std::string name,
  std::function<void(GoalHandle)> goal_cb,
  std::function<void(GoalHandle)> cancel_cb,
  bool auto_start)
: ActionServerBase<ActionSpec>(goal_cb, cancel_cb, auto_start),
  node_(n),
  topic_prefix_(name)
{
  // if we're to autostart... then we'll initialize things
  if (this->started_) {
    AWARN << 
    "You've passed in true for auto_start for the C++ action server at " << node_->Name()<<". You should always pass in false to avoid race conditions.";

    ActionServer<ActionSpec>::initialize();
    publishStatus();
  }
}



template<class ActionSpec>
ActionServer<ActionSpec>::ActionServer(std::shared_ptr<Node>n, std::string name,
  std::function<void(GoalHandle)> goal_cb,
  bool auto_start)
: ActionServerBase<ActionSpec>(goal_cb, std::function<void(GoalHandle)>(), auto_start),
  node_(n),
  topic_prefix_(name)

{
  // if we're to autostart... then we'll initialize things
  if (this->started_) {
    AWARN << 
    "You've passed in true for auto_start for the C++ action server at " << node_->Name()<<". You should always pass in false to avoid race conditions.";

    ActionServer<ActionSpec>::initialize();
    publishStatus();
  }
}

template<class ActionSpec>
ActionServer<ActionSpec>::~ActionServer()
{

}

template<class ActionSpec>
void ActionServer<ActionSpec>::initialize()
{
  // read the queue size for each of the publish & subscribe components of the action
  // server
//   int pub_queue_size = 50;
//   int sub_queue_size = 50;


  result_pub_ = node_->CreateWriter<ActionResult>(topic_prefix_+"/result");
  feedback_pub_ =
    node_->CreateWriter<ActionFeedback>(topic_prefix_+ "/feedback");
  status_pub_ =
    node_->CreateWriter<GoalStatusArray>(topic_prefix_ + "/status");

  // read the frequency with which to publish status from the parameter server
  // if not specified locally explicitly, use search param to find actionlib_status_frequency
  double status_frequency = 5.0;
  double  status_list_timeout = 5.0;


  this->status_list_timeout_ = cyber::Duration(status_list_timeout);

  if (status_frequency > 0) {
    status_timer_ = std::make_shared<cyber::Timer>(1000 / status_frequency,
        std::bind(&ActionServer::publishStatusTimerCB,this),false);
    status_timer_->Start();     

  }

  goal_sub_ = node_->CreateReader<ActionGoal>(topic_prefix_ + "/goal",
      std::bind(&ActionServerBase<ActionSpec>::goalCallback, this, std::placeholders::_1));

  cancel_sub_ =
    node_->CreateReader<GoalID>(topic_prefix_ + "/cancel", 
      std::bind(&ActionServerBase<ActionSpec>::cancelCallback, this, std::placeholders::_1));
}

template<class ActionSpec>
void ActionServer<ActionSpec>::publishResult(const GoalStatus & status,
  const Result & result)
{
  std::lock_guard<std::recursive_mutex> lock(this->lock_);


  std::shared_ptr<ActionResult> ar(new ActionResult);
   ar->mutable_header()->set_timestamp( cyber::Time::Now().ToNanosecond());
  *ar->mutable_status() = status;
  *ar->mutable_result() = result;
  ADEBUG << "Publishing result for goal with id:  " << status.goal_id().id()
         << " and stamp: " << status.goal_id().timestamp();

  result_pub_->Write(ar);
  publishStatus();
}

template<class ActionSpec>
void ActionServer<ActionSpec>::publishFeedback(const GoalStatus & status,
  const Feedback & feedback)
{
  std::lock_guard<std::recursive_mutex> lock(this->lock_);
  // we'll create a shared_ptr to pass to ROS to limit copying
  std::shared_ptr<ActionFeedback> af(new ActionFeedback);
   af->mutable_header()->set_timestamp( cyber::Time::Now().ToNanosecond());
  *af->mutable_status() = status;
  *af->mutable_feedback() = feedback;
  ADEBUG << "Publishing result for goal with id:  " << status.goal_id().id()
         << " and stamp: " << status.goal_id().timestamp();
  feedback_pub_->Write(af);
}

template<class ActionSpec>
void ActionServer<ActionSpec>::publishStatusTimerCB()
{
  std::lock_guard<std::recursive_mutex> lock(this->lock_);
  // we won't publish status unless we've been started
  if (!this->started_) {
    return;
  }

  publishStatus();
}

template<class ActionSpec>
void ActionServer<ActionSpec>::publishStatus()
{
  std::lock_guard<std::recursive_mutex> lock(this->lock_);
  // build a status array
  GoalStatusArray status_array;

  status_array.mutable_header()->set_timestamp(cyber::Time::Now().ToNanosecond());

  // status_array.mutable_status_list()->Reserve(this->status_list_.size());

  unsigned int i = 0;
  for (typename std::list<StatusTracker<ActionSpec> >::iterator it = this->status_list_.begin();
    it != this->status_list_.end(); )

  {
    GoalStatus *status = status_array.add_status_list();

    *status = (*it).status_;

    // check if the item is due for deletion from the status list
    if ((*it).handle_destruction_time_ != cyber::Time() &&
      (*it).handle_destruction_time_ + this->status_list_timeout_ < cyber::Time::Now())
    {
      it = this->status_list_.erase(it);
    } else {
      ++it;
    }
    ++i;
  }

  status_pub_->Write(status_array);
}

}  // namespace actionlib
}


#endif  // ACTIONLIB__SERVER__ACTION_SERVER_H_
