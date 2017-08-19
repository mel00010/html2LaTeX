/*******************************************************************************
 * FloatingPoint_test.cpp
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
#include <iostream>

#include <HTML/Microsyntaxes/Numbers/FloatingPoint.hpp>
#include <HTML/Microsyntaxes/Numbers/NumbersTypes.hpp>

namespace HTML {
namespace Microsyntaxes {
namespace Numbers {

TEST(HTML_Microsyntaxes_Numbers_FloatingPoint, isFloatingPoint) {
	EXPECT_TRUE(isFloatingPoint("123"));
	EXPECT_TRUE(isFloatingPoint("123.456"));
	EXPECT_TRUE(isFloatingPoint("123.456E7"));
	EXPECT_TRUE(isFloatingPoint("123.456e7"));
	EXPECT_TRUE(isFloatingPoint("-123.456e7"));
	EXPECT_TRUE(isFloatingPoint("-123.456E7"));
	EXPECT_TRUE(isFloatingPoint("-123e4"));
	EXPECT_TRUE(isFloatingPoint("-123E4"));
	EXPECT_TRUE(isFloatingPoint("123E4"));
	EXPECT_TRUE(isFloatingPoint("123e4"));
	EXPECT_TRUE(isFloatingPoint("-123e-4"));
	EXPECT_FALSE(isFloatingPoint("   123e4"));
	EXPECT_FALSE(isFloatingPoint("123-e4"));
	EXPECT_FALSE(isFloatingPoint("Not a floating point number"));
	EXPECT_FALSE(isFloatingPoint("-12-34"));
	EXPECT_FALSE(isFloatingPoint("1e2e3"));
	EXPECT_FALSE(isFloatingPoint("1..2"));
}

TEST(HTML_Microsyntaxes_Numbers_FloatingPoint, parseFloatingPoint) {
	EXPECT_DOUBLE_EQ(123.456l, parseFloatingPoint("123.456"));
	EXPECT_DOUBLE_EQ(123.456e7l, parseFloatingPoint("123.456e7"));
	EXPECT_DOUBLE_EQ(-123l, parseFloatingPoint("-123"));
	EXPECT_DOUBLE_EQ(123l, parseFloatingPoint("123"));
	EXPECT_DOUBLE_EQ(-123e-4l, parseFloatingPoint("-123e-4"));
	EXPECT_DOUBLE_EQ(123E4l, parseFloatingPoint("123E4"));
	EXPECT_THROW(parseFloatingPoint("123-e4"), parseException);
	EXPECT_THROW(parseFloatingPoint("Not a floating point number"), parseException);
	EXPECT_THROW(parseFloatingPoint("-12-34"), parseException);
	EXPECT_THROW(parseFloatingPoint("1e2e3"), parseException);
	EXPECT_THROW(parseFloatingPoint("1..2"), parseException);
}

} /* namespace Numbers */
} /* namespace Microsyntaxes */
} /* namespace HTML */


