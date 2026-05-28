vart_ml.lib.python.vaisw_import.mock_modules.tensorflow
=======================================================

.. py:class:: VaiswSessionWrapper(NetworkWrapper)

   Base class to overwrite the tf.compat.v1 Session class.
   
       The real wrapper will inherit from this class and the original Session
       class from tensorflow. Thus calling super() acually lead to access the
       original class.

   .. py:method:: run(fetches, feed_dict = None, options = None, run_metadata = None)

      :param fetches:
      :param feed_dict:
      :param options:
      :param run_metadata:

.. py:class:: VaiswClientSessionWrapper(ModuleWrapper)

   Wrapper for tensorflow.python.client.session module
   
       This module contains the original Session definition. It is valid
       for both tensorflow 1 and 2.

.. py:class:: VaiswSaverWrapper(NetworkWrapper)

   .. py:method:: restore(sess, save_path)

      :param sess:
      :param save_path:

.. py:class:: TFSaverWrapper(ModuleWrapper)

   Wrapper for tensorflow.python.training.saver module

.. py:class:: VaiswFunctionWrapper(NetworkWrapper)

.. py:class:: TFEagerDefFunctionWrapper(ModuleWrapper)

   Wrapper for tensorflow.python.eager.def_function module

.. py:class:: VaiswConcreteFunctionWrapper(NetworkWrapper)

   .. py:method:: get_concrete_function(*_args, **_kwargs)

      :param _args:
      :param _kwargs:

.. py:class:: TFEagerFunctionWrapper(ModuleWrapper)

   Wrapper for tensorflow.python.eager.function module

.. py:class:: TFSavedModelLoad(ModuleWrapper)

   Wrapper for tensorflow.python.saved_model.load module

   .. py:method:: load(*args, **kwargs)

      :param args:
      :param kwargs:

.. py:class:: TFWrapper(ModuleWrapper)

   Wrapper for tensorflow module

   .. py:method:: _after_exec_hook()

.. py:function:: reject_fetches(fetches)

   :param fetches:

.. py:function:: check_tf_inputs(inputs) -> bool

   Check data if is must fallback or can be used by vaisw.
       return True if we need to fallback to the original command.

   :param inputs:
   :rtype: bool

