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

#include <list>
#include <string>
#include <variant>

#include <HTML/HTMLTypes.hpp>

#define EOF32 ((char32_t) 0xFFFFFFFF)
#define EOF16 ((char16_t) 0xFFFF)
#define EOF8  ((char) 0xFF)

#define EOF32STRING U"\xFF\xFF\xFF\xFF"

namespace HTML {
namespace Parse {
namespace Tokenization {

class DOCTYPEToken {
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

class TagToken {
	public:
		enum class TagType {
			NONE,
			START,
			END
		};

	public:
		TagToken():
				type(TagType::NONE), tag_name(U""), self_closing(false), attributes( {}) {
		}
		explicit TagToken(const TagType& type, const std::u32string& tag_name = U"", const bool& self_closing = false, const std::list<Attribute>& attributes= {}):
				type(type), tag_name(tag_name), self_closing(self_closing), attributes(attributes) {
		}

	public:
		TagType type;
		std::u32string tag_name;
		bool self_closing;
		std::list<Attribute> attributes;
};

class StartTagToken: public TagToken {
	public:
		StartTagToken() :
				TagToken() {
		}
		explicit StartTagToken(const std::u32string& tag_name, const bool& self_closing, const std::list<Attribute>& attributes) :
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
		explicit EndTagToken(const std::u32string& tag_name, const bool& self_closing, const std::list<Attribute>& attributes) :
				TagToken(TagType::END, tag_name, self_closing, attributes) {
		}
};
::std::ostream& operator<<(::std::ostream& os, const EndTagToken& end_tag_Token);
bool operator==(const EndTagToken& lhs, const EndTagToken& rhs);
inline bool operator!=(const EndTagToken& lhs, const EndTagToken& rhs) {
	return !(lhs == rhs);
}

class CharacterToken {
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

class CommentToken {
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

class EOFToken {
	public:
		static constexpr char string[] = "\\(EOF)";
};
::std::ostream& operator<<(::std::ostream& os, const EOFToken& eof_token);
bool operator==(const EOFToken& lhs, const EOFToken& rhs);
inline bool operator!=(const EOFToken& lhs, const EOFToken& rhs) {
	return !(lhs == rhs);
}

class NoToken {
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

} /* namespace Tokenization */
} /* namespace Parse */
} /* namespace HTML */

#endif /* SRC_HTML_PARSE_TOKENIZATION_TOKENIZATIONTYPES_HPP_ */
