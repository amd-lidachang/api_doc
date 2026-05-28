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

#include <cstdint>
#include <string>
#include "vart_device.hpp"
#include "vart_memory_types.hpp"

namespace vart {

class MemoryImplBase;

/*!
 * This module is responsible for allocating and managing memory on the device.
 */

class Memory {
 public:
  /**
   * Memory() - Constructor to allocate memory using implementation
   *  specific method based on input 'type'
   *
   * @param type
   *  Enum class to specify which type of memory allocation method to use
   *
   * @param size
   *  Size of the buffer
   *
   * @param mbank_idx
   *  memory bank index on which memory needs to be allocated
   *
   * @param device
   *  Device handle to be used by implementation
   */
  Memory(MemoryImplType type,
         size_t size,
         uint8_t mbank_idx,
         std::shared_ptr<Device> device);

  /**
   * Memory() - Constructor to create Memory instance using user provided
   * data pointer
   *
   * @param type
   *  Enum class to specify which type of memory allocation method to use
   *
   * @param data
   *  user allocated buffer pointer
   *
   * @param size
   *  Size of the buffer
   *
   * @param device
   *  Device handle to be used by implementation
   */
  Memory(MemoryImplType type,
         uint8_t* data,
         size_t size,
         std::shared_ptr<Device> device);

  /**
   * Memory() - Constructor for using user defined implementation
   *
   * @param ptr
   *  Pointer to user's implementation instance
   */
  Memory(std::shared_ptr<MemoryImplBase> ptr);

  ~Memory() = default;

  /**
   * map() - Maps allocated memory to user space.
   *
   * @param map_flags
   *  Flag used to indicate mode of memory mapping
   *
   * @return
   *  returns the virtual address
   *
   * Only Memory allocated with XRT/CMA type of memory can be used with map()
   */
  const uint8_t* map(DataMapFlags map_flags);

  /**
   * unmap() - Unmaps allocated memory from user space
   */
  void unmap();

  /**
   * get_pimpl_handle() - Retrieves pointer to Memory Implementation Base class
   *
   * @return
   *  Returns a constant reference of pointer to implementation class.
   */
  const std::shared_ptr<MemoryImplBase>& get_pimpl_handle() const;

  /**
   * get_device_handle() - Retrieves the device handle associated with memory
   * allocation
   *
   * @return
   *  Returns Device handle
   */
  std::shared_ptr<Device> get_device_handle() const;

  /**
   * get_size() - gets the size of the allocated memory
   *
   * @return
   *  returns the memory size
   */
  size_t get_size();

  /**
   * get_physical_addr() - Retrieves the physical address of the
   *  allocated memory if memory type is XRT.
   *
   * @return
   *  returns the physical address
   */
  uint64_t get_physical_addr();

 private:
  std::shared_ptr<MemoryImplBase> pimpl;
};
}  // namespace vart
