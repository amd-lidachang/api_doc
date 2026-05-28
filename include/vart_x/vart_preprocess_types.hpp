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

#include "vart_videoframe.hpp"
#include "vart_videoframe_types.hpp"

namespace vart {

/**
 * @enum PreProcessImplType - Preprocess Implementation Type.
 *
 * @var IMAGE_PROCESSING_HLS
 *  Implementation using Image Processing HLS kernel.
 *
 * @var IMAGE_PROCESSING_SW
 *  Implementation using Image Processing software kernel.
 */
enum class PreProcessImplType { IMAGE_PROCESSING_HLS, IMAGE_PROCESSING_SW };

/**
 * @enum PreProcessType - Type to maintain aspect ratio
 *
 * @var DEFAULT
 *  Resizes the image by not  maintaining aspect ratio
 * @var LETTERBOX
 *  Resizes the image by maintainig aspect ratio
 */
enum class PreProcessType { DEFAULT, LETTERBOX };

/**
 * @struct PreProcessInfo
 *
 * @brief Struture to store Pre processing parameters
 *
 * @var qt_fctr
 *  PreProcessing parameter quantization factor value.
 *
 * @var mean_r
 *  PreProcessing parameter alpha/mean red channel value.
 *
 * @var mean_g
 *  PreProcessing parameter alpha/mean green channel value.
 *
 * @var mean_b
 *  PreProcessing parameter alpha/mean blue channel value.
 *
 * @var scale_r
 *  PreProcessing parameter beta/scale red channel value.
 *
 * @var scale_g
 *  PreProcessing parameter beta/scale green channel value.
 *
 * @var scale_b
 *  PreProcessing parameter beta/scale blue channel value.
 *
 * @var height
 *  Height of the required output.
 *
 * @var width
 *  Width of the required output.
 *
 * @var colour_format
 *  Colour format of the required output.
 *
 * @var preprocess_type
 *  PreProcessing Type to maintain aspect ratio.
 *
 * @var symmetric_padding
 *  Symmetric padding for letterbox preprocess type.
 */
typedef struct {
  float qt_fctr;
  float mean_r;
  float mean_g;
  float mean_b;
  float scale_r;
  float scale_g;
  float scale_b;
  uint32_t height;
  uint32_t width;
  VideoFormat colour_format;
  PreProcessType preprocess_type;
  bool symmetric_padding;
} PreProcessInfo;

/**
 * @struct RegionOfInterest
 *
 * @brief Contains information related to region of interest
 *
 * @var x
 *  X coordinate of the ROI.
 *
 * @var y
 *  Y coordinate of the ROI.
 *
 * @var height
 *  Height of the ROI.
 *
 * @var width
 *  Width of the ROI.
 */
typedef struct {
  uint16_t x;
  uint16_t y;
  uint16_t height;
  uint16_t width;
} RegionOfInterest;

/* @struct PreProcessOp
 *
 * @brief Contains information related to the pre processing operations
 *  to be performed on the input frame
 *
 * @var in_roi
 *  contains roi of input frame.
 *
 * @var out_roi
 *  contains roi of output frame.
 *
 * @var in_frame
 *   VideoFrame pointer to hold input frame.
 *
 * @var out_frame
 *   VideoFrame pointer to hold output frame.
 */
typedef struct {
  RegionOfInterest in_roi;
  RegionOfInterest out_roi;
  VideoFrame* in_frame = nullptr;
  VideoFrame* out_frame = nullptr;
} PreProcessOp;

}  // namespace vart
