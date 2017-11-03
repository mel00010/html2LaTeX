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

#include <list>
#include <string>

#include <HTML/Parse/Tokenization/CharacterReference.hpp>
#include <HTML/Parse/Tokenization/TokenizationTypes.hpp>
#include <HTML/Parse/Tokenization/TokenizationMisc.hpp>

#define EXPECT_NULL_TOKEN(test_string, expected_position) \
	{ \
		StateData test; \
		EXPECT_EQ(Token(), consumeCharacterReference(test = StateData { STATES::DATA, test_string})); \
		EXPECT_EQ(expected_position, (long) test.pos); \
	}
#define EXPECT_CHARACTER_TOKEN(first_character, second_character, test_string, expected_position) \
	{ \
		StateData test; \
		Token token = Token {TokenType::CHARACTER, CharacterToken {first_character, (char32_t) second_character}}; \
		EXPECT_EQ(token, consumeCharacterReference(test = StateData { STATES::DATA, test_string})); \
		EXPECT_EQ(expected_position, (long) test.pos); \
	}

namespace HTML {
namespace Parse {
namespace Tokenization {

TEST(HTML_Parse_Tokenization_CharacterReference, consumeCharacterReference) {
	StateData test;
	EXPECT_NULL_TOKEN(U"&\t", 0);
	EXPECT_NULL_TOKEN(U"&\n", 0);
	EXPECT_NULL_TOKEN(U"&\f", 0);
	EXPECT_NULL_TOKEN(U"& ", 0);
	EXPECT_NULL_TOKEN(U"&<", 0);
	EXPECT_NULL_TOKEN(U"&&", 0);
	EXPECT_NULL_TOKEN(U"&\0", 0);
	EXPECT_NULL_TOKEN(U"&a", 0);
	EXPECT_NULL_TOKEN(U"&#", 0);
	EXPECT_NULL_TOKEN(U"&#x", 0);
	EXPECT_NULL_TOKEN(U"&#X", 0);

	EXPECT_CHARACTER_TOKEN(U'\U0000FFFD', EOF, U"&#0", 3);
	EXPECT_CHARACTER_TOKEN(U'\U0000FFFD', EOF, U"&#x0", 4);
	EXPECT_CHARACTER_TOKEN(U'\U0000FFFD', EOF, U"&#X0", 4);

	EXPECT_CHARACTER_TOKEN(U'\U000020AC', EOF, U"&#128", 5);
	EXPECT_CHARACTER_TOKEN(U'\U000020AC', EOF, U"&#x80", 5);
	EXPECT_CHARACTER_TOKEN(U'\U000020AC', EOF, U"&#X80", 5);

	EXPECT_CHARACTER_TOKEN(U'\U0000201A', EOF, U"&#130", 5);
	EXPECT_CHARACTER_TOKEN(U'\U0000201A', EOF, U"&#x82", 5);
	EXPECT_CHARACTER_TOKEN(U'\U0000201A', EOF, U"&#X82", 5);

	EXPECT_CHARACTER_TOKEN(U'\U00000192', EOF, U"&#131", 5);
	EXPECT_CHARACTER_TOKEN(U'\U00000192', EOF, U"&#x83", 5);
	EXPECT_CHARACTER_TOKEN(U'\U00000192', EOF, U"&#X83", 5);

	EXPECT_CHARACTER_TOKEN(U'\U0000201E', EOF, U"&#132", 5);
	EXPECT_CHARACTER_TOKEN(U'\U0000201E', EOF, U"&#x84", 5);
	EXPECT_CHARACTER_TOKEN(U'\U0000201E', EOF, U"&#X84", 5);

	EXPECT_CHARACTER_TOKEN(U'\U00002026', EOF, U"&#133", 5);
	EXPECT_CHARACTER_TOKEN(U'\U00002026', EOF, U"&#x85", 5);
	EXPECT_CHARACTER_TOKEN(U'\U00002026', EOF, U"&#X85", 5);

	EXPECT_CHARACTER_TOKEN(U'\U00002020', EOF, U"&#134", 5);
	EXPECT_CHARACTER_TOKEN(U'\U00002020', EOF, U"&#x86", 5);
	EXPECT_CHARACTER_TOKEN(U'\U00002020', EOF, U"&#X86", 5);

	EXPECT_CHARACTER_TOKEN(U'\U00002021', EOF, U"&#135", 5);
	EXPECT_CHARACTER_TOKEN(U'\U00002021', EOF, U"&#x87", 5);
	EXPECT_CHARACTER_TOKEN(U'\U00002021', EOF, U"&#X87", 5);

	EXPECT_CHARACTER_TOKEN(U'\U000002C6', EOF, U"&#136", 5);
	EXPECT_CHARACTER_TOKEN(U'\U000002C6', EOF, U"&#x88", 5);
	EXPECT_CHARACTER_TOKEN(U'\U000002C6', EOF, U"&#X88", 5);

	EXPECT_CHARACTER_TOKEN(U'\U00002030', EOF, U"&#137", 5);
	EXPECT_CHARACTER_TOKEN(U'\U00002030', EOF, U"&#x89", 5);
	EXPECT_CHARACTER_TOKEN(U'\U00002030', EOF, U"&#X89", 5);

	EXPECT_CHARACTER_TOKEN(U'\U00000160', EOF, U"&#138", 5);
	EXPECT_CHARACTER_TOKEN(U'\U00000160', EOF, U"&#x8A", 5);
	EXPECT_CHARACTER_TOKEN(U'\U00000160', EOF, U"&#X8A", 5);

	EXPECT_CHARACTER_TOKEN(U'\U00002039', EOF, U"&#139", 5);
	EXPECT_CHARACTER_TOKEN(U'\U00002039', EOF, U"&#x8B", 5);
	EXPECT_CHARACTER_TOKEN(U'\U00002039', EOF, U"&#X8B", 5);

	EXPECT_CHARACTER_TOKEN(U'\U00000152', EOF, U"&#140", 5);
	EXPECT_CHARACTER_TOKEN(U'\U00000152', EOF, U"&#x8C", 5);
	EXPECT_CHARACTER_TOKEN(U'\U00000152', EOF, U"&#X8C", 5);

	EXPECT_CHARACTER_TOKEN(U'\U0000017D', EOF, U"&#142", 5);
	EXPECT_CHARACTER_TOKEN(U'\U0000017D', EOF, U"&#x8E", 5);
	EXPECT_CHARACTER_TOKEN(U'\U0000017D', EOF, U"&#X8E", 5);

	EXPECT_CHARACTER_TOKEN(U'\U00002018', EOF, U"&#145", 5);
	EXPECT_CHARACTER_TOKEN(U'\U00002018', EOF, U"&#x91", 5);
	EXPECT_CHARACTER_TOKEN(U'\U00002018', EOF, U"&#X91", 5);

	EXPECT_CHARACTER_TOKEN(U'\U00002019', EOF, U"&#146", 5);
	EXPECT_CHARACTER_TOKEN(U'\U00002019', EOF, U"&#x92", 5);
	EXPECT_CHARACTER_TOKEN(U'\U00002019', EOF, U"&#X92", 5);

	EXPECT_CHARACTER_TOKEN(U'\U0000201C', EOF, U"&#147", 5);
	EXPECT_CHARACTER_TOKEN(U'\U0000201C', EOF, U"&#x93", 5);
	EXPECT_CHARACTER_TOKEN(U'\U0000201C', EOF, U"&#X93", 5);

	EXPECT_CHARACTER_TOKEN(U'\U0000201D', EOF, U"&#148", 5);
	EXPECT_CHARACTER_TOKEN(U'\U0000201D', EOF, U"&#x94", 5);
	EXPECT_CHARACTER_TOKEN(U'\U0000201D', EOF, U"&#X94", 5);

	EXPECT_CHARACTER_TOKEN(U'\U00002022', EOF, U"&#149", 5);
	EXPECT_CHARACTER_TOKEN(U'\U00002022', EOF, U"&#x95", 5);
	EXPECT_CHARACTER_TOKEN(U'\U00002022', EOF, U"&#X95", 5);

	EXPECT_CHARACTER_TOKEN(U'\U00002013', EOF, U"&#150", 5);
	EXPECT_CHARACTER_TOKEN(U'\U00002013', EOF, U"&#x96", 5);
	EXPECT_CHARACTER_TOKEN(U'\U00002013', EOF, U"&#X96", 5);

	EXPECT_CHARACTER_TOKEN(U'\U00002014', EOF, U"&#151", 5);
	EXPECT_CHARACTER_TOKEN(U'\U00002014', EOF, U"&#x97", 5);
	EXPECT_CHARACTER_TOKEN(U'\U00002014', EOF, U"&#X97", 5);

	EXPECT_CHARACTER_TOKEN(U'\U000002DC', EOF, U"&#152", 5);
	EXPECT_CHARACTER_TOKEN(U'\U000002DC', EOF, U"&#x98", 5);
	EXPECT_CHARACTER_TOKEN(U'\U000002DC', EOF, U"&#X98", 5);

	EXPECT_CHARACTER_TOKEN(U'\U00002122', EOF, U"&#153", 5);
	EXPECT_CHARACTER_TOKEN(U'\U00002122', EOF, U"&#x99", 5);
	EXPECT_CHARACTER_TOKEN(U'\U00002122', EOF, U"&#X99", 5);

	EXPECT_CHARACTER_TOKEN(U'\U00000161', EOF, U"&#154", 5);
	EXPECT_CHARACTER_TOKEN(U'\U00000161', EOF, U"&#x9A", 5);
	EXPECT_CHARACTER_TOKEN(U'\U00000161', EOF, U"&#X9A", 5);

	EXPECT_CHARACTER_TOKEN(U'\U0000203A', EOF, U"&#155", 5);
	EXPECT_CHARACTER_TOKEN(U'\U0000203A', EOF, U"&#x9B", 5);
	EXPECT_CHARACTER_TOKEN(U'\U0000203A', EOF, U"&#X9B", 5);

	EXPECT_CHARACTER_TOKEN(U'\U00000153', EOF, U"&#156", 5);
	EXPECT_CHARACTER_TOKEN(U'\U00000153', EOF, U"&#x9C", 5);
	EXPECT_CHARACTER_TOKEN(U'\U00000153', EOF, U"&#X9C", 5);

	EXPECT_CHARACTER_TOKEN(U'\U0000017E', EOF, U"&#158", 5);
	EXPECT_CHARACTER_TOKEN(U'\U0000017E', EOF, U"&#x9E", 5);
	EXPECT_CHARACTER_TOKEN(U'\U0000017E', EOF, U"&#X9E", 5);

	EXPECT_CHARACTER_TOKEN(U'\U00000178', EOF, U"&#159", 5);
	EXPECT_CHARACTER_TOKEN(U'\U00000178', EOF, U"&#x9F", 5);
	EXPECT_CHARACTER_TOKEN(U'\U00000178', EOF, U"&#X9F", 5);

	EXPECT_CHARACTER_TOKEN(U'\U0000FFFD', EOF, U"&#55296", 7);
	EXPECT_CHARACTER_TOKEN(U'\U0000FFFD', EOF, U"&#xD800", 7);
	EXPECT_CHARACTER_TOKEN(U'\U0000FFFD', EOF, U"&#XD800", 7);

	EXPECT_CHARACTER_TOKEN(U'\U0000FFFD', EOF, U"&#57343", 7);
	EXPECT_CHARACTER_TOKEN(U'\U0000FFFD', EOF, U"&#xDFFF", 7);
	EXPECT_CHARACTER_TOKEN(U'\U0000FFFD', EOF, U"&#XDFFF", 7);

	EXPECT_CHARACTER_TOKEN(U'\U0000FFFD', EOF, U"&#57343", 7);
	EXPECT_CHARACTER_TOKEN(U'\U0000FFFD', EOF, U"&#xDFFF", 7);
	EXPECT_CHARACTER_TOKEN(U'\U0000FFFD', EOF, U"&#XDFFF", 7);

	EXPECT_CHARACTER_TOKEN(U'\U0000FFFD', EOF, U"&#1114112", 9);
	EXPECT_CHARACTER_TOKEN(U'\U0000FFFD', EOF, U"&#x110000", 9);
	EXPECT_CHARACTER_TOKEN(U'\U0000FFFD', EOF, U"&#X110000", 9);

	EXPECT_NULL_TOKEN(U"&#1", 3);
	EXPECT_NULL_TOKEN(U"&#x1", 4);
	EXPECT_NULL_TOKEN(U"&#X1", 4);

	EXPECT_NULL_TOKEN(U"&#2", 3);
	EXPECT_NULL_TOKEN(U"&#x2", 4);
	EXPECT_NULL_TOKEN(U"&#X2", 4);

	EXPECT_NULL_TOKEN(U"&#3", 3);
	EXPECT_NULL_TOKEN(U"&#x3", 4);
	EXPECT_NULL_TOKEN(U"&#X3", 4);

	EXPECT_NULL_TOKEN(U"&#4", 3);
	EXPECT_NULL_TOKEN(U"&#x4", 4);
	EXPECT_NULL_TOKEN(U"&#X4", 4);

	EXPECT_NULL_TOKEN(U"&#5", 3);
	EXPECT_NULL_TOKEN(U"&#x5", 4);
	EXPECT_NULL_TOKEN(U"&#X5", 4);

	EXPECT_NULL_TOKEN(U"&#6", 3);
	EXPECT_NULL_TOKEN(U"&#x6", 4);
	EXPECT_NULL_TOKEN(U"&#X6", 4);

	EXPECT_NULL_TOKEN(U"&#7", 3);
	EXPECT_NULL_TOKEN(U"&#x7", 4);
	EXPECT_NULL_TOKEN(U"&#X7", 4);

	EXPECT_NULL_TOKEN(U"&#8", 3);
	EXPECT_NULL_TOKEN(U"&#x8", 4);
	EXPECT_NULL_TOKEN(U"&#X8", 4);

	EXPECT_NULL_TOKEN(U"&#13", 4);
	EXPECT_NULL_TOKEN(U"&#xD", 4);
	EXPECT_NULL_TOKEN(U"&#XD", 4);

	EXPECT_NULL_TOKEN(U"&#14", 4);
	EXPECT_NULL_TOKEN(U"&#xE", 4);
	EXPECT_NULL_TOKEN(U"&#XE", 4);

	EXPECT_NULL_TOKEN(U"&#15", 4);
	EXPECT_NULL_TOKEN(U"&#xF", 4);
	EXPECT_NULL_TOKEN(U"&#XF", 4);

	EXPECT_NULL_TOKEN(U"&#16", 4);
	EXPECT_NULL_TOKEN(U"&#x10", 5);
	EXPECT_NULL_TOKEN(U"&#X10", 5);

	EXPECT_NULL_TOKEN(U"&#17", 4);
	EXPECT_NULL_TOKEN(U"&#x11", 5);
	EXPECT_NULL_TOKEN(U"&#X11", 5);

	EXPECT_NULL_TOKEN(U"&#18", 4);
	EXPECT_NULL_TOKEN(U"&#x12", 5);
	EXPECT_NULL_TOKEN(U"&#X12", 5);

	EXPECT_NULL_TOKEN(U"&#19", 4);
	EXPECT_NULL_TOKEN(U"&#x13", 5);
	EXPECT_NULL_TOKEN(U"&#X13", 5);

	EXPECT_NULL_TOKEN(U"&#20", 4);
	EXPECT_NULL_TOKEN(U"&#x14", 5);
	EXPECT_NULL_TOKEN(U"&#X14", 5);

	EXPECT_NULL_TOKEN(U"&#21", 4);
	EXPECT_NULL_TOKEN(U"&#x15", 5);
	EXPECT_NULL_TOKEN(U"&#X15", 5);

	EXPECT_NULL_TOKEN(U"&#22", 4);
	EXPECT_NULL_TOKEN(U"&#x16", 5);
	EXPECT_NULL_TOKEN(U"&#X16", 5);

	EXPECT_NULL_TOKEN(U"&#23", 4);
	EXPECT_NULL_TOKEN(U"&#x17", 5);
	EXPECT_NULL_TOKEN(U"&#X17", 5);

	EXPECT_NULL_TOKEN(U"&#24", 4);
	EXPECT_NULL_TOKEN(U"&#x18", 5);
	EXPECT_NULL_TOKEN(U"&#X18", 5);

	EXPECT_NULL_TOKEN(U"&#25", 4);
	EXPECT_NULL_TOKEN(U"&#x19", 5);
	EXPECT_NULL_TOKEN(U"&#X19", 5);

	EXPECT_NULL_TOKEN(U"&#26", 4);
	EXPECT_NULL_TOKEN(U"&#x1A", 5);
	EXPECT_NULL_TOKEN(U"&#X1A", 5);

	EXPECT_NULL_TOKEN(U"&#27", 4);
	EXPECT_NULL_TOKEN(U"&#x1B", 5);
	EXPECT_NULL_TOKEN(U"&#X1B", 5);

	EXPECT_NULL_TOKEN(U"&#28", 4);
	EXPECT_NULL_TOKEN(U"&#x1C", 5);
	EXPECT_NULL_TOKEN(U"&#X1C", 5);

	EXPECT_NULL_TOKEN(U"&#29", 4);
	EXPECT_NULL_TOKEN(U"&#x1D", 5);
	EXPECT_NULL_TOKEN(U"&#X1D", 5);

	EXPECT_NULL_TOKEN(U"&#30", 4);
	EXPECT_NULL_TOKEN(U"&#x1E", 5);
	EXPECT_NULL_TOKEN(U"&#X1E", 5);

	EXPECT_NULL_TOKEN(U"&#31", 4);
	EXPECT_NULL_TOKEN(U"&#x1F", 5);
	EXPECT_NULL_TOKEN(U"&#X1F", 5);

	EXPECT_NULL_TOKEN(U"&#127", 5);
	EXPECT_NULL_TOKEN(U"&#x7F", 5);
	EXPECT_NULL_TOKEN(U"&#X7F", 5);

	EXPECT_NULL_TOKEN(U"&#64976", 7);
	EXPECT_NULL_TOKEN(U"&#xFDD0", 7);
	EXPECT_NULL_TOKEN(U"&#XFDD0", 7);

	EXPECT_NULL_TOKEN(U"&#65007", 7);
	EXPECT_NULL_TOKEN(U"&#xFDEF", 7);
	EXPECT_NULL_TOKEN(U"&#XFDEF", 7);

	EXPECT_NULL_TOKEN(U"&#11", 4);
	EXPECT_NULL_TOKEN(U"&#xB", 4);
	EXPECT_NULL_TOKEN(U"&#XB", 4);

	EXPECT_NULL_TOKEN(U"&#65534", 7);
	EXPECT_NULL_TOKEN(U"&#xFFFE", 7);
	EXPECT_NULL_TOKEN(U"&#XFFFE", 7);

	EXPECT_NULL_TOKEN(U"&#65535", 7);
	EXPECT_NULL_TOKEN(U"&#xFFFF", 7);
	EXPECT_NULL_TOKEN(U"&#XFFFF", 7);

	EXPECT_NULL_TOKEN(U"&#131070", 8);
	EXPECT_NULL_TOKEN(U"&#x1FFFE", 8);
	EXPECT_NULL_TOKEN(U"&#X1FFFE", 8);

	EXPECT_NULL_TOKEN(U"&#131071", 8);
	EXPECT_NULL_TOKEN(U"&#x1FFFF", 8);
	EXPECT_NULL_TOKEN(U"&#X1FFFF", 8);

	EXPECT_NULL_TOKEN(U"&#196606", 8);
	EXPECT_NULL_TOKEN(U"&#x2FFFE", 8);
	EXPECT_NULL_TOKEN(U"&#X2FFFE", 8);

	EXPECT_NULL_TOKEN(U"&#196607", 8);
	EXPECT_NULL_TOKEN(U"&#x2FFFF", 8);
	EXPECT_NULL_TOKEN(U"&#X2FFFF", 8);

	EXPECT_NULL_TOKEN(U"&#262142", 8);
	EXPECT_NULL_TOKEN(U"&#x3FFFE", 8);
	EXPECT_NULL_TOKEN(U"&#X3FFFE", 8);

	EXPECT_NULL_TOKEN(U"&#262143", 8);
	EXPECT_NULL_TOKEN(U"&#x3FFFF", 8);
	EXPECT_NULL_TOKEN(U"&#X3FFFF", 8);

	EXPECT_NULL_TOKEN(U"&#327678", 8);
	EXPECT_NULL_TOKEN(U"&#x4FFFE", 8);
	EXPECT_NULL_TOKEN(U"&#X4FFFE", 8);

	EXPECT_NULL_TOKEN(U"&#327679", 8);
	EXPECT_NULL_TOKEN(U"&#x4FFFF", 8);
	EXPECT_NULL_TOKEN(U"&#X4FFFF", 8);

	EXPECT_NULL_TOKEN(U"&#393214", 8);
	EXPECT_NULL_TOKEN(U"&#x5FFFE", 8);
	EXPECT_NULL_TOKEN(U"&#X5FFFE", 8);

	EXPECT_NULL_TOKEN(U"&#393215", 8);
	EXPECT_NULL_TOKEN(U"&#x5FFFF", 8);
	EXPECT_NULL_TOKEN(U"&#X5FFFF", 8);

	EXPECT_NULL_TOKEN(U"&#458750", 8);
	EXPECT_NULL_TOKEN(U"&#x6FFFE", 8);
	EXPECT_NULL_TOKEN(U"&#X6FFFE", 8);

	EXPECT_NULL_TOKEN(U"&#458751", 8);
	EXPECT_NULL_TOKEN(U"&#x6FFFF", 8);
	EXPECT_NULL_TOKEN(U"&#X6FFFF", 8);

	EXPECT_NULL_TOKEN(U"&#524286", 8);
	EXPECT_NULL_TOKEN(U"&#x7FFFE", 8);
	EXPECT_NULL_TOKEN(U"&#X7FFFE", 8);

	EXPECT_NULL_TOKEN(U"&#524287", 8);
	EXPECT_NULL_TOKEN(U"&#x7FFFF", 8);
	EXPECT_NULL_TOKEN(U"&#X7FFFF", 8);

	EXPECT_NULL_TOKEN(U"&#589822", 8);
	EXPECT_NULL_TOKEN(U"&#x8FFFE", 8);
	EXPECT_NULL_TOKEN(U"&#X8FFFE", 8);

	EXPECT_NULL_TOKEN(U"&#589823", 8);
	EXPECT_NULL_TOKEN(U"&#x8FFFF", 8);
	EXPECT_NULL_TOKEN(U"&#X8FFFF", 8);

	EXPECT_NULL_TOKEN(U"&#655358", 8);
	EXPECT_NULL_TOKEN(U"&#x9FFFE", 8);
	EXPECT_NULL_TOKEN(U"&#X9FFFE", 8);

	EXPECT_NULL_TOKEN(U"&#655359", 8);
	EXPECT_NULL_TOKEN(U"&#x9FFFF", 8);
	EXPECT_NULL_TOKEN(U"&#X9FFFF", 8);

	EXPECT_NULL_TOKEN(U"&#720894", 8);
	EXPECT_NULL_TOKEN(U"&#xAFFFE", 8);
	EXPECT_NULL_TOKEN(U"&#XAFFFE", 8);

	EXPECT_NULL_TOKEN(U"&#720895", 8);
	EXPECT_NULL_TOKEN(U"&#xAFFFF", 8);
	EXPECT_NULL_TOKEN(U"&#XAFFFF", 8);

	EXPECT_NULL_TOKEN(U"&#786430", 8);
	EXPECT_NULL_TOKEN(U"&#xBFFFE", 8);
	EXPECT_NULL_TOKEN(U"&#XBFFFE", 8);

	EXPECT_NULL_TOKEN(U"&#786431", 8);
	EXPECT_NULL_TOKEN(U"&#xBFFFF", 8);
	EXPECT_NULL_TOKEN(U"&#XBFFFF", 8);

	EXPECT_NULL_TOKEN(U"&#851966", 8);
	EXPECT_NULL_TOKEN(U"&#xCFFFE", 8);
	EXPECT_NULL_TOKEN(U"&#XCFFFE", 8);

	EXPECT_NULL_TOKEN(U"&#851967", 8);
	EXPECT_NULL_TOKEN(U"&#xCFFFF", 8);
	EXPECT_NULL_TOKEN(U"&#XCFFFF", 8);

	EXPECT_NULL_TOKEN(U"&#917502", 8);
	EXPECT_NULL_TOKEN(U"&#xDFFFE", 8);
	EXPECT_NULL_TOKEN(U"&#XDFFFE", 8);

	EXPECT_NULL_TOKEN(U"&#917503", 8);
	EXPECT_NULL_TOKEN(U"&#xDFFFF", 8);
	EXPECT_NULL_TOKEN(U"&#XDFFFF", 8);

	EXPECT_NULL_TOKEN(U"&#983038", 8);
	EXPECT_NULL_TOKEN(U"&#xEFFFE", 8);
	EXPECT_NULL_TOKEN(U"&#XEFFFE", 8);

	EXPECT_NULL_TOKEN(U"&#983039", 8);
	EXPECT_NULL_TOKEN(U"&#xEFFFF", 8);
	EXPECT_NULL_TOKEN(U"&#XEFFFF", 8);

	EXPECT_NULL_TOKEN(U"&#1048574", 9);
	EXPECT_NULL_TOKEN(U"&#xFFFFE", 8);
	EXPECT_NULL_TOKEN(U"&#XFFFFE", 8);

	EXPECT_NULL_TOKEN(U"&#1048575", 9);
	EXPECT_NULL_TOKEN(U"&#xFFFFF", 8);
	EXPECT_NULL_TOKEN(U"&#XFFFFF", 8);

	EXPECT_NULL_TOKEN(U"&#1114110", 9);
	EXPECT_NULL_TOKEN(U"&#x10FFFE", 9);
	EXPECT_NULL_TOKEN(U"&#X10FFFE", 9);

	EXPECT_NULL_TOKEN(U"&#1114111", 9);
	EXPECT_NULL_TOKEN(U"&#x10FFFF", 9);
	EXPECT_NULL_TOKEN(U"&#X10FFFF", 9);

	EXPECT_CHARACTER_TOKEN(U'\U000000C1', EOF, U"&Aacute", 7);
	EXPECT_CHARACTER_TOKEN(U'\U000000C1', EOF, U"&Aacute;", 8);
	EXPECT_CHARACTER_TOKEN(U'\U0000223E', U'\U00000333', U"&acE;", 5);
	EXPECT_CHARACTER_TOKEN(U'\U00002233', EOF, U"&CounterClockwiseContourIntegral;", 33);
	EXPECT_CHARACTER_TOKEN(U'\U00002063', EOF, U"&ic;", 4);

}

}
/* namespace Tokenization */
} /* namespace Parse */
} /* namespace HTML */

