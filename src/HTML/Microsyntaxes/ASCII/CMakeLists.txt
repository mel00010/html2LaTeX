add_library(ASCII STATIC "")

target_sources(ASCII
	PRIVATE
		ASCII.cpp
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/ASCII.hpp
)
target_link_libraries(ASCII
	PUBLIC
		HTML_types
)