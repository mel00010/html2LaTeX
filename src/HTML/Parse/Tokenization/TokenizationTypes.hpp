/*******************************************************************************
 * TokenizationTypes.hpp
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
#ifndef SRC_HTML_PARSE_TOKENIZATION_TOKENIZATIONTYPES_HPP_
#define SRC_HTML_PARSE_TOKENIZATION_TOKENIZATIONTYPES_HPP_

#include <string>
#include <variant>
#include <vector>

#include <HTML/HTMLTypes.hpp>

#define EOF32 ((char32_t) 0xFFFFFFFF)
#define EOF16 ((char16_t) 0xFFFF)
#define EOF8  ((char) 0xFF)

#define EOF32STRING U"\xFF\xFF\xFF\xFF"

#define NO_CHARACTER ((char32_t) 0xFFFFFFFE)


namespace HTML {
namespace Parse {
namespace Tokenization {

class TokenBase {
};
class DOCTYPEToken: public TokenBase {
	public:
		explicit DOCTYPEToken(const std::u32string& name = EOF32STRING, const std::u32string& public_identifier = EOF32STRING,
				const std::u32string& system_identifier = EOF32STRING, const bool& force_quirks = false) :
				name(name), public_identifier(public_identifier), system_identifier(system_identifier), force_quirks(force_quirks) {
		}
	public:
		std::u32string name;
		std::u32string public_identifier;
		std::u32string system_identifier;
		bool force_quirks;
};
::std::ostream& operator<<(::std::ostream& os, const DOCTYPEToken& doctype_token);
bool operator==(const DOCTYPEToken& lhs, const DOCTYPEToken& rhs);
inline bool operator!=(const DOCTYPEToken& lhs, const DOCTYPEToken& rhs) {
	return !(lhs == rhs);
}

class TagToken: public TokenBase {
	public:
		enum class TagType {
			NONE,
			START,
			END
		};

	public:
		TagToken() : type(TagType::NONE), tag_name(U""), self_closing(false), attributes( {}) {}
		explicit TagToken(const TagType& type, const std::u32string& tag_name = U"", const bool& self_closing = false, const std::vector<Attribute>& attributes= {}):
				type(type), tag_name(tag_name), self_closing(self_closing), attributes(attributes) {
		}

	public:
		TagType type;
		std::u32string tag_name;
		bool self_closing;
		std::vector<Attribute> attributes;
};

class StartTagToken: public TagToken {
	public:
		StartTagToken() :
				TagToken() {
		}
		explicit StartTagToken(const std::u32string& tag_name, const bool& self_closing, const std::vector<Attribute>& attributes) :
				TagToken(TagType::START, tag_name, self_closing, attributes) {
		}
};
::std::ostream& operator<<(::std::ostream& os, const StartTagToken& start_tag_Token);
bool operator==(const StartTagToken& lhs, const StartTagToken& rhs);
inline bool operator!=(const StartTagToken& lhs, const StartTagToken& rhs) {
	return !(lhs == rhs);
}

class EndTagToken: public TagToken {
	public:
		EndTagToken() :
				TagToken() {
		}
		explicit EndTagToken(const std::u32string& tag_name, const bool& self_closing, const std::vector<Attribute>& attributes) :
				TagToken(TagType::END, tag_name, self_closing, attributes) {
		}
};
::std::ostream& operator<<(::std::ostream& os, const EndTagToken& end_tag_Token);
bool operator==(const EndTagToken& lhs, const EndTagToken& rhs);
inline bool operator!=(const EndTagToken& lhs, const EndTagToken& rhs) {
	return !(lhs == rhs);
}

class CharacterToken: public TokenBase {
	public:
		CharacterToken(const char32_t& data = EOF32) :
				data(data) {
		}

	public:
		char32_t data;
};
::std::ostream& operator<<(::std::ostream& os, const CharacterToken& character_token);
bool operator==(const CharacterToken& lhs, const CharacterToken& rhs);
inline bool operator!=(const CharacterToken& lhs, const CharacterToken& rhs) {
	return !(lhs == rhs);
}

class CommentToken: public TokenBase {
	public:
		CommentToken(const std::u32string& data = U"") : data(data) {}

	public:
		std::u32string data;
	};
::std::ostream& operator<<(::std::ostream& os, const CommentToken& comment_token);
bool operator==(const CommentToken& lhs, const CommentToken& rhs);
inline bool operator!=(const CommentToken& lhs, const CommentToken& rhs) {
	return !(lhs == rhs);
}

class EOFToken: public TokenBase {
	public:
		static constexpr char string[] = "\\(EOF)";
};
::std::ostream& operator<<(::std::ostream& os, const EOFToken& eof_token);
bool operator==(const EOFToken& lhs, const EOFToken& rhs);
inline bool operator!=(const EOFToken& lhs, const EOFToken& rhs) {
	return !(lhs == rhs);
}

class NoToken: public TokenBase {
	public:
		static constexpr char string[] = "No Token!";
};
::std::ostream& operator<<(::std::ostream& os, const NoToken& no_token);
bool operator==(const NoToken& lhs, const NoToken& rhs);
inline bool operator!=(const NoToken& lhs, const NoToken& rhs) {
	return !(lhs == rhs);
}

enum class TokenType {
	NO_TOKEN,
	DOCTYPE,
	START_TAG,
	END_TAG,
	COMMENT,
	CHARACTER,
	END_OF_FILE
};
::std::ostream& operator<<(::std::ostream& os, const TokenType& token_type);

typedef std::variant<NoToken, DOCTYPEToken, StartTagToken, EndTagToken, CharacterToken, CommentToken, EOFToken> TokenVariant;

class Token {
	public:
		Token(const NoToken& token) :
				type(TokenType::NO_TOKEN), token(token) {
		}
		Token(const DOCTYPEToken& token) :
				type(TokenType::DOCTYPE), token(token) {
		}
		Token(const StartTagToken& token) :
				type(TokenType::START_TAG), token(token) {
		}
		Token(const EndTagToken& token) :
				type(TokenType::END_TAG), token(token) {
		}
		Token(const CommentToken& token) :
				type(TokenType::COMMENT), token(token) {
		}
		Token(const CharacterToken& token) :
				type(TokenType::CHARACTER), token(token) {
		}
		Token(const EOFToken& token) :
				type(TokenType::END_OF_FILE), token(token) {
		}
		Token(const Token& token) :
				type(token.type), token(token.token) {
		}
		Token() :
				type(TokenType::NO_TOKEN), token(NoToken()) {
		}
	public:
		TokenType type;
		TokenVariant token;
};
::std::ostream& operator<<(::std::ostream& os, const Token& token);
bool operator==(const Token& lhs, const Token& rhs);
inline bool operator!=(const Token& lhs, const Token& rhs) {
	return !(lhs == rhs);
}

struct TokenPair {
		Token first;
		Token second;
};
::std::ostream& operator<<(::std::ostream& os, const TokenPair& tokens);
bool operator==(const TokenPair& lhs, const TokenPair& rhs);
inline bool operator!=(const TokenPair& lhs, const TokenPair& rhs) {
	return !(lhs == rhs);
}

/**
 * @brief Enum specifying the states in the tokenizer state machine
 * @details Section 8.2.4 in the W3C HTML5 specification
 */
