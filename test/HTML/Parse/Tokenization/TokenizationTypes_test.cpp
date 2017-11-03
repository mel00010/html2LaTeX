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

TEST(HTML_Parse_Tokenization_TokenizationTypes, TokenTypeStreamWrite) {
	EXPECT_EQ("TokenType::DOCTYPE", static_cast<std::stringstream&>(std::stringstream() << TokenType::DOCTYPE).str());
	EXPECT_EQ("TokenType::START_TAG", static_cast<std::stringstream&>(std::stringstream() << TokenType::START_TAG).str());
	EXPECT_EQ("TokenType::END_TAG", static_cast<std::stringstream&>(std::stringstream() << TokenType::END_TAG).str());
	EXPECT_EQ("TokenType::COMMENT", static_cast<std::stringstream&>(std::stringstream() << TokenType::COMMENT).str());
	EXPECT_EQ("TokenType::CHARACTER", static_cast<std::stringstream&>(std::stringstream() << TokenType::CHARACTER).str());
	EXPECT_EQ("TokenType::END_OF_FILE", static_cast<std::stringstream&>(std::stringstream() << TokenType::END_OF_FILE).str());
	EXPECT_EQ("TokenType::NO_TOKEN", static_cast<std::stringstream&>(std::stringstream() << TokenType::NO_TOKEN).str());

}

TEST(HTML_Parse_Tokenization_TokenizationTypes, DOCTYPETokenStreamWrite) {
	{
		std::stringstream testStream;
		testStream << DOCTYPEToken();
		std::string result = "";
		result += "std::string name = \\(EOF)\n";
		result += "std::string public_identifier = \\(EOF)\n";
		result += "std::string system_identifier = \\(EOF)\n";
		result += "bool force_quirks = 0";
		EXPECT_EQ(result, testStream.str());
	}
	{
		std::stringstream testStream;
		testStream << (DOCTYPEToken { "name", "public_identifier", "system_identifier", true });
		std::string result = "";
		result += "std::string name = name\n";
		result += "std::string public_identifier = public_identifier\n";
		result += "std::string system_identifier = system_identifier\n";
		result += "bool force_quirks = 1";
		EXPECT_EQ(result, testStream.str());
	}
}

TEST(HTML_Parse_Tokenization_TokenizationTypes, DOCTYPETokenEquality) {
	EXPECT_EQ((DOCTYPEToken { "name", "public_identifier", "system_identifier", false }),
			(DOCTYPEToken { "name", "public_identifier", "system_identifier", false }));
	EXPECT_NE((DOCTYPEToken { "not a name", "not a public_identifier", "system system_identifier", true }),
			(DOCTYPEToken { "name", "public_identifier", "system_identifier", false }));
	EXPECT_NE((DOCTYPEToken { "name", "not a public_identifier", "not a system_identifier", true }),
			(DOCTYPEToken { "name", "public_identifier", "system_identifier", false }));
	EXPECT_NE((DOCTYPEToken { "name", "public_identifier", "system_identifier", true }),
			(DOCTYPEToken { "name", "public_identifier", "system_identifier", false }));
}

TEST(HTML_Parse_Tokenization_TokenizationTypes, StartTagTokenStreamWrite) {
	{
		std::stringstream testStream;
		testStream << StartTagToken();
		std::string result = "";
		result += "std::string tag_name = \n";
		result += "bool self_closing = 0\n";
		result += "std::list<Attribute> attributes = ";
		EXPECT_EQ(result, testStream.str());
	}
	{
		std::stringstream testStream;
		testStream << (StartTagToken { "tag_name",
				true,
				std::list<Attribute> {
						Attribute { "name1", "value1" },
						Attribute { "name2", "value2" } } });
		std::string result = "";
		result += "std::string tag_name = tag_name\n";
		result += "bool self_closing = 1\n";
		result += "std::list<Attribute> attributes = \"name1\":\"value1\", \"name2\":\"value2\", ";
		EXPECT_EQ(result, testStream.str());
	}
}

