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
#ifndef SRC_HTML_PARSE_TOKENIZATION_STATES_HPP_
#define SRC_HTML_PARSE_TOKENIZATION_STATES_HPP_

#include "TokenizationTypes.hpp"

#include <string>

namespace HTML {
namespace Parse {
namespace Tokenization {
namespace States {

void dataState(StateData& data);
void characterReferenceInDataState(StateData& data);
void RCDATAState(StateData& data);
void characterReferenceINRCDATAState(StateData& data);
void RAWTEXTState(StateData& data);
void scriptDataState(StateData& data);
void plainTextState(StateData& data);
void tagOpenState(StateData& data);
void endTagOpenState(StateData& data);
void tagNameState(StateData& data);
void RCDATALessThanSignState(StateData& data);
void RCDATAEndTagOpenState(StateData& data);
void RCDATAEndTagNameState(StateData& data);
void RAWTEXTLessThanSignState(StateData& data);
void RAWTEXTEndTagOpenState(StateData& data);
void RAWTEXTEndTagNameState(StateData& data);
void scriptDataLessThanSignState(StateData& data);
void scriptDataEndTagOpenState(StateData& data);
void scriptDataEndTagNameState(StateData& data);
void scriptDataEscapeStartState(StateData& data);
void scriptDataEscapeStartDashState(StateData& data);
void scriptDataEscapedState(StateData& data);
void scriptDataEscapedDashState(StateData& data);
void scriptDataEscapedDashDashState(StateData& data);
void scriptDataEscapedLessThanSignState(StateData& data);
void scriptDataEscapedEndTagNameState(StateData& data);
void scriptDataDoubleEscapeStartState(StateData& data);
void scriptDataDoubleEscapedState(StateData& data);
void scriptDataDoubleEscapedDashState(StateData& data);
void scriptDataDoubleEscapedDashDashState(StateData& data);
void scriptDataDoubleEscapedLessThanSignState(StateData& data);
void scriptDataDoubleEscapeEndState(StateData& data);
void beforeAttributeState(StateData& data);
void attributeNameState(StateData& data);
void beforeAttributeValueState(StateData& data);
void afterAttributeNameState(StateData& data);
void attributeValueDoubleQuotedState(StateData& data);
void attributeValueSingleQuotedState(StateData& data);
void attributeValueUnquotedState(StateData& data);
void characterReferenceInAttributeValueState(StateData& data);
void afterAttributeQuotedState(StateData& data);
void selfClosingStartTagState(StateData& data);
void bogusCommentState(StateData& data);
void markupDeclarationOpenState(StateData& data);
void commentStartState(StateData& data);
void commentStartDashState(StateData& data);
void commentState(StateData& data);
void commentEndDashState(StateData& data);
void commentEndState(StateData& data);
void commentEndBangState(StateData& data);
void DOCTYPEState(StateData& data);
void beforeDOCTYPENameState(StateData& data);
void DOCTYPENameState(StateData& data);
void afterDOCTYPENameState(StateData& data);
void afterDOCTYPEPublicKeywordState(StateData& data);
void beforeDOCTYPEPublicIdentifierState(StateData& data);
void DOCTYPEPublicIdentifierDoubleQuotedState(StateData& data);
void DOCTYPEPublicIdentifierSingleQuotedState(StateData& data);
void afterDOCTYPEPublicIdentifierState(StateData& data);
void betweenDOCTYPEPublicAndSystemIdentifiersState(StateData& data);
void afterDOCTYPESystemKeywordState(StateData& data);
void beforeDOCTYPESystemIdentifierState(StateData& data);
void DOCTYPESystemIdentifierDoubleQuotedState(StateData& data);
void DOCTYPESystemIdentifierSingleQuotedState(StateData& data);
void afterDOCTYPESystemIdentifierState(StateData& data);
void bogusDOCTYPEState(StateData& data);
void CDATASectionState(StateData& data);

} /* namespace States */
} /* namespace Tokenization */
} /* namespace Parse */
} /* namespace HTML */



#endif /* SRC_HTML_PARSE_TOKENIZATION_STATES_HPP_ */
