.. AMD PSAS Python API Documentation
   Generated 2026-05-28

AMD PSAS Python Inference Library
===================================

.. toctree::
   :maxdepth: 2
   :caption: API Reference

   psas_runner
   npu_device

Overview
--------

The AMD PSAS Python Inference Library provides a high-level Python binding for
the NPU inference engine, enabling developers to load compiled models and run
batch inference on AMD NPU hardware.

Modules
-------

- :doc:`psas_runner` — High-level inference runner for PSAS models.
- :doc:`npu_device` — NPU device management utilities.

Quick Start
-----------

.. code-block:: python

   from psas_runner import PSASRunner
   from npu_device import NpuDevice

   # Optional: inspect the target device first
   dev = NpuDevice(index=0)
   print(dev.get_memory_usage())

   # Load a compiled model and run inference
   runner = PSASRunner("model.xmodel", device_index=0)
   runner.warmup(iterations=3)
   outputs = runner.run(inputs)
