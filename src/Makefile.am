bin_PROGRAMS=html2LaTeX


html2LaTeX_SOURCES= \
	main.cpp \
	ProgramOptions.cpp \
	\
	\
	HTML/HTMLTree.cpp \
	HTML/HTMLTreeInterface.cpp \
	HTML/HTMLTreeElement.cpp \
	HTML/HTMLTreeElementInterface.cpp \
	HTML/HTMLTypes.cpp \
	\
	HTML/Microsyntaxes/ASCII.cpp \
	HTML/Microsyntaxes/SignedInteger.cpp \
	\
	HTML/Parse/DetermineCharEncoding.cpp \
	HTML/Parse/MagicString.cpp \
	HTML/Parse/ParseHTML.cpp \
	\
	\
	LaTeX/GenerateLaTeX.cpp \
	LaTeX/LaTeXOStream.cpp \
	LaTeX/LaTeXTreeInterface.cpp \
	LaTeX/UnicodeToLaTeX.cpp 
	
include_HEADERS = \
	ProgramOptions.hpp \
	\
	\
	HTML/HTMLTree.hpp \
	HTML/HTMLTreeInterface.hpp \
	HTML/HTMLTreeElement.hpp \
	HTML/HTMLTreeElementInterface.hpp \
	HTML/HTMLTypes.hpp \
	\
	HTML/Microsyntaxes/ASCII.hpp \
	HTML/Microsyntaxes/SignedInteger.hpp \
	\
	HTML/Parse/DetermineCharEncoding.hpp \
	HTML/Parse/MagicString.hpp \
	HTML/Parse/ParseHTML.hpp \
	\
	\
	LaTeX/ConcreteUnicodeToLaTeX.hpp \
	LaTeX/ConcreteUnicodeToLaTeXConversionArray.hpp \
	LaTeX/GenerateLaTeX.hpp \
	LaTeX/LaTeXOStream.hpp \
	LaTeX/LaTeXTreeInterface.hpp \
	LaTeX/LaTeXTypes.hpp \
	LaTeX/UnicodeToLaTeX.hpp
	
html2LaTeX_CXXFLAGS= \
	-Wno-unused-result \
	-Wsign-compare \
	-g \
	-fstack-protector-strong \
	-Wformat \
	-Werror=format-security \
	-DNDEBUG \
	-g \
	-fwrapv \
	-Wall \
	-Wextra \
	-std=gnu++11 \
	-I /usr/local/include
	
html2LaTeX_LDFLAGS= \
	-L/usr/local/lib/ \
	-lboost_program_options \
	-lpthread
	
