/*******************************************************************************
 * HTMLTypes.cpp
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

#include <HTMLTypes.hpp>
#include <iostream>

namespace HTML {

::std::ostream& operator<<(::std::ostream& os, const Attribute& attribute) {
	return os << "\"" << attribute.name << "\":\"" << attribute.value << "\"";
}
::std::ostream& operator<<(::std::ostream& os, const CharEncoding& charEncoding) {
	switch (charEncoding) {
		case NULL_ENC:
			os << "NULL_ENC";
			break;
		case UNKNOWN:
			os << "UNKNOWN";
			break;
		case UTF_16_BE:
			os << "UTF_16_BE";
			break;
		case UTF_16_LE:
			os << "UTF_16_LE";
			break;
		case UTF_8:
			os << "UTF_8";
			break;
		default: // LCOV_EXCL_LINE
			os << "INVALID"; // LCOV_EXCL_LINE
	}
	return os;
}
::std::ostream& operator<<(::std::ostream& os, const Confidence& confidence) {
	switch (confidence) {
		case CERTAIN:
			os << "CERTAIN";
			break;
		case TENTATIVE:
			os << "TENTATIVE";
			break;
		case IRRELEVANT:
			os << "IRRELEVANT";
			break;
		default: // LCOV_EXCL_LINE
			os << "INVALID"; // LCOV_EXCL_LINE
	}
	return os;
}
::std::ostream& operator<<(::std::ostream& os, const ContentType& contentType) {
	return os << contentType.charEncoding << ":" << contentType.confidence;
}


} /* namespace HTML */ // LCOV_EXCL_LINE
