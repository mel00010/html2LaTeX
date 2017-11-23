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
#include <stack>

namespace HTML {
namespace Parse {
namespace Tokenization {

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

	public:
		inline std::stack<Token>& get_token_stack() {
			return token_stack;
		}
		/* Implemented in ConsumeCharacterReference.cpp */
	public:
		/**
		 * @brief Consumes a character reference
		 * @details Described in section 8.2.4.69 in the W3C HTML5 specification
		 * @return Returns the number of character tokens pushed to the token stack
		 */
		size_t consumeCharacterReference();
	private:
		/**
		 * @brief Helper function for consumeCharacterReference()
		 * @details Handles a manually specified Unicode codepoint
		 * @return Returns a TokenPair object containing the decoded characters
		 */
		size_t consumeCharacterReferenceCodepointHelper();
		/**
		 * @brief Helper function for consumeCharacterReference()
		 * @details Handles a named character reference
		 * @return Returns a TokenPair object containing the decoded characters
		 */
		size_t consumeCharacterReferenceNamedCharacterReferenceHelper();

		/* Implemented in TokenizerUtil.cpp */
	private:
		bool atEOF();
		char32_t consume();
		char32_t consume(size_t& consume_counter);
		std::u32string consume(const size_t& number_of_chars, size_t& consume_counter);
		void emit(const DOCTYPEToken& token);
		void emit(const StartTagToken& token);
		void emit(const EndTagToken& token);
		void emit(const TagToken& token);
		void emit(const CommentToken& token);
		void emit(const CharacterToken& token);
		void emit(const EOFToken& token);
		void emit(const Token& token);
		void emitParseError(const ParseError& error = ParseError::OTHER);
		char32_t getCharacterAtPosition(const size_t& position);
		std::u32string getCharactersAtPosition(const size_t& position, const size_t& number_of_chars);
		bool isAppropriateEndTagToken();
		bool isAttributeNameUnique();
		char32_t peek();
		std::u32string peek(const size_t& number_of_chars);
		char32_t reconsume();
		void switchToState(const State& state);
		void unconsume();
		void unconsume(const size_t& number_of_chars);


	private:
		template<class T>
		void emitFromStack(std::stack<T> stack) {
			emit(stack.top());
			stack.pop();
		}

