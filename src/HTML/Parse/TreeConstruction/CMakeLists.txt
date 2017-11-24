add_library(treeconstruction STATIC "")
target_sources(treeconstruction
	PRIVATE
		Dispatch.cpp
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/Dispatch.hpp
)
target_link_libraries(treeconstruction
	PUBLIC
		ascii
		htmltypes
		tokenization_types
)
