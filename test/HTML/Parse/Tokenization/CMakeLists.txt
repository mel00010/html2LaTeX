add_library(tokenization_test INTERFACE)
target_sources(tokenization_test
	INTERFACE
		${CMAKE_CURRENT_SOURCE_DIR}/CharacterReference_test.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/States_test.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/TokenizationTypes_test.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/Tokenize_test.cpp
)
target_link_libraries(tokenization_test
	INTERFACE
		ascii
		htmltypes
		tokenization
)