TEST(HTML_Parse_Tokenization_TokenizationTypes, StartTagTokenEquality) {
	EXPECT_EQ((StartTagToken { "tag_name", false, std::list<Attribute> { } }),
			(StartTagToken { "tag_name", false, std::list<Attribute> { } }));
	EXPECT_EQ((StartTagToken { "tag_name", false, std::list<Attribute> { Attribute("name", "value") } }),
			(StartTagToken { "tag_name", false, std::list<Attribute> { Attribute("name", "value") } }));
	EXPECT_NE((StartTagToken { "tag_name", false, std::list<Attribute> { Attribute("not the same", "value") } }),
			(StartTagToken { "tag_name", false, std::list<Attribute> { Attribute("name", "value") } }));
	EXPECT_NE((StartTagToken { "tag_name", false, std::list<Attribute> { Attribute("name", "not the same") } }),
			(StartTagToken { "tag_name", false, std::list<Attribute> { Attribute("name", "value") } }));
	EXPECT_NE((StartTagToken { "not the same", false, std::list<Attribute> { Attribute("name", "value") } }),
			(StartTagToken { "tag_name", false, std::list<Attribute> { Attribute("name", "value") } }));
	EXPECT_NE((StartTagToken { "tag_name", true, std::list<Attribute> { Attribute("name", "value") } }),
			(StartTagToken { "tag_name", false, std::list<Attribute> { Attribute("name", "value") } }));
	EXPECT_NE((StartTagToken { "not the same", true, std::list<Attribute> { } }),
			(StartTagToken { "tag_name", false, std::list<Attribute> { Attribute("name", "value") } }));

}

TEST(HTML_Parse_Tokenization_TokenizationTypes, EndTagTokenStreamWrite) {
	{
		std::stringstream testStream;
		testStream << EndTagToken();
		std::string result = "";
		result += "std::string tag_name = \n";
		result += "bool self_closing = 0\n";
		result += "std::list<Attribute> attributes = ";
		EXPECT_EQ(result, testStream.str());
	}
	{
		std::stringstream testStream;
		testStream << (EndTagToken { "tag_name",
				true,
				std::list<Attribute> {
						Attribute { "name1", "value1" },
						Attribute { "name2", "value2" } } });

		std::string result = "";
		result += "std::string tag_name = tag_name\n";
		result += "bool self_closing = 1\n";
		result += "std::list<Attribute> attributes = \"name1\":\"value1\", \"name2\":\"value2\", ";
		EXPECT_EQ(result, testStream.str());
	}
}

TEST(HTML_Parse_Tokenization_TokenizationTypes, EndTagTokenEquality) {
	EXPECT_EQ((EndTagToken { "tag_name", false, std::list<Attribute> { } }),
			(EndTagToken { "tag_name", false, std::list<Attribute> { } }));
	EXPECT_EQ((EndTagToken { "tag_name", false, std::list<Attribute> { Attribute("name", "value") } }),
			(EndTagToken { "tag_name", false, std::list<Attribute> { Attribute("name", "value") } }));
	EXPECT_NE((EndTagToken { "tag_name", false, std::list<Attribute> { Attribute("not the same", "value") } }),
			(EndTagToken { "tag_name", false, std::list<Attribute> { Attribute("name", "value") } }));
	EXPECT_NE((EndTagToken { "tag_name", false, std::list<Attribute> { Attribute("name", "not the same") } }),
			(EndTagToken { "tag_name", false, std::list<Attribute> { Attribute("name", "value") } }));
	EXPECT_NE((EndTagToken { "not the same", false, std::list<Attribute> { Attribute("name", "value") } }),
			(EndTagToken { "tag_name", false, std::list<Attribute> { Attribute("name", "value") } }));
	EXPECT_NE((EndTagToken { "tag_name", true, std::list<Attribute> { Attribute("name", "value") } }),
			(EndTagToken { "tag_name", false, std::list<Attribute> { Attribute("name", "value") } }));
	EXPECT_NE((EndTagToken { "not the same", true, std::list<Attribute> { } }),
			(EndTagToken { "tag_name", false, std::list<Attribute> { Attribute("name", "value") } }));

}

TEST(HTML_Parse_Tokenization_TokenizationTypes, CharacterTokenStreamWrite) {
	{
		std::stringstream testStream;
		testStream << CharacterToken();
		std::string result = "";
		result += "char32_t data = U+FFFFFFFF";
		EXPECT_EQ(result, testStream.str());
	}
	{
		std::stringstream testStream;
		testStream << (CharacterToken { U'\U00001234' });
		std::string result = "";
		result += "char32_t data = U+00001234";
		EXPECT_EQ(result, testStream.str());
	}
	{
		std::stringstream testStream;
		testStream << (CharacterToken { U'\U00001234' });
		std::string result = "";
		result += "char32_t data = U+00001234";
		EXPECT_EQ(result, testStream.str());
	}
}

