add_library(HTML_test INTERFACE)

target_sources(HTML_test
	INTERFACE
		${CMAKE_CURRENT_SOURCE_DIR}/HTMLTree_test.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/HTMLTreeInterface_test.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/HTMLTypes_test.cpp
)
target_link_libraries(HTML_test
	INTERFACE
		Elements
		Elements_test
		HTML
		HTML_types
		Microsyntaxes_test
		Parse_test
)

add_subdirectory(Elements)
add_subdirectory(Microsyntaxes)
add_subdirectory(Parse)