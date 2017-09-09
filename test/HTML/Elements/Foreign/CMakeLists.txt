add_library(foreign_test INTERFACE)

target_sources(foreign_test
	INTERFACE
		${CMAKE_CURRENT_SOURCE_DIR}/Foreign_test.cpp
)
target_link_libraries(foreign_test
	INTERFACE
		foreign
)
