# Needed to call Doxygen (on ReadTheDocs server)
import subprocess, os

# Needed to copy files
from shutil import copyfile

# Function for processing Doxygen.in configuration file and other configuration files
def configureDoxyfile(input_dir, output_dir):
  # Process Doxyfile.in
  with open('Doxyfile.in', 'r') as file :
    filedata = file.read()

  filedata = filedata.replace('@DOXYGEN_INPUT_DIR@',  input_dir)
  filedata = filedata.replace('@DOXYGEN_OUTPUT_DIR@', output_dir)

  with open('Doxyfile', 'w') as file:
    file.write(filedata)

  # Copy other configuration files
  copyfile('conf.py.in',          'conf.py')
  copyfile('index.rst.in',        'index.rst.py')
  copyfile('requirements.txt.in', 'requirements.txt.py')

# Minimum sphinx version
needs_sphinx = '2.0.1'

# Set breathe as an extension
extensions = [ "breathe" ]

# Breathe configuration
breathe_default_project = 'hi-solve'

# Use the ReadTheDocs theme
html_theme = "sphinx_rtd_theme"

# Check if we're on the ReadTheDocs server
read_the_docs_build = os.environ.get('READTHEDOCS', None) == 'True'

breathe_projects = {};

# If we're on the ReadTheDocs server, process the Doxygen configuration file etc.
if read_the_docs_build:
  input_dir = '.'
  output_dir = 'build'
  configureDoxyfile(input_dir, output_dir)
  subprocess.call('doxygen', shell=True)
  breathe_projects['hi-solve'] = output_dir + '/docs/xml'
