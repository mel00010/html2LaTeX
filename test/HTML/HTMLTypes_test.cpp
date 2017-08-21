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


TEST(HTML_HTMLTypes, ContentType) {
	std::ostringstream osContentType;
	std::ostringstream osUTF_8;
	std::ostringstream osUTF_16_BE;
	std::ostringstream osUTF_16_LE;
	std::ostringstream osUNKNOWN;
	std::ostringstream osNULL_ENC;
	std::ostringstream osIRRELEVANT;
	std::ostringstream osTENTATIVE;
	std::ostringstream osCERTAIN;

	osContentType << ContentType(UTF_8, CERTAIN);
	osUTF_8 << UTF_8;
	osUTF_16_BE << UTF_16_BE;
	osUTF_16_LE << UTF_16_LE;
	osUNKNOWN << UNKNOWN;
	osNULL_ENC << NULL_ENC;
	osIRRELEVANT << IRRELEVANT;
	osTENTATIVE << TENTATIVE;
	osCERTAIN << CERTAIN;

	EXPECT_EQ(osContentType.str(), std::string("UTF_8:CERTAIN"));
	EXPECT_EQ(osUTF_8.str(), std::string("UTF_8"));
	EXPECT_EQ(osUTF_16_BE.str(), std::string("UTF_16_BE"));
	EXPECT_EQ(osUTF_16_LE.str(), std::string("UTF_16_LE"));
	EXPECT_EQ(osUNKNOWN.str(), std::string("UNKNOWN"));
	EXPECT_EQ(osNULL_ENC.str(), std::string("NULL_ENC"));
	EXPECT_EQ(osIRRELEVANT.str(), std::string("IRRELEVANT"));
	EXPECT_EQ(osTENTATIVE.str(), std::string("TENTATIVE"));
	EXPECT_EQ(osCERTAIN.str(), std::string("CERTAIN"));



	EXPECT_TRUE(ContentType(UTF_8, CERTAIN) == ContentType(UTF_8, CERTAIN));
	EXPECT_FALSE(ContentType(UTF_8, CERTAIN) == ContentType(UNKNOWN, CERTAIN));
	EXPECT_FALSE(ContentType(UTF_8, CERTAIN) == ContentType(UTF_8, IRRELEVANT));
	EXPECT_FALSE(ContentType(UTF_8, CERTAIN) == ContentType(UNKNOWN, CERTAIN));
	EXPECT_TRUE(ContentType(UTF_8, CERTAIN) != ContentType(UNKNOWN, IRRELEVANT));
	EXPECT_FALSE(ContentType(UTF_8, CERTAIN) != ContentType(UTF_8, CERTAIN));
}


} /* namespace HTML */
