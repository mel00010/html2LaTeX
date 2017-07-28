add_library(numbers STATIC "")

target_sources(numbers
	PRIVATE
		NonNegativeInteger.cpp
		NumbersMisc.cpp
		NumbersTypes.cpp
		SignedInteger.cpp
	PUBLIC
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
target_include_directories(numbers
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}
		${PROJECT_SOURCE_DIR}/src
)