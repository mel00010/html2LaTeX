add_executable(html2LaTeX "")

target_sources(html2LaTeX
	PRIVATE
		main.cpp
		ProgramOptions.cpp
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/ProgramOptions.hpp
)

target_link_libraries (html2LaTeX
	boost_program_options
	HTML
	LaTeX
	pthread
)


install(TARGETS html2LaTeX
		RUNTIME DESTINATION bin)


add_subdirectory(HTML)
add_subdirectory(LaTeX)
