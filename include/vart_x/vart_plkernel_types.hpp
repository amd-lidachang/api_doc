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

#include <memory>
#include <string>

namespace vart {

enum class PLKernelImplType { PL_KERNEL_XRT };

/**
 * @class ArgumentInfo
 *
 * @brief Contains information related to an argument for the PL kernel.
 *
 * @var arg_name
 *  Name of the argument.
 *
 * @var arg_index
 *  Index of the argument.
 *
 * @var arg_size
 *  Size of the argument.
 *
 * @var mem_index
 *  Memory index on which the argument is attached, required to allocate
 * VartMemory.
 */
class ArgumentInfo {
public:
  std::string arg_name;
  unsigned int arg_index;
  size_t arg_size;
  int mem_index;
  /* Add shape and more info */
};

} /* namespace vart */
