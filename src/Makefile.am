bin_PROGRAMS=html2LaTeX


html2LaTeX_SOURCES= \
	main.cpp \
	ProgramOptions.cpp \
	\
	ParseHTML/DetermineCharEncoding.cpp \
	ParseHTML/MagicString.cpp

include_HEADERS = \
	ProgramOptions.hpp \
	\
	ParseHTML/DetermineCharEncoding.hpp \
	ParseHTML/MagicString.hpp
	
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
	
