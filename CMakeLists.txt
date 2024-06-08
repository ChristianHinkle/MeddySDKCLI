# Copyright (c) 2023-2024 Christian Hinkle, Brian Hinkle.

cmake_minimum_required(VERSION 3.24)

project(MeddySDKCLI
  VERSION 0.1.0
  DESCRIPTION ""
  HOMEPAGE_URL "https://github.com/ChristianHinko/MeddySDKCLI"
  LANGUAGES CXX
  )

#
# Add targets.
#
# We namespace target names using underscore characters "_". Not namespacing your target names can result in their
# file names not be specific enough. E.g., for the DAM library of MeddySDK, we want its library file to be named
# something like "MeddySDK_DAM.lib" instead of just "DAM.lib" - because that would be super vague.
#

add_executable(MeddySDKCLI)

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

add_executable(::MeddySDKCLI ALIAS MeddySDKCLI)

# List out required language features.
target_compile_features(MeddySDKCLI
  PUBLIC
    cxx_std_20
  )

#
# Add all header files and set up their include directories.
#
# The `BASE_DIRS` of file sets automatically get added to the target's include
# directories. So we don't use the `target_include_directories()` command anymore
# because that would be redundant.
#
# The file set of public headers is important because we use it to install
# them for install interface users. It's very important to list out all public headers
# in this file set so that install interface users have them.
#
# A nice benefit of listing all header files is that they can be easily-discoverable by IDEs.
#
target_sources(MeddySDKCLI
  PUBLIC
    FILE_SET meddysdkcli_public_headers
      TYPE HEADERS
      BASE_DIRS
        # Base directory of public headers.
        "${MeddySDKCLI_SOURCE_DIR}/Source/Public"
        # Base directory of generated headers.
        "${CMAKE_CURRENT_BINARY_DIR}"
      FILES
        # Add all public header files.
        "${MeddySDKCLI_SOURCE_DIR}/Source/Public/Main.h"
  PRIVATE
    FILE_SET meddysdkcli_private_headers
      TYPE HEADERS
      BASE_DIRS
        #
        # Base directory of private headers.
        #
        # It's nice to leave the "Private" directory out of this base include path so that, for
        # cpp include statements, you have to type "Private/" to access the non-public headers. This
        # makes it obvious for programmers when a header shouldn't be included in public files.
        #
        "${MeddySDKCLI_SOURCE_DIR}/Source"
      FILES
        # Add all private header files.
  )

# Add all source files.
target_sources(MeddySDKCLI
  PRIVATE
    "${MeddySDKCLI_SOURCE_DIR}/Source/Private/Main.cpp"
  )

# Get the MeddySDK_Meddyproject export. This gives us its imported targets.
find_package(MeddySDK_Meddyproject 0 CONFIG REQUIRED)

# Add dependencies to other targets.
target_link_libraries(MeddySDKCLI
  PRIVATE
    # Only depend on imported targets if we are BUILD_LOCAL_INTERFACE because we don't
    # want to have to put them in the export.
    $<BUILD_LOCAL_INTERFACE:MeddySDK::Meddyproject> # Add the imported MeddySDK::Meddyproject target as a dependency.
  )

include(GNUInstallDirs)

# Associate our target with an export and set up installation.
install(TARGETS MeddySDKCLI
  EXPORT MeddySDKCLIExport
  LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
  ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
  RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
  #
  # Add to interface include directories.
  #
  # Note: We take care of install-specific include directories here instead of `target_include_directories()`.
  #
  # Note: It's important to make sure cpp include statements of public headers are compatible between
  # install interface users and build interface users. E.g., a user's include statements should work for
  # both packaged library usage and subproject library usage, without having to adapt their code to either use case.
  #
  INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/MeddySDKCLI"
  # Copy over public headers.
  FILE_SET meddysdkcli_public_headers DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/MeddySDKCLI"
  )

# Generate script that imports targets associated with our export.
install(EXPORT MeddySDKCLIExport
  FILE "MeddySDKCLIExport.cmake"
  DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/MeddySDKCLI"
  )

# Create a package version file for our export.
include(CMakePackageConfigHelpers)
write_basic_package_version_file("${CMAKE_CURRENT_BINARY_DIR}/MeddySDKCLIConfigVersion.cmake"
  VERSION ${MeddySDKCLI_VERSION}
  COMPATIBILITY SameMajorVersion
  )

# Copy any files for downstream usage to the install directory.
install(
  FILES
    "${MeddySDKCLI_SOURCE_DIR}/MeddySDKCLIConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/MeddySDKCLIConfigVersion.cmake"
  DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/MeddySDKCLI"
  )

# Set some simple values for CPack based on this current project. The default
# values for these are specific to the top-level project but we want to allow for
# having several projects generate their own CPack configs without conflicting.
set(CPACK_PACKAGE_NAME "${PROJECT_NAME}")
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "${PROJECT_DESCRIPTION}")
set(CPACK_PACKAGE_HOMEPAGE_URL "${PROJECT_HOMEPAGE_URL}")
set(CPACK_INSTALL_CMAKE_PROJECTS "${CMAKE_BINARY_DIR};${PROJECT_NAME};ALL;/")

# Output the generated CPack configs in a directory specific to this project. This is
# nice so we can generate our own config without conflicting with other projects.
set(CPACK_OUTPUT_CONFIG_FILE "${CMAKE_BINARY_DIR}/${PROJECT_NAME}/CPackConfig.cmake")
set(CPACK_SOURCE_OUTPUT_CONFIG_FILE "${CMAKE_BINARY_DIR}/${PROJECT_NAME}/CPackSourceConfig.cmake")

# TODO: Decide on an appropriate place to set generator-specific variables. I tried
# wrapping this NSIS-specific variable in an if condition `CPACK_GENERATOR MATCHES "NSIS"` but
# it was never being entered.

#
# Use NSIS' feature for appending our binary directory to the PATH environment
# variable.
#
# TODO @techdebt: We want to have this functionality for other generators as well. I
# don't believe there's a generator-agnostic solution to this. E.g., in CMake's source
# code, they re-implement this feature for their WIX generator. I believe this kind
# of per-generator implementation would be the "correct" way. Alternatively, it's technically
# possible to run an install script that sets the env var manually but we would have to
# be transparent about it and give the user control over that behavior - not to mention, it
# would also have to do the opposite on uninstall.
#
set(CPACK_NSIS_MODIFY_PATH "ON")

# Generate a CPackConfig.cmake file for this project.
include(CPack)
