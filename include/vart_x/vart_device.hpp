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

#ifndef VART_DEVICE_HPP
#define VART_DEVICE_HPP

#include <memory>

namespace vart {

class DeviceImplBase;

/*!
 * This module manages the hardware context and loading of xclbin on to the
 * device.  Please check API documentation for more information. Any module
 * utilizing hardware acceleration requires an instance of the Device class.
 */

class Device {
 public:
  /**
   * get_device_hdl() - Creates a Device() instance if not created earlier,
   *   else return an existing instance for given device index and xclbin.
   *
   * @param dev_idx
   *  Device index on which XCLBIN is to be loaded.
   *
   * @param xclbin_loc
   *  XCLBIN path.
   *
   * @return
   *  Returns a Device pointer created using given dev_idx, xclbin_loc
   *
   * The following criteria is the basis for either to create a new Device
   * instance or not:
   *
   * ~~~
   * ------------------------------------------------------------
   * | dev_idx    | xclbin |   Result                           |
   * ------------------------------------------------------------
   * | Exists     | Exists | Returns an existing Device instance|
   * | new        | new    | creates a new Device instance      |
   * | Exists     | new    | Returns error                      |
   * | new        | Exists | creates a new Device instance      |
   * ------------------------------------------------------------
   * ~~~
   */
  static std::shared_ptr<Device> get_device_hdl(const int32_t dev_idx,
                                                const std::string& xclbin_loc);

  /** get_pimpl_handle() - Retrieves pointer to Device implementation
   *  Base class
   *
   * @return
   *  Returns a constant reference of pointer to implementation class.
   */
  const std::shared_ptr<DeviceImplBase>& get_pimpl_handle() const;

  /**
   * get_device_index() - Retrieves device index of current instance
   *
   * @return
   *  Returns the device index
   */
  int32_t get_device_index() const;
  Device() = delete;
  ~Device() = default;

 private:
  Device(std::shared_ptr<DeviceImplBase> pimpl_hdl);
  std::shared_ptr<DeviceImplBase> pimpl;
};

}  // namespace vart
#endif  // VART_DEVICE_HPP
