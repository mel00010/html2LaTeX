/*******************************************************************************
 * Tokenize.cpp
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

#include "TokenizationTypes.hpp"

#include <list>
#include <string>

namespace HTML {
namespace Parse {
namespace Tokenization {

void Tokenizer::tokenize() {
	switchToState(DATA);
	while (pos <= string.length()) {
		(this->*getStateFunction(state))(); // Rather strange C++ syntax for calling a pointer to a member function of the same class
	}
}
Tokenizer::StateFunction Tokenizer::getStateFunction(const State& state) {
	switch (state) {
		case DATA: // Section 8.2.4.1
			return &HTML::Parse::Tokenization::Tokenizer::dataState;
		case CHARACTER_REFERENCE_IN_DATA: // Section 8.2.4.2
			return &HTML::Parse::Tokenization::Tokenizer::characterReferenceInDataState;
		case RCDATA: // Section 8.2.4.3
			return &HTML::Parse::Tokenization::Tokenizer::RCDATAState;
		case CHARACTER_REFERENCE_IN_RCDATA: // Section 8.2.4.4
			return &HTML::Parse::Tokenization::Tokenizer::characterReferenceInRCDATAState;
		case RAWTEXT: // Section 8.2.4.5
			return &HTML::Parse::Tokenization::Tokenizer::RAWTEXTState;
		case SCRIPT_DATA: // Section 8.2.4.6
			return &HTML::Parse::Tokenization::Tokenizer::scriptDataState;
		case PLAINTEXT: // Section 8.2.4.7
			return &HTML::Parse::Tokenization::Tokenizer::plainTextState;
		case TAG_OPEN: // Section 8.2.4.8
			return &HTML::Parse::Tokenization::Tokenizer::tagOpenState;
		case END_TAG_OPEN: // Section 8.2.4.9
			return &HTML::Parse::Tokenization::Tokenizer::endTagOpenState;
		case TAG_NAME: // Section 8.2.4.10
			return &HTML::Parse::Tokenization::Tokenizer::tagNameState;
		case RCDATA_LESS_THAN_SIGN: // Section 8.2.4.11
			return &HTML::Parse::Tokenization::Tokenizer::RCDATALessThanSignState;
		case RCDATA_END_TAG_OPEN: // Section 8.2.4.12
			return &HTML::Parse::Tokenization::Tokenizer::RCDATAEndTagOpenState;
		case RCDATA_END_TAG_NAME: // Section 8.2.4.13
			return &HTML::Parse::Tokenization::Tokenizer::RCDATAEndTagNameState;
		case RAWTEXT_LESS_THAN_SIGN: // Section 8.2.4.14
			return &HTML::Parse::Tokenization::Tokenizer::RAWTEXTLessThanSignState;
		case RAWTEXT_END_TAG_OPEN: // Section 8.2.4.15
			return &HTML::Parse::Tokenization::Tokenizer::RAWTEXTEndTagOpenState;
		case RAWTEXT_END_TAG_NAME: // Section 8.2.4.16
			return &HTML::Parse::Tokenization::Tokenizer::RAWTEXTEndTagNameState;
		case SCRIPT_DATA_LESS_THAN_SIGN: // Section 8.2.4.17
			return &HTML::Parse::Tokenization::Tokenizer::scriptDataLessThanSignState;
		case SCRIPT_DATA_END_TAG_OPEN: // Section 8.2.4.18
			return &HTML::Parse::Tokenization::Tokenizer::scriptDataEndTagOpenState;
		case SCRIPT_DATA_END_TAG_NAME: // Section 8.2.4.19
			return &HTML::Parse::Tokenization::Tokenizer::scriptDataEndTagNameState;
		case SCRIPT_DATA_ESCAPE_START: // Section 8.2.4.20
			return &HTML::Parse::Tokenization::Tokenizer::scriptDataEscapeStartState;
		case SCRIPT_DATA_ESCAPE_START_DASH: // Section 8.2.4.21
			return &HTML::Parse::Tokenization::Tokenizer::scriptDataEscapeStartDashState;
		case SCRIPT_DATA_ESCAPED: // Section 8.2.4.22
			return &HTML::Parse::Tokenization::Tokenizer::scriptDataEscapedState;
		case SCRIPT_DATA_ESCAPED_DASH: // Section 8.2.4.23
			return &HTML::Parse::Tokenization::Tokenizer::scriptDataEscapedDashState;
		case SCRIPT_DATA_ESCAPED_DASH_DASH: // Section 8.2.4.24
			return &HTML::Parse::Tokenization::Tokenizer::scriptDataEscapedDashDashState;
		case SCRIPT_DATA_ESCAPED_LESS_THAN_SIGN: // Section 8.2.4.25
			return &HTML::Parse::Tokenization::Tokenizer::scriptDataEscapedLessThanSignState;
		case SCRIPT_DATA_ESCAPED_END_TAG_OPEN: // Section 8.2.4.26
			return &HTML::Parse::Tokenization::Tokenizer::scriptDataEscapedEndTagOpenState;
		case SCRIPT_DATA_ESCAPED_END_TAG_NAME: // Section 8.2.4.27
			return &HTML::Parse::Tokenization::Tokenizer::scriptDataEscapedEndTagNameState;
		case SCRIPT_DATA_DOUBLE_ESCAPE_START: // Section 8.2.4.28
			return &HTML::Parse::Tokenization::Tokenizer::scriptDataDoubleEscapeStartState;
		case SCRIPT_DATA_DOUBLE_ESCAPED: // Section 8.2.4.29
			return &HTML::Parse::Tokenization::Tokenizer::scriptDataDoubleEscapedState;
		case SCRIPT_DATA_DOUBLE_ESCAPED_DASH: // Section 8.2.4.30
			return &HTML::Parse::Tokenization::Tokenizer::scriptDataDoubleEscapedDashState;
		case SCRIPT_DATA_DOUBLE_ESCAPED_DASH_DASH: // Section 8.2.4.31
			return &HTML::Parse::Tokenization::Tokenizer::scriptDataDoubleEscapedDashDashState;
		case SCRIPT_DATA_DOUBLE_ESCAPED_LESS_THAN_SIGN: // Section 8.2.4.32
			return &HTML::Parse::Tokenization::Tokenizer::scriptDataDoubleEscapedLessThanSignState;
		case SCRIPT_DATA_DOUBLE_ESCAPE_END: // Section 8.2.4.33
			return &HTML::Parse::Tokenization::Tokenizer::scriptDataDoubleEscapeEndState;
		case BEFORE_ATTRIBUTE_NAME: // Section 8.2.4.34
			return &HTML::Parse::Tokenization::Tokenizer::beforeAttributeNameState;
		case ATTRIBUTE_NAME: // Section 8.2.4.35
			return &HTML::Parse::Tokenization::Tokenizer::attributeNameState;
		case AFTER_ATTRIBUTE_NAME: // Section 8.2.4.36
			return &HTML::Parse::Tokenization::Tokenizer::afterAttributeNameState;
		case BEFORE_ATTRIBUTE_VALUE: // Section 8.2.4.37
			return &HTML::Parse::Tokenization::Tokenizer::beforeAttributeValueState;
		case ATTRIBUTE_VALUE_DOUBLE_QUOTED: // Section 8.2.4.38
			return &HTML::Parse::Tokenization::Tokenizer::attributeValueDoubleQuotedState;
		case ATTRIBUTE_VALUE_SINGLE_QUOTED: // Section 8.2.4.39
			return &HTML::Parse::Tokenization::Tokenizer::attributeValueSingleQuotedState;
		case ATTRIBUTE_VALUE_UNQUOTED: // Section 8.2.4.40
			return &HTML::Parse::Tokenization::Tokenizer::attributeValueUnquotedState;
		case CHARACTER_REFERENCE_IN_ATTRIBUTE_VALUE: // Section 8.2.4.41
			return &HTML::Parse::Tokenization::Tokenizer::characterReferenceInAttributeValueState;
		case AFTER_ATTRIBUTE_QUOTED: // Section 8.2.4.42
			return &HTML::Parse::Tokenization::Tokenizer::afterAttributeQuotedState;
		case SELF_CLOSING_START_TAG: // Section 8.2.4.43
			return &HTML::Parse::Tokenization::Tokenizer::selfClosingStartTagState;
		case BOGUS_COMMENT: // Section 8.2.4.44
			return &HTML::Parse::Tokenization::Tokenizer::bogusCommentState;
		case MARKUP_DECLARATION_OPEN: // Section 8.2.4.45
			return &HTML::Parse::Tokenization::Tokenizer::markupDeclarationOpenState;
		case COMMENT_START: // Section 8.2.4.46
			return &HTML::Parse::Tokenization::Tokenizer::commentStartState;
		case COMMENT_START_DASH: // Section 8.2.4.47
			return &HTML::Parse::Tokenization::Tokenizer::commentStartDashState;
		case COMMENT: // Section 8.2.4.48
			return &HTML::Parse::Tokenization::Tokenizer::commentState;
		case COMMENT_END_DASH: // Section 8.2.4.49
			return &HTML::Parse::Tokenization::Tokenizer::commentEndDashState;
		case COMMENT_END: // Section 8.2.4.50
			return &HTML::Parse::Tokenization::Tokenizer::commentEndState;
		case COMMENT_END_BANG: // Section 8.2.4.51
			return &HTML::Parse::Tokenization::Tokenizer::commentEndBangState;
		case DOCTYPE: // Section 8.2.4.52
			return &HTML::Parse::Tokenization::Tokenizer::DOCTYPEState;
		case BEFORE_DOCTYPE_NAME: // Section 8.2.4.53
			return &HTML::Parse::Tokenization::Tokenizer::beforeDOCTYPENameState;
		case DOCTYPE_NAME: // Section 8.2.4.54
			return &HTML::Parse::Tokenization::Tokenizer::DOCTYPENameState;
		case AFTER_DOCTYPE_NAME: // Section 8.2.4.55
			return &HTML::Parse::Tokenization::Tokenizer::afterDOCTYPENameState;
		case AFTER_DOCTYPE_PUBLIC_KEYWORD: // Section 8.2.4.56
			return &HTML::Parse::Tokenization::Tokenizer::afterDOCTYPEPublicKeywordState;
		case BEFORE_DOCTYPE_PUBLIC_IDENTIFIER: // Section 8.2.4.57
			return &HTML::Parse::Tokenization::Tokenizer::beforeDOCTYPEPublicIdentifierState;
		case DOCTYPE_PUBLIC_IDENTIFIER_DOUBLE_QUOTED: // Section 8.2.4.58
			return &HTML::Parse::Tokenization::Tokenizer::DOCTYPEPublicIdentifierDoubleQuotedState;
		case DOCTYPE_PUBLIC_IDENTIFIER_SINGLE_QUOTED: // Section 8.2.4.59
			return &HTML::Parse::Tokenization::Tokenizer::DOCTYPEPublicIdentifierSingleQuotedState;
		case AFTER_DOCTYPE_PUBLIC_IDENTIFIER: // Section 8.2.4.60
			return &HTML::Parse::Tokenization::Tokenizer::afterDOCTYPEPublicIdentifierState;
		case BETWEEN_DOCTYPE_PUBLIC_AND_SYSTEM_IDENTIFIERS: // Section 8.2.4.61
			return &HTML::Parse::Tokenization::Tokenizer::betweenDOCTYPEPublicAndSystemIdentifiersState;
		case AFTER_DOCTYPE_SYSTEM_KEYWORD: // Section 8.2.4.62
			return &HTML::Parse::Tokenization::Tokenizer::afterDOCTYPESystemKeywordState;
		case BEFORE_DOCTYPE_SYSTEM_IDENTIFIER: // Section 8.2.4.63
			return &HTML::Parse::Tokenization::Tokenizer::beforeDOCTYPESystemIdentifierState;
		case DOCTYPE_SYSTEM_IDENTIFIER_DOUBLE_QUOTED: // Section 8.2.4.64
			return &HTML::Parse::Tokenization::Tokenizer::DOCTYPESystemIdentifierDoubleQuotedState;
		case DOCTYPE_SYSTEM_IDENTIFIER_SINGLE_QUOTED: // Section 8.2.4.65
			return &HTML::Parse::Tokenization::Tokenizer::DOCTYPESystemIdentifierSingleQuotedState;
		case AFTER_DOCTYPE_SYSTEM_IDENTIFIER: // Section 8.2.4.66
			return &HTML::Parse::Tokenization::Tokenizer::afterDOCTYPESystemIdentifierState;
		case BOGUS_DOCTYPE: // Section 8.2.4.67
			return &HTML::Parse::Tokenization::Tokenizer::bogusDOCTYPEState;
		case CDATA_SECTION: // Section 8.2.4.68
			return &HTML::Parse::Tokenization::Tokenizer::CDATASectionState;
		default:
			return nullptr;
			break;
	}
//	return nullptr;
}

} /* Tokenization */
} /* Parse */
} /* HTML */
