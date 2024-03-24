
include(CMakeFindDependencyMacro)

# Get the Meddyproject export.
find_dependency(Meddyproject 0 CONFIG)

# Include our export. This imports all of our targets.
include("${CMAKE_CURRENT_LIST_DIR}/MeddySDKCLIExport.cmake")

#
# Add alias targets whose names match those from the project file.
#
# It's important to make sure the names are the same for consistency. Namely, so that build
# interface users can use `OVERRIDE_FIND_PACKAGE` with `FetchContent_Declare()`.
#

add_executable(::MeddySDKCLI ALIAS MeddySDKCLI)
