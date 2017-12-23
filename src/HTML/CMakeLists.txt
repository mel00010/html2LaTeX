add_library(HTML STATIC "")

target_sources(HTML
	PRIVATE
		HTMLTree.cpp
		HTMLTreeInterface.cpp
		HTMLTypes.cpp
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/HTMLTree.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/HTMLTreeInterface.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/HTMLTypes.hpp
)

target_link_libraries(HTML
	PUBLIC
		Elements
		HTML_types
		Microsyntaxes
		Parse
)

add_library(HTML_types STATIC "")
target_sources(HTML_types
	PRIVATE
		HTMLTypes.cpp
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/HTMLTypes.hpp
)
target_include_directories(HTML_types
	PUBLIC
		${PROJECT_SOURCE_DIR}/src
)

add_subdirectory(DOM_Interfaces)
add_subdirectory(Elements)
add_subdirectory(Microsyntaxes)
add_subdirectory(Parse)