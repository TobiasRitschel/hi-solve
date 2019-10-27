# Minimum version required
cmake_minimum_required(VERSION 3.1..3.15)

if(${CMAKE_VERSION} VERSION_LESS 3.15)
	cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
else()
	cmake_policy(VERSION 3.15)
endif()

# Project information
project(hi-solve VERSION 1.0.0
	DESCRIPTION "The Hi-solve project implements a class of high-order numerical methods for solving nonlinear algebraic equations which are inspired by numerical methods for solving cubic equations of state in thermodynamics. This library is concerned with scalar equations."
	LANGUAGES CXX)

# Options
option(BUILD_DOC "Build documentation" ON) # Build documentation

# Require out-of-source builds
file(TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH)
if(EXISTS "${LOC_PATH}")
  message(FATAL_ERROR "You cannot build in a source directory (or any directory with a CMakeLists.txt file). Please make a build subdirectory. Feel free to remove CMakeCache.txt and CMakeFiles.")
endif()

# Source files
file(GLOB SOURCE_CODE_FILES
  src/*.cpp)

# Header files
file(GLOB HEADER_FILES
  include/*.h)

# Add the library
add_library(${CMAKE_PROJECT_NAME} SHARED ${SOURCE_CODE_FILES} ${HEADER_FILES})

# Require C++11
target_compile_features(${CMAKE_PROJECT_NAME} PUBLIC cxx_std_11)

# Add the include directory
target_include_directories(${CMAKE_PROJECT_NAME}
  PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

# Add examples
add_subdirectory(examples)

# Add testing if this is the main project and testing is turned on
if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  include(CTest)
endif()

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND BUILD_TESTING)
  add_subdirectory(test)
endif()

# Add the cmake modules folder
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

# Add the documentation subfolder
add_subdirectory("docs")

# Check if Doxygen is installed
find_package(Doxygen)
if(DOXYGEN_FOUND)
  # Documentation input and output directories
  set(DOCS_INPUT_DIR         ${CMAKE_CURRENT_SOURCE_DIR}/docs)
  set(DOCS_OUTPUT_DIR        ${CMAKE_CURRENT_BINARY_DIR}/docs)

  # Doxygen configuration file in the build folder
  set(DOXYGEN_CONFIG_FILE_IN    ${DOCS_INPUT_DIR}/Doxyfile.in)
  set(DOXYGEN_CONFIG_FILE_BUILD ${DOCS_OUTPUT_DIR}/Doxyfile)

  # Copy the doxygen file into the build directory
  configure_file(
    ${DOXYGEN_CONFIG_FILE_IN}
    ${DOXYGEN_CONFIG_FILE_BUILD}
    @ONLY)
  message("-- Creating ${DOXYGEN_CONFIG_FILE_BUILD} from ${DOXYGEN_CONFIG_FILE_IN}")

  # Add doc as a target
  add_custom_target(doc
    COMMAND
    ${DOXYGEN_EXECUTABLE}
    ${DOXYGEN_CONFIG_FILE_BUILD}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Generating documentation using Doxygen"
    VERBATIM)

  # Specify that the sphinx package is required
  find_package(Sphinx REQUIRED)
  if(SPHINX_FOUND)
    # Copy the conf.py file into the build directory
    configure_file(
      ${DOCS_INPUT_DIR}/conf.py.in
      ${DOCS_OUTPUT_DIR}/conf.py
      @ONLY)
    message("-- Creating ${DOCS_OUTPUT_DIR}/conf.py from ${DOCS_INPUT_DIR}/conf.py.in")

    # Copy other configuration files
    configure_file(
      ${DOCS_INPUT_DIR}/index.rst.in
      ${DOCS_OUTPUT_DIR}/index.rst)
    message("-- Copying ${DOCS_INPUT_DIR}/index.rst.in to ${DOCS_OUTPUT_DIR}/index.rst")

    configure_file(
      ${DOCS_INPUT_DIR}/requirements.txt.in
      ${DOCS_OUTPUT_DIR}/requirements.txt)
    message("-- Copying ${DOCS_INPUT_DIR}/requirements.txt.in to ${DOCS_OUTPUT_DIR}/requirements.txt")

    # Add sphinx target
    add_custom_target(Sphinx
      COMMAND
      ${SPHINX_EXECUTABLE} -b html
      ${DOCS_OUTPUT_DIR} ${DOCS_OUTPUT_DIR}/sphinx
      -Dbreathe_projects.${CMAKE_PROJECT_NAME}=${DOCS_OUTPUT_DIR}/xml
      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
      COMMENT "Generating documentation using Sphinx")

    # The Sphinx target depends on the doc target (because of the Doxygen XML files)
    add_dependencies(Sphinx doc)
  else()
    message("Sphinx is required in order to generate the documentation for ReadTheDocs")
  endif()
else()
  message("Doxygen is required in order to generate the documentation")
endif()

# Create a config file so that other projects can find this one
set(PROJECT_TARGET_NAME ${CMAKE_PROJECT_NAME})
set(PROJECT_CONFIG_NAME ${CMAKE_PROJECT_NAME}Config)
set(PROJECT_NAMESPACE   ${CMAKE_PROJECT_NAME}::)

install(TARGETS
        ${PROJECT_TARGET_NAME}
        EXPORT ${PROJECT_CONFIG_NAME}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
export( TARGETS
        ${PROJECT_TARGET_NAME}
        NAMESPACE ${PROJECT_NAMESPACE}
        FILE "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_CONFIG_NAME}.cmake"
)
install(EXPORT
        ${PROJECT_CONFIG_NAME}
        DESTINATION "${CMAKE_INSTALL_DATADIR}/${PROJECT_TARGET_NAME}/cmake"
        NAMESPACE ${PROJECT_NAMESPACE}
)
