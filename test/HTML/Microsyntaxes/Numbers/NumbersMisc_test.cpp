/*******************************************************************************
 * NumbersMisc_test.cpp
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

#include <HTML/Microsyntaxes/Numbers/NumbersMisc.hpp>
#include <HTML/Microsyntaxes/Numbers/NumbersTypes.hpp>

namespace HTML {
namespace Microsyntaxes {
namespace Numbers {

TEST(HTML_Microsyntaxes_Numbers_NumbersMisc, ASCIIDigitToInt) {
	EXPECT_EQ(0u, ASCIIDigitToInt('0'));
	EXPECT_EQ(1u, ASCIIDigitToInt('1'));
	EXPECT_EQ(2u, ASCIIDigitToInt('2'));
	EXPECT_EQ(3u, ASCIIDigitToInt('3'));
	EXPECT_EQ(4u, ASCIIDigitToInt('4'));
	EXPECT_EQ(5u, ASCIIDigitToInt('5'));
	EXPECT_EQ(6u, ASCIIDigitToInt('6'));
	EXPECT_EQ(7u, ASCIIDigitToInt('7'));
	EXPECT_EQ(8u, ASCIIDigitToInt('8'));
	EXPECT_EQ(9u, ASCIIDigitToInt('9'));

	EXPECT_THROW(ASCIIDigitToInt('a'), parseException);
}
TEST(HTML_Microsyntaxes_Numbers_NumbersMisc, ASCIIHexDigitToInt) {
	EXPECT_EQ(0x0u, ASCIIHexDigitToInt('0'));
	EXPECT_EQ(0x1u, ASCIIHexDigitToInt('1'));
	EXPECT_EQ(0x2u, ASCIIHexDigitToInt('2'));
	EXPECT_EQ(0x3u, ASCIIHexDigitToInt('3'));
	EXPECT_EQ(0x4u, ASCIIHexDigitToInt('4'));
	EXPECT_EQ(0x5u, ASCIIHexDigitToInt('5'));
	EXPECT_EQ(0x6u, ASCIIHexDigitToInt('6'));
	EXPECT_EQ(0x7u, ASCIIHexDigitToInt('7'));
	EXPECT_EQ(0x8u, ASCIIHexDigitToInt('8'));
	EXPECT_EQ(0x9u, ASCIIHexDigitToInt('9'));
	EXPECT_EQ(0xAu, ASCIIHexDigitToInt('a'));
	EXPECT_EQ(0xAu, ASCIIHexDigitToInt('A'));
	EXPECT_EQ(0xBu, ASCIIHexDigitToInt('b'));
	EXPECT_EQ(0xBu, ASCIIHexDigitToInt('B'));
	EXPECT_EQ(0xCu, ASCIIHexDigitToInt('c'));
	EXPECT_EQ(0xCu, ASCIIHexDigitToInt('C'));
	EXPECT_EQ(0xDu, ASCIIHexDigitToInt('d'));
	EXPECT_EQ(0xDu, ASCIIHexDigitToInt('D'));
	EXPECT_EQ(0xEu, ASCIIHexDigitToInt('e'));
	EXPECT_EQ(0xEu, ASCIIHexDigitToInt('E'));
	EXPECT_EQ(0xFu, ASCIIHexDigitToInt('f'));
	EXPECT_EQ(0xFu, ASCIIHexDigitToInt('F'));
	EXPECT_THROW(ASCIIHexDigitToInt('g'), parseException);
}

} /* namespace Numbers */
} /* namespace Microsyntaxes */
} /* namespace HTML */

