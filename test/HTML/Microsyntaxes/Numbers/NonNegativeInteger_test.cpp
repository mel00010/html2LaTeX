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
	EXPECT_TRUE(isNonNegativeInteger(std::string("0123456789")));
	EXPECT_FALSE(isNonNegativeInteger(std::string("-0123456789")));
	EXPECT_FALSE(isNonNegativeInteger(std::string("Not An Integer")));
	EXPECT_FALSE(isNonNegativeInteger(std::string("0-123456789")));
	EXPECT_FALSE(isNonNegativeInteger(std::string("0 123456789")));
	EXPECT_FALSE(isNonNegativeInteger(std::string("0a123456789")));
	EXPECT_FALSE(isNonNegativeInteger(std::string("")));
}

TEST(HTML_Microsyntaxes_Numbers_NonNegativeInteger, parseNonNegativeInteger) {
	EXPECT_EQ(123456789u, parseNonNegativeInteger(std::string("   0123456789")));
	EXPECT_EQ(123456789u, parseNonNegativeInteger(std::string("0123456789   ")));
	EXPECT_EQ(123456789u, parseNonNegativeInteger(std::string("0123456789")));

	EXPECT_EQ(123u, parseNonNegativeInteger(std::string("0123 4567 89")));
	EXPECT_EQ(0u, parseNonNegativeInteger(std::string("0-123456789")));

	EXPECT_THROW(parseNonNegativeInteger(std::string("-0123456789")), parseException);
	EXPECT_THROW(parseNonNegativeInteger(std::string("Not an integer")), parseException);
	EXPECT_THROW(parseNonNegativeInteger(std::string("")), parseException);
}

} /* namespace Numbers */
} /* namespace Microsyntaxes */
} /* namespace HTML */

