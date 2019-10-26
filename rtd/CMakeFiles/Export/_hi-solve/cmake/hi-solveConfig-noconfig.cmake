#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "hi-solve::hi-solve" for configuration ""
set_property(TARGET hi-solve::hi-solve APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(hi-solve::hi-solve PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libhi-solve.so"
  IMPORTED_SONAME_NOCONFIG "libhi-solve.so"
  )

list(APPEND _IMPORT_CHECK_TARGETS hi-solve::hi-solve )
list(APPEND _IMPORT_CHECK_FILES_FOR_hi-solve::hi-solve "${_IMPORT_PREFIX}/lib/libhi-solve.so" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
