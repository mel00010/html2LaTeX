add_library(microsyntaxes_test INTERFACE)

target_link_libraries(microsyntaxes_test
	INTERFACE
		microsyntaxes
		ascii_test
		dates_test
		numbers_test
)
add_subdirectory(ASCII)
add_subdirectory(Dates)
add_subdirectory(Numbers)
