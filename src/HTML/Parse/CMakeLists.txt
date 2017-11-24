add_library(parse STATIC "")

target_sources(parse
	PRIVATE
		DetermineCharEncoding.cpp
		MagicString.cpp
		ParseHTML.cpp
		ParseTypes.cpp
		ParseUnicode.cpp
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/DetermineCharEncoding.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/MagicString.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/ParseHTML.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/ParseTypes.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/ParseUnicode.hpp
)
target_link_libraries(parse
	PUBLIC
		ascii
		htmltypes
		tokenization
		treeconstruction
)
add_subdirectory(Tokenization)
add_subdirectory(TreeConstruction)