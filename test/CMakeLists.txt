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
					
set(TEST_SOURCES
	main_test.cpp
	HTML/HTMLTree_test.cpp
	HTML/HTMLTreeInterface_test.cpp
	HTML/Parse/DetermineCharEncoding_test.cpp
	HTML/Parse/MagicString_test.cpp
	HTML/Parse/ParseHTML_test.cpp
	LaTeX/GenerateLaTeX_test.cpp
	LaTeX/LaTeXOStream_test.cpp
	LaTeX/UnicodeToLaTeX_test.cpp
	../src/HTML/HTMLTree.cpp
	../src/HTML/HTMLTreeInterface.cpp
	../src/HTML/HTMLTreeElement.cpp
	../src/HTML/HTMLTreeElementInterface.cpp
	../src/HTML/HTMLTypes.cpp
	../src/HTML/Microsyntaxes/ASCII.cpp
	../src/HTML/Parse/DetermineCharEncoding.cpp
	../src/HTML/Parse/MagicString.cpp
	../src/HTML/Parse/ParseHTML.cpp
	../src/LaTeX/GenerateLaTeX.cpp
	../src/LaTeX/LaTeXOStream.cpp
	../src/LaTeX/LaTeXTreeInterface.cpp
	../src/LaTeX/UnicodeToLaTeX.cpp
)

add_compile_options (
	-Wno-unused-result
	-Wsign-compare
	-g
	-fstack-protector-strong
	-Wformat
	-Werror=format-security
	-DNDEBUG
	-g
	-fwrapv
	-Wall
	-Wextra
	-std=gnu++17
)


include_directories (${INCLUDE_DIRECTORIES} ../src)


add_executable (tests ${TEST_SOURCES})

target_link_libraries (tests
	libgmock_main
    libgtest
    libgmock
	pthread
)
