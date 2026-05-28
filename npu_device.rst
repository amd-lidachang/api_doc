.. _npu_device:

npu_device — NPU Device Management
=====================================

.. module:: npu_device
   :synopsis: Utilities for managing AMD NPU device state and resources.

Module description
------------------

``npu_device`` provides low-level NPU device management utilities.  Use this
module to query device resource usage or to reset device state between
inference sessions.

.. code-block:: python

   from npu_device import NpuDevice

   dev = NpuDevice(index=0)
   print(dev.get_memory_usage())

Classes
-------

NpuDevice
~~~~~~~~~

.. class:: NpuDevice(index=0)

   Represents a single AMD NPU device.

   :param index: Zero-based device index identifying which NPU to manage.
                 Defaults to ``0``.
   :type index: int

   **Attributes**

   .. attribute:: NpuDevice.index

      :type: int

      The zero-based device index passed at construction time.

   Methods
   ^^^^^^^

   .. method:: NpuDevice.__init__(index=0)

      Create a handle to the NPU device identified by *index*.

      :param index: Zero-based device index. Defaults to ``0``.
      :type index: int

   .. method:: NpuDevice.get_memory_usage()

      Return the current NPU memory consumption.

      :returns: Current NPU memory usage in bytes.
      :rtype: int

      **Example**

      .. code-block:: python

         dev = NpuDevice(index=0)
         used = dev.get_memory_usage()
         print(f"NPU memory in use: {used / 1024**2:.1f} MiB")

   .. method:: NpuDevice.reset()

      Reset the NPU device to its initial state.

      All in-flight operations are cancelled and device memory is freed.
      Call this method between independent inference sessions to guarantee
      a clean execution environment.

      **Example**

      .. code-block:: python

         dev = NpuDevice(index=0)
         dev.reset()
