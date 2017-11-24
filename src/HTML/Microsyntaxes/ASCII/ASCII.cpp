/*******************************************************************************
 * ASCII.cpp
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

#include "ASCII.hpp"

#include <stddef.h>
#include <cstdint>
//#include <iostream>
//#include <string>


namespace HTML {
namespace Microsyntaxes {
namespace ASCII {

bool isWhitespace(const char& character) {
	for (const char& i : ASCIIWhitespace) {
		if (character == i) {
			return true;
		}
	}
	return false;
}

bool isWhitespace(const char32_t& character) {
	for (const char32_t& i : ASCIIWhitespaceUTF32) {
		if (character == i) {
			return true;
		}
	}
	return false;
}

bool isWhitespace(const std::string& string) {
	for (const char& i : string) {
		if (!isWhitespace(i)) {
			return false;
		}
	}
	return true;
}

bool isWhitespace(const std::u32string& string) {
	for (const char32_t& i : string) {
		if (!isWhitespace(i)) {
			return false;
		}
	}
	return true;
}

bool isUnicodeWhitespace(const char32_t& character __attribute__ ((unused))) {
	//! @todo Finish function
	return false;
}

bool isUnicodeWhitespace(const std::u32string& string) {
	for (const char32_t& i : string) {
		if (!isUnicodeWhitespace(i)) {
			return false;
		}
	}
	return true;
}

bool isASCII(const char32_t& character) {
	for (const char32_t& i : ASCIIUTF32) {
		if (character == i) {
			return true;
		}
	}
	return false;
}

bool isASCII(const std::u32string& string) {
	for (const char32_t& i : string) {
		if (!isASCII(i)) {
			return false;
		}
	}
	return true;
}

bool isASCIIDigit(const char32_t& character) {
	for (const char32_t& i : ASCIIDigitsUTF32) {
		if (character == i) {
			return true;
		}
	}
	return false;
}

bool isASCIIDigits(const std::u32string& string) {
	for (const char32_t& i : string) {
		if (!isASCIIDigit(i)) {
			return false;
		}
	}
	return true;
}

bool isASCIIUpper(const char32_t& character) {
	for (const char32_t& i : ASCIIUpperUTF32) {
		if (character == i) {
			return true;
		}
	}
	return false;
}

bool isASCIIUpper(const std::u32string& string) {
	for (const char32_t& i : string) {
		if (!isASCIIUpper(i)) {
			return false;
		}
	}
	return true;
}

bool isASCIILower(const char32_t& character) {
	for (const char32_t& i : ASCIILowerUTF32) {
		if (character == i) {
			return true;
		}
	}
	return false;
}

bool isASCIILower(const std::u32string& string) {
	for (const char32_t& i : string) {
		if (!isASCIILower(i)) {
			return false;
		}
	}
	return true;
}

bool isAlphanumericASCII(const char32_t& character) {
	for (const char32_t& i : ASCIIAlphanumericUTF32) {
		if (character == i) {
			return true;
		}
	}
	return false;
}

bool isAlphanumericASCII(const std::u32string& string) {
	for (const char32_t& i : string) {
		if (!isAlphanumericASCII(i)) {
			return false;
		}
	}
	return true;
}

bool isASCIIHex(const char32_t& character) {
	for (const char32_t& i : ASCIIHexUTF32) {
		if (character == i) {
			return true;
		}
	}
	return false;
}

bool isASCIIHex(const std::u32string& string) {
	for (const char32_t& i : string) {
		if (!isASCIIHex(i)) {
			return false;
		}
	}
	return true;
}

bool isASCIIHexUpper(const char32_t& character) {
	for (const char32_t& i : ASCIIHexUpperUTF32) {
		if (character == i) {
			return true;
		}
	}
	return false;
}

bool isASCIIHexUpper(const std::u32string& string) {
	for (const char32_t& i : string) {
		if (!isASCIIHexUpper(i)) {
			return false;
		}
	}
	return true;
}

bool isASCIIHexLower(const char32_t& character) {
	for (const char32_t& i : ASCIIHexLowerUTF32) {
		if (character == i) {
			return true;
		}
	}
	return false;
}

bool isASCIIHexLower(const std::u32string& string) {
	for (const char32_t& i : string) {
		if (!isASCIIHexLower(i)) {
			return false;
		}
	}
	return true;
}

bool isASCIINonAlphanumeric(const char32_t& character) {
	for (const char32_t& i : ASCIINonAlphanumericUTF32) {
		if (character == i) {
			return true;
		}
	}
	return false;
}

bool isASCIINonAlphanumeric(const std::u32string& string) {
	for (const char32_t& i : string) {
		if (!isASCIINonAlphanumeric(i)) {
			return false;
		}
	}
	return true;
}

char32_t toUpper(const char32_t& character) {
	for (size_t i = 0; i < sizeof(ASCIILowerUTF32) / 4; i++) {
		if (character == ASCIILowerUTF32[i]) {
			return ASCIIUpperUTF32[i];
		}
	}
	return character;
}


std::u32string toUpper(const std::u32string& string) {
	std::u32string converted;
	for (const char32_t& i : string) {
		if (isASCIILower(i)) {
			converted += toUpper(i);
		} else {
			converted += i;
		}
	}
	return converted;
}

char32_t toLower(const char32_t& character) {
	for (size_t i = 0; i < sizeof(ASCIIUpperUTF32) / 4; i++) {
		if (character == ASCIIUpperUTF32[i]) {
			return ASCIILowerUTF32[i];
		}
	}
	return character;
}

std::u32string toLower(const std::u32string& string) {
	std::u32string converted;
	for (const char32_t& i : string) {
		if (isASCIIUpper(i)) {
			converted += toLower(i);
		} else {
			converted += i;
		}
	}
	return converted;
}
bool caseInsensitiveMatch(const char32_t& lhs, const char32_t& rhs) {
	if (toUpper(lhs) == toUpper(rhs)) {
		return true;
	}
	return false;
}


bool caseInsensitiveMatch(const std::u32string& lhs, const std::u32string& rhs) {
	if (toUpper(lhs) == toUpper(rhs)) {
		return true;
	}
	return false;

}

std::istream& skipWhitespace(std::istream& stream, bool swallowExceptions) {
	char buf = '\0';
	try {
		stream.exceptions(std::istream::eofbit);
		while (isWhitespace((char) stream.peek())) {
			stream.read(&buf, 1);
		}
		return stream;
	}
	catch (...) {
		if (swallowExceptions) {
			return stream;
		} else {
			throw;
		}
	}
	return stream;
}

const std::u32string& skipWhitespace(const std::u32string& string, size_t& position) {
	for (; position < string.length(); position++) {
		if (isWhitespace(string[position])) {
			continue;
		} else {
			break;
		}
	}
	return string;
}

} /* namespace ASCII */
} /* namespace Microsyntaxes */
} /* namespace HTML */
