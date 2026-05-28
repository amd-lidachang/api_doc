vart_ml.demo.vart_ml_runner
===========================

.. py:function:: get_formats_from_snapshot(path)

   :param path:

.. py:function:: data_to_numpy(data)

   :param data:

.. py:function:: dump_outputs(path, data, name)

   :param path:
   :param data:
   :param name:

.. py:function:: transform_input_data(data, dest_data_format, shape_format)

   :param data:
   :param dest_data_format:
   :param shape_format:

.. py:function:: copy_to_ddr(dst, src)

   :param dst:
   :param src:

.. py:function:: load_ios(args, inputs_types, input_format, input_shape_formats)

   Load and read inputs/outputs numpy archives

   :param args:
   :param inputs_types:
   :param input_format:
   :param input_shape_formats:

.. py:function:: gen_rand_inputs(runners, input_format)

   Generate 10 random batches of inputs for the given runners

   :param runners:
   :param input_format:

.. py:function:: quantize_tensor(tensor, nat_dtype, coeff)

   Quantize a single tensor

   :param tensor:
   :param nat_dtype:
   :param coeff:

.. py:function:: reorder_tensor(tensor, from_layout, to_layout, to_shape = ())

   Reorder a single tensor

   :param tensor:
   :param from_layout:
   :param to_layout:
   :param to_shape:

.. py:function:: process_input(args, runners, inputs, input_shape_formats, ddr_bufs = None)

   Process input to native / zero copy format.

   :param args:
   :param runners:
   :param inputs:
   :param input_shape_formats:
   :param ddr_bufs:

.. py:function:: get_channel_idx(layout)

   Get channel index in shape from layout.

   :param layout:

.. py:function:: process_output(args, runner, outputs, output_shape_formats, output_shapes)

   Process vart_ml_runner output to snapshot format.
   
       Must be called on native / zero_copy outputs.

   :param args:
   :param runner:
   :param outputs:
   :param output_shape_formats:
   :param output_shapes:

.. py:function:: stability_test(args, runners, batch_idx, inputs, ref_outputs, stab_test_errors)

   Rerun the model n times to ensure it is stable.
   
       If there is any error, add it to stab_test_errors.

   :param args:
   :param runners:
   :param batch_idx:
   :param inputs:
   :param ref_outputs:
   :param stab_test_errors:

.. py:function:: gold_check(output_refs, outputs, error)

   Check vart_ml_runner outputs correspond to dumped ones.
   
       Must be called in real data mode.

   :param output_refs:
   :param outputs:
   :param error:

.. py:function:: run(args)

   :param args:

