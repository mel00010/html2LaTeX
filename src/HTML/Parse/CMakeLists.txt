add_library(parse STATIC "")

target_sources(parse
	PRIVATE
		DetermineCharEncoding.cpp
		MagicString.cpp
		ParseHTML.cpp
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/DetermineCharEncoding.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/MagicString.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/ParseHTML.hpp
)
target_link_libraries(parse
	PUBLIC
		ascii
		htmltypes
		tokenization
		treeconstruction
)
#target_include_directories(parse
#	PUBLIC
#		${CMAKE_CURRENT_SOURCE_DIR}
#		${PROJECT_SOURCE_DIR}/src
#)
add_subdirectory(Tokenization)
add_subdirectory(TreeConstruction)