add_library(html_test INTERFACE)

target_sources(html_test
	INTERFACE
		${CMAKE_CURRENT_SOURCE_DIR}/HTMLTree_test.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/HTMLTreeInterface_test.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/HTMLTypes_test.cpp
)
target_link_libraries(html_test
	INTERFACE
		elements
		elements_test
		html
		htmltypes
		microsyntaxes_test
		parse_test
)

add_subdirectory(Elements)
add_subdirectory(Microsyntaxes)
add_subdirectory(Parse)