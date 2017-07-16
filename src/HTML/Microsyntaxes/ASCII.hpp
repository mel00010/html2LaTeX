/*******************************************************************************
 * ASCII.hpp
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
#ifndef HTML_MICROSYNTAXES_ASCII_HPP_
#define HTML_MICROSYNTAXES_ASCII_HPP_

#include <string>

namespace HTML {
namespace Microsyntaxes {

/**
 * @brief An array containing all of the ASCII letters
 * @showinitializer
 */
constexpr char ASCIILetters[52] = {
		'A',
		'B',
		'C',
		'D',
		'E',
		'F',
		'G',
		'H',
		'I',
		'J',
		'K',
		'L',
		'M',
		'N',
		'O',
		'P',
		'Q',
		'R',
		'S',
		'T',
		'U',
		'V',
		'W',
		'X',
		'Y',
		'Z',
		'a',
		'b',
		'c',
		'd',
		'e',
		'f',
		'g',
		'h',
		'i',
		'j',
		'k',
		'l',
		'm',
		'n',
		'o',
		'p',
		'q',
		'r',
		's',
		't',
		'u',
		'v',
		'w',
		'x',
		'y',
		'z'
};

/**
 * @brief An array containing all of the ASCII upper case letters
 * @showinitializer
 */
constexpr char ASCIIUpper[26] = {
		'A',
		'B',
		'C',
		'D',
		'E',
		'F',
		'G',
		'H',
		'I',
		'J',
		'K',
		'L',
		'M',
		'N',
		'O',
		'P',
		'Q',
		'R',
		'S',
		'T',
		'U',
		'V',
		'W',
		'X',
		'Y',
		'Z'
};

/**
 * @brief An array containing all of the ASCII lower case letters
 * @showinitializer
 */
constexpr char ASCIILower[26] = {
		'a',
		'b',
		'c',
		'd',
		'e',
		'f',
		'g',
		'h',
		'i',
		'j',
		'k',
		'l',
		'm',
		'n',
		'o',
		'p',
		'q',
		'r',
		's',
		't',
		'u',
		'v',
		'w',
		'x',
		'y',
		'z'
};

/**
 * @brief An array containing all of the ASCII upper case, lower case, and numeric characters
 * @showinitializer
 */
constexpr char ASCIIAlphanumeric[62] = {
		'A',
		'B',
		'C',
		'D',
		'E',
		'F',
		'G',
		'H',
		'I',
		'J',
		'K',
		'L',
		'M',
		'N',
		'O',
		'P',
		'Q',
		'R',
		'S',
		'T',
		'U',
		'V',
		'W',
		'X',
		'Y',
		'Z',
		'a',
		'b',
		'c',
		'd',
		'e',
		'f',
		'g',
		'h',
		'i',
		'j',
		'k',
		'l',
		'm',
		'n',
		'o',
		'p',
		'q',
		'r',
		's',
		't',
		'u',
		'v',
		'w',
		'x',
		'y',
		'z',
		'0',
		'1',
		'2',
		'3',
		'4',
		'5',
		'6',
		'7',
		'8',
		'9'
};

/**
 * @brief An array containing all of the ASCII numerals and the upper and lower case letters A through F
 * @showinitializer
 */
constexpr char ASCIIHex[22] = {
		'0',
		'1',
		'2',
		'3',
		'4',
		'5',
		'6',
		'7',
		'8',
		'9',
		'A',
		'B',
		'C',
		'D',
		'E',
		'F',
		'a',
		'b',
		'c',
		'd',
		'e',
		'f',

};

/**
 * @brief An array containing all of the ASCII numerals and the uppercase letters A through F
 * @showinitializer
 */
constexpr char ASCIIHexUpper[16] = {
		'0',
		'1',
		'2',
		'3',
		'4',
		'5',
		'6',
		'7',
		'8',
		'9',
		'A',
		'B',
		'C',
		'D',
		'E',
		'F'
};

/**
 * @brief An array containing all of the ASCII numerals and the lowercase letters A through F
 * @showinitializer
 */
constexpr char ASCIIHexLower[16] = {
		'0',
		'1',
		'2',
		'3',
		'4',
		'5',
		'6',
		'7',
		'8',
		'9',
		'a',
		'b',
		'c',
		'd',
		'e',
		'f'
};

/**
 * @brief An array containing all of the ASCII numerals
 * @showinitializer
 */
constexpr char ASCIIDigit[10] = {
		'0',
		'1',
		'2',
		'3',
		'4',
		'5',
		'6',
		'7',
		'8',
		'9'
};


/**
 * @brief An array containing all of the space characters
 *
 * The space characters are U+0020 SPACE, "tab" (U+0009), "LF" (U+000A), "FF" (U+000C), and "CR" (U+000D).
 * @showinitializer
 */
