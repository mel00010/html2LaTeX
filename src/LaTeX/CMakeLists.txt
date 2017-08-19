add_library(latex STATIC "")
target_sources(latex
	PRIVATE
		ConcreteUnicodeToLaTeXConversionArray.hpp
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
