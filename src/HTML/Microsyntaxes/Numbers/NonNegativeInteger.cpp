/*******************************************************************************
 * NonNegativeInteger.cpp
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

#include "NonNegativeInteger.hpp"

#include "NumbersMisc.hpp"
#include "NumbersTypes.hpp"

#include <cstdint>
#include <limits>
#include <stddef.h>

#include "HTML/Microsyntaxes/ASCII/ASCII.hpp"

namespace HTML {
namespace Microsyntaxes {
namespace Numbers {

bool isNonNegativeInteger(const std::u32string& string) {
	return !string.empty() && ASCII::isASCIIDigits(string);
}
bool isNonNegativeHexInteger(const std::u32string& string) {
	return !string.empty() && ASCII::isASCIIHex(string);
}

uint32_t parseNonNegativeInteger(const std::u32string& string) {
	uint32_t accumulated = 0;
	bool started = false;
	for (size_t i = 0; i < string.length(); i++) {
		if (ASCII::isWhitespace(string[i]) && !started) {
			continue;
		} else if (ASCII::isASCIIDigit(string[i])) {
			started = true;
			uint8_t digit = ASCIIDigitToInt(string[i]);
			accumulated = accumulated * 10 + digit;
		} else if (started) {
			break;
		} else {
			throw parseException();
		}
	}
	if (!started) {
		throw parseException();
	}
	return accumulated;
}

uint32_t parseNonNegativeHexInteger(const std::u32string& string) {
	uint32_t accumulated = 0;
	bool started = false;
	for (size_t i = 0; i < string.length(); i++) {
		if (ASCII::isWhitespace(string[i]) && !started) {
			continue;
		} else if (ASCII::isASCIIHex(string[i])) {
			started = true;
			uint8_t digit = ASCIIHexDigitToInt(string[i]);
			accumulated = accumulated * 0x10 + digit;
		} else if (started) {
			break;
		} else {
			throw parseException();
		}
	}
	if (!started) {
		throw parseException();
	}
	return accumulated;
}
} /* namespace Numbers */
} /* namespace Microsyntaxes */
} /* namespace HTML */
