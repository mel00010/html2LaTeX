add_library(ASCII_test INTERFACE)

target_sources(ASCII_test
	INTERFACE
		${CMAKE_CURRENT_SOURCE_DIR}/ASCII_test.cpp
)
target_link_libraries(ASCII_test
	INTERFACE
		ASCII
)
