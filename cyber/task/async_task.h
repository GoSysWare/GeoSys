/******************************************************************************
 * Copyright 2018 The Apollo Authors. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *****************************************************************************/

#ifndef CYBER_TASK_ASYNC_TASK_H_
#define CYBER_TASK_ASYNC_TASK_H_

#include <list>
#include <memory>
#include <string>
#include <utility>

#include "cyber/common/types.h"
#include "cyber/node/node_channel_impl.h"
#include "cyber/scheduler/scheduler.h"
#include "cyber/task/async_task_base.h"
#include "cyber/task/task.h"

namespace apollo {
namespace cyber {

/**
 * @class AsyncTask
 * @brief AsyncTask handles `Request` from the Client, and send a `Response` to
 * it.
 *
 * @tparam Request the request type
 * @tparam Response the response type
 */
template <typename Request, typename Response>
class AsyncTask : public AsyncTaskBase {
 public:
  using TaskCallback = std::function<void(const std::shared_ptr<Request>&,
                                             std::shared_ptr<Response>&)>;
  /**
   * @brief Construct a new AsyncTask object
   *
   * @param node_name used to fill RoleAttribute when join the topology
   * @param task_name the AsyncTask name we provide
   * @param task_callback reference of `TaskCallback` object
   */
  AsyncTask(const std::string& node_name, const std::string& task_name,
          const TaskCallback& task_callback)
      : AsyncTaskBase(task_name),
        node_name_(node_name),
        task_callback_(task_callback),
        request_channel_(task_name + SRV_CHANNEL_REQ_SUFFIX),
        response_channel_(task_name + SRV_CHANNEL_RES_SUFFIX) {}

  /**
   * @brief Construct a new AsyncTask object
   *
   * @param node_name used to fill RoleAttribute when join the topology
   * @param task_name the task name we provide
   * @param task_callback rvalue reference of `TaskCallback` object
   */
  AsyncTask(const std::string& node_name, const std::string& task_name,
          TaskCallback&& task_callback)
      : AsyncTaskBase(task_name),
        node_name_(node_name),
        task_callback_(task_callback),
        request_channel_(task_name + SRV_CHANNEL_REQ_SUFFIX),
        response_channel_(task_name + SRV_CHANNEL_RES_SUFFIX) {}

  /**
   * @brief Forbid default constructing
   */
  AsyncTask() = delete;

  ~AsyncTask() { destroy(); }

  /**
   * @brief Init the AsyncTask
   */
  bool Init();

  /**
   * @brief Destroy the AsyncTask
   */
  void destroy();

 private:
  void HandleRequest(const std::shared_ptr<Request>& request,
                     const transport::MessageInfo& message_info);

  void SendResponse(const transport::MessageInfo& message_info,
                    const std::shared_ptr<Response>& response);

  bool IsInit(void) const { return request_receiver_ != nullptr; }

  std::string node_name_;
  TaskCallback task_callback_;

  std::function<void(const std::shared_ptr<Request>&,
                     const transport::MessageInfo&)>
      request_callback_;
  std::shared_ptr<transport::Transmitter<Response>> response_transmitter_;
  std::shared_ptr<transport::Receiver<Request>> request_receiver_;
  std::string request_channel_;
  std::string response_channel_;
  //不支持多并发
  std::mutex task_handle_request_mutex_;

  volatile bool inited_ = false;
  void Enqueue(std::function<void()>&& task);
};

template <typename Request, typename Response>
void AsyncTask<Request, Response>::destroy() {
  inited_ = false;
}



template <typename Request, typename Response>
bool AsyncTask<Request, Response>::Init() {
  if (IsInit()) {
    return true;
  }
  proto::RoleAttributes role;
  role.set_node_name(node_name_);
  role.set_channel_name(response_channel_);
  auto channel_id = common::GlobalData::RegisterChannel(response_channel_);
  role.set_channel_id(channel_id);
  role.mutable_qos_profile()->CopyFrom(
      transport::QosProfileConf::QOS_PROFILE_SERVICES_DEFAULT);
  auto transport = transport::Transport::Instance();
  response_transmitter_ =
      transport->CreateTransmitter<Response>(role, proto::OptionalMode::RTPS);
  if (response_transmitter_ == nullptr) {
    AERROR << " Create response pub failed.";
    return false;
  }

  role.set_channel_name(request_channel_);
  channel_id = common::GlobalData::RegisterChannel(request_channel_);
  role.set_channel_id(channel_id);
  request_receiver_ = transport->CreateReceiver<Request>(
      role,
      [=](const std::shared_ptr<Request>& request,
          const transport::MessageInfo& message_info,
          const proto::RoleAttributes& reader_attr) {
        (void)reader_attr;
        auto task = [this, request, message_info]() {
          this->HandleRequest(request, message_info);
        };
        Async(std::move(task));
      },
      proto::OptionalMode::RTPS);
  inited_ = true;
  if (request_receiver_ == nullptr) {
    AERROR << " Create request sub failed." << request_channel_;
    response_transmitter_.reset();
    return false;
  }
  return true;
}

template <typename Request, typename Response>
void AsyncTask<Request, Response>::HandleRequest(
    const std::shared_ptr<Request>& request,
    const transport::MessageInfo& message_info) {
  if (!IsInit()) {
    // LOG_DEBUG << "not inited error.";
    return;
  }
  ADEBUG << "handling request:" << request_channel_;
  std::lock_guard<std::mutex> lk(task_handle_request_mutex_);
  auto response = std::make_shared<Response>();
  task_callback_(request, response);
  transport::MessageInfo msg_info(message_info);
  msg_info.set_sender_id(response_transmitter_->id());
  SendResponse(msg_info, response);
}

template <typename Request, typename Response>
void AsyncTask<Request, Response>::SendResponse(
    const transport::MessageInfo& message_info,
    const std::shared_ptr<Response>& response) {
  if (!IsInit()) {
    // LOG_DEBUG << "not inited error.";
    return;
  }
  // publish return value ?
  // LOG_DEBUG << "send response id:" << message_id.sequence_number;
  response_transmitter_->Transmit(response, message_info);
}

}  // namespace cyber
}  // namespace apollo

#endif  // CYBER_TASK_ASYNC_TASK_H_
