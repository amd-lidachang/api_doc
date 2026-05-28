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

#ifndef VART_VIDEOFRAME_TYPES_HPP
#define VART_VIDEOFRAME_TYPES_HPP

#include <cstdint>
#include <string>

#define VART_VIDEO_MAX_PLANES 4

namespace vart {

/**
 * @enum VideoFrameImplType - Video Frame implementation type
 *
 * @var XRT
 *  Allocate memory using Xilinx Run Time (XRT) framework. This will allocate
 * physically contiguous memory.
 *
 * @var NON_CMA
 *  Non contiguos memory type
 *
 */
enum class VideoFrameImplType { XRT, NON_CMA };

/**
 * enum class VideoFormat - Represents video color formats supported by
 *   VART core APIs
 *
 * @var UNKNOWN
 *  Unknown color format
 *
 * @var Y_UV8_420
 *  planar 4:2:0 YUV with interleaved UV plane
 *
 * @var RGBx
 *  Packed RGB, 4 bytes per pixel
 *
 * @var r210
 *  Packed 4:4:4 RGB, 10 bits per channel
 *
 * @var Y410
 *  Packed 4:4:4 YUV, 10 bits per channel
 *
 * @var BGRx
 *  Packed BGR, 4 bytes per pixel
 *
 * @var BGRA
 *  Reverse rgb with alpha channel last
 *
 * @var RGBA
 *  RGB with alpha channel last
 *
 * @var YUY2
 *  Packed 4:2:2 YUV (Y0-U0-Y1-V0, Y2-U2-Y3-V2 Y4...)
 *
 * @var NV16
 *  Planar 4:2:2 YUV with interleaved UV plane
 *
 * @var RGB
 *  RGB packed into 24 bits without padding
 *
 * @var v308
 *  Packed 4:4:4 YUV
 *
 * @var BGR
 *  BGR packed into 24 bits without padding
 *
 * @var I422_10LE
 *  Planar 4:2:2 YUV, 10 bits per channel
 *
 * @var NV12_10LE32
 *  10-bit variant of NV12, packed into 32bit words (MSB 2 bits padding)
 *
 * @var GRAY8
 *  8-bit grayscale
 *
 * @var GRAY10_LE32
 *  10-bit grayscale, packed into 32bit words (2 bits padding)
 *
 * @var I420
 *  Planar 4:2:0 YUV
 *
 * @var RGBP
 *  Planar RGB
 *
 * @var BGR_FLOAT
 *  BGR float data packed into 96 bits without padding (32 bits per component)
 *
 * @var RGB_FLOAT
 *  RGB float data packed into 96 bits without padding (32 bits per component)
 *
 * @var RGBP_FLOAT
 *  RGB float data planar (32 bits per component)
 *
 * @var GRAY32_FLOAT
 *  Grayscale with 32bit float data
 *
 * @var RGBx_BF16
 *  Packed RGB (Brain Float) 16 bytes per pixel
 *
 * @var BGRx_BF16
 *  Packed BGR (Brain Float) 16 bytes per pixel
 *
 * @var GRAY_BF16
 *  Grayscale with 16bit brain float data
 */
enum class VideoFormat {
  UNKNOWN = 0,
  Y_UV8_420,
  RGBx,
  r210,
  Y410,
  BGRx,
  BGRA,
  RGBA,
  YUY2,
  NV16,
  RGB,
  v308,
  BGR,
  I422_10LE,
  NV12_10LE32,
  GRAY8,
  GRAY10_LE32,
  I420,
  RGBP,
  BGR_FLOAT,
  RGB_FLOAT,
  RGBP_FLOAT,
  GRAY32_FLOAT,
  RGBx_BF16,
  BGRx_BF16,
  GRAY_BF16
};

/**
 * @struct VideoAlignment
 *
 * @brief Contains video alignment information
 *
 * @var padding_right
 *  Padding to the right
 *
 * @var padding_left
 *  Padding to the left
 *
 * @var padding_top
 *  Padding to the top
 *
 * @var padding_bottom
 *  Padding to the bottom
 *
 * @var stride_align
 *  Extra alignment requirement for strides (which is in bytes)
 */

typedef struct {
  uint32_t padding_right;
  uint32_t padding_left;
  uint32_t padding_top;
  uint32_t padding_bottom;
  uint32_t stride_align[VART_VIDEO_MAX_PLANES];
} VideoAlignment;

/**
 * @struct VideoInfo
 *
 * @brief Contains infomation related to a video frame
 *
 * @var width
 *  Width of a video frame
 *
 * @var height
 *  Height of a video frame
 *
 * @var fmt
 *  Video frame color format
 *
 * @var n_planes
 *  Number of planes in video frame color format
 *
 * @var stride
 *  Array of stride values
 *
 * @var elevation
 *  Array of elevation values
 *
 * @var alignment
 *  Video frame's alignment information
 */
typedef struct {
  int32_t width;
  int32_t height;
  VideoFormat fmt;
  uint32_t n_planes;
  size_t stride[VART_VIDEO_MAX_PLANES];
  size_t elevation[VART_VIDEO_MAX_PLANES];
  VideoAlignment alignment;
} VideoInfo;

/**
 * @struct VideoPlaneInfo
 *
 * @brief Structure contains information specific to a
 *  video frame plane
 *
 * @var data
 *  Pointer to a video frame plane data
 *
 * @var phy_addr
 *  Physical memory address on the device
 *
 * @var size
 *  Size of a video plane
 *
 * @var offset
 *  Offset of the first valid data from the @data pointer
 *
 * @var stride
 *  Stride of a video plane
 *
 * @var elevation
 *  Elevation (in height direction) of a video plane
 */
typedef struct {
  uint8_t* data;
  uint64_t phy_addr;
  size_t size;
  size_t offset;
  int32_t stride;
  int32_t elevation;
} VideoPlaneInfo;

/**
 * @struct VideoFrameMapInfo
 *
 * @brief Structure encapsulating details pertaining to a
 * video frame post-mapping operation
 *
 * @var nplanes
 *  Number of planes in a video frame
 *
 * @var size
 *  Video frame size
 *
 * @var width
 *  Width of the mapped video frame
 *
 * @var height
 *  Height of the mapped video frame
 *
 * @var fmt
 *  Video frame color format
 *
 * @var alignment
 *  Video frame's Alignment information
 *
 * @var planes:
 *  Array containing video plane specific information
 *
 * @var usr_meta
 *  points to user specific meta data if any
 */
typedef struct {
  uint8_t nplanes;
  size_t size;
  int32_t width;
  int32_t height;
  VideoFormat fmt;
  VideoAlignment alignment;
  VideoPlaneInfo planes[VART_VIDEO_MAX_PLANES];
  void* usr_meta;
} VideoFrameMapInfo;

}  // namespace vart
#endif  // VART_VIDEOFRAME_TYPES_HPP
