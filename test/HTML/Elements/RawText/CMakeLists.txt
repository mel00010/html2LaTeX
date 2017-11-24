add_library(rawtext_test INTERFACE)

target_sources(rawtext_test
	INTERFACE
		${CMAKE_CURRENT_SOURCE_DIR}/RawText_test.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/Script_test.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/Style_test.cpp
)
target_link_libraries(rawtext_test
	INTERFACE
		rawtext
)
