
include(CMakeFindDependencyMacro)

# Get the Meddyproject export.
find_dependency(Meddyproject 0 CONFIG)

# Include our export. This imports all of our targets.
include("${CMAKE_CURRENT_LIST_DIR}/MeddySDKCLIExport.cmake")
