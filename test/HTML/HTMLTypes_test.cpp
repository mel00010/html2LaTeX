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
	EXPECT_EQ("\"name\":\"value\"", static_cast<std::stringstream&>(std::stringstream() << Attribute(U"name", U"value")).str());
	EXPECT_FALSE(Attribute() == true);
	EXPECT_FALSE(Attribute(U"test", U"") == false);
	EXPECT_FALSE(Attribute(U"test", U"test") == false);
	EXPECT_FALSE(true == Attribute());
	EXPECT_TRUE(false == Attribute());
	EXPECT_FALSE(false == Attribute(U"test", U"test"));
	EXPECT_TRUE(true == Attribute(U"test", U"test"));

	EXPECT_TRUE(Attribute(U"test1", U"test2") == Attribute(U"test1", U"test2"));
	EXPECT_FALSE(Attribute(U"test1", U"test2") == Attribute(U"test1", U"test3"));
	EXPECT_FALSE(Attribute(U"test1", U"test2") == Attribute(U"test3", U"test2"));
	EXPECT_FALSE(Attribute(U"test1", U"test2") == Attribute(U"test3", U"test4"));
	EXPECT_TRUE(Attribute(U"test1", U"test2") != Attribute(U"test3", U"test4"));
	EXPECT_FALSE(Attribute(U"test1", U"test2") != Attribute(U"test1", U"test2"));
}

TEST(HTML_HTMLTypes, ASCIIAttribute) {
	EXPECT_EQ("\"name\":\"value\"", static_cast<std::stringstream&>(std::stringstream() << ASCIIAttribute("name", "value")).str());
	EXPECT_FALSE(ASCIIAttribute() == true);
	EXPECT_FALSE(ASCIIAttribute("test", "") == false);
	EXPECT_FALSE(ASCIIAttribute("test", "test") == false);
	EXPECT_FALSE(true == ASCIIAttribute());
	EXPECT_TRUE(false == ASCIIAttribute());
	EXPECT_FALSE(false == ASCIIAttribute("test", "test"));
	EXPECT_TRUE(true == ASCIIAttribute("test", "test"));

	EXPECT_TRUE(ASCIIAttribute("test1", "test2") == ASCIIAttribute("test1", "test2"));
	EXPECT_FALSE(ASCIIAttribute("test1", "test2") == ASCIIAttribute("test1", "test3"));
	EXPECT_FALSE(ASCIIAttribute("test1", "test2") == ASCIIAttribute("test3", "test2"));
	EXPECT_FALSE(ASCIIAttribute("test1", "test2") == ASCIIAttribute("test3", "test4"));
	EXPECT_TRUE(ASCIIAttribute("test1", "test2") != ASCIIAttribute("test3", "test4"));
	EXPECT_FALSE(ASCIIAttribute("test1", "test2") != ASCIIAttribute("test1", "test2"));
}


TEST(HTML_HTMLTypes, ContentType) {
	EXPECT_EQ("CharEncoding::UTF_8:Confidence::CERTAIN", static_cast<std::stringstream&>(std::stringstream() << ContentType(CharEncoding::UTF_8, Confidence::CERTAIN)).str());
	EXPECT_EQ("CharEncoding::UTF_8", static_cast<std::stringstream&>(std::stringstream() << CharEncoding::UTF_8).str());
	EXPECT_EQ("CharEncoding::UTF_16_BE", static_cast<std::stringstream&>(std::stringstream() << CharEncoding::UTF_16_BE).str());
	EXPECT_EQ("CharEncoding::UTF_16_LE", static_cast<std::stringstream&>(std::stringstream() << CharEncoding::UTF_16_LE).str());
	EXPECT_EQ("CharEncoding::UNKNOWN", static_cast<std::stringstream&>(std::stringstream() << CharEncoding::UNKNOWN).str());
	EXPECT_EQ("CharEncoding::NULL_ENC", static_cast<std::stringstream&>(std::stringstream() << CharEncoding::NULL_ENC).str());
	EXPECT_EQ("Confidence::IRRELEVANT", static_cast<std::stringstream&>(std::stringstream() << Confidence::IRRELEVANT).str());
	EXPECT_EQ("Confidence::TENTATIVE", static_cast<std::stringstream&>(std::stringstream() << Confidence::TENTATIVE).str());
	EXPECT_EQ("Confidence::CERTAIN", static_cast<std::stringstream&>(std::stringstream() << Confidence::CERTAIN).str());

	EXPECT_TRUE(ContentType(CharEncoding::UTF_8, Confidence::CERTAIN) == ContentType(CharEncoding::UTF_8, Confidence::CERTAIN));
	EXPECT_FALSE(ContentType(CharEncoding::UTF_8, Confidence::CERTAIN) == ContentType(CharEncoding::UNKNOWN, Confidence::CERTAIN));
	EXPECT_FALSE(ContentType(CharEncoding::UTF_8, Confidence::CERTAIN) == ContentType(CharEncoding::UTF_8, Confidence::IRRELEVANT));
	EXPECT_FALSE(ContentType(CharEncoding::UTF_8, Confidence::CERTAIN) == ContentType(CharEncoding::UNKNOWN, Confidence::CERTAIN));
	EXPECT_TRUE(ContentType(CharEncoding::UTF_8, Confidence::CERTAIN) != ContentType(CharEncoding::UNKNOWN, Confidence::IRRELEVANT));
	EXPECT_FALSE(ContentType(CharEncoding::UTF_8, Confidence::CERTAIN) != ContentType(CharEncoding::UTF_8, Confidence::CERTAIN));
}


} /* namespace HTML */
