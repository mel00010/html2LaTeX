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

#include "SignedInteger.hpp"

#include "NumbersMisc.hpp"
#include "NumbersTypes.hpp"

#include <stddef.h>

#include "HTML/Microsyntaxes/ASCII/ASCII.hpp"


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
		if (isWhitespace(string[i]) && !started) {
			continue;
		} else if (isASCIIDigit(string[i])) {
			started = true;
			unsigned int digit = ASCIIDigitToInt(string[i]);
			accumulated = accumulated * 10 + digit;
		} else if ((!started) && (string[i] == '-')) {
			positive = false;
		} else if (started) {
			break;
		} else {
			throw parseException();
		}
	}
	if (!started) {
		throw parseException();
	}
	if (!positive) {
		return 0 - accumulated;
	}
	return accumulated;
}

} /* namespace Numbers */
} /* namespace Microsyntaxes */ // LCOV_EXCL_LINE
} /* namespace HTML */ // LCOV_EXCL_LINE

