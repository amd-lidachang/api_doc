/**
 * @file vart_runner_factory.hpp
 *
 * @copyright Copyright 2025 Advanced Micro Devices Inc.
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

#include <any>
#include <chrono>
#include <cstdint>
#include <functional>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "vart_npu_tensor.hpp"

namespace vart
{

/**
 * @enum RunnerType
 * @brief Enumerates the types of runner implementations supported.
 *
 * This enumeration specifies the different runner types available for model
 * inference. RunnerType identifies the backend or solution used to execute the
 * model.
 *
 * - VAIML:   VAIML-based runner implementation.
 */
enum class RunnerType
{
	VAIML
};

/**
 * @enum RoundingMode
 * @brief Enumerates the rounding modes used in quantization.
 *
 * This enum defines the different rounding modes that can be applied during
 * quantization, such as rounding to nearest even or truncating towards zero.
 *
 * - UNKNOWN:               Unknown rounding mode.
 * - ROUND_TO_NEAREST_EVEN: Round to nearest even value.
 * - ROUND_TOWARD_ZERO:     Truncate towards zero (no rounding).
 */
enum class RoundingMode
{
	UNKNOWN,
	ROUND_TO_NEAREST_EVEN,
	ROUND_TOWARD_ZERO,
};

/**
 * @struct QuantParameters
 * @brief Struct representing quantization parameters for a tensor.
 *
 * This struct holds the quantization parameters such as scale factor, zero
 * point, and rounding mode used for quantizing tensors in the VART.
 *
 * @var QuantParameters::scale
 *   Scale factor for quantization.
 * @var QuantParameters::zero_point
 *   Optional zero point for asymmetric quantization. Optional.
 * @var QuantParameters::rounding_mode
 *   Rounding mode used during quantization. Optional.
 */
struct QuantParameters
{
	double       scale         = 0.0;
	int32_t      zero_point    = 0;
	RoundingMode rounding_mode = RoundingMode::UNKNOWN;
};

/**
 * @enum StatusCode
 * @brief Enumerates the status codes used in the VART.
 *
 * This enum defines the various status codes that can be returned by VART
 * functions, indicating the success or failure of an operation.
 *
 * - SUCCESS:             Operation completed successfully.
 * - FAILURE:             Operation failed.
 * - INVALID_INPUT:       Invalid input parameters.
 * - INVALID_OUTPUT:      Invalid output parameters.
 * - OUT_OF_MEMORY:       Memory allocation failed.
 * - RUNTIME_ERROR:       Runtime error occurred.
 * - JOB_PENDING:         Job is still pending.
 * - INVALID_JOB_ID:      Provided job ID is invalid.
 * - RESOURCE_UNAVAILABLE: Required resource is unavailable.
 */
enum class StatusCode
{
	SUCCESS = 0,
	FAILURE,
	INVALID_INPUT,
	INVALID_OUTPUT,
	OUT_OF_MEMORY,
	RUNTIME_ERROR,
	JOB_PENDING,
	INVALID_JOB_ID,
	RESOURCE_UNAVAILABLE
};

/**
 * @struct JobHandle
 * @brief Struct representing a job handle for asynchronous execution.
 *
 * This struct holds the status of a submitted job, including whether it was
 * successfully submitted and its unique identifier.
 *
 * @var JobHandle::status
 *   Status of the submitted job.
 * @var JobHandle::job_id
 *   Unique identifier for the job. A value of 0 is reserved as invalid;
 *   valid job IDs start from 1.
 */
struct JobHandle
{
	StatusCode status; // Submission status of the job.
	uint32_t   job_id; // Unique identifier for the job.

	JobHandle(StatusCode stat, uint32_t id) : status(stat), job_id(id) {}

	JobHandle() : status(StatusCode::FAILURE), job_id(0) {}
};

