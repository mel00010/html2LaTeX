/*******************************************************************************
 * ListsOfDimensions_test.cpp
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

#include <HTML/Microsyntaxes/Numbers/ListsOfDimensions.hpp>
#include <HTML/Microsyntaxes/Numbers/NumbersTypes.hpp>

#include <list>


namespace HTML {
namespace Microsyntaxes {
namespace Numbers {

TEST(HTML_Microsyntaxes_Numbers_ListsOfDimensions, isListOfDimensions) {
	EXPECT_TRUE(isListOfDimensions("1,1%,1*"));
	EXPECT_TRUE(isListOfDimensions("1,1%,1*,"));
	EXPECT_TRUE(isListOfDimensions("1"));
	EXPECT_TRUE(isListOfDimensions("1,2,3,4,5,6,7,8,9,0"));
	EXPECT_TRUE(isListOfDimensions("1.0,2.1,3.2,4.3,5.4,6.5,7.6,8.7,9.8,0.1"));
	EXPECT_FALSE(isListOfDimensions("a"));
	EXPECT_FALSE(isListOfDimensions(""));
	EXPECT_FALSE(isListOfDimensions(","));
	EXPECT_FALSE(isListOfDimensions(";"));
	EXPECT_FALSE(isListOfDimensions("."));
	EXPECT_FALSE(isListOfDimensions(" "));
	EXPECT_FALSE(isListOfDimensions("%"));
	EXPECT_FALSE(isListOfDimensions("*"));
	EXPECT_FALSE(isListOfDimensions("1,2,a,3"));
	EXPECT_FALSE(isListOfDimensions("1%,2%,a,3"));
	EXPECT_FALSE(isListOfDimensions("a%"));
	EXPECT_FALSE(isListOfDimensions("%a,a"));
	EXPECT_FALSE(isListOfDimensions("1,%,2,3"));
	EXPECT_FALSE(isListOfDimensions("1,*,2,3"));
	EXPECT_FALSE(isListOfDimensions("1,%2,3"));
	EXPECT_FALSE(isListOfDimensions("1,*2,3"));
	EXPECT_FALSE(isListOfDimensions("1,.,2,3"));
	EXPECT_FALSE(isListOfDimensions("1.2.3"));
	EXPECT_FALSE(isListOfDimensions("1*2*3"));
}

TEST(HTML_Microsyntaxes_Numbers_ListsOfDimensions, parseListOfDimensions) {
	EXPECT_EQ(parseListOfDimensions(""), (std::list<Dimension> { }));
	EXPECT_EQ(parseListOfDimensions(","), (std::list<Dimension> { }));
	EXPECT_EQ(parseListOfDimensions("1,1%,1*"),
			(std::list<Dimension> {
					Dimension(1, DimensionType::ABSOLUTE),
					Dimension(1, DimensionType::PERCENTAGE),
					Dimension(1, DimensionType::RELATIVE)
			}));
	EXPECT_EQ(parseListOfDimensions("1,1%,1*,"),
			(std::list<Dimension> {
					Dimension(1, DimensionType::ABSOLUTE),
					Dimension(1, DimensionType::PERCENTAGE),
					Dimension(1, DimensionType::RELATIVE)
			}));

	EXPECT_EQ(parseListOfDimensions("1"),
			(std::list<Dimension> {
					Dimension(1, DimensionType::ABSOLUTE)
			}));
	EXPECT_EQ(parseListOfDimensions("1,2,3,4,5,6,7,8,9,0"),
			(std::list<Dimension> {
					Dimension(1, DimensionType::ABSOLUTE),
					Dimension(2, DimensionType::ABSOLUTE),
					Dimension(3, DimensionType::ABSOLUTE),
					Dimension(4, DimensionType::ABSOLUTE),
					Dimension(5, DimensionType::ABSOLUTE),
					Dimension(6, DimensionType::ABSOLUTE),
					Dimension(7, DimensionType::ABSOLUTE),
					Dimension(8, DimensionType::ABSOLUTE),
					Dimension(9, DimensionType::ABSOLUTE),
					Dimension(0, DimensionType::ABSOLUTE)
			}));
	EXPECT_EQ(parseListOfDimensions("1.0,2.1,3.2,4.3,5.4,6.5,7.6,8.7,9.8,0.9"),
			(std::list<Dimension> {
					Dimension(1.0, DimensionType::ABSOLUTE),
					Dimension(2.1, DimensionType::ABSOLUTE),
					Dimension(3.2, DimensionType::ABSOLUTE),
					Dimension(4.3, DimensionType::ABSOLUTE),
					Dimension(5.4, DimensionType::ABSOLUTE),
					Dimension(6.5, DimensionType::ABSOLUTE),
					Dimension(7.6, DimensionType::ABSOLUTE),
					Dimension(8.7, DimensionType::ABSOLUTE),
					Dimension(9.8, DimensionType::ABSOLUTE),
					Dimension(0.9, DimensionType::ABSOLUTE)
			}));
	EXPECT_EQ(parseListOfDimensions("1,2,a,3"),
			(std::list<Dimension> {
					Dimension(1, DimensionType::ABSOLUTE),
					Dimension(2, DimensionType::ABSOLUTE),
					Dimension(0, DimensionType::ABSOLUTE),
					Dimension(3, DimensionType::ABSOLUTE)
			}));
	EXPECT_EQ(
			parseListOfDimensions("1%,2%,a,3"),
			(std::list<Dimension> {
					Dimension(1, DimensionType::PERCENTAGE),
					Dimension(2, DimensionType::PERCENTAGE),
					Dimension(0, DimensionType::ABSOLUTE),
					Dimension(3, DimensionType::ABSOLUTE)
			}));

	EXPECT_EQ(parseListOfDimensions("1,%,2,3"),
			(std::list<Dimension> {
					Dimension(1, DimensionType::ABSOLUTE),
					Dimension(0, DimensionType::PERCENTAGE),
					Dimension(2, DimensionType::ABSOLUTE),
					Dimension(3, DimensionType::ABSOLUTE)
			}));
	EXPECT_EQ(parseListOfDimensions("1,*,2,3"),
			(std::list<Dimension> {
					Dimension(1, DimensionType::ABSOLUTE),
					Dimension(0, DimensionType::RELATIVE),
					Dimension(2, DimensionType::ABSOLUTE),
					Dimension(3, DimensionType::ABSOLUTE)
			}));
	EXPECT_EQ(parseListOfDimensions("1,%2,3"),
			(std::list<Dimension> {
					Dimension(1, DimensionType::ABSOLUTE),
					Dimension(0, DimensionType::PERCENTAGE),
					Dimension(3, DimensionType::ABSOLUTE)
			}));
	EXPECT_EQ(parseListOfDimensions("1,*2,3"),
			(std::list<Dimension> {
					Dimension(1, DimensionType::ABSOLUTE),
					Dimension(0, DimensionType::RELATIVE),
					Dimension(3, DimensionType::ABSOLUTE)
			}));
	EXPECT_EQ(parseListOfDimensions("1,.,2,3"),
			(std::list<Dimension> {
					Dimension(1, DimensionType::ABSOLUTE),
					Dimension(0, DimensionType::ABSOLUTE),
					Dimension(2, DimensionType::ABSOLUTE),
					Dimension(3, DimensionType::ABSOLUTE)
			}));
	EXPECT_EQ(parseListOfDimensions("1.2.3"),
			(std::list<Dimension> {
					Dimension(1.2, DimensionType::ABSOLUTE)
			}));
	EXPECT_EQ(parseListOfDimensions("1*2*3"),
			(std::list<Dimension> {
					Dimension(1, DimensionType::RELATIVE)
			}));
	EXPECT_EQ(parseListOfDimensions("a"),
			(std::list<Dimension> {
					Dimension(0, DimensionType::ABSOLUTE)
			}));

	EXPECT_EQ(parseListOfDimensions(";"),
			(std::list<Dimension> {
					Dimension(0, DimensionType::ABSOLUTE)
			}));
	EXPECT_EQ(parseListOfDimensions("."),
			(std::list<Dimension> {
					Dimension(0, DimensionType::ABSOLUTE)
			}));
	EXPECT_EQ(parseListOfDimensions(" "),
			(std::list<Dimension> {
					Dimension(0, DimensionType::ABSOLUTE)
			}));
	EXPECT_EQ(parseListOfDimensions("%"),
			(std::list<Dimension> {
					Dimension(0, DimensionType::PERCENTAGE)
			}));
	EXPECT_EQ(parseListOfDimensions("*"),
			(std::list<Dimension> {
					Dimension(0, DimensionType::RELATIVE)
			}));
	EXPECT_EQ(parseListOfDimensions("a%"),
			(std::list<Dimension> {
					Dimension(0, DimensionType::ABSOLUTE)
			}));
	EXPECT_EQ(parseListOfDimensions("%a,a"),
			(std::list<Dimension> {
					Dimension(0, DimensionType::PERCENTAGE),
					Dimension(0, DimensionType::ABSOLUTE),
			}));
}

} /* namespace Numbers */
} /* namespace Microsyntaxes */
} /* namespace HTML */


