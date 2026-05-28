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
#include "vart_memory.hpp"
#include "vart_memory_types.hpp"
#include "vart_inferresult.hpp"
#include "vart_postprocess_types.hpp"

namespace vart {

class PostProcessImplBase;

/*!
 * This module performs additional computations on output tensor data from NPU
 * to generate more meaningful interpretation. Post processing by default
 * supports YOLOv2, ResNet50, SSD-ResNet34, please check API documentation on
 * usage and additional information. If an application requires custom post
 * processing, it can override the base class methods.
 */

class PostProcess {
 public:
  PostProcess() = delete;

  /**
   * PostProcess() - Constructor for using existing post-process implementations
   *
   * @param postprocess_type
   *  Enum class to specify which implementation to instantiate
   * @param json_data
   *  JSON config string based on the implementation class
   * @param device
   *  Device handle to be used by implementations
   *
   */
  PostProcess(PostProcessType postprocess_type,
              std::string& json_data,
              std::shared_ptr<Device> device);

  /**
   * PostProcess() - Constructor for using user defined implementation
   *
   * @param ptr
   *  Pointer to user's implementation instance
   *
   */
  PostProcess(std::shared_ptr<PostProcessImplBase> ptr);

  /**
   * get_pimpl_handle() - Gives pointer to implementation class.
   *
   * @return
   *  Returns a constant reference of pointer to implementation class.
   */
  const std::shared_ptr<PostProcessImplBase>& get_pimpl_handle() const;

  /**
   * set_config() - Set PostProcessInfo config data before start doing the
   * post-process.
   *
   * @param info
   *  TensorInfo to be set.
   * @param batch_size
   *  Supported batch size.
   *
   * Use this method to set batch size per tensor and tensor information
   * required to parse/process the ML network output. Call this method before
   * the first call to "process" method.
   */
  void set_config(std::vector<TensorInfo>& info, uint32_t batch_size);

  /**
   * process() - Process/parse tensors data from ML network output to create
   * infer results.
   *
   * @param data
   *  Vector of tensors data. Each tensor will have the data for the entire
   * batch of images.
   * @param current_batch_size
   *  Numer of inputs in the current batch
   *
   * @return
   *  Vector of inference result objects for every image in the batch.
   */
  std::vector<std::vector<std::shared_ptr<InferResult>>> process(
      std::vector<int8_t*> data,
      uint32_t current_batch_size);


   /**
   * process() - Process/parse tensors data from ML network output to create
   * infer results.
   *
   * @param tensor_memory
   *  Vector of vart::Memory pointers. Each vart::Memory contains one tensor,
   *  total number of tensors is equal to current_batch_size * number of tensors in each batch.
   * @param current_batch_size
   *  Numer of inputs in the current batch
   *
   * @return
   *  Vector of inference result objects for every image in the batch.
   */
  std::vector<std::vector<std::shared_ptr<InferResult>>> process(
    std::vector<std::vector<std::shared_ptr<vart::Memory>>> tensor_memory,
    uint32_t current_batch_size);

 private:
  std::shared_ptr<PostProcessImplBase> pimpl;
};

}  // namespace vart
