# Copyright (c) 2023-2025 Christian Hinkle, Brian Hinkle.

cmake_minimum_required(VERSION 4.0)

project(MeddySDKCLI_Source
  VERSION 0.1.0
  LANGUAGES CXX
  )

#
# Create targets.
#
# We namespace target names using underscore characters "_". Namespacing helps avoid ambiguity. E.g., for
# the DAM library of MeddySDK, we name it "MeddySDK_DAM" instead of just "DAM", because that would be very vague.
#

add_library(MeddySDKCLI_Source INTERFACE)

#
# Set output names of our targets.
#
# This determines the name of the binary files generated for the target. The name may differ from the actual
# target name. E.g., for MeddySDKCLI, we name its executable file "meddy" to suit our desired command line usage.
#

set_target_properties(MeddySDKCLI_Source
  PROPERTIES
    OUTPUT_NAME "meddy"
  )

#
# Add alias targets.
#
# We name these with special characters that filenames can't have. We use these aliases instead of the direct
# target names where possible so that they can't be be interpreted as filenames.
#
# It's conventional to use "::" in these names, like namespaces. If a target doesn't have anything to namespace in its
# name then just prepend "::" to it, analogous to how we indicate global scope in cpp.
#
# The aliases set up here get used by build interface users. Make sure the same aliases are also set up for install
# interface users somewhere else. We do that in the export's config file. It's important to make sure the names are
# the same in both cases for consistency. Namely, so that build interface users can use `OVERRIDE_FIND_PACKAGE` with
# `FetchContent_Declare()`.
#

add_library(MeddySDKCLI::Source ALIAS MeddySDKCLI_Source)

# List out required language features.
target_compile_features(MeddySDKCLI_Source
  INTERFACE
    cxx_std_20
  )

#
# Add all header files and set up their include directories.
#
# The `BASE_DIRS` of file sets automatically get added to the target's include
# directories. So we don't use the `target_include_directories()` command anymore
# because that would be redundant.
#
# Interface and/or public file sets are important because we use them to install headers for
# the install interface users.
#
# A nice benefit of listing all header files is that they can be easily-discoverable by IDEs.
#
target_sources(MeddySDKCLI_Source
  INTERFACE
    FILE_SET meddysdkcli_source_interface_headers
      TYPE HEADERS
      BASE_DIRS
        #
        # Base directory of private headers.
        #
        # It's nice to leave the "Source" directory out of this base include path so that, for
        # cpp include statements, you have to type "Source/" to access the non-public headers. This
        # makes it obvious for programmers when a header shouldn't be included in public files.
        #
        "${CMAKE_CURRENT_SOURCE_DIR}"
      FILES
        # Add all private header files.
  )

# Add all source files.
target_sources(MeddySDKCLI_Source
  INTERFACE
    "${CMAKE_CURRENT_SOURCE_DIR}/Source/Main.cpp"
  )

# Get any package exports which we depend on. This gives us imported targets for them.

find_package(MeddySDK_Meddyproject 0 CONFIG REQUIRED
  COMPONENTS Static
  )

# Add dependencies to other targets. For imported targets, it's important to only depend on them if we
# are BUILD_LOCAL_INTERFACE, because we don't want them to get mixed into our export.
target_link_libraries(MeddySDKCLI_Source
  INTERFACE
    $<BUILD_LOCAL_INTERFACE:MeddySDK::Meddyproject::Static>
  )

# Idea: It might be cool to install this library and all its source files. That would allow downstream projects to use
# us. For now, this library is just a way for us to share source files across all the different types of libraries.
