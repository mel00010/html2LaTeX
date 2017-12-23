add_library(Tokenization STATIC "")
target_sources(Tokenization
	PRIVATE
		ConsumeCharacterReference.cpp
		${CMAKE_CURRENT_BINARY_DIR}/CharacterReferences.hpp
		TokenizerStates.cpp
		Tokenize.cpp
		TokenizerUtil.cpp
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/Tokenizer.hpp		
)
target_link_libraries(Tokenization
	PUBLIC
		ASCII
		Numbers
		HTML_types
		Tokenization_types
		TreeConstruction
)
target_include_directories(Tokenization 
	PUBLIC
		${CMAKE_CURRENT_BINARY_DIR}
)
add_custom_command(OUTPUT CharacterReferences.hpp
    COMMAND python3 ${PROJECT_SOURCE_DIR}/scripts/generateCharacterReferenceArray.py 
    				${CMAKE_CURRENT_SOURCE_DIR}/CharacterReferences.json 
    				${CMAKE_CURRENT_BINARY_DIR}/CharacterReferences.hpp
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/CharacterReferences.json
)

add_library(Tokenization_types STATIC "")
target_sources(Tokenization_types
	PRIVATE
		TokenizationTypes.cpp
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/TokenizationTypes.hpp
)
target_link_libraries(Tokenization_types
	PUBLIC
		HTML_types
)