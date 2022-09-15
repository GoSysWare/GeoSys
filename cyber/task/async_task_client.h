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

#ifndef CYBER_TASK_ASYNC_CLIENT_H_
#define CYBER_TASK_ASYNC_CLIENT_H_

#include <future>
#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <tuple>
#include <unordered_map>
#include <utility>

#include "cyber/common/log.h"
#include "cyber/common/types.h"

#include "cyber/node/node_channel_impl.h"
#include "cyber/task/async_task_client_base.h"

namespace apollo {
namespace cyber {

/**
 * @class AsyncTaskClient
 * @brief AsyncTaskClient get `Response` from a responding `AsyncTask` by sending a Request
 *
 * @tparam Request the `AsyncTask` request type
 * @tparam Response the `AsyncTask` response type
 *
 * @warning One Client can only request one AsyncTask
 */
template <typename Request, typename Response>
class AsyncTaskClient : public AsyncTaskClientBase {
 public:
  using SharedRequest = typename std::shared_ptr<Request>;
  using SharedResponse = typename std::shared_ptr<Response>;
  using Promise = std::promise<SharedResponse>;
  using SharedPromise = std::shared_ptr<Promise>;
  using SharedFuture = std::shared_future<SharedResponse>;
  using CallbackType = std::function<void(SharedFuture)>;

  /**
   * @brief Construct a new Client object
   *
   * @param node_name used to fill RoleAttribute
   * @param task_name task name the Client can request
   */
  AsyncTaskClient(const std::string& node_name, const std::string& task_name)
      : AsyncTaskClientBase(task_name),
        node_name_(node_name),
        request_channel_(task_name + SRV_CHANNEL_REQ_SUFFIX),
        response_channel_(task_name + SRV_CHANNEL_RES_SUFFIX),
        sequence_number_(0) {}

  /**
   * @brief forbid Constructing a new Client object with empty params
   */
  AsyncTaskClient() = delete;

  virtual ~AsyncTaskClient() {}

  /**
   * @brief Init the Client
   *
   * @return true if init successfully
   * @return false if init failed
   */
  bool Init();

  /**
   * @brief Request the Task with a shared ptr Request type
   *
   * @param request shared ptr of Request type
   * @param timeout_s request timeout, if timeout, response will be empty
   * @return SharedResponse result of this request
   */
  SharedResponse SendRequest(
      SharedRequest request,
      const std::chrono::seconds& timeout_s = std::chrono::seconds(5));

  /**
   * @brief Request the Task with a Request object
   *
   * @param request Request object
   * @param timeout_s request timeout, if timeout, response will be empty
   * @return SharedResponse result of this request
   */
  SharedResponse SendRequest(
      const Request& request,
      const std::chrono::seconds& timeout_s = std::chrono::seconds(5));

  /**
   * @brief Send Request shared ptr asynchronously
   */
  SharedFuture AsyncSendRequest(SharedRequest request);

  /**
   * @brief Send Request object asynchronously
   */
  SharedFuture AsyncSendRequest(const Request& request);

  /**
   * @brief Send Request shared ptr asynchronously and invoke `cb` after we get
   * response
   *
   * @param request Request shared ptr
   * @param cb callback function after we get response
   * @return SharedFuture a `std::future` shared ptr
   */
  SharedFuture AsyncSendRequest(SharedRequest request, CallbackType&& cb);

  /**
   * @brief Is the Task is ready?
   */
  bool TaskIsReady() const;

  /**
   * @brief destroy this Client
   */
  void Destroy();

  /**
   * @brief wait for the connection with the Task established
   *
   * @tparam RatioT timeout unit, default is std::milli
   * @param timeout wait time in unit of `RatioT`
   * @return true if the connection established
   * @return false if timeout
   */
  template <typename RatioT = std::milli>
  bool WaitForTask(std::chrono::duration<int64_t, RatioT> timeout =
                          std::chrono::duration<int64_t, RatioT>(-1)) {
    return WaitForTaskNanoseconds(
        std::chrono::duration_cast<std::chrono::nanoseconds>(timeout));
  }

 private:
  void HandleResponse(const std::shared_ptr<Response>& response,
                      const transport::MessageInfo& request_info);

  bool IsInit(void) const { return response_receiver_ != nullptr; }

  std::string node_name_;

  std::function<void(const std::shared_ptr<Response>&,
                     const transport::MessageInfo&)>
      response_callback_;

  std::unordered_map<uint64_t,
                     std::tuple<SharedPromise, CallbackType, SharedFuture>>
      pending_requests_;
  std::mutex pending_requests_mutex_;

  std::shared_ptr<transport::Transmitter<Request>> request_transmitter_;
  std::shared_ptr<transport::Receiver<Response>> response_receiver_;
  std::string request_channel_;
  std::string response_channel_;

