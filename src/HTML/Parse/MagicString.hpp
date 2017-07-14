/*******************************************************************************
 * MagicString.hpp
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
#ifndef HTML_PARSE_MAGICSTRING_HPP_
#define HTML_PARSE_MAGICSTRING_HPP_

#include <HTML/Microsyntaxes/ASCII.hpp>


#include <cassert>
#include <cstring>

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#include <gtest/gtest.h>
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

/**
 * @file  HTML/Parse/MagicString.hpp
 * @brief Holds many constants and magic strings relating to determining the character encoding of a document,
 * 		  in addition to their helper classes and functions.
 */
namespace HTML {
namespace Parse {

typedef uint8_t Byte;

/**
 * @brief A namespace holding constants and magic strings.
 */
namespace MagicString {

/**
 * @brief An array containing the characters getAttribute() will skip.
 * @showinitializer
 */
constexpr Byte ATTRIBUTE_SKIP_CHARS[6] = {
		0x09,
		0x0A,
		0x0C,
		0x0D,
		0x20,
		0x2F
};


/**
 * @brief Tests if a Byte array holds the case insensitive ASCII string 'charset'
 * @param string The Byte array to be tested
 * @return If the Byte array matches the case insensitive ASCII string 'charset', the function returns true.
 * 		   Otherwise, the function returns false.
 *
 * @test MagicString_Test::TEST_F(ParseHTML_MagicString_isCharset_Test, trueCase)
 * @test MagicString_Test::TEST_F(ParseHTML_MagicString_isCharset_Test, falseCase)
 */
bool isCharset(const Byte (&string)[7]);

/**
 * @brief Holds the Unicode Byte Order Marking strings
 */
struct UnicodeBOM {
		static constexpr Byte UTF_16_BE[2] = { 0xFE, 0xFF }; /**<	@brief Holds the BOM for the UTF-16 big endian encoding */
		static constexpr Byte UTF_16_LE[2] = { 0xFF, 0xFE }; /**<	@brief Holds the BOM for the UTF-16 little endian encoding */
		static constexpr Byte UTF_8[3] = { 0xEF, 0xBB, 0xBF }; /**<	@brief Holds the BOM for the UTF-8 encoding */
};
/**
 * @brief Holds the byte sequences indicating the start or end of an HTML comment tag.
 */
struct CommentTag {
		static constexpr Byte start[4] = { 0x3C, 0x21, 0x2D, 0x2D }; /**< 	@brief Holds the byte sequence for the beginning of a comment tag */
		static constexpr Byte end[3] = { 0x2D, 0x2D, 0x3E }; /**< 			@brief Holds the byte sequence for the end of a comment tag */
};

/**
 * @brief Holds the byte sequences indicating the start or end of an HTML tag starting with '!', '?', or '/'.
 *
 * @test MagicString_Test::TEST_F(ParseHTML_MagicString_PunctuationTag_Test, exclamationPointEqual)
 * @test MagicString_Test::TEST_F(ParseHTML_MagicString_PunctuationTag_Test, forwardSlashEqual)
 * @test MagicString_Test::TEST_F(ParseHTML_MagicString_PunctuationTag_Test, questionMarkEqual)
 * @test MagicString_Test::TEST_F(ParseHTML_MagicString_PunctuationTag_Test, almostEqual)
 * @test MagicString_Test::TEST_F(ParseHTML_MagicString_PunctuationTag_Test, notEqual)
 */
struct PunctuationTag {
		/**
		 * @brief An enum mapping the range of integers [0,1] to symbols.
		 * @details Used so that indexes outside of the array throw type errors.
		 */
		enum PunctuationTagSizeT {
			FIRST = 0, /**< 	@brief 0 */
			SECOND = 1, /**< 	@brief 1 */
		};

		const Byte first[1] = { 0x3C }; /**< 				@brief An array holding all of the possibilities for the first character of the tag */
		const Byte second[3] = { 0x21, 0x2F, 0x3F }; /**< 	@brief An array holding all of the possibilities for the second character of the tag*/

