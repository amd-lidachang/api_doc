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
#include <functional>
#include <memory>
#include <vector>
#include "vart_inferresult_types.hpp"

namespace vart {

class InferResultImplBase;

/*!
 * This module is used to represent inference results. Presently, the default
 * supported types include classification and detection. Users can integrate
 * new types by overriding base class methods to incorporate custom inference
 * results. For additional information please check API documentation.
 */

class InferResult : public std::enable_shared_from_this<InferResult> {
 public:
  InferResult() = delete;

  /**
   * InferResult() - Constructor for using supported infer result type
   * implementations
   *
   * @param infer_res_type
   *  Enum class to specify which implementation to instantiate
   *
   */
  InferResult(InferResultType infer_res_type);

  /**
   * InferResult() - Constructor for using user defined implementation
   *
   * @param ptr
   *  Pointer to user's implementation instance
   *
   */
  InferResult(std::shared_ptr<InferResultImplBase> ptr);

  /**
   * get_pimpl_handle() - Gives pointer to implementation class.
   *
   * @return
   *  Returns a constant reference of pointer to implementation class.
   */
  const std::shared_ptr<InferResultImplBase>& get_pimpl_handle() const;

  /**
   * transform() - Scales the infer results by a given scale factor
   *
   * @param info
   *  Scale factor info with which infer results to be scaled.
   *
   * Typically, in video pipelines, the original input resolution differs from
   * the resolution of the input to the machine learning model.
   * If we have inference results, like detection from may be 200x200 resolution
   * (input resolution to ML model) and if we want to transform the bounding box results
   * to the original input resolution, which may be 1920x1080.
   * In such cases, one can use this function to transform the bounding box
   * dimensions in the infer results to the resolution of input image.
   */
  void transform(InferResScaleInfo& info);

  /**
   * get_infer_result() - Get inference results for a frame.
   *
   * @return
   *  Inference result object for the requested frame.
   */
  InferResultData* get_infer_result();

  /**
   * add_child() - Add a child to this infer result node.
   *
   * @param child
   *  Child node to be added
   *
   * User can use this method to build cascade infer result tree by
   * adding child nodes to the previous inference level starting
   * with a dummy root node.
   */
  void add_child(std::shared_ptr<InferResult> child);

  /**
   * add_children() - Add all children at once.
   *
   * @param arg_children
   *  Child nodes to be added
   *
   * User can use this method to add all children at once.
   */
  void add_children(std::vector<std::shared_ptr<InferResult>> arg_children);

  /**
   * get_children() - Returns all children of the node.
   *
   * @return
   *  vector of child nodes.
   */
  std::vector<std::shared_ptr<InferResult>> get_children();

  /**
   * get_parent() - Returns parent of the given inference result node.
   *
   * @return
   *  Parent result node.
   */
  std::shared_ptr<InferResult> get_parent();

  /**
   * get_root() - Returns root of the given inference result node.
   *
   * @return
   *  Root result node.
   */
  std::shared_ptr<InferResult> get_root();

  /**
   * traverse() - Traverse through the tree nodes in a given order.
   *
   * @param callback
   *  User callback function to be called for each node as per the order chosen.
   *
   * @param order
   *  Order in which the tree nodes to be traversed.
   *
   * @param user_data
   *  User data to be passed to the callback function.
   *
   */
  void traverse(
      const std::function<void(std::shared_ptr<InferResult>, void*)>& callback,
      TraversalOrder order,
      void* user_data);

  /**
   * get_depth() - Returns depth of the current node
   *
   * @return
   *  Depth of the current node.
   */
  size_t get_depth();

 private:
  std::shared_ptr<InferResultImplBase> pimpl;
  std::weak_ptr<InferResult> parent;
  std::vector<std::shared_ptr<InferResult>> children;
};

}  // namespace vart
