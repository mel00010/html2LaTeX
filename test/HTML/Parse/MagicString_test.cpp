/*******************************************************************************
 * MagicString_test.cpp
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
#include <HTML/Parse/DetermineCharEncoding.hpp>
#include <HTML/Parse/MagicString.hpp>
/**
 * @file test/HTML/Parse/MagicString_test.cpp
 * @brief Holds all of the unit tests for HTML/Parse/MagicString.hpp and HTML/Parse/MagicString.cpp
 */
namespace HTML {
namespace Parse {
namespace MagicString {

/**
 * @brief Holds all of the unit tests for the namespace HTML::Parse::MagicString
 */
namespace MagicString_Test {

/**@{*/

TEST(HTML_Parse_MagicString, MetaTag) {
	HTML::Parse::MagicString::MetaTag MetaTag;

	const HTML::Parse::Byte equal[6] = { '\x3C', '\x4D', '\x65', '\x54', '\x61', '\x0C' };
	const HTML::Parse::Byte almostEqual[6] = { '\x3C', '\x4D', '\x65', '\x53', '\x61', '\x0C' };
	const HTML::Parse::Byte notEqual[6] = { '\x09', '\x0A', '\x0C', '\x0D', '\x20', '\x2F' };

	EXPECT_EQ(MetaTag, equal);
	EXPECT_NE(MetaTag, almostEqual);
	EXPECT_NE(MetaTag, notEqual);
}


TEST(HTML_Parse_MagicString, ASCIITag) {
	HTML::Parse::MagicString::ASCIITag ASCIITag;

	const HTML::Parse::Byte equal[2] = { '\x3C', '\x5A' };
	const HTML::Parse::Byte almostEqual[2] = { '\x3C', '\x8A' };
	const HTML::Parse::Byte notEqual[2] = { '\x24', '\x8A' };

	EXPECT_EQ(ASCIITag, equal);
	EXPECT_NE(ASCIITag, almostEqual);
	EXPECT_NE(ASCIITag, notEqual);

}


TEST(HTML_Parse_MagicString, ASCIIEndTag) {
	HTML::Parse::MagicString::ASCIIEndTag ASCIIEndTag;

	const HTML::Parse::Byte equal[3] = { '\x3C', '\x4D', '\x5A' };
	const HTML::Parse::Byte almostEqual[3] = { '\x3C', '\x4D', '\x8A' };
	const HTML::Parse::Byte notEqual[3] = { '\x24', '\x40', '\x8A' };
	EXPECT_EQ(ASCIIEndTag, equal);
	EXPECT_NE(ASCIIEndTag, almostEqual);
	EXPECT_NE(ASCIIEndTag, notEqual);

}


TEST(HTML_Parse_MagicString, PunctuationTag) {
	HTML::Parse::MagicString::PunctuationTag PunctuationTag;

	const HTML::Parse::Byte exclamationPointEqual[2] = { '\x3C', '\x21' };
	const HTML::Parse::Byte forwardSlashEqual[2] = { '\x3C', '\x2F' };
	const HTML::Parse::Byte questionMarkEqual[2] = { '\x3C', '\x3F' };
	const HTML::Parse::Byte almostEqual[2] = { '\x3C', '\x20' };
	const HTML::Parse::Byte notEqual[2] = { '\x24', '\x20' };

	EXPECT_EQ(PunctuationTag, exclamationPointEqual);
	EXPECT_EQ(PunctuationTag, forwardSlashEqual);
	EXPECT_EQ(PunctuationTag, questionMarkEqual);
	EXPECT_NE(PunctuationTag, almostEqual);
	EXPECT_NE(PunctuationTag, notEqual);

}


TEST(HTML_Parse_MagicString, isCharset) {
	const HTML::Parse::Byte trueCase[7] = { 'C', 'h', 'A', 'r', 'S', 'e', 'T' };
	const HTML::Parse::Byte falseCase[7] = { 'c', 'a', 'h', 't', 's', 'e', 'l' };

	EXPECT_TRUE(HTML::Parse::MagicString::isCharset(trueCase));
	EXPECT_FALSE(HTML::Parse::MagicString::isCharset(falseCase));

}
/**@}*/

} /* namespace MagicString_Test */
} /* namespace MagicString */
} /* namespace ParseHTML */
} /* namespace HTML */
