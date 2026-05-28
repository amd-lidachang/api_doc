/*
 * Copyright 2024 Advanced Micro Devices Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include <string>
#include "vart_device.hpp"
#include "vart_videoframe.hpp"
#include "vart_inferresult.hpp"

namespace vart {
class TrackerImplBase;

/*!
 * The tracker module tracks detected objects from a sequence of video frames.
 * Tracker supports detecting 16 objects supporting tracker Id from 0
 * to 15. Beyond these, the tracker Id restart from 0.
 */

class Tracker {
 public:
  Tracker() = delete;

  /**
   * Tracker() - Constructor with implementation type and json data.
   *
   * @param device
   *  Device handle to be used by implementations.
   * 
   * @param json_data
   *  Tracker related configuration in JSON Format.
   */
  Tracker(std::shared_ptr<Device> device, std::string& json_data);

  /**
   * Tracker() - Constructor for using user defined implementation
   *
   * @param ptr
   *  Pointer to user's implementation instance
   *
   */
  Tracker(std::shared_ptr<TrackerImplBase> ptr);
  ~Tracker() = default;

  /**
   * process() - Perform tracking based on the specified parameters.
   *
   * @param frame
   *  Videoframe instance to be processed.
   * 
   * @param root_infer_res
   *  Root node of the Inference results. This will have child nodes if infer
   *  results are available, else with no child nodes.
   */
  void process(VideoFrame& frame, std::shared_ptr<InferResult> root_infer_res);

  /**
   * get_pimpl_handle() - Gives pointer to implementation class.
   *
   * @return
   *  Returns a constant reference of pointer to implementation class.
   */
  const std::shared_ptr<TrackerImplBase>& get_pimpl_handle() const;

 private:
  std::shared_ptr<TrackerImplBase> pimpl;  // Pointer to implementation
};
}  // namespace vart

