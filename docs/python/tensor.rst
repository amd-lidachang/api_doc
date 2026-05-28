Tensors
=======

.. py:module:: vart_ml

.. py:class:: NpuTensor(info, buffer, mem_type)

   Wraps a user-supplied buffer as an NPU tensor. Does **not** take ownership of the buffer —
   the caller must keep the buffer alive for the lifetime of this object.

   :param info: Tensor metadata (:py:class:`NpuTensorInfo`).
   :param buffer: Raw buffer pointer or compatible Python buffer object.
   :param mem_type: :py:class:`MemoryType` of the buffer.
   :raises RuntimeError: If the buffer is null, mem_type is invalid, or info validation fails.

   .. py:method:: get_buffer() -> memoryview

      Return a view of the tensor data buffer.

   .. py:method:: get_virtual_address() -> int

      Return the virtual address of the buffer as an integer. Not supported for ``DMA_FD``.

   .. py:method:: get_physical_address() -> int

      Return the physical address. Only supported for ``XRT_BO`` memory type.

   .. py:method:: get_info() -> NpuTensorInfo

      Return the tensor metadata.

   .. py:method:: get_memory_type() -> MemoryType

      Return the memory type of this tensor.

   .. py:method:: sync_buffer()

      Synchronize the tensor buffer between CPU and AIE:

      - **INPUT** direction: flush CPU cache to DDR so the AIE can read it.
      - **OUTPUT** direction: invalidate CPU cache so the CPU reads fresh AIE output.

      Only supported for tensors allocated via :py:meth:`Runner.allocate_npu_tensor`.

   .. py:method:: print_info()

      Print tensor metadata (name, shape, strides, data type, layout, size) to stdout.


.. py:class:: NpuTensorInfo

   Metadata struct describing a tensor.

   .. py:attribute:: name
      :type: str

      Tensor name as defined in the model.

   .. py:attribute:: data_type
      :type: DataType

   .. py:attribute:: direction
      :type: TensorDirection

   .. py:attribute:: tensor_type
      :type: TensorType

   .. py:attribute:: memory_layout
      :type: MemoryLayout

   .. py:attribute:: shape
      :type: list[int]

      Dimension sizes.

   .. py:attribute:: strides
      :type: list[int]

      Per-dimension stride in elements.

   .. py:attribute:: size
      :type: int

      Total number of elements.

   .. py:attribute:: size_in_bytes
      :type: int

      Total buffer size in bytes.

   .. py:method:: print()

      Print tensor metadata to stdout.


.. py:class:: DataType

   Supported element data types.

   .. py:attribute:: UNKNOWN
   .. py:attribute:: BOOLEAN
   .. py:attribute:: INT8
   .. py:attribute:: UINT8
   .. py:attribute:: INT16
   .. py:attribute:: UINT16
   .. py:attribute:: BF16
   .. py:attribute:: FP16
   .. py:attribute:: INT32
   .. py:attribute:: UINT32
   .. py:attribute:: FLOAT32
   .. py:attribute:: INT64
   .. py:attribute:: UINT64


.. py:class:: MemoryLayout

   Tensor memory layout formats.

   .. py:attribute:: NHWC
   .. py:attribute:: NCHW
   .. py:attribute:: NC
   .. py:attribute:: NHWC4
   .. py:attribute:: NHWC8
   .. py:attribute:: NC4HW4
   .. py:attribute:: NC8HW8
   .. py:attribute:: GENERIC

      Generic layout; see ``NpuTensorInfo.memory_layout_order`` for the dimension permutation.

   *(Additional layouts: NCH, NHC, NHW, NWC, HCWNC4, HCWNC8, HCWNC16, NHW16C4WC, NHW16WC4C)*


.. py:class:: MemoryType

   Buffer memory type.

   .. py:attribute:: XRT_BO

      XRT Buffer Object — allocated by the XRT runtime, suitable for zero-copy NPU access.

   .. py:attribute:: DMA_FD

      DMA file descriptor.

   .. py:attribute:: USER_POINTER_CMA

      User-provided virtual pointer to physically contiguous (CMA) memory.

   .. py:attribute:: USER_POINTER_NON_CMA

      User-provided virtual pointer to non-contiguous memory (new/malloc/calloc).


.. py:class:: TensorDirection

   .. py:attribute:: INPUT
   .. py:attribute:: OUTPUT


.. py:class:: TensorType

   .. py:attribute:: CPU

      CPU-facing tensor format as defined by the ONNX model.

   .. py:attribute:: HW

      AMD hardware-specific tensor format, optimized for AI engine execution.
      Layout and format will typically differ from the CPU representation.


.. py:class:: QuantParameters

   Quantization parameters for a tensor.

   .. py:attribute:: scale
      :type: float

   .. py:attribute:: zero_point
      :type: int

   .. py:attribute:: rounding_mode
      :type: RoundingMode


.. py:class:: RoundingMode

   .. py:attribute:: UNKNOWN
   .. py:attribute:: ROUND_TO_NEAREST_EVEN
   .. py:attribute:: ROUND_TOWARD_ZERO
