/*******************************************************************************
 * ParseUnicode_test.cpp
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
#include <gtest/gtest.h>

#include <HTML/Parse/ParseUnicode.hpp>

#include <HTML/HTMLTypes.hpp>
#include <HTML/Parse/ParseTypes.hpp>

#include <string>
#include <type_traits>

namespace HTML {
namespace Parse {

TEST(HTML_Parse_ParseUnicode, parseUnicode) {
	EXPECT_EQ(std::u32string(U"\U00000024"), parseUnicode( {'\x24'}, ContentType(CharEncoding::UTF_8, Confidence::CERTAIN)));
	EXPECT_EQ(std::u32string(U"\U000000A2"), parseUnicode( {'\xC2','\xA2'}, ContentType(CharEncoding::UTF_8, Confidence::CERTAIN)));
	EXPECT_EQ(std::u32string(U"\U000020AC"), parseUnicode( {'\xE2','\x82','\xAC'}, ContentType(CharEncoding::UTF_8, Confidence::CERTAIN)));
	EXPECT_EQ(std::u32string(U"\U00010348"), parseUnicode( {'\xF0','\x90','\x8D','\x88'}, ContentType(CharEncoding::UTF_8, Confidence::CERTAIN)));

	EXPECT_EQ(std::u32string(U"\U00000024"), parseUnicode( {'\x00','\x24'}, ContentType(CharEncoding::UTF_16_BE, Confidence::CERTAIN)));
	EXPECT_EQ(std::u32string(U"\U000020AC"), parseUnicode( {'\x20','\xAC'}, ContentType(CharEncoding::UTF_16_BE, Confidence::CERTAIN)));
	EXPECT_EQ(std::u32string(U"\U00010437"), parseUnicode( {'\xD8','\x01','\xDC','\x37'}, ContentType(CharEncoding::UTF_16_BE, Confidence::CERTAIN)));
	EXPECT_EQ(std::u32string(U"\U00024B62"), parseUnicode( {'\xD8','\x52','\xDF','\x62'}, ContentType(CharEncoding::UTF_16_BE, Confidence::CERTAIN)));

	EXPECT_EQ(std::u32string(U"\U00000024"), parseUnicode( {'\x24','\x00'}, ContentType(CharEncoding::UTF_16_LE, Confidence::CERTAIN)));
	EXPECT_EQ(std::u32string(U"\U000020AC"), parseUnicode( {'\xAC','\x20'}, ContentType(CharEncoding::UTF_16_LE, Confidence::CERTAIN)));
	EXPECT_EQ(std::u32string(U"\U00010437"), parseUnicode( {'\x01','\xD8','\x37','\xDC'}, ContentType(CharEncoding::UTF_16_LE, Confidence::CERTAIN)));
	EXPECT_EQ(std::u32string(U"\U00024B62"), parseUnicode( {'\x52','\xD8','\x62','\xDF'}, ContentType(CharEncoding::UTF_16_LE, Confidence::CERTAIN)));

	EXPECT_THROW(parseUnicode("", ContentType(CharEncoding::NULL_ENC, Confidence::CERTAIN)), UnicodeParseException);
	EXPECT_THROW(parseUnicode("", ContentType(CharEncoding::UNKNOWN, Confidence::CERTAIN)), UnicodeParseException);
}

}
/* namespace HTML */
} /* namespace Parse */
