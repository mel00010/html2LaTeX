add_library(numbers_test STATIC "")

target_sources(numbers_test
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/NumbersTypes_test.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/SignedInteger_test.cpp
)
target_link_libraries(numbers_test
	PUBLIC
		numbers
)
target_include_directories(numbers_test
	PUBLIC
		${PROJECT_SOURCE_DIR}/src
)