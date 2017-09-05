/*******************************************************************************
 * ListsOfDimensions.cpp
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

#include "ListsOfDimensions.hpp"

#include "NonNegativeInteger.hpp"
#include "NumbersMisc.hpp"
#include "NumbersTypes.hpp"

#include <boost/algorithm/string.hpp>
#include <boost/tokenizer.hpp>
#include <list>
#include <string>

#include <HTML/Microsyntaxes/ASCII/ASCII.hpp>

namespace HTML {
namespace Microsyntaxes {
namespace Numbers {

bool isListOfDimensions(const std::string& string) {
	return false;
}

std::list<Dimension> parseListOfDimensions(const std::string& string) {
	std::list<Dimension> dimensions = { };
	std::string processed_string;
	if (string[string.length() - 1] == ',') {
		processed_string = string.substr(0, string.length() - 1);
	} else {
		processed_string = string;
	}

	boost::char_separator<char> sep(",");
	boost::tokenizer<boost::char_separator<char>> raw_tokens(processed_string, sep);
	for (const auto& token : raw_tokens) {
		size_t i = 0;
		Dimension dimension(0, DimensionType::ABSOLUTE);
		if (i >= token.length()) {
			dimension.type = DimensionType::RELATIVE;
			dimensions.push_back(dimension);
			continue;
		}
		if (ASCII::isASCIIDigit(token[i])) {
			std::string digits = "";
			for (; i < token.length(); i++) {
				if (ASCII::isASCIIDigit(token[i])) {
					digits += token[i];
				} else {
					break;
				}
			}

			if (digits.empty()) {
				throw(parseException("digits is empty!"));
			}
			dimension.value += parseNonNegativeInteger(digits);
		}
		if (token[i] == '.') {
			i++;
			std::string digitsAndSpaces = "";
			for (; i < token.length(); i++) {
				if (ASCII::isASCIIDigit(token[i]) || token[i] == ' ') {
					digitsAndSpaces += token[i];
				} else {
					break;
				}
			}
			boost::erase_all(digitsAndSpaces, " ");
			if (!digitsAndSpaces.empty()) {
				double numerator = static_cast<double>(parseNonNegativeInteger(digitsAndSpaces));
				double denominator = pow(10, digitsAndSpaces.length());
				dimension.value += (numerator / denominator);
			}
		}
		ASCII::skipWhitespace(token, i);
		if (token[i] == '%') {
			dimension.type = DimensionType::PERCENTAGE;
		} else if (token[i] == '*') {
			dimension.type = DimensionType::RELATIVE;
		}
		dimensions.push_back(dimension);
	}
	return dimensions;
}

} /* namespace Numbers */
} /* namespace Microsyntaxes */
} /* namespace HTML */


