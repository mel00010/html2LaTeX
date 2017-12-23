add_library(Numbers_test INTERFACE)

target_sources(Numbers_test
	INTERFACE
		${CMAKE_CURRENT_SOURCE_DIR}/Dimension_test.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/FloatingPoint_test.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/ListsOfDimensions_test.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/ListsOfIntegers_test.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/NonNegativeInteger_test.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/NumbersTypes_test.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/NumbersMisc_test.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/SignedInteger_test.cpp
)
target_link_libraries(Numbers_test
	INTERFACE
		Numbers
)