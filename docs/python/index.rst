Python API Reference
====================

The VART ML Python API provides Python bindings over the C++ runtime via the ``vart_ml`` extension
module. The ``VART`` convenience module re-exports the primary interface.

**Quick start**

.. code-block:: python

   from VART import Runner

   runner = Runner("/path/to/snapshot")
   inputs  = [runner.allocate_npu_tensor(i) for i in runner.get_tensors_info("INPUT", "CPU")]
   outputs = [runner.allocate_npu_tensor(o) for o in runner.get_tensors_info("OUTPUT", "CPU")]
   runner.execute(inputs, outputs)

.. toctree::
   :maxdepth: 1

   runner
   tensor
   vaisw
