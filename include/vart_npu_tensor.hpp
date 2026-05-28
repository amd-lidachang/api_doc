/**
 * @file vart_npu_tensor.hpp
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

#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace vart
{

// Forward declaration of the private NpuTensor implementation
class NpuTensorPriv;

/**
 * @enum DataType
 * @brief Enumerates the supported data types for tensors in the VART API.
 *
 * This enum defines the various data types that can be used to represent tensor
 * elements. It includes integer and floating-point formats, as well as
 * specialized types such as BF16.
 *
 * - UNKNOWN:        Unknown data type.
 * - BOOLEAN:        Boolean type.
 * - INT8:           8-bit signed integer.
 * - UINT8:          8-bit unsigned integer.
 * - INT16:          16-bit signed integer.
 * - UINT16:         16-bit unsigned integer.
 * - BF16:           16-bit Brain Floating Point format.
 * - FP16:           16-bit floating point.
 * - INT32:          32-bit signed integer.
 * - UINT32:         32-bit unsigned integer.
 * - FLOAT32:        32-bit floating point.
 * - INT64:          64-bit signed integer.
 * - UINT64:         64-bit unsigned integer.
 */
enum class DataType
{
	UNKNOWN,
	BOOLEAN,
	INT8,
	UINT8,
	INT16,
	UINT16,
	BF16,
	FP16,
	INT32,
	UINT32,
	FLOAT32,
	INT64,
	UINT64,
};

/**
 * @enum MemoryLayout
 * @brief Enumerates the supported memory layouts for tensors in the VART API.
 *
 * This enum defines the various memory layouts that can be used to represent
 * tensor data. It includes formats such as NHWC, NCHW, and others that specify
 * how tensor dimensions are organized in memory.
 *
 * - UNKNOWN:       Unknown memory layout.
 * - NC:            Model batch, Channels (packed format).
 * - NCH:           Model batch, Channels (packed format), Height.
 * - NHC:           Model batch, Height, Channels (packed format).
 * - NHW:           Model batch, Height, Width.
 * - NWC:           Model batch, Width, Channels (packed format).
 * - NHWC:          Model batch, Height, Width, Channels (packed format).
 * - NCHW:          Model batch, Channels, Height, Width (planar format).
 * - NHWC4:         Model batch, Height, Width, Channel groups of 4 (e.g RGBA).
 * - NHWC8:         Model batch, Height, Width, Channel groups of 8.
 * - NC4HW4:        Model batch, Channels / 4, Height, Width, Channel groups of 4.
 * - NC8HW8:        Model batch, Channels / 8, Height, Width, Channel groups of 8.
 * - HCWNC4:        Height, Channels / 4, Width, N = 1, Channel groups of 4.
 * - HCWNC8:        Height, Channels / 8, Width, N = 1, Channel groups of 8.
 * - HCWNC16:       Height, Channels / 16, Width, N = 1, Channel groups of 16.
 * - NHW16C4WC:     Model batch, Height, Width / 16, Channels / 4, Width groups of 16, Channel groups of 4.
 * - NHW16WC4C:     Model batch, Height, Width / 16, Width groups of 16, Channels / 4, Channel groups of 4.
 * - GENERIC:       Generic layout. See NpuTensorInfo::memory_layout_order for more info.
 */
enum class MemoryLayout
{
	UNKNOWN,
	NC,
	NCH,
	NHC,
	NHW,
	NWC,
	NHWC,
	NCHW,
	NHWC4,
	NHWC8,
	NC4HW4,
	NC8HW8,
	HCWNC4,
	HCWNC8,
	HCWNC16,
	NHW16C4WC,
	NHW16WC4C,
	GENERIC,
};

/**
 * @enum MemoryType
 * @brief Enumerates the various memory types utilized for tensors in the VART API.
 *
 * This enumeration specifies the locations where tensor data is stored:
 * - UNKNOWN:               Memory type is not specified or recognized.
 * - XRT_BO:                Represents a buffer object associated with the XRT (Xilinx Runtime).
 * - DMA_FD:                Corresponds to a file descriptor used for Direct Memory Access (DMA).
 * - USER_POINTER_CMA:      Indicates a user-provided virtual pointer that points to a contiguous physical
 * block of memory.
 * - USER_POINTER_NON_CMA:  Indicates a user-provided virtual pointer that does not guarantee contiguous
 * memory allocation. This memory can be allocated using standard methods such as new, malloc, or calloc.
 */
enum class MemoryType
{
	UNKNOWN,
	XRT_BO,
	DMA_FD,
	USER_POINTER_CMA,
	USER_POINTER_NON_CMA,
};

/**
 * @enum TensorDirection
 * @brief Enumerates the supported tensor directions in the VART API.
 *
 * This enum defines the various directions that tensors can have in the context
 * of model inference. It includes input and output directions.
 *
 * - INPUT:         Input tensor direction.
 * - OUTPUT:        Output tensor direction.
 *
 */
enum class TensorDirection
{
	INPUT,
	OUTPUT
};

/**
 * @enum TensorType
 * @brief Specifies the tensor types supported in the VART API.
 *
 * Enumerates the available tensor types:
 * - CPU: Represents tensor metadata from the ONNX model, as defined for
 * standard CPU execution.
 * - HW:  Corresponds to AMD hardware-specific tensor metadata, formatted for
 * direct execution on AMD AI engines.
 *
 * @note AMD optimizes its AI engines with unique data formats and memory
 * layouts. As a result, the HW tensor layout and format will typically differ
 * from the CPU tensor representation defined by the ONNX model.
 */
enum class TensorType
{
	CPU,
	HW
};

/**
 * @struct NpuTensorInfo
 * @brief Metadata structure describing a tensor used in VART.
 *
 * Contains various attributes used to define and manage a tensor:
 *
 * @var NpuTensorInfo::name
 *   Name of the tensor.
 *
 * @var NpuTensorInfo::data_type
 *   Data type of the tensor elements.
 *
 * @var NpuTensorInfo::direction
 *   Direction of the tensor (input or output).
 *
 * @var NpuTensorInfo::tensor_type
 *   Type of the tensor (CPU or HW).
 *
 * @var NpuTensorInfo::memory_layout
 *   Memory layout type of the tensor.
 *
 * @var NpuTensorInfo::memory_layout_order
 *   (Optional) Only relevant when memory_layout is GENERIC. Specifies the
 * dimension permutation order for buffer data. This vector defines how
 * dimensions are arranged compared to the reference TensorType::CPU tensor
 * format. For example, if the TensorType::CPU format is "ABCD",
 * memory_layout_order is {0, 1, 2, 3}; if the TensorType::HW format is "ADBC",
 * memory_layout_order is {0, 3, 1, 2}.
 *
 * @var NpuTensorInfo::size
 *   Number of elements in the tensor.
 *
 * @var NpuTensorInfo::size_in_bytes
 *   Size of the tensor data in bytes.
 *
 * @var NpuTensorInfo::shape
 *   Dimensions of the tensor.
 *
 * @var NpuTensorInfo::strides
 *   Stride values for each dimension, specified in units of elements.
 *
 * @fn void NpuTensorInfo::print() const
 *   Prints tensor metadata to standard output.
 */
struct NpuTensorInfo
{
	std::string           name;
	DataType              data_type     = DataType::UNKNOWN;
	TensorDirection       direction     = TensorDirection::INPUT;
	TensorType            tensor_type   = TensorType::HW;
	MemoryLayout          memory_layout = MemoryLayout::UNKNOWN;
	std::vector<uint32_t> memory_layout_order;
	size_t                size          = 0;
	size_t                size_in_bytes = 0;
	std::vector<uint32_t> shape;
	std::vector<uint32_t> strides;

	void print() const;
};

/**
 * @brief This class represents a tensor in the VART API.
 *
 * This class encapsulates tensor metadata and offers access to the tensor's
 * data buffers. It acts as a lightweight wrapper around buffers supplied by the
 * user.
 *
 * @note: This class does not take ownership of the buffer memory.
 * The user is responsible for managing the buffer's lifecycle.
 */
class NpuTensor
{
  public:
	/**
	 * @brief Construct a NpuTensor from a user-supplied buffer.
	 *
	 * Initializes the tensor using the specified metadata and buffer.
	 *
	 * @param info      Tensor metadata (NpuTensorInfo).
	 * @param buffer    Pointer to the user buffer containing the tensor data.
	 *                  The buffer must remain valid for the lifetime of the NpuTensor object.
	 * @param mem_type  Specifies the memory type of the buffer.
	 *
	 * @note The NpuTensor does not take ownership of the buffer.
	 *       The caller is responsible for ensuring the buffer remains valid for the lifetime of this object.
	 * @throws std::runtime_error if the buffer is null, memory type is invalid, or tensor info validation
	 * fails.
	 */
	NpuTensor(const NpuTensorInfo& info, void* buffer, MemoryType mem_type);

