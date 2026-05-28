vart_ml.lib.python.vaisw_import.mock_modules.wrappers
=====================================================

.. py:class:: MarkedWrapper

   Base class to mark wrappers for the upper world

.. py:class:: FrameworkFallbackExc(Exception)

   Special exception to avoid intercepting function from this object anymore.
   
       When this exception is raised, the wrapper will mark the object as not supported
       and future call will always be passthrough the original version.

.. py:class:: Framework(Enum)

.. py:class:: NetworkWrapper(MarkedWrapper)

   Base class for all classes that are intended to replace a network.
   
       All framework will call a 'network' object (with one or multiple layers)
       to handle the result. All common functions to all those objects can be
       put here.

   .. py:method:: set_network_name(name: str)

      Vaisw function to allow wrapped network to be named.

      :param str name:

   .. py:method:: vaisw_run(framework, input_data, init_args = None, **kwargs)

      Unique link to vaiswRunner so it can be changed easily
      
              Will create the vaiswRunner.Z* object and call run on it. The extra
              kwargs are passed to the underline run function, see this function to
              get details of the args.
              The init_args dict is passed to the Z* object creation function.

      :param framework:
      :param input_data:
      :param init_args:
      :param kwargs:

.. py:class:: _NWDecorators

   Decorators for the NetworkWrapper
   
       This class list all decorators that will be applied to the NetworkWrapper.
       We cannot use metaclass to avoid issue if a class in the framework inherit from
       the wrapper and use another metaclass (multiple metaclass being forbidden).
       But it would be easier that way :(

   .. py:method:: no_protect(func: Callable[..., Any]) -> Callable[..., Any]

      Decorator to apply to functions that does not have to be protected by
              the wrap protect

      :param Callable[..., Any] func:
      :rtype: Callable[..., Any]

   .. py:method:: to_be_protected(fname: str, func: Callable[..., Any]) -> bool

      Return True if the function must be protected

      :param str fname:
      :param Callable[..., Any] func:
      :rtype: bool

   .. py:method:: wrap_protect()

      Decorator to add recall protect to a Network wrapper class
      
              When acting on Network (loading, dump to onnx, ...), the framework may
              call its wrapped function to perform some caluclation. If we are not able
              to differenciate standard inference and special case, the decrator add a
              'recall_protect' context manager to a wrapper that make it fully passthrough.
      
              The object need to inherit from the original Network class as we call super()
              to get the original function.

   .. py:method:: transfer_vars(orig_cls)

      Decorator to transfer vars from original funcs into wrapped one.
      
              In tensorflow v1, tensorflow mark some of the original functions with
              a specific attribute and the behavior may change depending on the existence
              of this attribute.
              Thus we copy all attributes to the wrapping function to avoid such change.

      :param orig_cls:

   .. py:method:: decorate(orig_cls)

      :param orig_cls:

.. py:class:: MetaModule(type)

   Meta class for ModuleWrapper
   
       If the class define variables that are subclasses of NetworkWrapper, this meta
       replace them with a real wrapper in the 'Module' class. This wrapper is created
       lazily when the user access the attribute in the module.
       The wrapper inherit from the NetworkWrapper and the original class (the one
       with the same name in the original module).

   .. py:method:: _after_exec_code(orig_after_exec_func, net_wraps: List[Tuple[str, Any]], wrapped_cls: Dict[NetworkWrapper, str])

      Make wrapper for the after_exec_hook
      
              This allow to the wrapper to make some special change after the loading
              of the original module.
              If the wrapper already have this function set it is passed as orig_after_exec_func
              here to be called at the end.

      :param orig_after_exec_func:
      :param List[Tuple[str, Any]] net_wraps:
      :param Dict[NetworkWrapper, str] wrapped_cls:

   .. py:method:: _wrapped_type_code(local_name: str, prop: str, wrap_cls: NetworkWrapper, wrapped_cls: Dict[NetworkWrapper, str])

      Make the code to create the wrapped class.
      
              The wrapped class inherit from wrapper and the prop (the original property
              from the original module).
              If the wrapper inherit from another wrapper, the wrapped class of this other
              wrapper will correctly setup the class hierarchy. This is needed when a class
              inherit from another in the same module and we want to wrap both classes.
              In case of inheritance from another module, nothing special need to be done.
              e.g.:
                orig module :
                  class A:
                      ...
                  class B(A):
                      ...
      
                wrapper :
                  class Wa(NetworkWrapper):
                      ...
                  class Wb(Wa): # Mark inheritance in the wrapper too.
                      ...
      
                wrapped classes (created at runtime, no code from them as all come from wrappers):
                  class A'(Wa, A):
                      pass
                  class B'(Wb, B, A'):
                      pass
      
              The final hierarchy is the following (it would be the same if B was in
              another module and import A, which would be A' in the wrapping context) :
      
                            Wa          A
                             \        /
                              -- A' --
                                /
                   Wb          B
                    \        /
                      -- B' --
      
              In case of multiple wrapping of the same object, we avoid wrapping the
              wrapper. Otherwise we have an inheritance loop.

      :param str local_name:
      :param str prop:
      :param NetworkWrapper wrap_cls:
      :param Dict[NetworkWrapper, str] wrapped_cls:

.. py:class:: ModuleWrapper(ModuleType, MarkedWrapper)

   Wrapper for any module
   
       This wrapper is seen as a module. All attributes accessible through the
       original module is accessible in this wrapper. Any attribute overwritten
       by the wrapper will shadow the original attribute, allowing to do other actions.
       The 'orig_module' property allow to retrieve the original module.
   
       The original module must be available when constructing this wrapper.

   .. py:property:: orig_module

   .. py:method:: _module_pass_through()

      Context manager to allow importing the original module under it.
      
              This is mostly intended to be used during module initilization so that
              exec code can import the original module to make some changes on it
              without being distrupt by the wrapper.

   .. py:method:: _before_exec_hook()

      Called at the beginning of the exec_module function in the Spec wrapper

   .. py:method:: _after_exec_hook()

      Called at the end of the exec_module function in the Spec wrapper

.. py:class:: VaiswAvailableModuleSpec(ModuleSpec)

   Special spec for modules that were already imported but not put in sys.modules

   .. py:method:: create_module(_spec)

      :param _spec:

   .. py:method:: exec_module(module)

      :param module:

.. py:class:: VaiswWrapperSpec(ModuleSpec, Loader)

   Vaisw Wrapper for modules spec
   
       Load the original module pass as parameter and return the wrapper specified
       in the constructor. The wrapper must hinerit from the ModuleWrapper class.
   
       The exec_wrp wrap the exec_module into a 'with' statement

   .. py:method:: _no_context()

   .. py:method:: create_module(_orig_spec)

      :param _orig_spec:

   .. py:method:: exec_module(module_wrp)

      :param module_wrp:

.. py:function:: add_module_to_wrapped_modules(module: ModuleType, name: Optional[str] = None)

   :param ModuleType module:
   :param Optional[str] name:

.. py:function:: disable_wrap()

   Wrapper need to be disable in each entry into vaiswRunner to avoid re-entry.

.. py:function:: is_vaisw_wrapper()

