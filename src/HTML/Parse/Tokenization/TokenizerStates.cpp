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

// Section 8.2.4.1
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

// Section 8.2.4.2
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

// Section 8.2.4.3
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

// Section 8.2.4.4
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

// Section 8.2.4.5
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

// Section 8.2.4.6
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

// Section 8.2.4.7
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

// Section 8.2.4.9=8
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

// Section 8.2.4.9
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

// Section 8.2.4.10
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

// Section 8.2.4.11
void Tokenizer::RCDATALessThanSignState() {

}

// Section 8.2.4.12
void Tokenizer::RCDATAEndTagOpenState() {

}

// Section 8.2.4.13
void Tokenizer::RCDATAEndTagNameState() {

}

// Section 8.2.4.14
void Tokenizer::RAWTEXTLessThanSignState() {

}

// Section 8.2.4.15
void Tokenizer::RAWTEXTEndTagOpenState() {

}

// Section 8.2.4.16
void Tokenizer::RAWTEXTEndTagNameState() {

}

// Section 8.2.4.17
void Tokenizer::scriptDataLessThanSignState() {

}

// Section 8.2.4.18
void Tokenizer::scriptDataEndTagOpenState() {

}

// Section 8.2.4.19
void Tokenizer::scriptDataEndTagNameState() {

}

// Section 8.2.4.20
void Tokenizer::scriptDataEscapeStartState() {

}

// Section 8.2.4.21
void Tokenizer::scriptDataEscapeStartDashState() {

}

// Section 8.2.4.22
void Tokenizer::scriptDataEscapedState() {

}

// Section 8.2.4.23
void Tokenizer::scriptDataEscapedDashState() {

}

// Section 8.2.4.24
void Tokenizer::scriptDataEscapedDashDashState() {

}

// Section 8.2.4.25
void Tokenizer::scriptDataEscapedLessThanSignState() {

}

// Section 8.2.4.26
void Tokenizer::scriptDataEscapedEndTagOpenState() {

}

// Section 8.2.4.27
void Tokenizer::scriptDataEscapedEndTagNameState() {

}

// Section 8.2.4.28
void Tokenizer::scriptDataDoubleEscapeStartState() {

}

// Section 8.2.4.29
void Tokenizer::scriptDataDoubleEscapedState() {

}

// Section 8.2.4.30
void Tokenizer::scriptDataDoubleEscapedDashState() {

}

// Section 8.2.4.31
void Tokenizer::scriptDataDoubleEscapedDashDashState() {

}

// Section 8.2.4.32
void Tokenizer::scriptDataDoubleEscapedLessThanSignState() {

}

// Section 8.2.4.33
void Tokenizer::scriptDataDoubleEscapeEndState() {

}

// Section 8.2.4.34
void Tokenizer::beforeAttributeNameState() {

}

// Section 8.2.4.35
void Tokenizer::attributeNameState() {

}

// Section 8.2.4.36
void Tokenizer::afterAttributeNameState() {

}

// Section 8.2.4.37
void Tokenizer::beforeAttributeValueState() {

}

// Section 8.2.4.38
void Tokenizer::attributeValueDoubleQuotedState() {

}

// Section 8.2.4.39
void Tokenizer::attributeValueSingleQuotedState() {

}

// Section 8.2.4.30
void Tokenizer::attributeValueUnquotedState() {

}

// Section 8.2.4.41
void Tokenizer::characterReferenceInAttributeValueState() {

}

// Section 8.2.4.42
void Tokenizer::afterAttributeQuotedState() {

}

// Section 8.2.4.43
void Tokenizer::selfClosingStartTagState() {

}

// Section 8.2.4.44
void Tokenizer::bogusCommentState() {

}

// Section 8.2.4.45
void Tokenizer::markupDeclarationOpenState() {

}

// Section 8.2.4.46
void Tokenizer::commentStartState() {

}

// Section 8.2.4.47
void Tokenizer::commentStartDashState() {

}

// Section 8.2.4.48
void Tokenizer::commentState() {

}

// Section 8.2.4.49
void Tokenizer::commentEndDashState() {

}

// Section 8.2.4.50
void Tokenizer::commentEndState() {

}

// Section 8.2.4.51
void Tokenizer::commentEndBangState() {

}

// Section 8.2.4.52
void Tokenizer::DOCTYPEState() {

}

// Section 8.2.4.53
void Tokenizer::beforeDOCTYPENameState() {

}

// Section 8.2.4.54
void Tokenizer::DOCTYPENameState() {

}

// Section 8.2.4.55
void Tokenizer::afterDOCTYPENameState() {

}

// Section 8.2.4.56
void Tokenizer::afterDOCTYPEPublicKeywordState() {

}

// Section 8.2.4.57
void Tokenizer::beforeDOCTYPEPublicIdentifierState() {

}

// Section 8.2.4.58
void Tokenizer::DOCTYPEPublicIdentifierDoubleQuotedState() {

}

// Section 8.2.4.59
void Tokenizer::DOCTYPEPublicIdentifierSingleQuotedState() {

}

// Section 8.2.4.60
void Tokenizer::afterDOCTYPEPublicIdentifierState() {

}

// Section 8.2.4.61
void Tokenizer::betweenDOCTYPEPublicAndSystemIdentifiersState() {

}

// Section 8.2.4.62
void Tokenizer::afterDOCTYPESystemKeywordState() {

}

// Section 8.2.4.63
void Tokenizer::beforeDOCTYPESystemIdentifierState() {

}

// Section 8.2.4.64
void Tokenizer::DOCTYPESystemIdentifierDoubleQuotedState() {

}

// Section 8.2.4.65
void Tokenizer::DOCTYPESystemIdentifierSingleQuotedState() {

}

// Section 8.2.4.66
void Tokenizer::afterDOCTYPESystemIdentifierState() {

}

// Section 8.2.4.67
void Tokenizer::bogusDOCTYPEState() {

}

// Section 8.2.4.68
void Tokenizer::CDATASectionState() {

}


} /* namespace Tokenization */
} /* namespace Parse */
} /* namespace HTML */
