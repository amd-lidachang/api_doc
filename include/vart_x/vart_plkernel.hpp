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

#include "base/vart_plkernel_impl_base.hpp"
#include "vart_device.hpp"
#include "vart_plkernel_types.hpp"
#include <any>
#include <memory>
#include <string>
#include <utility>
#include <vector>
#include <chrono>

namespace vart {

class PLKernelImplBase;

class PLKernel {
public:
  /**
   * PLKernel() - Constructs a PLKernel object.
   *
   * @param type
   *  The type of the kernel implementation.
   * @param kernel_name
   *  The name of the kernel.
   * @param json_data
   *  The JSON data for the kernel configuration.
   * @param device
   *  The device on which the kernel will run.
   */
  PLKernel(PLKernelImplType type, const std::string &kernel_name,
           std::string &json_data, std::shared_ptr<Device> device);

  /**
   * PLKernel() - Constructs a PLKernel object with a given implementation
   * pointer.
   * @param ptr
   *  A shared pointer to the kernel implementation.
   */
  PLKernel(std::shared_ptr<PLKernelImplBase> ptr);

  /**
   * ~PLKernel() - Destructs a PLKernel object
   */
  ~PLKernel();

  /**
   * get_pimpl_handle() - Gives pointer to implementation class.
   *
   * @return
   *  Returns a constant reference of pointer to implementation class.
   */
  const std::shared_ptr<PLKernelImplBase> &get_pimpl_handle() const;

  /**
   * Process() - Set and process the given arguments on Kernel.
   * @tparam Args
   *  Variadic template arguments
   * @param args
   * 	 Arguments to be processed. Arguments specified to program as
   *   kernel arguments in sequence.
   */
  template <typename... Args> void process(Args &&... args) {
    try {
      std::vector<std::any> any_args = {std::forward<Args>(args)...};
      if (enable_profiling) {
        profile_start_time.push_back(std::chrono::high_resolution_clock::now());
      }
      pimpl->process(any_args);
    } catch (...) {
      /* Rethrow the caught exception */
      throw;
    }
  }

  /**
   * wait() - Waits for the kernel to complete processing.
   *
   * @param timeout
   *  The timeout value in milliseconds.
   * @return
   *   An integer indicating the status.
   */
  int wait(unsigned int timeout);

  /**
   * set_config() - Sets the configuration for the kernel.
   *
   * @tparam PLKernelAnyInfo
   *  The type of the configuration information.
   * @param info
   *  The configuration information.
   */
  template <typename PLKernelAnyInfo> void set_config(PLKernelAnyInfo &info) {
    pimpl->set_config(info);
  }

  /**
   * get_config() - Gets the configuration of the kernel.
   *
   * @tparam PLKernelAnyInfo
   *  The type of the configuration information.
   * @param info
   *  The configuration information.
   */
  template <typename PLKernelAnyInfo> void get_config(PLKernelAnyInfo &info) {
    std::any any_info = info;
    pimpl->get_config_impl(any_info);
    info = std::any_cast<PLKernelAnyInfo>(any_info);
  }

private:
  std::shared_ptr<PLKernelImplBase> pimpl;
  bool enable_profiling = false;
  std::vector<std::chrono::high_resolution_clock::time_point> profile_start_time;
  std::vector<std::chrono::high_resolution_clock::time_point> profile_end_time;
};

} // namespace vart
