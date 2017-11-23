/*******************************************************************************
 * StatesUtil.cpp
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

#include "Tokenizer.hpp"

#include <HTML/Microsyntaxes/ASCII/ASCII.hpp>
#include <HTML/Parse/TreeConstruction/Dispatch.hpp>

namespace HTML {
namespace Parse {
namespace Tokenization {


char32_t Tokenizer::consume() {
	return getCharacterAtPosition(pos++);
}
char32_t Tokenizer::consume(size_t& consume_counter) {
	consume_counter++;
	return getCharacterAtPosition(pos++);
}

std::u32string Tokenizer::consume(const size_t& number_of_chars, size_t& consume_counter) {
	std::u32string buffer = getCharactersAtPosition(pos, number_of_chars);
	pos += buffer.length();
	consume_counter += buffer.length();
	return buffer;
}

void Tokenizer::emit(const DOCTYPEToken& token) {
	TreeConstruction::dispatch(Token(token));
}
void Tokenizer::emit(const StartTagToken& token) {
	last_start_tag_token_emitted = token;
	TreeConstruction::dispatch(Token(token));
}
void Tokenizer::emit(const EndTagToken& token) {
	TreeConstruction::dispatch(Token(token));
}
void Tokenizer::emit(const TagToken& token) {
	switch(token.type) {
		case TagToken::TagType::START:
			emit(static_cast<const StartTagToken&>(token));
			break;
		case TagToken::TagType::END:
			emit(static_cast<const EndTagToken&>(token));
			break;
		case TagToken::TagType::NONE:
			emitParseError();
			break;
		default:
			emitParseError();
			break;
	}
}
void Tokenizer::emit(const CommentToken& token) {
	TreeConstruction::dispatch(Token(token));
}
void Tokenizer::emit(const CharacterToken& token) {
	TreeConstruction::dispatch(Token(token));
}
void Tokenizer::emit(const EOFToken& token) {
	TreeConstruction::dispatch(Token(token));
}
void Tokenizer::emit(const Token& token) {
	TreeConstruction::dispatch(token);
}
void Tokenizer::emitParseError(const ParseError& error) {
}


char32_t Tokenizer::getCharacterAtPosition(const size_t& position) {
	if (position >= string.length()) {
		return EOF32;
	}
	return string[position];
}

std::u32string Tokenizer::getCharactersAtPosition(const size_t& position, const size_t& number_of_chars) {
	std::u32string characters = U"";
	for(size_t i = 0; i < number_of_chars; i++) {
		if (position + i >= string.length()) {
			characters.push_back(EOF32);
			break;
		}
		characters.push_back(string[position + i]);
	}
	return characters;
}

bool Tokenizer::isAppropriateEndTagToken() {
	if(current_tag.type != TagToken::TagType::END) {
		return false;
	}
	if(last_start_tag_token_emitted.tag_name != current_tag.tag_name) {
		return false;
	}
	return true;
}

char32_t Tokenizer::peek() {
	return getCharacterAtPosition(pos);
}

std::u32string Tokenizer::peek(const size_t& number_of_chars) {
	return getCharactersAtPosition(pos, number_of_chars);
}

char32_t Tokenizer::reconsume() {
	return getCharacterAtPosition(pos - 1);
}

void Tokenizer::switchToState(const State& new_state) {
	state = new_state;
}

void Tokenizer::unconsume() {
	pos--;
}

void Tokenizer::unconsume(const size_t& number_of_chars) {
	pos -= number_of_chars;
}

::std::ostream& operator<<(::std::ostream& os, const State& state) {
	switch (state) {
		case NULL_STATE:
			os << "NULL_STATE";
			break;
		case DATA:
			os << "DATA";
			break;
		case CHARACTER_REFERENCE_IN_DATA:
			os << "CHARACTER_REFERENCE_IN_DATA";
			break;
		case RCDATA:
			os << "RCDATA";
			break;
		case CHARACTER_REFERENCE_IN_RCDATA:
			os << "CHARACTER_REFERENCE_IN_RCDATA";
			break;
		case RAWTEXT:
			os << "RAWTEXT";
			break;
		case SCRIPT_DATA:
			os << "SCRIPT_DATA";
			break;
		case PLAINTEXT:
			os << "PLAINTEXT";
			break;
		case TAG_OPEN:
			os << "TAG_OPEN";
			break;
		case END_TAG_OPEN:
			os << "END_TAG_OPEN";
			break;
		case TAG_NAME:
			os << "TAG_NAME";
			break;
		case RCDATA_LESS_THAN_SIGN:
			os << "RCDATA_LESS_THAN_SIGN";
			break;
		case RCDATA_END_TAG_OPEN:
			os << "RCDATA_END_TAG_OPEN";
			break;
		case RCDATA_END_TAG_NAME:
			os << "RCDATA_END_TAG_NAME";
			break;
		case RAWTEXT_END_TAG_OPEN:
			os << "RAWTEXT_END_TAG_OPEN";
			break;
		case RAWTEXT_END_TAG_NAME:
			os << "RAWTEXT_END_TAG_NAME";
			break;
		case SCRIPT_DATA_LESS_THAN_SIGN:
			os << "SCRIPT_DATA_LESS_THAN_SIGN";
			break;
		case SCRIPT_DATA_END_TAG_OPEN:
			os << "SCRIPT_DATA_END_TAG_OPEN";
			break;
		case SCRIPT_DATA_END_TAG_NAME:
			os << "SCRIPT_DATA_END_TAG_NAME";
			break;
		case SCRIPT_DATA_ESCAPE_START:
			os << "SCRIPT_DATA_ESCAPE_START";
			break;
		case SCRIPT_DATA_ESCAPE_START_DASH:
			os << "SCRIPT_DATA_ESCAPE_START_DASH";
			break;
		case SCRIPT_DATA_ESCAPED:
			os << "SCRIPT_DATA_ESCAPED";
			break;
		case SCRIPT_DATA_ESCAPED_DASH:
			os << "SCRIPT_DATA_ESCAPED_DASH";
			break;
		case SCRIPT_DATA_ESCAPED_DASH_DASH:
			os << "SCRIPT_DATA_ESCAPED_DASH_DASH";
			break;
		case SCRIPT_DATA_ESCAPED_LESS_THAN_SIGN:
			os << "SCRIPT_DATA_ESCAPED_LESS_THAN_SIGN";
			break;
		case SCRIPT_DATA_ESCAPED_END_TAG_NAME:
			os << "SCRIPT_DATA_ESCAPED_END_TAG_NAME";
			break;
		case SCRIPT_DATA_DOUBLE_ESCAPE_START:
			os << "SCRIPT_DATA_DOUBLE_ESCAPE_START";
			break;
		case SCRIPT_DATA_DOUBLE_ESCAPED:
			os << "SCRIPT_DATA_DOUBLE_ESCAPED";
			break;
		case SCRIPT_DATA_DOUBLE_ESCAPED_DASH:
			os << "SCRIPT_DATA_DOUBLE_ESCAPED_DASH";
			break;
		case SCRIPT_DATA_DOUBLE_ESCAPED_DASH_DASH:
			os << "SCRIPT_DATA_DOUBLE_ESCAPED_DASH_DASH";
			break;
		case SCRIPT_DATA_DOUBLE_ESCAPED_LESS_THAN_SIGN:
			os << "SCRIPT_DATA_DOUBLE_ESCAPED_LESS_THAN_SIGN";
			break;
		case SCRIPT_DATA_DOUBLE_ESCAPE_END:
			os << "SCRIPT_DATA_DOUBLE_ESCAPE_END";
			break;
		case BEFORE_ATTRIBUTE_NAME:
			os << "BEFORE_ATTRIBUTE";
			break;
		case ATTRIBUTE_NAME:
			os << "ATTRIBUTE_NAME";
			break;
		case AFTER_ATTRIBUTE_NAME:
			os << "AFTER_ATTRIBUTE_NAME";
			break;
		case BEFORE_ATTRIBUTE_VALUE:
			os << "BEFORE_ATTRIBUTE_VALUE";
			break;
		case ATTRIBUTE_VALUE_DOUBLE_QUOTED:
			os << "ATTRIBUTE_VALUE_DOUBLE_QUOTED";
			break;
		case ATTRIBUTE_VALUE_SINGLE_QUOTED:
			os << "ATTRIBUTE_VALUE_SINGLE_QUOTED";
			break;
		case ATTRIBUTE_VALUE_UNQUOTED:
			os << "ATTRIBUTE_VALUE_UNQUOTED";
			break;
		case CHARACTER_REFERENCE_IN_ATTRIBUTE_VALUE:
			os << "CHARACTER_REFERENCE_IN_ATTRIBUTE_VALUE";
			break;
		case AFTER_ATTRIBUTE_QUOTED:
			os << "AFTER_ATTRIBUTE_QUOTED";
			break;
		case SELF_CLOSING_START_TAG:
			os << "SELF_CLOSING_START_TAG";
			break;
		case BOGUS_COMMENT:
			os << "BOGUS_COMMENT";
			break;
		case MARKUP_DECLARATION_OPEN:
			os << "MARKUP_DECLARATION_OPEN";
			break;
		case COMMENT_START:
			os << "COMMENT_START";
			break;
		case COMMENT_START_DASH:
			os << "COMMENT_START_DASH";
			break;
		case COMMENT:
			os << "COMMENT";
			break;
		case COMMENT_END_DASH:
			os << "COMMENT_END_DASH";
			break;
		case COMMENT_END:
			os << "COMMENT_END";
			break;
		case COMMENT_END_BANG:
			os << "COMMENT_END_BANG";
			break;
		case DOCTYPE:
			os << "DOCTYPE";
			break;
		case BEFORE_DOCTYPE_NAME:
			os << "BEFORE_DOCTYPE_NAME";
			break;
		case DOCTYPE_NAME:
			os << "DOCTYPE_NAME";
			break;
		case AFTER_DOCTYPE_NAME:
			os << "AFTER_DOCTYPE_NAME";
			break;
		case AFTER_DOCTYPE_PUBLIC_KEYWORD:
			os << "AFTER_DOCTYPE_PUBLIC_KEYWORD";
			break;
		case BEFORE_DOCTYPE_PUBLIC_IDENTIFIER:
			os << "BEFORE_DOCTYPE_PUBLIC_IDENTIFIER";
			break;
		case DOCTYPE_PUBLIC_IDENTIFIER_DOUBLE_QUOTED:
			os << "DOCTYPE_PUBLIC_IDENTIFIER_DOUBLE_QUOTED";
			break;
		case DOCTYPE_PUBLIC_IDENTIFIER_SINGLE_QUOTED:
			os << "DOCTYPE_PUBLIC_IDENTIFIER_SINGLE_QUOTED";
			break;
		case AFTER_DOCTYPE_PUBLIC_IDENTIFIER:
			os << "AFTER_DOCTYPE_PUBLIC_IDENTIFIER";
			break;
		case BETWEEN_DOCTYPE_PUBLIC_AND_SYSTEM_IDENTIFIERS:
			os << "BETWEEN_DOCTYPE_PUBLIC_AND_SYSTEM_IDENTIFIERS";
			break;
		case AFTER_DOCTYPE_SYSTEM_KEYWORD:
			os << "AFTER_DOCTYPE_SYSTEM_KEYWORD";
			break;
		case BEFORE_DOCTYPE_SYSTEM_IDENTIFIER:
			os << "BEFORE_DOCTYPE_SYSTEM_IDENTIFIER";
			break;
		case DOCTYPE_SYSTEM_IDENTIFIER_DOUBLE_QUOTED:
			os << "DOCTYPE_SYSTEM_IDENTIFIER_DOUBLE_QUOTED";
			break;
		case DOCTYPE_SYSTEM_IDENTIFIER_SINGLE_QUOTED:
			os << "DOCTYPE_SYSTEM_IDENTIFIER_SINGLE_QUOTED";
			break;
		case AFTER_DOCTYPE_SYSTEM_IDENTIFIER:
			os << "AFTER_DOCTYPE_SYSTEM_IDENTIFIER";
			break;
		case BOGUS_DOCTYPE:
			os << "BOGUS_DOCTYPE";
			break;
		case CDATA_SECTION:
			os << "CDATA_SECTION";
			break;
		default:
			os << "Error:  Unknown state!";
			break;
	}
	return os;
}

} /* namespace Tokenization */
} /* namespace Parse */
} /* namespace HTML */

