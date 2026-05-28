vart_ml.lib.python.vaiswRunnerEmbedded
======================================

.. py:class:: VaiswEmbedded(vaiswRunnerCommon.VaiswCommon)

   .. py:method:: _initialize(_model, _inputs)

      :param _model:
      :param _inputs:

   .. py:method:: run(model, inputs, _opset_version = None)

      :param model:
      :param inputs:
      :param _opset_version:

.. py:class:: ZOnnx(VaiswEmbedded)

   .. py:method:: run(model, inputs, onnxModel = None, **kwargs)

      :param model:
      :param inputs:
      :param onnxModel:
      :param kwargs:

.. py:class:: ZTorch(VaiswEmbedded)

   .. py:method:: _compute_outputs_format(torch_outputs, index_output: int) -> Tuple[Union[list, int], int]

      Recursive function which computes an outputs_fomat from a torch output
      It replaces every torch.Tensor by a unique index_output
      
      Example of torch_outputs:  [out0, [out1, out2 ,out3]]
      Example of outputs_format: [0, [1, 2, 3]]

      :param torch_outputs:
      :param int index_output:
      :rtype: Tuple[Union[list, int], int]

   .. py:method:: _apply_preproc_if_set(t, preproc_transform)

      :param t:
      :param preproc_transform:

   .. py:method:: _set_outputs_format(pytorchModel, torch_inputs, call_kwargs)

      Set the outputs_format with the output of the pytorch model

      :param pytorchModel:
      :param torch_inputs:
      :param call_kwargs:

   .. py:method:: _fill_outputs_format_with_iriz_outputs(outputs_format: List[Union[list, int]], iriz_outputs: list)

      Recursive function which creates a new_outputs from iriz_outputs and outputs_fomat
      It replaces every index from outputs_format by the output from iriz_outputs
      
      Example of outputs_format: [0,[1,2,3]]
      Example of iriz_outputs:   [out0, out1, out2, out3]
      Example of new_outputs:    [out0, [out1, out2, out3]]

      :param List[Union[list, int]] outputs_format:
      :param list iriz_outputs:

   .. py:method:: run(model, inputs, torchInput = True, torchOutput = True, call_kwargs = None, **kwargs)

      :param model:
      :param inputs:
      :param torchInput:
      :param torchOutput:
      :param call_kwargs:
      :param kwargs:

.. py:class:: ZTensorflow(VaiswEmbedded)

   .. py:method:: run(model, inputs, fetches = None, **kwargs)

      :param model:
      :param inputs:
      :param fetches:
      :param kwargs:

.. py:class:: ZKeras(ZTensorflow)

   .. py:method:: run(model, inputs, **kwargs)

      :param model:
      :param inputs:
      :param kwargs:

