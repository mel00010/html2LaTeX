/*******************************************************************************
 * NumbersTypes.cpp
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

#include "NumbersTypes.hpp"

//#include <iostream>

namespace HTML {
namespace Microsyntaxes {
namespace Numbers {

parseException::parseException() {
}

parseException::parseException(const char* error_message) {
	message = error_message;
}

const char* parseException::what() const noexcept {
	return message;
}

::std::ostream& operator<<(::std::ostream& os, const parseException& parseException) {
	return os << parseException.what();
}

::std::ostream& operator<<(::std::ostream& os, const Dimension& dimension) {
	return os << dimension.value << ":" << dimension.type;
}
::std::ostream& operator<<(::std::ostream& os, const DimensionType& dimensionType) {
	switch (dimensionType) {
		case DimensionType::UNKNOWN:
			os << "DimensionType::UNKNOWN";
			break;
		case DimensionType::LENGTH:
			os << "DimensionType::LENGTH";
			break;
		case DimensionType::PERCENTAGE:
			os << "DimensionType::PERCENTAGE";
			break;
		case DimensionType::RELATIVE:
			os << "DimensionType::RELATIVE";
			break;
		case DimensionType::ABSOLUTE:
			os << "DimensionType::ABSOLUTE";
			break;
		default:
			os << "Error:  Value is not defined in enum DimensionType!";
			break;
	}
	return os;
}

} /* namespace Numbers */
} /* namespace Microsyntaxes */
} /* namespace HTML */
