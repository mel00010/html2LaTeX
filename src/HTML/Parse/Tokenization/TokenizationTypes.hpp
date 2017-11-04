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


namespace HTML {
namespace Parse {
namespace Tokenization {

class DOCTYPEToken {
	public:
		std::u32string name = U"\xFF\xFF\xFF\xFF";
		std::u32string public_identifier = U"\xFF\xFF\xFF\xFF";
		std::u32string system_identifier = U"\xFF\xFF\xFF\xFF";
		bool force_quirks = false;
};
::std::ostream& operator<<(::std::ostream& os, const DOCTYPEToken& doctype_token);
bool operator==(const DOCTYPEToken& lhs, const DOCTYPEToken& rhs);
inline bool operator!=(const DOCTYPEToken& lhs, const DOCTYPEToken& rhs) {
	return !(lhs == rhs);
}

class StartTagToken {
	public:
		std::u32string tag_name = U"";
		bool self_closing = false;
		std::list<Attribute> attributes = { };
};
::std::ostream& operator<<(::std::ostream& os, const StartTagToken& start_tag_Token);
bool operator==(const StartTagToken& lhs, const StartTagToken& rhs);
inline bool operator!=(const StartTagToken& lhs, const StartTagToken& rhs) {
	return !(lhs == rhs);
}

class EndTagToken {
	public:
		std::u32string tag_name = U"";
		bool self_closing = false;
		std::list<Attribute> attributes = { };
};
::std::ostream& operator<<(::std::ostream& os, const EndTagToken& end_tag_Token);
bool operator==(const EndTagToken& lhs, const EndTagToken& rhs);
inline bool operator!=(const EndTagToken& lhs, const EndTagToken& rhs) {
	return !(lhs == rhs);
}

class CharacterToken {
	public:
		char32_t data = EOF;
};
::std::ostream& operator<<(::std::ostream& os, const CharacterToken& character_token);
bool operator==(const CharacterToken& lhs, const CharacterToken& rhs);
inline bool operator!=(const CharacterToken& lhs, const CharacterToken& rhs) {
	return !(lhs == rhs);
}

class CommentToken {
	public:
		std::u32string data = U"";
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
		TokenType type = TokenType::NO_TOKEN;
		TokenVariant token = NoToken();

};
::std::ostream& operator<<(::std::ostream& os, const Token& token);
bool operator==(const Token& lhs, const Token& rhs);
inline bool operator!=(const Token& lhs, const Token& rhs) {
	return !(lhs == rhs);
}

struct EmmittedTokens {
		Token first;
		Token second;
};
::std::ostream& operator<<(::std::ostream& os, const EmmittedTokens& tokens);
bool operator==(const EmmittedTokens& lhs, const EmmittedTokens& rhs);
inline bool operator!=(const EmmittedTokens& lhs, const EmmittedTokens& rhs) {
	return !(lhs == rhs);
}

} /* namespace Tokenization */
} /* namespace Parse */
} /* namespace HTML */



#endif /* SRC_HTML_PARSE_TOKENIZATION_TOKENIZATIONTYPES_HPP_ */
