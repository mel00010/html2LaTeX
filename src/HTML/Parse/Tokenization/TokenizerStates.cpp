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

#include "Tokenizer.hpp"

#include "TokenizationMisc.hpp"
#include "TokenizationTypes.hpp"

#include <list>

#include <HTML/Parse/TreeConstruction/Dispatch.hpp>
#include <HTML/Microsyntaxes/ASCII/ASCII.hpp>

namespace HTML {
namespace Parse {
namespace Tokenization {

void Tokenizer::dataState() {
	if (pos >= string.length()) {
		TreeConstruction::dispatch(createEOFToken());
	} else {
		switch (string[pos]) {
			case '&':
				state = STATES::CHARACTER_REFERENCE_IN_DATA;
				break;
			case '<':
				state = STATES::TAG_OPEN;
				break;
			case '\0':
				TreeConstruction::dispatch(createCharacterToken(string[pos]));
				break;
			default:
				TreeConstruction::dispatch(createCharacterToken(string[pos]));
				break;
		}
	}
	pos++;
	return;
}

void Tokenizer::characterReferenceInDataState() {
	state = STATES::DATA;

	EmmittedTokens tokens = consumeCharacterReference();
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

void Tokenizer::RCDATAState() {
	if (pos >= string.length()) {
		TreeConstruction::dispatch(createEOFToken());
	} else {
		switch (string[pos]) {
			case '&':
				state = STATES::CHARACTER_REFERENCE_IN_RCDATA;
				break;
			case '<':
				state = STATES::RCDATA_LESS_THAN_SIGN;
				break;
			case '\0':
				TreeConstruction::dispatch(createCharacterToken(U'\U0000FFFD'));
				break;
			default:
				TreeConstruction::dispatch(createCharacterToken(string[pos]));
				break;
		}
	}
	pos++;
	return;
}

void Tokenizer::characterReferenceINRCDATAState() {
	state = STATES::RCDATA;
	EmmittedTokens tokens = consumeCharacterReference();
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

void Tokenizer::RAWTEXTState() {
	if (pos >= string.length()) {
		TreeConstruction::dispatch(createEOFToken());
	} else {
		switch (string[pos]) {
			case '<':
				state = STATES::RAWTEXT_LESS_THAN_SIGN;
				break;
			case '\0':
				TreeConstruction::dispatch(createCharacterToken(U'\U0000FFFD'));
				pos++;
				break;
			default:
				TreeConstruction::dispatch(createCharacterToken(string[pos]));
				break;
		}
	}
	pos++;
	return;
}

void Tokenizer::scriptDataState() {
	if (pos >= string.length()) {
		TreeConstruction::dispatch(createEOFToken());
	} else {
		switch (string[pos]) {
			case '<':
				state = STATES::SCRIPT_DATA_LESS_THAN_SIGN;
				break;
			case '\0':
				TreeConstruction::dispatch(createCharacterToken(U'\U0000FFFD'));
				pos++;
				break;
			default:
				TreeConstruction::dispatch(createCharacterToken(string[pos]));
				break;
		}
	}
	pos++;
	return;
}

void Tokenizer::plainTextState() {
	if (pos >= string.length()) {
		TreeConstruction::dispatch(createEOFToken());
	} else {
		switch (string[pos]) {
			case '\0':
				TreeConstruction::dispatch(createCharacterToken(U'\U0000FFFD'));
				pos++;
				break;
			default:
				TreeConstruction::dispatch(createCharacterToken(string[pos]));
				break;
		}
	}
	pos++;
	return;
}

void Tokenizer::tagOpenState() {
	if (pos >= string.length()) {
		TreeConstruction::dispatch(createEOFToken());
	} else {
		if (Microsyntaxes::ASCII::isASCIIUpper(string[pos])) {
			token_buffer = createStartTagToken(Microsyntaxes::ASCII::toLower(std::u32string(&string[pos])), false, { });
			/* Create new start tag token */
		} else if (Microsyntaxes::ASCII::isASCIILower(string[pos])) {
			token_buffer = createStartTagToken(std::u32string(&string[pos]), false, { });
		}
		switch (string[pos]) {
			case '!':
				state = STATES::MARKUP_DECLARATION_OPEN;
				break;
			case '/':
				state = STATES::END_TAG_OPEN;
				break;
			case '?':
				state = STATES::BOGUS_COMMENT;
				break;
			default:
				state = STATES::DATA;
				TreeConstruction::dispatch(createCharacterToken('>'));
				pos--;
				break;
		}
	}
	pos++;
	return;
}

void Tokenizer::endTagOpenState() {

}

void Tokenizer::tagNameState() {

}

void Tokenizer::RCDATALessThanSignState() {

}

void Tokenizer::RCDATAEndTagOpenState() {

}

void Tokenizer::RCDATAEndTagNameState() {

}

void Tokenizer::RAWTEXTLessThanSignState() {

}

void Tokenizer::RAWTEXTEndTagOpenState() {

}

void Tokenizer::RAWTEXTEndTagNameState() {

}

void Tokenizer::scriptDataLessThanSignState() {

}

void Tokenizer::scriptDataEndTagOpenState() {

}

void Tokenizer::scriptDataEndTagNameState() {

}

void Tokenizer::scriptDataEscapeStartState() {

}

void Tokenizer::scriptDataEscapeStartDashState() {

}

void Tokenizer::scriptDataEscapedState() {

}

void Tokenizer::scriptDataEscapedDashState() {

}

void Tokenizer::scriptDataEscapedDashDashState() {

}

void Tokenizer::scriptDataEscapedLessThanSignState() {

}
void Tokenizer::scriptDataEscapedEndTagNameState() {

}

void Tokenizer::scriptDataDoubleEscapeStartState() {

}

void Tokenizer::scriptDataDoubleEscapedState() {

}

void Tokenizer::scriptDataDoubleEscapedDashState() {

}

void Tokenizer::scriptDataDoubleEscapedDashDashState() {

}

void Tokenizer::scriptDataDoubleEscapedLessThanSignState() {

}

void Tokenizer::scriptDataDoubleEscapeEndState() {

}

void Tokenizer::beforeAttributeState() {

}

void Tokenizer::attributeNameState() {

}

void Tokenizer::afterAttributeNameState() {

}
void Tokenizer::beforeAttributeValueState() {

}
void Tokenizer::attributeValueDoubleQuotedState() {

}

void Tokenizer::attributeValueSingleQuotedState() {

}

void Tokenizer::attributeValueUnquotedState() {

}

void Tokenizer::characterReferenceInAttributeValueState() {

}

void Tokenizer::afterAttributeQuotedState() {

}

void Tokenizer::selfClosingStartTagState() {

}

void Tokenizer::bogusCommentState() {

}

void Tokenizer::markupDeclarationOpenState() {

}

void Tokenizer::commentStartState() {

}

void Tokenizer::commentStartDashState() {

}

void Tokenizer::commentState() {

}

void Tokenizer::commentEndDashState() {

}

void Tokenizer::commentEndState() {

}

void Tokenizer::commentEndBangState() {

}

void Tokenizer::DOCTYPEState() {

}

void Tokenizer::beforeDOCTYPENameState() {

}

void Tokenizer::DOCTYPENameState() {

}

void Tokenizer::afterDOCTYPENameState() {

}

void Tokenizer::afterDOCTYPEPublicKeywordState() {

}

void Tokenizer::beforeDOCTYPEPublicIdentifierState() {

}

void Tokenizer::DOCTYPEPublicIdentifierDoubleQuotedState() {

}

void Tokenizer::DOCTYPEPublicIdentifierSingleQuotedState() {

}

void Tokenizer::afterDOCTYPEPublicIdentifierState() {

}

void Tokenizer::betweenDOCTYPEPublicAndSystemIdentifiersState() {

}

void Tokenizer::afterDOCTYPESystemKeywordState() {

}

void Tokenizer::beforeDOCTYPESystemIdentifierState() {

}

void Tokenizer::DOCTYPESystemIdentifierDoubleQuotedState() {

}

void Tokenizer::DOCTYPESystemIdentifierSingleQuotedState() {

}

void Tokenizer::afterDOCTYPESystemIdentifierState() {

}

void Tokenizer::bogusDOCTYPEState() {

}

void Tokenizer::CDATASectionState() {

}


} /* namespace Tokenization */
} /* namespace Parse */
} /* namespace HTML */
