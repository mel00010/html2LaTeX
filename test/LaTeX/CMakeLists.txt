add_library(LaTeX_test INTERFACE)

target_sources(LaTeX_test
	INTERFACE
		${CMAKE_CURRENT_SOURCE_DIR}/GenerateLaTeX_test.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/LaTeXOStream_test.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/UnicodeToLaTeX_test.cpp	
)
target_link_libraries(LaTeX_test
	INTERFACE
		LaTeX
)
