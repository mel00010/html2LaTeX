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

#include "HTMLTypes.hpp"

#include <codecvt>
#include <locale>

namespace HTML {

::std::ostream& operator<<(::std::ostream& os, const ASCIIAttribute& attribute) {
	return os << "\"" << attribute.name << "\":\"" << attribute.value << "\"";
}

::std::ostream& operator<<(::std::ostream& os, const Attribute& attribute) {
	return os << "\"" << std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t>().to_bytes(attribute.name)
			<< "\":\"" << std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t>().to_bytes(attribute.value) << "\"";
}
::std::ostream& operator<<(::std::ostream& os, const CharEncoding& charEncoding) {
	switch (charEncoding) {
		case CharEncoding::NULL_ENC:
			os << "CharEncoding::NULL_ENC";
			break;
		case CharEncoding::UNKNOWN:
			os << "CharEncoding::UNKNOWN";
			break;
		case CharEncoding::UTF_16_BE:
			os << "CharEncoding::UTF_16_BE";
			break;
		case CharEncoding::UTF_16_LE:
			os << "CharEncoding::UTF_16_LE";
			break;
		case CharEncoding::UTF_8:
			os << "CharEncoding::UTF_8";
			break;
		default: // LCOV_EXCL_LINE
			os << "Unknown CharEncoding!"; // LCOV_EXCL_LINE
	}
	return os;
}
::std::ostream& operator<<(::std::ostream& os, const Confidence& confidence) {
	switch (confidence) {
		case Confidence::CERTAIN:
			os << "Confidence::CERTAIN";
			break;
		case Confidence::TENTATIVE:
			os << "Confidence::TENTATIVE";
			break;
		case Confidence::IRRELEVANT:
			os << "Confidence::IRRELEVANT";
			break;
		default: // LCOV_EXCL_LINE
			os << "Unknown Confidence!"; // LCOV_EXCL_LINE
	}
	return os;
}
::std::ostream& operator<<(::std::ostream& os, const ContentType& contentType) {
	return os << contentType.char_encoding << ":" << contentType.confidence;
}


} /* namespace HTML */ // LCOV_EXCL_LINE
