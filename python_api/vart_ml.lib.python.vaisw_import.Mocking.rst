vart_ml.lib.python.vaisw_import.Mocking
=======================================

.. py:class:: MockingObject

   Simple mock object that should not be used.
   
       All access to attributes should raise AttributeError unless the attribute
       was explicitly set.
       Calling the object like a function return another Mock object.

.. py:class:: MockingModule(ModuleType, MarkedWrapper)

   False class mocking a module.
   
       Return MockingObject subclass on every attributes access.

