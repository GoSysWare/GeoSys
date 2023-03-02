/******************************************************************************
 * Copyright 2017 The Apollo Authors. All Rights Reserved.
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

#pragma once

#include <atomic>
#include <future>
#include <memory>
#include <vector>

#include "cyber/cyber.h"
#include "modules/calc/devices/camera/proto/config.pb.h"

#include "modules/calc/devices/camera/usb_cam.h"


using apollo::drivers::camera::config::Config;

class CameraComponent {
 public:
  bool Init(std::string config) ;
  ~CameraComponent();
  CameraImagePtr raw_image_ = nullptr;

 private:
  void run();

  std::unique_ptr<UsbCam> camera_device_;
  std::shared_ptr<Config> camera_config_;
  std::vector<CameraImagePtr> raw_image_buffer_;

  uint32_t spin_rate_ = 200;
  uint32_t device_wait_ = 2000;
  int index_ = 0;
  int buffer_size_ = 16;
  const int32_t MAX_IMAGE_SIZE = 20 * 1024 * 1024;
  std::future<void> async_result_;
  std::atomic<bool> running_ = {false};
};