TEST(HTML_Parse_Tokenization_TokenizationTypes, CharacterTokenEquality) {
	EXPECT_EQ(CharacterToken(), CharacterToken());
	EXPECT_EQ((CharacterToken { U'\U00001234' }), (CharacterToken { U'\U00001234' }));
	EXPECT_NE((CharacterToken { U'\U00001234' }), (CharacterToken { U'\U12340000' }));
	EXPECT_NE((CharacterToken { U'\U00001234' }), CharacterToken());
}

TEST(HTML_Parse_Tokenization_TokenizationTypes, CommentTokenStreamWrite) {
	{
		std::stringstream testStream;
		testStream << CommentToken();
		std::string result = "std::string data = \"\"";
		EXPECT_EQ(result, testStream.str());
	}
	{
		std::stringstream testStream;
		testStream << (CommentToken { "this is a comment" });
		std::string result = "std::string data = \"this is a comment\"";
		EXPECT_EQ(result, testStream.str());
	}
}

TEST(HTML_Parse_Tokenization_TokenizationTypes, CommentTokenEquality) {
	EXPECT_EQ(CommentToken(), CommentToken());
	EXPECT_EQ((CommentToken { "this is a comment" }), (CommentToken { "this is a comment" }));
	EXPECT_NE((CommentToken { "this is a comment" }), (CommentToken { "this is not a comment" }));
	EXPECT_NE((CommentToken { "this is a comment" }), CommentToken());
}

TEST(HTML_Parse_Tokenization_TokenizationTypes, EOFTokenStreamWrite) {
	{
		std::stringstream testStream;
		testStream << EOFToken();
		std::string result = "\\(EOF)";
		EXPECT_EQ(result, testStream.str());
	}
}

TEST(HTML_Parse_Tokenization_TokenizationTypes, EOFTokenEquality) {
	EXPECT_EQ(EOFToken(), EOFToken());
	EXPECT_FALSE(EOFToken() != EOFToken());
}

TEST(HTML_Parse_Tokenization_TokenizationTypes, NoTokenStreamWrite) {
	{
		std::stringstream testStream;
		testStream << NoToken();
		std::string result = "No Token!";
		EXPECT_EQ(result, testStream.str());
	}
}

TEST(HTML_Parse_Tokenization_TokenizationTypes, NoTokenEquality) {
	EXPECT_EQ(NoToken(), NoToken());
	EXPECT_FALSE(NoToken() != NoToken());
}

TEST(HTML_Parse_Tokenization_TokenizationTypes, TokenStreamWrite) {
	{
		std::stringstream testStream;
		testStream << (Token { TokenType::END_OF_FILE, EOFToken() });

		std::string result = "";
		result += "TokenType type = TokenType::END_OF_FILE\n";
		result += "TokenVariant token = \\(EOF)";

		EXPECT_EQ(result, testStream.str());

	}
	{
		std::stringstream testStream;
		testStream << (Token { TokenType::NO_TOKEN, NoToken() });

		std::string result = "";
		result += "TokenType type = TokenType::NO_TOKEN\n";
		result += "TokenVariant token = No Token!";

		EXPECT_EQ(result, testStream.str());

	}
	{
		std::stringstream testStream;
		testStream << (Token { TokenType::START_TAG,
				StartTagToken { "tag_name",
						true,
						std::list<Attribute> {
								Attribute { "name1", "value1" },
								Attribute { "name2", "value2" }
						}
				}
		});

		std::string result = "";
		result += "TokenType type = TokenType::START_TAG\n";
		result += "TokenVariant token = ";
		result += "std::string tag_name = tag_name\n";
		result += "bool self_closing = 1\n";
		result += "std::list<Attribute> attributes = \"name1\":\"value1\", \"name2\":\"value2\", ";

		EXPECT_EQ(result, testStream.str());

	}
	{
		std::stringstream testStream;
		testStream << (Token { TokenType::END_TAG,
				EndTagToken { "tag_name",
						true,
						std::list<Attribute> {
								Attribute { "name1", "value1" },
								Attribute { "name2", "value2" }
						}
				}
		});

		std::string result = "";
		result += "TokenType type = TokenType::END_TAG\n";
		result += "TokenVariant token = ";
		result += "std::string tag_name = tag_name\n";
		result += "bool self_closing = 1\n";
		result += "std::list<Attribute> attributes = \"name1\":\"value1\", \"name2\":\"value2\", ";

		EXPECT_EQ(result, testStream.str());

	}
	{
		std::stringstream testStream;
		testStream << (Token { TokenType::COMMENT, CommentToken { "this is a comment" } });

		std::string result = "";
		result += "TokenType type = TokenType::COMMENT\n";
		result += "TokenVariant token = ";
		result += "std::string data = \"this is a comment\"";

		EXPECT_EQ(result, testStream.str());

	}

	{
		std::stringstream testStream;
		testStream << (Token { TokenType::CHARACTER, CharacterToken { U'\U00001234' } });

		std::string result = "";
		result += "TokenType type = TokenType::CHARACTER\n";
		result += "TokenVariant token = ";
		result += "char32_t data = U+00001234";

		EXPECT_EQ(result, testStream.str());

	}
	{
		std::stringstream testStream;
		testStream << (Token { TokenType::DOCTYPE, DOCTYPEToken { "name", "public_identifier", "system_identifier", true } });

		std::string result = "";
		result += "TokenType type = TokenType::DOCTYPE\n";
		result += "TokenVariant token = ";
		result += "std::string name = name\n";
		result += "std::string public_identifier = public_identifier\n";
		result += "std::string system_identifier = system_identifier\n";
		result += "bool force_quirks = 1";

		EXPECT_EQ(result, testStream.str());

	}

}