enum State {
	NULL_STATE,                                   //!< NULL_STATE @brief Used to indicate a null state
	DATA,                                         //!< DATA @brief Section 8.2.4.1 in the W3C HTML5 specification
	CHARACTER_REFERENCE_IN_DATA,                  //!< CHARACTER_REFERENCE_IN_DATA @brief Section 8.2.4.2 in the W3C HTML5 specification
	RCDATA,                                       //!< RCDATA @brief Section 8.2.4.3 in the W3C HTML5 specification
	CHARACTER_REFERENCE_IN_RCDATA,                //!< CHARACTER_REFERENCE_IN_RCDATA @brief Section 8.2.4.4 in the W3C HTML5 specification
	RAWTEXT,                                      //!< RAWTEXT @brief Section 8.2.4.5 in the W3C HTML5 specification
	SCRIPT_DATA,                                  //!< SCRIPT_DATA @brief Section 8.2.4.6 in the W3C HTML5 specification
	PLAINTEXT,                                    //!< PLAINTEXT @brief Section 8.2.4.7 in the W3C HTML5 specification
	TAG_OPEN,                                     //!< TAG_OPEN @brief Section 8.2.4.8 in the W3C HTML5 specification
	END_TAG_OPEN,                                 //!< END_TAG_OPEN @brief Section 8.2.4.9 in the W3C HTML5 specification
	TAG_NAME,                                     //!< TAG_NAME @brief Section 8.2.4.10 in the W3C HTML5 specification
	RCDATA_LESS_THAN_SIGN,                        //!< RCDATA_LESS_THAN_SIGN @brief Section 8.2.4.11 in the W3C HTML5 specification
	RCDATA_END_TAG_OPEN,                          //!< RCDATA_END_TAG_OPEN @brief Section 8.2.4.12 in the W3C HTML5 specification
	RCDATA_END_TAG_NAME,                          //!< RCDATA_END_TAG_NAME @brief Section 8.2.4.13 in the W3C HTML5 specification
	RAWTEXT_LESS_THAN_SIGN,                       //!< RAWTEXT_LESS_THAN_SIGN @brief Section 8.2.4.14 in the W3C HTML5 specification
	RAWTEXT_END_TAG_OPEN,                         //!< RAWTEXT_END_TAG_OPEN @brief Section 8.2.4.15 in the W3C HTML5 specification
	RAWTEXT_END_TAG_NAME,                         //!< RAWTEXT_END_TAG_NAME @brief Section 8.2.4.16 in the W3C HTML5 specification
	SCRIPT_DATA_LESS_THAN_SIGN,                   //!< SCRIPT_DATA_LESS_THAN_SIGN @brief Section 8.2.4.17 in the W3C HTML5 specification
	SCRIPT_DATA_END_TAG_OPEN,                     //!< SCRIPT_DATA_END_TAG_OPEN @brief Section 8.2.4.18 in the W3C HTML5 specification
	SCRIPT_DATA_END_TAG_NAME,                     //!< SCRIPT_DATA_END_TAG_NAME @brief Section 8.2.4.19 in the W3C HTML5 specification
	SCRIPT_DATA_ESCAPE_START,                     //!< SCRIPT_DATA_ESCAPE_START @brief Section 8.2.4.20 in the W3C HTML5 specification
	SCRIPT_DATA_ESCAPE_START_DASH,                //!< SCRIPT_DATA_ESCAPE_START_DASH @brief Section 8.2.4.21 in the W3C HTML5 specification
	SCRIPT_DATA_ESCAPED,                          //!< SCRIPT_DATA_ESCAPED @brief Section 8.2.4.22 in the W3C HTML5 specification
	SCRIPT_DATA_ESCAPED_DASH,                     //!< SCRIPT_DATA_ESCAPED_DASH @brief Section 8.2.4.23 in the W3C HTML5 specification
	SCRIPT_DATA_ESCAPED_DASH_DASH,                //!< SCRIPT_DATA_ESCAPED_DASH_DASH @brief Section 8.2.4.24 in the W3C HTML5 specification
	SCRIPT_DATA_ESCAPED_LESS_THAN_SIGN,           //!< SCRIPT_DATA_ESCAPED_LESS_THAN_SIGN @brief Section 8.2.4.25 in the W3C HTML5 specification
	SCRIPT_DATA_ESCAPED_END_TAG_OPEN,             //!< SCRIPT_DATA_ESCAPED_END_TAG_NAME @brief Section 8.2.4.26 in the W3C HTML5 specification
	SCRIPT_DATA_ESCAPED_END_TAG_NAME,             //!< SCRIPT_DATA_ESCAPED_END_TAG_NAME @brief Section 8.2.4.27 in the W3C HTML5 specification
	SCRIPT_DATA_DOUBLE_ESCAPE_START,              //!< SCRIPT_DATA_DOUBLE_ESCAPE_START @brief Section 8.2.4.28 in the W3C HTML5 specification
	SCRIPT_DATA_DOUBLE_ESCAPED,                   //!< SCRIPT_DATA_DOUBLE_ESCAPED @brief Section 8.2.4.29 in the W3C HTML5 specification
	SCRIPT_DATA_DOUBLE_ESCAPED_DASH,              //!< SCRIPT_DATA_DOUBLE_ESCAPED_DASH @brief Section 8.2.4.30 in the W3C HTML5 specification
	SCRIPT_DATA_DOUBLE_ESCAPED_DASH_DASH,         //!< SCRIPT_DATA_DOUBLE_ESCAPED_DASH_DASH @brief Section 8.2.4.31 in the W3C HTML5 specification
	SCRIPT_DATA_DOUBLE_ESCAPED_LESS_THAN_SIGN,    //!< SCRIPT_DATA_DOUBLE_ESCAPED_LESS_THAN_SIGN @brief Section 8.2.4.32 in the W3C HTML5 specification
	SCRIPT_DATA_DOUBLE_ESCAPE_END,                //!< SCRIPT_DATA_DOUBLE_ESCAPE_END @brief Section 8.2.4.33 in the W3C HTML5 specification
	BEFORE_ATTRIBUTE_NAME,                        //!< BEFORE_ATTRIBUTE_NAME @brief Section 8.2.4.34 in the W3C HTML5 specification
	ATTRIBUTE_NAME,                               //!< ATTRIBUTE_NAME @brief Section 8.2.4.35 in the W3C HTML5 specification
	AFTER_ATTRIBUTE_NAME,                         //!< AFTER_ATTRIBUTE_NAME @brief Section 8.2.4.36 in the W3C HTML5 specification
	BEFORE_ATTRIBUTE_VALUE,                       //!< BEFORE_ATTRIBUTE_VALUE @brief Section 8.2.4.37 in the W3C HTML5 specification
	ATTRIBUTE_VALUE_DOUBLE_QUOTED,                //!< ATTRIBUTE_VALUE_DOUBLE_QUOTED @brief Section 8.2.4.38 in the W3C HTML5 specification
	ATTRIBUTE_VALUE_SINGLE_QUOTED,                //!< ATTRIBUTE_VALUE_SINGLE_QUOTED @brief Section 8.2.4.39 in the W3C HTML5 specification
	ATTRIBUTE_VALUE_UNQUOTED,                     //!< ATTRIBUTE_VALUE_UNQUOTED @brief Section 8.2.4.40 in the W3C HTML5 specification
	CHARACTER_REFERENCE_IN_ATTRIBUTE_VALUE,       //!< CHARACTER_REFERENCE_IN_ATTRIBUTE_VALUE @brief Section 8.2.4.41 in the W3C HTML5 specification
	AFTER_ATTRIBUTE_QUOTED,                       //!< AFTER_ATTRIBUTE_QUOTED @brief Section 8.2.4.42 in the W3C HTML5 specification
	SELF_CLOSING_START_TAG,                       //!< SELF_CLOSING_START_TAG @brief Section 8.2.4.43 in the W3C HTML5 specification
	BOGUS_COMMENT,                                //!< BOGUS_COMMENT @brief Section 8.2.4.44 in the W3C HTML5 specification
	MARKUP_DECLARATION_OPEN,                      //!< MARKUP_DECLARATION_OPEN @brief Section 8.2.4.45 in the W3C HTML5 specification
	COMMENT_START,                                //!< COMMENT_START @brief Section 8.2.4.46 in the W3C HTML5 specification
	COMMENT_START_DASH,                           //!< COMMENT_START_DASH @brief Section 8.2.4.47 in the W3C HTML5 specification
	COMMENT,                                      //!< COMMENT @brief Section 8.2.4.48 in the W3C HTML5 specification
	COMMENT_END_DASH,                             //!< COMMENT_END_DASH @brief Section 8.2.4.49 in the W3C HTML5 specification
	COMMENT_END,                                  //!< COMMENT_END @brief Section 8.2.4.50 in the W3C HTML5 specification
	COMMENT_END_BANG,                             //!< COMMENT_END_BANG @brief Section 8.2.4.51 in the W3C HTML5 specification
	DOCTYPE,                                      //!< DOCTYPE @brief Section 8.2.4.52 in the W3C HTML5 specification
	BEFORE_DOCTYPE_NAME,                          //!< BEFORE_DOCTYPE_NAME @brief Section 8.2.4.53 in the W3C HTML5 specification
	DOCTYPE_NAME,                                 //!< DOCTYPE_NAME @brief Section 8.2.4.54 in the W3C HTML5 specification
	AFTER_DOCTYPE_NAME,                           //!< AFTER_DOCTYPE_NAME @brief Section 8.2.4.55 in the W3C HTML5 specification
	AFTER_DOCTYPE_PUBLIC_KEYWORD,                 //!< AFTER_DOCTYPE_PUBLIC_KEYWORD @brief Section 8.2.4.56 in the W3C HTML5 specification
	BEFORE_DOCTYPE_PUBLIC_IDENTIFIER,             //!< BEFORE_DOCTYPE_PUBLIC_IDENTIFIER @brief Section 8.2.4.57 in the W3C HTML5 specification
	DOCTYPE_PUBLIC_IDENTIFIER_DOUBLE_QUOTED,      //!< DOCTYPE_PUBLIC_IDENTIFIER_DOUBLE_QUOTED @brief Section 8.2.4.58 in the W3C HTML5 specification
	DOCTYPE_PUBLIC_IDENTIFIER_SINGLE_QUOTED,      //!< DOCTYPE_PUBLIC_IDENTIFIER_SINGLE_QUOTED @brief Section 8.2.4.59 in the W3C HTML5 specification
	AFTER_DOCTYPE_PUBLIC_IDENTIFIER,              //!< AFTER_DOCTYPE_PUBLIC_IDENTIFIER @brief Section 8.2.4.60 in the W3C HTML5 specification
	BETWEEN_DOCTYPE_PUBLIC_AND_SYSTEM_IDENTIFIERS,//!< BETWEEN_DOCTYPE_PUBLIC_AND_SYSTEM_IDENTIFIERS @brief Section 8.2.4.61 in the W3C HTML5 specification
	AFTER_DOCTYPE_SYSTEM_KEYWORD,                 //!< AFTER_DOCTYPE_SYSTEM_KEYWORD @brief Section 8.2.4.62 in the W3C HTML5 specification
	BEFORE_DOCTYPE_SYSTEM_IDENTIFIER,             //!< BEFORE_DOCTYPE_SYSTEM_IDENTIFIER @brief Section 8.2.4.63 in the W3C HTML5 specification
	DOCTYPE_SYSTEM_IDENTIFIER_DOUBLE_QUOTED,      //!< DOCTYPE_SYSTEM_IDENTIFIER_DOUBLE_QUOTED @brief Section 8.2.4.64 in the W3C HTML5 specification
	DOCTYPE_SYSTEM_IDENTIFIER_SINGLE_QUOTED,      //!< DOCTYPE_SYSTEM_IDENTIFIER_SINGLE_QUOTED @brief Section 8.2.4.65 in the W3C HTML5 specification
	AFTER_DOCTYPE_SYSTEM_IDENTIFIER,              //!< AFTER_DOCTYPE_SYSTEM_IDENTIFIER @brief Section 8.2.4.66 in the W3C HTML5 specification
	BOGUS_DOCTYPE,                                //!< BOGUS_DOCTYPE @brief Section 8.2.4.67 in the W3C HTML5 specification
	CDATA_SECTION                                 //!< CDATA_SECTION @brief Section 8.2.4.68 in the W3C HTML5 specification
};

::std::ostream& operator<<(::std::ostream& os, const State& state);

} /* namespace Tokenization */
} /* namespace Parse */
} /* namespace HTML */

#endif /* SRC_HTML_PARSE_TOKENIZATION_TOKENIZATIONTYPES_HPP_ */
