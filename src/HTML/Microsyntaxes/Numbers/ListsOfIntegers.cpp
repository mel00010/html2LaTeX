/*******************************************************************************
 * ListsOfIntegers.cpp
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

#include "ListsOfIntegers.hpp"

#include "NumbersMisc.hpp"

#include <list>
#include <string>

#include <HTML/Microsyntaxes/ASCII/ASCII.hpp>

namespace HTML {
namespace Microsyntaxes {
namespace Numbers {

bool isListOfIntegers(const std::string& string) {
	size_t i = 0;
	if (i >= string.length()) {
		return false;
	}

	bool got_number = false;
	bool finished = false;

	for (; i < string.length(); i++) {
		if (string[i] == '-') {
			if (got_number) {
				return false;
			}
		} else if (ASCII::isASCIIDigit(string[i])) {
			if (finished) {
				continue;
			}
			got_number = true;
			if (i >= string.length() - 1) {
				return true;
			}
		} else if (string[i] == ',') {
			if (!got_number) {
				return false;
			}
			if (i >= string.length() - 1) {
				return true;
			}

			got_number = false;
			finished = false;

		} else {
			return false;
		}
	}
	return false;
}

std::list<int> parseListOfIntegers(const std::string& string) {
	size_t i = 0;
	std::list<int> numbers = { };

	if ((string[i] == ' ') || (string[i] == ',') || (string[i] == ';')) {
		i++;
	}
	if (i >= string.length()) {
		return numbers;
	}
	for (; i < string.length(); i++) {
		if ((string[i] == ' ') || (string[i] == ',') || (string[i] == ';')) {
			continue;
		} else {
			break;
		}
	}
	if (i >= string.length()) {
		return numbers;
	}

	bool negated = false;
	int value = 0;
	bool started = false;
	bool got_number = false;
	bool finished = false;
	bool bogus = false;

	for (; i < string.length(); i++) {
		if (string[i] == '-') {
			if (got_number) {
				finished = true;
			}
			if (finished) {
				continue;
			}
			if (started) {
				negated = false;
			} else if (started == false && bogus == false) {
				negated = true;
			}
			started = true;
		} else if (ASCII::isASCIIDigit(string[i])) {
			if (finished) {
				continue;
			}
			value *= 10;
			value += static_cast<int>(ASCIIDigitToInt(string[i]));
			started = true;
			got_number = true;
		} else if ((string[i] == ' ') || (string[i] == ',') || (string[i] == ';')) {

			if (!got_number) {
				return numbers;
			}
			if (negated) {
				value = 0 - value;
			}

			numbers.push_back(value);

			if ((string[i] == ' ') || (string[i] == ',') || (string[i] == ';')) {
				for (; i < string.length(); i++) {
					if ((string[i] == ' ') || (string[i] == ',') || (string[i] == ';')) {
						continue;
					} else {
						break;
					}
				}
			}
			i--;
			if (i >= string.length()) {
				return numbers;
			}


			negated = false;
			value = 0;
			started = false;
			got_number = false;
			finished = false;
			bogus = false;

			continue;

		} else if (ASCII::isASCIINonAlphanumeric(string[i]) && (string[i] != ' ') && (string[i] != ',') && (string[i] != ';')) {
			if (got_number) {
				finished = true;
			}
			if (finished) {
				continue;
			}
			negated = false;
		} else {
			if (finished) {
				continue;
			}
			negated = false;
			bogus = true;
			if (started) {
				return numbers;
			}
		}
	}

	if (negated) {
		value = 0 - value;
	}
	if (got_number) {
		numbers.push_back(value);
	}
	return numbers;
}


} /* namespace Numbers */
} /* namespace Microsyntaxes */
} /* namespace HTML */


