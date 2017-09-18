/*******************************************************************************
 * ParseUnicode.cpp
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

#include "ParseUnicode.hpp"

#include "ParseTypes.hpp"

#include <codecvt>
#include <cstring>
#include <locale>

namespace HTML {
namespace Parse {

std::u32string parseUnicode(const std::string& string, const ContentType& content_type) {
	switch (content_type.char_encoding) {
		case CharEncoding::UTF_8:
			return std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> { }.from_bytes(string);
			break;
		case CharEncoding::UTF_16_BE:
			return std::wstring_convert<std::codecvt_utf16<char32_t>, char32_t> { }.from_bytes(string);
			break;
		case CharEncoding::UTF_16_LE:
			return std::wstring_convert<std::codecvt_utf16<char32_t, 0x10ffff, std::codecvt_mode::little_endian>, char32_t> { }.from_bytes(string);
			break;
		default:
			throw UnicodeParseException();
			break;
	}
}

} /* namespace Parse */
} /* namespace HTML */
