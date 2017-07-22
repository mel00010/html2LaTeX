add_library(html_test STATIC "")

target_sources(html_test
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/HTMLTree_test.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/HTMLTreeElement_test.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/HTMLTreeInterface_test.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/HTMLTypes_test.cpp
)
target_link_libraries(html_test
	PUBLIC
		html
		htmltypes
		microsyntaxes_test
		parse_test
)
target_include_directories(html_test
	PUBLIC
		${PROJECT_SOURCE_DIR}/src
)

add_subdirectory(Microsyntaxes)
add_subdirectory(Parse)