		/**
		 * @brief Defines array-like access to the struct.
		 * @param idx The index of the array being fetched.
		 * @return Returns the array corresponding to the index.
		 */
		const Byte** operator[](PunctuationTagSizeT idx) const {
			assert((idx == PunctuationTagSizeT::FIRST) ||
					(idx == PunctuationTagSizeT::SECOND));
			switch (idx) {
				case FIRST:
					return (const Byte**) (&first);
				case SECOND:
					return (const Byte**) (&second);
			}
			// Should be impossible for control to reach here.
			return nullptr;
		}
};

/**
 * @brief Compares a byte sequence to a PunctuationTag object
 * @param lhs The byte sequence being compared
 * @param rhs The PunctuationTag object being compared
 * @return If the byte sequence matches an possible pattern for a punctuation tag, then the function returns true.
 * 		   Otherwise, the function returns false.
 */
inline bool operator==(const Byte (&lhs)[2], const MagicString::PunctuationTag& rhs) {
	{
		Byte byte = lhs[0];
		Byte reference[1];
		memcpy(reference, rhs[(Parse::MagicString::PunctuationTag::PunctuationTagSizeT) 0], 1);
		if (reference[0] != byte) {
			return false;
		}
	}
	{
		Byte byte = lhs[1];
		Byte reference[3];
		memcpy(reference, rhs[(Parse::MagicString::PunctuationTag::PunctuationTagSizeT) 1], 3);
		bool equal = false;
		for (int j = 0; j < 3; j++) {
			if (reference[j] == byte) {
				equal = true;
				break;
			}
		}
		if (!equal) {
			return false;
		}
	}
	return true;
}

/**
 * @brief Compares a PunctuationTag object to a byte sequence
 * @param lhs The PunctuationTag object being compared
 * @param rhs The byte sequence being compared
 * @return If the byte sequence matches an possible pattern for a punctuation tag, then the function returns true.
 * 		   Otherwise, the function returns false.
 */
inline bool operator==(const MagicString::PunctuationTag& lhs, const Byte (&rhs)[2]) {
	return (rhs == lhs);
}

/**
 * @brief Compares a byte sequence to a PuncuationTag object
 * @param lhs The PunctuationTag object being compared
 * @param rhs The PunctuationTag object being compared
 * @return If the byte sequence matches an possible pattern for a punctuation tag, then the function returns false.
 * 		   Otherwise, the function returns true.
 */
inline bool operator!=(const Byte (&lhs)[2], const MagicString::PunctuationTag& rhs) {
	return !(lhs == rhs);
}

/**
 * @brief Compares a PunctuationTag object to a byte sequence
 * @param lhs The PunctuationTag object being compared
 * @param rhs The byte sequence being compared
 * @return If the byte sequence matches an possible pattern for a punctuation tag, then the function returns false.
 * 		   Otherwise, the function returns true.
 */
inline bool operator!=(const MagicString::PunctuationTag& lhs, const Byte (&rhs)[2]) {
	return !(lhs == rhs);
}

/**
 * @brief Holds the byte sequences corresponding to a case-insensitive HTML/XML meta tag.
 *
 * @test MagicString_Test::TEST_F(ParseHTML_MagicString_MetaTag_Test, equal)
 * @test MagicString_Test::TEST_F(ParseHTML_MagicString_MetaTag_Test, almostEqual)
 * @test MagicString_Test::TEST_F(ParseHTML_MagicString_MetaTag_Test, notEqual)
 */
struct MetaTag {
		/**
		 * @brief An enum mapping the range of integers [0,5] to symbols.
		 * @details Used so that indexes outside of the array throw type errors.
		 */
		enum MetaTagSizeT {
			FIRST = 0, /**< 	@brief 0 */
			SECOND = 1, /**< 	@brief 1 */
			THIRD = 2, /**< 	@brief 2 */
			FOURTH = 3, /**< 	@brief 3 */
			FIFTH = 4, /**< 	@brief 4 */
			SIXTH = 5 /**< 		@brief 5 */
		};

