/*******************************************************************************
 * HTMLTypes_test.cpp
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
#include <HTML/HTMLTypes.hpp>
#include <sstream>

namespace HTML {

TEST(HTMLTypes, Attribute) {
//	Attribute test;
//	Attribute* testPtr = new Attribute();
//	delete testPtr;
	std::ostringstream out;
	out << Attribute("test", "test");
	EXPECT_FALSE(Attribute() == true);
	EXPECT_FALSE(Attribute("test", "") == false);
	EXPECT_FALSE(Attribute("test", "test") == false);
	EXPECT_FALSE(true == Attribute());
	EXPECT_TRUE(false == Attribute());
	EXPECT_FALSE(false == Attribute("test", "test"));
	EXPECT_TRUE(true == Attribute("test", "test"));

	EXPECT_TRUE(Attribute("test1", "test2") == Attribute("test1", "test2"));
	EXPECT_FALSE(Attribute("test1", "test2") == Attribute("test1", "test3"));
	EXPECT_FALSE(Attribute("test1", "test2") == Attribute("test3", "test2"));
	EXPECT_FALSE(Attribute("test1", "test2") == Attribute("test3", "test4"));
	EXPECT_TRUE(Attribute("test1", "test2") != Attribute("test3", "test4"));
	EXPECT_FALSE(Attribute("test1", "test2") != Attribute("test1", "test2"));
}


TEST(HTMLTypes, ContentType) {
	std::ostringstream out;
	out << ContentType(UTF_8, CERTAIN);
	out << UTF_8 << UTF_16_BE << UTF_16_LE << UNKNOWN << NULL_ENC;
	out << IRRELEVANT << TENTATIVE << CERTAIN;

	EXPECT_TRUE(ContentType(UTF_8, CERTAIN) == ContentType(UTF_8, CERTAIN));
	EXPECT_FALSE(ContentType(UTF_8, CERTAIN) == ContentType(UNKNOWN, CERTAIN));
	EXPECT_FALSE(ContentType(UTF_8, CERTAIN) == ContentType(UTF_8, IRRELEVANT));
	EXPECT_FALSE(ContentType(UTF_8, CERTAIN) == ContentType(UNKNOWN, CERTAIN));
	EXPECT_TRUE(ContentType(UTF_8, CERTAIN) != ContentType(UNKNOWN, IRRELEVANT));
	EXPECT_FALSE(ContentType(UTF_8, CERTAIN) != ContentType(UTF_8, CERTAIN));
}


} /* namespace HTML */
