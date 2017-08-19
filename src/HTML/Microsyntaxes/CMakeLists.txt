add_library(microsyntaxes STATIC "")

#target_sources(microsyntaxes
#)

target_link_libraries(microsyntaxes
	PUBLIC
		ascii
		numbers
)

#target_include_directories(microsyntaxes
#	PUBLIC
#		${CMAKE_CURRENT_SOURCE_DIR}
#		${PROJECT_SOURCE_DIR}/src
#)
add_subdirectory(ASCII)
add_subdirectory(Numbers)