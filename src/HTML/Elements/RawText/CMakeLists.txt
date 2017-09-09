add_library(rawtext STATIC "")
target_sources(rawtext
	PRIVATE
		RawText.cpp
		Script.cpp
		Style.cpp
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/RawText.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/Script.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/Style.hpp
)
target_link_libraries(rawtext
	PUBLIC
		htmltypes
)