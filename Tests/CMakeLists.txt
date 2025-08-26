# Copyright (c) 2023-2025 Christian Hinkle, Brian Hinkle.

cmake_minimum_required(VERSION 4.0)

project(MeddySDKCLI_Tests
  VERSION 0.1.0
  LANGUAGES CXX
  )

# Note that we do not "find package" for our parent project. We don't need to since we are built in the same
# cmake invocation as the it. That means we're being processed during the same configuration step as them, which
# means we'll have all their targets. Also, the targets that we reference in `target_link_libraries` commands don't
# even need to exist yet because CMake only validates the existence of targets at the end of the entire
# configuration process.

add_test(
  NAME MeddySDKCLI.Project.New.SuccessCase
  COMMAND ${CMAKE_COMMAND}
    -D"CMAKE_MODULE_PATH"=${CMAKE_MODULE_PATH}
    -D"MY_MEDDY_EXECUTABLE_PATH"='$<TARGET_FILE:MeddySDKCLI::Executable>'
    -D"MY_TEST_WORKING_DIRECTORY"='${CMAKE_CURRENT_BINARY_DIR}'
    -P "${CMAKE_CURRENT_SOURCE_DIR}/CMake/Scripts/Project_New_SuccessCase.cmake"
  )
