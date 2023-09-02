
cmake_minimum_required(VERSION 3.8)

project("MeddySDKCLI" LANGUAGES CXX)

add_executable(MeddySDKCLI)

# Pathname to source directory.
set(MEDDYSDKCLI_SOURCE_PATHNAME "Source")

# Pathname to public source directory.
set(MEDDYSDKCLI_SOURCE_PATHNAME_PUBLIC "${MEDDYSDKCLI_SOURCE_PATHNAME}/Public")

# Pathname to private source directory.
set(MEDDYSDKCLI_SOURCE_PATHNAME_PRIVATE "${MEDDYSDKCLI_SOURCE_PATHNAME}/Private")

# All public source files.
file(GLOB_RECURSE MEDDYSDKCLI_SOURCE_FILES_PUBLIC LIST_DIRECTORIES false "${MEDDYSDKCLI_SOURCE_PATHNAME_PUBLIC}/*")

# All private source files.
file(GLOB_RECURSE MEDDYSDKCLI_SOURCE_FILES_PRIVATE LIST_DIRECTORIES false "${MEDDYSDKCLI_SOURCE_PATHNAME_PRIVATE}/*")

# Configure MeddySDKCLI sources

target_sources(MeddySDKCLI PUBLIC ${MEDDYSDKCLI_SOURCE_FILES_PUBLIC})

target_sources(MeddySDKCLI PRIVATE ${MEDDYSDKCLI_SOURCE_FILES_PRIVATE})

# Configure MeddySDKCLI include directories

target_include_directories(MeddySDKCLI PUBLIC ${MEDDYSDKCLI_SOURCE_PATHNAME_PUBLIC})

target_include_directories(MeddySDKCLI PRIVATE ${MEDDYSDKCLI_SOURCE_PATHNAME})

# Enable C++20 if supported
if(CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET MeddySDKCLI PROPERTY CXX_STANDARD 20)
endif()

# Enable Hot Reload for MSVC compilers if supported
if(POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()
