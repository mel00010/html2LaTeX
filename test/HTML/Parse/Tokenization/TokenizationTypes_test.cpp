/*******************************************************************************
 * TokenizationTypes_test.cpp
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

#include <HTML/Parse/Tokenization/TokenizationTypes.hpp>

#include <HTML/HTMLTypes.hpp>

#include <iostream>
#include <list>
#include <sstream>
#include <string>

namespace HTML {
namespace Parse {
namespace Tokenization {

TEST(HTML_Parse_Tokenization_TokenizationTypes, DOCTYPEToken) {
	EXPECT_EQ((DOCTYPEToken { U"name", U"public_identifier", U"system_identifier", false}),
(DOCTYPEToken {U"name", U"public_identifier", U"system_identifier", false}));
EXPECT_NE((DOCTYPEToken {U"not a name", U"not a public_identifier", U"system system_identifier", true}),
(DOCTYPEToken {U"name", U"public_identifier", U"system_identifier", false}));
EXPECT_NE((DOCTYPEToken {U"name", U"not a public_identifier", U"not a system_identifier", true}),
(DOCTYPEToken {U"name", U"public_identifier", U"system_identifier", false}));
EXPECT_NE((DOCTYPEToken {U"name", U"public_identifier", U"system_identifier", true}),
(DOCTYPEToken {U"name", U"public_identifier", U"system_identifier", false}));
}

TEST(HTML_Parse_Tokenization_TokenizationTypes, StartTagToken) {
	EXPECT_EQ((StartTagToken { U"tag_name", false, std::list<Attribute> {}}),
(StartTagToken {U"tag_name", false, std::list<Attribute> {}}));
EXPECT_EQ((StartTagToken {U"tag_name", false, std::list<Attribute> {Attribute(U"name", U"value")}}),
(StartTagToken {U"tag_name", false, std::list<Attribute> {Attribute(U"name", U"value")}}));
EXPECT_NE((StartTagToken {U"tag_name", false, std::list<Attribute> {Attribute(U"not the same", U"value")}}),
(StartTagToken {U"tag_name", false, std::list<Attribute> {Attribute(U"name", U"value")}}));
EXPECT_NE((StartTagToken {U"tag_name", false, std::list<Attribute> {Attribute(U"name", U"not the same")}}),
(StartTagToken {U"tag_name", false, std::list<Attribute> {Attribute(U"name", U"value")}}));
EXPECT_NE((StartTagToken {U"not the same", false, std::list<Attribute> {Attribute(U"name", U"value")}}),
(StartTagToken {U"tag_name", false, std::list<Attribute> {Attribute(U"name", U"value")}}));
EXPECT_NE((StartTagToken {U"tag_name", true, std::list<Attribute> {Attribute(U"name", U"value")}}),
(StartTagToken {U"tag_name", false, std::list<Attribute> {Attribute(U"name", U"value")}}));
EXPECT_NE((StartTagToken {U"not the same", true, std::list<Attribute> {}}),
(StartTagToken {U"tag_name", false, std::list<Attribute> {Attribute(U"name", U"value")}}));

}

TEST(HTML_Parse_Tokenization_TokenizationTypes, EndTagToken) {
	EXPECT_EQ((EndTagToken { U"tag_name", false, std::list<Attribute> {}}),
(EndTagToken {U"tag_name", false, std::list<Attribute> {}}));
EXPECT_EQ((EndTagToken {U"tag_name", false, std::list<Attribute> {Attribute(U"name", U"value")}}),
(EndTagToken {U"tag_name", false, std::list<Attribute> {Attribute(U"name", U"value")}}));
EXPECT_NE((EndTagToken {U"tag_name", false, std::list<Attribute> {Attribute(U"not the same", U"value")}}),
(EndTagToken {U"tag_name", false, std::list<Attribute> {Attribute(U"name", U"value")}}));
EXPECT_NE((EndTagToken {U"tag_name", false, std::list<Attribute> {Attribute(U"name", U"not the same")}}),
(EndTagToken {U"tag_name", false, std::list<Attribute> {Attribute(U"name", U"value")}}));
EXPECT_NE((EndTagToken {U"not the same", false, std::list<Attribute> {Attribute(U"name", U"value")}}),
(EndTagToken {U"tag_name", false, std::list<Attribute> {Attribute(U"name", U"value")}}));
EXPECT_NE((EndTagToken {U"tag_name", true, std::list<Attribute> {Attribute(U"name", U"value")}}),
(EndTagToken {U"tag_name", false, std::list<Attribute> {Attribute(U"name", U"value")}}));
EXPECT_NE((EndTagToken {U"not the same", true, std::list<Attribute> {}}),
(EndTagToken {U"tag_name", false, std::list<Attribute> {Attribute(U"name", U"value")}}));

}

TEST(HTML_Parse_Tokenization_TokenizationTypes, CharacterToken) {
	EXPECT_EQ(CharacterToken(), CharacterToken());
	EXPECT_EQ((CharacterToken { U'\U00001234' }), (CharacterToken { U'\U00001234' }));
	EXPECT_NE((CharacterToken { U'\U00001234' }), (CharacterToken { U'\U12340000' }));
	EXPECT_NE((CharacterToken { U'\U00001234' }), CharacterToken());
}

TEST(HTML_Parse_Tokenization_TokenizationTypes, CommentToken) {
	EXPECT_EQ(CommentToken(), CommentToken());
	EXPECT_EQ((CommentToken { U"this is a comment"}), (CommentToken {U"this is a comment"}));

EXPECT_NE((CommentToken {U"this is a comment"}), (CommentToken {U"this is not a comment"}));
EXPECT_NE((CommentToken {U"this is a comment"}), CommentToken());
}

TEST(HTML_Parse_Tokenization_TokenizationTypes, EOFToken) {
	EXPECT_EQ(EOFToken(), EOFToken());
	EXPECT_FALSE(EOFToken() != EOFToken());
}

TEST(HTML_Parse_Tokenization_TokenizationTypes, NoToken) {
	EXPECT_EQ(NoToken(), NoToken());
	EXPECT_FALSE(NoToken() != NoToken());
}

TEST(HTML_Parse_Tokenization_TokenizationTypes, Token) {
	EXPECT_EQ(Token(), Token());
	EXPECT_EQ((Token { TokenType::END_OF_FILE, EOFToken() }), (Token { TokenType::END_OF_FILE, EOFToken() }));
	EXPECT_NE((Token { TokenType::END_OF_FILE, EOFToken() }), (Token { TokenType::NO_TOKEN, EOFToken() }));
	EXPECT_NE((Token { TokenType::END_OF_FILE, EOFToken() }), (Token { TokenType::END_OF_FILE, NoToken() }));
	EXPECT_NE((Token { TokenType::END_OF_FILE, EOFToken() }), (Token { TokenType::NO_TOKEN, EOFToken() }));
	EXPECT_NE((Token { TokenType::END_OF_FILE, EOFToken() }), Token());
}

} /* namespace Tokenization */
} /* namespace Parse */
} /* namespace HTML */
