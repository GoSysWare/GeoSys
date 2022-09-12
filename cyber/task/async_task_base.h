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

#ifndef CYBER_TASK_ASYNC_TASK_BASEH_
#define CYBER_TASK_ASYNC_TASK_BASEH_

#include <string>

namespace apollo {
namespace cyber {

/**
 * @class AsyncTaskBase
 * @brief Base class for AsyncTask
 *
 */
class AsyncTaskBase {
 public:
  /**
   * @brief Construct a new Task Base object
   *
   * @param task_name name of this Task
   */
  explicit AsyncTaskBase(const std::string& task_name)
      : task_name_(task_name) {}

  virtual ~AsyncTaskBase() {}

  virtual void destroy() = 0;

  /**
   * @brief Get the task name
   */
  const std::string& task_name() const { return task_name_; }

 protected:
  std::string task_name_;
};

}  // namespace cyber
}  // namespace apollo

#endif  // CYBER_TASK_ASYNC_TASK_BASEH_
