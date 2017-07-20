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

#include <HTML/Microsyntaxes/ASCII.hpp>

#include <string>

namespace HTML {
namespace Microsyntaxes {

bool isWhitespace(const char& character) {
	for (const char& i : ASCIIWhitespace) {
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

bool isUnicodeWhitespace(const char& character) {
	//! @TODO Finish function
	return false;
}

bool isUnicodeWhitespace(const std::string& string) {
	for (const char& i : string) {
		if (!isUnicodeWhitespace(i)) {
			return false;
		}
	}
	return true;
}

bool isASCII(const char& character) {
	for (const char& i : ASCII) {
		if (character == i) {
			return true;
		}
	}
	return false;
}

bool isASCII(const std::string& string) {
	for (const char& i : string) {
		if (!isASCII(i)) {
			return false;
		}
	}
	return true;
}

bool isASCIIDigit(const char& character) {
	for (const char& i : ASCIIDigit) {
		if (character == i) {
			return true;
		}
	}
	return false;
}

bool isASCIIDigits(const std::string& string) {
	for (const char& i : string) {
		if (!isASCIIDigit(i)) {
			return false;
		}
	}
	return true;
}

bool isASCIIUpper(const char& character) {
	for (const char& i : ASCIIUpper) {
		if (character == i) {
			return true;
		}
	}
	return false;
}

bool isASCIIUpper(const std::string& string) {
	for (const char& i : string) {
		if (!isASCIIUpper(i)) {
			return false;
		}
	}
	return true;
}

bool isASCIILower(const char& character) {
	for (const char& i : ASCIILower) {
		if (character == i) {
			return true;
		}
	}
	return false;
}

bool isASCIILower(const std::string& string) {
	for (const char& i : string) {
		if (!isASCIILower(i)) {
			return false;
		}
	}
	return true;
}

bool isAlphanumericASCII(const char& character) {
	for (const char& i : ASCIIAlphanumeric) {
		if (character == i) {
			return true;
		}
	}
	return false;
}

bool isAlphanumericASCII(const std::string& string) {
	for (const char& i : string) {
		if (!isAlphanumericASCII(i)) {
			return false;
		}
	}
	return true;
}

bool isASCIIHex(const char& character) {
	for (const char& i : ASCIIHex) {
		if (character == i) {
			return true;
		}
	}
	return false;
}

bool isASCIIHex(const std::string& string) {
	for (const char& i : string) {
		if (!isASCIIHex(i)) {
			return false;
		}
	}
	return true;
}

bool isASCIIHexUpper(const char& character) {
	for (const char& i : ASCIIHexUpper) {
		if (character == i) {
			return true;
		}
	}
	return false;
}

bool isASCIIHexUpper(const std::string& string) {
	for (const char& i : string) {
		if (!isASCIIHexUpper(i)) {
			return false;
		}
	}
	return true;
}

bool isASCIIHexLower(const char& character) {
	for (const char& i : ASCIIHexLower) {
		if (character == i) {
			return true;
		}
	}
	return false;
}

bool isASCIIHexLower(const std::string& string) {
	for (const char& i : string) {
		if (!isASCIIHexLower(i)) {
			return false;
		}
	}
	return true;
}
char toUpper(const char& character) {
	for (size_t i = 0; i < sizeof(ASCIILower); i++) {
		if (character == ASCIILower[i]) {
			return ASCIIUpper[i];
		}
	}
	return character;
}


std::string toUpper(const std::string& string) {
	std::string converted;
	for (const char& i : string) {
		if (isASCIILower(i)) {
			converted += toUpper(i);
		} else {
			converted += i;
		}
	}
	return converted;
}

char toLower(const char& character) {
	for (size_t i = 0; i < sizeof(ASCIIUpper); i++) {
		if (character == ASCIIUpper[i]) {
			return ASCIILower[i];
		}
	}
	return character;
}

std::string toLower(const std::string& string) {
	std::string converted;
	for (const char& i : string) {
		if (isASCIIUpper(i)) {
			converted += toLower(i);
		} else {
			converted += i;
		}
	}
	return converted;
}

} /* namespace Microsyntaxes */
} /* namespace HTML */
