add_library(html STATIC "")

target_sources(html
	PRIVATE
		HTMLTree.cpp
		HTMLTreeInterface.cpp
		HTMLTreeElement.cpp
		HTMLTreeElementInterface.cpp
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/HTMLTree.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/HTMLTreeElement.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/HTMLTreeElementInterface.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/HTMLTreeInterface.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/HTMLTypes.hpp
)
target_include_directories(html
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}
		${PROJECT_SOURCE_DIR}/src
)
target_link_libraries(html
	PUBLIC
		htmltypes
		microsyntaxes
		parse
)

add_library(htmltypes STATIC "")
#message(${CMAKE_CURRENT_SOURCE_DIR})
target_sources(htmltypes
	PRIVATE
		HTMLTypes.cpp
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/HTMLTypes.hpp
)
target_include_directories(htmltypes
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}
		${PROJECT_SOURCE_DIR}/src
)

add_subdirectory(Microsyntaxes)
add_subdirectory(Parse)