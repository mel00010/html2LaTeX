/*******************************************************************************
 * ListsOfIntegers_test.cpp
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

#include <HTML/Microsyntaxes/Numbers/ListsOfIntegers.hpp>

#include <HTML/Microsyntaxes/Numbers/NumbersTypes.hpp>

#include <list>

namespace HTML {
namespace Microsyntaxes {
namespace Numbers {

TEST(HTML_Microsyntaxes_Numbers_ListsOfIntegers, isListOfIntegers) {
	EXPECT_TRUE(isListOfIntegers("1,2,3,4,5,6,7,8,9,0"));
	EXPECT_TRUE(isListOfIntegers("-1,-2,-3,-4,-5,-6,-7,-8,-9,0"));
	EXPECT_TRUE(isListOfIntegers("-5,-4,-3,-2,-1,0,1,2,3,4,5"));
	EXPECT_TRUE(isListOfIntegers("1"));
	EXPECT_TRUE(isListOfIntegers("1,2"));
	EXPECT_TRUE(isListOfIntegers("5,4,3,2,1"));
	EXPECT_FALSE(isListOfIntegers("a"));
	EXPECT_FALSE(isListOfIntegers("1,2, ,3,4,5"));
	EXPECT_FALSE(isListOfIntegers("1,2,3 ,4,5"));
	EXPECT_FALSE(isListOfIntegers("1,2, 3,4,5"));
	EXPECT_FALSE(isListOfIntegers("1 2 3 4 5"));
	EXPECT_FALSE(isListOfIntegers(","));
	EXPECT_FALSE(isListOfIntegers(" "));
	EXPECT_FALSE(isListOfIntegers(";"));
	EXPECT_FALSE(isListOfIntegers("-"));
	EXPECT_FALSE(isListOfIntegers("a,b,c,d"));
	EXPECT_FALSE(isListOfIntegers("1,2,a,b,c,3"));
	EXPECT_FALSE(isListOfIntegers("1,2,3,-,4,5"));
	EXPECT_FALSE(isListOfIntegers("1,2,3,4-,5"));
}


TEST(HTML_Microsyntaxes_Numbers_ListsOfIntegers, parseListOfIntegers) {
	EXPECT_EQ((std::list<int> { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 }), parseListOfIntegers("1,2,3,4,5,6,7,8,9,0"));
	EXPECT_EQ((std::list<int> { -1, -2, -3, -4, -5, -6, -7, -8, -9, 0 }), parseListOfIntegers("-1,-2,-3,-4,-5,-6,-7,-8,-9,0"));
	EXPECT_EQ((std::list<int> { -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5 }), parseListOfIntegers("-5,-4,-3,-2,-1,0,1,2,3,4,5"));
	EXPECT_EQ((std::list<int> { 1 }), parseListOfIntegers("1"));
	EXPECT_EQ((std::list<int> { 1, 2 }), parseListOfIntegers("1,2"));
	EXPECT_EQ((std::list<int> { 5, 4, 3, 2, 1 }), parseListOfIntegers("5,4,3,2,1"));
	EXPECT_EQ((std::list<int> { }), parseListOfIntegers(","));
	EXPECT_EQ((std::list<int> { }), parseListOfIntegers(" "));
	EXPECT_EQ((std::list<int> { }), parseListOfIntegers(";"));
	EXPECT_EQ((std::list<int> { }), parseListOfIntegers("a"));
	EXPECT_EQ((std::list<int> { 1, 2, 3, 4, 5 }), parseListOfIntegers("1,2, ,3,4,5"));
	EXPECT_EQ((std::list<int> { 1, 2, 3, 4, 5 }), parseListOfIntegers("1,2,3 ,4,5"));
	EXPECT_EQ((std::list<int> { 1, 2, 3, 4, 5 }), parseListOfIntegers("1,2, 3,4,5"));
	EXPECT_EQ((std::list<int> { 1, 2, 3, 4, 5 }), parseListOfIntegers("1 2 3 4 5"));
	EXPECT_EQ((std::list<int> { }), parseListOfIntegers("-"));
	EXPECT_EQ((std::list<int> { }), parseListOfIntegers("a,b,c,d"));
	EXPECT_EQ((std::list<int> { 1, 2 }), parseListOfIntegers("1,2,a,b,c,3"));
	EXPECT_EQ((std::list<int> { 1, 2, 3 }), parseListOfIntegers("1,2,3,-,4,5"));
	EXPECT_EQ((std::list<int> { 1, 2, 3, 4, 5 }), parseListOfIntegers("1,2,3,4-,5"));
}

} /* namespace Numbers */
} /* namespace Microsyntaxes */
} /* namespace HTML */


