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

#include "Tokenize.hpp"

#include "States.hpp"
#include "TokenizationTypes.hpp"

#include <list>
#include <string>

namespace HTML {
namespace Parse {
namespace Tokenization {

std::list<Token> tokenize(const std::u32string& string) {
	StateData state_data;
	state_data.string = string;

	while (state_data.pos < state_data.string.length()) {
		switch (state_data.state) {
			case STATES::DATA:
				States::dataState(state_data);
				break;
			case STATES::CHARACTER_REFERENCE_IN_DATA:
				States::characterReferenceInDataState(state_data);
				break;
			case STATES::RCDATA:
				States::RCDATAState(state_data);
				break;
			case STATES::CHARACTER_REFERENCE_IN_RCDATA:
				States::characterReferenceINRCDATAState(state_data);
				break;
			case STATES::RAWTEXT:
				States::RAWTEXTState(state_data);
				break;
			case STATES::SCRIPT_DATA:
				States::scriptDataState(state_data);
				break;
			case STATES::PLAINTEXT:
				States::plainTextState(state_data);
				break;
			case STATES::TAG_OPEN:
				States::tagOpenState(state_data);
				break;
			case STATES::END_TAG_OPEN:
				States::endTagOpenState(state_data);
				break;
			case STATES::TAG_NAME:
				States::tagNameState(state_data);
				break;
			case STATES::RCDATA_LESS_THAN_SIGN:
				States::RCDATALessThanSignState(state_data);
				break;
			case STATES::RCDATA_END_TAG_OPEN:
				States::RCDATAEndTagOpenState(state_data);
				break;
			case STATES::RCDATA_END_TAG_NAME:
				States::RCDATAEndTagNameState(state_data);
				break;
			case STATES::RAWTEXT_END_TAG_OPEN:
				States::RAWTEXTEndTagOpenState(state_data);
				break;
			case STATES::RAWTEXT_END_TAG_NAME:
				States::RAWTEXTEndTagNameState(state_data);
				break;
			case STATES::SCRIPT_DATA_LESS_THAN_SIGN:
				States::scriptDataLessThanSignState(state_data);
				break;
			case STATES::SCRIPT_DATA_END_TAG_OPEN:
				States::scriptDataEndTagOpenState(state_data);
				break;
			case STATES::SCRIPT_DATA_END_TAG_NAME:
				States::scriptDataEndTagNameState(state_data);
				break;
			case STATES::SCRIPT_DATA_ESCAPE_START:
				States::scriptDataEscapeStartState(state_data);
				break;
			case STATES::SCRIPT_DATA_ESCAPE_START_DASH:
				States::scriptDataEscapeStartDashState(state_data);
				break;
			case STATES::SCRIPT_DATA_ESCAPED:
				States::scriptDataEscapedState(state_data);
				break;
			case STATES::SCRIPT_DATA_ESCAPED_DASH:
				States::scriptDataEscapedDashState(state_data);
				break;
			case STATES::SCRIPT_DATA_ESCAPED_DASH_DASH:
				States::scriptDataEscapedDashDashState(state_data);
				break;
			case STATES::SCRIPT_DATA_ESCAPED_LESS_THAN_SIGN:
				States::scriptDataEscapedLessThanSignState(state_data);
				break;
			case STATES::SCRIPT_DATA_ESCAPED_END_TAG_NAME:
				States::scriptDataEscapedEndTagNameState(state_data);
				break;
			case STATES::SCRIPT_DATA_DOUBLE_ESCAPE_START:
				States::scriptDataDoubleEscapeStartState(state_data);
				break;
			case STATES::SCRIPT_DATA_DOUBLE_ESCAPED:
				States::scriptDataDoubleEscapedState(state_data);
				break;
			case STATES::SCRIPT_DATA_DOUBLE_ESCAPED_DASH:
				States::scriptDataDoubleEscapedDashState(state_data);
				break;
			case STATES::SCRIPT_DATA_DOUBLE_ESCAPED_DASH_DASH:
				States::scriptDataDoubleEscapedDashDashState(state_data);
				break;
			case STATES::SCRIPT_DATA_DOUBLE_ESCAPED_LESS_THAN_SIGN:
				States::scriptDataDoubleEscapedLessThanSignState(state_data);
				break;
			case STATES::SCRIPT_DATA_DOUBLE_ESCAPE_END:
				States::scriptDataDoubleEscapeEndState(state_data);
				break;
			case STATES::BEFORE_ATTRIBUTE:
				States::beforeAttributeState(state_data);
				break;
			case STATES::ATTRIBUTE_NAME:
				States::attributeNameState(state_data);
				break;
			case STATES::AFTER_ATTRIBUTE_NAME:
				States::afterAttributeNameState(state_data);
				break;
			case STATES::BEFORE_ATTRIBUTE_VALUE:
				States::beforeAttributeValueState(state_data);
				break;
			case STATES::ATTRIBUTE_VALUE_DOUBLE_QUOTED:
				States::attributeValueDoubleQuotedState(state_data);
				break;
			case STATES::ATTRIBUTE_VALUE_SINGLE_QUOTED:
				States::attributeValueSingleQuotedState(state_data);
				break;
			case STATES::ATTRIBUTE_VALUE_UNQUOTED:
				States::attributeValueUnquotedState(state_data);
				break;
			case STATES::CHARACTER_REFERENCE_IN_ATTRIBUTE_VALUE:
				States::characterReferenceInAttributeValueState(state_data);
				break;
			case STATES::AFTER_ATTRIBUTE_QUOTED:
				States::afterAttributeQuotedState(state_data);
				break;
			case STATES::SELF_CLOSING_START_TAG:
				States::selfClosingStartTagState(state_data);
				break;
			case STATES::BOGUS_COMMENT:
				States::bogusCommentState(state_data);
				break;
			case STATES::MARKUP_DECLARATION_OPEN:
				States::markupDeclarationOpenState(state_data);
				break;
			case STATES::COMMENT_START:
				States::commentStartState(state_data);
				break;
			case STATES::COMMENT_START_DASH:
				States::commentStartDashState(state_data);
				break;
			case STATES::COMMENT:
				States::commentState(state_data);
				break;
			case STATES::COMMENT_END_DASH:
				States::commentEndDashState(state_data);
				break;
			case STATES::COMMENT_END:
				States::commentEndState(state_data);
				break;
			case STATES::COMMENT_END_BANG:
				States::commentEndBangState(state_data);
				break;
			case STATES::DOCTYPE:
				States::DOCTYPEState(state_data);
				break;
			case STATES::BEFORE_DOCTYPE_NAME:
				States::beforeDOCTYPENameState(state_data);
				break;
			case STATES::DOCTYPE_NAME:
				States::DOCTYPENameState(state_data);
				break;
			case STATES::AFTER_DOCTYPE_NAME:
				States::afterDOCTYPENameState(state_data);
				break;
			case STATES::AFTER_DOCTYPE_PUBLIC_KEYWORD:
				States::afterDOCTYPEPublicKeywordState(state_data);
				break;
			case STATES::BEFORE_DOCTYPE_PUBLIC_IDENTIFIER:
				States::beforeDOCTYPEPublicIdentifierState(state_data);
				break;
			case STATES::DOCTYPE_PUBLIC_IDENTIFIER_DOUBLE_QUOTED:
				States::DOCTYPEPublicIdentifierDoubleQuotedState(state_data);
				break;
			case STATES::DOCTYPE_PUBLIC_IDENTIFIER_SINGLE_QUOTED:
				States::DOCTYPEPublicIdentifierSingleQuotedState(state_data);
				break;
			case STATES::AFTER_DOCTYPE_PUBLIC_IDENTIFIER:
				States::afterDOCTYPEPublicIdentifierState(state_data);
				break;
			case STATES::BETWEEN_DOCTYPE_PUBLIC_AND_SYSTEM_IDENTIFIERS:
				States::betweenDOCTYPEPublicAndSystemIdentifiersState(state_data);
				break;
			case STATES::AFTER_DOCTYPE_SYSTEM_KEYWORD:
				States::afterDOCTYPESystemKeywordState(state_data);
				break;
			case STATES::BEFORE_DOCTYPE_SYSTEM_IDENTIFIER:
				States::beforeDOCTYPESystemIdentifierState(state_data);
				break;
			case STATES::DOCTYPE_SYSTEM_IDENTIFIER_DOUBLE_QUOTED:
				States::DOCTYPESystemIdentifierDoubleQuotedState(state_data);
				break;
			case STATES::DOCTYPE_SYSTEM_IDENTIFIER_SINGLE_QUOTED:
				States::DOCTYPESystemIdentifierSingleQuotedState(state_data);
				break;
			case STATES::AFTER_DOCTYPE_SYSTEM_IDENTIFIER:
				States::afterDOCTYPESystemIdentifierState(state_data);
				break;
			case STATES::BOGUS_DOCTYPE:
				States::bogusDOCTYPEState(state_data);
				break;
			case STATES::CDATA_SECTION:
				States::CDATASectionState(state_data);
				break;
//			case STATES::TOKENIZING_CHARACTER_REFERENCES:
//				States::tokenizingCharacterReferences(state_data);
//				break;
			default:
				break;
		}
	}
	return state_data.tokens;
}

} /* Tokenization */
} /* Parse */
} /* HTML */