/**
 * @class Runner
 * @brief Abstract base class for executing model inference operations.
 *
 * The Runner class defines a unified interface for running synchronous and
 * asynchronous inference tasks on machine learning models. It provides methods
 * for retrieving tensor metadata, executing computations, and managing
 * asynchronous job execution.
 *
 * Key Features:
 * - Query input and output tensor information, including support for zero-copy
 * operations.
 * - Perform synchronous inference with input and output tensors.
 * - Submit asynchronous inference jobs and manage their lifecycle via job
 * handles or callbacks.
 * - Support for both polling/waiting and callback-based asynchronous execution
 * models.
 *
 */
class Runner
{
  protected:
	/**
	 * @brief Constructs a Runner object with the specified model path and
	 * options.
	 *
	 * @param model_path The file path to the model to be used by the Runner.
	 * @param options Optional configuration parameters for the Runner, provided
	 * as a map of string keys to values of any type.
	 * @throws std::runtime_error if Runner initialization fails.
	 */
	explicit Runner(const std::string&                               model_path,
	                const std::unordered_map<std::string, std::any>& options = {})
	{
		(void)model_path;
		(void)options;
	}

  public:
	/**
	 * @brief Destroys the Runner object.
	 */
	virtual ~Runner() = default;

	/**
	 * @brief Return the model name.
	 *
	 * @return Model name.
	 */
	virtual const std::string& get_model_name(void) const = 0;

	/**
	 * @brief Unified API to retrieve tensor information based on direction and
	 * tensor type (CPU/HW).
	 *
	 * This method retrieves tensor information based on the specified direction
	 * (input/output) and tensor type (CPU/HW).
	 *
	 * @param direction Specifies whether to retrieve input or output tensor
	 * information.
	 * @param type Specifies whether to retrieve CPU or HW tensor information.
	 * @return A constant reference to a vector containing NpuTensorInfo objects,
	 *         each describing a tensor matching the specified criteria.
	 */
	virtual const std::vector<NpuTensorInfo>& get_tensors_info(TensorDirection direction,
	                                                           TensorType      type) const = 0;

	/**
	 * @brief Unified API to retrieve tensor information by name and tensor type
	 * (CPU/HW).
	 *
	 * This method retrieves tensor information for a specific tensor identified
	 * by name, with the ability to specify whether to retrieve CPU or HW tensor
	 * information.
	 *
	 * @param tensor_name The name of the tensor for which to retrieve
	 * information.
	 * @param type Specifies whether to retrieve CPU or HW tensor information.
	 * @return A constant reference to the NpuTensorInfo object describing the
	 * specified tensor.
	 * @throws std::runtime_error if the tensor name is not found.
	 */
	virtual const NpuTensorInfo& get_tensor_info_by_name(const std::string& tensor_name,
	                                                     TensorType         type) const = 0;

	/**
	 * @brief Retrieves the quantization parameters for a specific tensor.
	 *
	 * This method retrieves the quantization parameters for a tensor identified
	 * by its name.
	 *
	 * @param tensor_name The name of the tensor for which to retrieve
	 * quantization parameters.
	 * @return A QuantParameters object containing the scale factor and optional
	 * zero point.
	 * @throws std::runtime_error if quantization parameters are not found for the tensor.
	 */
	virtual const QuantParameters& get_quant_parameters(const std::string& tensor_name) const = 0;

	/**
	 * @brief Returns the number of input tensors.
	 *
	 * This method retrieves the number of input tensors required by the model or
	 * operation.
	 *
	 * @return The number of input tensors.
	 */
	virtual size_t get_num_input_tensors() const = 0;

	/**
	 * @brief Returns the number of output tensors.
	 *
	 * This method retrieves the number of output tensors produced by the model or
	 * operation.
	 *
	 * @return The number of output tensors.
	 */
	virtual size_t get_num_output_tensors() const = 0;

	/**
	 * @brief Returns the device batch size.
	 *
	 * This method retrieves the device batch size for the model or operation.
	 *
	 * @return The device batch size.
	 */
	virtual size_t get_batch_size() const = 0;