		const Byte first[6] = { 0x3C, 0, 0, 0, 0, 0 }; /**< 				@brief An array holding all of the possibilities for the first character of the tag*/
		const Byte second[6] = { 0x4D, 0x6D, 0, 0, 0, 0 }; /**< 			@brief An array holding all of the possibilities for the second character of the tag*/
		const Byte third[6] = { 0x45, 0x65, 0, 0, 0, 0 }; /**< 				@brief An array holding all of the possibilities for the third character of the tag*/
		const Byte fourth[6] = { 0x54, 0x74, 0, 0, 0, 0 }; /**< 			@brief An array holding all of the possibilities for the fourth character of the tag*/
		const Byte fifth[6] = { 0x41, 0x61, 0, 0, 0, 0 }; /**< 				@brief An array holding all of the possibilities for the fifth character of the tag*/
		const Byte sixth[6] = { 0x09, 0x0A, 0x0C, 0x0D, 0x20, 0x2F }; /**< 	@brief An array holding all of the possibilities for the sixth character of the tag*/

		/**
		 * @brief Defines array-like access to the struct.
		 * @param idx The index of the array being fetched.
		 * @return Returns the array corresponding to the index.
		 */
		const Byte** operator[](MetaTagSizeT idx) const {
			assert((idx == MetaTagSizeT::FIRST) ||
					(idx == MetaTagSizeT::SECOND) ||
					(idx == MetaTagSizeT::THIRD) ||
					(idx == MetaTagSizeT::FOURTH) ||
					(idx == MetaTagSizeT::FIFTH) ||
					(idx == MetaTagSizeT::SIXTH));
			switch (idx) {
				case FIRST:
					return (const Byte**) (&first);
				case SECOND:
					return (const Byte**) (&second);
				case THIRD:
					return (const Byte**) (&third);
				case FOURTH:
					return (const Byte**) (&fourth);
				case FIFTH:
					return (const Byte**) (&fifth);
				case SIXTH:
					return (const Byte**) (&sixth);
			}
			// Should be impossible for control to reach here.
			return nullptr;
		}
};

/**
 * @brief Compares a byte sequence to a MetaTag object
 * @param lhs The byte sequence being compared
 * @param rhs The MetaTag object being compared
 * @return If the byte sequence matches an possible pattern for a meta tag, then the function returns true.
 * 		   Otherwise, the function returns false.
 */
inline bool operator==(const Byte (&lhs)[6], const MagicString::MetaTag& rhs) {
	for (int i = 0; i < 6; i++) {
		Byte byte = lhs[i];
		Byte reference[6];
		memcpy(reference, rhs[(Parse::MagicString::MetaTag::MetaTagSizeT) i], 6);
		bool equal = false;
		for (int j = 0; j < 6; j++) {
			if (reference[j] == byte) {
				equal = true;
				break;
			}
		}
		if (!equal) {
			return false;
		}
	}
	return true;
}

/**
 * @brief Compares a MetaTag object to a byte sequence
 * @param lhs The MetaTag object being compared
 * @param rhs The byte sequence being compared
 * @return If the byte sequence matches an possible pattern for a meta tag, then the function returns true.
 * 		   Otherwise, the function returns false.
 */
inline bool operator==(const MagicString::MetaTag& lhs, const Byte (&rhs)[6]) {
	return (rhs == lhs);
}

/**
 * @brief Compares a byte sequence to a MetaTag object
 * @param lhs The byte sequence being compared
 * @param rhs The MetaTag object being compared
 * @return If the byte sequence matches an possible pattern for a meta tag, then the function returns false.
 * 		   Otherwise, the function returns true.
 */
inline bool operator!=(const Byte (&lhs)[6], const MagicString::MetaTag& rhs) {
	return !(lhs == rhs);
}
/**
 * @brief Compares a MetaTag object to a byte sequence
 * @param lhs The MetaTag object being compared
 * @param rhs The byte sequence being compared
 * @return If the byte sequence matches an possible pattern for a meta tag, then the function returns false.
 * 		   Otherwise, the function returns true.
 */
inline bool operator!=(const MagicString::MetaTag& lhs, const Byte (&rhs)[6]) {
	return !(lhs == rhs);
}

/**
 * @brief Holds the byte sequences corresponding to an HTML tag starting with an ASCII letter.
 *
 * @test MagicString_Test::TEST_F(ParseHTML_MagicString_ASCIITag_Test, equal)
 * @test MagicString_Test::TEST_F(ParseHTML_MagicString_ASCIITag_Test, almostEqual)
 * @test MagicString_Test::TEST_F(ParseHTML_MagicString_ASCIITag_Test, notEqual)
 */
struct ASCIITag {
		/**
		 * @brief An enum mapping the range of integers [0,1] to symbols.
		 * @details Used so that indexes outside of the array throw type errors.
		 */
		enum ASCIITagSizeT {
			FIRST = 0, /**< 	@brief 0 */
			SECOND = 1 /**< 	@brief 1 */
		};

