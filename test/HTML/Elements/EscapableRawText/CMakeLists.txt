add_library(EscapableRawText_test INTERFACE)

target_sources(EscapableRawText_test
	INTERFACE
		${CMAKE_CURRENT_SOURCE_DIR}/EscapableRawText_test.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/TextArea_test.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/Title_test.cpp
)
target_link_libraries(EscapableRawText_test
	INTERFACE
		EscapableRawText
)
