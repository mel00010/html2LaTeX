/*******************************************************************************
 * SignedInteger_test.cpp
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

#include <HTML/Microsyntaxes/Numbers/SignedInteger.hpp>
#include <HTML/Microsyntaxes/Numbers/NumbersTypes.hpp>

namespace HTML {
namespace Microsyntaxes {
namespace Numbers {

TEST(HTML_Microsyntaxes_Numbers_SignedInteger, isInteger) {
	EXPECT_TRUE(isInteger(std::u32string(U"0123456789")));
	EXPECT_TRUE(isInteger(std::u32string(U"-0123456789")));
	EXPECT_FALSE(isInteger(std::u32string(U"Not An Integer")));
	EXPECT_FALSE(isInteger(std::u32string(U"0-123456789")));
	EXPECT_FALSE(isInteger(std::u32string(U"0 123456789")));
	EXPECT_FALSE(isInteger(std::u32string(U"0a123456789")));
	EXPECT_FALSE(isInteger(std::u32string(U"")));
}

TEST(HTML_Microsyntaxes_Numbers_SignedInteger, parseInteger) {
	EXPECT_EQ(123456789, parseInteger(std::u32string(U"   0123456789")));
	EXPECT_EQ(123456789, parseInteger(std::u32string(U"0123456789   ")));
	EXPECT_EQ(123456789, parseInteger(std::u32string(U"0123456789")));
	EXPECT_EQ(-123456789, parseInteger(std::u32string(U"-0123456789")));
	EXPECT_EQ(123, parseInteger(std::u32string(U"0123 4567 89")));
	EXPECT_EQ(0, parseInteger(std::u32string(U"0-123456789")));

	EXPECT_THROW(parseInteger(std::u32string(U"Not an integer")), parseException);
	EXPECT_THROW(parseInteger(std::u32string(U"")), parseException);
}


} /* namespace Numbers */
} /* namespace Microsyntaxes */
} /* namespace HTML */
