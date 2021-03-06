/*******************************************************************************
 * CharacterReference_test.cpp
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
#include <gmock/gmock.h>

#include <stack>
#include <string>

#include <HTML/Parse/Tokenization/Tokenizer.hpp>
#include <HTML/Parse/Tokenization/TokenizationTypes.hpp>

#include <HTML/Parse/TreeConstruction/TreeConstructor.hpp>

#define EXPECT_NO_TOKENS(test_string, expected_position) \
	{ \
		MockTreeConstructor tree_constructor; \
		Tokenizer tokenizer(test_string, 1, DATA, tree_constructor); \
		EXPECT_EQ(0u, tokenizer.consumeCharacterReference()); \
		std::stack<CharacterToken>& stack = tokenizer.getCharTokenStack(); \
		EXPECT_TRUE(stack.empty()); \
		EXPECT_EQ(expected_position, (long) tokenizer.pos); \
	}

#define EXPECT_ONE_CHARACTER_TOKEN(first_character, test_string, expected_position) \
	{ \
		MockTreeConstructor tree_constructor; \
		Tokenizer tokenizer(test_string, 1, DATA, tree_constructor); \
		EXPECT_EQ(1u, tokenizer.consumeCharacterReference()); \
		std::stack<CharacterToken>& stack = tokenizer.getCharTokenStack(); \
		EXPECT_EQ((char32_t) first_character, tokenizer.pop(stack).data); \
		EXPECT_TRUE(stack.empty()); \
		EXPECT_EQ(expected_position, (long) tokenizer.pos); \
	}

#define EXPECT_TWO_CHARACTER_TOKENS(first_character, second_character, test_string, expected_position) \
	{ \
		MockTreeConstructor tree_constructor; \
		Tokenizer tokenizer(test_string, 1, DATA, tree_constructor); \
		EXPECT_EQ(2u, tokenizer.consumeCharacterReference()); \
		std::stack<CharacterToken>& stack = tokenizer.getCharTokenStack(); \
		EXPECT_EQ((char32_t) first_character, tokenizer.pop(stack).data); \
		EXPECT_EQ((char32_t) second_character, tokenizer.pop(stack).data); \
		EXPECT_TRUE(stack.empty()); \
		EXPECT_EQ(expected_position, (long) tokenizer.pos); \
	}

namespace HTML {
namespace Parse {
namespace Tokenization {

class MockTreeConstructor {};

TEST(HTML_Parse_Tokenization_CharacterReference, consumeCharacterReference) {
	EXPECT_NO_TOKENS(U"&\t", 1);
	EXPECT_NO_TOKENS(U"&\n", 1);
	EXPECT_NO_TOKENS(U"&\f", 1);
	EXPECT_NO_TOKENS(U"& ", 1);
	EXPECT_NO_TOKENS(U"&<", 1);
	EXPECT_NO_TOKENS(U"&&", 1);
	EXPECT_NO_TOKENS(U"&\0", 1);
	EXPECT_NO_TOKENS(U"&a", 1);
	EXPECT_NO_TOKENS(U"&#", 1);
	EXPECT_NO_TOKENS(U"&#x", 1);
	EXPECT_NO_TOKENS(U"&#X", 1);

	EXPECT_ONE_CHARACTER_TOKEN(U'\U0000FFFD', U"&#0", 3);
	EXPECT_ONE_CHARACTER_TOKEN(U'\U0000FFFD', U"&#x0", 4);
	EXPECT_ONE_CHARACTER_TOKEN(U'\U0000FFFD', U"&#X0", 4);

	EXPECT_ONE_CHARACTER_TOKEN(U'\U000020AC', U"&#128", 5);
	EXPECT_ONE_CHARACTER_TOKEN(U'\U000020AC', U"&#x80", 5);
	EXPECT_ONE_CHARACTER_TOKEN(U'\U000020AC', U"&#X80", 5);

	EXPECT_ONE_CHARACTER_TOKEN(U'\U0000201A', U"&#130", 5);
	EXPECT_ONE_CHARACTER_TOKEN(U'\U0000201A', U"&#x82", 5);
	EXPECT_ONE_CHARACTER_TOKEN(U'\U0000201A', U"&#X82", 5);

	EXPECT_ONE_CHARACTER_TOKEN(U'\U00000192', U"&#131", 5);
	EXPECT_ONE_CHARACTER_TOKEN(U'\U00000192', U"&#x83", 5);
	EXPECT_ONE_CHARACTER_TOKEN(U'\U00000192', U"&#X83", 5);

	EXPECT_ONE_CHARACTER_TOKEN(U'\U0000201E', U"&#132", 5);
	EXPECT_ONE_CHARACTER_TOKEN(U'\U0000201E', U"&#x84", 5);
	EXPECT_ONE_CHARACTER_TOKEN(U'\U0000201E', U"&#X84", 5);

	EXPECT_ONE_CHARACTER_TOKEN(U'\U00002026', U"&#133", 5);
	EXPECT_ONE_CHARACTER_TOKEN(U'\U00002026', U"&#x85", 5);
	EXPECT_ONE_CHARACTER_TOKEN(U'\U00002026', U"&#X85", 5);

	EXPECT_ONE_CHARACTER_TOKEN(U'\U00002020', U"&#134", 5);
	EXPECT_ONE_CHARACTER_TOKEN(U'\U00002020', U"&#x86", 5);
	EXPECT_ONE_CHARACTER_TOKEN(U'\U00002020', U"&#X86", 5);

	EXPECT_ONE_CHARACTER_TOKEN(U'\U00002021', U"&#135", 5);
	EXPECT_ONE_CHARACTER_TOKEN(U'\U00002021', U"&#x87", 5);
	EXPECT_ONE_CHARACTER_TOKEN(U'\U00002021', U"&#X87", 5);

	EXPECT_ONE_CHARACTER_TOKEN(U'\U000002C6', U"&#136", 5);
	EXPECT_ONE_CHARACTER_TOKEN(U'\U000002C6', U"&#x88", 5);
	EXPECT_ONE_CHARACTER_TOKEN(U'\U000002C6', U"&#X88", 5);

	EXPECT_ONE_CHARACTER_TOKEN(U'\U00002030', U"&#137", 5);
	EXPECT_ONE_CHARACTER_TOKEN(U'\U00002030', U"&#x89", 5);
	EXPECT_ONE_CHARACTER_TOKEN(U'\U00002030', U"&#X89", 5);

	EXPECT_ONE_CHARACTER_TOKEN(U'\U00000160', U"&#138", 5);
	EXPECT_ONE_CHARACTER_TOKEN(U'\U00000160', U"&#x8A", 5);
	EXPECT_ONE_CHARACTER_TOKEN(U'\U00000160', U"&#X8A", 5);

	EXPECT_ONE_CHARACTER_TOKEN(U'\U00002039', U"&#139", 5);
	EXPECT_ONE_CHARACTER_TOKEN(U'\U00002039', U"&#x8B", 5);
	EXPECT_ONE_CHARACTER_TOKEN(U'\U00002039', U"&#X8B", 5);

	EXPECT_ONE_CHARACTER_TOKEN(U'\U00000152', U"&#140", 5);
	EXPECT_ONE_CHARACTER_TOKEN(U'\U00000152', U"&#x8C", 5);
	EXPECT_ONE_CHARACTER_TOKEN(U'\U00000152', U"&#X8C", 5);

	EXPECT_ONE_CHARACTER_TOKEN(U'\U0000017D', U"&#142", 5);
	EXPECT_ONE_CHARACTER_TOKEN(U'\U0000017D', U"&#x8E", 5);
	EXPECT_ONE_CHARACTER_TOKEN(U'\U0000017D', U"&#X8E", 5);

	EXPECT_ONE_CHARACTER_TOKEN(U'\U00002018', U"&#145", 5);
	EXPECT_ONE_CHARACTER_TOKEN(U'\U00002018', U"&#x91", 5);
	EXPECT_ONE_CHARACTER_TOKEN(U'\U00002018', U"&#X91", 5);

	EXPECT_ONE_CHARACTER_TOKEN(U'\U00002019', U"&#146", 5);
	EXPECT_ONE_CHARACTER_TOKEN(U'\U00002019', U"&#x92", 5);
	EXPECT_ONE_CHARACTER_TOKEN(U'\U00002019', U"&#X92", 5);

	EXPECT_ONE_CHARACTER_TOKEN(U'\U0000201C', U"&#147", 5);
	EXPECT_ONE_CHARACTER_TOKEN(U'\U0000201C', U"&#x93", 5);
	EXPECT_ONE_CHARACTER_TOKEN(U'\U0000201C', U"&#X93", 5);

	EXPECT_ONE_CHARACTER_TOKEN(U'\U0000201D', U"&#148", 5);
	EXPECT_ONE_CHARACTER_TOKEN(U'\U0000201D', U"&#x94", 5);
	EXPECT_ONE_CHARACTER_TOKEN(U'\U0000201D', U"&#X94", 5);

	EXPECT_ONE_CHARACTER_TOKEN(U'\U00002022', U"&#149", 5);
	EXPECT_ONE_CHARACTER_TOKEN(U'\U00002022', U"&#x95", 5);
	EXPECT_ONE_CHARACTER_TOKEN(U'\U00002022', U"&#X95", 5);

	EXPECT_ONE_CHARACTER_TOKEN(U'\U00002013', U"&#150", 5);
	EXPECT_ONE_CHARACTER_TOKEN(U'\U00002013', U"&#x96", 5);
	EXPECT_ONE_CHARACTER_TOKEN(U'\U00002013', U"&#X96", 5);

	EXPECT_ONE_CHARACTER_TOKEN(U'\U00002014', U"&#151", 5);
	EXPECT_ONE_CHARACTER_TOKEN(U'\U00002014', U"&#x97", 5);
	EXPECT_ONE_CHARACTER_TOKEN(U'\U00002014', U"&#X97", 5);

	EXPECT_ONE_CHARACTER_TOKEN(U'\U000002DC', U"&#152", 5);
	EXPECT_ONE_CHARACTER_TOKEN(U'\U000002DC', U"&#x98", 5);
	EXPECT_ONE_CHARACTER_TOKEN(U'\U000002DC', U"&#X98", 5);

	EXPECT_ONE_CHARACTER_TOKEN(U'\U00002122', U"&#153", 5);
	EXPECT_ONE_CHARACTER_TOKEN(U'\U00002122', U"&#x99", 5);
	EXPECT_ONE_CHARACTER_TOKEN(U'\U00002122', U"&#X99", 5);

	EXPECT_ONE_CHARACTER_TOKEN(U'\U00000161', U"&#154", 5);
	EXPECT_ONE_CHARACTER_TOKEN(U'\U00000161', U"&#x9A", 5);
	EXPECT_ONE_CHARACTER_TOKEN(U'\U00000161', U"&#X9A", 5);

	EXPECT_ONE_CHARACTER_TOKEN(U'\U0000203A', U"&#155", 5);
	EXPECT_ONE_CHARACTER_TOKEN(U'\U0000203A', U"&#x9B", 5);
	EXPECT_ONE_CHARACTER_TOKEN(U'\U0000203A', U"&#X9B", 5);

	EXPECT_ONE_CHARACTER_TOKEN(U'\U00000153', U"&#156", 5);
	EXPECT_ONE_CHARACTER_TOKEN(U'\U00000153', U"&#x9C", 5);
	EXPECT_ONE_CHARACTER_TOKEN(U'\U00000153', U"&#X9C", 5);

	EXPECT_ONE_CHARACTER_TOKEN(U'\U0000017E', U"&#158", 5);
	EXPECT_ONE_CHARACTER_TOKEN(U'\U0000017E', U"&#x9E", 5);
	EXPECT_ONE_CHARACTER_TOKEN(U'\U0000017E', U"&#X9E", 5);

	EXPECT_ONE_CHARACTER_TOKEN(U'\U00000178', U"&#159", 5);
	EXPECT_ONE_CHARACTER_TOKEN(U'\U00000178', U"&#x9F", 5);
	EXPECT_ONE_CHARACTER_TOKEN(U'\U00000178', U"&#X9F", 5);

	EXPECT_ONE_CHARACTER_TOKEN(U'\U0000FFFD', U"&#55296", 7);
	EXPECT_ONE_CHARACTER_TOKEN(U'\U0000FFFD', U"&#xD800", 7);
	EXPECT_ONE_CHARACTER_TOKEN(U'\U0000FFFD', U"&#XD800", 7);

	EXPECT_ONE_CHARACTER_TOKEN(U'\U0000FFFD', U"&#57343", 7);
	EXPECT_ONE_CHARACTER_TOKEN(U'\U0000FFFD', U"&#xDFFF", 7);
	EXPECT_ONE_CHARACTER_TOKEN(U'\U0000FFFD', U"&#XDFFF", 7);

	EXPECT_ONE_CHARACTER_TOKEN(U'\U0000FFFD', U"&#57343", 7);
	EXPECT_ONE_CHARACTER_TOKEN(U'\U0000FFFD', U"&#xDFFF", 7);
	EXPECT_ONE_CHARACTER_TOKEN(U'\U0000FFFD', U"&#XDFFF", 7);

	EXPECT_ONE_CHARACTER_TOKEN(U'\U0000FFFD', U"&#1114112", 9);
	EXPECT_ONE_CHARACTER_TOKEN(U'\U0000FFFD', U"&#x110000", 9);
	EXPECT_ONE_CHARACTER_TOKEN(U'\U0000FFFD', U"&#X110000", 9);

	EXPECT_NO_TOKENS(U"&#1", 3);
	EXPECT_NO_TOKENS(U"&#x1", 4);
	EXPECT_NO_TOKENS(U"&#X1", 4);

	EXPECT_NO_TOKENS(U"&#2", 3);
	EXPECT_NO_TOKENS(U"&#x2", 4);
	EXPECT_NO_TOKENS(U"&#X2", 4);

	EXPECT_NO_TOKENS(U"&#3", 3);
	EXPECT_NO_TOKENS(U"&#x3", 4);
	EXPECT_NO_TOKENS(U"&#X3", 4);

	EXPECT_NO_TOKENS(U"&#4", 3);
	EXPECT_NO_TOKENS(U"&#x4", 4);
	EXPECT_NO_TOKENS(U"&#X4", 4);

	EXPECT_NO_TOKENS(U"&#5", 3);
	EXPECT_NO_TOKENS(U"&#x5", 4);
	EXPECT_NO_TOKENS(U"&#X5", 4);

	EXPECT_NO_TOKENS(U"&#6", 3);
	EXPECT_NO_TOKENS(U"&#x6", 4);
	EXPECT_NO_TOKENS(U"&#X6", 4);

	EXPECT_NO_TOKENS(U"&#7", 3);
	EXPECT_NO_TOKENS(U"&#x7", 4);
	EXPECT_NO_TOKENS(U"&#X7", 4);

	EXPECT_NO_TOKENS(U"&#8", 3);
	EXPECT_NO_TOKENS(U"&#x8", 4);
	EXPECT_NO_TOKENS(U"&#X8", 4);

	EXPECT_NO_TOKENS(U"&#13", 4);
	EXPECT_NO_TOKENS(U"&#xD", 4);
	EXPECT_NO_TOKENS(U"&#XD", 4);

	EXPECT_NO_TOKENS(U"&#14", 4);
	EXPECT_NO_TOKENS(U"&#xE", 4);
	EXPECT_NO_TOKENS(U"&#XE", 4);

	EXPECT_NO_TOKENS(U"&#15", 4);
	EXPECT_NO_TOKENS(U"&#xF", 4);
	EXPECT_NO_TOKENS(U"&#XF", 4);

	EXPECT_NO_TOKENS(U"&#16", 4);
	EXPECT_NO_TOKENS(U"&#x10", 5);
	EXPECT_NO_TOKENS(U"&#X10", 5);

	EXPECT_NO_TOKENS(U"&#17", 4);
	EXPECT_NO_TOKENS(U"&#x11", 5);
	EXPECT_NO_TOKENS(U"&#X11", 5);

	EXPECT_NO_TOKENS(U"&#18", 4);
	EXPECT_NO_TOKENS(U"&#x12", 5);
	EXPECT_NO_TOKENS(U"&#X12", 5);

	EXPECT_NO_TOKENS(U"&#19", 4);
	EXPECT_NO_TOKENS(U"&#x13", 5);
	EXPECT_NO_TOKENS(U"&#X13", 5);

	EXPECT_NO_TOKENS(U"&#20", 4);
	EXPECT_NO_TOKENS(U"&#x14", 5);
	EXPECT_NO_TOKENS(U"&#X14", 5);

	EXPECT_NO_TOKENS(U"&#21", 4);
	EXPECT_NO_TOKENS(U"&#x15", 5);
	EXPECT_NO_TOKENS(U"&#X15", 5);

	EXPECT_NO_TOKENS(U"&#22", 4);
	EXPECT_NO_TOKENS(U"&#x16", 5);
	EXPECT_NO_TOKENS(U"&#X16", 5);

	EXPECT_NO_TOKENS(U"&#23", 4);
	EXPECT_NO_TOKENS(U"&#x17", 5);
	EXPECT_NO_TOKENS(U"&#X17", 5);

	EXPECT_NO_TOKENS(U"&#24", 4);
	EXPECT_NO_TOKENS(U"&#x18", 5);
	EXPECT_NO_TOKENS(U"&#X18", 5);

	EXPECT_NO_TOKENS(U"&#25", 4);
	EXPECT_NO_TOKENS(U"&#x19", 5);
	EXPECT_NO_TOKENS(U"&#X19", 5);

	EXPECT_NO_TOKENS(U"&#26", 4);
	EXPECT_NO_TOKENS(U"&#x1A", 5);
	EXPECT_NO_TOKENS(U"&#X1A", 5);

	EXPECT_NO_TOKENS(U"&#27", 4);
	EXPECT_NO_TOKENS(U"&#x1B", 5);
	EXPECT_NO_TOKENS(U"&#X1B", 5);

	EXPECT_NO_TOKENS(U"&#28", 4);
	EXPECT_NO_TOKENS(U"&#x1C", 5);
	EXPECT_NO_TOKENS(U"&#X1C", 5);

	EXPECT_NO_TOKENS(U"&#29", 4);
	EXPECT_NO_TOKENS(U"&#x1D", 5);
	EXPECT_NO_TOKENS(U"&#X1D", 5);

	EXPECT_NO_TOKENS(U"&#30", 4);
	EXPECT_NO_TOKENS(U"&#x1E", 5);
	EXPECT_NO_TOKENS(U"&#X1E", 5);

	EXPECT_NO_TOKENS(U"&#31", 4);
	EXPECT_NO_TOKENS(U"&#x1F", 5);
	EXPECT_NO_TOKENS(U"&#X1F", 5);

	EXPECT_NO_TOKENS(U"&#127", 5);
	EXPECT_NO_TOKENS(U"&#x7F", 5);
	EXPECT_NO_TOKENS(U"&#X7F", 5);

	EXPECT_NO_TOKENS(U"&#64976", 7);
	EXPECT_NO_TOKENS(U"&#xFDD0", 7);
	EXPECT_NO_TOKENS(U"&#XFDD0", 7);

	EXPECT_NO_TOKENS(U"&#65007", 7);
	EXPECT_NO_TOKENS(U"&#xFDEF", 7);
	EXPECT_NO_TOKENS(U"&#XFDEF", 7);

	EXPECT_NO_TOKENS(U"&#11", 4);
	EXPECT_NO_TOKENS(U"&#xB", 4);
	EXPECT_NO_TOKENS(U"&#XB", 4);

	EXPECT_NO_TOKENS(U"&#65534", 7);
	EXPECT_NO_TOKENS(U"&#xFFFE", 7);
	EXPECT_NO_TOKENS(U"&#XFFFE", 7);

	EXPECT_NO_TOKENS(U"&#65535", 7);
	EXPECT_NO_TOKENS(U"&#xFFFF", 7);
	EXPECT_NO_TOKENS(U"&#XFFFF", 7);

	EXPECT_NO_TOKENS(U"&#131070", 8);
	EXPECT_NO_TOKENS(U"&#x1FFFE", 8);
	EXPECT_NO_TOKENS(U"&#X1FFFE", 8);

	EXPECT_NO_TOKENS(U"&#131071", 8);
	EXPECT_NO_TOKENS(U"&#x1FFFF", 8);
	EXPECT_NO_TOKENS(U"&#X1FFFF", 8);

	EXPECT_NO_TOKENS(U"&#196606", 8);
	EXPECT_NO_TOKENS(U"&#x2FFFE", 8);
	EXPECT_NO_TOKENS(U"&#X2FFFE", 8);

	EXPECT_NO_TOKENS(U"&#196607", 8);
	EXPECT_NO_TOKENS(U"&#x2FFFF", 8);
	EXPECT_NO_TOKENS(U"&#X2FFFF", 8);

	EXPECT_NO_TOKENS(U"&#262142", 8);
	EXPECT_NO_TOKENS(U"&#x3FFFE", 8);
	EXPECT_NO_TOKENS(U"&#X3FFFE", 8);

	EXPECT_NO_TOKENS(U"&#262143", 8);
	EXPECT_NO_TOKENS(U"&#x3FFFF", 8);
	EXPECT_NO_TOKENS(U"&#X3FFFF", 8);

	EXPECT_NO_TOKENS(U"&#327678", 8);
	EXPECT_NO_TOKENS(U"&#x4FFFE", 8);
	EXPECT_NO_TOKENS(U"&#X4FFFE", 8);

	EXPECT_NO_TOKENS(U"&#327679", 8);
	EXPECT_NO_TOKENS(U"&#x4FFFF", 8);
	EXPECT_NO_TOKENS(U"&#X4FFFF", 8);

	EXPECT_NO_TOKENS(U"&#393214", 8);
	EXPECT_NO_TOKENS(U"&#x5FFFE", 8);
	EXPECT_NO_TOKENS(U"&#X5FFFE", 8);

	EXPECT_NO_TOKENS(U"&#393215", 8);
	EXPECT_NO_TOKENS(U"&#x5FFFF", 8);
	EXPECT_NO_TOKENS(U"&#X5FFFF", 8);

	EXPECT_NO_TOKENS(U"&#458750", 8);
	EXPECT_NO_TOKENS(U"&#x6FFFE", 8);
	EXPECT_NO_TOKENS(U"&#X6FFFE", 8);

	EXPECT_NO_TOKENS(U"&#458751", 8);
	EXPECT_NO_TOKENS(U"&#x6FFFF", 8);
	EXPECT_NO_TOKENS(U"&#X6FFFF", 8);

	EXPECT_NO_TOKENS(U"&#524286", 8);
	EXPECT_NO_TOKENS(U"&#x7FFFE", 8);
	EXPECT_NO_TOKENS(U"&#X7FFFE", 8);

	EXPECT_NO_TOKENS(U"&#524287", 8);
	EXPECT_NO_TOKENS(U"&#x7FFFF", 8);
	EXPECT_NO_TOKENS(U"&#X7FFFF", 8);

	EXPECT_NO_TOKENS(U"&#589822", 8);
	EXPECT_NO_TOKENS(U"&#x8FFFE", 8);
	EXPECT_NO_TOKENS(U"&#X8FFFE", 8);

	EXPECT_NO_TOKENS(U"&#589823", 8);
	EXPECT_NO_TOKENS(U"&#x8FFFF", 8);
	EXPECT_NO_TOKENS(U"&#X8FFFF", 8);

	EXPECT_NO_TOKENS(U"&#655358", 8);
	EXPECT_NO_TOKENS(U"&#x9FFFE", 8);
	EXPECT_NO_TOKENS(U"&#X9FFFE", 8);

	EXPECT_NO_TOKENS(U"&#655359", 8);
	EXPECT_NO_TOKENS(U"&#x9FFFF", 8);
	EXPECT_NO_TOKENS(U"&#X9FFFF", 8);

	EXPECT_NO_TOKENS(U"&#720894", 8);
	EXPECT_NO_TOKENS(U"&#xAFFFE", 8);
	EXPECT_NO_TOKENS(U"&#XAFFFE", 8);

	EXPECT_NO_TOKENS(U"&#720895", 8);
	EXPECT_NO_TOKENS(U"&#xAFFFF", 8);
	EXPECT_NO_TOKENS(U"&#XAFFFF", 8);

	EXPECT_NO_TOKENS(U"&#786430", 8);
	EXPECT_NO_TOKENS(U"&#xBFFFE", 8);
	EXPECT_NO_TOKENS(U"&#XBFFFE", 8);

	EXPECT_NO_TOKENS(U"&#786431", 8);
	EXPECT_NO_TOKENS(U"&#xBFFFF", 8);
	EXPECT_NO_TOKENS(U"&#XBFFFF", 8);

	EXPECT_NO_TOKENS(U"&#851966", 8);
	EXPECT_NO_TOKENS(U"&#xCFFFE", 8);
	EXPECT_NO_TOKENS(U"&#XCFFFE", 8);

	EXPECT_NO_TOKENS(U"&#851967", 8);
	EXPECT_NO_TOKENS(U"&#xCFFFF", 8);
	EXPECT_NO_TOKENS(U"&#XCFFFF", 8);

	EXPECT_NO_TOKENS(U"&#917502", 8);
	EXPECT_NO_TOKENS(U"&#xDFFFE", 8);
	EXPECT_NO_TOKENS(U"&#XDFFFE", 8);

	EXPECT_NO_TOKENS(U"&#917503", 8);
	EXPECT_NO_TOKENS(U"&#xDFFFF", 8);
	EXPECT_NO_TOKENS(U"&#XDFFFF", 8);

	EXPECT_NO_TOKENS(U"&#983038", 8);
	EXPECT_NO_TOKENS(U"&#xEFFFE", 8);
	EXPECT_NO_TOKENS(U"&#XEFFFE", 8);

	EXPECT_NO_TOKENS(U"&#983039", 8);
	EXPECT_NO_TOKENS(U"&#xEFFFF", 8);
	EXPECT_NO_TOKENS(U"&#XEFFFF", 8);

	EXPECT_NO_TOKENS(U"&#1048574", 9);
	EXPECT_NO_TOKENS(U"&#xFFFFE", 8);
	EXPECT_NO_TOKENS(U"&#XFFFFE", 8);

	EXPECT_NO_TOKENS(U"&#1048575", 9);
	EXPECT_NO_TOKENS(U"&#xFFFFF", 8);
	EXPECT_NO_TOKENS(U"&#XFFFFF", 8);

	EXPECT_NO_TOKENS(U"&#1114110", 9);
	EXPECT_NO_TOKENS(U"&#x10FFFE", 9);
	EXPECT_NO_TOKENS(U"&#X10FFFE", 9);

	EXPECT_NO_TOKENS(U"&#1114111", 9);
	EXPECT_NO_TOKENS(U"&#x10FFFF", 9);
	EXPECT_NO_TOKENS(U"&#X10FFFF", 9);

	EXPECT_ONE_CHARACTER_TOKEN(U'\U000000C1', U"&Aacute", 7);
	EXPECT_ONE_CHARACTER_TOKEN(U'\U000000C1', U"&Aacute;", 8);
	EXPECT_TWO_CHARACTER_TOKENS(U'\U0000223E', U'\U00000333', U"&acE;", 5);
	EXPECT_ONE_CHARACTER_TOKEN(U'\U00002233', U"&CounterClockwiseContourIntegral;", 33);
	EXPECT_ONE_CHARACTER_TOKEN(U'\U00002063', U"&ic;", 4);

}

} /* namespace Tokenization */
} /* namespace Parse */
} /* namespace HTML */

