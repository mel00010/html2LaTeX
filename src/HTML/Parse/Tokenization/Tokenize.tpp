/*******************************************************************************
 * Tokenize.tpp
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

template <class T> void Tokenizer<T>::tokenize() {
	switchToState(DATA);
	while (pos < string.length()) {
		switch (state) {
			case DATA: // Section 8.2.4.1
				dataState();
				break;
			case CHARACTER_REFERENCE_IN_DATA: // Section 8.2.4.2
				characterReferenceInDataState();
				break;
			case RCDATA: // Section 8.2.4.3
				RCDATAState();
				break;
			case CHARACTER_REFERENCE_IN_RCDATA: // Section 8.2.4.4
				characterReferenceINRCDATAState();
				break;
			case RAWTEXT: // Section 8.2.4.5
				RAWTEXTState();
				break;
			case SCRIPT_DATA: // Section 8.2.4.6
				scriptDataState();
				break;
			case PLAINTEXT: // Section 8.2.4.7
				plainTextState();
				break;
			case TAG_OPEN: // Section 8.2.4.8
				tagOpenState();
				break;
			case END_TAG_OPEN: // Section 8.2.4.9
				endTagOpenState();
				break;
			case TAG_NAME: // Section 8.2.4.10
				tagNameState();
				break;
			case RCDATA_LESS_THAN_SIGN: // Section 8.2.4.11
				RCDATALessThanSignState();
				break;
			case RCDATA_END_TAG_OPEN: // Section 8.2.4.12
				RCDATAEndTagOpenState();
				break;
			case RCDATA_END_TAG_NAME: // Section 8.2.4.13
				RCDATAEndTagNameState();
				break;
			case RAWTEXT_LESS_THAN_SIGN: // Section 8.2.4.14
				RAWTEXTLessThanSignState();
				break;
			case RAWTEXT_END_TAG_OPEN: // Section 8.2.4.15
				RAWTEXTEndTagOpenState();
				break;
			case RAWTEXT_END_TAG_NAME: // Section 8.2.4.16
				RAWTEXTEndTagNameState();
				break;
			case SCRIPT_DATA_LESS_THAN_SIGN: // Section 8.2.4.17
				scriptDataLessThanSignState();
				break;
			case SCRIPT_DATA_END_TAG_OPEN: // Section 8.2.4.18
				scriptDataEndTagOpenState();
				break;
			case SCRIPT_DATA_END_TAG_NAME: // Section 8.2.4.19
				scriptDataEndTagNameState();
				break;
			case SCRIPT_DATA_ESCAPE_START: // Section 8.2.4.20
				scriptDataEscapeStartState();
				break;
			case SCRIPT_DATA_ESCAPE_START_DASH: // Section 8.2.4.21
				scriptDataEscapeStartDashState();
				break;
			case SCRIPT_DATA_ESCAPED: // Section 8.2.4.22
				scriptDataEscapedState();
				break;
			case SCRIPT_DATA_ESCAPED_DASH: // Section 8.2.4.23
				scriptDataEscapedDashState();
				break;
			case SCRIPT_DATA_ESCAPED_DASH_DASH: // Section 8.2.4.24
				scriptDataEscapedDashDashState();
				break;
			case SCRIPT_DATA_ESCAPED_LESS_THAN_SIGN: // Section 8.2.4.25
				scriptDataEscapedLessThanSignState();
				break;
			case SCRIPT_DATA_ESCAPED_END_TAG_OPEN: // Section 8.2.4.26
				scriptDataEscapedEndTagOpenState();
				break;
			case SCRIPT_DATA_ESCAPED_END_TAG_NAME: // Section 8.2.4.27
				scriptDataEscapedEndTagNameState();
				break;
			case SCRIPT_DATA_DOUBLE_ESCAPE_START: // Section 8.2.4.28
				scriptDataDoubleEscapeStartState();
				break;
			case SCRIPT_DATA_DOUBLE_ESCAPED: // Section 8.2.4.29
				scriptDataDoubleEscapedState();
				break;
			case SCRIPT_DATA_DOUBLE_ESCAPED_DASH: // Section 8.2.4.30
				scriptDataDoubleEscapedDashState();
				break;
			case SCRIPT_DATA_DOUBLE_ESCAPED_DASH_DASH: // Section 8.2.4.31
				scriptDataDoubleEscapedDashDashState();
				break;
			case SCRIPT_DATA_DOUBLE_ESCAPED_LESS_THAN_SIGN: // Section 8.2.4.32
				scriptDataDoubleEscapedLessThanSignState();
				break;
			case SCRIPT_DATA_DOUBLE_ESCAPE_END: // Section 8.2.4.33
				scriptDataDoubleEscapeEndState();
				break;
			case BEFORE_ATTRIBUTE_NAME: // Section 8.2.4.34
				beforeAttributeNameState();
				break;
			case ATTRIBUTE_NAME: // Section 8.2.4.35
				attributeNameState();
				break;
			case AFTER_ATTRIBUTE_NAME: // Section 8.2.4.36
				afterAttributeNameState();
				break;
			case BEFORE_ATTRIBUTE_VALUE: // Section 8.2.4.37
				beforeAttributeValueState();
				break;
			case ATTRIBUTE_VALUE_DOUBLE_QUOTED: // Section 8.2.4.38
				attributeValueDoubleQuotedState();
				break;
			case ATTRIBUTE_VALUE_SINGLE_QUOTED: // Section 8.2.4.39
				attributeValueSingleQuotedState();
				break;
			case ATTRIBUTE_VALUE_UNQUOTED: // Section 8.2.4.40
				attributeValueUnquotedState();
				break;
			case CHARACTER_REFERENCE_IN_ATTRIBUTE_VALUE: // Section 8.2.4.41
				characterReferenceInAttributeValueState();
				break;
			case AFTER_ATTRIBUTE_QUOTED: // Section 8.2.4.42
				afterAttributeQuotedState();
				break;
			case SELF_CLOSING_START_TAG: // Section 8.2.4.43
				selfClosingStartTagState();
				break;
			case BOGUS_COMMENT: // Section 8.2.4.44
				bogusCommentState();
				break;
			case MARKUP_DECLARATION_OPEN: // Section 8.2.4.45
				markupDeclarationOpenState();
				break;
			case COMMENT_START: // Section 8.2.4.46
				commentStartState();
				break;
			case COMMENT_START_DASH: // Section 8.2.4.47
				commentStartDashState();
				break;
			case COMMENT: // Section 8.2.4.48
				commentState();
				break;
			case COMMENT_END_DASH: // Section 8.2.4.49
				commentEndDashState();
				break;
			case COMMENT_END: // Section 8.2.4.50
				commentEndState();
				break;
			case COMMENT_END_BANG: // Section 8.2.4.51
				commentEndBangState();
				break;
			case DOCTYPE: // Section 8.2.4.52
				DOCTYPEState();
				break;
			case BEFORE_DOCTYPE_NAME: // Section 8.2.4.53
				beforeDOCTYPENameState();
				break;
			case DOCTYPE_NAME: // Section 8.2.4.54
				DOCTYPENameState();
				break;
			case AFTER_DOCTYPE_NAME: // Section 8.2.4.55
				afterDOCTYPENameState();
				break;
			case AFTER_DOCTYPE_PUBLIC_KEYWORD: // Section 8.2.4.56
				afterDOCTYPEPublicKeywordState();
				break;
			case BEFORE_DOCTYPE_PUBLIC_IDENTIFIER: // Section 8.2.4.57
				beforeDOCTYPEPublicIdentifierState();
				break;
			case DOCTYPE_PUBLIC_IDENTIFIER_DOUBLE_QUOTED: // Section 8.2.4.58
				DOCTYPEPublicIdentifierDoubleQuotedState();
				break;
			case DOCTYPE_PUBLIC_IDENTIFIER_SINGLE_QUOTED: // Section 8.2.4.59
				DOCTYPEPublicIdentifierSingleQuotedState();
				break;
			case AFTER_DOCTYPE_PUBLIC_IDENTIFIER: // Section 8.2.4.60
				afterDOCTYPEPublicIdentifierState();
				break;
			case BETWEEN_DOCTYPE_PUBLIC_AND_SYSTEM_IDENTIFIERS: // Section 8.2.4.61
				betweenDOCTYPEPublicAndSystemIdentifiersState();
				break;
			case AFTER_DOCTYPE_SYSTEM_KEYWORD: // Section 8.2.4.62
				afterDOCTYPESystemKeywordState();
				break;
			case BEFORE_DOCTYPE_SYSTEM_IDENTIFIER: // Section 8.2.4.63
				beforeDOCTYPESystemIdentifierState();
				break;
			case DOCTYPE_SYSTEM_IDENTIFIER_DOUBLE_QUOTED: // Section 8.2.4.64
				DOCTYPESystemIdentifierDoubleQuotedState();
				break;
			case DOCTYPE_SYSTEM_IDENTIFIER_SINGLE_QUOTED: // Section 8.2.4.65
				DOCTYPESystemIdentifierSingleQuotedState();
				break;
			case AFTER_DOCTYPE_SYSTEM_IDENTIFIER: // Section 8.2.4.66
				afterDOCTYPESystemIdentifierState();
				break;
			case BOGUS_DOCTYPE: // Section 8.2.4.67
				bogusDOCTYPEState();
				break;
			case CDATA_SECTION: // Section 8.2.4.68
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
