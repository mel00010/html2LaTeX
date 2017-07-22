# We need thread support
find_package (Threads REQUIRED)

# Enable ExternalProject CMake module
include (ExternalProject)

# Download and install GoogleTest
ExternalProject_Add(
	gtest
	URL https://github.com/google/googletest/archive/master.zip
	PREFIX ${CMAKE_CURRENT_BINARY_DIR}/gtest
	# Disable install step
	INSTALL_COMMAND ""
)

# Get GTest source and binary directories from CMake project
ExternalProject_Get_Property(gtest source_dir binary_dir)

# Create a libgtest target to be used as a dependency by test programs
add_library(libgtest IMPORTED STATIC GLOBAL)
add_dependencies(libgtest gtest)

# Set libgtest properties
set_target_properties(libgtest PROPERTIES
	"IMPORTED_LOCATION" "${binary_dir}/googlemock/gtest/libgtest.a"
	"IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
)

# Create a libgmock target to be used as a dependency by test programs
add_library(libgmock IMPORTED STATIC GLOBAL)
add_dependencies(libgmock gtest)

# Set libgmock properties
set_target_properties(libgmock PROPERTIES
	"IMPORTED_LOCATION" "${binary_dir}/googlemock/libgmock.a"
	"IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
)
add_library(libgmock_main IMPORTED STATIC GLOBAL)
set_target_properties(libgmock_main PROPERTIES
	"IMPORTED_LOCATION" "${binary_dir}/googlemock/libgmock_main.a"
	"IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
)
# I couldn't make it work with INTERFACE_INCLUDE_DIRECTORIES
include_directories("${source_dir}/googletest/include"
					"${source_dir}/googlemock/include")

# coverage target setup
include(CodeCoverage)
append_coverage_compiler_flags()
set(COVERAGE_EXCLUDES
	'${PROJECT_BINARY_DIR}/test/gtest/*'
	'/usr/include/c++/6/*'

)
setup_target_for_coverage(NAME coverage EXECUTABLE test/tests DEPENDENCIES tests)

add_executable(tests "")

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
	libgtest
	libgmock
	gmock_main
	pthread
)

add_subdirectory(HTML)
add_subdirectory(LaTeX)
