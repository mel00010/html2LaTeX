/*******************************************************************************
 * ASCII_test.cpp
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
#include <HTML/Microsyntaxes/ASCII.hpp>
#include <HTML/HTMLTypes.hpp>

namespace HTML {
namespace Microsyntaxes {
/**
 * @brief Holds all of the unit tests for the namespace HTML::Microsyntaxes
 */
namespace Microsyntaxes_Test {
/**
 * @brief Test fixture for HTML::Parse::MagicString::isASCIIUpperCaseLetter()
 */
class HTML_Microsyntaxes_isASCIIUpper_Test: public ::testing::Test {
	protected:
		const HTML::Byte trueCase = 0x53;
		const HTML::Byte falseCase = 0x70;
};

TEST_F(HTML_Microsyntaxes_isASCIIUpper_Test, trueCase) {
	EXPECT_TRUE(HTML::Microsyntaxes::isASCIIUpper(trueCase));
}
TEST_F(HTML_Microsyntaxes_isASCIIUpper_Test, falseCase) {
	EXPECT_FALSE(HTML::Microsyntaxes::isASCIIUpper(falseCase));
}

} /* namespace Microsyntaxes_Test */
} /* namespace Microsyntaxes */
} /* namespace HTML */

