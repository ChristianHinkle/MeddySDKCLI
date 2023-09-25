
cmake_minimum_required(VERSION 3.8)

project(MeddySDKCLI
  VERSION 0.1
  LANGUAGES CXX
  )

add_executable(MeddySDKCLI)

# Add source files. Including header files as well so they are easily-discoverable by IDEs.
target_sources(MeddySDKCLI
  PUBLIC
    # Add all public headers under a file set.
    #
    # This file set is usable for installing headers.
    FILE_SET meddysdkcli_public_headers
      TYPE HEADERS
      BASE_DIRS
        "${MeddySDKCLI_SOURCE_DIR}/Source/Public"
        "${MeddySDKCLI_BINARY_DIR}" # base directory of generated headers
      FILES
        # Add all public header files.
        "${MeddySDKCLI_SOURCE_DIR}/Source/Public/MeddySDKCLI.h"
  PRIVATE
    # Add all private source files.
    "${MeddySDKCLI_SOURCE_DIR}/Source/Private/MeddySDKCLI.cpp"
  )

# Add include directories.
#
# All are enclosed in BUILD_INTERFACE because they are specific to our source directory and
# should be used only when building binaries for our target.
#
# No install-specific directories are provided here. That gets taken care of
# elsewhere, i.e., the install command.
target_include_directories(MeddySDKCLI
  PUBLIC
    "$<BUILD_INTERFACE:${MeddySDKCLI_SOURCE_DIR}/Source/Public>" # add our public includes
    "$<BUILD_INTERFACE:${MeddySDKCLI_BINARY_DIR}>" # add easy access to generated headers
  PRIVATE
    "$<BUILD_INTERFACE:${MeddySDKCLI_SOURCE_DIR}/Source>" # add easy access to non-public includes
  )

# Get the Meddyproject export. This gives us its imported targets.
find_package(Meddyproject 0 CONFIG REQUIRED)

# Add dependencies to other targets.
target_link_libraries(MeddySDKCLI
  PRIVATE
    MeddySDK::Meddyproject # add the imported Meddyproject target
  )

include(GNUInstallDirs)

# Associate our target with an export and set up installation.
install(TARGETS MeddySDKCLI
  EXPORT MeddySDKCLIExport
  LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
  ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
  RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}"
  INCLUDES DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}" # gets added to interface include directories
  FILE_SET meddysdkcli_public_headers DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/MeddySDKCLI" # copy over public headers
  )

# Generate script that imports targets associated with our export.
install(EXPORT MeddySDKCLIExport
  FILE "MeddySDKCLIExport.cmake"
  NAMESPACE MeddySDK::
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

# Enable C++20 if supported.
if(CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET MeddySDKCLI PROPERTY CXX_STANDARD 20)
endif()

# Enable Hot Reload for MSVC compilers if supported.
if(POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()
