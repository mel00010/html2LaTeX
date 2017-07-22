add_library(microsyntaxes_test STATIC "")

target_link_libraries(microsyntaxes_test
	PUBLIC
		microsyntaxes
		ascii_test
		numbers_test
)
target_include_directories(microsyntaxes_test
	PUBLIC
		${PROJECT_SOURCE_DIR}/src
)
add_subdirectory(ASCII)
add_subdirectory(Numbers)
