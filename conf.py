project = 'Vitis-AI'
author = "AMD"
copyright = "2024, Advanced Micro Devices Inc."
extensions = [
    "sphinx.ext.napoleon",
    "sphinx.ext.viewcode",
    "sphinx.ext.intersphinx",
    "breathe",
]
breathe_projects = {"Vitis-AI": "../doxygen_output/xml"}
breathe_default_project = "Vitis-AI"
breathe_default_members = ("members", "undoc-members")

html_theme = "sphinx_rtd_theme"
html_theme_options = {
    "navigation_depth": 4,
    "collapse_navigation": False,
    "sticky_navigation": True,
    "includehidden": True,
    "titles_only": False,
    "logo_only": False,
    "display_version": True,
    "prev_next_buttons_location": "bottom",
}
html_context = {
    "display_github": False,
}
napoleon_google_docstring = True
napoleon_numpy_docstring = True
napoleon_include_init_with_doc = True
exclude_patterns = ["_build"]
master_doc = "index"