TEST(HTML_Parse_Tokenization_TokenizationTypes, TokenEquality) {
	EXPECT_EQ(Token(), Token());
	EXPECT_EQ((Token { TokenType::END_OF_FILE, EOFToken() }), (Token { TokenType::END_OF_FILE, EOFToken() }));
	EXPECT_NE((Token { TokenType::END_OF_FILE, EOFToken() }), (Token { TokenType::NO_TOKEN, EOFToken() }));
	EXPECT_NE((Token { TokenType::END_OF_FILE, EOFToken() }), (Token { TokenType::END_OF_FILE, NoToken() }));
	EXPECT_NE((Token { TokenType::END_OF_FILE, EOFToken() }), (Token { TokenType::NO_TOKEN, EOFToken() }));
	EXPECT_NE((Token { TokenType::END_OF_FILE, EOFToken() }), Token());
}

TEST(HTML_Parse_Tokenization_TokenizationTypes, STATESStreamWrite) {
	EXPECT_EQ("STATES::NULL_STATE", static_cast<std::stringstream&>(std::stringstream() << STATES::NULL_STATE).str());
	EXPECT_EQ("STATES::DATA", static_cast<std::stringstream&>(std::stringstream() << STATES::DATA).str());
	EXPECT_EQ("STATES::CHARACTER_REFERENCE_IN_DATA", static_cast<std::stringstream&>(std::stringstream() << STATES::CHARACTER_REFERENCE_IN_DATA).str());
	EXPECT_EQ("STATES::RCDATA", static_cast<std::stringstream&>(std::stringstream() << STATES::RCDATA).str());
	EXPECT_EQ("STATES::CHARACTER_REFERENCE_IN_RCDATA", static_cast<std::stringstream&>(std::stringstream() << STATES::CHARACTER_REFERENCE_IN_RCDATA).str());
	EXPECT_EQ("STATES::RAWTEXT", static_cast<std::stringstream&>(std::stringstream() << STATES::RAWTEXT).str());
	EXPECT_EQ("STATES::SCRIPT_DATA", static_cast<std::stringstream&>(std::stringstream() << STATES::SCRIPT_DATA).str());
	EXPECT_EQ("STATES::PLAINTEXT", static_cast<std::stringstream&>(std::stringstream() << STATES::PLAINTEXT).str());
	EXPECT_EQ("STATES::TAG_OPEN", static_cast<std::stringstream&>(std::stringstream() << STATES::TAG_OPEN).str());
	EXPECT_EQ("STATES::END_TAG_OPEN", static_cast<std::stringstream&>(std::stringstream() << STATES::END_TAG_OPEN).str());
	EXPECT_EQ("STATES::TAG_NAME", static_cast<std::stringstream&>(std::stringstream() << STATES::TAG_NAME).str());
	EXPECT_EQ("STATES::RCDATA_LESS_THAN_SIGN", static_cast<std::stringstream&>(std::stringstream() << STATES::RCDATA_LESS_THAN_SIGN).str());
	EXPECT_EQ("STATES::RCDATA_END_TAG_OPEN", static_cast<std::stringstream&>(std::stringstream() << STATES::RCDATA_END_TAG_OPEN).str());
	EXPECT_EQ("STATES::RCDATA_END_TAG_NAME", static_cast<std::stringstream&>(std::stringstream() << STATES::RCDATA_END_TAG_NAME).str());
	EXPECT_EQ("STATES::RAWTEXT_END_TAG_OPEN", static_cast<std::stringstream&>(std::stringstream() << STATES::RAWTEXT_END_TAG_OPEN).str());
	EXPECT_EQ("STATES::RAWTEXT_END_TAG_NAME", static_cast<std::stringstream&>(std::stringstream() << STATES::RAWTEXT_END_TAG_NAME).str());
	EXPECT_EQ("STATES::SCRIPT_DATA_LESS_THAN_SIGN", static_cast<std::stringstream&>(std::stringstream() << STATES::SCRIPT_DATA_LESS_THAN_SIGN).str());
	EXPECT_EQ("STATES::SCRIPT_DATA_END_TAG_NAME", static_cast<std::stringstream&>(std::stringstream() << STATES::SCRIPT_DATA_END_TAG_NAME).str());
	EXPECT_EQ("STATES::SCRIPT_DATA_ESCAPE_START", static_cast<std::stringstream&>(std::stringstream() << STATES::SCRIPT_DATA_ESCAPE_START).str());
	EXPECT_EQ("STATES::SCRIPT_DATA_ESCAPE_START_DASH", static_cast<std::stringstream&>(std::stringstream() << STATES::SCRIPT_DATA_ESCAPE_START_DASH).str());
	EXPECT_EQ("STATES::SCRIPT_DATA_ESCAPED", static_cast<std::stringstream&>(std::stringstream() << STATES::SCRIPT_DATA_ESCAPED).str());
	EXPECT_EQ("STATES::SCRIPT_DATA_ESCAPED_DASH", static_cast<std::stringstream&>(std::stringstream() << STATES::SCRIPT_DATA_ESCAPED_DASH).str());
	EXPECT_EQ("STATES::SCRIPT_DATA_ESCAPED_DASH_DASH", static_cast<std::stringstream&>(std::stringstream() << STATES::SCRIPT_DATA_ESCAPED_DASH_DASH).str());
	EXPECT_EQ("STATES::SCRIPT_DATA_ESCAPED_LESS_THAN_SIGN", static_cast<std::stringstream&>(std::stringstream() << STATES::SCRIPT_DATA_ESCAPED_LESS_THAN_SIGN).str());
	EXPECT_EQ("STATES::SCRIPT_DATA_ESCAPED_END_TAG_NAME", static_cast<std::stringstream&>(std::stringstream() << STATES::SCRIPT_DATA_ESCAPED_END_TAG_NAME).str());
	EXPECT_EQ("STATES::SCRIPT_DATA_DOUBLE_ESCAPE_START", static_cast<std::stringstream&>(std::stringstream() << STATES::SCRIPT_DATA_DOUBLE_ESCAPE_START).str());
	EXPECT_EQ("STATES::SCRIPT_DATA_DOUBLE_ESCAPED", static_cast<std::stringstream&>(std::stringstream() << STATES::SCRIPT_DATA_DOUBLE_ESCAPED).str());
	EXPECT_EQ("STATES::SCRIPT_DATA_DOUBLE_ESCAPED_DASH", static_cast<std::stringstream&>(std::stringstream() << STATES::SCRIPT_DATA_DOUBLE_ESCAPED_DASH).str());
	EXPECT_EQ("STATES::SCRIPT_DATA_DOUBLE_ESCAPED_DASH_DASH", static_cast<std::stringstream&>(std::stringstream() << STATES::SCRIPT_DATA_DOUBLE_ESCAPED_DASH_DASH).str());
	EXPECT_EQ("STATES::SCRIPT_DATA_DOUBLE_ESCAPED_LESS_THAN_SIGN", static_cast<std::stringstream&>(std::stringstream() << STATES::SCRIPT_DATA_DOUBLE_ESCAPED_LESS_THAN_SIGN).str());
	EXPECT_EQ("STATES::SCRIPT_DATA_DOUBLE_ESCAPE_END", static_cast<std::stringstream&>(std::stringstream() << STATES::SCRIPT_DATA_DOUBLE_ESCAPE_END).str());
	EXPECT_EQ("STATES::BEFORE_ATTRIBUTE", static_cast<std::stringstream&>(std::stringstream() << STATES::BEFORE_ATTRIBUTE).str());
	EXPECT_EQ("STATES::ATTRIBUTE_NAME", static_cast<std::stringstream&>(std::stringstream() << STATES::ATTRIBUTE_NAME).str());
	EXPECT_EQ("STATES::AFTER_ATTRIBUTE_NAME", static_cast<std::stringstream&>(std::stringstream() << STATES::AFTER_ATTRIBUTE_NAME).str());
	EXPECT_EQ("STATES::BEFORE_ATTRIBUTE_VALUE", static_cast<std::stringstream&>(std::stringstream() << STATES::BEFORE_ATTRIBUTE_VALUE).str());
	EXPECT_EQ("STATES::ATTRIBUTE_VALUE_DOUBLE_QUOTED", static_cast<std::stringstream&>(std::stringstream() << STATES::ATTRIBUTE_VALUE_DOUBLE_QUOTED).str());
	EXPECT_EQ("STATES::ATTRIBUTE_VALUE_SINGLE_QUOTED", static_cast<std::stringstream&>(std::stringstream() << STATES::ATTRIBUTE_VALUE_SINGLE_QUOTED).str());
	EXPECT_EQ("STATES::ATTRIBUTE_VALUE_UNQUOTED", static_cast<std::stringstream&>(std::stringstream() << STATES::ATTRIBUTE_VALUE_UNQUOTED).str());
	EXPECT_EQ("STATES::CHARACTER_REFERENCE_IN_ATTRIBUTE_VALUE", static_cast<std::stringstream&>(std::stringstream() << STATES::CHARACTER_REFERENCE_IN_ATTRIBUTE_VALUE).str());
	EXPECT_EQ("STATES::AFTER_ATTRIBUTE_QUOTED", static_cast<std::stringstream&>(std::stringstream() << STATES::AFTER_ATTRIBUTE_QUOTED).str());
	EXPECT_EQ("STATES::SELF_CLOSING_START_TAG", static_cast<std::stringstream&>(std::stringstream() << STATES::SELF_CLOSING_START_TAG).str());
	EXPECT_EQ("STATES::BOGUS_COMMENT", static_cast<std::stringstream&>(std::stringstream() << STATES::BOGUS_COMMENT).str());
	EXPECT_EQ("STATES::MARKUP_DECLARATION_OPEN", static_cast<std::stringstream&>(std::stringstream() << STATES::MARKUP_DECLARATION_OPEN).str());
	EXPECT_EQ("STATES::COMMENT_START", static_cast<std::stringstream&>(std::stringstream() << STATES::COMMENT_START).str());
	EXPECT_EQ("STATES::COMMENT_START_DASH", static_cast<std::stringstream&>(std::stringstream() << STATES::COMMENT_START_DASH).str());
	EXPECT_EQ("STATES::COMMENT", static_cast<std::stringstream&>(std::stringstream() << STATES::COMMENT).str());
	EXPECT_EQ("STATES::COMMENT_END_DASH", static_cast<std::stringstream&>(std::stringstream() << STATES::COMMENT_END_DASH).str());
	EXPECT_EQ("STATES::COMMENT_END", static_cast<std::stringstream&>(std::stringstream() << STATES::COMMENT_END).str());
	EXPECT_EQ("STATES::COMMENT_END_BANG", static_cast<std::stringstream&>(std::stringstream() << STATES::COMMENT_END_BANG).str());
	EXPECT_EQ("STATES::DOCTYPE", static_cast<std::stringstream&>(std::stringstream() << STATES::DOCTYPE).str());
	EXPECT_EQ("STATES::BEFORE_DOCTYPE_NAME", static_cast<std::stringstream&>(std::stringstream() << STATES::BEFORE_DOCTYPE_NAME).str());
	EXPECT_EQ("STATES::DOCTYPE_NAME", static_cast<std::stringstream&>(std::stringstream() << STATES::DOCTYPE_NAME).str());
	EXPECT_EQ("STATES::AFTER_DOCTYPE_NAME", static_cast<std::stringstream&>(std::stringstream() << STATES::AFTER_DOCTYPE_NAME).str());
	EXPECT_EQ("STATES::AFTER_DOCTYPE_PUBLIC_KEYWORD", static_cast<std::stringstream&>(std::stringstream() << STATES::AFTER_DOCTYPE_PUBLIC_KEYWORD).str());
	EXPECT_EQ("STATES::BEFORE_DOCTYPE_PUBLIC_IDENTIFIER", static_cast<std::stringstream&>(std::stringstream() << STATES::BEFORE_DOCTYPE_PUBLIC_IDENTIFIER).str());
	EXPECT_EQ("STATES::DOCTYPE_PUBLIC_IDENTIFIER_DOUBLE_QUOTED", static_cast<std::stringstream&>(std::stringstream() << STATES::DOCTYPE_PUBLIC_IDENTIFIER_DOUBLE_QUOTED).str());
	EXPECT_EQ("STATES::DOCTYPE_PUBLIC_IDENTIFIER_SINGLE_QUOTED", static_cast<std::stringstream&>(std::stringstream() << STATES::DOCTYPE_PUBLIC_IDENTIFIER_SINGLE_QUOTED).str());
	EXPECT_EQ("STATES::AFTER_DOCTYPE_PUBLIC_IDENTIFIER", static_cast<std::stringstream&>(std::stringstream() << STATES::AFTER_DOCTYPE_PUBLIC_IDENTIFIER).str());
	EXPECT_EQ("STATES::BETWEEN_DOCTYPE_PUBLIC_AND_SYSTEM_IDENTIFIERS", static_cast<std::stringstream&>(std::stringstream() << STATES::BETWEEN_DOCTYPE_PUBLIC_AND_SYSTEM_IDENTIFIERS).str());
	EXPECT_EQ("STATES::AFTER_DOCTYPE_SYSTEM_KEYWORD", static_cast<std::stringstream&>(std::stringstream() << STATES::AFTER_DOCTYPE_SYSTEM_KEYWORD).str());
	EXPECT_EQ("STATES::BEFORE_DOCTYPE_SYSTEM_IDENTIFIER", static_cast<std::stringstream&>(std::stringstream() << STATES::BEFORE_DOCTYPE_SYSTEM_IDENTIFIER).str());
	EXPECT_EQ("STATES::DOCTYPE_SYSTEM_IDENTIFIER_DOUBLE_QUOTED", static_cast<std::stringstream&>(std::stringstream() << STATES::DOCTYPE_SYSTEM_IDENTIFIER_DOUBLE_QUOTED).str());
	EXPECT_EQ("STATES::DOCTYPE_SYSTEM_IDENTIFIER_SINGLE_QUOTED", static_cast<std::stringstream&>(std::stringstream() << STATES::DOCTYPE_SYSTEM_IDENTIFIER_SINGLE_QUOTED).str());
	EXPECT_EQ("STATES::AFTER_DOCTYPE_SYSTEM_IDENTIFIER", static_cast<std::stringstream&>(std::stringstream() << STATES::AFTER_DOCTYPE_SYSTEM_IDENTIFIER).str());
	EXPECT_EQ("STATES::BOGUS_DOCTYPE", static_cast<std::stringstream&>(std::stringstream() << STATES::BOGUS_DOCTYPE).str());
	EXPECT_EQ("STATES::CDATA_SECTION", static_cast<std::stringstream&>(std::stringstream() << STATES::CDATA_SECTION).str());
}

