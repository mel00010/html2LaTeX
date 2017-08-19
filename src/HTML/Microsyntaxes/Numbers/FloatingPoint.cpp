/*******************************************************************************
 * FloatingPoint.cpp
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

#include "FloatingPoint.hpp"

#include "NonNegativeInteger.hpp"
#include "NumbersMisc.hpp"
#include "NumbersTypes.hpp"

#include <stddef.h>
#include <cmath>
//#include <string>

#include "../ASCII/ASCII.hpp"

namespace HTML {
namespace Microsyntaxes {
namespace Numbers {

bool isFloatingPoint(const std::string& string) {
	if (string.empty()) {
		return false;
	}
	bool started = false;
	bool decimalPointFound = false;
	size_t decimalPointPosition = 0;
	bool exponentDelimiterFound = false;
	size_t exponentDelimiterPosition = 0;

	for (size_t i = 0; i < string.length(); i++) {
		if (isWhitespace(string[i]) && !started) {
			continue;
		} else if (isWhitespace(string[i]) && started) {
			break;
		} else if (isASCIIDigit(string[i]) && !decimalPointFound && !exponentDelimiterFound) {

		} else if (isASCIIDigit(string[i]) && decimalPointFound && !exponentDelimiterFound) {

		} else if (isASCIIDigit(string[i]) && !exponentDelimiterFound) {

		} else if (string[i] == '.' && !decimalPointFound && !exponentDelimiterFound) {
			decimalPointFound = true;
			decimalPointPosition = i;
		} else if ((string[i] == 'e' || string[i] == 'E') && !exponentDelimiterFound) {
			exponentDelimiterFound = true;
			exponentDelimiterPosition = i;
		} else if ((i == (exponentDelimiterPosition + 1)) && (string[i] == '+')) {

		} else if ((i == (exponentDelimiterPosition + 1)) && (string[i] == '-')) {

		}
	}
}

double exponentStep(const std::string& string, size_t& position, double& value, double& exponent) {
	position++;
	if (position > string.length()) {
		return value;
	}

	if ((string[position] == '-')) {
		exponent = -1;
		position++;
		if (position > string.length()) {
			return value;
		}
	} else if ((string[position] == '+')) {
		position++;
		if (position > string.length()) {
			return value;
		}
	}
	if (!isASCIIDigit(string[position])) {
		return value;
	}

	std::string digits = "";
	for (; position < string.length(); position++) {
		if (isASCIIDigit(string[position])) {
			digits += string[position];
		} else {
			break;
		}
	}

	if (digits.empty()) {
		return value;
	}
	exponent *= parseNonNegativeInteger(digits);
	value *= pow(10, exponent);
	return value;
}

double fractionStep(const std::string& string, size_t& position, double& value, double& divisor, double& exponent) {
	if (position > string.length()) {
		return value;
	}

	if ((string[position] == 'e') || (string[position] == 'E')) {
		return exponentStep(string, position, value, exponent);
	}

	for (; position < string.length(); position++) {
		divisor = divisor * 10;

		if (!isASCIIDigit(string[position])) {
			break;
		}

		value += (static_cast<double>(ASCIIDigitToInt(string[position]))) / divisor;
	}

	if (position > string.length()) {
		return value;
	}

	if ((string[position] == 'e') || (string[position] == 'E')) {
		return exponentStep(string, position, value, exponent);
	} else if (!(isASCIIDigit(string[position]) || string[position] == 'e' || string[position] == 'E')) {
		throw(parseException());
	}
	return value;
}

double parseFloatingPoint(const std::string& string) {
	if (string.empty()) {
		throw parseException("string is empty!");
	}

	size_t position = 0;

	double value = 1;
	double divisor = 1;
	double exponent = 1;

	for (; position < string.length(); position++) {
		if (isWhitespace(string[position])) {
			continue;
		} else {
			break;
		}
	}
	if ((string[position] == '-')) {
		value = -1;
		divisor = -1;
		position++;
	} else if ((string[position] == '+')) {
		position++;
	}

	if ((string[position] == '.')) {
		value = 0;
		if (isASCIIDigit(string[position + 1])) {
			position++;
			return fractionStep(string, position, value, divisor, exponent);
		}
		position++;
	}
	if (!isASCIIDigit(string[position])) {
		throw(parseException("Unexpected non ASCII digit in floating point string!"));
	}

	std::string digits = "";
	for (; position < string.length(); position++) {
		if (isASCIIDigit(string[position])) {
			digits += string[position];
		} else {
			break;
		}
	}

	if (digits.empty()) {
		throw(parseException("digits is empty!"));
	}
	value *= parseNonNegativeInteger(digits);

	if (position > string.length()) {
		return value;
	}
	if (string[position] == '.') {
		position++;
		return fractionStep(string, position, value, divisor, exponent);
	}
	if ((string[position] == 'e') || (string[position] == 'E')) {
		return exponentStep(string, position, value, exponent);
	}
	return value;
}

} /* namespace Numbers */
} /* namespace Microsyntaxes */
} /* namespace HTML */

