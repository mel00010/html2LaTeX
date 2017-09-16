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

TEST(HTML_HTMLTypes, Attribute) {
	EXPECT_EQ("\"name\":\"value\"", static_cast<std::stringstream&>(std::stringstream() << Attribute("name", "value")).str());
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


TEST(HTML_HTMLTypes, ContentType) {
	EXPECT_EQ("UTF_8:CERTAIN", static_cast<std::stringstream&>(std::stringstream() << ContentType(UTF_8, CERTAIN)).str());
	EXPECT_EQ("UTF_8", static_cast<std::stringstream&>(std::stringstream() << UTF_8).str());
	EXPECT_EQ("UTF_16_BE", static_cast<std::stringstream&>(std::stringstream() << UTF_16_BE).str());
	EXPECT_EQ("UTF_16_LE", static_cast<std::stringstream&>(std::stringstream() << UTF_16_LE).str());
	EXPECT_EQ("UNKNOWN", static_cast<std::stringstream&>(std::stringstream() << UNKNOWN).str());
	EXPECT_EQ("NULL_ENC", static_cast<std::stringstream&>(std::stringstream() << NULL_ENC).str());
	EXPECT_EQ("IRRELEVANT", static_cast<std::stringstream&>(std::stringstream() << IRRELEVANT).str());
	EXPECT_EQ("TENTATIVE", static_cast<std::stringstream&>(std::stringstream() << TENTATIVE).str());
	EXPECT_EQ("CERTAIN", static_cast<std::stringstream&>(std::stringstream() << CERTAIN).str());

	EXPECT_TRUE(ContentType(UTF_8, CERTAIN) == ContentType(UTF_8, CERTAIN));
	EXPECT_FALSE(ContentType(UTF_8, CERTAIN) == ContentType(UNKNOWN, CERTAIN));
	EXPECT_FALSE(ContentType(UTF_8, CERTAIN) == ContentType(UTF_8, IRRELEVANT));
	EXPECT_FALSE(ContentType(UTF_8, CERTAIN) == ContentType(UNKNOWN, CERTAIN));
	EXPECT_TRUE(ContentType(UTF_8, CERTAIN) != ContentType(UNKNOWN, IRRELEVANT));
	EXPECT_FALSE(ContentType(UTF_8, CERTAIN) != ContentType(UTF_8, CERTAIN));
}


} /* namespace HTML */
