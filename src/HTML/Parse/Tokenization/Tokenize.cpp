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

std::list<Token> Tokenizer::tokenize() {
	changeState(STATES::DATA);
	while (pos < string.length()) {
		switch (state) {
			case STATES::DATA:
				dataState();
				break;
			case STATES::CHARACTER_REFERENCE_IN_DATA:
				characterReferenceInDataState();
				break;
			case STATES::RCDATA:
				RCDATAState();
				break;
			case STATES::CHARACTER_REFERENCE_IN_RCDATA:
				characterReferenceINRCDATAState();
				break;
			case STATES::RAWTEXT:
				RAWTEXTState();
				break;
			case STATES::SCRIPT_DATA:
				scriptDataState();
				break;
			case STATES::PLAINTEXT:
				plainTextState();
				break;
			case STATES::TAG_OPEN:
				tagOpenState();
				break;
			case STATES::END_TAG_OPEN:
				endTagOpenState();
				break;
			case STATES::TAG_NAME:
				tagNameState();
				break;
			case STATES::RCDATA_LESS_THAN_SIGN:
				RCDATALessThanSignState();
				break;
			case STATES::RCDATA_END_TAG_OPEN:
				RCDATAEndTagOpenState();
				break;
			case STATES::RCDATA_END_TAG_NAME:
				RCDATAEndTagNameState();
				break;
			case STATES::RAWTEXT_LESS_THAN_SIGN:
				RAWTEXTLessThanSignState();
				break;
			case STATES::RAWTEXT_END_TAG_OPEN:
				RAWTEXTEndTagOpenState();
				break;
			case STATES::RAWTEXT_END_TAG_NAME:
				RAWTEXTEndTagNameState();
				break;
			case STATES::SCRIPT_DATA_LESS_THAN_SIGN:
				scriptDataLessThanSignState();
				break;
			case STATES::SCRIPT_DATA_END_TAG_OPEN:
				scriptDataEndTagOpenState();
				break;
			case STATES::SCRIPT_DATA_END_TAG_NAME:
				scriptDataEndTagNameState();
				break;
			case STATES::SCRIPT_DATA_ESCAPE_START:
				scriptDataEscapeStartState();
				break;
			case STATES::SCRIPT_DATA_ESCAPE_START_DASH:
				scriptDataEscapeStartDashState();
				break;
			case STATES::SCRIPT_DATA_ESCAPED:
				scriptDataEscapedState();
				break;
			case STATES::SCRIPT_DATA_ESCAPED_DASH:
				scriptDataEscapedDashState();
				break;
			case STATES::SCRIPT_DATA_ESCAPED_DASH_DASH:
				scriptDataEscapedDashDashState();
				break;
			case STATES::SCRIPT_DATA_ESCAPED_LESS_THAN_SIGN:
				scriptDataEscapedLessThanSignState();
				break;
			case STATES::SCRIPT_DATA_ESCAPED_END_TAG_NAME:
				scriptDataEscapedEndTagNameState();
				break;
			case STATES::SCRIPT_DATA_DOUBLE_ESCAPE_START:
				scriptDataDoubleEscapeStartState();
				break;
			case STATES::SCRIPT_DATA_DOUBLE_ESCAPED:
				scriptDataDoubleEscapedState();
				break;
			case STATES::SCRIPT_DATA_DOUBLE_ESCAPED_DASH:
				scriptDataDoubleEscapedDashState();
				break;
			case STATES::SCRIPT_DATA_DOUBLE_ESCAPED_DASH_DASH:
				scriptDataDoubleEscapedDashDashState();
				break;
			case STATES::SCRIPT_DATA_DOUBLE_ESCAPED_LESS_THAN_SIGN:
				scriptDataDoubleEscapedLessThanSignState();
				break;
			case STATES::SCRIPT_DATA_DOUBLE_ESCAPE_END:
				scriptDataDoubleEscapeEndState();
				break;
			case STATES::BEFORE_ATTRIBUTE:
				beforeAttributeState();
				break;
			case STATES::ATTRIBUTE_NAME:
				attributeNameState();
				break;
			case STATES::AFTER_ATTRIBUTE_NAME:
				afterAttributeNameState();
				break;
			case STATES::BEFORE_ATTRIBUTE_VALUE:
				beforeAttributeValueState();
				break;
			case STATES::ATTRIBUTE_VALUE_DOUBLE_QUOTED:
				attributeValueDoubleQuotedState();
				break;
			case STATES::ATTRIBUTE_VALUE_SINGLE_QUOTED:
				attributeValueSingleQuotedState();
				break;
			case STATES::ATTRIBUTE_VALUE_UNQUOTED:
				attributeValueUnquotedState();
				break;
			case STATES::CHARACTER_REFERENCE_IN_ATTRIBUTE_VALUE:
				characterReferenceInAttributeValueState();
				break;
			case STATES::AFTER_ATTRIBUTE_QUOTED:
				afterAttributeQuotedState();
				break;
			case STATES::SELF_CLOSING_START_TAG:
				selfClosingStartTagState();
				break;
			case STATES::BOGUS_COMMENT:
				bogusCommentState();
				break;
			case STATES::MARKUP_DECLARATION_OPEN:
				markupDeclarationOpenState();
				break;
			case STATES::COMMENT_START:
				commentStartState();
				break;
			case STATES::COMMENT_START_DASH:
				commentStartDashState();
				break;
			case STATES::COMMENT:
				commentState();
				break;
			case STATES::COMMENT_END_DASH:
				commentEndDashState();
				break;
			case STATES::COMMENT_END:
				commentEndState();
				break;
			case STATES::COMMENT_END_BANG:
				commentEndBangState();
				break;
			case STATES::DOCTYPE:
				DOCTYPEState();
				break;
			case STATES::BEFORE_DOCTYPE_NAME:
				beforeDOCTYPENameState();
				break;
			case STATES::DOCTYPE_NAME:
				DOCTYPENameState();
				break;
			case STATES::AFTER_DOCTYPE_NAME:
				afterDOCTYPENameState();
				break;
			case STATES::AFTER_DOCTYPE_PUBLIC_KEYWORD:
				afterDOCTYPEPublicKeywordState();
				break;
			case STATES::BEFORE_DOCTYPE_PUBLIC_IDENTIFIER:
				beforeDOCTYPEPublicIdentifierState();
				break;
			case STATES::DOCTYPE_PUBLIC_IDENTIFIER_DOUBLE_QUOTED:
				DOCTYPEPublicIdentifierDoubleQuotedState();
				break;
			case STATES::DOCTYPE_PUBLIC_IDENTIFIER_SINGLE_QUOTED:
				DOCTYPEPublicIdentifierSingleQuotedState();
				break;
			case STATES::AFTER_DOCTYPE_PUBLIC_IDENTIFIER:
				afterDOCTYPEPublicIdentifierState();
				break;
			case STATES::BETWEEN_DOCTYPE_PUBLIC_AND_SYSTEM_IDENTIFIERS:
				betweenDOCTYPEPublicAndSystemIdentifiersState();
				break;
			case STATES::AFTER_DOCTYPE_SYSTEM_KEYWORD:
				afterDOCTYPESystemKeywordState();
				break;
			case STATES::BEFORE_DOCTYPE_SYSTEM_IDENTIFIER:
				beforeDOCTYPESystemIdentifierState();
				break;
			case STATES::DOCTYPE_SYSTEM_IDENTIFIER_DOUBLE_QUOTED:
				DOCTYPESystemIdentifierDoubleQuotedState();
				break;
			case STATES::DOCTYPE_SYSTEM_IDENTIFIER_SINGLE_QUOTED:
				DOCTYPESystemIdentifierSingleQuotedState();
				break;
			case STATES::AFTER_DOCTYPE_SYSTEM_IDENTIFIER:
				afterDOCTYPESystemIdentifierState();
				break;
			case STATES::BOGUS_DOCTYPE:
				bogusDOCTYPEState();
				break;
			case STATES::CDATA_SECTION:
				CDATASectionState();
				break;
			default:
				break;
		}
	}
	return tokens;
}

} /* Tokenization */
} /* Parse */
} /* HTML */
