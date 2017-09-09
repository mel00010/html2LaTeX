add_library(foreign STATIC "")
target_sources(foreign
	PRIVATE
		Foreign.cpp
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/Foreign.hpp
)