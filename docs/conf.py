# Minimum sphinx version
needs_sphinx = '2.0.1'

# Set breathe as an extension
extensions = [ "breathe" ]

# Breathe configuration
breathe_default_project = "@CMAKE_PROJECT_NAME@"

# Use the ReadTheDocs theme
html_theme = "sphinx_rtd_theme"
