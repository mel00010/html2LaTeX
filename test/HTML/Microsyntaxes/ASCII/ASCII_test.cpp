/*******************************************************************************
 * ASCII_test.cpp
 * Copyright (C) 2017  Mel McCalla <melmccalla@gmail.com>
 *
 * This file is part of html2LaTeX.
 *
 * html2LaTeX is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * html2LaTeX is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with html2LaTeX.  If not, see <http://www.gnu.org/licenses/>.
 *******************************************************************************/

#include <gtest/gtest.h>

#include <HTML/Microsyntaxes/ASCII/ASCII.hpp>
#include <HTML/HTMLTypes.hpp>

#include <sstream>
#include <iostream>

namespace HTML {
namespace Microsyntaxes {
namespace ASCII {

TEST(HTML_Microsyntaxes_ASCII, isWhitespace) {
	const char space = ' ';
	const char tab = '\t';
	const char linefeed = '\n';
	const char formfeed = '\f';
	const char carriageReturn = '\r';
	const char other = 'x';

	const std::string trueCase = " \t\n";
	const std::string falseCase = " \t\n x";


	EXPECT_TRUE(isWhitespace(space));
	EXPECT_TRUE(isWhitespace(tab));
	EXPECT_TRUE(isWhitespace(linefeed));
	EXPECT_TRUE(isWhitespace(formfeed));
	EXPECT_TRUE(isWhitespace(carriageReturn));
	EXPECT_FALSE(isWhitespace(other));

	EXPECT_TRUE(isWhitespace(trueCase));
	EXPECT_FALSE(isWhitespace(falseCase));

}

TEST(HTML_Microsyntaxes_ASCII, isUnicodeWhitespace) {
	EXPECT_FALSE(isUnicodeWhitespace('a'));
	EXPECT_FALSE(isUnicodeWhitespace("testString"));
}

TEST(HTML_Microsyntaxes_ASCII, isASCII) {
	const char digit = '0';
	const char upperCaseLetter = 'U';
	const char lowerCaseLetter = 'l';
	const char punctuation = '.';
	const char whitespace = ' ';
	const char other = '\a';

	const std::string trueCase = " sltU2";
	const std::string falseCase = "0Ul\a";

	EXPECT_TRUE(isASCII(digit));
	EXPECT_TRUE(isASCII(upperCaseLetter));
	EXPECT_TRUE(isASCII(lowerCaseLetter));
	EXPECT_TRUE(isASCII(punctuation));
	EXPECT_TRUE(isASCII(whitespace));
	EXPECT_FALSE(isASCII(other));

	EXPECT_TRUE(isASCII(trueCase));
	EXPECT_FALSE(isASCII(falseCase));

}

TEST(HTML_Microsyntaxes_ASCII, isASCIIDigit) {
	const char zero = '0';
	const char one = '1';
	const char two = '2';
	const char three = '3';
	const char four = '4';
	const char five = '5';
	const char six = '6';
	const char seven = '7';
	const char eight = '8';
	const char nine = '9';
	const char other = 'x';

	const std::string trueCase = "0123456789";
	const std::string falseCase = "0234xs";

	EXPECT_TRUE(isASCIIDigit(zero));
	EXPECT_TRUE(isASCIIDigit(one));
	EXPECT_TRUE(isASCIIDigit(two));
	EXPECT_TRUE(isASCIIDigit(three));
	EXPECT_TRUE(isASCIIDigit(four));
	EXPECT_TRUE(isASCIIDigit(five));
	EXPECT_TRUE(isASCIIDigit(six));
	EXPECT_TRUE(isASCIIDigit(seven));
	EXPECT_TRUE(isASCIIDigit(eight));
	EXPECT_TRUE(isASCIIDigit(nine));
	EXPECT_FALSE(isASCIIDigit(other));

	EXPECT_TRUE(isASCIIDigits(trueCase));
	EXPECT_FALSE(isASCIIDigits(falseCase));
}

TEST(HTML_Microsyntaxes_ASCII, isASCIIUpper) {
	const char upperCase = 'A';
	const char lowerCase = 'a';

	const std::string trueCase = "UPPERCASE";
	const std::string falseCase = "lowercase";

	EXPECT_TRUE(isASCIIUpper(upperCase));
	EXPECT_FALSE(isASCIIUpper(lowerCase));

	EXPECT_TRUE(isASCIIUpper(trueCase));
	EXPECT_FALSE(isASCIIUpper(falseCase));
}

TEST(HTML_Microsyntaxes_ASCII, isASCIILower) {
	const char upperCase = 'A';
	const char lowerCase = 'a';

	const std::string trueCase = "lowercase";
	const std::string falseCase = "UPPERCASE";

	EXPECT_TRUE(isASCIILower(lowerCase));
	EXPECT_FALSE(isASCIILower(upperCase));

	EXPECT_TRUE(isASCIILower(trueCase));
	EXPECT_FALSE(isASCIILower(falseCase));
}

TEST(HTML_Microsyntaxes_ASCII, isAlphanumericASCII) {
	const char letter = 'a';
	const char number = '0';
	const char other = '.';

	const std::string trueCase = "trueCase0";
	const std::string falseCase = "falseCase.";

	EXPECT_TRUE(isAlphanumericASCII(letter));
	EXPECT_TRUE(isAlphanumericASCII(number));
	EXPECT_FALSE(isAlphanumericASCII(other));

	EXPECT_TRUE(isAlphanumericASCII(trueCase));
	EXPECT_FALSE(isAlphanumericASCII(falseCase));
}

TEST(HTML_Microsyntaxes_ASCII, isASCIIHex) {
	const char zero = '0';
	const char one = '1';
	const char two = '2';
	const char three = '3';
	const char four = '4';
	const char five = '5';
	const char six = '6';
	const char seven = '7';
	const char eight = '8';
	const char nine = '9';
	const char a = 'a';
	const char b = 'b';
	const char c = 'c';
	const char d = 'd';
	const char e = 'e';
	const char f = 'f';
	const char A = 'A';
	const char B = 'B';
	const char C = 'C';
	const char D = 'D';
	const char E = 'E';
	const char F = 'F';
	const char other = 'x';

	const std::string trueCase = "0123456789abcdefABCDEF";
	const std::string falseCase = "falseCase";

	EXPECT_TRUE(isASCIIHex(zero));
	EXPECT_TRUE(isASCIIHex(one));
	EXPECT_TRUE(isASCIIHex(two));
	EXPECT_TRUE(isASCIIHex(three));
	EXPECT_TRUE(isASCIIHex(four));
	EXPECT_TRUE(isASCIIHex(five));
	EXPECT_TRUE(isASCIIHex(six));
	EXPECT_TRUE(isASCIIHex(seven));
	EXPECT_TRUE(isASCIIHex(eight));
	EXPECT_TRUE(isASCIIHex(nine));
	EXPECT_TRUE(isASCIIHex(a));
	EXPECT_TRUE(isASCIIHex(b));
	EXPECT_TRUE(isASCIIHex(c));
	EXPECT_TRUE(isASCIIHex(d));
	EXPECT_TRUE(isASCIIHex(e));
	EXPECT_TRUE(isASCIIHex(f));
	EXPECT_TRUE(isASCIIHex(A));
	EXPECT_TRUE(isASCIIHex(B));
	EXPECT_TRUE(isASCIIHex(C));
	EXPECT_TRUE(isASCIIHex(D));
	EXPECT_TRUE(isASCIIHex(E));
	EXPECT_TRUE(isASCIIHex(F));
	EXPECT_FALSE(isASCIIHex(other));


	EXPECT_TRUE(isASCIIHex(trueCase));
	EXPECT_FALSE(isASCIIHex(falseCase));
}

TEST(HTML_Microsyntaxes_ASCII, isASCIIHexUpper) {
	const char zero = '0';
	const char one = '1';
	const char two = '2';
	const char three = '3';
	const char four = '4';
	const char five = '5';
	const char six = '6';
	const char seven = '7';
	const char eight = '8';
	const char nine = '9';
	const char A = 'A';
	const char B = 'B';
	const char C = 'C';
	const char D = 'D';
	const char E = 'E';
	const char F = 'F';
	const char other = 'x';

	const std::string trueCase = "0123456789ABCDEF";
	const std::string falseCase = "falseCase";

	EXPECT_TRUE(isASCIIHexUpper(zero));
	EXPECT_TRUE(isASCIIHexUpper(one));
	EXPECT_TRUE(isASCIIHexUpper(two));
	EXPECT_TRUE(isASCIIHexUpper(three));
	EXPECT_TRUE(isASCIIHexUpper(four));
	EXPECT_TRUE(isASCIIHexUpper(five));
	EXPECT_TRUE(isASCIIHexUpper(six));
	EXPECT_TRUE(isASCIIHexUpper(seven));
	EXPECT_TRUE(isASCIIHexUpper(eight));
	EXPECT_TRUE(isASCIIHexUpper(nine));
	EXPECT_TRUE(isASCIIHexUpper(A));
	EXPECT_TRUE(isASCIIHexUpper(B));
	EXPECT_TRUE(isASCIIHexUpper(C));
	EXPECT_TRUE(isASCIIHexUpper(D));
	EXPECT_TRUE(isASCIIHexUpper(E));
	EXPECT_TRUE(isASCIIHexUpper(F));
	EXPECT_FALSE(isASCIIHexUpper(other));

	EXPECT_TRUE(isASCIIHexUpper(trueCase));
	EXPECT_FALSE(isASCIIHexUpper(falseCase));
}

TEST(HTML_Microsyntaxes_ASCII, isASCIIHexLower) {
	const char zero = '0';
	const char one = '1';
	const char two = '2';
	const char three = '3';
	const char four = '4';
	const char five = '5';
	const char six = '6';
	const char seven = '7';
	const char eight = '8';
	const char nine = '9';
	const char a = 'a';
	const char b = 'b';
	const char c = 'c';
	const char d = 'd';
	const char e = 'e';
	const char f = 'f';
	const char other = 'x';

	const std::string trueCase = "0123456789abcdef";
	const std::string falseCase = "falseCase";

	EXPECT_TRUE(isASCIIHexLower(zero));
	EXPECT_TRUE(isASCIIHexLower(one));
	EXPECT_TRUE(isASCIIHexLower(two));
	EXPECT_TRUE(isASCIIHexLower(three));
	EXPECT_TRUE(isASCIIHexLower(four));
	EXPECT_TRUE(isASCIIHexLower(five));
	EXPECT_TRUE(isASCIIHexLower(six));
	EXPECT_TRUE(isASCIIHexLower(seven));
	EXPECT_TRUE(isASCIIHexLower(eight));
	EXPECT_TRUE(isASCIIHexLower(nine));
	EXPECT_TRUE(isASCIIHexLower(a));
	EXPECT_TRUE(isASCIIHexLower(b));
	EXPECT_TRUE(isASCIIHexLower(c));
	EXPECT_TRUE(isASCIIHexLower(d));
	EXPECT_TRUE(isASCIIHexLower(e));
	EXPECT_TRUE(isASCIIHexLower(f));
	EXPECT_FALSE(isASCIIHexLower(other));

	EXPECT_TRUE(isASCIIHexLower(trueCase));
	EXPECT_FALSE(isASCIIHexLower(falseCase));
}

TEST(HTML_Microsyntaxes_ASCII, isASCIINonAlphanumeric) {
	for (const char& i : ASCIINonAlphanumeric) {
		EXPECT_TRUE(isASCIINonAlphanumeric(i));
	}
	for (const char& i : ASCIIAlphanumeric) {
		EXPECT_FALSE(isASCIINonAlphanumeric(i));
	}
	EXPECT_TRUE(isASCIINonAlphanumeric("\n \r\"'"));
	EXPECT_FALSE(isASCIINonAlphanumeric("Alphanumeric0123456789"));
}

TEST(HTML_Microsyntaxes_ASCII, toUpper) {
	EXPECT_EQ('A', toUpper('a'));
	EXPECT_EQ('A', toUpper('A'));
	EXPECT_EQ('0', toUpper('0'));
	EXPECT_EQ('.', toUpper('.'));
	EXPECT_EQ(' ', toUpper(' '));

	EXPECT_EQ(std::string("MIXED CASE WITH SPACES AND PUNCTUATION."), toUpper(std::string("mixed CASE with spaces and punctuation.")));
}

TEST(HTML_Microsyntaxes_ASCII, toLower) {
	EXPECT_EQ('a', toLower('a'));
	EXPECT_EQ('a', toLower('A'));
	EXPECT_EQ('0', toLower('0'));
	EXPECT_EQ('.', toLower('.'));
	EXPECT_EQ(' ', toLower(' '));

	EXPECT_EQ(std::string("mixed case with spaces and punctuation."), toLower(std::string("mixed CASE with spaces and punctuation.")));
}

TEST(HTML_Microsyntaxes_ASCII, caseInsensitiveMatch) {
	EXPECT_TRUE(caseInsensitiveMatch('a', 'a'));
	EXPECT_TRUE(caseInsensitiveMatch('a', 'A'));
	EXPECT_TRUE(caseInsensitiveMatch('.', '.'));
	EXPECT_FALSE(caseInsensitiveMatch('a', 'b'));

	EXPECT_TRUE(caseInsensitiveMatch("TEST STRING.", "test string."));
	EXPECT_TRUE(caseInsensitiveMatch("test String.", "TEST sTRING."));
	EXPECT_TRUE(caseInsensitiveMatch("TEST STRING.", "test string."));
	EXPECT_TRUE(caseInsensitiveMatch("TEST STRING.", "TEST STRING."));
	EXPECT_TRUE(caseInsensitiveMatch("test string.", "test string."));
	EXPECT_FALSE(caseInsensitiveMatch("UPPER CASE.", "lower case."));

}

TEST(HTML_Microsyntaxes_ASCII, istream_skipWhitespace) {
	using iterator = std::istreambuf_iterator<char>;

	std::stringstream spaces("    test stream data");
	std::stringstream lineFeeds("\n\n\n\ntest stream data");
	std::stringstream carriageReturns("\r\r\r\rtest stream data");
	std::stringstream formFeeds("\f\f\f\ftest stream data");
	std::stringstream tabs("\t\t\t\ttest stream data");
	std::stringstream mixed(" \n\t\r\ftest stream data");
	std::stringstream allWhitespace("\n\n\n\n");


	EXPECT_EQ("test stream data", std::string(iterator(skipWhitespace(spaces)), iterator()));
	EXPECT_EQ("test stream data", std::string(iterator(skipWhitespace(lineFeeds)), iterator()));
	EXPECT_EQ("test stream data", std::string(iterator(skipWhitespace(carriageReturns)), iterator()));
	EXPECT_EQ("test stream data", std::string(iterator(skipWhitespace(formFeeds)), iterator()));
	EXPECT_EQ("test stream data", std::string(iterator(skipWhitespace(tabs)), iterator()));
	EXPECT_EQ("test stream data", std::string(iterator(skipWhitespace(mixed)), iterator()));

	EXPECT_THROW(skipWhitespace(allWhitespace), std::istream::failure);
	EXPECT_NO_THROW(skipWhitespace(allWhitespace, true));

}
TEST(HTML_Microsyntaxes_ASCII, string_skipWhitespace) {
	//Testing value of pos because skipWhitespace advances pos until string[pos] is no longer whitespace
	{	// String with whitespace at beginning and pos = 0
		size_t pos = 0;
		std::string testString = " \n\t\f \r Not Whitespace Text";
		skipWhitespace(testString, pos);
		EXPECT_EQ(7, (long ) pos);
	}
	{ // String with whitespace at beginning and pos = 7
		size_t pos = 7;
		std::string testString = " \n\t\f \r Not Whitespace Text";
		skipWhitespace(testString, pos);
		EXPECT_EQ(7, (long ) pos);
	}
	{ // String with whitespace at beginning and pos = 9
		size_t pos = 10;
		std::string testString = " \n\t\f \r Not Whitespace Text";
		skipWhitespace(testString, pos);
		EXPECT_EQ(11, (long ) pos);
	}
	{ // String with whitespace at end and pos = 19
		size_t pos = 19;
		std::string testString = "Not Whitespace Text \n\r\f\t";
		skipWhitespace(testString, pos);
		EXPECT_EQ(24, (long ) pos);
	}
	{ // Empty string and pos = 0
		size_t pos = 0;
		std::string testString = "";
		skipWhitespace(testString, pos);
		EXPECT_EQ(0, (long ) pos);
	}
	{ // Empty string and pos = 1
		size_t pos = 1;
		std::string testString = "";
		skipWhitespace(testString, pos);
		EXPECT_EQ(1, (long ) pos);
	}
}

} /* namespace ASCII */
} /* namespace Microsyntaxes */
} /* namespace HTML */

