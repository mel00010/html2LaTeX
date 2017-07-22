add_library(latex_test STATIC "")

target_sources(latex_test
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/GenerateLaTeX_test.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/LaTeXOStream_test.cpp
		${CMAKE_CURRENT_SOURCE_DIR}/UnicodeToLaTeX_test.cpp
)
target_link_libraries(latex_test
	PUBLIC
		latex
)
target_include_directories(latex
	PUBLIC
		${PROJECT_SOURCE_DIR}/src
)