add_library(numbers STATIC "")

target_sources(numbers
	PRIVATE
		Dimension.cpp
		FloatingPoint.cpp
		ListsOfDimensions.cpp
		ListsOfIntegers.cpp
		NonNegativeInteger.cpp
		NumbersMisc.cpp
		NumbersTypes.cpp
		SignedInteger.cpp
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/Dimension.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/FloatingPoint.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/ListsOfDimensions.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/ListsOfIntegers.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/NonNegativeInteger.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/NumbersMisc.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/NumbersTypes.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/SignedInteger.hpp
)
target_link_libraries(numbers
	PUBLIC
		ascii
		htmltypes
)
#target_include_directories(numbers
#	PUBLIC
#		${CMAKE_CURRENT_SOURCE_DIR}
#		${PROJECT_SOURCE_DIR}/src
#)