TEST(HTML_Parse_Tokenization_TokenizationTypes, StateDataStreamWrite) {
	{
		using namespace std::string_literals;
		std::stringstream testStream;
		testStream << (StateData());
		std::string result = "";
		result += "STATES state = STATES::NULL_STATE\n";
		result += "std::u32string string = \"\"\n";
		result += "size_t pos = 0\n";
		result += "char buf = '\0'\n"s;
		result += "bool parser_pause_flag = 0\n";
		result += "size_t script_nesting_level = 0\n";
		result += "std::list<Token> tokens = {\n";
		result += "}";
		EXPECT_EQ(result, testStream.str());
	}
	{
		std::stringstream testStream;
		testStream << (StateData {
				STATES::DATA,
				U"test string",
				5,
				'a',
				true,
				6,
				std::list<Token> {
						Token { TokenType::END_OF_FILE, EOFToken() },
						Token { TokenType::NO_TOKEN, NoToken() },
						Token { TokenType::START_TAG,
								StartTagToken { "tag_name",
										true,
										std::list<Attribute> {
												Attribute { "name1", "value1" },
												Attribute { "name2", "value2" }
										}
								}
						}
				}
		});
		std::string result = "";
		result += "STATES state = STATES::DATA\n";
		result += "std::u32string string = \"test string\"\n";
		result += "size_t pos = 5\n";
		result += "char buf = 'a'\n";
		result += "bool parser_pause_flag = 1\n";
		result += "size_t script_nesting_level = 6\n";
		result += "std::list<Token> tokens = {\n";

		result += "Token { TokenType type = TokenType::END_OF_FILE\n";
		result += "TokenVariant token = \\(EOF)}, \n";

		result += "Token { TokenType type = TokenType::NO_TOKEN\n";
		result += "TokenVariant token = No Token!}, \n";

		result += "Token { TokenType type = TokenType::START_TAG\n";
		result += "TokenVariant token = std::string tag_name = tag_name\n";
		result += "bool self_closing = 1\n";
		result += "std::list<Attribute> attributes = \"name1\":\"value1\", \"name2\":\"value2\", ";
		result += "}, \n";
		result += "}";
		EXPECT_EQ(result, testStream.str());
	}

}

