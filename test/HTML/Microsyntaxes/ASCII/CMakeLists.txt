add_library(ascii_test STATIC "")

target_sources(ascii_test
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/ASCII_test.cpp
)
target_link_libraries(ascii_test
	PUBLIC
		ascii
)
target_include_directories(ascii_test
	PUBLIC
		${PROJECT_SOURCE_DIR}/src
)