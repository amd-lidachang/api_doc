import os
import sys

project = "VART API Reference"
author = "Advanced Micro Devices, Inc."
release = "2025.1"
copyright = "2025 Advanced Micro Devices, Inc."

extensions = [
    "breathe",
    "sphinx.ext.autodoc",
    "sphinx.ext.napoleon",
    "sphinx.ext.viewcode",
    "sphinx.ext.intersphinx",
]

# Use rocm_docs_theme (the Sphinx theme) without the rocm_docs *extension*.
# The extension calls util.get_branch() which fails on ReadTheDocs shallow clones
# because the branch ref is not in the format the regex expects.
try:
    import rocm_docs_theme  # noqa: F401
    html_theme = "rocm_docs_theme"
    html_theme_options = {"flavor": "rocm"}
except ImportError:
    html_theme = "pydata_sphinx_theme"
    html_theme_options = {
        "logo": {"text": "VART API"},
        "navbar_start": ["navbar-logo"],
        "primary_sidebar_end": [],
    }

# Breathe — integrates Doxygen XML into Sphinx (single project covers vart_ml + vart_x)
breathe_projects = {"vart_ml": "../docs/doxygen/xml"}
breathe_default_project = "vart_ml"
breathe_domain_by_extension = {"hpp": "cpp", "h": "cpp"}
breathe_default_members = ("members", "undoc-members")

# Napoleon docstring style
napoleon_google_docstring = True
napoleon_numpy_docstring = True
napoleon_include_init_with_doc = True
napoleon_use_param = True
napoleon_use_rtype = True

html_static_path = ["_static"]
html_css_files = ["custom.css"]
html_favicon = "https://www.amd.com/themes/custom/amd/favicon.ico"

exclude_patterns = ["_build", "Thumbs.db", ".DS_Store"]
