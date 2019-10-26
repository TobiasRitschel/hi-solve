# Find all unit test programs
file(GLOB testprogs "unittests/*.cpp")

# Loop over every unit test program
foreach(prog ${testprogs})
  # Get name of test program executable
  get_filename_component(exe ${prog} NAME_WE)

  # Add the test program
  add_executable(${exe} ${prog})

  # Link the test program executable to the BaseVec library
  target_link_libraries(${exe} ${CMAKE_PROJECT_NAME})

  # Add test program executable as a test
  add_test(${exe} ${exe})
endforeach()
