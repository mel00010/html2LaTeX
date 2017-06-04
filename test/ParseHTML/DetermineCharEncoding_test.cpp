/*******************************************************************************
 * DetermineCharEncoding_test.cpp
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

#include <ParseHTML/MagicString.hpp>
#include <ParseHTML/DetermineCharEncoding.hpp>

#include <gtest/gtest.h>
#include <exception>
#include <iostream>

/**
 * @file test/ParseHTML/DetermineCharEncoding_test.cpp
 * @brief Holds all of the unit tests for ParseHTML/DetermineCharEncoding.hpp and ParseHTML/DetermineCharEncoding.cpp
 */
/**
 * @dir test/ParseHTML
 * @brief Holds all of the source files and headers for the tests for the directory ParseHTML
 */
namespace ParseHTML {

/**
 * @brief Test fixture for ParseHTML::DetermineCharEncoding
 */
class ParseHTML_DetermineCharEncoding_Test: public ::testing::Test {
	protected:
		DetermineCharEncoding determineCharEncoding;
};
/**
 * @{
 * @name DetermineCharEncoding_Tests
 */

TEST_F(ParseHTML_DetermineCharEncoding_Test, determineCharEncoding_BOM) {
	Byte BOM[2] = { 0xFE, 0xFF };
	std::string testString = (char*) BOM;
	testString += "unrelated <tags> and other text";
	std::istringstream testStream(testString);
	ContentType expected;
	expected.charEncoding = UTF_16_BE;
	expected.confidence = CERTAIN;
	EXPECT_EQ(expected, determineCharEncoding.determineCharEncoding(testStream));
}
TEST_F(ParseHTML_DetermineCharEncoding_Test, determineCharEncoding_preScan) {
	std::string testString = "<html>\n<head>\n\t<meta charset=utf-8> more unrelated text and <tags>";
	std::istringstream testStream(testString);
	ContentType expected;
	expected.charEncoding = UTF_8;
	expected.confidence = TENTATIVE;
	EXPECT_EQ(expected, determineCharEncoding.determineCharEncoding(testStream));
}

TEST_F(ParseHTML_DetermineCharEncoding_Test, preScan_commentTagAlgorithm) {
	std::string testString = "<html>\n<head>\n\t<!-- charset=utf-8> more unrelated text and <tags> --> <meta charset=utf-8>";
	std::istringstream testStream(testString);
	ContentType expected;
	expected.charEncoding = UTF_8;
	expected.confidence = TENTATIVE;
	EXPECT_EQ(expected, determineCharEncoding.determineCharEncoding(testStream));
}
TEST_F(ParseHTML_DetermineCharEncoding_Test, preScan_metaTagAlgorithm) {
	std::string testString = "<html>\n<head>\n\t<meta charset=utf-8> more unrelated text and <tags>";
	std::istringstream testStream(testString);
	ContentType expected;
	expected.charEncoding = UTF_8;
	expected.confidence = TENTATIVE;
	EXPECT_EQ(expected, determineCharEncoding.determineCharEncoding(testStream));
}
TEST_F(ParseHTML_DetermineCharEncoding_Test, preScan_asciiTagAlgorithm) {
	std::string testString = "<html>\n<head>\n\t<unrelatedTag charset=utf-8> more unrelated text and <tags><unrelatedTag> <meta charset=utf-8>";
	std::istringstream testStream(testString);
	ContentType expected;
	expected.charEncoding = UTF_8;
	expected.confidence = TENTATIVE;
	EXPECT_EQ(expected, determineCharEncoding.determineCharEncoding(testStream));
}
TEST_F(ParseHTML_DetermineCharEncoding_Test, preScan_punctuationTagAlgorithm) {
	std::string testString = "<html>\n<head>\n\t<? charset=utf-8> more unrelated text and <tags> > <meta charset=utf-8>";
	std::istringstream testStream(testString);
	ContentType expected;
	expected.charEncoding = UTF_8;
	expected.confidence = TENTATIVE;
	EXPECT_EQ(expected, determineCharEncoding.determineCharEncoding(testStream));
}

TEST_F(ParseHTML_DetermineCharEncoding_Test, tryUnicodeBOM_UTF_16_BE) {
	Byte BOM[2] = { 0xFE, 0xFF };
	std::string testString = (char*) BOM;
	std::istringstream testStream(testString);
	ContentType expected;
	expected.charEncoding = UTF_16_BE;
	expected.confidence = CERTAIN;
	EXPECT_EQ(expected, determineCharEncoding.tryUnicodeBOM(testStream));
}
TEST_F(ParseHTML_DetermineCharEncoding_Test, tryUnicodeBOM_UTF_16_LE) {
	Byte BOM[2] = { 0xFF, 0xFE };
	std::string testString = (char*) BOM;
	std::istringstream testStream(testString);
	ContentType expected;
	expected.charEncoding = UTF_16_LE;
	expected.confidence = CERTAIN;
	EXPECT_EQ(expected, determineCharEncoding.tryUnicodeBOM(testStream));
}
TEST_F(ParseHTML_DetermineCharEncoding_Test, tryUnicodeBOM_UTF_8) {
	Byte BOM[3] = { 0xEF, 0xBB, 0xBF };
	std::string testString = (char*) BOM;
	std::istringstream testStream(testString);
	ContentType expected;
	expected.charEncoding = UTF_8;
	expected.confidence = CERTAIN;
	EXPECT_EQ(expected, determineCharEncoding.tryUnicodeBOM(testStream));
}
TEST_F(ParseHTML_DetermineCharEncoding_Test, tryUnicodeBOM_invalidBOM) {
	Byte BOM[3] = { 0x5A, 0xDE, 0xCC };
	std::string testString = (char*) BOM;
	std::istringstream testStream(testString);
	ContentType expected;
	expected.charEncoding = UNKNOWN;
	expected.confidence = IRRELEVANT;
	EXPECT_EQ(expected, determineCharEncoding.tryUnicodeBOM(testStream));
}
TEST_F(ParseHTML_DetermineCharEncoding_Test, tryUnicodeBOM_none) {
	std::string testString = "";
	std::istringstream testStream(testString);
	ContentType expected;
	expected.charEncoding = UNKNOWN;
	expected.confidence = IRRELEVANT;
	EXPECT_EQ(expected, determineCharEncoding.tryUnicodeBOM(testStream));
}

TEST_F(ParseHTML_DetermineCharEncoding_Test, commentTagAlgorithm_normal) {
	std::string testString = "<!-- commentText -->";
	std::istringstream testStream(testString);
	ContentType expected;
	expected.charEncoding = UNKNOWN;
	expected.confidence = IRRELEVANT;
	EXPECT_EQ(expected, determineCharEncoding.commentTagAlgorithm(testStream));
}
TEST_F(ParseHTML_DetermineCharEncoding_Test, commentTagAlgorithm_sharingDashes) {
	std::string testString = "<!-->";
	std::istringstream testStream(testString);
	ContentType expected;
	expected.charEncoding = UNKNOWN;
	expected.confidence = IRRELEVANT;
	EXPECT_EQ(expected, determineCharEncoding.commentTagAlgorithm(testStream));
}
TEST_F(ParseHTML_DetermineCharEncoding_Test, commentTagAlgorithm_notCommentTag) {
	std::string testString = "<notCommentTag>";
	std::istringstream testStream(testString);
	ContentType expected;
	expected.charEncoding = UNKNOWN;
	expected.confidence = IRRELEVANT;
	EXPECT_EQ(expected, determineCharEncoding.commentTagAlgorithm(testStream));
}
TEST_F(ParseHTML_DetermineCharEncoding_Test, commentTagAlgorithm_unclosed) {
	std::string testString = "<!-- ";
	std::istringstream testStream(testString);
	EXPECT_THROW(determineCharEncoding.commentTagAlgorithm(testStream), std::istream::failure);
}

TEST_F(ParseHTML_DetermineCharEncoding_Test, metaTagAlgorithm_normal) {
	std::string testString = "<meta charset=utf-8>";
	std::istringstream testStream(testString);
	ContentType expected;
	expected.charEncoding = UTF_8;
	expected.confidence = TENTATIVE;
	EXPECT_EQ(expected, determineCharEncoding.metaTagAlgorithm(testStream));
}
TEST_F(ParseHTML_DetermineCharEncoding_Test, metaTagAlgorithm_notMetaTag) {
	std::string testString = "<notMetaTag>";
	std::istringstream testStream(testString);
	ContentType expected;
	expected.charEncoding = UNKNOWN;
	expected.confidence = IRRELEVANT;
	EXPECT_EQ(expected, determineCharEncoding.metaTagAlgorithm(testStream));
}
TEST_F(ParseHTML_DetermineCharEncoding_Test, metaTagAlgorithm_content_Present_http_equiv_Present) {
	std::string testString = "<meta content=\"charset=utf-8\" http-equiv=\"content-type\">";
	std::istringstream testStream(testString);
	ContentType expected;
	expected.charEncoding = UTF_8;
	expected.confidence = TENTATIVE;
	EXPECT_EQ(expected, determineCharEncoding.metaTagAlgorithm(testStream));
}
TEST_F(ParseHTML_DetermineCharEncoding_Test, metaTagAlgorithm_content_Present_http_equiv_NotPresent) {
	std::string testString = "<meta content=\"charset=utf-8\" >";
	std::istringstream testStream(testString);
	ContentType expected;
	expected.charEncoding = UNKNOWN;
	expected.confidence = IRRELEVANT;
	EXPECT_EQ(expected, determineCharEncoding.metaTagAlgorithm(testStream));
}
TEST_F(ParseHTML_DetermineCharEncoding_Test, metaTagAlgorithm_content_Present_http_equiv_HasNoValue) {
	std::string testString = "<meta content=\"charset=utf-8\" http-equiv>";
	std::istringstream testStream(testString);
	ContentType expected;
	expected.charEncoding = UNKNOWN;
	expected.confidence = IRRELEVANT;
	EXPECT_EQ(expected, determineCharEncoding.metaTagAlgorithm(testStream));
}
TEST_F(ParseHTML_DetermineCharEncoding_Test, metaTagAlgorithm_content_Present_http_equiv_HasWrongValue) {
	std::string testString = "<meta content=\"charset=utf-8\" http-equiv=\"wrong\">";
	std::istringstream testStream(testString);
	ContentType expected;
	expected.charEncoding = UNKNOWN;
	expected.confidence = IRRELEVANT;
	EXPECT_EQ(expected, determineCharEncoding.metaTagAlgorithm(testStream));
}
TEST_F(ParseHTML_DetermineCharEncoding_Test, metaTagAlgorithm_content_Present_charset_Present) {
	std::string testString = "<meta content=\"charset=utf-8\" charset=\"utf-8\">";
	std::istringstream testStream(testString);
	ContentType expected;
	expected.charEncoding = UTF_8;
	expected.confidence = TENTATIVE;
	EXPECT_EQ(expected, determineCharEncoding.metaTagAlgorithm(testStream));
}
TEST_F(ParseHTML_DetermineCharEncoding_Test, metaTagAlgorithm_charset) {
	std::string testString = "<meta charset=utf-8>";
	std::istringstream testStream(testString);
	ContentType expected;
	expected.charEncoding = UTF_8;
	expected.confidence = TENTATIVE;
	EXPECT_EQ(expected, determineCharEncoding.metaTagAlgorithm(testStream));
}
TEST_F(ParseHTML_DetermineCharEncoding_Test, metaTagAlgorithm_noAttributes) {
	std::string testString = "<meta>";
	std::istringstream testStream(testString);
	ContentType expected;
	expected.charEncoding = UNKNOWN;
	expected.confidence = IRRELEVANT;
	EXPECT_EQ(expected, determineCharEncoding.metaTagAlgorithm(testStream));
}
TEST_F(ParseHTML_DetermineCharEncoding_Test, metaTagAlgorithm_noUsefulAttributes) {
	std::string testString = "<meta attributeName1=attributeValue1 attributeName2=attributeValue2>";
	std::istringstream testStream(testString);
	ContentType expected;
	expected.charEncoding = UNKNOWN;
	expected.confidence = IRRELEVANT;
	EXPECT_EQ(expected, determineCharEncoding.metaTagAlgorithm(testStream));
}
TEST_F(ParseHTML_DetermineCharEncoding_Test, metaTagAlgorithm_unclosed) {
	std::string testString = "<meta";
	std::istringstream testStream(testString);
	EXPECT_THROW(determineCharEncoding.metaTagAlgorithm(testStream), std::istream::failure);
}

TEST_F(ParseHTML_DetermineCharEncoding_Test, asciiTagAlgorithm_normal) {
	std::string testString = "<AsciiTag>";
	std::istringstream testStream(testString);
	ContentType expected;
	expected.charEncoding = UNKNOWN;
	expected.confidence = IRRELEVANT;
	EXPECT_EQ(expected, determineCharEncoding.asciiTagAlgorithm(testStream));
}
TEST_F(ParseHTML_DetermineCharEncoding_Test, asciiTagAlgorithm_notAsciiTag) {
	std::string testString = "<!-->";
	std::istringstream testStream(testString);
	ContentType expected;
	expected.charEncoding = UNKNOWN;
	expected.confidence = IRRELEVANT;
	EXPECT_EQ(expected, determineCharEncoding.asciiTagAlgorithm(testStream));
}
TEST_F(ParseHTML_DetermineCharEncoding_Test, asciiTagAlgorithm_startTag) {
	std::string testString = "<AsciiTag>";
	std::istringstream testStream(testString);
	ContentType expected;
	expected.charEncoding = UNKNOWN;
	expected.confidence = IRRELEVANT;
	EXPECT_EQ(expected, determineCharEncoding.asciiTagAlgorithm(testStream));
}
TEST_F(ParseHTML_DetermineCharEncoding_Test, asciiTagAlgorithm_endTag) {
	std::string testString = "</AsciiTag>";
	std::istringstream testStream(testString);
	ContentType expected;
	expected.charEncoding = UNKNOWN;
	expected.confidence = IRRELEVANT;
	EXPECT_EQ(expected, determineCharEncoding.asciiTagAlgorithm(testStream));
}
TEST_F(ParseHTML_DetermineCharEncoding_Test, asciiTagAlgorithm_startTagWithAttributes) {
	std::string testString = "<AsciiTag attribute1=value1>";
	std::istringstream testStream(testString);
	ContentType expected;
	expected.charEncoding = UNKNOWN;
	expected.confidence = IRRELEVANT;
	EXPECT_EQ(expected, determineCharEncoding.asciiTagAlgorithm(testStream));
}
TEST_F(ParseHTML_DetermineCharEncoding_Test, asciiTagAlgorithm_unclosed) {
	std::string testString = "<AsciiTag";
	std::istringstream testStream(testString);
	EXPECT_THROW(determineCharEncoding.asciiTagAlgorithm(testStream), std::istream::failure);
}

TEST_F(ParseHTML_DetermineCharEncoding_Test, punctuationTagAlgorithm_normal) {
	std::string testString = "<!punctuationTag>";
	std::istringstream testStream(testString);
	ContentType expected;
	expected.charEncoding = UNKNOWN;
	expected.confidence = IRRELEVANT;
	EXPECT_EQ(expected, determineCharEncoding.punctuationTagAlgorithm(testStream));
}
TEST_F(ParseHTML_DetermineCharEncoding_Test, punctuationTagAlgorithm_notPunctuationTag) {
	std::string testString = "<notPunctuationTag>";
	std::istringstream testStream(testString);
	ContentType expected;
	expected.charEncoding = UNKNOWN;
	expected.confidence = IRRELEVANT;
	EXPECT_EQ(expected, determineCharEncoding.punctuationTagAlgorithm(testStream));
}
TEST_F(ParseHTML_DetermineCharEncoding_Test, punctuationTagAlgorithm_unclosed) {
	std::string testString = "<!";
	std::istringstream testStream(testString);
	EXPECT_THROW(determineCharEncoding.punctuationTagAlgorithm(testStream), std::istream::failure);
}

TEST_F(ParseHTML_DetermineCharEncoding_Test, getAttribute_nameAndValue) {
	std::string testString = "testName=testValue";
	std::istringstream testStream(testString);
	testStream.exceptions(std::istream::eofbit);
	Attribute expected;
	expected.name = "testname";
	expected.value = "testvalue";
	EXPECT_EQ(expected, determineCharEncoding.getAttribute(testStream));

}
TEST_F(ParseHTML_DetermineCharEncoding_Test, getAttribute_nameOnly) {
	std::string testString = "testName";
	std::istringstream testStream(testString);
	testStream.exceptions(std::istream::eofbit);
	Attribute expected;
	expected.name = "testname";
	expected.value = "";
	EXPECT_EQ(expected, determineCharEncoding.getAttribute(testStream));
}
TEST_F(ParseHTML_DetermineCharEncoding_Test, getAttribute_unclosed) {
	std::string testString = "testName = >";
	std::istringstream testStream(testString);
	testStream.exceptions(std::istream::eofbit);
	Attribute expected;
	expected.name = "testname";
	expected.value = "";
	EXPECT_EQ(expected, determineCharEncoding.getAttribute(testStream));
}
TEST_F(ParseHTML_DetermineCharEncoding_Test, getAttribute_noAttribute) {
	std::string testString = "";
	std::istringstream testStream(testString);
	testStream.exceptions(std::istream::eofbit);
	Attribute expected;
	expected.name = "";
	expected.value = "";
	EXPECT_EQ(expected, determineCharEncoding.getAttribute(testStream));
}
TEST_F(ParseHTML_DetermineCharEncoding_Test, getAttribute_valueInDoubleQuotes) {
	std::string testString = "testName = \"testValue\"";
	std::istringstream testStream(testString);
	testStream.exceptions(std::istream::eofbit);
	Attribute expected;
	expected.name = "testname";
	expected.value = "testvalue";
	EXPECT_EQ(expected, determineCharEncoding.getAttribute(testStream));
}
TEST_F(ParseHTML_DetermineCharEncoding_Test, getAttribute_valueInSingleQuotes) {
	std::string testString = "testName = 'testValue'";
	std::istringstream testStream(testString);
	testStream.exceptions(std::istream::eofbit);
	Attribute expected;
	expected.name = "testname";
	expected.value = "testvalue";
	EXPECT_EQ(expected, determineCharEncoding.getAttribute(testStream));
}
TEST_F(ParseHTML_DetermineCharEncoding_Test, getAttribute_valueInUnmatchedDoubleQuotes) {
	std::string testString = "testName = \"testValue";
	std::istringstream testStream(testString);
	testStream.exceptions(std::istream::eofbit);
	Attribute expected;
	expected.name = "testname";
	expected.value = "testvalue";
	EXPECT_EQ(expected, determineCharEncoding.getAttribute(testStream));
}
TEST_F(ParseHTML_DetermineCharEncoding_Test, getAttribute_valueInUnmatchedSingleQuotes) {
	std::string testString = "testName = 'testValue";
	std::istringstream testStream(testString);
	testStream.exceptions(std::istream::eofbit);
	Attribute expected;
	expected.name = "testname";
	expected.value = "testvalue";
	EXPECT_EQ(expected, determineCharEncoding.getAttribute(testStream));
}

TEST_F(ParseHTML_DetermineCharEncoding_Test, extractCharEncodingFromMetaTag_normal) {
	std::string testString = "charSet = utf-8";
	EXPECT_EQ(UTF_8, determineCharEncoding.extractCharEncodingFromMetaTag(testString));
}
TEST_F(ParseHTML_DetermineCharEncoding_Test, extractCharEncodingFromMetaTag_partialCharset) {
	std::string testString = "char=utf-8";
	EXPECT_EQ(NULL_ENC, determineCharEncoding.extractCharEncodingFromMetaTag(testString));
}
TEST_F(ParseHTML_DetermineCharEncoding_Test, extractCharEncodingFromMetaTag_noCharset) {
	std::string testString = "utf-8";
	EXPECT_EQ(NULL_ENC, determineCharEncoding.extractCharEncodingFromMetaTag(testString));
}
TEST_F(ParseHTML_DetermineCharEncoding_Test, extractCharEncodingFromMetaTag_noEncoding) {
	std::string testString = "charset=";
	EXPECT_EQ(NULL_ENC, determineCharEncoding.extractCharEncodingFromMetaTag(testString));
}
TEST_F(ParseHTML_DetermineCharEncoding_Test, extractCharEncodingFromMetaTag_noEquals) {
	std::string testString = "charset utf-8";
	EXPECT_EQ(NULL_ENC, determineCharEncoding.extractCharEncodingFromMetaTag(testString));
}
TEST_F(ParseHTML_DetermineCharEncoding_Test, extractCharEncodingFromMetaTag_unknownEncoding) {
	std::string testString = "charset=unknown";
	EXPECT_EQ(NULL_ENC, determineCharEncoding.extractCharEncodingFromMetaTag(testString));
}
TEST_F(ParseHTML_DetermineCharEncoding_Test, extractCharEncodingFromMetaTag_doubleQuotes) {
	std::string testString = "charset = \"utf-8\"";
	EXPECT_EQ(UTF_8, determineCharEncoding.extractCharEncodingFromMetaTag(testString));
}
TEST_F(ParseHTML_DetermineCharEncoding_Test, extractCharEncodingFromMetaTag_singleQuotes) {
	std::string testString = "charset = 'utf-8'";
	EXPECT_EQ(UTF_8, determineCharEncoding.extractCharEncodingFromMetaTag(testString));
}
TEST_F(ParseHTML_DetermineCharEncoding_Test, extractCharEncodingFromMetaTag_unmatchedDoubleQuotes) {
	std::string testString = "charset = \"utf-8";
	EXPECT_EQ(NULL_ENC, determineCharEncoding.extractCharEncodingFromMetaTag(testString));
}
TEST_F(ParseHTML_DetermineCharEncoding_Test, extractCharEncodingFromMetaTag_unmatchedSingleQuotes) {
	std::string testString = "charset = 'utf-8";
	EXPECT_EQ(NULL_ENC, determineCharEncoding.extractCharEncodingFromMetaTag(testString));
}
TEST_F(ParseHTML_DetermineCharEncoding_Test, extractCharEncodingFromMetaTag_endSpace) {
	std::string testString = "charset = utf-8 ";
	EXPECT_EQ(UTF_8, determineCharEncoding.extractCharEncodingFromMetaTag(testString));
}
TEST_F(ParseHTML_DetermineCharEncoding_Test, extractCharEncodingFromMetaTag_endSemicolon) {
	std::string testString = "charset = utf-8;";
	EXPECT_EQ(UTF_8, determineCharEncoding.extractCharEncodingFromMetaTag(testString));
}

TEST_F(ParseHTML_DetermineCharEncoding_Test, getCharEncodingFromString_unicode_1_1_utf_8) {
	std::string testString = "unicode-1-1-utf-8";
	EXPECT_EQ(UTF_8, determineCharEncoding.getCharEncodingFromString(testString));
}
TEST_F(ParseHTML_DetermineCharEncoding_Test, getCharEncodingFromString_utf_8) {
	std::string testString = "utf-8";
	EXPECT_EQ(UTF_8, determineCharEncoding.getCharEncodingFromString(testString));
}
TEST_F(ParseHTML_DetermineCharEncoding_Test, getCharEncodingFromString_utf8) {
	std::string testString = "utf8";
	EXPECT_EQ(UTF_8, determineCharEncoding.getCharEncodingFromString(testString));
}
TEST_F(ParseHTML_DetermineCharEncoding_Test, getCharEncodingFromString_utf_16be) {
	std::string testString = "utf-16be";
	EXPECT_EQ(UTF_16_BE, determineCharEncoding.getCharEncodingFromString(testString));
}
TEST_F(ParseHTML_DetermineCharEncoding_Test, getCharEncodingFromString_utf_16) {
	std::string testString = "utf-16";
	EXPECT_EQ(UTF_16_LE, determineCharEncoding.getCharEncodingFromString(testString));
}
TEST_F(ParseHTML_DetermineCharEncoding_Test, getCharEncodingFromString_utf_16le) {
	std::string testString = "utf-16le";
	EXPECT_EQ(UTF_16_LE, determineCharEncoding.getCharEncodingFromString(testString));
}
TEST_F(ParseHTML_DetermineCharEncoding_Test, getCharEncodingFromString_unknown) {
	std::string testString = "badEncoding";
	EXPECT_EQ(NULL_ENC, determineCharEncoding.getCharEncodingFromString(testString));
}
TEST_F(ParseHTML_DetermineCharEncoding_Test, getCharEncodingFromString_none) {
	std::string testString = "";
	EXPECT_EQ(NULL_ENC, determineCharEncoding.getCharEncodingFromString(testString));
}
/**@}*/

} /* namespace ParseHTML */
