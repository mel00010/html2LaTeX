find_package (Boost 1.65 COMPONENTS program_options REQUIRED)

set (HTML2LATEX_SRCS
	main.cpp
	ProgramOptions.cpp
	HTML/HTMLTree.cpp
	HTML/HTMLTreeInterface.cpp
	HTML/HTMLTreeElement.cpp
	HTML/HTMLTreeElementInterface.cpp
	HTML/HTMLTypes.cpp
	HTML/Microsyntaxes/ASCII.cpp
	HTML/Microsyntaxes/SignedInteger.cpp
	HTML/Parse/DetermineCharEncoding.cpp
	HTML/Parse/MagicString.cpp
	HTML/Parse/ParseHTML.cpp
	LaTeX/GenerateLaTeX.cpp
	LaTeX/LaTeXOStream.cpp
	LaTeX/LaTeXTreeInterface.cpp
	LaTeX/UnicodeToLaTeX.cpp 
)

add_executable (html2LaTeX ${HTML2LATEX_SRCS})
target_link_libraries (html2LaTeX
	boost_program_options
	pthread
)