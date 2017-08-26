/*******************************************************************************
 * Dimension_test.cpp
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

#include <HTML/Microsyntaxes/Numbers/Dimension.hpp>
#include <HTML/Microsyntaxes/Numbers/NumbersTypes.hpp>

#include <gtest/gtest.h>


namespace HTML {
namespace Microsyntaxes {
namespace Numbers {

TEST(HTML_Microsyntaxes_Numbers_Dimension, isDimension) {
	EXPECT_TRUE(isDimension("1"));
	EXPECT_TRUE(isDimension("01"));
	EXPECT_TRUE(isDimension("010"));
	EXPECT_TRUE(isDimension("1%"));
	EXPECT_TRUE(isDimension("1.0"));
	EXPECT_TRUE(isDimension("1.0%"));
	EXPECT_TRUE(isDimension("01.0%"));
	EXPECT_TRUE(isDimension("0001.0%"));
	EXPECT_TRUE(isDimension("0001.0"));
	EXPECT_TRUE(isDimension("0001"));
	EXPECT_TRUE(isDimension("0002"));
	EXPECT_FALSE(isDimension(""));
	EXPECT_FALSE(isDimension("a"));
	EXPECT_FALSE(isDimension("0a1"));
	EXPECT_FALSE(isDimension("01.a"));
	EXPECT_FALSE(isDimension("0.1&"));
	EXPECT_FALSE(isDimension("1.1.1"));
	EXPECT_FALSE(isDimension("00000"));
	EXPECT_FALSE(isDimension("0"));
	EXPECT_FALSE(isDimension("%"));
	EXPECT_FALSE(isDimension("."));
	EXPECT_FALSE(isDimension("1.0e10"));
	EXPECT_FALSE(isDimension("0.1"));
	EXPECT_FALSE(isDimension("0.1%"));
	EXPECT_FALSE(isDimension("0."));
	EXPECT_FALSE(isDimension(".0"));
}

TEST(HTML_Microsyntaxes_Numbers_Dimension, parseDimension) {
	EXPECT_EQ(Dimension(1, DimensionType::LENGTH), parseDimension("1"));
	EXPECT_EQ(Dimension(1, DimensionType::LENGTH), parseDimension("01"));
	EXPECT_EQ(Dimension(10, DimensionType::LENGTH), parseDimension("010"));
	EXPECT_EQ(Dimension(1, DimensionType::PERCENTAGE), parseDimension("1%"));
	EXPECT_EQ(Dimension(1, DimensionType::LENGTH), parseDimension("1.0"));
	EXPECT_EQ(Dimension(1.1, DimensionType::LENGTH), parseDimension("1.1"));
	EXPECT_EQ(Dimension(10.1, DimensionType::LENGTH), parseDimension("10.1"));
	EXPECT_EQ(Dimension(12.34, DimensionType::LENGTH), parseDimension("12.34"));
	EXPECT_EQ(Dimension(1, DimensionType::PERCENTAGE), parseDimension("1.0%"));
	EXPECT_EQ(Dimension(1, DimensionType::PERCENTAGE), parseDimension("01.0%"));
	EXPECT_EQ(Dimension(1, DimensionType::PERCENTAGE), parseDimension("0001.0%"));
	EXPECT_EQ(Dimension(1, DimensionType::LENGTH), parseDimension("0001.0"));
	EXPECT_EQ(Dimension(1, DimensionType::LENGTH), parseDimension("0001"));
	EXPECT_EQ(Dimension(2, DimensionType::LENGTH), parseDimension("0002"));
	EXPECT_EQ(Dimension(1.1, DimensionType::LENGTH), parseDimension("1.1.1"));
	EXPECT_EQ(Dimension(1, DimensionType::LENGTH), parseDimension("1.0e10"));
	EXPECT_EQ(Dimension(1, DimensionType::LENGTH), parseDimension("01.a"));
	EXPECT_EQ(Dimension(1, DimensionType::LENGTH), parseDimension("01.a&"));
	EXPECT_THROW(parseDimension(""), parseException);
	EXPECT_THROW(parseDimension("a"), parseException);
	EXPECT_THROW(parseDimension("0a1"), parseException);
	EXPECT_THROW(parseDimension("00000"), parseException);
	EXPECT_THROW(parseDimension("0"), parseException);
	EXPECT_THROW(parseDimension("%"), parseException);
	EXPECT_THROW(parseDimension("."), parseException);
	EXPECT_THROW(parseDimension("0.1"), parseException);
	EXPECT_THROW(parseDimension("0.1%"), parseException);
	EXPECT_THROW(parseDimension("0."), parseException);
	EXPECT_THROW(parseDimension(".0"), parseException);
}

} /* namespace Numbers */
} /* namespace Microsyntaxes */
} /* namespace HTML */


