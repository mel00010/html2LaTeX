add_library(numbers STATIC "")

target_sources(numbers
	PRIVATE
		SignedInteger.cpp
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/SignedInteger.hpp
)
target_include_directories(numbers
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}
		${PROJECT_SOURCE_DIR}/src
)