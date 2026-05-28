C++ API Reference
=================

The VART C++ API is organized in the ``vart`` namespace across two libraries:

- **VART ML** — NPU runner, tensor management, and low-level snapshot inference
- **VART-X** — Device lifecycle, memory, pre/post processing, video pipeline, and tracking

VART ML
-------

.. toctree::
   :maxdepth: 1

   Runner
   RunnerFactory
   VartMLRunner
   NpuTensor
   NpuTensorInfo
   enums

VART-X
------

.. toctree::
   :maxdepth: 1

   Device
   Memory
   InferResult
   PreProcess
   PostProcess
   Overlay
   MetaConvert
   Tracker
   VideoFrame
   PLKernel
   Logger
   vart_x_types
