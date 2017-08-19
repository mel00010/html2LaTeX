/*******************************************************************************
 * DetermineCharEncoding.hpp
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
#ifndef HTML_PARSE_DETERMINECHARENCODING_HPP_
#define HTML_PARSE_DETERMINECHARENCODING_HPP_

//#include <gtest/gtest.h>
#include <gtest/gtest_prod.h>
//#include <fstream>
#include <iostream>
//#include <sstream>
#include <string>

#include "HTML/HTMLTypes.hpp"

//#endif /* DOXYGEN_SHOULD_SKIP_THIS */

/**
 * @file HTML/Parse/DetermineCharEncoding.hpp
 * @brief Holds the definition of class DetermineCharEncoding and many other auxiliary structs and classes.
 */

namespace HTML {
/**
 * @brief A namespace encapsulating everything related to HTML parsing
 */
namespace Parse {


/**
 * @brief A class for determining the character encoding of a document.
 *
 * Implements the algorithms for determining the character encoding of an HTML document defined in the W3C HTML5 specification.
 */
class DetermineCharEncoding {
#ifndef DOXYGEN_SHOULD_SKIP_THIS
	private:
		FRIEND_TEST(HTML_Parse_DetermineCharEncoding, determineCharEncoding);
		FRIEND_TEST(HTML_Parse_DetermineCharEncoding, tryUnicodeBOM);
		FRIEND_TEST(HTML_Parse_DetermineCharEncoding, preScan);
		FRIEND_TEST(HTML_Parse_DetermineCharEncoding, commentTagAlgorithm);
		FRIEND_TEST(HTML_Parse_DetermineCharEncoding, metaTagAlgorithm);
		FRIEND_TEST(HTML_Parse_DetermineCharEncoding, asciiTagAlgorithm);
		FRIEND_TEST(HTML_Parse_DetermineCharEncoding, punctuationTagAlgorithm);
		FRIEND_TEST(HTML_Parse_DetermineCharEncoding, getAttribute);
		FRIEND_TEST(HTML_Parse_DetermineCharEncoding, extractCharEncodingFromMetaTag);
		FRIEND_TEST(HTML_Parse_DetermineCharEncoding, getCharEncodingFromString);
		#endif /* DOXYGEN_SHOULD_SKIP_THIS */

	public:
		/**
		 * @brief Determines the character encoding of an input stream.
		 *
		 * Uses the algorithms for determining the character encoding of a document defined
		 * in Section 8.2 of the W3C HTML5 specification.
		 * @param input The input stream whose character encoding will be determined.
		 * @return A ContentType object containing the character encoding and the confidence in the result.
		 * @exception std::istream::failure The input stream failed before enough data could be read to make a guess.
		 * @test HTML::Parse::TEST(HTML_Parse_DetermineCharEncoding, determineCharEncoding)
		 */
		ContentType determineCharEncoding(std::istream& input);

	protected:

		/**
		 * @brief Tries to use Unicode Byte Order Markings to determine the content encoding of a document.
		 *
		 * Helper function for ContentType determineCharEncoding(std::istream& input)
		 * @see ContentType determineCharEncoding(std::istream& input)
		 * @param input The input stream whose character encoding will be determined.
		 * @return If successful, returns a ContentType object containing the character encoding and with the confidence CERTAIN.
		 * 		   If unsuccessful, returns a ContentType object with the character encoding UNKNOWN and the confidence IRRELEVANT.
		 * @exception std::istream::failure The input stream failed before enough data could be read to make a guess.
		 *
		 * @test HTML::Parse::TEST(HTML_Parse_DetermineCharEncoding, tryUnicodeBOM)
		 */
		ContentType tryUnicodeBOM(std::istream& input);

