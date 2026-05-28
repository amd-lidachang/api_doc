Framework Runner Wrappers
=========================

.. py:module:: vaiswRunnerCommon

These modules provide framework-agnostic wrappers that route ONNX, PyTorch, TensorFlow, and Caffe
inference requests through the VART NPU runtime. They are the recommended entry point when
integrating VART into existing ML framework pipelines.

.. py:class:: VaiswCommon(networkName=None)

   Base class for all framework runner wrappers. Manages initialization state, input/output
   registration, and data-type normalisation.

   :param networkName: Model session name. Reads from ``runSession.networkName`` in ``vaisw.ini``
                       if not given; defaults to ``"wrp_network"``.
   :type networkName: str, optional

   .. py:method:: convert_float32_or_uint8(value)

      Normalize an array-like value to its natural dtype (preserves ``int8``, ``uint8``,
      ``int32``, ``int64``; converts everything else to ``float32``).

      :param value: Input tensor or sequence.
      :returns: ``numpy.ndarray`` with appropriate dtype.

   .. py:method:: force_float32(vec)

      Convert every element of *vec* to ``float32``.

      :param vec: List of array-like objects.
      :returns: List of ``numpy.ndarray`` with dtype ``float32``.


.. py:module:: vaiswRunnerEmbedded

.. py:class:: VaiswEmbedded(**kwargs)

   Bases: :py:class:`~vaiswRunnerCommon.VaiswCommon`

   Embedded NPU runner that wraps :py:class:`~VART.Runner`. Instantiated once, then driven
   by successive :py:meth:`run` calls.

   .. py:method:: run(model, inputs, opset_version=None)

      Run NPU inference.

      :param model: Framework model object (used only to infer snapshot path on first call).
      :param inputs: Single ``numpy.ndarray`` or list of arrays.
      :param opset_version: Ignored; accepted for API compatibility.
      :returns: List of output ``numpy.ndarray``.


.. py:class:: ZOnnx(**kwargs)

   Bases: :py:class:`VaiswEmbedded`

   ONNX-specific embedded runner. Accepts both dict-keyed and list inputs.

   .. py:method:: run(model, inputs, onnxModel=None, **kwargs)

      :param model: ONNX ``ModelProto``.
      :param inputs: Dict mapping input name → array, or list of arrays.
      :param onnxModel: Alternate ONNX model; overrides *model* when provided.
      :returns: List of output ``numpy.ndarray``.


.. py:class:: ZTorch(**kwargs)

   Bases: :py:class:`VaiswEmbedded`

   PyTorch-specific embedded runner. Handles nested list/tuple output structures so that
   the return type matches the original ``torch.Tensor`` tree shape.

   .. py:method:: run(model, inputs, **kwargs)

      :param model: A ``torch.nn.Module``.
      :param inputs: List of input tensors or ``numpy.ndarray``.
      :returns: Outputs preserving the nested list/tuple structure of the original model.
