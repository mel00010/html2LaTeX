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

#include <vector>
#include <string>
#include <stack>

namespace HTML {
namespace Parse {
namespace Tokenization {

template <class T>
class Tokenizer {
	public:
		Tokenizer(const std::u32string& string, T& tree_constructor) :
				string(string), pos(0), state(NULL_STATE), tree_constructor{tree_constructor}, parser_pause_flag(false),
				script_nesting_level(0) {
		}
		Tokenizer(const std::u32string& string, const size_t& pos, T& tree_constructor) :
				string(string), pos(pos), state(NULL_STATE), tree_constructor{tree_constructor}, parser_pause_flag(false),
				script_nesting_level(0)	{
		}
		Tokenizer(const std::u32string& string, const size_t& pos,  const State& state, T& tree_constructor) :
				string(string), pos(pos), state(state), tree_constructor{tree_constructor}, parser_pause_flag(false),
				script_nesting_level(0) {
		}

		/* Implemented in Tokenize.tpp */
	public:
		void tokenize();

	public:
		inline State getCurrentState() {
			return state;
		};
		inline std::stack<CharacterToken>& getCharTokenStack() {
			return char_tokens;
		}

		/* Implemented in ConsumeCharacterReference.tpp */
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

		/* Implemented in TokenizerUtil.tpp */
	private:
		bool atEOF();
		char32_t consume();
		std::u32string consume(const size_t& number_of_chars);
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
		bool isAdjustedCurrentNode();
		bool currentNodeInHTMLNamespace();
		char32_t peek();
		std::u32string peek(const size_t& number_of_chars);
		char32_t reconsume();
		void switchToState(const State& state);
		void unconsume();
		void unconsume(const size_t& number_of_chars);


	public:
		template<class R>
		R pop(std::stack<R>& stack) {
			R copy = stack.top();
			stack.pop();
			return copy;
		}

		/* Implemented in TokenizerStates.tpp */
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
		T& tree_constructor;

		bool parser_pause_flag;
		size_t script_nesting_level;

		TagToken tag;
		CommentToken comment;
		Attribute attribute;
		DOCTYPEToken doctype;

		std::u32string temporary_buffer;

		std::stack<CharacterToken> char_tokens;
		std::stack<char32_t> char_stack;
		StartTagToken prev_start_tag;

		char32_t additional_allowed_character = NO_CHARACTER;
		bool discard_attribute = false;

		size_t chars_consumed = 0;
};

} /* namespace Tokenization */
} /* namespace Parse */
} /* namespace HTML */

#include "ConsumeCharacterReference.tpp"
#include "Tokenize.tpp"
#include "TokenizerStates.tpp"
#include "TokenizerUtil.tpp"

#endif /* SRC_HTML_PARSE_TOKENIZATION_TOKENIZER_HPP_ */
