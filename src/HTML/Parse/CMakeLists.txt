add_library(Parse STATIC "")

target_sources(Parse
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
target_link_libraries(Parse
	PUBLIC
		ASCII
		HTML_types
		Tokenization
		TreeConstruction
		gtest
)
add_subdirectory(Tokenization)
add_subdirectory(TreeConstruction)