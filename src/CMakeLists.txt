add_executable(html2LaTeX "")

target_sources(html2LaTeX
	PRIVATE
		main.cpp
		ProgramOptions.cpp
)

target_link_libraries (html2LaTeX
	boost_program_options
	html
	latex
	pthread
)
target_include_directories(html2LaTeX
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}
		${PROJECT_SOURCE_DIR}/src
)

install(TARGETS html2LaTeX
		RUNTIME DESTINATION bin)


add_subdirectory(HTML)
add_subdirectory(LaTeX)
