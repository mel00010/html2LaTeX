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

#include "TokenizationTypes.hpp"

#include <list>

#include <HTML/Microsyntaxes/ASCII/ASCII.hpp>

namespace HTML {
namespace Parse {
namespace Tokenization {

void Tokenizer::dataState() {
	switch (char32_t buf = consume()) {
		case '&':
			switchToState(CHARACTER_REFERENCE_IN_DATA);
			break;
		case '<':
			switchToState(TAG_OPEN);
			break;
		case '\0':
			emit(CharacterToken(buf));
			break;
		case EOF32:
			emit(EOFToken());
			break;
		default:
			emit(CharacterToken(buf));
			break;
	}
}

void Tokenizer::characterReferenceInDataState() {
	switchToState(DATA);
	TokenPair tokens = consumeCharacterReference();
	if (tokens.first != Token()) {
		emit(tokens.first);
	}
	if (tokens.second != Token()) {
		emit(tokens.second);
	}
	if (tokens == TokenPair()) {
		emit(CharacterToken('&'));
	}
}

void Tokenizer::RCDATAState() {
	switch (char32_t buf = consume()) {
		case '&':
			switchToState(CHARACTER_REFERENCE_IN_RCDATA);
			break;
		case '<':
			switchToState(RCDATA_LESS_THAN_SIGN);
			break;
		case '\0':
			emit(CharacterToken(U'\U0000FFFD'));
			break;
		case EOF32:
			emit(EOFToken());
			break;
		default:
			emit(CharacterToken(buf));
			break;
	}
}

void Tokenizer::characterReferenceINRCDATAState() {
	switchToState(RCDATA);
	TokenPair tokens = consumeCharacterReference();
	if (tokens.first != Token()) {
		emit(tokens.first);
	}
	if (tokens.second != Token()) {
		emit(tokens.second);
	}
	if (tokens == TokenPair()) {
		emit(CharacterToken('&'));
	}
}

void Tokenizer::RAWTEXTState() {
	switch (char32_t buf = consume()) {
		case '<':
			switchToState(RAWTEXT_LESS_THAN_SIGN);
			break;
		case '\0':
			emit(CharacterToken(U'\U0000FFFD'));
			break;
		case EOF32:
			emit(EOFToken());
			break;
		default:
			emit(CharacterToken(buf));
			break;
	}
}

void Tokenizer::scriptDataState() {
	switch (char32_t buf = consume()) {
		case '<':
			switchToState(SCRIPT_DATA_LESS_THAN_SIGN);
			break;
		case '\0':
			emit(CharacterToken(U'\U0000FFFD'));
			break;
		case EOF32:
			emit(EOFToken());
			break;
		default:
			emit(CharacterToken(buf));
			break;
	}
}

void Tokenizer::plainTextState() {
	switch (char32_t buf = consume()) {
		case '\0':
			emit(CharacterToken(U'\U0000FFFD'));
			break;
		case EOF32:
			emit(EOFToken());
			break;
		default:
			emit(CharacterToken(buf));
			break;
	}
}

void Tokenizer::tagOpenState() {
	switch (char32_t buf = consume()) {
		case '!':
			switchToState(MARKUP_DECLARATION_OPEN);
			break;
		case '/':
			switchToState(END_TAG_OPEN);
			break;
		case ASCII_UPPER_CASE_LETTER:
			tag_token_buffer = StartTagToken();
			tag_token_buffer.tag_name.push_back(Microsyntaxes::ASCII::toLower(buf));
			switchToState(TAG_NAME);
			break;
		case ASCII_LOWER_CASE_LETTER:
			tag_token_buffer = StartTagToken();
			tag_token_buffer.tag_name.push_back(buf);
			switchToState(TAG_NAME);
			break;
		case '?':
			switchToState(BOGUS_COMMENT);
			break;
		default:
			switchToState(DATA);
			emit(CharacterToken('<'));
			break;
	}
}

void Tokenizer::endTagOpenState() {
	switch (char32_t buf = consume()) {
		case ASCII_UPPER_CASE_LETTER:
			tag_token_buffer = EndTagToken();
			tag_token_buffer.tag_name.push_back(Microsyntaxes::ASCII::toLower(buf));
			switchToState(TAG_NAME);
			break;
		case ASCII_LOWER_CASE_LETTER:
			tag_token_buffer = EndTagToken();
			tag_token_buffer.tag_name.push_back(buf);
			switchToState(TAG_NAME);
			break;
		case '>':
			switchToState(DATA);
			break;
		case EOF32:
			switchToState(DATA);
			emit(CharacterToken('>'));
			emit(CharacterToken('/'));
			unconsume();
			break;
		default:
			switchToState(BOGUS_COMMENT);
			break;
	}
}

void Tokenizer::tagNameState() {
	switch (char32_t buf = consume()) {
		case '\t':
		case '\r':
		case '\f':
		case ' ':
			switchToState(BEFORE_ATTRIBUTE_NAME);
			break;
		case '/':
			switchToState(SELF_CLOSING_START_TAG);
			break;
		case ASCII_UPPER_CASE_LETTER:
			tag_token_buffer.tag_name.push_back(Microsyntaxes::ASCII::toLower(buf));
			break;
		case '\0':
			tag_token_buffer.tag_name.push_back(U'\U0000FFFD');
			break;
		case EOF32:
			switchToState(DATA);
			unconsume();
			break;
		default:
			tag_token_buffer.tag_name.push_back(buf);
			break;
	}
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

void Tokenizer::beforeAttributeNameState() {

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
