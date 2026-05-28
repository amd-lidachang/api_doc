Runner
======

.. py:module:: VART

.. py:class:: Runner(model_path, options={})

   Python binding for ``vart::VartMLRunner``. Provides the primary interface for loading a
   compiled model and executing NPU inference.

   Import via the ``VART`` convenience module:

   .. code-block:: python

      from VART import Runner

      runner = Runner("model.xmodel")

   :param model_path: Path to the compiled ``.xmodel`` snapshot file.
   :type model_path: str
   :param options: Optional configuration key-value pairs passed to the runtime.
   :type options: dict

   .. py:method:: get_model_name() -> str

      Return the name of the loaded model.

      :returns: Model name string.
      :rtype: str

   .. py:method:: get_tensors_info(direction, tensor_type) -> list[NpuTensorInfo]

      Retrieve metadata for all tensors in the given direction and type.

      :param direction: ``TensorDirection.INPUT`` or ``TensorDirection.OUTPUT``.
      :param tensor_type: ``TensorType.CPU`` or ``TensorType.HW``.
      :returns: List of :py:class:`NpuTensorInfo` objects.

   .. py:method:: get_tensor_info_by_name(tensor_name, tensor_type) -> NpuTensorInfo

      Retrieve metadata for a specific tensor by name.

      :param tensor_name: Name of the tensor.
      :type tensor_name: str
      :param tensor_type: ``TensorType.CPU`` or ``TensorType.HW``.
      :returns: :py:class:`NpuTensorInfo` for the named tensor.
      :raises RuntimeError: If the tensor name is not found.

   .. py:method:: get_num_input_tensors() -> int

      Return the number of input tensors the model expects.

      :rtype: int

   .. py:method:: get_num_output_tensors() -> int

      Return the number of output tensors the model produces.

      :rtype: int

   .. py:method:: get_batch_size() -> int

      Return the device batch size.

      :rtype: int

   .. py:method:: execute(inputs, outputs) -> StatusCode

      Run synchronous inference.

      :param inputs: List of lists of :py:class:`NpuTensor` — dimensions ``[batch][tensor]``.
      :param outputs: List of lists of :py:class:`NpuTensor` — filled in place.
      :returns: :py:class:`StatusCode` indicating success or failure.

      .. code-block:: python

         status = runner.execute(inputs, outputs)
         if status != StatusCode.SUCCESS:
             raise RuntimeError(f"Inference failed: {status}")

   .. py:method:: execute_async(inputs, outputs, callback=None) -> JobHandle

      Submit an asynchronous inference job.

      :param inputs: ``[batch][tensor]`` list of :py:class:`NpuTensor`.
      :param outputs: ``[batch][tensor]`` list of :py:class:`NpuTensor` (filled on completion).
      :param callback: Optional callable invoked with a :py:class:`JobHandle` on completion.
      :returns: :py:class:`JobHandle` for tracking the job.

   .. py:method:: wait(job_handle, timeout_ms) -> StatusCode

      Block until an asynchronous job completes or the timeout elapses.

      :param job_handle: Handle returned by :py:meth:`execute_async`.
      :param timeout_ms: Maximum wait in milliseconds. ``0`` checks and returns immediately.
      :type timeout_ms: int
      :returns: :py:class:`StatusCode`.

   .. py:method:: allocate_npu_tensor(info, mem_type=None, ddr_idx=0) -> NpuTensor

      Allocate a tensor buffer on the NPU.

      :param info: :py:class:`NpuTensorInfo` describing the tensor.
      :param mem_type: :py:class:`MemoryType` (defaults to ``XRT_BO`` for HW tensors).
      :param ddr_idx: DDR bank index. Defaults to ``0``.
      :returns: Allocated :py:class:`NpuTensor`.
      :raises RuntimeError: If allocation fails.

   .. py:method:: get_quant_parameters(tensor_name) -> QuantParameters

      Retrieve quantization parameters for a tensor.

      :param tensor_name: Name of the tensor.
      :type tensor_name: str
      :returns: :py:class:`QuantParameters` with scale, zero_point, and rounding_mode.


.. py:class:: StatusCode

   Enumerates inference status codes.

   .. py:attribute:: SUCCESS
   .. py:attribute:: FAILURE
   .. py:attribute:: INVALID_INPUT
   .. py:attribute:: INVALID_OUTPUT
   .. py:attribute:: OUT_OF_MEMORY
   .. py:attribute:: RUNTIME_ERROR
   .. py:attribute:: JOB_PENDING
   .. py:attribute:: INVALID_JOB_ID
   .. py:attribute:: RESOURCE_UNAVAILABLE


.. py:class:: JobHandle

   Handle returned by :py:meth:`Runner.execute_async`.

   .. py:attribute:: status
      :type: StatusCode

      Submission status of the job.

   .. py:attribute:: job_id
      :type: int

      Unique identifier. ``0`` is reserved as invalid; valid IDs start from ``1``.
