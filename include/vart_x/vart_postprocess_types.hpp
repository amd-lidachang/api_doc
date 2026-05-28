/*
 * Copyright 2024-2025 Advanced Micro Devices Inc.
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
#include <vector>

namespace vart {

/**
 * @enum vart::TensorDataType
 *
 * @brief Specifies the data type of a tensor.
 *
 * @var vart::TensorDataType::INT8
 *  Represents an 8-bit integer data type.
 *
 * @var vart::TensorDataType::FLOAT32
 *  Represents a 32-bit floating-point data type.
 */
enum class TensorDataType {
  INT8,
  FLOAT32,
  BF16,
  UNKNOWN
};

/**
 * @struct TensorInfo
 *
 * @brief Tensor config information
 *
 * @var size
 *  Size of the entire tensor in bytes
 * @var scale_coeff
 *  Quantization scale factor of tensor
 * @var shape
 *  Shape dimension of each tensor
 * @var name
 *   Name of the tensor
 *
 */
typedef struct {
  uint32_t size;
  float scale_coeff;
  std::vector<uint32_t> shape;
  std::string name;
  TensorDataType data_type;
} TensorInfo;

/**
 * @enum PostProcessType - ML Model type
 *
 * @var RESNET50
 *  Resnet50 model
 * @var YOLOV2
 *  Yolov2 model
 * @var SSDRESNET34
 *  ssdresnet34 model
 */
enum class PostProcessType { RESNET50, YOLOV2, SSDRESNET34 };

}  // namespace vart
