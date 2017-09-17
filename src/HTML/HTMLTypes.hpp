/*******************************************************************************
 * HTMLTypes.hpp
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
#ifndef HTML_HTMLTYPES_HPP_
#define HTML_HTMLTYPES_HPP_

#include <cstdint>
#include <iostream>
#include <string>

/**
 * @file src/HTML/HTMLTypes.hpp
 * @brief Holds type declarations for many types relating to HTML
 */
/**
 * @dir src/HTML
 * @brief Holds all source files related to HTML
 */
/**
 * @brief Namespace encapsulating everything relating to HTML
 */
namespace HTML {

/**
 * @brief A convenience type that holds one byte.
 *
 * Derived from uint8_t.
 */
typedef uint8_t Byte;

enum class InsertionMode {
	INITIAL,
	BEFORE_HTML,
	BEFORE_HEAD,
	IN_HEAD,
	IN_HEAD_NOSCRIPT,
	AFTER_HEAD,
	IN_BODY,
	TEXT,
	IN_TABLE,
	IN_TABLE_TEXT,
	IN_CAPTION,
	IN_COLUMN_GROUP,
	IN_TABLE_BODY,
	IN_ROW,
	IN_CELL,
	IN_SELECT,
	IN_SELECT_IN_TABLE,
	IN_TEMPLATE,
	AFTER_BODY,
	IN_FRAMESET,
	AFTER_FRAMESET,
	AFTER_AFTER_BODY,
	AFTER_AFTER_FRAMESET
};

enum class Alignment {
	LEFT,
	CENTER,
	RIGHT,
	JUSTIFY
};
enum class HTMLHeadings {
	H1,
	H2,
	H3,
	H4,
	H5,
	H6
};

/**
 * @brief A three valued boolean logic type.
 */
enum class TriBool {
	NONE, /**<	@brief Neither true nor false. @details Used to signify that the variable has not been explicitly set to be true or false. */
	TRUE, /**<	@brief True */
	FALSE /**<	@brief False */
};

/**
 * @brief Specifies the valid character encodings for a document.
 *
 * Defined by the W3C HTML5 standard
 */
enum class CharEncoding {
	NULL_ENC, /**<	@brief Represents that the character encoding has not been set by the algorithm. */
	UNKNOWN, /**<	@brief Represents an unknown character encoding. */
	UTF_16_BE, /**<	@brief Represents the UTF-16 big endian character encoding. */
	UTF_16_LE, /**<	@brief Represents the UTF-16 little endian character encoding. */
	UTF_8 /**<		@brief Represents the UTF-8 character encoding. */
};

/**
 * @brief Specifies the confidence values for character encoding guesses.
 *
 * Defined by the W3C HTML5 standard.
 */
enum class Confidence {
	CERTAIN, /**<	@brief Indicates a definite match for the character encoding of the document.*/
	TENTATIVE, /**<	@brief Indicates a tentative guess for the character encoding of the document. */
	IRRELEVANT /**<	@brief Indicates that a guess could not be made. */
};

/**
 * @brief Holds a character encoding and a confidence.
 *
 * Represents a result from the character encoding determining algorithm defined in the W3C HTML5 standard
 */
class ContentType {
	public:
		ContentType(CharEncoding charEncoding = CharEncoding::UNKNOWN, Confidence confidence = Confidence::IRRELEVANT) :
				charEncoding(charEncoding), confidence(confidence) {
		}
		CharEncoding charEncoding = CharEncoding::UNKNOWN; /**<	@brief Holds the character encoding of the document. */
		Confidence confidence = Confidence::IRRELEVANT; /**<	@brief Holds the confidence of the guess at the character encoding. */
};

/**
 * @brief Describes the formatting properties of an HTML element.
 */
class Formatting {
	public:
		bool bold;
		bool italic;
		bool underline;
		bool strikethrough;
		bool highlight;
		bool smallCaps;
		bool slanted;

