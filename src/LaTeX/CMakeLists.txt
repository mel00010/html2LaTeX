add_library(latex STATIC "")
target_sources(latex
	PRIVATE
		${CMAKE_CURRENT_BINARY_DIR}/UnicodeToLaTeXConversionArray.ipp
		GenerateLaTeX.cpp
		LaTeXOStream.cpp
		LaTeXTreeInterface.cpp
		UnicodeToLaTeX.cpp
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/GenerateLaTeX.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/LaTeXOStream.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/LaTeXTypes.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/UnicodeToLaTeX.hpp
		${CMAKE_CURRENT_SOURCE_DIR}/UnicodeToLaTeXInterface.hpp

)
add_custom_command(OUTPUT UnicodeToLaTeXConversionArray.ipp
    COMMAND python3 ${PROJECT_SOURCE_DIR}/scripts/generateConversionArray.py 
    				${CMAKE_CURRENT_SOURCE_DIR}/UnicodeToLaTeXConversionArray.json 
    				${CMAKE_CURRENT_BINARY_DIR}/UnicodeToLaTeXConversionArray.ipp
    DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/UnicodeToLaTeXConversionArray.json
)
target_include_directories(latex 
	PUBLIC
		${CMAKE_CURRENT_BINARY_DIR}
)