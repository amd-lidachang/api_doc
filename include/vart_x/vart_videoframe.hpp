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

#ifndef VART_VIDEOFRAME_HPP
#define VART_VIDEOFRAME_HPP

#include <xrt/xrt_bo.h>
#include <vector>
#include "vart_device.hpp"
#include "vart_memory_types.hpp"
#include "vart_videoframe_types.hpp"

namespace vart {

class VideoFrameImplBase;

/*!
 * This module simplifies the management of frame memory complexities and
 * provides APIs for reading and writing a frame. The VideoFrame class offers
 * flexibility for applications to encapsulate their own memory into the
 * VideoFrame class. In such instances, the application bears the
 * responsibility for deallocating the frame memory.
 */

class VideoFrame {
 public:
  /**
   *  VideoFrame() - Constructor for creating video frame instance using
   *  implementation specific method based on input 'type'
   *
   * @param type
   *  Enum class to specify which type of memory allocation method to use
   *
   * @param size
   *  Size of the buffer
   *
   * @param mbank_idx
   *  memory bank index on which memory needss to be allocated
   *
   * @param vinfo
   *  VideoInfo instance which contains video frame specific information
   *
   * @param device
   *  Device handle to be used by implementation
   */
  VideoFrame(VideoFrameImplType type,
             size_t size,
             uint8_t mbank_idx,
             VideoInfo& vinfo,
             std::shared_ptr<Device> device);

  /**
   * VideoFrame() - Constructor for creating video frame instance using
   * input data pointers
   *
   * @param type
   *  Enum class to specify which type of memory allocation method to use
   *
   * @param data_vec
   *  Vector of user allocated buffer pointers
   *
   * @param vinfo
   *  VideoInfo instance which contains video frame specific information
   *
   * @param device
   *  Device handle to be used by implementation
   */
  VideoFrame(VideoFrameImplType type,
             std::vector<uint8_t*>& data_vec,
             VideoInfo& vinfo,
             std::shared_ptr<Device> device);

  /**
   * VideoFrame() - Constructor for creating video frame instance using
   * input XRT Buffer object(BO)
   *
   * @param type
   *  Enum class to specify which type of memory allocation method to use
   *
   * @param mbank_idx
   *  memory bank index on which memory was allocated
   *
   * @param bo_vec
   *  Vector of XRT BOs allocated by user
   *
   * @param vinfo
   *  VideoInfo instance which contains video frame specific information
   *
   * @param device
   *  Device handle to be used by implementation
   */
  VideoFrame(VideoFrameImplType type,
             uint8_t mbank_idx,
             std::vector<xrt::bo*>& bo_vec,
             VideoInfo& vinfo,
             std::shared_ptr<Device> device);

  ~VideoFrame() = default;

  /**
   * map() - Maps video frame data to user space
   *
   * @param map_flags
   *  Flag used to indicate mode of memory mapping
   *
   * @return
   *  Returns information containing user space data pointer(s) and
   *  its corresponding video frame information.
   */
  const VideoFrameMapInfo& map(DataMapFlags map_flags);

  /**
   * unmap() - Unmaps video frame data from user space
   */
  void unmap();

  /**
   * get_video_info() - Retrieves the video frame information from video frame
   *
   * @return
   *  Returns infomation related to video frame
   */
  const VideoInfo& get_video_info() const;

  /**
   * get_device_handle() - Retrieves the device handle associated with the
   * current frame
   *
   */
  std::shared_ptr<Device> get_device_handle() const;

  /**
   * get_pimpl_handle() - Retrieves pointer to implementation class.
   *
   * @return
   *  Returns a constant reference of pointer to implementation class.
   */
  const std::shared_ptr<VideoFrameImplBase>& get_pimpl_handle() const;

 private:
  std::shared_ptr<VideoFrameImplBase> pimpl;
};
}  // namespace vart
#endif  // VART_VIDEOFRAME_HPP
