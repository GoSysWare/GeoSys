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

#ifndef ACTIONLIB__CLIENT__ACTION_CLIENT_H_
#define ACTIONLIB__CLIENT__ACTION_CLIENT_H_

#include "client_helpers.h"
#include "connection_monitor.h"
#include "modules/action/destruction_guard.h"
#include "cyber/message/raw_message.h"
#include "cyber/proto/topology_change.pb.h"

#include <string>

using apollo::cyber::Node;
using apollo::cyber::ReaderBase;
using apollo::cyber::base::Connection;
using apollo::cyber::message::RawMessage;

using apollo::cyber::proto::ChangeMsg;
using apollo::cyber::proto::RoleAttributes;
using apollo::cyber::proto::RoleType;

using apollo::cyber::service_discovery::ChannelManager;

using apollo::cyber::service_discovery::TopologyManager;

using namespace apollo::cyber::service_discovery;
using namespace apollo::cyber::proto;

namespace apollo {
namespace actionlib {

/**
 * \brief Full interface to an ActionServer
 *
 * ActionClient provides a complete client side implementation of the
 * ActionInterface protocol. It provides callbacks for every client side
 * transition, giving the user full observation into the client side state
 * machine.
 */
template <class ActionSpec> class ActionClient {
public:
  typedef ClientGoalHandle<ActionSpec> GoalHandle;

private:
  ACTION_DEFINITION(ActionSpec);
  typedef ActionClient<ActionSpec> ActionClientT;
  typedef std::function<void(GoalHandle)> TransitionCallback;
  typedef std::function<void(GoalHandle, const FeedbackConstPtr &)>
      FeedbackCallback;
  typedef std::function<void(const ActionGoalConstPtr)> SendGoalFunc;
  typedef std::function<void(const RoleAttributes &)> SubscriberStatusCallback;

public:
  /**
   * \brief Constructor with namespacing options
   *
   * Constructs an ActionClient and sets up the necessary ros topics for the
   * ActionInterface, and namespaces them according the a specified NodeHandle
   * \param n The node handle on top of which we want to namespace our action
   * \param name The action name. Defines the namespace in which the action
   * communicates \param queue CallbackQueue from which this action will process
   * messages. The default (NULL) is to use the global queue
   */
  ActionClient(std::shared_ptr<Node> n, const std::string &name)
      : n_(n), guard_(new DestructionGuard()), manager_(guard_),
        topic_prefix_(name) {
    initClient();
  }

  ~ActionClient() {
    ADEBUG << "ActionClient: Waiting for destruction guard to clean up";
    guard_->destruct();
    channel_manager_->RemoveChangeListener(change_conn_);
    ADEBUG << "ActionClient: destruction guard destruct() done";
  }

  /**
   * \brief Sends a goal to the ActionServer, and also registers callbacks
   * \param transition_cb Callback that gets called on every client state
   * transition \param feedback_cb Callback that gets called whenever feedback
   * for this goal is received
   */
  GoalHandle sendGoal(const Goal &goal,
                      TransitionCallback transition_cb = TransitionCallback(),
                      FeedbackCallback feedback_cb = FeedbackCallback()) {
    ADEBUG << "about to start initGoal()";
    GoalHandle gh = manager_.initGoal(goal, transition_cb, feedback_cb);
    ADEBUG << "Done with initGoal()";

    return gh;
  }

  /**
   * \brief Cancel all goals currently running on the action server
   *
   * This preempts all goals running on the action server at the point that
   * this message is serviced by the ActionServer.
   */
  void cancelAllGoals() {
    GoalID cancel_msg;
    // CancelAll policy encoded by stamp=0, id=0
    cancel_msg.set_timestamp(cyber::Time(0, 0).ToNanosecond());
    cancel_msg.set_id(std::string(""));
    cancel_pub_->Write(cancel_msg);
  }

  /**
   * \brief Cancel all goals that were stamped at and before the specified time
   * \param time All goals stamped at or before `time` will be canceled
   */
  void cancelGoalsAtAndBeforeTime(const cyber::Time &time) {
    GoalID cancel_msg;
    cancel_msg.set_timestamp(time.ToNanosecond());
    cancel_msg.set_id(std::string(""));
    cancel_pub_->Write(cancel_msg);
  }

  /**
   * \brief Waits for the ActionServer to connect to this client
   * Often, it can take a second for the action server & client to negotiate
   * a connection, thus, risking the first few goals to be dropped. This call
   * lets the user wait until the network connection to the server is negotiated
   * NOTE: Using this call in a single threaded ROS application, or any
   * application where the action client's callback queue is not being
   * serviced, will not work. Without a separate thread servicing the queue, or
   * a multi-threaded spinner, there is no way for the client to tell whether
   * or not the server is up because it can't receive a status message.
   * \param timeout Max time to block before returning. A zero timeout is
   * interpreted as an infinite timeout. \return True if the server connected in
   * the allocated time. False on timeout
   */
  bool waitForActionServerToStart(
      const cyber::Duration &timeout = cyber::Duration(0, 0)) {
    // if ros::Time::isSimTime(), then wait for it to become valid
    cyber::Time::SleepUntil(cyber::Time::Now() + timeout);

    if (connection_monitor_) {
      return connection_monitor_->waitForActionServerToStart(timeout, n_);
    } else {
      return false;
    }
  }

  /**
   * @brief  Checks if the action client is successfully connected to the action
   * server
   * @return True if the server is connected, false otherwise
   */
  bool isServerConnected() { return connection_monitor_->isServerConnected(); }

private:
  std::shared_ptr<Node> n_;
  ChannelManagerPtr channel_manager_;

  std::shared_ptr<DestructionGuard> guard_;
  GoalManager<ActionSpec> manager_;
  Connection<const ChangeMsg &> change_conn_;
  std::string topic_prefix_;

  std::shared_ptr<cyber::Reader<ActionResult>> result_sub_;
  std::shared_ptr<cyber::Reader<ActionFeedback>> feedback_sub_;

  std::shared_ptr<ConnectionMonitor<ActionSpec>>
      connection_monitor_; // Have to destroy subscribers and publishers before
                           // the connection_monitor_, since we call callbacks
                           // in the connection_monitor_

  std::shared_ptr<cyber::Writer<ActionGoal>> goal_pub_;
  std::shared_ptr<cyber::Writer<GoalID>> cancel_pub_;
  std::shared_ptr<cyber::Reader<GoalStatusArray>> status_sub_;

  SubscriberStatusCallback goal_connect_cb_;
  SubscriberStatusCallback goal_disconnect_cb_;
  SubscriberStatusCallback cancel_connect_cb_;
  SubscriberStatusCallback cancel_disconnect_cb_;

  void sendGoalFunc(ActionGoalPtr action_goal) {
    goal_pub_->Write(action_goal);
  }

  void sendCancelFunc(std::shared_ptr<GoalID> cancel_msg) {
    cancel_pub_->Write(cancel_msg);
  }

  void initClient() {
    // read parameters indicating publish/subscribe queue sizes
    status_sub_ = n_->CreateReader<GoalStatusArray>(
        topic_prefix_ + "/status",
        std::bind(&ActionClientT::statusCb, this, std::placeholders::_1));
    feedback_sub_ = n_->CreateReader<ActionFeedback>(
        topic_prefix_ + "/feedback",
        std::bind(&ActionClientT::feedbackCb, this, std::placeholders::_1));
    result_sub_ = n_->CreateReader<ActionResult>(
        topic_prefix_ + "/result",
        std::bind(&ActionClientT::resultCb, this, std::placeholders::_1));

    connection_monitor_.reset(
        new ConnectionMonitor<ActionSpec>(feedback_sub_, result_sub_));

    goal_connect_cb_ =
        std::bind(&ConnectionMonitor<ActionSpec>::goalConnectCallback,
                  connection_monitor_, std::placeholders::_1);
    goal_disconnect_cb_ =
        std::bind(&ConnectionMonitor<ActionSpec>::goalDisconnectCallback,
                  connection_monitor_, std::placeholders::_1);
    cancel_connect_cb_ =
        std::bind(&ConnectionMonitor<ActionSpec>::cancelConnectCallback,
                  connection_monitor_, std::placeholders::_1);
    cancel_disconnect_cb_ =
        std::bind(&ConnectionMonitor<ActionSpec>::cancelDisconnectCallback,
                  connection_monitor_, std::placeholders::_1);

    // Start publishers and subscribers
    goal_pub_ = queue_advertise<ActionGoal>(topic_prefix_ + "/goal");
    cancel_pub_ = queue_advertise<GoalID>(topic_prefix_ + "/cancel");

    channel_manager_ = TopologyManager::Instance()->channel_manager();
    // listen new writers in future
    change_conn_ = channel_manager_->AddChangeListener(std::bind(
        &ActionClientT::OnChannelChange, this, std::placeholders::_1));

    manager_.registerSendGoalFunc(
        std::bind(&ActionClientT::sendGoalFunc, this, std::placeholders::_1));
    manager_.registerCancelFunc(
        std::bind(&ActionClientT::sendCancelFunc, this, std::placeholders::_1));
  }

  template <class M>
  std::shared_ptr<cyber::Writer<M>> queue_advertise(const std::string &topic) {

    return n_->CreateWriter<M>(topic);
  }

  void OnChannelChange(const ChangeMsg &change_msg) {

    if (change_msg.role_type() != RoleType::ROLE_READER) {
      return;
    }
    auto &reader_attr = change_msg.role_attr();
    if (reader_attr.channel_name() != topic_prefix_ + "/cancel" &&
        reader_attr.channel_name() != topic_prefix_ + "/goal") {
      return;
    }
    auto operate_type = change_msg.operate_type();

    if (operate_type == OperateType::OPT_JOIN) {
      if (reader_attr.channel_name() == topic_prefix_ + "/cancel" &&
          cancel_connect_cb_) {
        cancel_connect_cb_(reader_attr);
      } else if (reader_attr.channel_name() == topic_prefix_ + "/goal" &&
                 cancel_connect_cb_) {
        goal_connect_cb_(reader_attr);
      }

    } else if (operate_type == OperateType::OPT_LEAVE) {
      if (reader_attr.channel_name() == topic_prefix_ + "/cancel" &&
          cancel_disconnect_cb_) {
        cancel_disconnect_cb_(reader_attr);
      } else if (reader_attr.channel_name() == topic_prefix_ + "/goal" &&
                 cancel_disconnect_cb_) {
        goal_disconnect_cb_(reader_attr);
      }
    }
  }

  template <class M, class T>
  std::shared_ptr<cyber::Writer<M>>
  queue_subscribe(const std::string &topic, void (T::*fp)(const M &), T *obj) {

    return n_->CreateReader<M>(topic,
                               std::bind(fp, obj, std::placeholders::_1));
  }

  void statusCb(const GoalStatusArrayConstPtr &status_array_event) {

    ADEBUG << "Getting status over the wire.";
    if (connection_monitor_) {
      ChannelManager::RoleAttrVec pubs ;
      channel_manager_->GetWritersOfChannel(topic_prefix_ + "/status",&pubs);
      if(pubs.size() ==1 )
      {
      connection_monitor_->processStatus(status_array_event, pubs[0]);

      }

    }
    manager_.updateStatuses(status_array_event);
  }

  void feedbackCb(const ActionFeedbackConstPtr &action_feedback) {
    manager_.updateFeedbacks(action_feedback);
  }

  void resultCb(const ActionResultConstPtr &action_result) {
    manager_.updateResults(action_result);
  }
};

} // namespace actionlib
} // namespace apollo

#endif // ACTIONLIB__CLIENT__ACTION_CLIENT_H_
