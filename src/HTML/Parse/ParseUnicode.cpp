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
enum ByteOrder {
	big_endian,
	little_endian
};

template<class T, ByteOrder byte_order = big_endian, typename = std::enable_if_t<
		std::is_same_v<T, char> || std::is_same_v<T, char16_t> || std::is_same_v<T, char32_t>>>
std::u32string parseUTF(const std::string& string) {
	constexpr size_t code_units = sizeof(T) / 4;
	std::u32string converted;
	converted.reserve(string.length());

	size_t byte_number = 0;
	size_t code_units_remaining = code_units;
	auto u32it = converted.begin();
	for (auto it = string.begin(); it != string.end(); it++) {
		byte_number++;
		if (code_units_remaining <= 0) {
			u32it++;
			byte_number = 0;
			code_units_remaining = code_units;
		}
		if (std::is_same_v<T, char>) {
			if (byte_number == 0 && code_units_remaining != 0) {
				char four_byte_mask = 0b11111000;
				char four_byte_pattern = 0b11110000;
				char three_byte_mask = 0b11110000;
				char three_byte_pattern = 0b11100000;
				char two_byte_mask = 0b11100000;
				char two_byte_pattern = 0b11000000;
				char one_byte_mask = 0b10000000;
				char one_byte_pattern = 0b00000000;

				if ((*it & four_byte_mask) == four_byte_pattern) {
					code_units_remaining = 4;
					code_units_remaining--;
					*u32it = static_cast<char32_t>((*it & four_byte_mask) >> 5) << (code_units_remaining * 8);
				} else if ((*it & three_byte_mask) == three_byte_pattern) {
					code_units_remaining = 3;
					code_units_remaining--;
					*u32it = static_cast<char32_t>((*it & three_byte_mask) >> 4) << (code_units_remaining * 8);
				} else if ((*it & two_byte_mask) == two_byte_pattern) {
					code_units_remaining = 2;
					code_units_remaining--;

					*u32it = static_cast<char32_t>((*it & two_byte_mask) >> 3) << (code_units_remaining * 8);
				} else if ((*it & one_byte_mask) == one_byte_pattern) {
					code_units_remaining = 1;
					code_units_remaining--;
					*u32it = static_cast<char32_t>((*it & one_byte_mask) >> 1) << (code_units_remaining * 8);
				} else {
					throw UnicodeParseException();
				}
			} else if (code_units_remaining != 0) {
				char continuation_mask = 0b11000000;
				char continuation_pattern = 0b11000000;
				if (((*it) & continuation_mask) == continuation_pattern) {
					code_units_remaining--;
					*u32it = static_cast<char32_t>((*it & continuation_mask) >> 2) << (code_units_remaining * 8);
				} else {
					throw UnicodeParseException();
				}
			}
		} else if (std::is_same_v<T, char16_t>) {
			if (byte_number == 0 && code_units_remaining != 0) {
				char two_byte_mask = 0b11111100;
				char two_byte_pattern = 0b11011000;

				if ((*it & two_byte_mask) == two_byte_pattern) {
					code_units_remaining = 2;
					code_units_remaining--;
					*u32it = static_cast<char32_t>((*it & two_byte_mask) >> 6) << (code_units_remaining * 16);
				} else {
					code_units_remaining = 1;
					code_units_remaining--;
					*u32it = static_cast<char32_t>((*it & two_byte_mask) >> 0) << (code_units_remaining * 16);
				}
			} else if (code_units_remaining != 0) {
				char continuation_mask = 0b11111100;
				char continuation_pattern = 0b11011100;
				if (((*it) & continuation_mask) == continuation_pattern) {
					code_units_remaining--;
					*u32it = static_cast<char32_t>((*it & continuation_mask) >> 6) << (code_units_remaining * 16);
				} else {
					throw UnicodeParseException();
				}
			}
		} else if (std::is_same_v<T, char32_t>) {
			*u32it = *it;
			code_units_remaining--;
		}
	}

	return converted;
}

std::u32string parseUnicode(const std::string& string, const ContentType& content_type) {
	switch (content_type.char_encoding) {
		case CharEncoding::UTF_8: {
			return parseUTF<char>(string);
			break;
		}
		case CharEncoding::UTF_16_BE: {
			return parseUTF<char16_t>(string);
			break;
		}
		case CharEncoding::UTF_16_LE: {
			return parseUTF<char16_t, little_endian>(string);
			break;
		}
		default: {
			throw UnicodeParseException();
			break;
		}
	}
}

std::u32string parseUnicodeOld(const std::string& string, const ContentType& content_type) {
	switch (content_type.char_encoding) {
		case CharEncoding::UTF_8:
			return std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> { }.from_bytes(string);
			break;
		case CharEncoding::UTF_16_BE:
			return std::wstring_convert<std::codecvt_utf16<char32_t>, char32_t> { }.from_bytes(string);
			break;
		case CharEncoding::UTF_16_LE:
			return std::wstring_convert<std::codecvt_utf16<char32_t, std::codecvt_mode::little_endian>, char32_t> { }.from_bytes(string);
			break;
		default:
			throw UnicodeParseException();
			break;
	}
}

} /* namespace Parse */
} /* namespace HTML */
