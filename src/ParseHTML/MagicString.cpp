/*******************************************************************************
 * MagicString.cpp
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

#include <ParseHTML/MagicString.hpp>

namespace ParseHTML {
namespace MagicString {

/**
 * @file ParseHTML/MagicString.cpp
 * @brief Implements ParseHTML::MagicString::isASCIIUpperCaseLetter and ParseHTML::MagicString::isCharset
 */

bool isASCIIUpperCaseLetter(const Byte& buf) {
	for (auto& i : ASCIIUpperCaseLetters) {
		if (buf == i) {
			return true;
		}
	}
	return false;
}

bool isCharset(const Byte (&string)[7]) {
	if (((string[0] == 'c') || (string[0] == 'C')) &&
			((string[1] == 'h') || (string[1] == 'H')) &&
			((string[2] == 'a') || (string[2] == 'A')) &&
			((string[3] == 'r') || (string[3] == 'R')) &&
			((string[4] == 's') || (string[4] == 'S')) &&
			((string[5] == 'e') || (string[5] == 'E')) &&
			((string[6] == 't') || (string[6] == 'T'))) {
		return true;
	}
	return false;
}

} /* namespace MagicString */
} /* namespace ParseHTML */