TEST(HTML_Parse_Tokenization_TokenizationTypes, StateDataEquality) {
	EXPECT_EQ(StateData(), StateData());
	EXPECT_EQ((StateData {
			STATES::DATA,
			U"test string",
			5,
			'a',
			true,
			6,
			std::list<Token> {
					Token { TokenType::END_OF_FILE, EOFToken() },
					Token { TokenType::NO_TOKEN, NoToken() },
					Token { TokenType::START_TAG,
							StartTagToken { "tag_name",
								true,
								std::list<Attribute> {
											Attribute { "name1", "value1" },
											Attribute { "name2", "value2" }
								}
						}
					}
			}
	}), (StateData {
			STATES::DATA,
			U"test string",
			5,
			'a',
			true,
			6,
			std::list<Token> {
					Token { TokenType::END_OF_FILE, EOFToken() },
					Token { TokenType::NO_TOKEN, NoToken() },
					Token { TokenType::START_TAG,
							StartTagToken { "tag_name",
									true,
									std::list<Attribute> {
											Attribute { "name1", "value1" },
											Attribute { "name2", "value2" }
									}
							}
					}
			}
	}));
	EXPECT_NE((StateData {
			STATES::DATA,
			U"test string",
			5,
			'a',
			true,
			6,
			std::list<Token> {
					Token { TokenType::END_OF_FILE, EOFToken() },
					Token { TokenType::NO_TOKEN, NoToken() },
					Token { TokenType::START_TAG,
							StartTagToken { "tag_name",
									true,
									std::list<Attribute> {
											Attribute { "name1", "value1" },
											Attribute { "name2", "value2" }
									}
							}
					}
			}
	}), (StateData()));
	EXPECT_NE((StateData {
			STATES::DATA,
			U"test string",
			5,
			'a',
			true,
			6,
			std::list<Token> {
					Token { TokenType::END_OF_FILE, EOFToken() },
					Token { TokenType::NO_TOKEN, NoToken() },
					Token { TokenType::START_TAG,
							StartTagToken { "tag_name",
									true,
									std::list<Attribute> {
											Attribute { "name1", "value1" },
											Attribute { "name2", "value2" }
									}
							}
					}
			}
	}), (StateData {
			STATES::DATA,
			U"test string",
			5,
			'a',
			true,
			6,
			std::list<Token> {
					Token { TokenType::END_OF_FILE, EOFToken() },
					Token { TokenType::NO_TOKEN, NoToken() },
					Token { TokenType::START_TAG,
							StartTagToken { "tag_name",
									true,
									std::list<Attribute> {
											Attribute { "name1", "value1" },
									}
							}
					}
			}
	}));
}

} /* namespace Tokenization */
} /* namespace Parse */
} /* namespace HTML */
