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
		std::string name = "\0xFF";
		std::string public_identifier = "\0xFF";
		std::string system_identifier = "\0xFF";
		bool force_quirks = false;
};
::std::ostream& operator<<(::std::ostream& os, const DOCTYPEToken& doctype_token);
bool operator==(const DOCTYPEToken& lhs, const DOCTYPEToken& rhs);
inline bool operator!=(const DOCTYPEToken& lhs, const DOCTYPEToken& rhs) {
	return !(lhs == rhs);
}

class StartTagToken {
	public:
		std::string tag_name = "";
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
		std::string tag_name = "";
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
		std::string data = "";
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

class Token {
	public:
		TokenType type = TokenType::NO_TOKEN;
		std::variant<NoToken, DOCTYPEToken, StartTagToken, EndTagToken, CharacterToken, CommentToken, EOFToken> token = NoToken();

};
::std::ostream& operator<<(::std::ostream& os, const Token& token);
bool operator==(const Token& lhs, const Token& rhs);
inline bool operator!=(const Token& lhs, const Token& rhs) {
	return !(lhs == rhs);
}

enum class STATES {
	NULL_STATE,
	DATA,
	CHARACTER_REFERENCE_IN_DATA,
	RCDATA,
	CHARACTER_REFERENCE_IN_RCDATA,
	RAWTEXT,
	SCRIPT_DATA,
	PLAINTEXT,
	TAG_OPEN,
	END_TAG_OPEN,
	TAG_NAME,
	RCDATA_LESS_THAN_SIGN,
	RCDATA_END_TAG_OPEN,
	RCDATA_END_TAG_NAME,
	RAWTEXT_END_TAG_OPEN,
	RAWTEXT_END_TAG_NAME,
	SCRIPT_DATA_LESS_THAN_SIGN,
	SCRIPT_DATA_END_TAG_OPEN,
	SCRIPT_DATA_END_TAG_NAME,
	SCRIPT_DATA_ESCAPE_START,
	SCRIPT_DATA_ESCAPE_START_DASH,
	SCRIPT_DATA_ESCAPED,
	SCRIPT_DATA_ESCAPED_DASH,
	SCRIPT_DATA_ESCAPED_DASH_DASH,
	SCRIPT_DATA_ESCAPED_LESS_THAN_SIGN,
	SCRIPT_DATA_ESCAPED_END_TAG_NAME,
	SCRIPT_DATA_DOUBLE_ESCAPE_START,
	SCRIPT_DATA_DOUBLE_ESCAPED,
	SCRIPT_DATA_DOUBLE_ESCAPED_DASH,
	SCRIPT_DATA_DOUBLE_ESCAPED_DASH_DASH,
	SCRIPT_DATA_DOUBLE_ESCAPED_LESS_THAN_SIGN,
	SCRIPT_DATA_DOUBLE_ESCAPE_END,
	BEFORE_ATTRIBUTE,
	ATTRIBUTE_NAME,
	AFTER_ATTRIBUTE_NAME,
	BEFORE_ATTRIBUTE_VALUE,
	ATTRIBUTE_VALUE_DOUBLE_QUOTED,
	ATTRIBUTE_VALUE_SINGLE_QUOTED,
	ATTRIBUTE_VALUE_UNQUOTED,
	CHARACTER_REFERENCE_IN_ATTRIBUTE_VALUE,
	AFTER_ATTRIBUTE_QUOTED,
	SELF_CLOSING_START_TAG,
	BOGUS_COMMENT,
	MARKUP_DECLARATION_OPEN,
	COMMENT_START,
	COMMENT_START_DASH,
	COMMENT,
	COMMENT_END_DASH,
	COMMENT_END,
	COMMENT_END_BANG,
	DOCTYPE,
	BEFORE_DOCTYPE_NAME,
	DOCTYPE_NAME,
	AFTER_DOCTYPE_NAME,
	AFTER_DOCTYPE_PUBLIC_KEYWORD,
	BEFORE_DOCTYPE_PUBLIC_IDENTIFIER,
	DOCTYPE_PUBLIC_IDENTIFIER_DOUBLE_QUOTED,
	DOCTYPE_PUBLIC_IDENTIFIER_SINGLE_QUOTED,
	AFTER_DOCTYPE_PUBLIC_IDENTIFIER,
	BETWEEN_DOCTYPE_PUBLIC_AND_SYSTEM_IDENTIFIERS,
	AFTER_DOCTYPE_SYSTEM_KEYWORD,
	BEFORE_DOCTYPE_SYSTEM_IDENTIFIER,
	DOCTYPE_SYSTEM_IDENTIFIER_DOUBLE_QUOTED,
	DOCTYPE_SYSTEM_IDENTIFIER_SINGLE_QUOTED,
	AFTER_DOCTYPE_SYSTEM_IDENTIFIER,
	BOGUS_DOCTYPE,
	CDATA_SECTION
};

::std::ostream& operator<<(::std::ostream& os, const STATES& state);

struct StateData {
		STATES state;
		std::string string;
		size_t pos;
		char buf;
		bool parser_pause_flag;
		size_t script_nesting_level;
		std::list<Token> tokens;
		StateData(STATES state = STATES::NULL_STATE, std::string string = "",
				size_t pos = 0, char buf = '\0', bool parser_pause_flag = false,
				size_t script_nesting_level = 0, std::list<Token> tokens = { }) :
				state(state), string(string), pos(pos), buf(buf), parser_pause_flag(parser_pause_flag),
						script_nesting_level(script_nesting_level), tokens(tokens) {

		}
};

::std::ostream& operator<<(::std::ostream& os, const StateData& stateData);
bool operator==(const StateData& lhs, const StateData& rhs);
inline bool operator!=(const StateData& lhs, const StateData& rhs) {
	return !(lhs == rhs);
}

} /* namespace Tokenization */
} /* namespace Parse */
} /* namespace HTML */



#endif /* SRC_HTML_PARSE_TOKENIZATION_TOKENIZATIONTYPES_HPP_ */
