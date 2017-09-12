add_library(tokenization STATIC "")
target_sources(tokenization
	PRIVATE
		CharacterReference.cpp
		States.cpp
		Tokenize.cpp
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/CharacterReference.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/States.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/Tokenize.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/TokenizationTypes.hpp
		
)
target_link_libraries(tokenization
	PUBLIC
		ascii
		numbers
		htmltypes	
)