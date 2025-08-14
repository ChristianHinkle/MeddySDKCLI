# Copyright (c) 2023-2025 Christian Hinkle, Brian Hinkle.

cmake_minimum_required(VERSION 4.0)

project(MeddySDKCLI_Tests
  VERSION 0.1.0
  LANGUAGES CXX
  )

# Note that we do not "find package" for our parent project's export. We don't need to since we are assuming that
# our parent project is using `add_subdirectory` on us. That means that we are being processed in the same
# configuration step as them. The targets that we reference in `target_link_libraries` commands don't even need
# to exist at this point because CMake only validates existence of the targets at the end of the entire configuration
# process.
