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

#include "vart_device.hpp"
#include "vart_inferresult.hpp"
#include "vart_overlay_types.hpp"

namespace vart {

class MetaConvertImplBase;

/*!
 * This module facilitates the conversion of Infer metadata into a format
 * compatible with the overlay module. Metaconvert also accepts configuration
 * parameters as JSON string, which provide further flexibility on configuring
 * overlay information such as line thickness, font size, font type ., etc.
 * Please check API documentation for more information. Additionally, if users
 * have a custom meta data then they can integrate customized functions to
 * convert them into a format suitable for processing by the overlay module by
 * overriding base class.
 */

class MetaConvert {
 public:
  MetaConvert() = delete;

  /**
   * MetaConvert() - Constructor for using existing metaconvert implementations
   *
   * @param infer_res_type
   *  Enum class to specify which implementation to instantiate
   * @param json_data
   *  JSON config string based on the implementation class
   * @param device
   *  Device handle to be used
   *
   */
  MetaConvert(InferResultType infer_res_type,
              std::string& json_data,
              std::shared_ptr<Device> device);

  /**
   * MetaConvert() - Constructor for using user defined implementation
   *
   * @param ptr
   *  Pointer to user's implementation instance
   *
   */
  MetaConvert(std::shared_ptr<MetaConvertImplBase> ptr);

  /**
   * get_pimpl_handle() - Gives pointer to implementation class.
   *
   * @return
   *  Returns a constant reference of pointer to implementation class.
   */
  const std::shared_ptr<MetaConvertImplBase>& get_pimpl_handle() const;

    /**
     * prepare_overlay_meta() - Converts inference results to data structures needed for overlay. 
     *
     * @param root_infer_res
     *  Root node of the Inference results to be interpreted and converted
     *
     * @return
     *  Overlay shape info as per the inference results.
     */
    std::shared_ptr<OverlayShapeInfo> prepare_overlay_meta(
        std::shared_ptr<InferResult> root_infer_res);

 private:
  std::shared_ptr<MetaConvertImplBase> pimpl;
};

}  // namespace vart