	/**
	 * @brief Executes the main computation using the provided input tensors and
	 * produces output tensors.
	 *
	 * This method is responsible for performing the actual inference or
	 * computation using the specified input tensors and generating the
	 * corresponding output tensors.
	 *
	 * @param inputs A constant reference to a vector of input NpuTensor objects,
	 * vector dimensions: [batch][tensors].
	 * @param outputs A reference to a vector of NpuTensor objects where the
	 * outputs will be stored, vector dimensions: [batch][tensors].
	 * @return A StatusCode indicating the success or failure of the execution.
	 * @note Users should provide tensors in the same order as returned by
	 * get_tensors_info().
	 */
	virtual StatusCode execute(const std::vector<std::vector<NpuTensor>>& inputs,
	                           std::vector<std::vector<NpuTensor>>&       outputs) noexcept = 0;

	/**
	 * @brief Executes the job asynchronously with the given input tensors.
	 *
	 * This method initiates an asynchronous operation using the provided input
	 * tensors, and stores the results in the output tensors. The function returns
	 * a handle to the asynchronous job, allowing the caller to track or manage
	 * its execution.
	 *
	 * @param inputs A constant reference to a vector of input tensors required
	 * for the job, vector dimensions: [batch][tensors].
	 * @param outputs A reference to a vector where the output tensors will be
	 * stored upon completion, vector dimensions: [batch][tensors].
	 * @return JobHandle A handle representing the asynchronous job.
	 * @note Users should provide tensors in the same order as returned by
	 * get_tensors_info(). inputs and outputs must remain valid until the job is completed.
	 */
	virtual JobHandle execute_async(const std::vector<std::vector<NpuTensor>>& inputs,
	                                std::vector<std::vector<NpuTensor>>&       outputs) noexcept = 0;

	/**
	 * @brief Waits for the completion of an asynchronous job.
	 *
	 * This method is used to check the status of job submitted using
	 * execute_async and blocks until the specified job is completed or the
	 * timeout expires.
	 *
	 * @param job_handle A constant reference to the handle of the job to wait
	 * for.
	 * @param timeout The maximum time to wait for job completion.
	 * Zero timeout means the wait should check the job completion status and
	 * return immediately. If a positive timeout is specified, the wait will
	 * return once the task is completed, or the specified time has elapsed.
	 * @return StatusCode The status of the wait operation.
	 */
	virtual StatusCode wait(const JobHandle& job_handle, std::chrono::milliseconds timeout) noexcept = 0;

	/**
	 * @typedef ExecuteAsyncCallback
	 * @brief Type alias for the callback function used in asynchronous execution operations.
	 *
	 * This callback function is invoked when an asynchronous operation completes.
	 * The callback receives the job handle containing the completion status.
	 *
	 * @param job_handle The handle of the completed asynchronous job, containing
	 *                   the final status and job identifier.
	 *
	 * @note The callback may be invoked from an internal worker thread, so users
	 *       must ensure thread safety when accessing shared resources.
	 */
	using ExecuteAsyncCallback = std::function<void(const JobHandle&)>;

	/**
	 * @brief Executes the operation asynchronously with the given input tensors.
	 *
	 * This method starts the asynchronous execution of the operation using the
	 * provided input tensors. The results will be stored in the output tensors,
	 * and the specified callback will be invoked upon completion.
	 *
	 * @note The callback may be invoked from an internal worker thread, not
	 * necessarily the calling thread. Users are responsible for ensuring thread
	 * safety when accessing shared resources in the callback.
	 *
	 * @param inputs A vector of input tensors to be processed, vector dimensions:
	 * [batch][tensors].
	 * @param outputs A reference to a vector where the output tensors will be
	 * stored, vector dimensions: [batch][tensors].
	 * @param cb A callback function to be called when the asynchronous execution
	 * is complete.
	 * @return JobHandle JobHandle for the submitted asynchronous job.
	 * @note Users should provide tensors in the same order as returned by
	 * get_tensors_info(). inputs and outputs must be valid until the callback is invoked.
	 */
	virtual JobHandle execute_async(const std::vector<std::vector<NpuTensor>>& inputs,
	                                std::vector<std::vector<NpuTensor>>&       outputs,
	                                ExecuteAsyncCallback                       cb) noexcept = 0;

