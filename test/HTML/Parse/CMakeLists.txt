add_library(parse_test STATIC "")

target_sources(parse_test
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/DetermineCharEncoding_test.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/MagicString_test.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/ParseHTML_test.cpp
)
target_link_libraries(parse_test
	PUBLIC
		parse
)

target_include_directories(parse_test
	PUBLIC
		${PROJECT_SOURCE_DIR}/src
)