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

/**
 * @brief Test fixture for HTML::Parse::MagicString::MetaTag
 */
class HTML_Parse_MagicString_MetaTag_Test: public ::testing::Test {
	protected:
		HTML::Parse::MagicString::MetaTag MetaTag;
		const HTML::Parse::Byte equal[6] = { 0x3C, 0x4D, 0x65, 0x54, 0x61, 0x0C };
		const HTML::Parse::Byte almostEqual[6] = { 0x3C, 0x4D, 0x65, 0x53, 0x61, 0x0C };
		const HTML::Parse::Byte notEqual[6] = { 0x09, 0x0A, 0x0C, 0x0D, 0x20, 0x2F };

};
/**
 * @brief Test fixture for HTML::Parse::MagicString::ASCIITag
 */
class HTML_Parse_MagicString_ASCIITag_Test: public ::testing::Test {
	protected:
		HTML::Parse::MagicString::ASCIITag ASCIITag;
		const HTML::Parse::Byte equal[2] = { 0x3C, 0x5A };
		const HTML::Parse::Byte almostEqual[2] = { 0x3C, 0x8A };
		const HTML::Parse::Byte notEqual[2] = { 0x24, 0x8A };

};

/**
 * @brief Test fixture for HTML::Parse::MagicString::ASCIIEndTag
 */
class HTML_Parse_MagicString_ASCIIEndTag_Test: public ::testing::Test {
	protected:
		HTML::Parse::MagicString::ASCIIEndTag ASCIIEndTag;
		const HTML::Parse::Byte equal[3] = { 0x3C, 0x4D, 0x5A };
		const HTML::Parse::Byte almostEqual[3] = { 0x3C, 0x4D, 0x8A };
		const HTML::Parse::Byte notEqual[3] = { 0x24, 0x40, 0x8A };

};

/**
 * @brief Test fixture for HTML::Parse::MagicString::PunctuationTag
 */
class HTML_Parse_MagicString_PunctuationTag_Test: public ::testing::Test {
	protected:
		HTML::Parse::MagicString::PunctuationTag PunctuationTag;
		const HTML::Parse::Byte exclamationPointEqual[2] = { 0x3C, 0x21 };
		const HTML::Parse::Byte forwardSlashEqual[2] = { 0x3C, 0x2F };
		const HTML::Parse::Byte questionMarkEqual[2] = { 0x3C, 0x3F };
		const HTML::Parse::Byte almostEqual[2] = { 0x3C, 0x20 };
		const HTML::Parse::Byte notEqual[2] = { 0x24, 0x20 };

};


/**
 * @brief Test fixture for HTML::Parse::MagicString::isCharset()
 */
class HTML_Parse_MagicString_isCharset_Test: public ::testing::Test {
	protected:
		const HTML::Parse::Byte trueCase[7] = { 'C', 'h', 'A', 'r', 'S', 'e', 'T' };
		const HTML::Parse::Byte falseCase[7] = { 'c', 'a', 'h', 't', 's', 'e', 'l' };
};
/**@{*/

TEST_F(HTML_Parse_MagicString_MetaTag_Test, equal) {
	EXPECT_EQ(MetaTag, equal);
}
TEST_F(HTML_Parse_MagicString_MetaTag_Test, almostEqual) {
	EXPECT_NE(MetaTag, almostEqual);
}
TEST_F(HTML_Parse_MagicString_MetaTag_Test, notEqual) {
	EXPECT_NE(MetaTag, notEqual);
}

TEST_F(HTML_Parse_MagicString_ASCIITag_Test, equal) {
	EXPECT_EQ(ASCIITag, equal);
}
TEST_F(HTML_Parse_MagicString_ASCIITag_Test, almostEqual) {
	EXPECT_NE(ASCIITag, almostEqual);
}
TEST_F(HTML_Parse_MagicString_ASCIITag_Test, notEqual) {
	EXPECT_NE(ASCIITag, notEqual);
}

TEST_F(HTML_Parse_MagicString_ASCIIEndTag_Test, equal) {
	EXPECT_EQ(ASCIIEndTag, equal);
}
TEST_F(HTML_Parse_MagicString_ASCIIEndTag_Test, almostEqual) {
	EXPECT_NE(ASCIIEndTag, almostEqual);
}
TEST_F(HTML_Parse_MagicString_ASCIIEndTag_Test, notEqual) {
	EXPECT_NE(ASCIIEndTag, notEqual);
}

TEST_F(HTML_Parse_MagicString_PunctuationTag_Test, exclamationPointEqual) {
	EXPECT_EQ(PunctuationTag, exclamationPointEqual);
}
TEST_F(HTML_Parse_MagicString_PunctuationTag_Test, forwardSlashEqual) {
	EXPECT_EQ(PunctuationTag, forwardSlashEqual);
}
TEST_F(HTML_Parse_MagicString_PunctuationTag_Test, questionMarkEqual) {
	EXPECT_EQ(PunctuationTag, questionMarkEqual);
}
TEST_F(HTML_Parse_MagicString_PunctuationTag_Test, almostEqual) {
	EXPECT_NE(PunctuationTag, almostEqual);
}
TEST_F(HTML_Parse_MagicString_PunctuationTag_Test, notEqual) {
	EXPECT_NE(PunctuationTag, notEqual);
}

TEST_F(HTML_Parse_MagicString_isCharset_Test, trueCase) {
	EXPECT_TRUE(HTML::Parse::MagicString::isCharset(trueCase));
}
TEST_F(HTML_Parse_MagicString_isCharset_Test, falseCase) {
	EXPECT_FALSE(HTML::Parse::MagicString::isCharset(falseCase));
}
/**@}*/

} /* namespace MagicString_Test */
} /* namespace MagicString */
} /* namespace ParseHTML */
} /* namespace HTML */
