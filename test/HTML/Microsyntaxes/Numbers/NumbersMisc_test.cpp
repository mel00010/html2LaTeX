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

} /* namespace Numbers */
} /* namespace Microsyntaxes */
} /* namespace HTML */

