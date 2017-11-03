/*******************************************************************************
 * NonNegativeInteger_test.cpp
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

#include <HTML/Microsyntaxes/Numbers/NonNegativeInteger.hpp>
#include <HTML/Microsyntaxes/Numbers/NumbersTypes.hpp>

namespace HTML {
namespace Microsyntaxes {
namespace Numbers {

TEST(HTML_Microsyntaxes_Numbers_NonNegativeInteger, isNonNegativeInteger) {
	EXPECT_TRUE(isNonNegativeInteger(std::u32string(U"0123456789")));
	EXPECT_FALSE(isNonNegativeInteger(std::u32string(U"-0123456789")));
	EXPECT_FALSE(isNonNegativeInteger(std::u32string(U"Not An Integer")));
	EXPECT_FALSE(isNonNegativeInteger(std::u32string(U"0-123456789")));
	EXPECT_FALSE(isNonNegativeInteger(std::u32string(U"0 123456789")));
	EXPECT_FALSE(isNonNegativeInteger(std::u32string(U"0a123456789")));
	EXPECT_FALSE(isNonNegativeInteger(std::u32string(U"")));
}
TEST(HTML_Microsyntaxes_Numbers_NonNegativeInteger, isNonNegativeHexInteger) {
	EXPECT_TRUE(isNonNegativeHexInteger(std::u32string(U"0123456789abcdefABCDEF")));
	EXPECT_FALSE(isNonNegativeHexInteger(std::u32string(U"-0123456789")));
	EXPECT_FALSE(isNonNegativeHexInteger(std::u32string(U"Not An Integer")));
	EXPECT_FALSE(isNonNegativeHexInteger(std::u32string(U"0-123456789")));
	EXPECT_FALSE(isNonNegativeHexInteger(std::u32string(U"0 123456789")));
	EXPECT_FALSE(isNonNegativeHexInteger(std::u32string(U"")));
}


TEST(HTML_Microsyntaxes_Numbers_NonNegativeInteger, parseNonNegativeInteger) {
	EXPECT_EQ(123456789u, parseNonNegativeInteger(std::u32string(U"   0123456789")));
	EXPECT_EQ(123456789u, parseNonNegativeInteger(std::u32string(U"0123456789   ")));
	EXPECT_EQ(123456789u, parseNonNegativeInteger(std::u32string(U"0123456789")));

	EXPECT_EQ(123u, parseNonNegativeInteger(std::u32string(U"0123 4567 89")));
	EXPECT_EQ(0u, parseNonNegativeInteger(std::u32string(U"0-123456789")));

	EXPECT_THROW(parseNonNegativeInteger(std::u32string(U"-0123456789")), parseException);
	EXPECT_THROW(parseNonNegativeInteger(std::u32string(U"Not an integer")), parseException);
	EXPECT_THROW(parseNonNegativeInteger(std::u32string(U"")), parseException);
}
TEST(HTML_Microsyntaxes_Numbers_NonNegativeInteger, parseNonNegativeHexInteger) {
	EXPECT_EQ(0x123456789u, parseNonNegativeHexInteger(std::u32string(U"   0123456789")));
	EXPECT_EQ(0x123456789ABCDEFu, parseNonNegativeHexInteger(std::u32string(U"0123456789ABCDEF   ")));
	EXPECT_EQ(0x123456789ABCDEFu, parseNonNegativeHexInteger(std::u32string(U"0123456789abcdef")));

	EXPECT_EQ(0x123u, parseNonNegativeHexInteger(std::u32string(U"0123 4567 89 a b c d e f")));
	EXPECT_EQ(0x0u, parseNonNegativeHexInteger(std::u32string(U"0-123456789abcdefABCDEF")));

	EXPECT_THROW(parseNonNegativeHexInteger(std::u32string(U"-0123456789abcdefABCDEF")), parseException);
	EXPECT_THROW(parseNonNegativeHexInteger(std::u32string(U"Not an integer")), parseException);
	EXPECT_THROW(parseNonNegativeHexInteger(std::u32string(U"")), parseException);
}

} /* namespace Numbers */
} /* namespace Microsyntaxes */
} /* namespace HTML */