		const Byte first[1] = { 0x3C }; /**< 	@brief An array holding all of the possibilities for the first character of the tag*/

		/**
		 * @brief Defines array-like access to the struct.
		 * @param idx The index of the array being fetched.
		 * @return Returns the array corresponding to the index.
		 */
		const Byte** operator[](ASCIITagSizeT idx) const {
			assert((idx == ASCIITagSizeT::FIRST) ||
					(idx == ASCIITagSizeT::SECOND));
			switch (idx) {
				case FIRST:
					return (const Byte**) (&first);
				case SECOND:
					return (const Byte**) (&Microsyntaxes::ASCIILetters);
			}
			// Should be impossible for control to reach here.
			return nullptr;
		}
};

/**
 * @brief Compares a byte sequence to a ASCIITag object
 * @param lhs The byte sequence being compared
 * @param rhs The ASCIITag object being compared
 * @return If the byte sequence matches an possible pattern for an ASCII start tag, then the function returns true.
 * 		   Otherwise, the function returns false.
 */
inline bool operator==(const Byte (&lhs)[2], const MagicString::ASCIITag& rhs) {
	{
		Byte byte = lhs[0];
		Byte reference[1];
		memcpy(reference, rhs[(Parse::MagicString::ASCIITag::ASCIITagSizeT) 0], 1);
		if (reference[0] != byte) {
			return false;
		}
	}
	{
		Byte byte = lhs[1];
		Byte reference[52];
		memcpy(reference, rhs[(Parse::MagicString::ASCIITag::ASCIITagSizeT) 1], 52);
		bool equal = false;
		for (int j = 0; j < 52; j++) {
			if (reference[j] == byte) {
				equal = true;
				break;
			}
		}
		if (!equal) {
			return false;
		}
	}
	return true;
}

/**
 * @brief Compares a ASCIITag object to a byte sequence
 * @param lhs The ASCIITag object being compared
 * @param rhs The byte sequence being compared
 * @return If the byte sequence matches an possible pattern for an ASCII start tag, then the function returns true.
 * 		   Otherwise, the function returns false.
 */
inline bool operator==(const MagicString::ASCIITag& lhs, const Byte (&rhs)[2]) {
	return (rhs == lhs);
}

/**
 * @brief Compares a byte sequence to a ASCIITag object
 * @param lhs The byte sequence being compared
 * @param rhs The ASCIITag object being compared
 * @return If the byte sequence matches an possible pattern for an ASCII start tag, then the function returns false.
 * 		   Otherwise, the function returns true.
 */
inline bool operator!=(const Byte (&lhs)[2], const MagicString::ASCIITag& rhs) {
	return !(lhs == rhs);
}

/**
 * @brief Compares a ASCIITag object to a byte sequence
 * @param lhs The ASCIITag object being compared
 * @param rhs The byte sequence being compared
 * @return If the byte sequence matches an possible pattern for an ASCII start tag, then the function returns false.
 * 		   Otherwise, the function returns true.
 */
inline bool operator!=(const MagicString::ASCIITag& lhs, const Byte (&rhs)[2]) {
	return !(lhs == rhs);
}

/**
 * @brief Holds the byte sequences corresponding to an HTML end tag starting with an ASCII letter.
 *
 * @test MagicString_Test::TEST_F(ParseHTML_MagicString_ASCIIEndTag_Test, equal)
 * @test MagicString_Test::TEST_F(ParseHTML_MagicString_ASCIIEndTag_Test, almostEqual)
 * @test MagicString_Test::TEST_F(ParseHTML_MagicString_ASCIIEndTag_Test, notEqual)
 */
struct ASCIIEndTag {
		/**
		 * @brief An enum mapping the range of integers [0,2] to symbols.
		 * @details Used so that indexes outside of the array throw type errors.
		 */
		enum ASCIIEndTagSizeT {
			FIRST = 0, /**< 	@brief 0 */
			SECOND = 1, /**< 	@brief 1 */
			THIRD = 2 /**< 		@brief 2 */
		};

