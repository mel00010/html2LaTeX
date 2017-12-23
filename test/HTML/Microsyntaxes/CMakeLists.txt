add_library(Microsyntaxes_test INTERFACE)

target_link_libraries(Microsyntaxes_test
	INTERFACE
		Microsyntaxes
		ASCII_test
		Dates_test
		Numbers_test
)
add_subdirectory(ASCII)
add_subdirectory(Dates)
add_subdirectory(Numbers)
