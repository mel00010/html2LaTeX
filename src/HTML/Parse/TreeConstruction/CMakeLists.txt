add_library(treeconstruction STATIC "")
target_sources(treeconstruction
	PRIVATE
		TreeConstructor.cpp
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/TreeConstructor.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/TreeConstructorInterface.hpp
)
target_link_libraries(treeconstruction
	PUBLIC
		ascii
		htmltypes
		tokenization_types
)
