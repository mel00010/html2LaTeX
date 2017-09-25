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

namespace HTML {
namespace Parse {
namespace Tokenization {

TEST(HTML_Parse_Tokenization_CharacterReference, consumeCharacterReference) {
	StateData test;
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData { STATES::DATA, U"&\t"}));
	EXPECT_EQ(0u, test.pos);

	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&\n"}));
	EXPECT_EQ(0u, test.pos);

	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&\f"}));
	EXPECT_EQ(0u, test.pos);

	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"& "}));
	EXPECT_EQ(0u, test.pos);

	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&<"}));
	EXPECT_EQ(0u, test.pos);

	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&&"}));
	EXPECT_EQ(0u, test.pos);

	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&\0"}));
	EXPECT_EQ(0u, test.pos);

	EXPECT_EQ(Token(), consumeCharacterReference((test = StateData {STATES::DATA, U"&a"}), 'a'));
	EXPECT_EQ(0u, test.pos);

	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#"}));
	EXPECT_EQ(0u, test.pos);

	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#x"}));
	EXPECT_EQ(0u, test.pos);

	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#X"}));
	EXPECT_EQ(0u, test.pos);

	EXPECT_EQ((Token {TokenType::CHARACTER, CharacterToken {U'\U0000FFFD'}}), consumeCharacterReference(test = StateData {STATES::DATA, U"&#0"}));
	EXPECT_EQ(3u, test.pos);
	EXPECT_EQ((Token {TokenType::CHARACTER, CharacterToken {U'\U0000FFFD'}}), consumeCharacterReference(test = StateData {STATES::DATA, U"&#x0"}));
	EXPECT_EQ(4u, test.pos);
	EXPECT_EQ((Token {TokenType::CHARACTER, CharacterToken {U'\U0000FFFD'}}), consumeCharacterReference(test = StateData {STATES::DATA, U"&#X0"}));
	EXPECT_EQ(4u, test.pos);

	EXPECT_EQ((Token {TokenType::CHARACTER, CharacterToken {U'\U000020AC'}}), consumeCharacterReference(test = StateData {STATES::DATA, U"&#128"}));
	EXPECT_EQ(5u, test.pos);
	EXPECT_EQ((Token {TokenType::CHARACTER, CharacterToken {U'\U000020AC'}}), consumeCharacterReference(test = StateData {STATES::DATA, U"&#x80"}));
	EXPECT_EQ(5u, test.pos);
	EXPECT_EQ((Token {TokenType::CHARACTER, CharacterToken {U'\U000020AC'}}), consumeCharacterReference(test = StateData {STATES::DATA, U"&#X80"}));
	EXPECT_EQ(5u, test.pos);

	EXPECT_EQ((Token {TokenType::CHARACTER, CharacterToken {U'\U0000201A'}}), consumeCharacterReference(test = StateData {STATES::DATA, U"&#130"}));
	EXPECT_EQ(5u, test.pos);
	EXPECT_EQ((Token {TokenType::CHARACTER, CharacterToken {U'\U0000201A'}}), consumeCharacterReference(test = StateData {STATES::DATA, U"&#x82"}));
	EXPECT_EQ(5u, test.pos);
	EXPECT_EQ((Token {TokenType::CHARACTER, CharacterToken {U'\U0000201A'}}), consumeCharacterReference(test = StateData {STATES::DATA, U"&#X82"}));
	EXPECT_EQ(5u, test.pos);

	EXPECT_EQ((Token {TokenType::CHARACTER, CharacterToken {U'\U00000192'}}), consumeCharacterReference(test = StateData {STATES::DATA, U"&#131"}));
	EXPECT_EQ(5u, test.pos);
	EXPECT_EQ((Token {TokenType::CHARACTER, CharacterToken {U'\U00000192'}}), consumeCharacterReference(test = StateData {STATES::DATA, U"&#x83"}));
	EXPECT_EQ(5u, test.pos);
	EXPECT_EQ((Token {TokenType::CHARACTER, CharacterToken {U'\U00000192'}}), consumeCharacterReference(test = StateData {STATES::DATA, U"&#X83"}));
	EXPECT_EQ(5u, test.pos);

	EXPECT_EQ((Token {TokenType::CHARACTER, CharacterToken {U'\U0000201E'}}), consumeCharacterReference(test = StateData {STATES::DATA, U"&#132"}));
	EXPECT_EQ(5u, test.pos);
	EXPECT_EQ((Token {TokenType::CHARACTER, CharacterToken {U'\U0000201E'}}), consumeCharacterReference(test = StateData {STATES::DATA, U"&#x84"}));
	EXPECT_EQ(5u, test.pos);
	EXPECT_EQ((Token {TokenType::CHARACTER, CharacterToken {U'\U0000201E'}}), consumeCharacterReference(test = StateData {STATES::DATA, U"&#X84"}));
	EXPECT_EQ(5u, test.pos);

	EXPECT_EQ((Token {TokenType::CHARACTER, CharacterToken {U'\U00002026'}}), consumeCharacterReference(test = StateData {STATES::DATA, U"&#133"}));
	EXPECT_EQ(5u, test.pos);
	EXPECT_EQ((Token {TokenType::CHARACTER, CharacterToken {U'\U00002026'}}), consumeCharacterReference(test = StateData {STATES::DATA, U"&#x85"}));
	EXPECT_EQ(5u, test.pos);
	EXPECT_EQ((Token {TokenType::CHARACTER, CharacterToken {U'\U00002026'}}), consumeCharacterReference(test = StateData {STATES::DATA, U"&#X85"}));
	EXPECT_EQ(5u, test.pos);

	EXPECT_EQ((Token {TokenType::CHARACTER, CharacterToken {U'\U00002020'}}), consumeCharacterReference(test = StateData {STATES::DATA, U"&#134"}));
	EXPECT_EQ(5u, test.pos);
	EXPECT_EQ((Token {TokenType::CHARACTER, CharacterToken {U'\U00002020'}}), consumeCharacterReference(test = StateData {STATES::DATA, U"&#x86"}));
	EXPECT_EQ(5u, test.pos);
	EXPECT_EQ((Token {TokenType::CHARACTER, CharacterToken {U'\U00002020'}}), consumeCharacterReference(test = StateData {STATES::DATA, U"&#X86"}));
	EXPECT_EQ(5u, test.pos);

	EXPECT_EQ((Token {TokenType::CHARACTER, CharacterToken {U'\U00002021'}}), consumeCharacterReference(test = StateData {STATES::DATA, U"&#135"}));
	EXPECT_EQ(5u, test.pos);
	EXPECT_EQ((Token {TokenType::CHARACTER, CharacterToken {U'\U00002021'}}), consumeCharacterReference(test = StateData {STATES::DATA, U"&#x87"}));
	EXPECT_EQ(5u, test.pos);
	EXPECT_EQ((Token {TokenType::CHARACTER, CharacterToken {U'\U00002021'}}), consumeCharacterReference(test = StateData {STATES::DATA, U"&#X87"}));
	EXPECT_EQ(5u, test.pos);

	EXPECT_EQ((Token {TokenType::CHARACTER, CharacterToken {U'\U000002C6'}}), consumeCharacterReference(test = StateData {STATES::DATA, U"&#136"}));
	EXPECT_EQ(5u, test.pos);
	EXPECT_EQ((Token {TokenType::CHARACTER, CharacterToken {U'\U000002C6'}}), consumeCharacterReference(test = StateData {STATES::DATA, U"&#x88"}));
	EXPECT_EQ(5u, test.pos);
	EXPECT_EQ((Token {TokenType::CHARACTER, CharacterToken {U'\U000002C6'}}), consumeCharacterReference(test = StateData {STATES::DATA, U"&#X88"}));
	EXPECT_EQ(5u, test.pos);

	EXPECT_EQ((Token {TokenType::CHARACTER, CharacterToken {U'\U00002030'}}), consumeCharacterReference(test = StateData {STATES::DATA, U"&#137"}));
	EXPECT_EQ(5u, test.pos);
	EXPECT_EQ((Token {TokenType::CHARACTER, CharacterToken {U'\U00002030'}}), consumeCharacterReference(test = StateData {STATES::DATA, U"&#x89"}));
	EXPECT_EQ(5u, test.pos);
	EXPECT_EQ((Token {TokenType::CHARACTER, CharacterToken {U'\U00002030'}}), consumeCharacterReference(test = StateData {STATES::DATA, U"&#X89"}));
	EXPECT_EQ(5u, test.pos);

	EXPECT_EQ((Token {TokenType::CHARACTER, CharacterToken {U'\U00000160'}}), consumeCharacterReference(test = StateData {STATES::DATA, U"&#138"}));
	EXPECT_EQ(5u, test.pos);
	EXPECT_EQ((Token {TokenType::CHARACTER, CharacterToken {U'\U00000160'}}), consumeCharacterReference(test = StateData {STATES::DATA, U"&#x8A"}));
	EXPECT_EQ(5u, test.pos);
	EXPECT_EQ((Token {TokenType::CHARACTER, CharacterToken {U'\U00000160'}}), consumeCharacterReference(test = StateData {STATES::DATA, U"&#X8A"}));
	EXPECT_EQ(5u, test.pos);

	EXPECT_EQ((Token {TokenType::CHARACTER, CharacterToken {U'\U00002039'}}), consumeCharacterReference(test = StateData {STATES::DATA, U"&#139"}));
	EXPECT_EQ(5u, test.pos);
	EXPECT_EQ((Token {TokenType::CHARACTER, CharacterToken {U'\U00002039'}}), consumeCharacterReference(test = StateData {STATES::DATA, U"&#x8B"}));
	EXPECT_EQ(5u, test.pos);
	EXPECT_EQ((Token {TokenType::CHARACTER, CharacterToken {U'\U00002039'}}), consumeCharacterReference(test = StateData {STATES::DATA, U"&#X8B"}));
	EXPECT_EQ(5u, test.pos);

	EXPECT_EQ((Token {TokenType::CHARACTER, CharacterToken {U'\U00000152'}}), consumeCharacterReference(test = StateData {STATES::DATA, U"&#140"}));
	EXPECT_EQ(5u, test.pos);
	EXPECT_EQ((Token {TokenType::CHARACTER, CharacterToken {U'\U00000152'}}), consumeCharacterReference(test = StateData {STATES::DATA, U"&#x8C"}));
	EXPECT_EQ(5u, test.pos);
	EXPECT_EQ((Token {TokenType::CHARACTER, CharacterToken {U'\U00000152'}}), consumeCharacterReference(test = StateData {STATES::DATA, U"&#X8C"}));
	EXPECT_EQ(5u, test.pos);

	EXPECT_EQ((Token {TokenType::CHARACTER, CharacterToken {U'\U0000017D'}}), consumeCharacterReference(test = StateData {STATES::DATA, U"&#142"}));
	EXPECT_EQ(5u, test.pos);
	EXPECT_EQ((Token {TokenType::CHARACTER, CharacterToken {U'\U0000017D'}}), consumeCharacterReference(test = StateData {STATES::DATA, U"&#x8E"}));
	EXPECT_EQ(5u, test.pos);
	EXPECT_EQ((Token {TokenType::CHARACTER, CharacterToken {U'\U0000017D'}}), consumeCharacterReference(test = StateData {STATES::DATA, U"&#X8E"}));
	EXPECT_EQ(5u, test.pos);

	EXPECT_EQ((Token {TokenType::CHARACTER, CharacterToken {U'\U00002018'}}), consumeCharacterReference(test = StateData {STATES::DATA, U"&#145"}));
	EXPECT_EQ(5u, test.pos);
	EXPECT_EQ((Token {TokenType::CHARACTER, CharacterToken {U'\U00002018'}}), consumeCharacterReference(test = StateData {STATES::DATA, U"&#x91"}));
	EXPECT_EQ(5u, test.pos);
	EXPECT_EQ((Token {TokenType::CHARACTER, CharacterToken {U'\U00002018'}}), consumeCharacterReference(test = StateData {STATES::DATA, U"&#X91"}));
	EXPECT_EQ(5u, test.pos);

	EXPECT_EQ((Token {TokenType::CHARACTER, CharacterToken {U'\U00002019'}}), consumeCharacterReference(test = StateData {STATES::DATA, U"&#146"}));
	EXPECT_EQ(5u, test.pos);
	EXPECT_EQ((Token {TokenType::CHARACTER, CharacterToken {U'\U00002019'}}), consumeCharacterReference(test = StateData {STATES::DATA, U"&#x92"}));
	EXPECT_EQ(5u, test.pos);
	EXPECT_EQ((Token {TokenType::CHARACTER, CharacterToken {U'\U00002019'}}), consumeCharacterReference(test = StateData {STATES::DATA, U"&#X92"}));
	EXPECT_EQ(5u, test.pos);

	EXPECT_EQ((Token {TokenType::CHARACTER, CharacterToken {U'\U0000201C'}}), consumeCharacterReference(test = StateData {STATES::DATA, U"&#147"}));
	EXPECT_EQ(5u, test.pos);
	EXPECT_EQ((Token {TokenType::CHARACTER, CharacterToken {U'\U0000201C'}}), consumeCharacterReference(test = StateData {STATES::DATA, U"&#x93"}));
	EXPECT_EQ(5u, test.pos);
	EXPECT_EQ((Token {TokenType::CHARACTER, CharacterToken {U'\U0000201C'}}), consumeCharacterReference(test = StateData {STATES::DATA, U"&#X93"}));
	EXPECT_EQ(5u, test.pos);

	EXPECT_EQ((Token {TokenType::CHARACTER, CharacterToken {U'\U0000201D'}}), consumeCharacterReference(test = StateData {STATES::DATA, U"&#148"}));
	EXPECT_EQ(5u, test.pos);
	EXPECT_EQ((Token {TokenType::CHARACTER, CharacterToken {U'\U0000201D'}}), consumeCharacterReference(test = StateData {STATES::DATA, U"&#x94"}));
	EXPECT_EQ(5u, test.pos);
	EXPECT_EQ((Token {TokenType::CHARACTER, CharacterToken {U'\U0000201D'}}), consumeCharacterReference(test = StateData {STATES::DATA, U"&#X94"}));
	EXPECT_EQ(5u, test.pos);

	EXPECT_EQ((Token {TokenType::CHARACTER, CharacterToken {U'\U00002022'}}), consumeCharacterReference(test = StateData {STATES::DATA, U"&#149"}));
	EXPECT_EQ(5u, test.pos);
	EXPECT_EQ((Token {TokenType::CHARACTER, CharacterToken {U'\U00002022'}}), consumeCharacterReference(test = StateData {STATES::DATA, U"&#x95"}));
	EXPECT_EQ(5u, test.pos);
	EXPECT_EQ((Token {TokenType::CHARACTER, CharacterToken {U'\U00002022'}}), consumeCharacterReference(test = StateData {STATES::DATA, U"&#X95"}));
	EXPECT_EQ(5u, test.pos);

	EXPECT_EQ((Token {TokenType::CHARACTER, CharacterToken {U'\U00002013'}}), consumeCharacterReference(test = StateData {STATES::DATA, U"&#150"}));
	EXPECT_EQ(5u, test.pos);
	EXPECT_EQ((Token {TokenType::CHARACTER, CharacterToken {U'\U00002013'}}), consumeCharacterReference(test = StateData {STATES::DATA, U"&#x96"}));
	EXPECT_EQ(5u, test.pos);
	EXPECT_EQ((Token {TokenType::CHARACTER, CharacterToken {U'\U00002013'}}), consumeCharacterReference(test = StateData {STATES::DATA, U"&#X96"}));
	EXPECT_EQ(5u, test.pos);

	EXPECT_EQ((Token {TokenType::CHARACTER, CharacterToken {U'\U00002014'}}), consumeCharacterReference(test = StateData {STATES::DATA, U"&#151"}));
	EXPECT_EQ(5u, test.pos);
	EXPECT_EQ((Token {TokenType::CHARACTER, CharacterToken {U'\U00002014'}}), consumeCharacterReference(test = StateData {STATES::DATA, U"&#x97"}));
	EXPECT_EQ(5u, test.pos);
	EXPECT_EQ((Token {TokenType::CHARACTER, CharacterToken {U'\U00002014'}}), consumeCharacterReference(test = StateData {STATES::DATA, U"&#X97"}));
	EXPECT_EQ(5u, test.pos);

	EXPECT_EQ((Token {TokenType::CHARACTER, CharacterToken {U'\U000002DC'}}), consumeCharacterReference(test = StateData {STATES::DATA, U"&#152"}));
	EXPECT_EQ(5u, test.pos);
	EXPECT_EQ((Token {TokenType::CHARACTER, CharacterToken {U'\U000002DC'}}), consumeCharacterReference(test = StateData {STATES::DATA, U"&#x98"}));
	EXPECT_EQ(5u, test.pos);
	EXPECT_EQ((Token {TokenType::CHARACTER, CharacterToken {U'\U000002DC'}}), consumeCharacterReference(test = StateData {STATES::DATA, U"&#X98"}));
	EXPECT_EQ(5u, test.pos);

	EXPECT_EQ((Token {TokenType::CHARACTER, CharacterToken {U'\U00002122'}}), consumeCharacterReference(test = StateData {STATES::DATA, U"&#153"}));
	EXPECT_EQ(5u, test.pos);
	EXPECT_EQ((Token {TokenType::CHARACTER, CharacterToken {U'\U00002122'}}), consumeCharacterReference(test = StateData {STATES::DATA, U"&#x99"}));
	EXPECT_EQ(5u, test.pos);
	EXPECT_EQ((Token {TokenType::CHARACTER, CharacterToken {U'\U00002122'}}), consumeCharacterReference(test = StateData {STATES::DATA, U"&#X99"}));
	EXPECT_EQ(5u, test.pos);

	EXPECT_EQ((Token {TokenType::CHARACTER, CharacterToken {U'\U00000161'}}), consumeCharacterReference(test = StateData {STATES::DATA, U"&#154"}));
	EXPECT_EQ(5u, test.pos);
	EXPECT_EQ((Token {TokenType::CHARACTER, CharacterToken {U'\U00000161'}}), consumeCharacterReference(test = StateData {STATES::DATA, U"&#x9A"}));
	EXPECT_EQ(5u, test.pos);
	EXPECT_EQ((Token {TokenType::CHARACTER, CharacterToken {U'\U00000161'}}), consumeCharacterReference(test = StateData {STATES::DATA, U"&#X9A"}));
	EXPECT_EQ(5u, test.pos);

	EXPECT_EQ((Token {TokenType::CHARACTER, CharacterToken {U'\U0000203A'}}), consumeCharacterReference(test = StateData {STATES::DATA, U"&#155"}));
	EXPECT_EQ(5u, test.pos);
	EXPECT_EQ((Token {TokenType::CHARACTER, CharacterToken {U'\U0000203A'}}), consumeCharacterReference(test = StateData {STATES::DATA, U"&#x9B"}));
	EXPECT_EQ(5u, test.pos);
	EXPECT_EQ((Token {TokenType::CHARACTER, CharacterToken {U'\U0000203A'}}), consumeCharacterReference(test = StateData {STATES::DATA, U"&#X9B"}));
	EXPECT_EQ(5u, test.pos);

	EXPECT_EQ((Token {TokenType::CHARACTER, CharacterToken {U'\U00000153'}}), consumeCharacterReference(test = StateData {STATES::DATA, U"&#156"}));
	EXPECT_EQ(5u, test.pos);
	EXPECT_EQ((Token {TokenType::CHARACTER, CharacterToken {U'\U00000153'}}), consumeCharacterReference(test = StateData {STATES::DATA, U"&#x9C"}));
	EXPECT_EQ(5u, test.pos);
	EXPECT_EQ((Token {TokenType::CHARACTER, CharacterToken {U'\U00000153'}}), consumeCharacterReference(test = StateData {STATES::DATA, U"&#X9C"}));
	EXPECT_EQ(5u, test.pos);

	EXPECT_EQ((Token {TokenType::CHARACTER, CharacterToken {U'\U0000017E'}}), consumeCharacterReference(test = StateData {STATES::DATA, U"&#158"}));
	EXPECT_EQ(5u, test.pos);
	EXPECT_EQ((Token {TokenType::CHARACTER, CharacterToken {U'\U0000017E'}}), consumeCharacterReference(test = StateData {STATES::DATA, U"&#x9E"}));
	EXPECT_EQ(5u, test.pos);
	EXPECT_EQ((Token {TokenType::CHARACTER, CharacterToken {U'\U0000017E'}}), consumeCharacterReference(test = StateData {STATES::DATA, U"&#X9E"}));
	EXPECT_EQ(5u, test.pos);

	EXPECT_EQ((Token {TokenType::CHARACTER, CharacterToken {U'\U00000178'}}), consumeCharacterReference(test = StateData {STATES::DATA, U"&#159"}));
	EXPECT_EQ(5u, test.pos);
	EXPECT_EQ((Token {TokenType::CHARACTER, CharacterToken {U'\U00000178'}}), consumeCharacterReference(test = StateData {STATES::DATA, U"&#x9F"}));
	EXPECT_EQ(5u, test.pos);
	EXPECT_EQ((Token {TokenType::CHARACTER, CharacterToken {U'\U00000178'}}), consumeCharacterReference(test = StateData {STATES::DATA, U"&#X9F"}));
	EXPECT_EQ(5u, test.pos);

	EXPECT_EQ((Token {TokenType::CHARACTER, CharacterToken {U'\U0000FFFD'}}), consumeCharacterReference(test = StateData {STATES::DATA, U"&#55296"}));
	EXPECT_EQ(7u, test.pos);
	EXPECT_EQ((Token {TokenType::CHARACTER, CharacterToken {U'\U0000FFFD'}}), consumeCharacterReference(test = StateData {STATES::DATA, U"&#xD800"}));
	EXPECT_EQ(7u, test.pos);
	EXPECT_EQ((Token {TokenType::CHARACTER, CharacterToken {U'\U0000FFFD'}}), consumeCharacterReference(test = StateData {STATES::DATA, U"&#XD800"}));
	EXPECT_EQ(7u, test.pos);

	EXPECT_EQ((Token {TokenType::CHARACTER, CharacterToken {U'\U0000FFFD'}}), consumeCharacterReference(test = StateData {STATES::DATA, U"&#57343"}));
	EXPECT_EQ(7u, test.pos);
	EXPECT_EQ((Token {TokenType::CHARACTER, CharacterToken {U'\U0000FFFD'}}), consumeCharacterReference(test = StateData {STATES::DATA, U"&#xDFFF"}));
	EXPECT_EQ(7u, test.pos);
	EXPECT_EQ((Token {TokenType::CHARACTER, CharacterToken {U'\U0000FFFD'}}), consumeCharacterReference(test = StateData {STATES::DATA, U"&#XDFFF"}));
	EXPECT_EQ(7u, test.pos);

	EXPECT_EQ((Token {TokenType::CHARACTER, CharacterToken {U'\U0000FFFD'}}), consumeCharacterReference(test = StateData {STATES::DATA, U"&#57343"}));
	EXPECT_EQ(7u, test.pos);
	EXPECT_EQ((Token {TokenType::CHARACTER, CharacterToken {U'\U0000FFFD'}}), consumeCharacterReference(test = StateData {STATES::DATA, U"&#xDFFF"}));
	EXPECT_EQ(7u, test.pos);
	EXPECT_EQ((Token {TokenType::CHARACTER, CharacterToken {U'\U0000FFFD'}}), consumeCharacterReference(test = StateData {STATES::DATA, U"&#XDFFF"}));
	EXPECT_EQ(7u, test.pos);

	EXPECT_EQ((Token {TokenType::CHARACTER, CharacterToken {U'\U0000FFFD'}}), consumeCharacterReference(test = StateData {STATES::DATA, U"&#1114112"}));
	EXPECT_EQ(9u, test.pos);
	EXPECT_EQ((Token {TokenType::CHARACTER, CharacterToken {U'\U0000FFFD'}}), consumeCharacterReference(test = StateData {STATES::DATA, U"&#x110000"}));
	EXPECT_EQ(9u, test.pos);
	EXPECT_EQ((Token {TokenType::CHARACTER, CharacterToken {U'\U0000FFFD'}}), consumeCharacterReference(test = StateData {STATES::DATA, U"&#X110000"}));
	EXPECT_EQ(9u, test.pos);

	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#1"}));
	EXPECT_EQ(3u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#x1"}));
	EXPECT_EQ(4u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#X1"}));
	EXPECT_EQ(4u, test.pos);

	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#2"}));
	EXPECT_EQ(3u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#x2"}));
	EXPECT_EQ(4u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#X2"}));
	EXPECT_EQ(4u, test.pos);

	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#3"}));
	EXPECT_EQ(3u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#x3"}));
	EXPECT_EQ(4u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#X3"}));
	EXPECT_EQ(4u, test.pos);

	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#4"}));
	EXPECT_EQ(3u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#x4"}));
	EXPECT_EQ(4u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#X4"}));
	EXPECT_EQ(4u, test.pos);

	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#5"}));
	EXPECT_EQ(3u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#x5"}));
	EXPECT_EQ(4u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#X5"}));
	EXPECT_EQ(4u, test.pos);

	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#6"}));
	EXPECT_EQ(3u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#x6"}));
	EXPECT_EQ(4u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#X6"}));
	EXPECT_EQ(4u, test.pos);

	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#7"}));
	EXPECT_EQ(3u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#x7"}));
	EXPECT_EQ(4u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#X7"}));
	EXPECT_EQ(4u, test.pos);

	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#8"}));
	EXPECT_EQ(3u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#x8"}));
	EXPECT_EQ(4u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#X8"}));
	EXPECT_EQ(4u, test.pos);

	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#13"}));
	EXPECT_EQ(4u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#xD"}));
	EXPECT_EQ(4u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#XD"}));
	EXPECT_EQ(4u, test.pos);

	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#14"}));
	EXPECT_EQ(4u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#xE"}));
	EXPECT_EQ(4u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#XE"}));
	EXPECT_EQ(4u, test.pos);

	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#15"}));
	EXPECT_EQ(4u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#xF"}));
	EXPECT_EQ(4u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#XF"}));
	EXPECT_EQ(4u, test.pos);

	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#16"}));
	EXPECT_EQ(4u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#x10"}));
	EXPECT_EQ(5u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#X10"}));
	EXPECT_EQ(5u, test.pos);

	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#17"}));
	EXPECT_EQ(4u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#x11"}));
	EXPECT_EQ(5u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#X11"}));
	EXPECT_EQ(5u, test.pos);

	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#18"}));
	EXPECT_EQ(4u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#x12"}));
	EXPECT_EQ(5u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#X12"}));
	EXPECT_EQ(5u, test.pos);

	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#19"}));
	EXPECT_EQ(4u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#x13"}));
	EXPECT_EQ(5u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#X13"}));
	EXPECT_EQ(5u, test.pos);

	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#20"}));
	EXPECT_EQ(4u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#x14"}));
	EXPECT_EQ(5u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#X14"}));
	EXPECT_EQ(5u, test.pos);

	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#21"}));
	EXPECT_EQ(4u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#x15"}));
	EXPECT_EQ(5u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#X15"}));
	EXPECT_EQ(5u, test.pos);

	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#22"}));
	EXPECT_EQ(4u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#x16"}));
	EXPECT_EQ(5u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#X16"}));
	EXPECT_EQ(5u, test.pos);

	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#23"}));
	EXPECT_EQ(4u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#x17"}));
	EXPECT_EQ(5u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#X17"}));
	EXPECT_EQ(5u, test.pos);

	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#24"}));
	EXPECT_EQ(4u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#x18"}));
	EXPECT_EQ(5u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#X18"}));
	EXPECT_EQ(5u, test.pos);

	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#25"}));
	EXPECT_EQ(4u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#x19"}));
	EXPECT_EQ(5u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#X19"}));
	EXPECT_EQ(5u, test.pos);

	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#26"}));
	EXPECT_EQ(4u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#x1A"}));
	EXPECT_EQ(5u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#X1A"}));
	EXPECT_EQ(5u, test.pos);

	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#27"}));
	EXPECT_EQ(4u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#x1B"}));
	EXPECT_EQ(5u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#X1B"}));
	EXPECT_EQ(5u, test.pos);

	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#28"}));
	EXPECT_EQ(4u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#x1C"}));
	EXPECT_EQ(5u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#X1C"}));
	EXPECT_EQ(5u, test.pos);

	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#29"}));
	EXPECT_EQ(4u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#x1D"}));
	EXPECT_EQ(5u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#X1D"}));
	EXPECT_EQ(5u, test.pos);

	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#30"}));
	EXPECT_EQ(4u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#x1E"}));
	EXPECT_EQ(5u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#X1E"}));
	EXPECT_EQ(5u, test.pos);

	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#31"}));
	EXPECT_EQ(4u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#x1F"}));
	EXPECT_EQ(5u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#X1F"}));
	EXPECT_EQ(5u, test.pos);

	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#127"}));
	EXPECT_EQ(5u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#x7F"}));
	EXPECT_EQ(5u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#X7F"}));
	EXPECT_EQ(5u, test.pos);

	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#159"}));
	EXPECT_EQ(5u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#x9F"}));
	EXPECT_EQ(5u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#X9F"}));
	EXPECT_EQ(5u, test.pos);

	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#64976"}));
	EXPECT_EQ(7u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#xFDD0"}));
	EXPECT_EQ(7u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#XFDD0"}));
	EXPECT_EQ(7u, test.pos);

	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#65007"}));
	EXPECT_EQ(7u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#xFDEF"}));
	EXPECT_EQ(7u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#XFDEF"}));
	EXPECT_EQ(7u, test.pos);

	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#11"}));
	EXPECT_EQ(4u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#xB"}));
	EXPECT_EQ(4u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#XB"}));
	EXPECT_EQ(4u, test.pos);

	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#65534"}));
	EXPECT_EQ(7u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#xFFFE"}));
	EXPECT_EQ(7u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#XFFFE"}));
	EXPECT_EQ(7u, test.pos);

	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#65535"}));
	EXPECT_EQ(7u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#xFFFF"}));
	EXPECT_EQ(7u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#XFFFF"}));
	EXPECT_EQ(7u, test.pos);

	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#131070"}));
	EXPECT_EQ(8u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#x1FFFE"}));
	EXPECT_EQ(8u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#X1FFFE"}));
	EXPECT_EQ(8u, test.pos);

	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#131071"}));
	EXPECT_EQ(8u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#x1FFFF"}));
	EXPECT_EQ(8u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#X1FFFF"}));
	EXPECT_EQ(8u, test.pos);

	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#196606"}));
	EXPECT_EQ(8u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#x2FFFE"}));
	EXPECT_EQ(8u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#X2FFFE"}));
	EXPECT_EQ(8u, test.pos);

	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#196607"}));
	EXPECT_EQ(8u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#x2FFFF"}));
	EXPECT_EQ(8u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#X2FFFF"}));
	EXPECT_EQ(8u, test.pos);

	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#262142"}));
	EXPECT_EQ(8u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#x3FFFE"}));
	EXPECT_EQ(8u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#X3FFFE"}));
	EXPECT_EQ(8u, test.pos);

	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#262143"}));
	EXPECT_EQ(8u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#x3FFFF"}));
	EXPECT_EQ(8u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#X3FFFF"}));
	EXPECT_EQ(8u, test.pos);

	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#327678"}));
	EXPECT_EQ(8u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#x4FFFE"}));
	EXPECT_EQ(8u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#X4FFFE"}));
	EXPECT_EQ(8u, test.pos);

	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#327679"}));
	EXPECT_EQ(8u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#x4FFFF"}));
	EXPECT_EQ(8u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#X4FFFF"}));
	EXPECT_EQ(8u, test.pos);

	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#393214"}));
	EXPECT_EQ(8u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#x5FFFE"}));
	EXPECT_EQ(8u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#X5FFFE"}));
	EXPECT_EQ(8u, test.pos);

	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#393215"}));
	EXPECT_EQ(8u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#x5FFFF"}));
	EXPECT_EQ(8u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#X5FFFF"}));
	EXPECT_EQ(8u, test.pos);

	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#458750"}));
	EXPECT_EQ(8u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#x6FFFE"}));
	EXPECT_EQ(8u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#X6FFFE"}));
	EXPECT_EQ(8u, test.pos);

	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#458751"}));
	EXPECT_EQ(8u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#x6FFFF"}));
	EXPECT_EQ(8u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#X6FFFF"}));
	EXPECT_EQ(8u, test.pos);

	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#524286"}));
	EXPECT_EQ(8u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#x7FFFE"}));
	EXPECT_EQ(8u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#X7FFFE"}));
	EXPECT_EQ(8u, test.pos);

	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#524287"}));
	EXPECT_EQ(8u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#x7FFFF"}));
	EXPECT_EQ(8u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#X7FFFF"}));
	EXPECT_EQ(8u, test.pos);

	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#589822"}));
	EXPECT_EQ(8u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#x8FFFE"}));
	EXPECT_EQ(8u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#X8FFFE"}));
	EXPECT_EQ(8u, test.pos);

	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#589823"}));
	EXPECT_EQ(8u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#x8FFFF"}));
	EXPECT_EQ(8u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#X8FFFF"}));
	EXPECT_EQ(8u, test.pos);

	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#655358"}));
	EXPECT_EQ(8u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#x9FFFE"}));
	EXPECT_EQ(8u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#X9FFFE"}));
	EXPECT_EQ(8u, test.pos);

	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#655359"}));
	EXPECT_EQ(8u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#x9FFFF"}));
	EXPECT_EQ(8u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#X9FFFF"}));
	EXPECT_EQ(8u, test.pos);

	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#720894"}));
	EXPECT_EQ(8u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#xAFFFE"}));
	EXPECT_EQ(8u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#XAFFFE"}));
	EXPECT_EQ(8u, test.pos);

	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#720895"}));
	EXPECT_EQ(8u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#xAFFFF"}));
	EXPECT_EQ(8u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#XAFFFF"}));
	EXPECT_EQ(8u, test.pos);

	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#786430"}));
	EXPECT_EQ(8u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#xBFFFE"}));
	EXPECT_EQ(8u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#XBFFFE"}));
	EXPECT_EQ(8u, test.pos);

	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#786431"}));
	EXPECT_EQ(8u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#xBFFFF"}));
	EXPECT_EQ(8u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#XBFFFF"}));
	EXPECT_EQ(8u, test.pos);

	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#851966"}));
	EXPECT_EQ(8u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#xCFFFE"}));
	EXPECT_EQ(8u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#XCFFFE"}));
	EXPECT_EQ(8u, test.pos);

	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#851967"}));
	EXPECT_EQ(8u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#xCFFFF"}));
	EXPECT_EQ(8u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#XCFFFF"}));
	EXPECT_EQ(8u, test.pos);

	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#917502"}));
	EXPECT_EQ(8u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#xDFFFE"}));
	EXPECT_EQ(8u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#XDFFFE"}));
	EXPECT_EQ(8u, test.pos);

	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#917503"}));
	EXPECT_EQ(8u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#xDFFFF"}));
	EXPECT_EQ(8u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#XDFFFF"}));
	EXPECT_EQ(8u, test.pos);

	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#983038"}));
	EXPECT_EQ(8u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#xEFFFE"}));
	EXPECT_EQ(8u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#XEFFFE"}));
	EXPECT_EQ(8u, test.pos);

	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#983039"}));
	EXPECT_EQ(8u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#xEFFFF"}));
	EXPECT_EQ(8u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#XEFFFF"}));
	EXPECT_EQ(8u, test.pos);

	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#1048574"}));
	EXPECT_EQ(9u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#xFFFFE"}));
	EXPECT_EQ(8u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#XFFFFE"}));
	EXPECT_EQ(8u, test.pos);

	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#1048575"}));
	EXPECT_EQ(9u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#xFFFFF"}));
	EXPECT_EQ(8u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#XFFFFF"}));
	EXPECT_EQ(8u, test.pos);

	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#1114110"}));
	EXPECT_EQ(9u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#x10FFFE"}));
	EXPECT_EQ(9u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#X10FFFE"}));
	EXPECT_EQ(9u, test.pos);

	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#1114111"}));
	EXPECT_EQ(9u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#x10FFFF"}));
	EXPECT_EQ(9u, test.pos);
	EXPECT_EQ(Token(), consumeCharacterReference(test = StateData {STATES::DATA, U"&#X10FFFF"}));
	EXPECT_EQ(9u, test.pos);

}

}
/* namespace Tokenization */
} /* namespace Parse */
} /* namespace HTML */