		const Byte first[1] = { 0x3C }; /**< 	@brief An array holding all of the possibilities for the first character of the tag*/
		const Byte second[1] = { 0x4D }; /**< 	@brief An array holding all of the possibilities for the second character of the tag*/

		/**
		 * @brief Defines array-like access to the struct.
		 * @param idx The index of the array being fetched.
		 * @return Returns the array corresponding to the index.
		 */
		const Byte** operator[](ASCIIEndTagSizeT idx) const {
			assert((idx == ASCIIEndTagSizeT::FIRST) ||
					(idx == ASCIIEndTagSizeT::SECOND) ||
					(idx == ASCIIEndTagSizeT::THIRD));
			switch (idx) {
				case FIRST:
					return (const Byte**) (&first);
				case SECOND:
					return (const Byte**) (&second);
				case THIRD:
					return (const Byte**) (&Microsyntaxes::ASCIILetters);
			}
			// Should be impossible for control to reach here.
			return nullptr;
		}
};

/**
 * @brief Compares a byte sequence to a ASCIIEndTag object
 * @param lhs The byte sequence being compared
 * @param rhs The ASCIIEndTag object being compared
 * @return If the byte sequence matches an possible pattern for an ASCII end tag, then the function returns true.
 * 		   Otherwise, the function returns false.
 */
inline bool operator==(const Byte (&lhs)[3], const MagicString::ASCIIEndTag& rhs) {
	{
		Byte byte = lhs[0];
		Byte reference[1];
		memcpy(reference, rhs[(Parse::MagicString::ASCIIEndTag::ASCIIEndTagSizeT) 0], 1);
		if (reference[0] != byte) {
			return false;
		}
	}
	{
		Byte byte = lhs[1];
		Byte reference[1];
		memcpy(reference, rhs[(Parse::MagicString::ASCIIEndTag::ASCIIEndTagSizeT) 1], 1);
		if (reference[0] != byte) {
			return false;
		}
	}
	{
		Byte byte = lhs[2];
		Byte reference[52];
		memcpy(reference, rhs[(Parse::MagicString::ASCIIEndTag::ASCIIEndTagSizeT) 2], 52);
		bool equal = false;
		for (int j = 0; j < 52; j++) {
			if (reference[j] == byte) {
				equal = true;
				break;
			}
		}
		if (!equal) {
			return false;
		}
	}
	return true;
}

/**
 * @brief Compares a ASCIIEndTag object to byte sequence
 * @param lhs The ASCIIEndTag object being compared
 * @param rhs The byte sequence being compared
 * @return If the byte sequence matches an possible pattern for an ASCII end tag, then the function returns true.
 * 		   Otherwise, the function returns false.
 */
inline bool operator==(const MagicString::ASCIIEndTag& lhs, const Byte (&rhs)[3]) {
	return (rhs == lhs);
}

/**
 * @brief Compares a byte sequence to a ASCIIEndTag object
 * @param lhs The byte sequence being compared
 * @param rhs The ASCIIEndTag object being compared
 * @return If the byte sequence matches an possible pattern for an ASCII end tag, then the function returns false.
 * 		   Otherwise, the function returns true.
 */
inline bool operator!=(const Byte (&lhs)[3], const MagicString::ASCIIEndTag& rhs) {
	return !(lhs == rhs);
}

/**
 * @brief Compares a ASCIIEndTag object to byte sequence
 * @param lhs The ASCIIEndTag object being compared
 * @param rhs The byte sequence being compared
 * @return If the byte sequence matches an possible pattern for an ASCII end tag, then the function returns false.
 * 		   Otherwise, the function returns true.
 */
inline bool operator!=(const MagicString::ASCIIEndTag& lhs, const Byte (&rhs)[3]) {
	return !(lhs == rhs);
}

} /* namespace MagicString */
} /* namespace Parse */
} /* namespace HTML */

#endif /* HTML_PARSE_MAGICSTRING_HPP_ */
