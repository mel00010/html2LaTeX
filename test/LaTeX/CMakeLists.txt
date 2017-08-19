add_library(latex_test INTERFACE)

target_sources(latex_test
	INTERFACE
		${CMAKE_CURRENT_SOURCE_DIR}/GenerateLaTeX_test.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/LaTeXOStream_test.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/UnicodeToLaTeX_test.cpp	
)
target_link_libraries(latex_test
	INTERFACE
		latex
)
