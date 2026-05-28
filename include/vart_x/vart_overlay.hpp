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
#include "vart_overlay_types.hpp"
#include "vart_videoframe.hpp"

namespace vart {

class OverlayImplBase;

/*!
 * This module facilitates the overlay of annotations onto the video frame,
 * currently overlay utilizes OpenCV library to draw on frames, which is
 * software based. Overlay supports drawing of bounding boxes, text, lines,
 * arrows, circles and polygons on frames. Application can also incorporate
 * custom implementation using base class.
 */

class Overlay {
 public:
  Overlay() = delete;

  /**
   * Overlay() - Constructor for creating an overlay instance,
   * which accepts input type and device instance parameters.
   *
   * @param overlay_impl_type
   *  Enum class to specify which type of overlay implementation to use
   *
   * @param device
   *  Device handle to be used by implementation
   */
  Overlay(OverlayImplType overlay_impl_type, std::shared_ptr<Device> device);

  /**
   * Overlay() - Constructor for creating an overlay instance,
   * which accepts user defined pimpl parameters.
   *
   * @param ptr
   *  Pointer to user's implementation instance
   */
  Overlay(std::shared_ptr<OverlayImplBase> ptr);

  /**
   * get_pimpl_handle() - Retrieves pointer to implementation class.
   *
   * @return
   *  Returns a constant reference of pointer to implementation class.
   */
  const std::shared_ptr<OverlayImplBase>& get_pimpl_handle() const;

  /**
   * draw_overlay() - Draws the input overlay information on to the frame
   *
   * @param frame
   *  video frame on which drawing operation to be performed
   *
   * @param shape_info
   *  Information used in drawing operation
   */
  void draw_overlay(VideoFrame& frame, OverlayShapeInfo& shape_info);

 private:
  std::shared_ptr<OverlayImplBase> pimpl;
};

}  // namespace vart
