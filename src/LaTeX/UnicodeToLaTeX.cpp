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

#include <LaTeX/UnicodeToLaTeX.hpp>
#include <LaTeX/ConcreteUnicodeToLaTeX.hpp>

#include <utility>
#include <sstream>
#include <iostream>
#include <string>
#include <locale>
#include <iomanip>
#include <gtest/gtest.h>


namespace LaTeX {

constexpr Item ConcreteUnicodeToLaTeX::unicodeToLaTeX[];


const constexpr char* ConcreteUnicodeToLaTeX::findValue(const char32_t key, int range) {
	return
	(range == 0) ? throw "Key not present" :
	(unicodeToLaTeX[range - 1].first == key) ? unicodeToLaTeX[range - 1].second : findValue(key, range - 1);
}


constexpr char32_t ConcreteUnicodeToLaTeX::findKey(const char* value, int range) {
	return
	(range == 0) ? throw "Value not present" :
	(unicodeToLaTeX[range - 1].second == value) ? unicodeToLaTeX[range - 1].first :
													findKey(value, range - 1);
}

const std::string ConcreteUnicodeToLaTeX::convert(const char32_t codePoint) {
	try {
		const char* substitution = ConcreteUnicodeToLaTeX::findValue(codePoint);
		return substitution;
	} catch (const char* e) {
		const char* exceptionString = "Key not present";
		if (e == exceptionString) {
			std::ostringstream output;
			output << "\\char\"";
			for (size_t i = 0; i < 4; ++i) {
				output << std::hex << std::setfill('0') << std::setw(2) << (std::uppercase) << (int) codePoint;
			}
			return output.str();
		} else {
			throw;
		}
	}

}

const std::string ConcreteUnicodeToLaTeX::convert(const std::u32string string) {
	std::ostringstream output;
	for (auto& c : string) {
		output << convert(c);
	}
	return output.str();
}

} /* namespace LaTeX */
