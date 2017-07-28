/*******************************************************************************
 * SignedInteger.cpp
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

#include <SignedInteger.hpp>
#include <NumbersTypes.hpp>

#include <Microsyntaxes/ASCII/ASCII.hpp>


namespace HTML {
namespace Microsyntaxes {
namespace Numbers {

bool isInteger(const std::string& string) {
	if (string.empty()) {
		return false;
	}
	if (isASCIIDigits(string)) {
		return true;
	} else if ((string[0] == '-') && (isASCIIDigits(string.substr(1)))) {
		return true;
	}
	return false;
}

int parseInteger(const std::string& string) {
	int accumulated = 0;
	bool positive = true;
	bool started = false;
	for (size_t i = 0; i < string.length(); i++) {
		if (!isWhitespace(string[i])) {
			if (isASCIIDigit(string[i])) {
				started = true;
				int digit = 0;
				switch (string[i]) {
					case '0':
						digit = 0;
						break;
					case '1':
						digit = 1;
						break;
					case '2':
						digit = 2;
						break;
					case '3':
						digit = 3;
						break;
					case '4':
						digit = 4;
						break;
					case '5':
						digit = 5;
						break;
					case '6':
						digit = 6;
						break;
					case '7':
						digit = 7;
						break;
					case '8':
						digit = 8;
						break;
					case '9':
						digit = 9;
						break;
				}
				accumulated = accumulated * 10 + digit;
			} else if ((!started) && (string[i] == '-')) {
				positive = false;
			} else {
				throw parseException();
			}
		}
	}
	if (!started) {
		throw parseException();
	}
	if (!positive) {
		accumulated = 0 - accumulated;
	}
	return accumulated;
}

} /* namespace Numbers */
} /* namespace Microsyntaxes */ // LCOV_EXCL_LINE
} /* namespace HTML */ // LCOV_EXCL_LINE

