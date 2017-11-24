add_library(escapablerawtext_test INTERFACE)

target_sources(escapablerawtext_test
	INTERFACE
		${CMAKE_CURRENT_SOURCE_DIR}/EscapableRawText_test.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/TextArea_test.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/Title_test.cpp
)
target_link_libraries(escapablerawtext_test
	INTERFACE
		escapablerawtext
)
