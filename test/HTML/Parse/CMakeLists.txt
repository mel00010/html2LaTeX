add_library(parse_test INTERFACE)

target_sources(parse_test
	INTERFACE
		${CMAKE_CURRENT_SOURCE_DIR}/DetermineCharEncoding_test.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/MagicString_test.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/ParseHTML_test.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/ParseTypes_test.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/ParseUnicode_test.cpp
)
target_link_libraries(parse_test
	INTERFACE
		parse
		htmltypes
		tokenization_test
		treeconstruction_test
)

add_subdirectory(Tokenization)
add_subdirectory(TreeConstruction)
