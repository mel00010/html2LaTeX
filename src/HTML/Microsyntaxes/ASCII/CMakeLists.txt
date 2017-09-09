add_library(ascii STATIC "")

target_sources(ascii
	PRIVATE
		ASCII.cpp
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/ASCII.hpp
)
target_link_libraries(ascii
	PUBLIC
		htmltypes
)