vart_ml.lib.python.vaisw_import.mock_modules.caffe
==================================================

.. py:class:: VaiswNetWrapper(NetworkWrapper)

   Wrapper of caffe.Net object

   .. py:method:: forward(*args, **kwargs)

      :param args:
      :param kwargs:

.. py:class:: PyCaffeWrapper(ModuleWrapper)

   Wrapper for caffe.pycaffe module
   
       The real Net class is in caffe._caffe, pycaffe is only the python interface
       to it but it is almost certain that all use of Net will pass through pycaffe.

