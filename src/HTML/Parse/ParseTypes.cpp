/*******************************************************************************
 * ParseTypes.cpp
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

#include "ParseTypes.hpp"

namespace HTML {
namespace Parse {

UnicodeParseException::UnicodeParseException() {
}

UnicodeParseException::UnicodeParseException(const char* error_message) {
	message = error_message;
}

const char* UnicodeParseException::what() const noexcept {
	return message;
}
::std::ostream& operator<<(::std::ostream& os, const UnicodeParseException& unicode_parse_exception) {
	return os << unicode_parse_exception.what();
}

} /* namespace Parse */
} /* namespace HTML */
