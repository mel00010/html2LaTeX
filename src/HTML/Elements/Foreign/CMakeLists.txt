add_library(Foreign STATIC "")
target_sources(Foreign
	PRIVATE
		Foreign.cpp
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/Foreign.hpp
)
target_link_libraries(Foreign
	PUBLIC
		HTML_types
)