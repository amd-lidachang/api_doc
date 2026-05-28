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

#ifndef VART_MEMORY_TYPES_HPP
#define VART_MEMORY_TYPES_HPP

namespace vart {

/**
 * @enum DataMapFlags - Map flags.
 *
 * @var READ
 *  Map data in read mode.
 *
 * @var WRITE
 *  Map data in write mode.
 */
enum class DataMapFlags {
  NONE = 0,
  READ = 1 << 0,
  WRITE = 1 << 1,
};

/**
 * @enum MemoryImplType - Memory Implementation type.
 *
 * @var XRT
 *  XRT allocation type.
 *
 * @var NON_CMA
 *  Non CMA allocation type.
 */
enum class MemoryImplType { XRT, NON_CMA };
}  // namespace vart
#endif  // VART_MEMORY_TYPES_HPP
