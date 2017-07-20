cmake_minimum_required (VERSION 2.6)

project (html2LaTeX)

# The version number.
set (html2LaTeX_VERSION_MAJOR 1)
set (html2LaTeX_VERSION_MINOR 0)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

#Subdirectories
add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(docs)

			   
