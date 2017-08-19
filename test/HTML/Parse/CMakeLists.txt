add_library(parse_test INTERFACE)

target_sources(parse_test
	INTERFACE
		${CMAKE_CURRENT_SOURCE_DIR}/DetermineCharEncoding_test.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/MagicString_test.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/ParseHTML_test.cpp
)
target_link_libraries(parse_test
	INTERFACE
		parse
)
