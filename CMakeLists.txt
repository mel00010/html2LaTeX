cmake_minimum_required (VERSION 3.9)

project (html2LaTeX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(GNUInstallDirs)
INCLUDE(FindPkgConfig)
set(CMAKE_POLICY_DEFAULT_CMP0069 NEW)
cmake_policy(SET CMP0069 NEW)
include(CheckIPOSupported)

# Optional IPO. Do not use IPO if it's not supported by compiler.
check_ipo_supported(RESULT result OUTPUT output)
if(result)
  set(CMAKE_INTERPROCEDURAL_OPTIMIZATION TRUE)
else()
  message(WARNING "IPO is not supported: ${output}")
endif()

set(CMAKE_POLICY_DEFAULT_CMP0083 NEW)
cmake_policy(SET CMP0083 NEW)

include(CheckPIESupported)
check_pie_supported()
set(CMAKE_POSITION_INDEPENDENT_CODE FALSE)

set(CMAKE_LINK_WHAT_YOU_USE FALSE)

set(BUILD_SHARED_LIBS OFF)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--thinlto-cache-dir=${PROJECT_BINARY_DIR}/lto.cache")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,--thinlto-cache-dir=${PROJECT_BINARY_DIR}/lto.cache")


list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

set(REDIRECTION_FLAGS "-ffile-prefix-map=../../samples/=")
set(REDIRECTION_FLAGS "${REDIRECTION_FLAGS} -ffile-prefix-map=../samples/=")
set(REDIRECTION_FLAGS "${REDIRECTION_FLAGS} -ffile-prefix-map=${CMAKE_SOURCE_DIR}=")
set(REDIRECTION_FLAGS "${REDIRECTION_FLAGS} -ffile-prefix-map=../src=GameEngine")
set(REDIRECTION_FLAGS "${REDIRECTION_FLAGS} -ffile-prefix-map=../../src=GameEngine")
set(REDIRECTION_FLAGS "${REDIRECTION_FLAGS} -ffile-prefix-map=_deps/=")

set(SHARED_FLAGS "-Wno-unused-result -Wsign-compare")
set(SHARED_FLAGS "${SHARED_FLAGS} -fstack-protector-strong -Wformat")
set(SHARED_FLAGS "${SHARED_FLAGS} -Werror=format-security -fwrapv")
set(SHARED_FLAGS "${SHARED_FLAGS} -Wall -Wextra")
set(SHARED_FLAGS "${SHARED_FLAGS} -fdiagnostics-color=always")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${SHARED_FLAGS}")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${SHARED_FLAGS}")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -ggdb")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_DEBUG_BUILD=1 -DMIN_LOG_LEVEL=0")

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -D_DEBUG_BUILD=0 -DMIN_LOG_LEVEL=0 ${REDIRECTION_FLAGS}")


set( CMAKE_CXX_FLAGS_COVERAGE "${CMAKE_CXX_FLAGS_DEBUG}" CACHE STRING
    "Flags used by the C++ compiler during coverage builds."
    FORCE )
set( CMAKE_C_FLAGS_COVERAGE "${CMAKE_C_FLAGS_DEBUG}" CACHE STRING
    "Flags used by the C compiler during coverage builds."
    FORCE )
set( CMAKE_EXE_LINKER_FLAGS_COVERAGE
    "${CMAKE_EXE_LINKER_FLAGS_COVERAGE}" CACHE STRING
    "Flags used for linking binaries during coverage builds."
    FORCE )
set( CMAKE_SHARED_LINKER_FLAGS_COVERAGE
    "${CMAKE_SHARED_LINKER_FLAGS_COVERAGE}" CACHE STRING
    "Flags used by the shared libraries linker during coverage builds."
    FORCE )
mark_as_advanced(
    CMAKE_CXX_FLAGS_COVERAGE
    CMAKE_C_FLAGS_COVERAGE
    CMAKE_EXE_LINKER_FLAGS_COVERAGE
    CMAKE_SHARED_LINKER_FLAGS_COVERAGE )
# Update the documentation string of CMAKE_BUILD_TYPE for GUIs
set( CMAKE_BUILD_TYPE "${CMAKE_BUILD_TYPE}" CACHE STRING
    "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel Coverage."
    FORCE )

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
  set(CMAKE_CXX_FLAGS_COVERAGE "${CMAKE_CXX_FLAGS_COVERAGE} -fcoverage-mapping")
  set(CMAKE_CXX_FLAGS_COVERAGE "${CMAKE_CXX_FLAGS_COVERAGE} -fprofile-instr-generate")
  # using Clang
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fconcepts")
  set(CMAKE_CXX_FLAGS_COVERAGE "${CMAKE_CXX_FLAGS_COVERAGE} --coverage -fprofile-arcs")
  set(CMAKE_CXX_FLAGS_COVERAGE "${CMAKE_CXX_FLAGS_COVERAGE} -ftest-coverage")
  # using GCC
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Intel")
  # using Intel C++
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  # using Visual Studio C++
endif()

find_package (Boost COMPONENTS program_options REQUIRED)

add_library(boost INTERFACE IMPORTED)
target_link_libraries(boost ${boost_LIBRARIES})
target_include_directories(boost PUBLIC ${boost_INCLUDE_DIRS})


# The version number.
set(html2LaTeX_VERSION_MAJOR 1)
set(html2LaTeX_VERSION_MINOR 0)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

#Subdirectories
add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(docs)

# uninstall target
configure_file(
    "${CMAKE_SOURCE_DIR}/cmake/Uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/Uninstall.cmake"
    IMMEDIATE @ONLY)

add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/Uninstall.cmake)
