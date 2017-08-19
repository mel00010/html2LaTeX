add_library(dates_test INTERFACE)

target_sources(dates_test
	INTERFACE
		${CMAKE_CURRENT_SOURCE_DIR}/Dates_test.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/Durations_test.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/FloatingDatesAndTimes_test.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/GlobalDatesAndTimes_test.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/Months_test.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/Times_test.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/TimeZones_test.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/VaguerMomentsInTime_test.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/Weeks_test.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/YearlessDates_test.cpp
	
)
target_link_libraries(dates_test
	INTERFACE
		dates
)