		/* Implemented in TokenizerStates.cpp */
	private:
		void dataState(); // Section 8.2.4.1
		void characterReferenceInDataState(); // Section 8.2.4.2
		void RCDATAState(); // Section 8.2.4.3
		void characterReferenceINRCDATAState(); // Section 8.2.4.4
		void RAWTEXTState(); // Section 8.2.4.5
		void scriptDataState(); // Section 8.2.4.6
		void plainTextState(); // Section 8.2.4.7
		void tagOpenState(); // Section 8.2.4.8
		void endTagOpenState(); // Section 8.2.4.9
		void tagNameState(); // Section 8.2.4.10
		void RCDATALessThanSignState(); // Section 8.2.4.11
		void RCDATAEndTagOpenState(); // Section 8.2.4.12
		void RCDATAEndTagNameState(); // Section 8.2.4.13
		void RAWTEXTLessThanSignState(); // Section 8.2.4.14
		void RAWTEXTEndTagOpenState(); // Section 8.2.4.15
		void RAWTEXTEndTagNameState(); // Section 8.2.4.16
		void scriptDataLessThanSignState(); // Section 8.2.4.17
		void scriptDataEndTagOpenState(); // Section 8.2.4.18
		void scriptDataEndTagNameState(); // Section 8.2.4.19
		void scriptDataEscapeStartState(); // Section 8.2.4.20
		void scriptDataEscapeStartDashState(); // Section 8.2.4.21
		void scriptDataEscapedState(); // Section 8.2.4.22
		void scriptDataEscapedDashState(); // Section 8.2.4.23
		void scriptDataEscapedDashDashState(); // Section 8.2.4.24
		void scriptDataEscapedLessThanSignState(); // Section 8.2.4.25
		void scriptDataEscapedEndTagOpenState(); // Section 8.2.4.26
		void scriptDataEscapedEndTagNameState(); // Section 8.2.4.27
		void scriptDataDoubleEscapeStartState(); // Section 8.2.4.28
		void scriptDataDoubleEscapedState(); // Section 8.2.4.29
		void scriptDataDoubleEscapedDashState(); // Section 8.2.4.30
		void scriptDataDoubleEscapedDashDashState(); // Section 8.2.4.31
		void scriptDataDoubleEscapedLessThanSignState(); // Section 8.2.4.32
		void scriptDataDoubleEscapeEndState(); // Section 8.2.4.33
		void beforeAttributeNameState(); // Section 8.2.4.34
		void attributeNameState(); // Section 8.2.4.35
		void beforeAttributeValueState(); // Section 8.2.4.36
		void afterAttributeNameState(); // Section 8.2.4.37
		void attributeValueDoubleQuotedState(); // Section 8.2.4.38
		void attributeValueSingleQuotedState(); // Section 8.2.4.39
		void attributeValueUnquotedState(); // Section 8.2.4.40
		void characterReferenceInAttributeValueState(); // Section 8.2.4.41
		void afterAttributeQuotedState(); // Section 8.2.4.42
		void selfClosingStartTagState(); // Section 8.2.4.43
		void bogusCommentState(); // Section 8.2.4.44
		void markupDeclarationOpenState(); // Section 8.2.4.45
		void commentStartState(); // Section 8.2.4.46
		void commentStartDashState(); // Section 8.2.4.47
		void commentState(); // Section 8.2.4.48
		void commentEndDashState(); // Section 8.2.4.49
		void commentEndState(); // Section 8.2.4.50
		void commentEndBangState(); // Section 8.2.4.51
		void DOCTYPEState(); // Section 8.2.4.52
		void beforeDOCTYPENameState(); // Section 8.2.4.53
		void DOCTYPENameState(); // Section 8.2.4.54
		void afterDOCTYPENameState(); // Section 8.2.4.55
		void afterDOCTYPEPublicKeywordState(); // Section 8.2.4.56
		void beforeDOCTYPEPublicIdentifierState(); // Section 8.2.4.57
		void DOCTYPEPublicIdentifierDoubleQuotedState(); // Section 8.2.4.58
		void DOCTYPEPublicIdentifierSingleQuotedState(); // Section 8.2.4.59
		void afterDOCTYPEPublicIdentifierState(); // Section 8.2.4.60
		void betweenDOCTYPEPublicAndSystemIdentifiersState(); // Section 8.2.4.61
		void afterDOCTYPESystemKeywordState(); // Section 8.2.4.62
		void beforeDOCTYPESystemIdentifierState(); // Section 8.2.4.63
		void DOCTYPESystemIdentifierDoubleQuotedState(); // Section 8.2.4.64
		void DOCTYPESystemIdentifierSingleQuotedState(); // Section 8.2.4.65
		void afterDOCTYPESystemIdentifierState(); // Section 8.2.4.66
		void bogusDOCTYPEState(); // Section 8.2.4.67
		void CDATASectionState(); // Section 8.2.4.68

	public:
		const std::u32string string;
		size_t pos;

	private:
		State state;

		bool parser_pause_flag;
		size_t script_nesting_level;

		TagToken current_tag;
		Attribute current_attribute;

		std::u32string temporary_buffer;

		std::stack<Token> token_stack;
		std::stack<char32_t> char_stack;
		StartTagToken last_start_tag_token_emitted;

		char32_t additional_allowed_character = NO_CHARACTER;
		bool discard_current_attribute = false;
};

/* Implemented in TokenizerUtil.cpp */
::std::ostream& operator<<(::std::ostream& os, const State& state);

} /* namespace Tokenization */
} /* namespace Parse */
} /* namespace HTML */

#endif /* SRC_HTML_PARSE_TOKENIZATION_TOKENIZER_HPP_ */
