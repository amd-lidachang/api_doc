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

#include <cstdint>
#include <memory>
#include <string>
#include "vart_device.hpp"
#include "vart_preprocess_types.hpp"
#include "vart_videoframe.hpp"

namespace vart {
class PreProcessImplBase;

/*!
 * The preprocessing module handles data preparation tasks such as
 * normalization, scaling, and video format conversion. This module supports
 * software based pre-processing as well as hardware accelerated
 * pre-processing for optimized performance.  It ensures that input data is
 * appropriately formatted for inference. Application can also incorporate
 * custom pre processing by overriding base class methods.
 */

class PreProcess {
 public:
  PreProcess() = delete;

  /**
   * PreProcess() - Constructor with implementation type and json data.
   *
   * @param type
   *  PreProcessImplType based on which implementaion need to be used.
   *
   * @param json_data
   * Additional preprocessing/user related information
   * in JSON Format which can be used by implementations.
   *
   * @param device
   *  Device handle to be used by implementations.
   */
  PreProcess(PreProcessImplType type,
             std::string& json_data,
             std::shared_ptr<Device> device);

  /**
   * PreProcess() - Constructor for using user defined implementation
   *
   * @param ptr
   *  Pointer to user's implementation instance
   *
   */
  PreProcess(std::shared_ptr<PreProcessImplBase> ptr);
  ~PreProcess() = default;

  /**
   * process() - Perform pre-processing based on the specified parameters.
   *
   * @param preprocess_ops
   *  Vector of PreProcessOp to be performed.
   *  PreProcessOp contains input/output frame and their corresponding ROI.
   */
  void process(std::vector<PreProcessOp>& preprocess_ops);

  /**
   * get_input_vinfo() - Fills the input video info from input params.
   *
   * @param height
   *  Height of the input frame.
   *
   * @param width
   *  Width of the input frame.
   *
   * @param fmt
   *  Video format of the input frame.
   *
   * @param vinfo
   *  VideoInfo which can be filled by API. Filled VideoInfo can be used to construct
   *  input videoframe. User must provide valid pointer.
   */
  void get_input_vinfo(int32_t height,
                       int32_t width,
                       VideoFormat fmt,
                       VideoInfo& vinfo);

  /**
   * get_output_vinfo() - Get the output video info.
   *
   * @return
   *  Returns VideoInfo which can be used to construct output video frame.
   */
  const VideoInfo& get_output_vinfo();

  /**
   * set_preprocess_info() - Set the required Preprocess parameters.
   *
   * @param preprocess_info
   *  Struture with pre processing parameters.
   */
  void set_preprocess_info(PreProcessInfo& preprocess_info);

  /**
   * get_preprocess_info() - Get the preprocess info
   *
   * @return
   *  Returns struture of pre processing parameters.
   */
  const PreProcessInfo& get_preprocess_info();

  /**
   * get_pimpl_handle() - Gives pointer to implementation class.
   *
   * @return
   *  Returns a constant reference of pointer to implementation class.
   */
  const std::shared_ptr<PreProcessImplBase>& get_pimpl_handle() const;

 private:
  std::shared_ptr<PreProcessImplBase> pimpl;  // Pointer to implementation
};
}  // namespace vart
