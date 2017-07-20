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
#include <HTML/Microsyntaxes/ASCII.hpp>
#include <HTML/HTMLTypes.hpp>

namespace HTML {
namespace Microsyntaxes {
/**
 * @brief Holds all of the unit tests for the namespace HTML::Microsyntaxes
 */
namespace Microsyntaxes_Test {

TEST(HTML_Microsyntaxes_ASCII, isWhitespace) {
	const char space = ' ';
	const char tab = '\t';
	const char linefeed = '\n';
	const char formfeed = '\f';
	const char carriageReturn = '\r';
	const char other = 'x';

	const std::string trueCase = " \t\n";
	const std::string falseCase = " \t\n x";


	EXPECT_TRUE(HTML::Microsyntaxes::isWhitespace(space));
	EXPECT_TRUE(HTML::Microsyntaxes::isWhitespace(tab));
	EXPECT_TRUE(HTML::Microsyntaxes::isWhitespace(linefeed));
	EXPECT_TRUE(HTML::Microsyntaxes::isWhitespace(formfeed));
	EXPECT_TRUE(HTML::Microsyntaxes::isWhitespace(carriageReturn));
	EXPECT_FALSE(HTML::Microsyntaxes::isWhitespace(other));

	EXPECT_TRUE(HTML::Microsyntaxes::isWhitespace(trueCase));
	EXPECT_FALSE(HTML::Microsyntaxes::isWhitespace(falseCase));

}

TEST(HTML_Microsyntaxes_ASCII, isUnicodeWhitespace) {

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

	EXPECT_TRUE(HTML::Microsyntaxes::isASCII(digit));
	EXPECT_TRUE(HTML::Microsyntaxes::isASCII(upperCaseLetter));
	EXPECT_TRUE(HTML::Microsyntaxes::isASCII(lowerCaseLetter));
	EXPECT_TRUE(HTML::Microsyntaxes::isASCII(punctuation));
	EXPECT_TRUE(HTML::Microsyntaxes::isASCII(whitespace));
	EXPECT_FALSE(HTML::Microsyntaxes::isASCII(other));

	EXPECT_TRUE(HTML::Microsyntaxes::isASCII(trueCase));
	EXPECT_FALSE(HTML::Microsyntaxes::isASCII(falseCase));

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

	EXPECT_TRUE(HTML::Microsyntaxes::isASCIIDigit(zero));
	EXPECT_TRUE(HTML::Microsyntaxes::isASCIIDigit(one));
	EXPECT_TRUE(HTML::Microsyntaxes::isASCIIDigit(two));
	EXPECT_TRUE(HTML::Microsyntaxes::isASCIIDigit(three));
	EXPECT_TRUE(HTML::Microsyntaxes::isASCIIDigit(four));
	EXPECT_TRUE(HTML::Microsyntaxes::isASCIIDigit(five));
	EXPECT_TRUE(HTML::Microsyntaxes::isASCIIDigit(six));
	EXPECT_TRUE(HTML::Microsyntaxes::isASCIIDigit(seven));
	EXPECT_TRUE(HTML::Microsyntaxes::isASCIIDigit(eight));
	EXPECT_TRUE(HTML::Microsyntaxes::isASCIIDigit(nine));
	EXPECT_FALSE(HTML::Microsyntaxes::isASCIIDigit(other));

	EXPECT_TRUE(HTML::Microsyntaxes::isASCIIDigits(trueCase));
	EXPECT_FALSE(HTML::Microsyntaxes::isASCIIDigits(falseCase));
}

TEST(HTML_Microsyntaxes_ASCII, isASCIIUpper) {
	const char upperCase = 'A';
	const char lowerCase = 'a';

	const std::string trueCase = "UPPERCASE";
	const std::string falseCase = "lowercase";

	EXPECT_TRUE(HTML::Microsyntaxes::isASCIIUpper(upperCase));
	EXPECT_FALSE(HTML::Microsyntaxes::isASCIIUpper(lowerCase));

	EXPECT_TRUE(HTML::Microsyntaxes::isASCIIUpper(trueCase));
	EXPECT_FALSE(HTML::Microsyntaxes::isASCIIUpper(falseCase));
}

TEST(HTML_Microsyntaxes_ASCII, isASCIILower) {
	const char upperCase = 'A';
	const char lowerCase = 'a';

	const std::string trueCase = "lowercase";
	const std::string falseCase = "UPPERCASE";

	EXPECT_TRUE(HTML::Microsyntaxes::isASCIILower(lowerCase));
	EXPECT_FALSE(HTML::Microsyntaxes::isASCIILower(upperCase));

	EXPECT_TRUE(HTML::Microsyntaxes::isASCIILower(trueCase));
	EXPECT_FALSE(HTML::Microsyntaxes::isASCIILower(falseCase));
}

TEST(HTML_Microsyntaxes_ASCII, isAlphanumericASCII) {
	const char letter = 'a';
	const char number = '0';
	const char other = '.';

	const std::string trueCase = "trueCase0";
	const std::string falseCase = "falseCase.";

	EXPECT_TRUE(HTML::Microsyntaxes::isAlphanumericASCII(letter));
	EXPECT_TRUE(HTML::Microsyntaxes::isAlphanumericASCII(number));
	EXPECT_FALSE(HTML::Microsyntaxes::isAlphanumericASCII(other));

	EXPECT_TRUE(HTML::Microsyntaxes::isAlphanumericASCII(trueCase));
	EXPECT_FALSE(HTML::Microsyntaxes::isAlphanumericASCII(falseCase));
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

	EXPECT_TRUE(HTML::Microsyntaxes::isASCIIHex(zero));
	EXPECT_TRUE(HTML::Microsyntaxes::isASCIIHex(one));
	EXPECT_TRUE(HTML::Microsyntaxes::isASCIIHex(two));
	EXPECT_TRUE(HTML::Microsyntaxes::isASCIIHex(three));
	EXPECT_TRUE(HTML::Microsyntaxes::isASCIIHex(four));
	EXPECT_TRUE(HTML::Microsyntaxes::isASCIIHex(five));
	EXPECT_TRUE(HTML::Microsyntaxes::isASCIIHex(six));
	EXPECT_TRUE(HTML::Microsyntaxes::isASCIIHex(seven));
	EXPECT_TRUE(HTML::Microsyntaxes::isASCIIHex(eight));
	EXPECT_TRUE(HTML::Microsyntaxes::isASCIIHex(nine));
	EXPECT_TRUE(HTML::Microsyntaxes::isASCIIHex(a));
	EXPECT_TRUE(HTML::Microsyntaxes::isASCIIHex(b));
	EXPECT_TRUE(HTML::Microsyntaxes::isASCIIHex(c));
	EXPECT_TRUE(HTML::Microsyntaxes::isASCIIHex(d));
	EXPECT_TRUE(HTML::Microsyntaxes::isASCIIHex(e));
	EXPECT_TRUE(HTML::Microsyntaxes::isASCIIHex(f));
	EXPECT_TRUE(HTML::Microsyntaxes::isASCIIHex(A));
	EXPECT_TRUE(HTML::Microsyntaxes::isASCIIHex(B));
	EXPECT_TRUE(HTML::Microsyntaxes::isASCIIHex(C));
	EXPECT_TRUE(HTML::Microsyntaxes::isASCIIHex(D));
	EXPECT_TRUE(HTML::Microsyntaxes::isASCIIHex(E));
	EXPECT_TRUE(HTML::Microsyntaxes::isASCIIHex(F));
	EXPECT_FALSE(HTML::Microsyntaxes::isASCIIHex(other));


	EXPECT_TRUE(HTML::Microsyntaxes::isASCIIHex(trueCase));
	EXPECT_FALSE(HTML::Microsyntaxes::isASCIIHex(falseCase));
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

	EXPECT_TRUE(HTML::Microsyntaxes::isASCIIHexUpper(zero));
	EXPECT_TRUE(HTML::Microsyntaxes::isASCIIHexUpper(one));
	EXPECT_TRUE(HTML::Microsyntaxes::isASCIIHexUpper(two));
	EXPECT_TRUE(HTML::Microsyntaxes::isASCIIHexUpper(three));
	EXPECT_TRUE(HTML::Microsyntaxes::isASCIIHexUpper(four));
	EXPECT_TRUE(HTML::Microsyntaxes::isASCIIHexUpper(five));
	EXPECT_TRUE(HTML::Microsyntaxes::isASCIIHexUpper(six));
	EXPECT_TRUE(HTML::Microsyntaxes::isASCIIHexUpper(seven));
	EXPECT_TRUE(HTML::Microsyntaxes::isASCIIHexUpper(eight));
	EXPECT_TRUE(HTML::Microsyntaxes::isASCIIHexUpper(nine));
	EXPECT_TRUE(HTML::Microsyntaxes::isASCIIHexUpper(A));
	EXPECT_TRUE(HTML::Microsyntaxes::isASCIIHexUpper(B));
	EXPECT_TRUE(HTML::Microsyntaxes::isASCIIHexUpper(C));
	EXPECT_TRUE(HTML::Microsyntaxes::isASCIIHexUpper(D));
	EXPECT_TRUE(HTML::Microsyntaxes::isASCIIHexUpper(E));
	EXPECT_TRUE(HTML::Microsyntaxes::isASCIIHexUpper(F));
	EXPECT_FALSE(HTML::Microsyntaxes::isASCIIHexUpper(other));

	EXPECT_TRUE(HTML::Microsyntaxes::isASCIIHexUpper(trueCase));
	EXPECT_FALSE(HTML::Microsyntaxes::isASCIIHexUpper(falseCase));
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

	EXPECT_TRUE(HTML::Microsyntaxes::isASCIIHexLower(zero));
	EXPECT_TRUE(HTML::Microsyntaxes::isASCIIHexLower(one));
	EXPECT_TRUE(HTML::Microsyntaxes::isASCIIHexLower(two));
	EXPECT_TRUE(HTML::Microsyntaxes::isASCIIHexLower(three));
	EXPECT_TRUE(HTML::Microsyntaxes::isASCIIHexLower(four));
	EXPECT_TRUE(HTML::Microsyntaxes::isASCIIHexLower(five));
	EXPECT_TRUE(HTML::Microsyntaxes::isASCIIHexLower(six));
	EXPECT_TRUE(HTML::Microsyntaxes::isASCIIHexLower(seven));
	EXPECT_TRUE(HTML::Microsyntaxes::isASCIIHexLower(eight));
	EXPECT_TRUE(HTML::Microsyntaxes::isASCIIHexLower(nine));
	EXPECT_TRUE(HTML::Microsyntaxes::isASCIIHexLower(a));
	EXPECT_TRUE(HTML::Microsyntaxes::isASCIIHexLower(b));
	EXPECT_TRUE(HTML::Microsyntaxes::isASCIIHexLower(c));
	EXPECT_TRUE(HTML::Microsyntaxes::isASCIIHexLower(d));
	EXPECT_TRUE(HTML::Microsyntaxes::isASCIIHexLower(e));
	EXPECT_TRUE(HTML::Microsyntaxes::isASCIIHexLower(f));
	EXPECT_FALSE(HTML::Microsyntaxes::isASCIIHexLower(other));

	EXPECT_TRUE(HTML::Microsyntaxes::isASCIIHexLower(trueCase));
	EXPECT_FALSE(HTML::Microsyntaxes::isASCIIHexLower(falseCase));
}

TEST(HTML_Microsyntaxes_ASCII, toUpper) {
	EXPECT_EQ('A', HTML::Microsyntaxes::toUpper('a'));
	EXPECT_EQ('A', HTML::Microsyntaxes::toUpper('A'));
	EXPECT_EQ('0', HTML::Microsyntaxes::toUpper('0'));
	EXPECT_EQ('.', HTML::Microsyntaxes::toUpper('.'));
	EXPECT_EQ(' ', HTML::Microsyntaxes::toUpper(' '));

	EXPECT_EQ(std::string("MIXED CASE WITH SPACES AND PUNCTUATION."), HTML::Microsyntaxes::toUpper(std::string("mixed CASE with spaces and punctuation.")));
}

TEST(HTML_Microsyntaxes_ASCII, toLower) {
	EXPECT_EQ('a', HTML::Microsyntaxes::toLower('a'));
	EXPECT_EQ('a', HTML::Microsyntaxes::toLower('A'));
	EXPECT_EQ('0', HTML::Microsyntaxes::toLower('0'));
	EXPECT_EQ('.', HTML::Microsyntaxes::toLower('.'));
	EXPECT_EQ(' ', HTML::Microsyntaxes::toLower(' '));

	EXPECT_EQ(std::string("mixed case with spaces and punctuation."), HTML::Microsyntaxes::toLower(std::string("mixed CASE with spaces and punctuation.")));
}

TEST(HTML_Microsyntaxes_ASCII, caseInsensitiveMatch) {
	EXPECT_TRUE(HTML::Microsyntaxes::caseInsensitiveMatch("TEST STRING.", "test string."));
	EXPECT_TRUE(HTML::Microsyntaxes::caseInsensitiveMatch("test String.", "TEST sTRING."));
	EXPECT_TRUE(HTML::Microsyntaxes::caseInsensitiveMatch("TEST STRING.", "test string."));
	EXPECT_TRUE(HTML::Microsyntaxes::caseInsensitiveMatch("TEST STRING.", "TEST STRING."));
	EXPECT_TRUE(HTML::Microsyntaxes::caseInsensitiveMatch("test string.", "test string."));
	EXPECT_FALSE(HTML::Microsyntaxes::caseInsensitiveMatch("UPPER CASE.", "lower case."));
}
} /* namespace Microsyntaxes_Test */
} /* namespace Microsyntaxes */
} /* namespace HTML */

