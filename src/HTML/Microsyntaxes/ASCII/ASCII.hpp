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

#include <iostream>
#include <string>

namespace HTML {
namespace Microsyntaxes {

#define EOF32 ((char32_t) 0xFFFFFFFF)
#define EOF16 ((char16_t) 0xFFFF)
#define EOF8  ((char) 0xFF)

/**
 * @brief Holds functions related to parsing and manipulating ASCII text.
 */
namespace ASCII {
/**
 * @brief An array containing all of the ASCII letters
 * @showinitializer
 */
constexpr char32_t ASCIILettersUTF32[52] = {
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
 * Expands to a sequence of case statements from A to Z, for use in a switch statement.
 *
 * Example usage:
 * switch(a) {
 * 		// Beginning of switch block
 * 		case ASCII_UPPER_CASE_LETTER:
 * 			break;
 * 		// Rest of switch block
 * }
 */
#define ASCII_UPPER_CASE_LETTER \
	'A':                        \
	case 'B':                   \
	case 'C':                   \
	case 'D':                   \
	case 'E':                   \
	case 'F':                   \
	case 'G':                   \
	case 'H':                   \
	case 'I':                   \
	case 'J':                   \
	case 'K':                   \
	case 'L':                   \
	case 'M':                   \
	case 'N':                   \
	case 'O':                   \
	case 'P':                   \
	case 'Q':                   \
	case 'R':                   \
	case 'S':                   \
	case 'T':                   \
	case 'U':                   \
	case 'V':                   \
	case 'W':                   \
	case 'X':                   \
	case 'Y':                   \
	case 'Z'


/**
 * @brief An array containing all of the ASCII upper case letters
 * @showinitializer
 */
constexpr char32_t ASCIIUpperUTF32[26] = {
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
 * Expands to a sequence of case statements from a to z, for use in a switch statement.
 *
 * Example usage:
 * switch(a) {
 * 		// Beginning of switch block
 * 		case ASCII_LOWER_CASE_LETTER:
 * 			break;
 * 		// Rest of switch block
 * }
 */
#define ASCII_LOWER_CASE_LETTER \
	'A':                        \
	case 'B':                   \
	case 'C':                   \
	case 'D':                   \
	case 'E':                   \
	case 'F':                   \
	case 'G':                   \
	case 'H':                   \
	case 'I':                   \
	case 'J':                   \
	case 'K':                   \
	case 'L':                   \
	case 'M':                   \
	case 'N':                   \
	case 'O':                   \
	case 'P':                   \
	case 'Q':                   \
	case 'R':                   \
	case 'S':                   \
	case 'T':                   \
	case 'U':                   \
	case 'V':                   \
	case 'W':                   \
	case 'X':                   \
	case 'Y':                   \
	case 'Z'

/**
 * @brief An array containing all of the ASCII lower case letters
 * @showinitializer
 */
constexpr char32_t ASCIILowerUTF32[26] = {
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
constexpr char32_t ASCIIAlphanumericUTF32[62] = {
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
constexpr char32_t ASCIIHexUTF32[22] = {
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
		'f'
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
		'f'
};

/**
 * @brief An array containing all of the ASCII numerals and the uppercase letters A through F
 * @showinitializer
 */
constexpr char32_t ASCIIHexUpperUTF32[16] = {
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
constexpr char32_t ASCIIHexLowerUTF32[16] = {
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
 * @brief An array holding all of the ASCII characters that are not alphanumeric.
 * @showinitializer
 */
constexpr char32_t ASCIINonAlphanumericUTF32[66] = {
		'\x00',
		'\x01',
		'\x02',
		'\x03',
		'\x04',
		'\x05',
		'\x06',
		'\a',
		'\b',
		'\t',
		'\n',
		'\v',
		'\f',
		'\r',
		'\x0E',
		'\x0F',
		'\x10',
		'\x11',
		'\x12',
		'\x13',
		'\x14',
		'\x15',
		'\x16',
		'\x17',
		'\x18',
		'\x19',
		'\x1A',
		'\x1B',
		'\x1C',
		'\x1D',
		'\x1E',
		'\x1F',
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
		':',
		';',
		'<',
		'=',
		'>',
		'?',
		'@',
		'[',
		'\\',
		']',
		'^',
		'_',
		'`',
		'{',
		'|',
		'}',
		'~',
		'\x7F'
};

/**
 * @brief An array holding all of the ASCII characters that are not alphanumeric.
 * @showinitializer
 */
constexpr char ASCIINonAlphanumeric[66] = {
		'\x00',
		'\x01',
		'\x02',
		'\x03',
		'\x04',
		'\x05',
		'\x06',
		'\a',
		'\b',
		'\t',
		'\n',
		'\v',
		'\f',
		'\r',
		'\x0E',
		'\x0F',
		'\x10',
		'\x11',
		'\x12',
		'\x13',
		'\x14',
		'\x15',
		'\x16',
		'\x17',
		'\x18',
		'\x19',
		'\x1A',
		'\x1B',
		'\x1C',
		'\x1D',
		'\x1E',
		'\x1F',
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
		':',
		';',
		'<',
		'=',
		'>',
		'?',
		'@',
		'[',
		'\\',
		']',
		'^',
		'_',
		'`',
		'{',
		'|',
		'}',
		'~',
		'\x7F'
};

/**
 * @brief An array containing all of the ASCII numerals
 * @showinitializer
 */
constexpr char32_t ASCIIDigitsUTF32[10] = {
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
 * Expands to a sequence of case statements from 0 to 9, for use in a switch statement.
 *
 * Example usage:
 * switch(a) {
 * 		// Beginning of switch block
 * 		case ASCII_DIGIT:
 * 			break;
 * 		// Rest of switch block
 * }
 */
#define ASCII_DIGIT \
	'0':            \
	case '1':       \
	case '2':       \
	case '3':       \
	case '4':       \
	case '5':       \
	case '6':       \
	case '7':       \
	case '8':       \
	case '9'

/**
 * @brief An array containing all of the ASCII numerals
 * @showinitializer
 */
constexpr char ASCIIDigits[10] = {
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
constexpr char32_t ASCIIWhitespaceUTF32[5] = {
		' ',
		'\t',
		'\n',
		'\f',
		'\r'
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
constexpr char32_t ASCIIUTF32[128] = {
		'\x00',
		'\x01',
		'\x02',
		'\x03',
		'\x04',
		'\x05',
		'\x06',
		'\n',
		'\t',
		'\f',
		'\r',
		'\x0E',
		'\x0F',
		'\x10',
		'\x11',
		'\x12',
		'\x13',
		'\x14',
		'\x15',
		'\x16',
		'\x17',
		'\x18',
		'\x19',
		'\x1A',
		'\x1B',
		'\x1C',
		'\x1D',
		'\x1E',
		'\x1F',
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
		'~',
		'\x7F'
};

/**
 * @brief An array containing all of ASCII
 * @showinitializer
 */
constexpr char ASCII[128] = {
		'\x00',
		'\x01',
		'\x02',
		'\x03',
		'\x04',
		'\x05',
		'\x06',
		'\n',
		'\t',
		'\f',
		'\r',
		'\x0E',
		'\x0F',
		'\x10',
		'\x11',
		'\x12',
		'\x13',
		'\x14',
		'\x15',
		'\x16',
		'\x17',
		'\x18',
		'\x19',
		'\x1A',
		'\x1B',
		'\x1C',
		'\x1D',
		'\x1E',
		'\x1F',
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
		'~',
		'\x7F'
};

/**
 * @brief Tests if a character is whitespace
 * @param character Character to test
 * @return Returns @c true if character is whitespace, @c false if it is not.
 * @see ASCIIWhitespace
 *
 * @test HTML::Microsyntaxes::ASCII::TEST(HTML_Microsyntaxes_ASCII, isWhitespace)
 */
bool isWhitespace(const char& character);

/**
 * @brief Tests if a character is whitespace
 * @param character Character to test
 * @return Returns @c true if character is whitespace, @c false if it is not.
 * @see ASCIIWhitespace
 *
 * @test HTML::Microsyntaxes::ASCII::TEST(HTML_Microsyntaxes_ASCII, isWhitespace)
 */
bool isWhitespace(const char32_t& character);

/**
 * @brief Tests if a string is whitespace
 * @param string String to test
 * @return Returns @c true if string is whitespace, @c false if it is not.
 * @see ASCIIWhitespace
 *
 * @test HTML::Microsyntaxes::ASCII::TEST(HTML_Microsyntaxes_ASCII, isWhitespace)
 */
bool isWhitespace(const std::string& string);

/**
 * @brief Tests if a string is whitespace
 * @param string String to test
 * @return Returns @c true if string is whitespace, @c false if it is not.
 * @see ASCIIWhitespace
 *
 * @test HTML::Microsyntaxes::ASCII::TEST(HTML_Microsyntaxes_ASCII, isWhitespace)
 */
bool isWhitespace(const std::u32string& string);

/**
 * @brief Tests if a character is unicode whitespace
 * @param character Character to test
 * @return Returns @c true if character is unicode whitespace, @c false if it is not.
 *
 * @test HTML::Microsyntaxes::ASCII::TEST(HTML_Microsyntaxes_ASCII, isUnicodeWhitespace)
 */
bool isUnicodeWhitespace(const char32_t& character);

/**
 * @brief Tests if a string is unicode whitespace
 * @param string String to test
 * @return Returns @c true if string is unicode whitespace, @c false if it is not.
 *
 * @test HTML::Microsyntaxes::ASCII::TEST(HTML_Microsyntaxes_ASCII, isUnicodeWhitespace)
 */
bool isUnicodeWhitespace(const std::u32string& string);

/**
 * @brief Tests if a character is ASCII
 * @param character Character to test
 * @return Returns @c true if the character is ASCII, @c false if it is not.
 *
 * @test HTML::Microsyntaxes::ASCII::TEST(HTML_Microsyntaxes_ASCII, isASCII)
 */
bool isASCII(const char32_t& character);

/**
 * @brief Tests if a string is ASCII
 * @param string String to test
 * @return Returns @c true if string is ASCII, @c false if it is not.
 *
 * @test HTML::Microsyntaxes::ASCII::TEST(HTML_Microsyntaxes_ASCII, isASCII)
 */
bool isASCII(const std::u32string& string);

/**
 * @brief Tests if a character is an ASCII digit
 * @param character Character to test
 * @return Returns @c true if character is an ASCII digit, @c false if it is not.
 *
 * @test HTML::Microsyntaxes::ASCII::TEST(HTML_Microsyntaxes_ASCII, isASCIIDigit)
 */
bool isASCIIDigit(const char32_t& character);

/**
 * @brief Tests if a string is ASCII digits
 * @param string String to test
 * @return Returns @c true if string is ASCII digits, @c false if it is not.
 *
 * @test HTML::Microsyntaxes::ASCII::TEST(HTML_Microsyntaxes_ASCII, isASCIIDigit)
 */
bool isASCIIDigits(const std::u32string& string);

/**
 * @brief Tests if a byte is an ASCII upper case letter
 * @param character A reference to the byte to be tested
 * @return If the byte is an ASCII upper case letter, the function returns @c true.
 * 		   Otherwise, the function returns @c false.
 *
 * @test HTML::Microsyntaxes::ASCII::TEST(HTML_Microsyntaxes_ASCII, isASCIIUpper)
 */
bool isASCIIUpper(const char32_t& character);

/**
 * @brief Tests if a string is ASCII upper case
 * @param string String to test
 * @return Returns @c true if the string is ASCII upper case, @c false if it is not.
 *
 * @test HTML::Microsyntaxes::ASCII::TEST(HTML_Microsyntaxes_ASCII, isASCIIUpper)
 */
bool isASCIIUpper(const std::u32string& string);

/**
 * @brief Tests if a character is ASCII lower case
 * @param character Character to test
 * @return Returns @c true if the character is ASCII lower case, @c false if it is not.
 *
 * @test HTML::Microsyntaxes::ASCII::TEST(HTML_Microsyntaxes_ASCII, isASCIILower)
 */
bool isASCIILower(const char32_t& character);

/**
 * @brief Tests if a string is ASCII lower case
 * @param string String to test
 * @return Returns @c true if the string is ASCII lower case, @c false if it is not.
 *
 * @test HTML::Microsyntaxes::ASCII::TEST(HTML_Microsyntaxes_ASCII, isASCIILower)
 */
bool isASCIILower(const std::u32string& string);

/**
 * @brief Tests if a character is alphanumeric ASCII
 * @param character Character to test
 * @return Returns @c true if the character is alphanumeric ASCII, @c false if it is not.
 *
 * @test HTML::Microsyntaxes::ASCII::TEST(HTML_Microsyntaxes_ASCII, isAlphanumericASCII)
 */
bool isAlphanumericASCII(const char32_t& character);

/**
 * @brief Tests if a string is alphanumeric ASCII
 * @param string String to test
 * @return Returns @c true if the string is alphanumeric ASCII, @c false if it is not.
 *
 * @test HTML::Microsyntaxes::ASCII::TEST(HTML_Microsyntaxes_ASCII, isAlphanumericASCII)
 */
bool isAlphanumericASCII(const std::u32string& string);

/**
 * @brief Tests if a character is ASCII hex
 * @param character Character to test
 * @return Returns @c true if the character is ASCII hex, @c false if it is not.
 *
 * @test HTML::Microsyntaxes::ASCII::TEST(HTML_Microsyntaxes_ASCII, isASCIIHex)
 */
bool isASCIIHex(const char32_t& character);

/**
 * @brief Tests if a string is ASCII hex
 * @param string String to test
 * @return Returns @c true if the string is ASCII hex, @c false if it is not.
 *
 * @test HTML::Microsyntaxes::ASCII::TEST(HTML_Microsyntaxes_ASCII, isASCIIHex)
 */
bool isASCIIHex(const std::u32string& string);

/**
 * @brief Tests if a character is ASCII hex upper case
 * @param character Character to test
 * @return Returns @c true if the character is ASCII hex upper case, @c false if it is not.
 *
 * @test HTML::Microsyntaxes::ASCII::TEST(HTML_Microsyntaxes_ASCII, isASCIIHexUpper)
 */
bool isASCIIHexUpper(const char32_t& character);

/**
 * @brief Tests if a string is ASCII hex upper case
 * @param string String to test
 * @return Returns @c true if the string is ASCII hex upper case, @c false if it is not.
 *
 * @test HTML::Microsyntaxes::ASCII::TEST(HTML_Microsyntaxes_ASCII, isASCIIHexUpper)
 */
bool isASCIIHexUpper(const std::u32string& string);

/**
 * @brief Tests if a character is ASCII hex lower case
 * @param character Character to test
 * @return Returns @c true if the character is ASCII hex lower case, @c false if it is not.
 *
 * @test HTML::Microsyntaxes::ASCII::TEST(HTML_Microsyntaxes_ASCII, isASCIIHexLower)
 */
bool isASCIIHexLower(const char32_t& character);

/**
 * @brief Tests if a string is ASCII hex lower case
 * @param string String to test
 * @return Returns @c true if the string is ASCII hex lower case, @c false if it is not.
 *
 * @test HTML::Microsyntaxes::ASCII::TEST(HTML_Microsyntaxes_ASCII, isASCIIHexLower)
 */
bool isASCIIHexLower(const std::u32string& string);

/**
 * @brief Tests if a character is an ASCII non-alphanumeric character
 * @param character Character to test
 * @return  Returns @c true if the character is an ASCII non-alphanumeric character, @c false if it is not.
 *
 * @test HTML::Microsyntaxes::ASCII::TEST(HTML_Microsyntaxes_ASCII, isASCIINonAlphanumeric)
 */
bool isASCIINonAlphanumeric(const char32_t& character);

/**
 * @brief Tests if a string consists of ASCII non-alphanumeric characters
 * @param string String to test
 * @return  Returns @c true if the string consists of ASCII non-alphanumeric characters, @c false if it does not.
 *
 * @test HTML::Microsyntaxes::ASCII::TEST(HTML_Microsyntaxes_ASCII, isASCIINonAlphanumeric)
 */
bool isASCIINonAlphanumeric(const std::u32string& string);

/**
 * @brief Converts a character to its ASCII upper case equivalent
 * @param character Character to convert
 * @return Returns the ASCII upper case equivalent of the character given.
 * 		   If the character is not ASCII lower case, the original character is returned.
 *
 * @test HTML::Microsyntaxes::ASCII::TEST(HTML_Microsyntaxes_ASCII, toUpper)
 */
char32_t toUpper(const char32_t& character);

/**
 * @brief Converts a string to ASCII upper case
 * @param string String to convert
 * @return Returns the ASCII upper case equivalent of the string given.
 * 		   If a character in the string is not ASCII lower case, it is left unmodified in the string.
 *
 * @test HTML::Microsyntaxes::ASCII::TEST(HTML_Microsyntaxes_ASCII, toUpper)
 */
std::u32string toUpper(const std::u32string& string);

/**
 * @brief Converts a character to its ASCII lower case equivalent
 * @param character Character to convert
 * @return Returns the ASCII lower case equivalent of the character given.
 * 		   If the character is not ASCII upper case, the original character is returned.
 *
 * @test HTML::Microsyntaxes::ASCII::TEST(HTML_Microsyntaxes_ASCII, toLower)
 */
char32_t toLower(const char32_t& character);

/**
 * @brief Converts a string to ASCII lower case
 * @param string String to convert
 * @return Returns the ASCII lower case equivalent of the string given.
 * 		   If a character in the string is not ASCII upper case, it is left unmodified in the string.
 *
 * @test HTML::Microsyntaxes::ASCII::TEST(HTML_Microsyntaxes_ASCII, toLower)
 */
std::u32string toLower(const std::u32string& string);

/**
 * @brief Compares two characters in an ASCII case-insensitive manner.
 * @param lhs The first character to compare
 * @param rhs The second character to compare
 * @return Returns @c true if the characters match exactly except for the ASCII letters,
 *         which are considered to match to their corresponding characters in the other letter case.
 *         Returns @c false if the characters do not match.
 *
 */
bool caseInsensitiveMatch(const char32_t& lhs, const char32_t& rhs);

/**
 * @brief Compares two strings in an ASCII case-insensitive manner.
 * @param lhs The first string to compare
 * @param rhs The second string to compare
 * @return Returns @c true if the strings match exactly, code point for code point,
 * 		   except for the ASCII letters, which are considered to match to their corresponding
 * 		   characters in the other letter case.  Returns @c false if the strings do not match.
 *
 * @test  HTML::Microsyntaxes::ASCII::TEST(HTML_Microsyntaxes_ASCII, caseInsensitiveMatch)
 */
bool caseInsensitiveMatch(const std::u32string& lhs, const std::u32string& rhs);

/**
 * @brief Skips whitespace at the beginning of a stream
 * @details Reads from @c stream until there are no more whitespace characters left at the
 * 			front of @c stream.  This is determined using the isWhitespace() function.
 * @param stream Stream to be processed
 * @param swallowExceptions Boolean parameter that tells the function whether or not to emit exceptions.
 * 		  Defaults to @c false.
 * @return Returns a reference to @c stream
 * @exception std::istream::failure The input stream failed before a non whitespace character was found.
 *
 * @see isWhitespace(const char32_t& character)
 * @test HTML::Microsyntaxes::ASCII::TEST(HTML_Microsyntaxes_ASCII, istream_skipWhitespace)
 */
std::istream& skipWhitespace(std::istream& stream, bool swallowExceptions = false);

/**
 * @brief Skips whitespace
 * @details Increments @c position until the character located at @c string[@c position] is no longer whitespace
 * @param string String to be read
 * @param position Position index
 * @return Returns a reference to @c string
 * @see isWhitespace(const char32_t& character)
 * @test HTML::Microsyntaxes::ASCII::TEST(HTML_Microsyntaxes_ASCII, string_skipWhitespace)
 */
const std::u32string& skipWhitespace(const std::u32string& string, size_t& position);

} /* namespace ASCII */
} /* namespace Microsyntaxes */
} /* namespace HTML */



#endif /* HTML_MICROSYNTAXES_ASCII_HPP_ */