	/**
	 * @brief Construct a NpuTensor from a user-supplied constant buffer.
	 *
	 * Initializes the tensor using the specified metadata and constant buffer.
	 *
	 * @param info      Tensor metadata (NpuTensorInfo).
	 * @param buffer    Pointer to the user constant buffer containing the tensor data.
	 * @param mem_type  Specifies the memory type of the buffer.
	 *
	 * @note The NpuTensor does not take ownership of the buffer.
	 *       The caller is responsible for ensuring the buffer remains valid for the lifetime of this object.
	 * @throws std::runtime_error if the buffer is null, memory type is invalid, or tensor info validation
	 * fails.
	 */
	NpuTensor(const NpuTensorInfo& info, const void* buffer, MemoryType mem_type);

	NpuTensor(); // Default constructor

	/**
	 * @brief Retrieves a pointer to the tensor's buffer.
	 *
	 * This function provides access to the buffer that was provided during tensor
	 * construction.
	 *
	 * @return void*  Pointer to the buffer, or nullptr if no buffer is available
	 * or if the tensor was constructed with a const buffer.
	 * If the memory type is MemoryType::XRT_BO,
	 * it returns a pointer to the corresponding xrt::bo. If the memory type is
	 * MemoryType::DMA_FD, it returns a pointer to the file descriptor. For
	 * MemoryType::USER_POINTER_CMA and MemoryType::USER_POINTER_NON_CMA,
	 * it returns the virtual pointer.
	 * @note Returns nullptr for tensors constructed with const void* buffer.
	 */
	void* get_buffer();

	/**
	 * @brief Retrieves a pointer to the tensor's buffer.
	 *
	 * This function is the overloaded version for immutable (const) access
	 *
	 * @return const void*  Pointer to the buffer, or nullptr if no buffer is available.
	 */
	const void* get_buffer() const;

	/**
	 * @brief Returns the virtual address of the tensor buffer.
	 *
	 * @return void*   Pointer to the virtual address of the buffer, or nullptr if
	 * no buffer is available or if the tensor was constructed with a const buffer.
	 *
	 * @note Virtual address retrieval is not supported for MemoryType::DMA_FD.
	 * @note Returns nullptr for tensors constructed with const void* buffer.
	 */
	void* get_virtual_address();

	/**
	 * @brief Returns the virtual address of the tensor buffer.
	 *
	 * This function is the overloaded version for immutable (const) access.
	 *
	 * @return const void*   Pointer to the virtual address of the buffer, or nullptr if
	 * no buffer is available.
	 *
	 * @note Virtual address retrieval is not supported for MemoryType::DMA_FD
	 */
	const void* get_virtual_address() const;

	/**
	 * @brief Returns the physical address of the tensor buffer.
	 *
	 * @return uint64_t   Physical address of the buffer if applicable, 0
	 * otherwise.
	 *
	 * @note Physical address retrieval is only supported for MemoryType::XRT_BO
	 */
	uint64_t get_physical_address() const;

	/**
	 * @brief Returns the NpuTensorInfo metadata of the tensor.
	 *
	 * This method returns the NpuTensorInfo object that contains metadata about
	 * the tensor, such as its name, shape, strides, data type, and memory layout.
	 * @return A constant reference to the NpuTensorInfo object.
	 */
	const NpuTensorInfo& get_info() const;

	/**
	 * @brief Get the memory type of the tensor.
	 *
	 * @return MemoryType The memory type of the tensor.
	 */
	MemoryType get_memory_type() const;

	/**
	 * @brief Synchronizes the tensor buffer between CPU and AIE.
	 *
	 * Ensures data consistency between CPU and AIE by performing cache operations
	 * based on the tensor's direction:
	 * - For TensorDirection::INPUT, flushes cache to DDR for reading by AIE.
	 * - For TensorDirection::OUTPUT, invalidates cache for reading by CPU.
	 *
	 * @return void
	 *
	 * @note Supported only for NpuTensors allocated using vart::Runner::allocate_npu_tensor.
	 */
	void sync_buffer() const;

	/**
	 * @brief Prints the metadata of the tensor.
	 *
	 * This method prints the NpuTensorInfo metadata, including name, shape,
	 * strides, data type, memory layout, and size. It is useful for debugging and
	 * understanding the tensor's properties.
	 */
	void print_info() const;

  private:
	friend class NpuTensorPrivAccess;     // Allow controlled access to the private implementation
	std::shared_ptr<NpuTensorPriv> priv_; // NpuTensor private implementation
};

} // namespace vart