  transport::Identity writer_id_;
  uint64_t sequence_number_;
};

template <typename Request, typename Response>
void AsyncTaskClient<Request, Response>::Destroy() {}

template <typename Request, typename Response>
bool AsyncTaskClient<Request, Response>::Init() {
  proto::RoleAttributes role;
  role.set_node_name(node_name_);
  role.set_channel_name(request_channel_);
  auto channel_id = common::GlobalData::RegisterChannel(request_channel_);
  role.set_channel_id(channel_id);
  role.mutable_qos_profile()->CopyFrom(
      transport::QosProfileConf::QOS_PROFILE_SERVICES_DEFAULT);
  auto transport = transport::Transport::Instance();
  request_transmitter_ =
      transport->CreateTransmitter<Request>(role, proto::OptionalMode::INTRA);
  if (request_transmitter_ == nullptr) {
    AERROR << "Create request pub failed.";
    return false;
  }
  writer_id_ = request_transmitter_->id();

  response_callback_ =
      std::bind(&AsyncTaskClient<Request, Response>::HandleResponse, this,
                std::placeholders::_1, std::placeholders::_2);

  role.set_channel_name(response_channel_);
  channel_id = common::GlobalData::RegisterChannel(response_channel_);
  role.set_channel_id(channel_id);
  response_receiver_ = transport->CreateReceiver<Response>(
      role,
      [=](const std::shared_ptr<Response>& response,
          const transport::MessageInfo& message_info,
          const proto::RoleAttributes& reader_attr) {
        (void)message_info;
        (void)reader_attr;
        response_callback_(response, message_info);
      },
      proto::OptionalMode::INTRA);
  if (response_receiver_ == nullptr) {
    AERROR << "Create response sub failed.";
    request_transmitter_.reset();
    return false;
  }
  return true;
}

template <typename Request, typename Response>
typename AsyncTaskClient<Request, Response>::SharedResponse
AsyncTaskClient<Request, Response>::SendRequest(SharedRequest request,
                                       const std::chrono::seconds& timeout_s) {
  if (!IsInit()) {
    return nullptr;
  }
  auto future = AsyncSendRequest(request);
  if (!future.valid()) {
    return nullptr;
  }
  auto status = future.wait_for(timeout_s);
  if (status == std::future_status::ready) {
    return future.get();
  } else {
    return nullptr;
  }
}

template <typename Request, typename Response>
typename AsyncTaskClient<Request, Response>::SharedResponse
AsyncTaskClient<Request, Response>::SendRequest(const Request& request,
                                       const std::chrono::seconds& timeout_s) {
  if (!IsInit()) {
    return nullptr;
  }
  auto request_ptr = std::make_shared<const Request>(request);
  return SendRequest(request_ptr, timeout_s);
}

template <typename Request, typename Response>
typename AsyncTaskClient<Request, Response>::SharedFuture
AsyncTaskClient<Request, Response>::AsyncSendRequest(const Request& request) {
  auto request_ptr = std::make_shared<const Request>(request);
  return AsyncSendRequest(request_ptr);
}

template <typename Request, typename Response>
typename AsyncTaskClient<Request, Response>::SharedFuture
AsyncTaskClient<Request, Response>::AsyncSendRequest(SharedRequest request) {
  return AsyncSendRequest(request, [](SharedFuture) {});
}

template <typename Request, typename Response>
typename AsyncTaskClient<Request, Response>::SharedFuture
AsyncTaskClient<Request, Response>::AsyncSendRequest(SharedRequest request,
                                            CallbackType&& cb) {
  if (IsInit()) {
    std::lock_guard<std::mutex> lock(pending_requests_mutex_);
    sequence_number_++;
    transport::MessageInfo info(writer_id_, sequence_number_, writer_id_);
    request_transmitter_->Transmit(request, info);
    SharedPromise call_promise = std::make_shared<Promise>();
    SharedFuture f(call_promise->get_future());
    pending_requests_[info.seq_num()] =
        std::make_tuple(call_promise, std::forward<CallbackType>(cb), f);
    return f;
  } else {
    return std::shared_future<std::shared_ptr<Response>>();
  }
}

template <typename Request, typename Response>
bool AsyncTaskClient<Request, Response>::TaskIsReady() const {
  return true;
}

template <typename Request, typename Response>
void AsyncTaskClient<Request, Response>::HandleResponse(
    const std::shared_ptr<Response>& response,
    const transport::MessageInfo& request_header) {
  ADEBUG << "client recv response.";
  std::lock_guard<std::mutex> lock(pending_requests_mutex_);
  if (request_header.spare_id() != writer_id_) {
    return;
  }
  uint64_t sequence_number = request_header.seq_num();
  if (this->pending_requests_.count(sequence_number) == 0) {
    return;
  }
  auto tuple = this->pending_requests_[sequence_number];
  auto call_promise = std::get<0>(tuple);
  auto callback = std::get<1>(tuple);
  auto future = std::get<2>(tuple);
  this->pending_requests_.erase(sequence_number);
  call_promise->set_value(response);
  callback(future);
}

}  // namespace cyber
}  // namespace apollo

#endif  // CYBER_TASK_ASYNC_CLIENT_H_
