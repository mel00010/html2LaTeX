add_library(Foreign_test INTERFACE)

target_sources(Foreign_test
	INTERFACE
		${CMAKE_CURRENT_SOURCE_DIR}/Foreign_test.cpp
)
target_link_libraries(Foreign_test
	INTERFACE
		Foreign
)
