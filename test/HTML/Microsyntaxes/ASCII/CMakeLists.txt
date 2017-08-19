add_library(ascii_test INTERFACE)

target_sources(ascii_test
	INTERFACE
		${CMAKE_CURRENT_SOURCE_DIR}/ASCII_test.cpp
)
target_link_libraries(ascii_test
	INTERFACE
		ascii
)
