add_library(Microsyntaxes STATIC "")

#target_sources(microsyntaxes
#)

target_link_libraries(Microsyntaxes
	PUBLIC
		ASCII
		Dates
		Numbers
)

#target_include_directories(microsyntaxes
#	PUBLIC
#		${CMAKE_CURRENT_SOURCE_DIR}
#		${PROJECT_SOURCE_DIR}/src
#)
add_subdirectory(ASCII)
add_subdirectory(Dates)
add_subdirectory(Numbers)