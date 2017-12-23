add_library(Parse_test INTERFACE)

target_sources(Parse_test
	INTERFACE
		${CMAKE_CURRENT_SOURCE_DIR}/DetermineCharEncoding_test.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/MagicString_test.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/ParseHTML_test.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/ParseTypes_test.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/ParseUnicode_test.cpp
)
target_link_libraries(Parse_test
	INTERFACE
		Parse
		HTML_types
		Tokenization_test
		TreeConstruction_test
)

add_subdirectory(Tokenization)
add_subdirectory(TreeConstruction)