		/**
		 * @brief Scans the document looking for information about the character encoding.
		 * @param input The input stream whose character encoding will be determined.
		 * @return If successful, returns a ContentType object containing the character encoding and with the confidence CERTAIN.
		 * 		   If unsuccessful, returns a ContentType object with the character encoding UNKNOWN and the confidence IRRELEVANT.
		 * @exception std::istream::failure The input stream failed before enough data could be read to make a guess.
		 *
		 * @test HTML::Parse::TEST(HTML_Parse_DetermineCharEncoding, preScan)
		 */
		ContentType preScan(std::istream& input);

		/**
		 * @brief Reads from the input stream until the end of an HTML comment tag.
		 *
		 * Helper function for ContentType preScan(std::istream& input)
		 * Called by preScan() if the tag starts with the sequence of ASCII characters '<!--'
		 * @see ContentType preScan(std::istream& input)
		 * @param input The input stream whose character encoding will be determined.
		 * @return A ContentType object with the character encoding UNKNOWN and the confidence IRRELEVANT.
		 * @exception std::istream::failure The input stream failed before enough data could be read to make a guess.
		 *
		 * @test HTML::Parse::TEST(HTML_Parse_DetermineCharEncoding, commentTagAlgorithm)
		 */
		ContentType commentTagAlgorithm(std::istream& input);

		/**
		 * @brief Parses an HTML/XML meta tag to attempt to guess the character encoding.
		 *
		 * Helper function for ContentType preScan(std::istream& input)
		 * Called by preScan() if the tag starts with the case insensitive sequence of ASCII characters '<meta'
		 * @see ContentType preScan(std::istream& input)getCharEncodingFromString_utf_16le
		 * @param input The input stream whose character encoding will be determined.
		 * @return If successful, returns a ContentType object containing the character encoding and with the confidence CERTAIN.
		 * 		   If unsuccessful, returns a ContentType object with the character encoding UNKNOWN and the confidence IRRELEVANT.
		 * @exception std::istream::failure The input stream failed before enough data could be read to make a guess.
		 *
		 * @test HTML::Parse::TEST(HTML_Parse_DetermineCharEncoding, metaTagAlgorithm)
		 */
		ContentType metaTagAlgorithm(std::istream& input);

		/**
		 * @brief Reads from the input stream until the end of an HTML tag that starts with a sequence of ASCII letters.
		 *
		 * Helper function for ContentType preScan(std::istream& input)
		 * Called by preScan() if a tag starts with a sequence of ASCII letters other than '<meta'.
		 * @see ContentType preScan(std::istream& input)
		 * @param input The input stream whose character encoding will be determined.
		 * @return A ContentType object with the character encoding UNKNOWN and the confidence IRRELEVANT.
		 * @exception std::istream::failure The input stream failed before enough data could be read to make a guess.
		 *
		 * @test HTML::Parse::TEST(HTML_Parse_DetermineCharEncoding, asciiTagAlgorithm)
		 */
		ContentType asciiTagAlgorithm(std::istream& input);

		/**
		 * @brief Reads from the input stream until the end an HTML tag that starts with the ASCII characters '!', '?', or '/'.
		 *
		 * Helper function for ContentType preScan(std::istream& input)
		 * Called if an HTML tag starts with the ASCII characters '!', '?', or '/'.
		 * @see ContentType preScan(std::istream& input)
		 * @param input The input stream whose character encoding will be determined.
		 * @return A ContentType object with the character encoding UNKNOWN and the confidence IRRELEVANT.
		 * @exception std::istream::failure The input stream failed before enough data could be read to make a guess.
		 *
		 * @test HTML::Parse::TEST(HTML_Parse_DetermineCharEncoding, punctuationTagAlgorithm)
		 */
		ContentType punctuationTagAlgorithm(std::istream& input);

