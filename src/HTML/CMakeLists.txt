add_library(html STATIC "")

target_sources(html
	PRIVATE
		HTMLTree.cpp
		HTMLTreeInterface.cpp
		HTMLTypes.cpp
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/HTMLTree.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/HTMLTreeInterface.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/HTMLTypes.hpp
)

target_link_libraries(html
	PUBLIC
		elements
		htmltypes
		microsyntaxes
		parse
)

add_library(htmltypes STATIC "")
target_sources(htmltypes
	PRIVATE
		HTMLTypes.cpp
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/HTMLTypes.hpp
)
target_include_directories(htmltypes
	PUBLIC
		${PROJECT_SOURCE_DIR}/src
)

add_subdirectory(Elements)
add_subdirectory(Microsyntaxes)
add_subdirectory(Parse)