		Alignment alignment;
};

/**
 * @brief Holds an HTML attribute.
 */
class Attribute {
	public:
		Attribute(std::string name = "", std::string value = "") :
				name(name), value(value) {
		}
		std::string name = ""; /**<	@brief Holds the name of the attribute. */
		std::string value = ""; /**<@brief Holds the value of the attribute. */
};

/**
 * @brief Writes an Attribute object to an output stream.
 * @param os A reference to std::ostream object for the Attribute object to be written to.
 * @param attribute A reference to the Attribute object to be displayed.
 * @return A reference to the std::ostream object passed to the function.
 */
::std::ostream& operator<<(::std::ostream& os, const Attribute& attribute);

/**
 * @brief Compares two Attribute objects.
 * @param rhs The Attribute object on the right hand side of the expression
 * @param lhs The Attribute object on the left hand side of the expression
 * @return Returns true if the attribute objects have the same name and value, otherwise returns false
 *
 * @test TEST(HTMLTypes, Attribute)
 */
inline bool operator==(const Attribute& rhs, const Attribute& lhs) {
	if ((rhs.name == lhs.name) && (rhs.value == lhs.value)) {
		return true;
	}
	return false;
}
/**
 * @brief Compares two Attribute objects.
 * @param rhs The Attribute object on the right hand side of the expression
 * @param lhs The Attribute object on the left hand side of the expression
 * @return Returns true if the attribute objects do not have the same name and value, otherwise returns false
 *
 * @test TEST(HTMLTypes, Attribute)
 */
inline bool operator!=(const Attribute& rhs, const Attribute& lhs) {
	if (!(rhs == lhs)) {
		return true;
	}
	return false;
}

/**
 * @brief Compares a bool and an Attribute object
 * @param rhs The bool being compared
 * @param lhs The Attribute object being compared
 * @return If the bool evaluates to true, the function returns false
 * 		   if either the Attribute object's name or value fields are not empty,
 * 		   otherwise it returns true. If the bool evaluates to false, then the
 * 		   function returns the opposite values.
 *
 * @test TEST(HTMLTypes, Attribute)
 */
inline bool operator==(const bool& rhs, const Attribute& lhs) {
	if (lhs.name.empty() && lhs.value.empty()) {
		if (rhs) {
			return false;
		} else {
			return true;
		}
	} else {
		if (rhs) {
			return true;
		} else {
			return false;
		}
	}
	return false;
}

/**
 * @brief Compares an Attribute object and a bool
 * @see operator==(const bool& rhs, const Attribute& lhs)
 * @param lhs The Attribute object being compared
 * @param rhs The bool being compared
 * @return Returns the result of comparing a bool and an Attribute object
 *
 * @test TEST(HTMLTypes, Attribute)
 */
inline bool operator==(const Attribute& lhs, const bool& rhs) {
	return (rhs == lhs);
}

/**
 * @brief Writes an CharEncoding object to an output stream
 * @param os A reference to std::ostream object for the CharEncoding object to be written to.
 * @param charEncoding A reference to the Attribute object to be displayed
 * @return A reference to the std::ostream object passed to the function
 */
::std::ostream& operator<<(::std::ostream& os, const CharEncoding& charEncoding);

/**
 * @brief Writes a Confidence object to an output stream
 * @param os A reference to std::ostream object for the Confidence object to be written to.
 * @param confidence A reference to the Confidence object to be displayed
 * @return A reference to the std::ostream object passed to the function
 */
::std::ostream& operator<<(::std::ostream& os, const Confidence& confidence);

/**
 * @brief Writes a ContentType object to an output stream
 * @param os A reference to std::ostream object for the ContentType object to be written to.
 * @param contentType A reference to the ContentType object to be displayed.
 * @return A reference to the std::ostream object passed to the function
 */
::std::ostream& operator<<(::std::ostream& os, const ContentType& contentType);

/**
 * @brief Compares two ContentType objects
 * @param rhs The ContentType object being compared on the right hand side of the expression.
 * @param lhs The ContentType object being compared on the left hand side of the expression.
 * @return Returns true if the charEncoding and confidence properties of the ContentType objects are equal.
 * 		   Otherwise, the function returns false.
 *
 * @test TEST(HTMLTypes, ContentType)
 */
inline bool operator==(const ContentType& rhs, const ContentType& lhs) {
	if ((rhs.charEncoding == lhs.charEncoding) && (rhs.confidence == lhs.confidence)) {
		return true;
	}
	return false;
}

/**
 * @brief Compares two ContentType objects
 * @param rhs The ContentType object being compared on the right hand side of the expression.
 * @param lhs The ContentType object being compared on the left hand side of the expression.
 * @return Returns true if the charEncoding and confidence properties of the ContentType objects are not equal.
 * 		   Otherwise, the function returns false.
 * @test TEST(HTMLTypes, ContentType)
 */
inline bool operator!=(const ContentType& rhs, const ContentType& lhs) {
	if (!(rhs == lhs)) {
		return true;
	}
	return false;
}

} /* namespace HTML */



#endif /* HTML_HTMLTYPES_HPP_ */