		/**
		 * @brief Gets an HTML attribute from the input stream.
		 * @param input The input stream whose character encoding will be determined.
		 * @param swallowExceptions Boolean value determining whether the algorithm should throw an exception if the
		 * 							input stream throws an exception or simply return with the character encoding UNKNOWN
		 * 							and confidence IRRELEVANT. Defaults to true.
		 * @return An Attribute object containing the name of the attribute and its value.getCharEncodingFromString_utf8
		 * 		   If swallowExceptions is true and the input stream throws an exception, then the function returns an
		 * 		   Attribute object whose name and value fields are empty.
		 * 		   Otherwise, the exception is thrown upwards.
		 * @exception std::istream::failure The input stream failed before enough data could be read to make a guess.
		 *
		 * @test HTML::Parse::TEST(HTML_Parse_DetermineCharEncoding, getAttribute)
		 */
		Attribute getAttribute(std::istream& input, bool swallowExceptions = true);

		/**
		 * @brief Gets an HTML attribute value from the input stream.
		 *
		 * Helper function for Attribute getAttribute(std::istream& input, bool swallowExceptions = true)
		 * @param input The input stream whose character encoding will be determined.
		 * @param buf A reference to the buffer holding the last character read from the input stream
		 * @return A string containing the attribute's value
		 */
		std::string getAttributeValue(std::istream& input, Byte& buf);

		/**
		 * @brief Extracts an attribute value in quotes from the input stream.
		 *extractCharEncodingFromMetaTag_unmatchedDoubleQuotes
		 * Helper function for std::string getAttributeValue(std::istream& input, Byte& buf)
		 * Called if the attribute value has is in quotes.
		 * @see std::string getAttributeValue(std::istream& input, Byte& buf)
		 * @param input The input stream whose character encoding will be determined.
		 * @param buf A reference to the buffer holding the last character read from the input stream
		 * @param value A reference to the current contents of the attribute value.
		 * @return A string containing the attribute's value.
		 */
		std::string quoteLoop(std::istream& input, Byte& buf, std::string& value);

		/**
		 * @brief Extracts an attribute value that is not in quotes from the input stream.
		 *
		 * Helper function for std::string getAttributeValue(std::istream& input, Byte& buf)
		 * Called if the attribute value is not in quotes.
		 * @see std::string getAttributeValue(std::istream& input, Byte& buf)
		 * @param input The input stream whose character encoding will be determined.
		 * @param buf A reference to the buffer holding the last character read from the input stream
		 * @param value A reference to the current contents of the attribute value.
		 * @return A string containing the attribute's value.
		 */
		std::string processingLoop(std::istream& input, Byte& buf, std::string& value);

		/**
		 * @brief Extracts a character encoding from a HTML/XML meta tag.
		 * @param string The string containing the meta tag to extract the character encoding from
		 * @return If a character encoding is successfully extracted, the function returns the character encoding.
		 * 		   If no character encoding is extracted, the function returns NULL_ENC.
		 *
		 * @test HTML::Parse::TEST(HTML_Parse_DetermineCharEncoding, extractCharEncodingFromMetaTag)
		 */
		CharEncoding extractCharEncodingFromMetaTag(std::string& string);

		/**
		 * @brief Extracts a character encoding from a string.
		 *
		 * The character encoding is extracted according to the definitions in the table below.
		 * String 					| Character Encoding
		 * -------------------------| -------------
		 *  unicode-1-1-utf-8 		| UTF_8
		 *  utf-8					| UTF_8
		 *  utf8					| UTF_8
		 *  utf-16be				| UTF_16_BE
		 *  utf-16le				| UTF_16_LE
		 *  utf-16					| UTF_16_LE
		 *
		 *  Any string not in the table above is assigned the character encoding of NULL_ENC.
		 *
		 * @see HTMl::Parse::CharEncoding
		 * @param input The string the character encoding will be attempted to be extracted from.
		 * @return If a character encoding is successfully recognized, the function returns the character encoding.
		 * 		   If the character encoding is unrecognized, the function returns NULL_ENC.
		 *
		 * @test HTML::Parse::TEST(HTML_Parse_DetermineCharEncoding, getCharEncodingFromString)
		 */
		CharEncoding getCharEncodingFromString(std::string& input);

};

} /* namespace Parse */
} /* namespace HTML */

#endif /* HTML_PARSE_DETERMINECHARENCODING_HPP_ */
