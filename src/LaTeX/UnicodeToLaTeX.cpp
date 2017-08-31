/*******************************************************************************
 * UnicodeToLaTeX.cpp
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

#include "UnicodeToLaTeX.hpp"

#include <iomanip>
#include <sstream>

namespace LaTeX {

UnicodeToLaTeX::~UnicodeToLaTeX() {
}

const constexpr char* UnicodeToLaTeX::findValue(const char32_t key, int range) {
	return
	(range == 0) ? throw "Key not present" :
	(unicodeToLaTeX[range - 1].first == key) ? unicodeToLaTeX[range - 1].second : findValue(key, range - 1);
}


constexpr char32_t UnicodeToLaTeX::findKey(const char* value, int range) {
	return
	(range == 0) ? throw "Value not present" :
	(unicodeToLaTeX[range - 1].second == value) ? unicodeToLaTeX[range - 1].first : findKey(value, range - 1);
}

const std::string UnicodeToLaTeX::convert(const char32_t codePoint) {
	try {
		const char* substitution = UnicodeToLaTeX::findValue(codePoint);
		return substitution;
	} catch (const char* e) {
		const char* exceptionString = "Key not present";
		if (e == exceptionString) {
			std::ostringstream output;
			output << "\\char\"" << std::hex << std::setfill('0') << std::setw(8) << (std::uppercase) << (int) codePoint << "\"";
			return output.str();
		} else {
			throw;
		}
	}

}

const std::string UnicodeToLaTeX::convert(const std::u32string string) {
	std::ostringstream output;
	for (auto& c : string) {
		output << convert(c);
	}
	return output.str();
}

} /* namespace LaTeX */
