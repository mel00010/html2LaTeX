/*******************************************************************************
 * Dimension.cpp
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

#include "Dimension.hpp"

#include "SignedInteger.hpp"
#include "NumbersTypes.hpp"
#include "NumbersMisc.hpp"

#include <HTML/Microsyntaxes/ASCII/ASCII.hpp>


namespace HTML {
namespace Microsyntaxes {
namespace Numbers {

bool isDimension(const std::u32string& string) {
	size_t position = 0;

	if (position > string.length()) {
		return false;
	}

	if (string[position] == '+') {
		position++;
	}

	for (; position < string.length(); position++) {
		if (string[position] != '0') {
			break;
		}
	}

	if (position >= string.length()) {
		return false;
	}

	if (!ASCII::isASCIIDigit(string[position])) {
		return false;
	}

	if (string[position] == '0') {
		return false;
	}

	std::u32string digits = U"";
	for (; position < string.length(); position++) {
		if (ASCII::isASCIIDigit(string[position])) {
			digits += string[position];
		} else {
			break;
		}
	}

	double value = parseInteger(digits);

	if (position >= string.length()) {
		if (value >= 1) {
			return true;
		} else {
			return false;
		}
	}

	if (string[position] == '.') {
		position++;

		if (position >= string.length()) {
			if (value >= 1) {
				return true;
			} else {
				return false;
			}

		}

		if (!ASCII::isASCIIDigit(string[position])) {
			return false;

		}
		for (; position < string.length(); position++) {
			if (!ASCII::isASCIIDigit(string[position])) {
				break;
			}
		}
	}

	if (position >= string.length()) {
		if (value >= 1) {
			return true;
		} else {
			return false;
		}
	}
	if (string[position] == '%') {
		if (value >= 1) {
			return true;
		} else {
			return false;
		}

	} else {
		return false;
	}
	if (value >= 1) {
		return true;
	} else {
		return false;
	}
}

Dimension parseDimension(const std::u32string& string) {
	size_t position = 0;

	Dimension dimension = Dimension(NAN, DimensionType::UNKNOWN);

	ASCII::skipWhitespace(string, position);

	if (position > string.length()) {
		throw parseException();
	}

	if (string[position] == '+') {
		position++;
	}

	for (; position < string.length(); position++) {
		if (string[position] != '0') {
			break;
		}
	}

	if (position > string.length()) {
		throw parseException();
	}

	if (!ASCII::isASCIIDigit(string[position])) {
		throw parseException();
	}

	if (string[position] == '0') {
		throw parseException();
	}

	std::u32string digits = U"";
	for (; position < string.length(); position++) {
		if (ASCII::isASCIIDigit(string[position])) {
			digits += string[position];
		} else {
			break;
		}
	}

	dimension.value = parseInteger(digits);

	if (position > string.length()) {
		dimension.type = DimensionType::LENGTH;
		if (dimension.value >= 1) {
			return dimension;
		} else {
			throw parseException();
		}
	}

	if (string[position] == '.') {
		position++;

		if (position > string.length()) {
			dimension.type = DimensionType::LENGTH;
			if (dimension.value >= 1) {
				return dimension;
			} else {
				throw parseException();
			}

		}

		if (!ASCII::isASCIIDigit(string[position])) {
			dimension.type = DimensionType::LENGTH;
			if (dimension.value >= 1) {
				return dimension;
			} else {
				throw parseException();
			}
		}

		size_t divisor = 1;

		for (; position < string.length(); position++) {
			if (!ASCII::isASCIIDigit(string[position])) {
				break;
			}
			divisor *= 10;
			dimension.value += static_cast<double>(ASCIIDigitToInt(string[position])) / divisor;
		}
	}

	if (position > string.length()) {
		dimension.type = DimensionType::LENGTH;
		if (dimension.value >= 1) {
			return dimension;
		} else {
			throw parseException();
		}
	}
	if (string[position] == '%') {
		dimension.type = DimensionType::PERCENTAGE;
		if (dimension.value >= 1) {
			return dimension;
		} else {
			throw parseException();
		}
	}

	dimension.type = DimensionType::LENGTH;
	if (dimension.value >= 1) {
		return dimension;
	} else {
		throw parseException();
	}
}


} /* namespace Numbers */
} /* namespace Microsyntaxes */
} /* namespace HTML */