constexpr char ASCIIWhitespace[5] = {
		' ',
		'\t',
		'\n',
		'\f',
		'\r'
};
/**
 * @brief An array containing all of ASCII
 * @showinitializer
 */
constexpr char ASCII[128] = {
		'\n',
		'\t',
		'\f',
		'\r',
		' ',
		'!',
		'"',
		'#',
		'$',
		'%',
		'&',
		'\'',
		'(',
		')',
		'*',
		'+',
		',',
		'-',
		'.',
		'/',
		'0',
		'1',
		'2',
		'3',
		'4',
		'5',
		'6',
		'7',
		'8',
		'9',
		':',
		';',
		'<',
		'=',
		'>',
		'?',
		'@',
		'A',
		'B',
		'C',
		'D',
		'E',
		'F',
		'G',
		'H',
		'I',
		'J',
		'K',
		'L',
		'M',
		'N',
		'O',
		'P',
		'Q',
		'R',
		'S',
		'T',
		'U',
		'V',
		'W',
		'X',
		'Y',
		'Z',
		'[',
		'\\',
		']',
		'^',
		'_',
		'`',
		'a',
		'b',
		'c',
		'd',
		'e',
		'f',
		'g',
		'h',
		'i',
		'j',
		'k',
		'l',
		'm',
		'n',
		'o',
		'p',
		'q',
		'r',
		's',
		't',
		'u',
		'v',
		'w',
		'x',
		'y',
		'z',
		'{',
		'|',
		'}',
		'~'
};


/**
 * @brief Tests if a character is whitespace
 * @param character Character to test
 * @return Returns true if character is whitespace, false if it is not
 * @see ASCIIWhitespace
 */
bool isWhitespace(const char& character);

/**
 * @brief Tests if a string is whitespace
 * @param string String to test
 * @return Returns true if string is whitespace, false if it is not
 * @see ASCIIWhitespace
 */
bool isWhitespace(const std::string& string);



/**
 * @brief Tests if a character is unicode whitespace
 * @param character Character to test
 * @return Returns true if character is unicode whitespace, false if it is not
 */
bool isUnicodeWhitespace(const char& character);

/**
 * @brief Tests if a string is unicode whitespace
 * @param string String to test
 * @return Returns true if string is unicode whitespace, false if it is not
 */
bool isUnicodeWhitespace(const std::string& string);

/**
 *
 * @param character
 * @return
 */
bool isASCII(const char& character);
/**
 *
 * @param string
 * @return
 */
bool isASCII(const std::string& string);

/**
 *
 * @param character
 * @return
 */
bool isASCIIDigit(const char& character);
/**
 *
 * @param string
 * @return
 */
bool isASCIIDigits(const std::string& string);

/**
 * @brief Tests if a byte is an ASCII upper case letter
 * @param character A reference to the byte to be tested
 * @return If the byte is an ASCII upper case letter, the function returns true.
 * 		   Otherwise, the function returns false.
 *
 * @test HTML::Microsyntaxes::Microsyntaxes_Test::TEST_F(HTML_Microsyntaxes_isASCIIUpper_Test, trueCase)
 * @test HTML::Microsyntaxes::Microsyntaxes_Test::TEST_F(HTML_Microsyntaxes_isASCIIUpper_Test, falseCase)
 */
bool isASCIIUpper(const char& character);
/**
 *
 * @param string
 * @return
 */
bool isASCIIUpper(const std::string& string);

/**
 *
 * @param character
 * @return
 */
bool isASCIILower(const char& character);
/**
 *
 * @param string
 * @return
 */
bool isASCIILower(const std::string& string);

/**
 *
 * @param character
 * @return
 */
bool isAlphanumericASCII(const char& character);
/**
 *
 * @param string
 * @return
 */
bool isAlphanumericASCII(const std::string& string);

/**
 *
 * @param character
 * @return
 */
bool isASCIIHex(const char& character);
/**
 *
 * @param string
 * @return
 */
bool isASCIIHex(const std::string& string);

/**
 *
 * @param character
 * @return
 */
bool isASCIIHexUpper(const char& character);
/**
 *
 * @param string
 * @return
 */
bool isASCIIHexUpper(const std::string& string);

/**
 *
 * @param character
 * @return
 */
bool isASCIIHexLower(const char& character);
/**
 *
 * @param string
 * @return
 */
bool isASCIIHexLower(const std::string& string);

/**
 *
 * @param character
 * @return
 */
char toUpper(const char& character);
/**
 *
 * @param string
 * @return
 */
std::string toUpper(const std::string& string);

/**
 *
 * @param character
 * @return
 */
char toLower(const char& character);
/**
 *
 * @param string
 * @return
 */
std::string toLower(const std::string& string);

} /* namespace Microsyntaxes */
} /* namespace HTML */



#endif /* HTML_MICROSYNTAXES_ASCII_HPP_ */
