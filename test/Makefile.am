noinst_PROGRAMS = test

test_SOURCES= \
	main_test.cpp \
	\
	ParseHTML/DetermineCharEncoding_test.cpp \
	ParseHTML/MagicString_test.cpp \
	\
	../src/ParseHTML/DetermineCharEncoding.cpp \
	../src/ParseHTML/MagicString.cpp
	
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
	
test_LDFLAGS=  -lpthread -lgtest -lgtest_main -L/usr/local/lib