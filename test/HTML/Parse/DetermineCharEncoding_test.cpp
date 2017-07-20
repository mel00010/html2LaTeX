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

#include <gtest/gtest.h>
#include <HTML/HTMLTypes.hpp>
#include <HTML/Parse/DetermineCharEncoding.hpp>
#include <HTML/Parse/MagicString.hpp>
#include <exception>
#include <iostream>

/**
 * @file test/HTML/Parse/DetermineCharEncoding_test.cpp
 * @brief Holds all of the unit tests for HTML/Parse/DetermineCharEncoding.hpp and HTML/Parse/DetermineCharEncoding.cpp
 */
/**
 * @dir test/HTML/Parse
 * @brief Holds all of the source files and headers for the tests for the directory HTML/Parse
 */
namespace HTML {
namespace Parse {

/**
 * @{
 * @name DetermineCharEncoding_Tests
 */

TEST(HTML_Parse_DetermineCharEncoding, determineCharEncoding) {
	DetermineCharEncoding determineCharEncoding;

	std::istringstream BOM("\xFE\xFFunrelated <tags> and other text");
	std::istringstream preScan("<html>\n<head>\n\t<meta charset=utf-8> more unrelated text and <tags>");

	EXPECT_EQ(ContentType(UTF_16_BE, CERTAIN), determineCharEncoding.determineCharEncoding(BOM));
	EXPECT_EQ(ContentType(UTF_8, TENTATIVE), determineCharEncoding.determineCharEncoding(preScan));
}


TEST(HTML_Parse_DetermineCharEncoding, preScan) {
	DetermineCharEncoding determineCharEncoding;

	std::istringstream commentTagAlgorithm("<html>\n<head>\n\t<!-- charset=utf-8> more unrelated text and <tags> --> <meta charset=utf-8>");
	std::istringstream metaTagAlgorithm("<html>\n<head>\n\t<meta charset=utf-8> more unrelated text and <tags>");
	std::istringstream asciiTagAlgorithm("<html>\n<head>\n\t<unrelatedTag charset=utf-8> more unrelated text and <tags><unrelatedTag> <meta charset=utf-8>");
	std::istringstream punctuationTagAlgorithm("<html>\n<head>\n\t<? charset=utf-8> more unrelated text and <tags> > <meta charset=utf-8>");


	EXPECT_EQ(ContentType(UTF_8, TENTATIVE), determineCharEncoding.determineCharEncoding(commentTagAlgorithm));
	EXPECT_EQ(ContentType(UTF_8, TENTATIVE), determineCharEncoding.determineCharEncoding(metaTagAlgorithm));
	EXPECT_EQ(ContentType(UTF_8, TENTATIVE), determineCharEncoding.determineCharEncoding(asciiTagAlgorithm));
	EXPECT_EQ(ContentType(UTF_8, TENTATIVE), determineCharEncoding.determineCharEncoding(punctuationTagAlgorithm));
}
TEST(HTML_Parse_DetermineCharEncoding, tryUnicodeBOM) {
	DetermineCharEncoding determineCharEncoding;

	std::istringstream utf_16_be("\xFE\xFF");
	std::istringstream utf_16_le("\xFF\xFE");
	std::istringstream utf_8("\xEF\xBB\xBF");
	std::istringstream invalidBOM("\x5A,\xDE\xCC");
	std::istringstream none("");

	EXPECT_EQ(ContentType(UTF_16_BE, CERTAIN), determineCharEncoding.tryUnicodeBOM(utf_16_be));
	EXPECT_EQ(ContentType(UTF_16_LE, CERTAIN), determineCharEncoding.tryUnicodeBOM(utf_16_le));
	EXPECT_EQ(ContentType(UTF_8, CERTAIN), determineCharEncoding.tryUnicodeBOM(utf_8));
	EXPECT_EQ(ContentType(UNKNOWN, IRRELEVANT), determineCharEncoding.tryUnicodeBOM(invalidBOM));
	EXPECT_EQ(ContentType(UNKNOWN, IRRELEVANT), determineCharEncoding.tryUnicodeBOM(none));
}

TEST(HTML_Parse_DetermineCharEncoding, commentTagAlgorithm) {
	DetermineCharEncoding determineCharEncoding;

	std::istringstream normal("<!-- commentText -->");
	std::istringstream sharingDashes("<!-->");
	std::istringstream notCommentTag("<notCommentTag>");
	std::istringstream unclosed("<!-- ");

	EXPECT_EQ(ContentType(UNKNOWN, IRRELEVANT), determineCharEncoding.commentTagAlgorithm(normal));
	EXPECT_EQ(ContentType(UNKNOWN, IRRELEVANT), determineCharEncoding.commentTagAlgorithm(sharingDashes));
	EXPECT_EQ(ContentType(UNKNOWN, IRRELEVANT), determineCharEncoding.commentTagAlgorithm(notCommentTag));
	EXPECT_THROW(determineCharEncoding.commentTagAlgorithm(unclosed), std::istream::failure);
}

TEST(HTML_Parse_DetermineCharEncoding, metaTagAlgorithm) {
	DetermineCharEncoding determineCharEncoding;

	std::istringstream normal("<meta charset=utf-8>");
	std::istringstream notMetaTag("<notMetaTag>");
	std::istringstream content_Present_http_equiv_Present("<meta content=\"charset=utf-8\" http-equiv=\"content-type\">");
	std::istringstream content_Present_http_equiv_NotPresent("<meta content=\"charset=utf-8\" >");
	std::istringstream content_Present_http_equiv_HasNoValue("<meta content=\"charset=utf-8\" http-equiv>");
	std::istringstream content_Present_http_equiv_HasWrongValue("<meta content=\"charset=utf-8\" http-equiv=\"wrong\">");
	std::istringstream content_Present_charset_Present("<meta content=\"charset=utf-8\" charset=\"utf-8\">");
	std::istringstream charset("<meta charset=utf-8>");
	std::istringstream noAttributes("<meta>");
	std::istringstream noUsefulAttributes("<meta attributeName1=attributeValue1 attributeName2=attributeValue2>");
	std::istringstream unclosed("<meta");

	EXPECT_EQ(ContentType(UTF_8, TENTATIVE), determineCharEncoding.metaTagAlgorithm(normal));
	EXPECT_EQ(ContentType(UNKNOWN, IRRELEVANT), determineCharEncoding.metaTagAlgorithm(notMetaTag));
	EXPECT_EQ(ContentType(UTF_8, TENTATIVE), determineCharEncoding.metaTagAlgorithm(content_Present_http_equiv_Present));
	EXPECT_EQ(ContentType(UNKNOWN, IRRELEVANT), determineCharEncoding.metaTagAlgorithm(content_Present_http_equiv_NotPresent));
	EXPECT_EQ(ContentType(UNKNOWN, IRRELEVANT), determineCharEncoding.metaTagAlgorithm(content_Present_http_equiv_HasNoValue));
	EXPECT_EQ(ContentType(UNKNOWN, IRRELEVANT), determineCharEncoding.metaTagAlgorithm(content_Present_http_equiv_HasWrongValue));
	EXPECT_EQ(ContentType(UTF_8, TENTATIVE), determineCharEncoding.metaTagAlgorithm(content_Present_charset_Present));
	EXPECT_EQ(ContentType(UTF_8, TENTATIVE), determineCharEncoding.metaTagAlgorithm(charset));
	EXPECT_EQ(ContentType(UNKNOWN, IRRELEVANT), determineCharEncoding.metaTagAlgorithm(noAttributes));
	EXPECT_EQ(ContentType(UNKNOWN, IRRELEVANT), determineCharEncoding.metaTagAlgorithm(noUsefulAttributes));
	EXPECT_THROW(determineCharEncoding.metaTagAlgorithm(unclosed), std::istream::failure);
}

TEST(HTML_Parse_DetermineCharEncoding, asciiTagAlgorithm) {
	DetermineCharEncoding determineCharEncoding;

	std::istringstream normal("<AsciiTag>");
	std::istringstream notAsciiTag("<!-->");
	std::istringstream startTag("<AsciiTag>");
	std::istringstream endTag("</AsciiTag>");
	std::istringstream startTagWithAttributes("<AsciiTag attribute1=value1>");
	std::istringstream unclosed("<AsciiTag");

	EXPECT_EQ(ContentType(UNKNOWN, IRRELEVANT), determineCharEncoding.asciiTagAlgorithm(normal));
	EXPECT_EQ(ContentType(UNKNOWN, IRRELEVANT), determineCharEncoding.asciiTagAlgorithm(notAsciiTag));
	EXPECT_EQ(ContentType(UNKNOWN, IRRELEVANT), determineCharEncoding.asciiTagAlgorithm(startTag));
	EXPECT_EQ(ContentType(UNKNOWN, IRRELEVANT), determineCharEncoding.asciiTagAlgorithm(endTag));
	EXPECT_EQ(ContentType(UNKNOWN, IRRELEVANT), determineCharEncoding.asciiTagAlgorithm(startTagWithAttributes));
	EXPECT_THROW(determineCharEncoding.asciiTagAlgorithm(unclosed), std::istream::failure);
}

TEST(HTML_Parse_DetermineCharEncoding, punctuationTagAlgorithm) {
	DetermineCharEncoding determineCharEncoding;

	std::istringstream normal("<!punctuationTag>");
	std::istringstream notPunctuationTag("<notPunctuationTag>");
	std::istringstream unclosed("<!");

	EXPECT_EQ(ContentType(UNKNOWN, IRRELEVANT), determineCharEncoding.punctuationTagAlgorithm(normal));
	EXPECT_EQ(ContentType(UNKNOWN, IRRELEVANT), determineCharEncoding.punctuationTagAlgorithm(notPunctuationTag));
	EXPECT_THROW(determineCharEncoding.punctuationTagAlgorithm(unclosed), std::istream::failure);
}

TEST(HTML_Parse_DetermineCharEncoding, getAttribute) {
	DetermineCharEncoding determineCharEncoding;

	std::istringstream nameAndValue("testName=testValue");
	std::istringstream nameOnly("testName");
	std::istringstream unclosed("testName = >");
	std::istringstream noAttribute("");
	std::istringstream doubleQuotes("testName = \"testValue\"");
	std::istringstream singleQuotes("testName = 'testValue'");
	std::istringstream unmatchedDoubleQuotes("testName = \"testValue");
	std::istringstream unmatchedSingleQuotes("testName = 'testValue");

	nameAndValue.exceptions(std::istream::eofbit);
	nameOnly.exceptions(std::istream::eofbit);
	unclosed.exceptions(std::istream::eofbit);
	noAttribute.exceptions(std::istream::eofbit);
	doubleQuotes.exceptions(std::istream::eofbit);
	singleQuotes.exceptions(std::istream::eofbit);
	unmatchedDoubleQuotes.exceptions(std::istream::eofbit);
	unmatchedSingleQuotes.exceptions(std::istream::eofbit);

	EXPECT_EQ(Attribute("testname", "testvalue"), determineCharEncoding.getAttribute(nameAndValue));
	EXPECT_EQ(Attribute("testname", ""), determineCharEncoding.getAttribute(nameOnly));
	EXPECT_EQ(Attribute("testname", ""), determineCharEncoding.getAttribute(unclosed));
	EXPECT_EQ(Attribute("", ""), determineCharEncoding.getAttribute(noAttribute));
	EXPECT_EQ(Attribute("testname", "testvalue"), determineCharEncoding.getAttribute(doubleQuotes));
	EXPECT_EQ(Attribute("testname", "testvalue"), determineCharEncoding.getAttribute(singleQuotes));
	EXPECT_EQ(Attribute("testname", "testvalue"), determineCharEncoding.getAttribute(unmatchedDoubleQuotes));
	EXPECT_EQ(Attribute("testname", "testvalue"), determineCharEncoding.getAttribute(unmatchedSingleQuotes));

}

TEST(HTML_Parse_DetermineCharEncoding, extractCharEncodingFromMetaTag) {
	DetermineCharEncoding determineCharEncoding;

	std::string normal = "charSet = utf-8";
	std::string partialCharset = "char=utf-8";
	std::string noCharset = "utf-8";
	std::string noEncoding = "charset=";
	std::string noEquals = "charset utf-8";
	std::string unknownEncoding = "charset=unknown";
	std::string doubleQuotes = "charset = \"utf-8\"";
	std::string singleQuotes = "charset = 'utf-8'";
	std::string unmatchedDoubleQuotes = "charset = \"utf-8";
	std::string unmatchedSingleQuotes = "charset = 'utf-8";
	std::string endSpace = "charset = utf-8 ";
	std::string endSemicolon = "charset = utf-8;";


	EXPECT_EQ(UTF_8, determineCharEncoding.extractCharEncodingFromMetaTag(normal));
	EXPECT_EQ(NULL_ENC, determineCharEncoding.extractCharEncodingFromMetaTag(partialCharset));
	EXPECT_EQ(NULL_ENC, determineCharEncoding.extractCharEncodingFromMetaTag(noCharset));
	EXPECT_EQ(NULL_ENC, determineCharEncoding.extractCharEncodingFromMetaTag(noEncoding));
	EXPECT_EQ(NULL_ENC, determineCharEncoding.extractCharEncodingFromMetaTag(noEquals));
	EXPECT_EQ(NULL_ENC, determineCharEncoding.extractCharEncodingFromMetaTag(unknownEncoding));
	EXPECT_EQ(UTF_8, determineCharEncoding.extractCharEncodingFromMetaTag(doubleQuotes));
	EXPECT_EQ(UTF_8, determineCharEncoding.extractCharEncodingFromMetaTag(singleQuotes));
	EXPECT_EQ(NULL_ENC, determineCharEncoding.extractCharEncodingFromMetaTag(unmatchedDoubleQuotes));
	EXPECT_EQ(NULL_ENC, determineCharEncoding.extractCharEncodingFromMetaTag(unmatchedSingleQuotes));
	EXPECT_EQ(UTF_8, determineCharEncoding.extractCharEncodingFromMetaTag(endSpace));
	EXPECT_EQ(UTF_8, determineCharEncoding.extractCharEncodingFromMetaTag(endSemicolon));
}

TEST(HTML_Parse_DetermineCharEncoding, getCharEncodingFromString) {
	DetermineCharEncoding determineCharEncoding;

	std::string unicode_1_1_utf_8 = "unicode-1-1-utf-8";
	std::string utf_8 = "utf-8";
	std::string utf8 = "utf8";
	std::string utf_16be = "utf-16be";
	std::string utf_16 = "utf-16";
	std::string utf_16le = "utf-16le";
	std::string unknown = "badEncoding";
	std::string none = "";

	EXPECT_EQ(UTF_8, determineCharEncoding.getCharEncodingFromString(unicode_1_1_utf_8));
	EXPECT_EQ(UTF_8, determineCharEncoding.getCharEncodingFromString(utf_8));
	EXPECT_EQ(UTF_8, determineCharEncoding.getCharEncodingFromString(utf8));
	EXPECT_EQ(UTF_16_BE, determineCharEncoding.getCharEncodingFromString(utf_16be));
	EXPECT_EQ(UTF_16_LE, determineCharEncoding.getCharEncodingFromString(utf_16));
	EXPECT_EQ(UTF_16_LE, determineCharEncoding.getCharEncodingFromString(utf_16le));
	EXPECT_EQ(NULL_ENC, determineCharEncoding.getCharEncodingFromString(unknown));
	EXPECT_EQ(NULL_ENC, determineCharEncoding.getCharEncodingFromString(none));

}
/**@}*/
} /* namespace Parse */
} /* namespace HTML */
