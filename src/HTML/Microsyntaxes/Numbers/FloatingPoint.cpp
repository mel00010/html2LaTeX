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

#include <HTML/Microsyntaxes/ASCII/ASCII.hpp>

namespace HTML {
namespace Microsyntaxes {
namespace Numbers {

bool isFloatingPoint(const std::u32string& string) {
	if (string.empty()) {
		return false;
	}
	size_t position = 0;
	if (string[0] == '-') {
		position++;
	}
	for (; position < string.length(); position++) {
		if (!ASCII::isASCIIDigit(string[position])) {
			if (string[position] == '.') {
				position++;
				for (; position < string.length(); position++) {
					if (!ASCII::isASCIIDigit(string[position])) {
						if ((string[position] == 'e') || (string[position] == 'E')) {
							position++;
							if (string[position] == '-') {
								position++;
							}
							for (; position < string.length(); position++) {
								if (!ASCII::isASCIIDigit(string[position])) {
									return false;
								}
							}
							return true;
						}
						return false;
					}
				}
			} else if ((string[position] == 'e') || (string[position] == 'E')) {
				position++;
				if (string[position] == '-') {
					position++;
				}
				for (; position < string.length(); position++) {
					if (!ASCII::isASCIIDigit(string[position])) {
						return false;
					}
				}
				return true;
			} else {
				return false;
			}
		}
	}
	return true;
}

double exponentStep(const std::u32string& string, size_t& position, double& value, double& exponent) {
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
	if (!ASCII::isASCIIDigit(string[position])) {
		throw parseException();
	}

	std::u32string digits = U"";
	for (; position < string.length(); position++) {
		if (ASCII::isASCIIDigit(string[position])) {
			digits += string[position];
		} else {
			throw parseException();
		}
	}

	if (digits.empty()) {
		return value;
	}

	exponent *= parseNonNegativeInteger(digits);
	value *= pow(10, exponent);
	return value;
}

double fractionStep(const std::u32string& string, size_t& position, double& value, double& divisor, double& exponent) {
	position++;
	if (position > string.length()) {
		return value;
	}

	if ((string[position] == 'e') || (string[position] == 'E')) {
		return exponentStep(string, position, value, exponent);
	}

	for (; position < string.length(); position++) {
		divisor = divisor * 10;

		if (!ASCII::isASCIIDigit(string[position])) {
			break;
		}

		value += (static_cast<double>(ASCIIDigitToInt(string[position]))) / divisor;
	}

	if (position >= string.length()) {
		return value;
	}

	if ((string[position] == 'e') || (string[position] == 'E')) {
		return exponentStep(string, position, value, exponent);
	} else {
		throw parseException();
	}
	return value;
}

double parseFloatingPoint(const std::u32string& string) {
	if (string.empty()) {
		throw parseException("string is empty!");
	}

	size_t position = 0;

	double value = 1;
	double divisor = 1;
	double exponent = 1;

	for (; position < string.length(); position++) {
		if (ASCII::isWhitespace(string[position])) {
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
		if (ASCII::isASCIIDigit(string[position + 1])) {
			return fractionStep(string, position, value, divisor, exponent);
		}
		position++;
	}
	if (!ASCII::isASCIIDigit(string[position])) {
		throw(parseException("Unexpected non ASCII digit in floating point string!"));
	}

	std::u32string digits = U"";
	for (; position < string.length(); position++) {
		if (ASCII::isASCIIDigit(string[position])) {
			digits += string[position];
		} else {
			break;
		}
	}

	if (digits.empty()) {
		throw(parseException("digits is empty!"));
	}
	value *= parseNonNegativeInteger(digits);

	if (position >= string.length()) {
		return value;
	}
	if (string[position] == '.') {
		return fractionStep(string, position, value, divisor, exponent);
	}
	if ((string[position] == 'e') || (string[position] == 'E')) {
		return exponentStep(string, position, value, exponent);
	}
	if (!ASCII::isASCIIDigit(string[position])) {
		throw parseException();
	}
	return value;
}

} /* namespace Numbers */
} /* namespace Microsyntaxes */
} /* namespace HTML */

