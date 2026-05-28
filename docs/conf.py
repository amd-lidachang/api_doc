import os
import sys

# Add Python source paths so autodoc can import the modules
# Point to the directory containing psas_runner.py and npu_device.py
sys.path.insert(0, os.path.abspath(".."))
sys.path.insert(0, "/tmp/test_pyapi")

project = "API Reference"
author = "AMD"
release = "1.0"

extensions = [
    "rocm_docs",
    "breathe",
    "sphinx.ext.autodoc",
    "sphinx.ext.napoleon",
    "sphinx.ext.viewcode",
    "sphinx.ext.intersphinx",
]

# Breathe (C++ Doxygen integration) — no C++ files in this project, kept for completeness
breathe_projects = {"api": "doxygen/xml"}
breathe_default_project = "api"
breathe_domain_by_extension = {"h": "cpp", "hpp": "cpp"}
breathe_default_members = ("members", "undoc-members")

# Napoleon (Google/NumPy docstring support)
napoleon_google_docstring = True
napoleon_numpy_docstring = True
napoleon_include_init_with_doc = True

# Autodoc defaults
autodoc_default_options = {
    "members": True,
    "undoc-members": True,
    "show-inheritance": True,
    "member-order": "bysource",
}

# AMD ROCm theme
# Fallback: if rocm-docs-core is not importable, pydata-sphinx-theme is used with AMD color overrides in custom.css
html_theme = "rocm_docs_theme"
html_theme_options = {
    "flavor": "rocm",
}
html_static_path = ["_static"]
html_css_files = ["custom.css"]
html_favicon = "https://www.amd.com/themes/custom/amd/favicon.ico"
