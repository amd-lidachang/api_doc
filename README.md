# AMD PSAS Python Inference Library — API Documentation

This repository contains the AMD-style API reference documentation for the
PSAS Python Inference Library.

## Modules

| Module | Description |
|--------|-------------|
| [`psas_runner`](psas_runner.rst) | High-level inference runner for PSAS models |
| [`npu_device`](npu_device.rst) | NPU device management utilities |

## Quick Start

```python
from psas_runner import PSASRunner
from npu_device import NpuDevice

# Optional: inspect device resources
dev = NpuDevice(index=0)
print(f"NPU memory: {dev.get_memory_usage()} bytes")

# Load model and run inference
runner = PSASRunner("model.xmodel", device_index=0)
runner.warmup(iterations=3)
outputs = runner.run(inputs)
```

## Building the Docs

Prerequisites: `sphinx`, `sphinx-rtd-theme`

```bash
pip install sphinx sphinx-rtd-theme
sphinx-build -b html . _build/html
```

Open `_build/html/index.html` in a browser.

## API Reference

### PSASRunner

```
PSASRunner(model_path, device_index=0)
    High-level inference runner for PSAS models.

    Parameters
    ----------
    model_path : str
        Path to the compiled .xmodel snapshot.
    device_index : int, optional
        Zero-based NPU device index. Default: 0.

    Methods
    -------
    run(inputs) -> list
        Execute inference on a batch of inputs.
        Raises RuntimeError if the NPU device is not accessible.

    warmup(iterations=3) -> None
        Run warmup passes to prime the NPU pipeline.
```

### NpuDevice

```
NpuDevice(index=0)
    Represents a single AMD NPU device.

    Parameters
    ----------
    index : int, optional
        Zero-based device index. Default: 0.

    Methods
    -------
    get_memory_usage() -> int
        Return current NPU memory usage in bytes.

    reset() -> None
        Reset the NPU device to its initial state.
```

## License

Copyright 2026 Advanced Micro Devices, Inc. All rights reserved.
