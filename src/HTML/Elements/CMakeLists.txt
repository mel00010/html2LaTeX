add_library(elements STATIC "")
target_sources(elements
	PRIVATE
		Element.cpp
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/Element.hpp
)
target_link_libraries(elements
	PUBLIC
		escapablerawtext
		foreign
		htmltypes
		normal
		rawtext
		void
)
add_subdirectory(EscapableRawText)
add_subdirectory(Foreign)
add_subdirectory(Normal)
add_subdirectory(RawText)
add_subdirectory(Void)