add_library(Tokenization_test INTERFACE)
target_sources(Tokenization_test
	INTERFACE
		${CMAKE_CURRENT_SOURCE_DIR}/ConsumeCharacterReference_test.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/TokenizerStates_test.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/TokenizationTypes_test.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/Tokenize_test.cpp
)
target_link_libraries(Tokenization_test
	INTERFACE
		ASCII
		HTML_types
		Tokenization
		TreeConstruction
)