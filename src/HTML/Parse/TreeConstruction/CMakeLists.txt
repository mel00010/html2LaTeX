add_library(TreeConstruction STATIC "")
target_sources(TreeConstruction
	PRIVATE
		TreeConstructor.cpp
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/TreeConstructor.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/TreeConstructorInterface.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/TreeConstructionTypes.hpp
)
target_link_libraries(TreeConstruction
	PUBLIC
		ASCII
		Elements
		HTML_types
		Tokenization_types
)
