noinst_PROGRAMS = test

test_SOURCES= \
	main_test.cpp \
	\
	\
	HTML/HTMLTree_test.cpp \
	HTML/HTMLTreeInterface_test.cpp \
	\
	HTML/Parse/DetermineCharEncoding_test.cpp \
	HTML/Parse/MagicString_test.cpp \
	HTML/Parse/ParseHTML_test.cpp \
	\
	\
	LaTeX/GenerateLaTeX_test.cpp \
	LaTeX/LaTeXOStream_test.cpp \
	LaTeX/UnicodeToLaTeX_test.cpp \
	\
	\
	\
	../src/HTML/HTMLTree.cpp \
	../src/HTML/HTMLTreeInterface.cpp \
	../src/HTML/HTMLTreeElement.cpp \
	../src/HTML/HTMLTreeElementInterface.cpp \
	../src/HTML/HTMLTypes.cpp \
	\
	../src/HTML/Microsyntaxes/ASCII.cpp \
	\
	../src/HTML/Parse/DetermineCharEncoding.cpp \
	../src/HTML/Parse/MagicString.cpp \
	../src/HTML/Parse/ParseHTML.cpp \
	\
	\
	../src/LaTeX/GenerateLaTeX.cpp \
	../src/LaTeX/LaTeXOStream.cpp \
	../src/LaTeX/LaTeXTreeInterface.cpp \
	../src/LaTeX/UnicodeToLaTeX.cpp
	
	
test_CXXFLAGS= \
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
	-I /usr/local/include \
	-I ../src
	
test_LDFLAGS=  -lpthread -lgmock_main -L/usr/local/lib