	/**
	 * @brief Allocates memory for an NPU tensor.
	 *
	 * This API allocates contiguous tensor memory specifically for
	 * MemoryType::XRT_BO (i.e., an XRT Buffer Object), but only when the
	 * TensorType is set to HW.
	 *
	 * @param info     The metadata associated with the tensor.
	 * @return NpuTensor The allocated NPU tensor.
	 * @throws std::runtime_error if tensor allocation fails.
	 * @throws std::invalid_argument if the provided NpuTensorInfo is invalid.
	 */
	virtual NpuTensor allocate_npu_tensor(const NpuTensorInfo& info) const = 0;

	/**
	 * @brief Allocates memory for an NPU tensor.
	 *
	 * This API allocates contiguous tensor memory.
	 *
	 * @param info     The metadata associated with the tensor.
	 * @param mem_type Specifies the memory type of the buffer.
	 * @param ddr_idx  Select the DDR in which the buffer will be allocated.
	 * @return NpuTensor The allocated NPU tensor.
	 * @throws std::runtime_error if tensor allocation fails.
	 * @throws std::invalid_argument if the provided NpuTensorInfo is invalid.
	 */
	virtual NpuTensor
	allocate_npu_tensor(const NpuTensorInfo& info, MemoryType mem_type, size_t ddr_idx = 0) const = 0;

	/**
	 * @brief Creates a sub-tensor from a parent tensor with the specified metadata and offset.
	 *
	 * @param parent The parent tensor from which the sub-tensor will be created.
	 * @param info The metadata for the sub-tensor.
	 * @param offset The offset within the parent tensor where the sub-tensor starts.
	 * @return NpuTensor The created sub-tensor.
	 * @throws std::runtime_error if sub-tensor creation fails.
	 * @throws std::invalid_argument if the provided arguments are invalid.
	 * @note
	 * **Requirements:**
	 * - Sub-tensors can only be created from parent tensors allocated via `allocate_npu_tensor`.
	 * - The parent tensor must be large enough to contain the sub-tensor at the specified offset.
	 * - The offset and size in `info` must not exceed the parent tensor's buffer bounds.
	 * - Sub-tensors cannot be created from other sub-tensors (only one level of nesting is supported).
	 *
	 * **Memory Management:**
	 * - A sub-tensor is created from a parent tensor as a view at a specified offset.
	 * - Creating a sub-tensor does not allocate new memory; it reuses a portion of the parent tensor's
	 * memory.
	 * - Parent memory/buffer is released only after the parent tensor and all derived sub-tensors are
	 * destroyed.
	 * - Destroying only the parent tensor does not release the underlying memory while any sub-tensor is
	 * still alive.
	 */
	virtual NpuTensor
	allocate_sub_tensor(const NpuTensor& parent, const NpuTensorInfo& info, size_t offset) const = 0;

	/**
	 * @brief Return the number of DDR used bu the NPU.
	 *
	 * @return Number of DDR.
	 *
	 */
	virtual uint8_t get_nb_ddrs(void) const = 0;
};
/**
 * @class RunnerFactory
 * @brief Factory class for creating Runner instances.
 *
 * Provides a static method to instantiate Runner objects based on the specified
 * runner type, model path, and optional configuration options.
 */
class RunnerFactory
{
  public:
	/**
	 * @brief Creates and returns a shared pointer to a Runner instance.
	 *
	 * This static method initializes a Runner object for the specified runner
	 * type, using the provided model path and optional configuration options.
	 *
	 * @param runner_type The type of runner to create (e.g., VAIML).
	 * @param model_path The file system path to the model to be loaded by the
	 * Runner.
	 * @param options An optional map of additional configuration options, where
	 * each option is identified by a string key and can hold a value of any type.
	 * @return std::shared_ptr<Runner> A shared pointer to the created Runner
	 * instance.
	 * @throws std::runtime_error if the runner type is unsupported or creation fails.
	 */
	static std::shared_ptr<Runner>
	create_runner(RunnerType                                       runner_type,
	              const std::string&                               model_path,
	              const std::unordered_map<std::string, std::any>& options = {});
};

} // namespace vart
