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
#include <vector>

namespace vart {

enum class TraversalOrder { PREORDER, INORDER, POSTORDER };

/**
 * @enum InferResultType - ML Network type
 *
 * @var ROOT
 *  This type is used to represent the root node of the
 *  tree structure.
 * @var CLASSIFICATION
 *  Classification network
 * @var DETECTION
 *  Detection network
 * @var CUSTOM_RESULT_1
 *  Defined for user specific result type
 * @var CUSTOM_RESULT_2
 *  Defined for user specific result type
 * @var CUSTOM_RESULT_3
 *  Defined for user specific result type
 */
enum class InferResultType
  {
    ROOT,
    CLASSIFICATION,
    DETECTION,
    CUSTOM_RESULT_1 = 100,
    CUSTOM_RESULT_2,
    CUSTOM_RESULT_3,
  };

/**
 * @struct InferResScaleInfo
 *
 * @brief Scale factor info
 *
 * @var width_scale_factor
 *  Width scaler factor
 * @var height_scale_factor
 *  Height scale factor
 *
 */
typedef struct {
  float width_scale_factor;
  float height_scale_factor;
} InferResScaleInfo;

/**
 * @struct InferResultData
 *
 * @brief Base structure for inference result data.
 *
 * @var result_type
 *  Type of infer result
 */
struct InferResultData {
  InferResultType result_type;
};

/**
 * @struct ClassificationResData
 *
 * @brief Classification infer result
 *
 * @var label
 *  Array of label strings in classification result
 * @var confidence
 *  Array of probability score in classification result
 * @var index
 *  Index of the class
 */
struct ClassificationResData : public InferResultData {
  std::vector<std::string> label;
  std::vector<double> confidence;
  std::vector<uint8_t> index;
};

/**
 * @struct DetectionResData
 *
 * @brief Detection infer result
 *
 * @var x
 *  X co-ordinate of top left corner of the bounding box
 * @var y
 *  Y co-ordinate of top left corner of the bounding box
 * @var width
 *  Width of the bounding box
 * @var height
 *  Height of the bounding box
 * @var label
 *  Label string for the detected object
 * @var confidence
 *  Probability score of the infer result
 * @var obj_track_label
 *  Label of th tracked object
 * @var class_id
 *  Classification index
 */
struct DetectionResData : public InferResultData {
  int32_t x;
  int32_t y;
  uint32_t width;
  uint32_t height;
  std::string label;
  double confidence;
  std::string obj_track_label;
  int class_id;
};

}  // namespace vart
