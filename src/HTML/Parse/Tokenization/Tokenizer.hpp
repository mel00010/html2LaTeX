/*******************************************************************************
 * States.hpp
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
#ifndef SRC_HTML_PARSE_TOKENIZATION_TOKENIZER_HPP_
#define SRC_HTML_PARSE_TOKENIZATION_TOKENIZER_HPP_

#include "TokenizationTypes.hpp"

#include <list>
#include <string>

namespace HTML {
namespace Parse {
namespace Tokenization {

enum State {
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
	RAWTEXT_LESS_THAN_SIGN,
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
	BEFORE_ATTRIBUTE_NAME,
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

class Tokenizer {
	public:
		Tokenizer(const std::u32string& string) :
				string(string), pos(0), state(NULL_STATE), parser_pause_flag(false), script_nesting_level(0) {
		}
		Tokenizer(const std::u32string& string, const size_t& pos) :
				string(string), pos(pos), state(NULL_STATE), parser_pause_flag(false), script_nesting_level(0) {
		}
		Tokenizer(const std::u32string& string, const size_t& pos,  const State& state) :
				string(string), pos(pos), state(state), parser_pause_flag(false), script_nesting_level(0) {
		}

		/* Implemented in Tokenize.cpp */
	public:
		void tokenize();

		/* Implemented in ConsumeCharacterReference.cpp */
	public:
		TokenPair consumeCharacterReference();
		TokenPair consumeCharacterReference(const char32_t& additional_allowed_character);
	private:
		TokenPair consumeCharacterReferenceCodepointHelper();
		TokenPair consumeCharacterReferenceNamedCharacterReferenceHelper();

		/* Implemented in TokenizerUtil.cpp */
	private:
		bool atEOF();
		char32_t consume();
		char32_t consume(size_t& consume_counter);
		std::u32string consume(const size_t& number_of_chars, size_t& consume_counter);
		void emit(const DOCTYPEToken& token);
		void emit(const StartTagToken& token);
		void emit(const EndTagToken& token);
		void emit(const CommentToken& token);
		void emit(const CharacterToken& token);
		void emit(const EOFToken& token);
		void emit(const Token& token);
		void emitParseError(const ParseError& error);
		char32_t getCharacterAtPosition(const size_t& position);
		std::u32string getCharactersAtPosition(const size_t& position, const size_t& number_of_chars);
		char32_t peek();
		std::u32string peek(const size_t& number_of_chars);
		char32_t reconsume();
		void switchToState(const State& state);
		void unconsume();
		void unconsume(const size_t& number_of_chars);

		/* Implemented in TokenizerStates.cpp */
	private:
		void dataState();
		void characterReferenceInDataState();
		void RCDATAState();
		void characterReferenceINRCDATAState();
		void RAWTEXTState();
		void scriptDataState();
		void plainTextState();
		void tagOpenState();
		void endTagOpenState();
		void tagNameState();
		void RCDATALessThanSignState();
		void RCDATAEndTagOpenState();
		void RCDATAEndTagNameState();
		void RAWTEXTLessThanSignState();
		void RAWTEXTEndTagOpenState();
		void RAWTEXTEndTagNameState();
		void scriptDataLessThanSignState();
		void scriptDataEndTagOpenState();
		void scriptDataEndTagNameState();
		void scriptDataEscapeStartState();
		void scriptDataEscapeStartDashState();
		void scriptDataEscapedState();
		void scriptDataEscapedDashState();
		void scriptDataEscapedDashDashState();
		void scriptDataEscapedLessThanSignState();
		void scriptDataEscapedEndTagNameState();
		void scriptDataDoubleEscapeStartState();
		void scriptDataDoubleEscapedState();
		void scriptDataDoubleEscapedDashState();
		void scriptDataDoubleEscapedDashDashState();
		void scriptDataDoubleEscapedLessThanSignState();
		void scriptDataDoubleEscapeEndState();
		void beforeAttributeNameState();
		void attributeNameState();
		void beforeAttributeValueState();
		void afterAttributeNameState();
		void attributeValueDoubleQuotedState();
		void attributeValueSingleQuotedState();
		void attributeValueUnquotedState();
		void characterReferenceInAttributeValueState();
		void afterAttributeQuotedState();
		void selfClosingStartTagState();
		void bogusCommentState();
		void markupDeclarationOpenState();
		void commentStartState();
		void commentStartDashState();
		void commentState();
		void commentEndDashState();
		void commentEndState();
		void commentEndBangState();
		void DOCTYPEState();
		void beforeDOCTYPENameState();
		void DOCTYPENameState();
		void afterDOCTYPENameState();
		void afterDOCTYPEPublicKeywordState();
		void beforeDOCTYPEPublicIdentifierState();
		void DOCTYPEPublicIdentifierDoubleQuotedState();
		void DOCTYPEPublicIdentifierSingleQuotedState();
		void afterDOCTYPEPublicIdentifierState();
		void betweenDOCTYPEPublicAndSystemIdentifiersState();
		void afterDOCTYPESystemKeywordState();
		void beforeDOCTYPESystemIdentifierState();
		void DOCTYPESystemIdentifierDoubleQuotedState();
		void DOCTYPESystemIdentifierSingleQuotedState();
		void afterDOCTYPESystemIdentifierState();
		void bogusDOCTYPEState();
		void CDATASectionState();

	public:
		const std::u32string string;
		size_t pos;

	private:
		State state;

		bool parser_pause_flag;
		size_t script_nesting_level;

		TagToken tag_token_buffer;
};

/* Implemented in TokenizerUtil.cpp */
::std::ostream& operator<<(::std::ostream& os, const State& state);

} /* namespace Tokenization */
} /* namespace Parse */
} /* namespace HTML */

#endif /* SRC_HTML_PARSE_TOKENIZATION_TOKENIZER_HPP_ */
