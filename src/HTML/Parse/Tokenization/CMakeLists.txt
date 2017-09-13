add_library(tokenization STATIC "")
target_sources(tokenization
	PRIVATE
		CharacterReference.cpp
		States.cpp
		Tokenize.cpp
		TokenizationMisc.cpp
		TokenizationTypes.cpp
		${CMAKE_CURRENT_BINARY_DIR}/CharacterReferences.ipp
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/CharacterReference.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/States.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/Tokenize.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/TokenizationMisc.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/TokenizationTypes.hpp
		
)
target_link_libraries(tokenization
	PUBLIC
		ascii
		numbers
		htmltypes	
)
target_include_directories(tokenization 
	PUBLIC
		${CMAKE_CURRENT_BINARY_DIR}
)
add_custom_command(OUTPUT CharacterReferences.ipp
    COMMAND python3 ${PROJECT_SOURCE_DIR}/scripts/generateCharacterReferenceArray.py 
    				${CMAKE_CURRENT_SOURCE_DIR}/CharacterReferences.json 
    				${CMAKE_CURRENT_BINARY_DIR}/CharacterReferences.ipp
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/CharacterReferences.json
)