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

#include <ParseHTML/MagicString.hpp>
#include <ParseHTML/DetermineCharEncoding.hpp>

#include <gtest/gtest.h>
/**
 * @file test/ParseHTML/MagicString_test.cpp
 * @brief Holds all of the unit tests for ParseHTML/MagicString.hpp and ParseHTML/MagicString.cpp
 */

namespace ParseHTML {
namespace MagicString {

/**
 * @brief Holds all of the unit tests for the namespace ParseHTML::MagicString
 */
namespace MagicString_Test {

/**
 * @brief Test fixture for ParseHTML::MagicString::MetaTag
 */
class ParseHTML_MagicString_MetaTag_Test: public ::testing::Test {
	protected:
		ParseHTML::MagicString::MetaTag MetaTag;
		const ParseHTML::Byte equal[6] = { 0x3C, 0x4D, 0x65, 0x54, 0x61, 0x0C };
		const ParseHTML::Byte almostEqual[6] = { 0x3C, 0x4D, 0x65, 0x53, 0x61, 0x0C };
		const ParseHTML::Byte notEqual[6] = { 0x09, 0x0A, 0x0C, 0x0D, 0x20, 0x2F };

};
/**
 * @brief Test fixture for ParseHTML::MagicString::ASCIITag
 */
class ParseHTML_MagicString_ASCIITag_Test: public ::testing::Test {
	protected:
		ParseHTML::MagicString::ASCIITag ASCIITag;
		const ParseHTML::Byte equal[2] = { 0x3C, 0x5A };
		const ParseHTML::Byte almostEqual[2] = { 0x3C, 0x8A };
		const ParseHTML::Byte notEqual[2] = { 0x24, 0x8A };

};

/**
 * @brief Test fixture for ParseHTML::MagicString::ASCIIEndTag
 */
class ParseHTML_MagicString_ASCIIEndTag_Test: public ::testing::Test {
	protected:
		ParseHTML::MagicString::ASCIIEndTag ASCIIEndTag;
		const ParseHTML::Byte equal[3] = { 0x3C, 0x4D, 0x5A };
		const ParseHTML::Byte almostEqual[3] = { 0x3C, 0x4D, 0x8A };
		const ParseHTML::Byte notEqual[3] = { 0x24, 0x40, 0x8A };

};

/**
 * @brief Test fixture for ParseHTML::MagicString::PunctuationTag
 */
class ParseHTML_MagicString_PunctuationTag_Test: public ::testing::Test {
	protected:
		ParseHTML::MagicString::PunctuationTag PunctuationTag;
		const ParseHTML::Byte exclamationPointEqual[2] = { 0x3C, 0x21 };
		const ParseHTML::Byte forwardSlashEqual[2] = { 0x3C, 0x2F };
		const ParseHTML::Byte questionMarkEqual[2] = { 0x3C, 0x3F };
		const ParseHTML::Byte almostEqual[2] = { 0x3C, 0x20 };
		const ParseHTML::Byte notEqual[2] = { 0x24, 0x20 };

};

/**
 * @brief Test fixture for ParseHTML::MagicString::isASCIIUpperCaseLetter()
 */
class ParseHTML_MagicString_isASCIIUpperCaseLetter_Test: public ::testing::Test {
	protected:
		const ParseHTML::Byte trueCase = 0x53;
		const ParseHTML::Byte falseCase = 0x70;
};

/**
 * @brief Test fixture for ParseHTML::MagicString::isCharset()
 */
class ParseHTML_MagicString_isCharset_Test: public ::testing::Test {
	protected:
		const ParseHTML::Byte trueCase[7] = { 'C', 'h', 'A', 'r', 'S', 'e', 'T' };
		const ParseHTML::Byte falseCase[7] = { 'c', 'a', 'h', 't', 's', 'e', 'l' };
};
/**@{*/

TEST_F(ParseHTML_MagicString_MetaTag_Test, equal) {
	EXPECT_EQ(MetaTag, equal);
}
TEST_F(ParseHTML_MagicString_MetaTag_Test, almostEqual) {
	EXPECT_NE(MetaTag, almostEqual);
}
TEST_F(ParseHTML_MagicString_MetaTag_Test, notEqual) {
	EXPECT_NE(MetaTag, notEqual);
}

TEST_F(ParseHTML_MagicString_ASCIITag_Test, equal) {
	EXPECT_EQ(ASCIITag, equal);
}
TEST_F(ParseHTML_MagicString_ASCIITag_Test, almostEqual) {
	EXPECT_NE(ASCIITag, almostEqual);
}
TEST_F(ParseHTML_MagicString_ASCIITag_Test, notEqual) {
	EXPECT_NE(ASCIITag, notEqual);
}

TEST_F(ParseHTML_MagicString_ASCIIEndTag_Test, equal) {
	EXPECT_EQ(ASCIIEndTag, equal);
}
TEST_F(ParseHTML_MagicString_ASCIIEndTag_Test, almostEqual) {
	EXPECT_NE(ASCIIEndTag, almostEqual);
}
TEST_F(ParseHTML_MagicString_ASCIIEndTag_Test, notEqual) {
	EXPECT_NE(ASCIIEndTag, notEqual);
}

TEST_F(ParseHTML_MagicString_PunctuationTag_Test, exclamationPointEqual) {
	EXPECT_EQ(PunctuationTag, exclamationPointEqual);
}
TEST_F(ParseHTML_MagicString_PunctuationTag_Test, forwardSlashEqual) {
	EXPECT_EQ(PunctuationTag, forwardSlashEqual);
}
TEST_F(ParseHTML_MagicString_PunctuationTag_Test, questionMarkEqual) {
	EXPECT_EQ(PunctuationTag, questionMarkEqual);
}
TEST_F(ParseHTML_MagicString_PunctuationTag_Test, almostEqual) {
	EXPECT_NE(PunctuationTag, almostEqual);
}
TEST_F(ParseHTML_MagicString_PunctuationTag_Test, notEqual) {
	EXPECT_NE(PunctuationTag, notEqual);
}

TEST_F(ParseHTML_MagicString_isASCIIUpperCaseLetter_Test, trueCase) {
	EXPECT_TRUE(ParseHTML::MagicString::isASCIIUpperCaseLetter(trueCase));
}
TEST_F(ParseHTML_MagicString_isASCIIUpperCaseLetter_Test, falseCase) {
	EXPECT_FALSE(ParseHTML::MagicString::isASCIIUpperCaseLetter(falseCase));
}

TEST_F(ParseHTML_MagicString_isCharset_Test, trueCase) {
	EXPECT_TRUE(ParseHTML::MagicString::isCharset(trueCase));
}
TEST_F(ParseHTML_MagicString_isCharset_Test, falseCase) {
	EXPECT_FALSE(ParseHTML::MagicString::isCharset(falseCase));
}
/**@}*/

} /* namespace MagicString_Test */
} /* namespace MagicString */
} /* namespace ParseHTML */
