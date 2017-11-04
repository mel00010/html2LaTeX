add_library(tokenization STATIC "")
target_sources(tokenization
	PRIVATE
		ConsumeCharacterReference.cpp
		${CMAKE_CURRENT_BINARY_DIR}/CharacterReferences.hpp
		TokenizerStates.cpp
		TokenizationMisc.cpp
		Tokenize.cpp
		TokenizerUtil.cpp
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/Tokenizer.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/TokenizationMisc.hpp
		
)
target_link_libraries(tokenization
	PUBLIC
		ascii
		numbers
		htmltypes
		tokenization_types
		treeconstruction
)
target_include_directories(tokenization 
	PUBLIC
		${CMAKE_CURRENT_BINARY_DIR}
)
add_custom_command(OUTPUT CharacterReferences.hpp
    COMMAND python3 ${PROJECT_SOURCE_DIR}/scripts/generateCharacterReferenceArray.py 
    				${CMAKE_CURRENT_SOURCE_DIR}/CharacterReferences.json 
    				${CMAKE_CURRENT_BINARY_DIR}/CharacterReferences.hpp
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/CharacterReferences.json
)

add_library(tokenization_types STATIC "")
target_sources(tokenization_types
	PRIVATE
		TokenizationTypes.cpp
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/TokenizationTypes.hpp
)
target_link_libraries(tokenization_types
	PUBLIC
		htmltypes
)