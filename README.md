# VART ML API Reference

AMD Vitis AI Runtime (VART ML) API documentation — C++ and Python.

Built with [Sphinx](https://www.sphinx-doc.org/) + [Doxygen](https://www.doxygen.nl/) + [Breathe](https://breathe.readthedocs.io/),
styled with the AMD ROCm documentation theme.

## Build locally

```bash
pip install -r requirements.txt
apt install doxygen
doxygen Doxyfile
sphinx-build -b html docs docs/_build/html
open docs/_build/html/index.html
```

## Published docs

Automatically built and deployed on every push via ReadTheDocs.
