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
	while (pos < string.length()) {
		switch (state) {
			case DATA:
				dataState();
				break;
			case CHARACTER_REFERENCE_IN_DATA:
				characterReferenceInDataState();
				break;
			case RCDATA:
				RCDATAState();
				break;
			case CHARACTER_REFERENCE_IN_RCDATA:
				characterReferenceINRCDATAState();
				break;
			case RAWTEXT:
				RAWTEXTState();
				break;
			case SCRIPT_DATA:
				scriptDataState();
				break;
			case PLAINTEXT:
				plainTextState();
				break;
			case TAG_OPEN:
				tagOpenState();
				break;
			case END_TAG_OPEN:
				endTagOpenState();
				break;
			case TAG_NAME:
				tagNameState();
				break;
			case RCDATA_LESS_THAN_SIGN:
				RCDATALessThanSignState();
				break;
			case RCDATA_END_TAG_OPEN:
				RCDATAEndTagOpenState();
				break;
			case RCDATA_END_TAG_NAME:
				RCDATAEndTagNameState();
				break;
			case RAWTEXT_LESS_THAN_SIGN:
				RAWTEXTLessThanSignState();
				break;
			case RAWTEXT_END_TAG_OPEN:
				RAWTEXTEndTagOpenState();
				break;
			case RAWTEXT_END_TAG_NAME:
				RAWTEXTEndTagNameState();
				break;
			case SCRIPT_DATA_LESS_THAN_SIGN:
				scriptDataLessThanSignState();
				break;
			case SCRIPT_DATA_END_TAG_OPEN:
				scriptDataEndTagOpenState();
				break;
			case SCRIPT_DATA_END_TAG_NAME:
				scriptDataEndTagNameState();
				break;
			case SCRIPT_DATA_ESCAPE_START:
				scriptDataEscapeStartState();
				break;
			case SCRIPT_DATA_ESCAPE_START_DASH:
				scriptDataEscapeStartDashState();
				break;
			case SCRIPT_DATA_ESCAPED:
				scriptDataEscapedState();
				break;
			case SCRIPT_DATA_ESCAPED_DASH:
				scriptDataEscapedDashState();
				break;
			case SCRIPT_DATA_ESCAPED_DASH_DASH:
				scriptDataEscapedDashDashState();
				break;
			case SCRIPT_DATA_ESCAPED_LESS_THAN_SIGN:
				scriptDataEscapedLessThanSignState();
				break;
			case SCRIPT_DATA_ESCAPED_END_TAG_NAME:
				scriptDataEscapedEndTagNameState();
				break;
			case SCRIPT_DATA_DOUBLE_ESCAPE_START:
				scriptDataDoubleEscapeStartState();
				break;
			case SCRIPT_DATA_DOUBLE_ESCAPED:
				scriptDataDoubleEscapedState();
				break;
			case SCRIPT_DATA_DOUBLE_ESCAPED_DASH:
				scriptDataDoubleEscapedDashState();
				break;
			case SCRIPT_DATA_DOUBLE_ESCAPED_DASH_DASH:
				scriptDataDoubleEscapedDashDashState();
				break;
			case SCRIPT_DATA_DOUBLE_ESCAPED_LESS_THAN_SIGN:
				scriptDataDoubleEscapedLessThanSignState();
				break;
			case SCRIPT_DATA_DOUBLE_ESCAPE_END:
				scriptDataDoubleEscapeEndState();
				break;
			case BEFORE_ATTRIBUTE_NAME:
				beforeAttributeNameState();
				break;
			case ATTRIBUTE_NAME:
				attributeNameState();
				break;
			case AFTER_ATTRIBUTE_NAME:
				afterAttributeNameState();
				break;
			case BEFORE_ATTRIBUTE_VALUE:
				beforeAttributeValueState();
				break;
			case ATTRIBUTE_VALUE_DOUBLE_QUOTED:
				attributeValueDoubleQuotedState();
				break;
			case ATTRIBUTE_VALUE_SINGLE_QUOTED:
				attributeValueSingleQuotedState();
				break;
			case ATTRIBUTE_VALUE_UNQUOTED:
				attributeValueUnquotedState();
				break;
			case CHARACTER_REFERENCE_IN_ATTRIBUTE_VALUE:
				characterReferenceInAttributeValueState();
				break;
			case AFTER_ATTRIBUTE_QUOTED:
				afterAttributeQuotedState();
				break;
			case SELF_CLOSING_START_TAG:
				selfClosingStartTagState();
				break;
			case BOGUS_COMMENT:
				bogusCommentState();
				break;
			case MARKUP_DECLARATION_OPEN:
				markupDeclarationOpenState();
				break;
			case COMMENT_START:
				commentStartState();
				break;
			case COMMENT_START_DASH:
				commentStartDashState();
				break;
			case COMMENT:
				commentState();
				break;
			case COMMENT_END_DASH:
				commentEndDashState();
				break;
			case COMMENT_END:
				commentEndState();
				break;
			case COMMENT_END_BANG:
				commentEndBangState();
				break;
			case DOCTYPE:
				DOCTYPEState();
				break;
			case BEFORE_DOCTYPE_NAME:
				beforeDOCTYPENameState();
				break;
			case DOCTYPE_NAME:
				DOCTYPENameState();
				break;
			case AFTER_DOCTYPE_NAME:
				afterDOCTYPENameState();
				break;
			case AFTER_DOCTYPE_PUBLIC_KEYWORD:
				afterDOCTYPEPublicKeywordState();
				break;
			case BEFORE_DOCTYPE_PUBLIC_IDENTIFIER:
				beforeDOCTYPEPublicIdentifierState();
				break;
			case DOCTYPE_PUBLIC_IDENTIFIER_DOUBLE_QUOTED:
				DOCTYPEPublicIdentifierDoubleQuotedState();
				break;
			case DOCTYPE_PUBLIC_IDENTIFIER_SINGLE_QUOTED:
				DOCTYPEPublicIdentifierSingleQuotedState();
				break;
			case AFTER_DOCTYPE_PUBLIC_IDENTIFIER:
				afterDOCTYPEPublicIdentifierState();
				break;
			case BETWEEN_DOCTYPE_PUBLIC_AND_SYSTEM_IDENTIFIERS:
				betweenDOCTYPEPublicAndSystemIdentifiersState();
				break;
			case AFTER_DOCTYPE_SYSTEM_KEYWORD:
				afterDOCTYPESystemKeywordState();
				break;
			case BEFORE_DOCTYPE_SYSTEM_IDENTIFIER:
				beforeDOCTYPESystemIdentifierState();
				break;
			case DOCTYPE_SYSTEM_IDENTIFIER_DOUBLE_QUOTED:
				DOCTYPESystemIdentifierDoubleQuotedState();
				break;
			case DOCTYPE_SYSTEM_IDENTIFIER_SINGLE_QUOTED:
				DOCTYPESystemIdentifierSingleQuotedState();
				break;
			case AFTER_DOCTYPE_SYSTEM_IDENTIFIER:
				afterDOCTYPESystemIdentifierState();
				break;
			case BOGUS_DOCTYPE:
				bogusDOCTYPEState();
				break;
			case CDATA_SECTION:
				CDATASectionState();
				break;
			default:
				break;
		}
	}
}

} /* Tokenization */
} /* Parse */
} /* HTML */
