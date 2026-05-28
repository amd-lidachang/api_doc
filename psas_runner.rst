.. _psas_runner:

psas_runner — PSAS Inference Runner
=====================================

.. module:: psas_runner
   :synopsis: High-level interface for loading compiled models and running batch inference on AMD NPU hardware.

Module description
------------------

``psas_runner`` provides a high-level Python binding for the NPU inference engine.
It allows developers to load compiled ``.xmodel`` snapshots and execute batch
inference on AMD NPU hardware with minimal boilerplate.

.. code-block:: python

   from psas_runner import PSASRunner

   runner = PSASRunner("model.xmodel")
   outputs = runner.run(inputs)

Classes
-------

PSASRunner
~~~~~~~~~~

.. class:: PSASRunner(model_path, device_index=0)

   High-level inference runner for PSAS models.

   Loads a compiled ``.xmodel`` snapshot onto the specified AMD NPU device and
   exposes a simple :meth:`run` interface for batch inference.

   :param model_path: Path to the compiled ``.xmodel`` snapshot.
   :type model_path: str
   :param device_index: Zero-based NPU device index. Defaults to ``0``.
   :type device_index: int

   **Example**

   .. code-block:: python

      runner = PSASRunner("model.xmodel")
      outputs = runner.run(inputs)

   Methods
   ^^^^^^^

   .. method:: PSASRunner.__init__(model_path, device_index=0)

      Initialize the runner and load the model onto the NPU.

      :param model_path: Path to the compiled ``.xmodel`` snapshot.
      :type model_path: str
      :param device_index: Zero-based NPU device index. Defaults to ``0``.
      :type device_index: int

   .. method:: PSASRunner.run(inputs)

      Execute inference on a batch of inputs.

      :param inputs: List of NumPy arrays, one per input tensor.
      :type inputs: list
      :returns: List of NumPy arrays, one per output tensor.
      :rtype: list
      :raises RuntimeError: If the NPU device is not accessible.

      **Example**

      .. code-block:: python

         import numpy as np

         runner = PSASRunner("model.xmodel")
         x = np.random.rand(1, 3, 224, 224).astype(np.float32)
         outputs = runner.run([x])

   .. method:: PSASRunner.warmup(iterations=3)

      Run several inference passes to warm up the NPU pipeline.

      Warming up the pipeline before production inference reduces latency
      variance caused by lazy initialisation inside the NPU runtime.

      :param iterations: Number of warmup passes. Defaults to ``3``.
      :type iterations: int

      **Example**

      .. code-block:: python

         runner = PSASRunner("model.xmodel")
         runner.warmup(iterations=5)
         outputs = runner.run(inputs)
