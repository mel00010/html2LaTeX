/*******************************************************************************
 * States.cpp
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
 * but WITHOUT ANY WARRANTY {

 } without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with html2LaTeX.  If not, see <http://www.gnu.org/licenses/>.
 *******************************************************************************/

#include "States.hpp"

#include "CharacterReference.hpp"
#include "TokenizationMisc.hpp"
#include "TokenizationTypes.hpp"

#include <list>

#include <HTML/Parse/TreeConstruction/Dispatch.hpp>
#include <HTML/Microsyntaxes/ASCII/ASCII.hpp>

namespace HTML {
namespace Parse {
namespace Tokenization {
namespace States {

void dataState(StateData& data) {
	if (data.pos >= data.string.length()) {
		TreeConstruction::dispatch(createEOFToken());
	} else {
		switch (data.string[data.pos]) {
			case '&':
				data.state = STATES::CHARACTER_REFERENCE_IN_DATA;
				break;
			case '<':
				data.state = STATES::TAG_OPEN;
				break;
			case '\0':
				TreeConstruction::dispatch(createCharacterToken(data.string[data.pos]));
				break;
			default:
				TreeConstruction::dispatch(createCharacterToken(data.string[data.pos]));
				break;
		}
	}
	data.pos++;
	return;
}

void characterReferenceInDataState(StateData& data) {
	data.state = STATES::DATA;

	EmmittedTokens tokens = consumeCharacterReference(data);
	if (tokens.first.type == TokenType::CHARACTER) {
		TreeConstruction::dispatch(tokens.first);
		if (tokens.second.type == TokenType::CHARACTER) {
			TreeConstruction::dispatch(tokens.second);
		}
	} else {
		TreeConstruction::dispatch(createCharacterToken('&'));
	}
	return;
}

void RCDATAState(StateData& data) {
	if (data.pos >= data.string.length()) {
		TreeConstruction::dispatch(createEOFToken());
	} else {
		switch (data.string[data.pos]) {
			case '&':
				data.state = STATES::CHARACTER_REFERENCE_IN_RCDATA;
				break;
			case '<':
				data.state = STATES::RCDATA_LESS_THAN_SIGN;
				break;
			case '\0':
				TreeConstruction::dispatch(createCharacterToken(U'\U0000FFFD'));
				break;
			default:
				TreeConstruction::dispatch(createCharacterToken(data.string[data.pos]));
				break;
		}
	}
	data.pos++;
	return;
}

void characterReferenceINRCDATAState(StateData& data) {
	data.state = STATES::RCDATA;
	EmmittedTokens tokens = consumeCharacterReference(data);
	if (tokens.first.type == TokenType::CHARACTER) {
		TreeConstruction::dispatch(tokens.first);
		if (tokens.second.type == TokenType::CHARACTER) {
			TreeConstruction::dispatch(tokens.second);
		}
	} else {
		TreeConstruction::dispatch(createCharacterToken('&'));
	}
	return;
}

void RAWTEXTState(StateData& data) {
	if (data.pos >= data.string.length()) {
		TreeConstruction::dispatch(createEOFToken());
	} else {
		switch (data.string[data.pos]) {
			case '<':
				data.state = STATES::RAWTEXT_LESS_THAN_SIGN;
				break;
			case '\0':
				TreeConstruction::dispatch(createCharacterToken(U'\U0000FFFD'));
				data.pos++;
				break;
			default:
				TreeConstruction::dispatch(createCharacterToken(data.string[data.pos]));
				break;
		}
	}
	data.pos++;
	return;
}

void scriptDataState(__attribute__ ((unused)) StateData& data) {
	if (data.pos >= data.string.length()) {
		TreeConstruction::dispatch(createEOFToken());
	} else {
		switch (data.string[data.pos]) {
			case '<':
				data.state = STATES::SCRIPT_DATA_LESS_THAN_SIGN;
				break;
			case '\0':
				TreeConstruction::dispatch(createCharacterToken(U'\U0000FFFD'));
				data.pos++;
				break;
			default:
				TreeConstruction::dispatch(createCharacterToken(data.string[data.pos]));
				break;
		}
	}
	data.pos++;
	return;
}

void plainTextState(__attribute__ ((unused)) StateData& data) {
	if (data.pos >= data.string.length()) {
		TreeConstruction::dispatch(createEOFToken());
	} else {
		switch (data.string[data.pos]) {
			case '\0':
				TreeConstruction::dispatch(createCharacterToken(U'\U0000FFFD'));
				data.pos++;
				break;
			default:
				TreeConstruction::dispatch(createCharacterToken(data.string[data.pos]));
				break;
		}
	}
	data.pos++;
	return;
}

void tagOpenState(__attribute__ ((unused)) StateData& data) {
	if (data.pos >= data.string.length()) {
		TreeConstruction::dispatch(createEOFToken());
	} else {
		if (Microsyntaxes::ASCII::isASCIIUpper(data.string[data.pos])) {
			data.token_buffer = createStartTagToken(Microsyntaxes::ASCII::toLower(std::u32string(&data.string[data.pos])), false, { });
			/* Create new start tag token */
		} else if (Microsyntaxes::ASCII::isASCIILower(data.string[data.pos])) {
			data.token_buffer = createStartTagToken(std::u32string(&data.string[data.pos]), false, { });
		}
		switch (data.string[data.pos]) {
			case '!':
				data.state = STATES::MARKUP_DECLARATION_OPEN;
				break;
			case '/':
				data.state = STATES::END_TAG_OPEN;
				break;
			case '?':
				data.state = STATES::BOGUS_COMMENT;
				break;
			default:
				data.state = STATES::DATA;
				TreeConstruction::dispatch(createCharacterToken('>'));
				data.pos--;
				break;
		}
	}
	data.pos++;
	return;
}

void endTagOpenState(__attribute__ ((unused)) StateData& data) {

}

void tagNameState(__attribute__ ((unused)) StateData& data) {

}

void RCDATALessThanSignState(__attribute__ ((unused)) StateData& data) {

}

void RCDATAEndTagOpenState(__attribute__ ((unused)) StateData& data) {

}

void RCDATAEndTagNameState(__attribute__ ((unused)) StateData& data) {

}

void RAWTEXTLessThanSignState(__attribute__ ((unused)) StateData& data) {

}

void RAWTEXTEndTagOpenState(__attribute__ ((unused)) StateData& data) {

}

void RAWTEXTEndTagNameState(__attribute__ ((unused)) StateData& data) {

}

void scriptDataLessThanSignState(__attribute__ ((unused)) StateData& data) {

}

void scriptDataEndTagOpenState(__attribute__ ((unused)) StateData& data) {

}

void scriptDataEndTagNameState(__attribute__ ((unused)) StateData& data) {

}

void scriptDataEscapeStartState(__attribute__ ((unused)) StateData& data) {

}

void scriptDataEscapeStartDashState(__attribute__ ((unused)) StateData& data) {

}

void scriptDataEscapedState(__attribute__ ((unused)) StateData& data) {

}

void scriptDataEscapedDashState(__attribute__ ((unused)) StateData& data) {

}

void scriptDataEscapedDashDashState(__attribute__ ((unused)) StateData& data) {

}

void scriptDataEscapedLessThanSignState(__attribute__ ((unused)) StateData& data) {

}
void scriptDataEscapedEndTagNameState(__attribute__ ((unused)) StateData& data) {

}

void scriptDataDoubleEscapeStartState(__attribute__ ((unused)) StateData& data) {

}

void scriptDataDoubleEscapedState(__attribute__ ((unused)) StateData& data) {

}

void scriptDataDoubleEscapedDashState(__attribute__ ((unused)) StateData& data) {

}

void scriptDataDoubleEscapedDashDashState(__attribute__ ((unused)) StateData& data) {

}

void scriptDataDoubleEscapedLessThanSignState(__attribute__ ((unused)) StateData& data) {

}

void scriptDataDoubleEscapeEndState(__attribute__ ((unused)) StateData& data) {

}

void beforeAttributeState(__attribute__ ((unused)) StateData& data) {

}

void attributeNameState(__attribute__ ((unused)) StateData& data) {

}

void afterAttributeNameState(__attribute__ ((unused)) StateData& data) {

}
void beforeAttributeValueState(__attribute__ ((unused)) StateData& data) {

}
void attributeValueDoubleQuotedState(__attribute__ ((unused)) StateData& data) {

}

void attributeValueSingleQuotedState(__attribute__ ((unused)) StateData& data) {

}

void attributeValueUnquotedState(__attribute__ ((unused)) StateData& data) {

}

void characterReferenceInAttributeValueState(__attribute__ ((unused)) StateData& data) {

}

void afterAttributeQuotedState(__attribute__ ((unused)) StateData& data) {

}

void selfClosingStartTagState(__attribute__ ((unused)) StateData& data) {

}

void bogusCommentState(__attribute__ ((unused)) StateData& data) {

}

void markupDeclarationOpenState(__attribute__ ((unused)) StateData& data) {

}

void commentStartState(__attribute__ ((unused)) StateData& data) {

}

void commentStartDashState(__attribute__ ((unused)) StateData& data) {

}

void commentState(__attribute__ ((unused)) StateData& data) {

}

void commentEndDashState(__attribute__ ((unused)) StateData& data) {

}

void commentEndState(__attribute__ ((unused)) StateData& data) {

}

void commentEndBangState(__attribute__ ((unused)) StateData& data) {

}

void DOCTYPEState(__attribute__ ((unused)) StateData& data) {

}

void beforeDOCTYPENameState(__attribute__ ((unused)) StateData& data) {

}

void DOCTYPENameState(__attribute__ ((unused)) StateData& data) {

}

void afterDOCTYPENameState(__attribute__ ((unused)) StateData& data) {

}

void afterDOCTYPEPublicKeywordState(__attribute__ ((unused)) StateData& data) {

}

void beforeDOCTYPEPublicIdentifierState(__attribute__ ((unused)) StateData& data) {

}

void DOCTYPEPublicIdentifierDoubleQuotedState(__attribute__ ((unused)) StateData& data) {

}

void DOCTYPEPublicIdentifierSingleQuotedState(__attribute__ ((unused)) StateData& data) {

}

void afterDOCTYPEPublicIdentifierState(__attribute__ ((unused)) StateData& data) {

}

void betweenDOCTYPEPublicAndSystemIdentifiersState(__attribute__ ((unused)) StateData& data) {

}

void afterDOCTYPESystemKeywordState(__attribute__ ((unused)) StateData& data) {

}

void beforeDOCTYPESystemIdentifierState(__attribute__ ((unused)) StateData& data) {

}

void DOCTYPESystemIdentifierDoubleQuotedState(__attribute__ ((unused)) StateData& data) {

}

void DOCTYPESystemIdentifierSingleQuotedState(__attribute__ ((unused)) StateData& data) {

}

void afterDOCTYPESystemIdentifierState(__attribute__ ((unused)) StateData& data) {

}

void bogusDOCTYPEState(__attribute__ ((unused)) StateData& data) {

}

void CDATASectionState(__attribute__ ((unused)) StateData& data) {

}


} /* namespace States */
} /* namespace Tokenization */
} /* namespace Parse */
} /* namespace HTML */
