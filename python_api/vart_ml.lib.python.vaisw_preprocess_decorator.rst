vart_ml.lib.python.vaisw_preprocess_decorator
=============================================

.. py:class:: PassThroughWrapper

   Wrapper that forwards the first argument by default.
       It can pass through the original function call using the call_original_func method.

   .. py:method:: call_original_func(x)

      :param x:

   .. py:method:: get_original_input()

.. py:class:: PreprocTransformDecorator

   Decorator that wraps a preprocess function.
       At generation time, it traces the function and exports it to ONNX.
       At runtime, it replaces the original function by a simple forward of the first argument.
       In case one needs to pass through the original function call, it can be done using the
       call_original_func method of its replacement func attribute.

   .. py:method:: get_original_input()

   .. py:method:: call_original_func(x)

      :param x:

   .. py:method:: clean()

