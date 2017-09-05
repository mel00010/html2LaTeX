# We need thread support
find_package (Threads REQUIRED)

# Download and unpack googletest at configure time
configure_file(GoogleTest.cmake.in  ${CMAKE_BINARY_DIR}/googletest-download/CMakeLists.txt)

execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
                 ${CMAKE_BINARY_DIR}/googletest-build)

# The gtest/gtest_main targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
  include_directories("${gtest_SOURCE_DIR}/include")
endif()



if(CMAKE_BUILD_TYPE STREQUAL "Coverage")
	# coverage target setup
	include(CodeCoverage)
	append_coverage_compiler_flags()
	set(COVERAGE_EXCLUDES
		'${PROJECT_SOURCE_DIR}/test/*'
		'${PROJECT_BINARY_DIR}/googletest-src/*'
		'${PROJECT_BINARY_DIR}/googletest-build/*'
		'/usr/include/c++/6/*'
		'/usr/include/c++/7/*'
		'/usr/local/include/boost/*'
	)
	setup_target_for_coverage(NAME coverage EXECUTABLE test/tests DEPENDENCIES tests)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Release")
	add_executable(tests EXCLUDE_FROM_ALL "")
else()
	add_executable(tests "")	
endif()
target_sources(tests
	PRIVATE
		main_test.cpp
)

target_include_directories(tests
	PRIVATE
		${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(tests
	html_test
	latex_test
	html
	latex
	gtest
	gmock
	gmock_main
	pthread
)

add_subdirectory(HTML)
add_subdirectory(LaTeX)
