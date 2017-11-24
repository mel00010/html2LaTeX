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

#include <vector>

#include <HTML/Microsyntaxes/ASCII/ASCII.hpp>

namespace HTML {
namespace Parse {
namespace Tokenization {

using namespace Microsyntaxes::ASCII;

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
	switch(consumeCharacterReference()) {
		case 2:
			emit(pop(char_tokens));
			emit(pop(char_tokens));
			break;
		case 1:
			emit(pop(char_tokens));
			break;
		case 0:
			emit(CharacterToken('&'));
			break;
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
	switch(consumeCharacterReference()) {
		case 2: {
			emit(pop(char_tokens));
			emit(pop(char_tokens));
			break;
		}
		case 1: {
			emit(pop(char_tokens));
			break;
		}
		case 0: {
			emit(CharacterToken('&'));
			break;
		}
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

// Section 8.2.4.8
void Tokenizer::tagOpenState() {
	switch (char32_t buf = consume()) {
		case '!':
			switchToState(MARKUP_DECLARATION_OPEN);
			break;
		case '/':
			switchToState(END_TAG_OPEN);
			break;
		case ASCII_UPPER_CASE_LETTER:
			tag = StartTagToken();
			tag.tag_name.push_back(toLower(buf));
			switchToState(TAG_NAME);
			break;
		case ASCII_LOWER_CASE_LETTER:
			tag = StartTagToken();
			tag.tag_name.push_back(buf);
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
			tag = EndTagToken();
			tag.tag_name.push_back(toLower(buf));
			switchToState(TAG_NAME);
			break;
		case ASCII_LOWER_CASE_LETTER:
			tag = EndTagToken();
			tag.tag_name.push_back(buf);
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
			tag.tag_name.push_back(toLower(buf));
			break;
		case '\0':
			tag.tag_name.push_back(U'\U0000FFFD');
			break;
		case EOF32:
			switchToState(DATA);
			unconsume();
			break;
		default:
			tag.tag_name.push_back(buf);
			break;
	}
}

// Section 8.2.4.11
void Tokenizer::RCDATALessThanSignState() {
	switch (consume()) {
		case '/':
			temporary_buffer = U"";
			switchToState(RCDATA_END_TAG_OPEN);
			break;
		default:
			switchToState(RCDATA);
			emit(CharacterToken('<'));
			unconsume();
			break;
	}
}

// Section 8.2.4.12
void Tokenizer::RCDATAEndTagOpenState() {
	switch (char32_t buf = consume()) {
		case ASCII_UPPER_CASE_LETTER:
			tag = EndTagToken();
			tag.tag_name.push_back(toLower(buf));
			temporary_buffer.push_back(buf);
			switchToState(RCDATA_END_TAG_NAME);
			break;
		case ASCII_LOWER_CASE_LETTER:
			tag = EndTagToken();
			tag.tag_name.push_back(buf);
			temporary_buffer.push_back(buf);
			switchToState(RCDATA_END_TAG_NAME);
			break;
		default:
			switchToState(RCDATA);
			emit(CharacterToken('<'));
			emit(CharacterToken('/'));
			unconsume();
			break;
	}
}

// Section 8.2.4.13
void Tokenizer::RCDATAEndTagNameState() {
	switch (char32_t buf = consume()) {
		case '\t':
		case '\n':
		case '\f':
		case ' ':
			if(!isAppropriateEndTagToken()) {
				break; // Go to default case, which for brevity is outside the switch block
			}
			switchToState(BEFORE_ATTRIBUTE_NAME);
			return;
		case '/':
			if(!isAppropriateEndTagToken()) {
				break; // Go to default case
			}
			switchToState(SELF_CLOSING_START_TAG);
			return;
		case '>':
			if(!isAppropriateEndTagToken()) {
				break; // Go to default case
			}
			switchToState(DATA);
			emit(tag);
			tag = TagToken();
			return;
		case ASCII_UPPER_CASE_LETTER:
			tag.tag_name.push_back(toLower(buf));
			temporary_buffer.push_back(buf);
			return;
		case ASCII_LOWER_CASE_LETTER:
			tag.tag_name.push_back(buf);
			temporary_buffer.push_back(buf);
			return;
		default:
			break; // Go to default case
	}
	switchToState(RCDATA);
	emit(CharacterToken('<'));
	emit(CharacterToken('/'));
	for(auto& i : temporary_buffer) {
		emit(CharacterToken(i));
	}
	unconsume();
}

// Section 8.2.4.14
void Tokenizer::RAWTEXTLessThanSignState() {
	switch (consume()) {
		case '/':
			temporary_buffer = U"";
			switchToState(RAWTEXT_END_TAG_OPEN);
			break;
		default:
			switchToState(RAWTEXT);
			emit(CharacterToken('<'));
			unconsume();
			break;
	}
}

// Section 8.2.4.15
void Tokenizer::RAWTEXTEndTagOpenState() {
	switch (char32_t buf = consume()) {
		case ASCII_UPPER_CASE_LETTER:
			tag = EndTagToken();
			tag.tag_name.push_back(toLower(buf));
			temporary_buffer.push_back(buf);
			switchToState(RAWTEXT_END_TAG_NAME);
			break;
		case ASCII_LOWER_CASE_LETTER:
			tag = EndTagToken();
			tag.tag_name.push_back(buf);
			temporary_buffer.push_back(buf);
			switchToState(RAWTEXT_END_TAG_NAME);
			break;
		default:
			switchToState(RAWTEXT);
			emit(CharacterToken('<'));
			emit(CharacterToken('/'));
			unconsume();
			break;
	}
}

// Section 8.2.4.16
void Tokenizer::RAWTEXTEndTagNameState() {
	switch (char32_t buf = consume()) {
		case '\t':
		case '\n':
		case '\f':
		case ' ':
			if(!isAppropriateEndTagToken()) {
				break; // Go to default case, which for brevity is outside the switch block
			}
			switchToState(BEFORE_ATTRIBUTE_NAME);
			return;
		case '/':
			if(!isAppropriateEndTagToken()) {
				break; // Go to default case
			}
			switchToState(SELF_CLOSING_START_TAG);
			return;
		case '>':
			if(!isAppropriateEndTagToken()) {
				break; // Go to default case
			}
			switchToState(DATA);
			emit(tag);
			tag = TagToken();
			return;
		case ASCII_UPPER_CASE_LETTER:
			tag.tag_name.push_back(toLower(buf));
			temporary_buffer.push_back(buf);
			return;
		case ASCII_LOWER_CASE_LETTER:
			tag.tag_name.push_back(buf);
			temporary_buffer.push_back(buf);
			return;
		default:
			break; // Go to default case
	}
	switchToState(RAWTEXT);
	emit(CharacterToken('<'));
	emit(CharacterToken('/'));
	for(auto& i : temporary_buffer) {
		emit(CharacterToken(i));
	}
	unconsume();
}

// Section 8.2.4.17
void Tokenizer::scriptDataLessThanSignState() {
	switch (consume()) {
		case '/':
			temporary_buffer = U"";
			switchToState(SCRIPT_DATA_END_TAG_OPEN);
			break;
		case '!':
			switchToState(SCRIPT_DATA_ESCAPE_START);
			emit(CharacterToken('<'));
			emit(CharacterToken('!'));
			break;
		default:
			switchToState(SCRIPT_DATA);
			emit(CharacterToken('<'));
			unconsume();
			break;
	}
}

// Section 8.2.4.18
void Tokenizer::scriptDataEndTagOpenState() {
	switch (char32_t buf = consume()) {
		case ASCII_UPPER_CASE_LETTER:
			tag = EndTagToken();
			tag.tag_name.push_back(toLower(buf));
			temporary_buffer.push_back(buf);
			switchToState(SCRIPT_DATA_END_TAG_NAME);
			break;
		case ASCII_LOWER_CASE_LETTER:
			tag = EndTagToken();
			tag.tag_name.push_back(buf);
			temporary_buffer.push_back(buf);
			switchToState(SCRIPT_DATA_END_TAG_NAME);
			break;
		default:
			switchToState(SCRIPT_DATA);
			emit(CharacterToken('<'));
			emit(CharacterToken('/'));
			unconsume();
			break;
	}
}

// Section 8.2.4.19
void Tokenizer::scriptDataEndTagNameState() {
	switch (char32_t buf = consume()) {
		case '\t':
		case '\n':
		case '\f':
		case ' ':
			if(!isAppropriateEndTagToken()) {
				break; // Go to default case, which for brevity is outside the switch block
			}
			switchToState(BEFORE_ATTRIBUTE_NAME);
			return;
		case '/':
			if(!isAppropriateEndTagToken()) {
				break; // Go to default case
			}
			switchToState(SELF_CLOSING_START_TAG);
			return;
		case '>':
			if(!isAppropriateEndTagToken()) {
				break; // Go to default case
			}
			switchToState(DATA);
			emit(tag);
			tag = TagToken();
			return;
		case ASCII_UPPER_CASE_LETTER:
			tag.tag_name.push_back(toLower(buf));
			temporary_buffer.push_back(buf);
			return;
		case ASCII_LOWER_CASE_LETTER:
			tag.tag_name.push_back(buf);
			temporary_buffer.push_back(buf);
			return;
		default:
			break; // Go to default case
	}
	switchToState(SCRIPT_DATA);
	emit(CharacterToken('<'));
	emit(CharacterToken('/'));
	for(auto& i : temporary_buffer) {
		emit(CharacterToken(i));
	}
	unconsume();
}

// Section 8.2.4.20
void Tokenizer::scriptDataEscapeStartState() {
	switch (consume()) {
		case '-':
			switchToState(SCRIPT_DATA_ESCAPE_START_DASH);
			emit(CharacterToken('-'));
			break;
		default:
			switchToState(SCRIPT_DATA);
			unconsume();
			break;
	}
}

// Section 8.2.4.21
void Tokenizer::scriptDataEscapeStartDashState() {
	switch (consume()) {
		case '-':
			switchToState(SCRIPT_DATA_ESCAPED_DASH_DASH);
			emit(CharacterToken('-'));
			break;
		default:
			switchToState(SCRIPT_DATA);
			unconsume();
			break;
	}
}

// Section 8.2.4.22
void Tokenizer::scriptDataEscapedState() {
	switch (char32_t buf = consume()) {
		case '-':
			switchToState(SCRIPT_DATA_ESCAPED_DASH);
			emit(CharacterToken('-'));
			break;
		case '<':
			switchToState(SCRIPT_DATA_ESCAPED_LESS_THAN_SIGN);
			break;
		case '\0':
			emitParseError();
			emit(CharacterToken(U'\U0000FFFD'));
			break;
		case EOF32:
			switchToState(DATA);
			emitParseError();
			unconsume();
			break;
		default:
			emit(CharacterToken(buf));
			break;
	}
}

// Section 8.2.4.23
void Tokenizer::scriptDataEscapedDashState() {
	switch (char32_t buf = consume()) {
		case '-':
			switchToState(SCRIPT_DATA_ESCAPED_DASH_DASH);
			emit(CharacterToken('-'));
			break;
		case '<':
			switchToState(SCRIPT_DATA_ESCAPED_LESS_THAN_SIGN);
			break;
		case '\0':
			emitParseError();
			switchToState(SCRIPT_DATA_ESCAPED);
			emit(CharacterToken(U'\U0000FFFD'));
			break;
		case EOF32:
			emitParseError();
			switchToState(DATA);
			unconsume();
			break;
		default:
			switchToState(SCRIPT_DATA_ESCAPED);
			emit(CharacterToken(buf));
			break;
	}
}

// Section 8.2.4.24
void Tokenizer::scriptDataEscapedDashDashState() {
	switch (char32_t buf = consume()) {
		case '-':
			emit(CharacterToken('-'));
			break;
		case '<':
			switchToState(SCRIPT_DATA_ESCAPED_LESS_THAN_SIGN);
			break;
		case '>':
			switchToState(SCRIPT_DATA);
			emit(CharacterToken('>'));
			break;
		case '\0':
			emitParseError();
			switchToState(SCRIPT_DATA_ESCAPED);
			emit(CharacterToken(U'\U0000FFFD'));
			break;
		case EOF32:
			emitParseError();
			switchToState(DATA);
			unconsume();
			break;
		default:
			switchToState(SCRIPT_DATA_ESCAPED);
			emit(CharacterToken(buf));
			break;
	}
}

// Section 8.2.4.25
void Tokenizer::scriptDataEscapedLessThanSignState() {
	switch (char32_t buf = consume()) {
		case '/':
			temporary_buffer = U"";
			switchToState(SCRIPT_DATA_ESCAPED_END_TAG_OPEN);
			break;
		case ASCII_UPPER_CASE_LETTER:
			temporary_buffer = U"";
			temporary_buffer.push_back(toLower(buf));
			switchToState(SCRIPT_DATA_DOUBLE_ESCAPE_START);
			emit(CharacterToken('<'));
			emit(CharacterToken(buf));
			break;
		case ASCII_LOWER_CASE_LETTER:
			temporary_buffer = U"";
			temporary_buffer.push_back(buf);
			switchToState(SCRIPT_DATA_DOUBLE_ESCAPE_START);
			emit(CharacterToken('<'));
			emit(CharacterToken(buf));
			break;
		default:
			switchToState(SCRIPT_DATA_ESCAPED);
			emit(CharacterToken('<'));
			unconsume();
			break;
	}
}

// Section 8.2.4.26
void Tokenizer::scriptDataEscapedEndTagOpenState() {
	switch (char32_t buf = consume()) {
		case ASCII_UPPER_CASE_LETTER:
			tag = EndTagToken();
			tag.tag_name.push_back(toLower(buf));
			temporary_buffer.push_back(buf);
			switchToState(SCRIPT_DATA_ESCAPED_END_TAG_NAME);
			break;
		case ASCII_LOWER_CASE_LETTER:
			tag = EndTagToken();
			tag.tag_name.push_back(buf);
			temporary_buffer.push_back(buf);
			switchToState(SCRIPT_DATA_ESCAPED_END_TAG_NAME);
			break;
		default:
			switchToState(SCRIPT_DATA_ESCAPED);
			emit(CharacterToken('<'));
			emit(CharacterToken('/'));
			unconsume();
			break;
	}
}

// Section 8.2.4.27
void Tokenizer::scriptDataEscapedEndTagNameState() {
	switch (char32_t buf = consume()) {
			case '\t':
			case '\n':
			case '\f':
			case ' ':
				if(!isAppropriateEndTagToken()) {
					break; // Go to default case, which for brevity is outside the switch block
				}
				switchToState(BEFORE_ATTRIBUTE_NAME);
				return;
			case '/':
				if(!isAppropriateEndTagToken()) {
					break; // Go to default case
				}
				switchToState(SELF_CLOSING_START_TAG);
				return;
			case '>':
				if(!isAppropriateEndTagToken()) {
					break; // Go to default case
				}
				switchToState(DATA);
				emit(tag);
				tag = TagToken();
				return;
			case ASCII_UPPER_CASE_LETTER:
				tag.tag_name.push_back(toLower(buf));
				temporary_buffer.push_back(buf);
				return;
			case ASCII_LOWER_CASE_LETTER:
				tag.tag_name.push_back(buf);
				temporary_buffer.push_back(buf);
				return;
			default:
				break; // Go to default case
		}
		switchToState(SCRIPT_DATA_ESCAPED);
		emit(CharacterToken('<'));
		emit(CharacterToken('/'));
		for(auto& i : temporary_buffer) {
			emit(CharacterToken(i));
		}
		unconsume();
}

// Section 8.2.4.28
void Tokenizer::scriptDataDoubleEscapeStartState() {
	switch (char32_t buf = consume()) {
		case '\t':
		case '\n':
		case '\f':
		case ' ':
		case '/':
		case '>':
			if(temporary_buffer == U"script") {
				switchToState(SCRIPT_DATA_DOUBLE_ESCAPED);
			} else {
				switchToState(SCRIPT_DATA_ESCAPED);
			}
			emit(CharacterToken(buf));
			break;
		case ASCII_UPPER_CASE_LETTER:
			temporary_buffer.push_back(toLower(buf));
			emit(CharacterToken(buf));
			break;
		case ASCII_LOWER_CASE_LETTER:
			temporary_buffer.push_back(buf);
			emit(CharacterToken(buf));
			break;
		default:
			switchToState(SCRIPT_DATA_ESCAPED);
			unconsume();
			break;
	}
}

// Section 8.2.4.29
void Tokenizer::scriptDataDoubleEscapedState() {
	switch (char32_t buf = consume()) {
		case '-':
			switchToState(SCRIPT_DATA_DOUBLE_ESCAPED_DASH);
			emit(CharacterToken('-'));
			break;
		case '<':
			switchToState(SCRIPT_DATA_DOUBLE_ESCAPED_LESS_THAN_SIGN);
			emit(CharacterToken('<'));
			break;
		case '\0':
			emitParseError();
			emit(CharacterToken(U'\U0000FFFD'));
			break;
		case EOF32:
			emitParseError();
			switchToState(DATA);
			unconsume();
			break;
		default:
			emit(CharacterToken(buf));
			break;
	}
}

// Section 8.2.4.30
void Tokenizer::scriptDataDoubleEscapedDashState() {
	switch (char32_t buf = consume()) {
		case '-':
			switchToState(SCRIPT_DATA_DOUBLE_ESCAPED_DASH_DASH);
			emit(CharacterToken('-'));
			break;
		case '<':
			switchToState(SCRIPT_DATA_DOUBLE_ESCAPED_LESS_THAN_SIGN);
			emit(CharacterToken('<'));
			break;
		case '\0':
			emitParseError();
			switchToState(SCRIPT_DATA_DOUBLE_ESCAPED);
			emit(CharacterToken(U'\U0000FFFD'));
			break;
		case EOF32:
			emitParseError();
			switchToState(DATA);
			unconsume();
			break;
		default:
			switchToState(SCRIPT_DATA_DOUBLE_ESCAPED);
			emit(CharacterToken(buf));
			break;
	}
}

// Section 8.2.4.31
void Tokenizer::scriptDataDoubleEscapedDashDashState() {
	switch (char32_t buf = consume()) {
		case '-':
			switchToState(SCRIPT_DATA_DOUBLE_ESCAPED_DASH_DASH);
			emit(CharacterToken('-'));
			break;
		case '<':
			switchToState(SCRIPT_DATA_DOUBLE_ESCAPED_LESS_THAN_SIGN);
			emit(CharacterToken('<'));
			break;
		case '>':
			switchToState(SCRIPT_DATA);
			emit(CharacterToken('>'));
			break;
		case '\0':
			emitParseError();
			switchToState(SCRIPT_DATA_DOUBLE_ESCAPED);
			emit(CharacterToken(U'\U0000FFFD'));
			break;
		case EOF32:
			emitParseError();
			switchToState(DATA);
			unconsume();
			break;
		default:
			switchToState(SCRIPT_DATA_DOUBLE_ESCAPED);
			emit(CharacterToken(buf));
			break;
	}
}

// Section 8.2.4.32
void Tokenizer::scriptDataDoubleEscapedLessThanSignState() {
	switch (consume()) {
		case '/':
			temporary_buffer = U"";
			switchToState(SCRIPT_DATA_DOUBLE_ESCAPE_END);
			emit(CharacterToken('/'));
			break;
		default:
			switchToState(SCRIPT_DATA_DOUBLE_ESCAPED);
			unconsume();
			break;
	}
}

// Section 8.2.4.33
void Tokenizer::scriptDataDoubleEscapeEndState() {
	switch (char32_t buf = consume()) {
		case '\t':
		case '\n':
		case '\f':
		case ' ':
		case '/':
		case '>':
			if(temporary_buffer == U"script") {
				switchToState(SCRIPT_DATA_ESCAPED);
			} else {
				switchToState(SCRIPT_DATA_DOUBLE_ESCAPED);
			}
			emit(CharacterToken(buf));
			break;
		case ASCII_UPPER_CASE_LETTER:
			temporary_buffer.push_back(toLower(buf));
			emit(CharacterToken(buf));
			break;
		case ASCII_LOWER_CASE_LETTER:
			temporary_buffer.push_back(buf);
			emit(CharacterToken(buf));
			break;
		default:
			switchToState(SCRIPT_DATA_DOUBLE_ESCAPED);
			unconsume();
			break;
	}
}

// Section 8.2.4.34
void Tokenizer::beforeAttributeNameState() {
	switch (char32_t buf = consume()) {
		case '\t':
		case '\n':
		case '\f':
		case ' ':
			break;
		case '/':
			switchToState(SELF_CLOSING_START_TAG);
			break;
		case '>':
			switchToState(DATA);
			emit(tag);
			return;
		case ASCII_UPPER_CASE_LETTER:
			attribute = Attribute();
			attribute.name.push_back(toLower(buf));
			switchToState(ATTRIBUTE_NAME);
			break;
		case '\0':
			emitParseError();
			attribute = Attribute();
			attribute.name.push_back(U'\U0000FFFD');
			switchToState(ATTRIBUTE_NAME);
			break;
		case '"':
		case '\'':
		case '<':
		case '=':
			emitParseError();
			attribute = Attribute();
			attribute.name.push_back(buf);
			switchToState(ATTRIBUTE_NAME);
			break;
		case EOF32:
			emitParseError();
			switchToState(DATA);
			unconsume();
			break;
		default:
			attribute = Attribute();
			attribute.name.push_back(buf);
			switchToState(ATTRIBUTE_NAME);
			break;
	}

}

// Section 8.2.4.35
void Tokenizer::attributeNameState() {
	switch (char32_t buf = consume()) {
		case '\t':
		case '\n':
		case '\f':
		case ' ':
			isAttributeNameUnique();
			switchToState(AFTER_ATTRIBUTE_NAME);
			break;
		case '/':
			isAttributeNameUnique();
			switchToState(SELF_CLOSING_START_TAG);
			break;
		case '=':
			isAttributeNameUnique();
			switchToState(BEFORE_ATTRIBUTE_VALUE);
			break;
		case '>':
			isAttributeNameUnique();
			switchToState(DATA);
			emit(tag);
			break;
		case ASCII_UPPER_CASE_LETTER:
			attribute.name.push_back(toLower(buf));
			break;
		case '\0':
			emitParseError();
			attribute.name.push_back(U'\U0000FFFD');
			break;
		case '"':
		case '\'':
		case '<':
			emitParseError();
			attribute.name.push_back(buf);
			break;
		case EOF32:
			isAttributeNameUnique();
			emitParseError();
			switchToState(DATA);
			unconsume();
			break;
		default:
			attribute.name.push_back(buf);
			break;
	}
}

// Section 8.2.4.36
void Tokenizer::afterAttributeNameState() {
	switch (char32_t buf = consume()) {
		case '\t':
		case '\n':
		case '\f':
		case ' ':
			break;
		case '/':
			switchToState(SELF_CLOSING_START_TAG);
			break;
		case '=':
			switchToState(BEFORE_ATTRIBUTE_VALUE);
			break;
		case '>':
			switchToState(DATA);
			break;
		case ASCII_UPPER_CASE_LETTER:
			attribute = Attribute();
			attribute.name.push_back(toLower(buf));
			switchToState(ATTRIBUTE_NAME);
			break;
		case '\0':
			emitParseError();
			attribute = Attribute();
			attribute.name.push_back(U'\U0000FFFD');
			switchToState(ATTRIBUTE_NAME);
			break;
		case '"':
		case '<':
			emitParseError();
			attribute = Attribute();
			attribute.name.push_back(buf);
			switchToState(ATTRIBUTE_NAME);
			break;
		case EOF32:
			emitParseError();
			switchToState(DATA);
			unconsume();
			break;
		default:
			attribute = Attribute();
			attribute.name.push_back(buf);
			switchToState(ATTRIBUTE_NAME);
			break;
	}
}

// Section 8.2.4.37
void Tokenizer::beforeAttributeValueState() {
	switch (char32_t buf = consume()) {
		case '\t':
		case '\n':
		case '\f':
		case ' ':
			break;
		case '"':
			switchToState(ATTRIBUTE_VALUE_DOUBLE_QUOTED);
			break;
		case '&':
			switchToState(ATTRIBUTE_VALUE_UNQUOTED);
			unconsume();
			break;
		case '\'':
			switchToState(ATTRIBUTE_VALUE_SINGLE_QUOTED);
			break;
		case '\0':
			emitParseError();
			attribute.value.push_back(U'\U0000FFFD');
			switchToState(ATTRIBUTE_VALUE_UNQUOTED);
			break;
		case '>':
			emitParseError();
			switchToState(DATA);
			emit(tag);
			break;
		case '<':
		case '=':
		case '`':
			emitParseError();
			attribute.value.push_back(buf);
			switchToState(ATTRIBUTE_VALUE_UNQUOTED);
			break;
		case EOF32:
			emitParseError();
			switchToState(DATA);
			unconsume();
			break;
		default:
			attribute.value.push_back(buf);
			switchToState(ATTRIBUTE_VALUE_UNQUOTED);
			break;
	}
}

// Section 8.2.4.38
void Tokenizer::attributeValueDoubleQuotedState() {
	switch (char32_t buf = consume()) {
		case '"':
			switchToState(AFTER_ATTRIBUTE_QUOTED);
			break;
		case '&':
			switchToState(CHARACTER_REFERENCE_IN_ATTRIBUTE_VALUE);
			additional_allowed_character='"';
			break;
		case '\0':
			emitParseError();
			attribute.value.push_back(U'\U0000FFFD');
			break;
		case EOF32:
			emitParseError();
			switchToState(DATA);
			unconsume();
			break;
		default:
			attribute.value.push_back(buf);
			break;
	}
}

// Section 8.2.4.39
void Tokenizer::attributeValueSingleQuotedState() {
	switch (char32_t buf = consume()) {
		case '\'':
			switchToState(AFTER_ATTRIBUTE_QUOTED);
			break;
		case '&':
			switchToState(CHARACTER_REFERENCE_IN_ATTRIBUTE_VALUE);
			additional_allowed_character='\'';
			break;
		case '\0':
			emitParseError();
			attribute.value.push_back(U'\U0000FFFD');
			break;
		case EOF32:
			emitParseError();
			switchToState(DATA);
			unconsume();
			break;
		default:
			attribute.value.push_back(buf);
			break;
	}
}

// Section 8.2.4.40
void Tokenizer::attributeValueUnquotedState() {
	switch (char32_t buf = consume()) {
		case '\t':
		case '\n':
		case '\f':
		case ' ':
			switchToState(BEFORE_ATTRIBUTE_NAME);
			break;
		case '&':
			switchToState(CHARACTER_REFERENCE_IN_ATTRIBUTE_VALUE);
			additional_allowed_character='>';
			break;
		case '>':
			switchToState(DATA);
			emit(tag);
			break;
		case '\0':
			emitParseError();
			attribute.value.push_back(U'\U0000FFFD');
			break;
		case '"':
		case '\'':
		case '<':
		case '=':
		case '`':
			emitParseError();
			attribute.value.push_back(buf);
			break;
		case EOF32:
			emitParseError();
			switchToState(DATA);
			unconsume();
			break;
		default:
			attribute.value.push_back(buf);
			break;
	}
}

// Section 8.2.4.41
void Tokenizer::characterReferenceInAttributeValueState() {
	switch(consumeCharacterReference()) {
		case 2: {
			attribute.value.push_back(pop(char_tokens).data);
			attribute.value.push_back(pop(char_tokens).data);
			break;
		}
		case 1: {
			attribute.value.push_back(pop(char_tokens).data);
			break;
		}
		case 0: {
			attribute.value.push_back('&');
			break;
		}
	}

}

// Section 8.2.4.42
void Tokenizer::afterAttributeQuotedState() {
	switch (consume()) {
		case '\t':
		case '\n':
		case '\f':
		case ' ':
			switchToState(BEFORE_ATTRIBUTE_NAME);
			break;
		case '/':
			switchToState(SELF_CLOSING_START_TAG);
			break;
		case '>':
			emit(tag);
			switchToState(DATA);
			break;
		case EOF32:
			emitParseError();
			switchToState(DATA);
			unconsume();
			break;
		default:
			emitParseError();
			switchToState(BEFORE_ATTRIBUTE_NAME);
			unconsume();
			break;
	}
}

// Section 8.2.4.43
void Tokenizer::selfClosingStartTagState() {
	switch (consume()) {
		case '>':
			tag.self_closing = true;
			switchToState(DATA);
			emit(tag);
			break;
		case EOF32:
			emitParseError();
			switchToState(DATA);
			unconsume();
			break;
		default:
			emitParseError();
			switchToState(BEFORE_ATTRIBUTE_NAME);
			unconsume();
			break;
	}
}

// Section 8.2.4.44
void Tokenizer::bogusCommentState() {
	comment = CommentToken();
	while(char32_t buf = consume()) {
		switch(buf) {
			case '>':
				emit(comment);
				switchToState(DATA);
				return;
			case EOF32:
				emit(comment);
				switchToState(DATA);
				unconsume();
				return;
			case '\0':
				comment.data.push_back(U'\U0000FFFD');
				break;
			default:
				comment.data.push_back(buf);
				break;
		}
	}
}

// Section 8.2.4.45
void Tokenizer::markupDeclarationOpenState() {
	if(peek(2) == U"--") {
		consume(2);
		comment = CommentToken();
		switchToState(COMMENT_START);
	} else if (caseInsensitiveMatch(peek(7), U"DOCTYPE")) {
		consume(7);
		switchToState(DOCTYPE);
	} else if (isAdjustedCurrentNode() && !currentNodeInHTMLNamespace() && peek(7) == U"[CDATA[") {
		//TODO Replace dummy status functions that need the parse stage with real ones
		consume(7);
		switchToState(CDATA_SECTION);
	} else {
		emitParseError();
		switchToState(BOGUS_COMMENT);
	}
}

// Section 8.2.4.46
void Tokenizer::commentStartState() {
	switch (char32_t buf = consume()) {
		case '-':
			switchToState(COMMENT_START_DASH);
			break;
		case '\0':
			emitParseError();
			comment.data.push_back(U'\U0000FFFD');
			switchToState(COMMENT);
			break;
		case '>':
			emitParseError();
			switchToState(DATA);
			emit(comment);
			break;
		case EOF32:
			emitParseError();
			switchToState(DATA);
			emit(comment);
			unconsume();
			break;
		default:
			comment.data.push_back(buf);
			switchToState(COMMENT);
			break;
	}
}

// Section 8.2.4.47
void Tokenizer::commentStartDashState() {
	switch (char32_t buf = consume()) {
		case '-':
			switchToState(COMMENT_END);
			break;
		case '\0':
			emitParseError();
			comment.data.push_back('-');
			comment.data.push_back(U'\U0000FFFD');
			switchToState(COMMENT);
			break;
		case '>':
			emitParseError();
			switchToState(DATA);
			emit(comment);
			break;
		case EOF32:
			emitParseError();
			switchToState(DATA);
			emit(comment);
			unconsume();
			break;
		default:
			comment.data.push_back('-');
			comment.data.push_back(buf);
			switchToState(COMMENT);
			break;
	}
}

// Section 8.2.4.48
void Tokenizer::commentState() {
	switch (char32_t buf = consume()) {
		case '-':
			switchToState(COMMENT_END_DASH);
			break;
		case '\0':
			emitParseError();
			comment.data.push_back(U'\U0000FFFD');
			break;
		case EOF32:
			emitParseError();
			switchToState(DATA);
			emit(comment);
			break;
		default:
			comment.data.push_back(buf);
			break;
	}
}

// Section 8.2.4.49
void Tokenizer::commentEndDashState() {
	switch (char32_t buf = consume()) {
		case '-':
			switchToState(COMMENT_END);
			break;
		case '\0':
			emitParseError();
			comment.data.push_back('-');
			comment.data.push_back(U'\U0000FFFD');
			switchToState(COMMENT);
			break;
		case EOF32:
			emitParseError();
			switchToState(DATA);
			emit(comment);
			unconsume();
			break;
		default:
			comment.data.push_back('-');
			comment.data.push_back(buf);
			switchToState(COMMENT);
			break;
	}
}

// Section 8.2.4.50
void Tokenizer::commentEndState() {
	switch (char32_t buf = consume()) {
		case '>':
			switchToState(DATA);
			emit(comment);
			break;
		case '\0':
			emitParseError();
			comment.data.push_back('-');
			comment.data.push_back('-');
			comment.data.push_back(U'\U0000FFFD');
			switchToState(COMMENT);
			break;
		case '!':
			emitParseError();
			switchToState(COMMENT_END_BANG);
			break;
		case '-':
			emitParseError();
			comment.data.push_back('-');
			break;
		case EOF32:
			emitParseError();
			switchToState(DATA);
			emit(comment);
			unconsume();
			break;
		default:
			emitParseError();
			comment.data.push_back('-');
			comment.data.push_back('-');
			comment.data.push_back(buf);
			switchToState(COMMENT);
			break;
	}
}

// Section 8.2.4.51
void Tokenizer::commentEndBangState() {
	switch (char32_t buf = consume()) {
		case '-':
			comment.data.push_back('-');
			comment.data.push_back('-');
			comment.data.push_back('!');
			switchToState(COMMENT_END_DASH);
			break;
		case '>':
			switchToState(DATA);
			emit(comment);
			break;
		case '\0':
			emitParseError();
			comment.data.push_back('-');
			comment.data.push_back('-');
			comment.data.push_back('!');
			comment.data.push_back(U'\U0000FFFD');
			switchToState(COMMENT);
			break;
		case EOF32:
			emitParseError();
			switchToState(DATA);
			emit(comment);
			unconsume();
			break;
		default:
			comment.data.push_back('-');
			comment.data.push_back('-');
			comment.data.push_back('!');
			comment.data.push_back(buf);
			switchToState(COMMENT);
			break;
	}
}

// Section 8.2.4.52
void Tokenizer::DOCTYPEState() {
	switch (consume()) {
		case '\t':
		case '\n':
		case '\f':
		case ' ':
			switchToState(BEFORE_DOCTYPE_NAME);
			break;
		case EOF32:
			emitParseError();
			switchToState(DATA);
			doctype = DOCTYPEToken();
			doctype.force_quirks = true;
			emit(doctype);
			unconsume();
			break;
		default:
			emitParseError();
			switchToState(BEFORE_DOCTYPE_NAME);
			unconsume();
			break;
	}
}

// Section 8.2.4.53
void Tokenizer::beforeDOCTYPENameState() {
	switch (char32_t buf = consume()) {
		case '\t':
		case '\n':
		case '\f':
		case ' ':
			break;
		case ASCII_UPPER_CASE_LETTER:
			doctype = DOCTYPEToken();
			doctype.name = U"";
			doctype.name.push_back(toLower(buf));
			switchToState(DOCTYPE_NAME);
			break;
		case '\0':
			emitParseError();
			doctype = DOCTYPEToken();
			doctype.name = U"";
			doctype.name.push_back(U'\U0000FFFD');
			switchToState(DOCTYPE_NAME);
			break;
		case '>':
			emitParseError();
			doctype = DOCTYPEToken();
			doctype.force_quirks = true;
			switchToState(DATA);
			emit(doctype);
			break;
		case EOF32:
			emitParseError();
			switchToState(DATA);
			doctype = DOCTYPEToken();
			doctype.force_quirks = true;
			emit(doctype);
			unconsume();
			break;
		default:
			doctype = DOCTYPEToken();
			doctype.name.push_back(buf);
			switchToState(DOCTYPE_NAME);
			break;
	}
}

// Section 8.2.4.54
void Tokenizer::DOCTYPENameState() {
	switch (char32_t buf = consume()) {
		case '\t':
		case '\n':
		case '\f':
		case ' ':
			switchToState(AFTER_DOCTYPE_NAME);
			break;
		case '>':
			switchToState(DATA);
			emit(doctype);
			break;
		case ASCII_UPPER_CASE_LETTER:
			doctype.name.push_back(toLower(buf));
			break;
		case '\0':
			emitParseError();
			doctype.name.push_back(U'\U0000FFFD');
			break;
		case EOF32:
			emitParseError();
			switchToState(DATA);
			emit(doctype);
			break;
		default:
			doctype.name.push_back(buf);
			break;
	}
}

// Section 8.2.4.55
void Tokenizer::afterDOCTYPENameState() {
	switch (char32_t buf = consume()) {
		case '\t':
		case '\n':
		case '\f':
		case ' ':
			break;
		case '>':
			switchToState(DATA);
			emit(doctype);
			break;
		case EOF32:
			emitParseError();
			switchToState(DATA);
			doctype.force_quirks = true;
			emit(doctype);
			unconsume();
			break;
		default:
			std::u32string characters = buf + peek(5);
			if(caseInsensitiveMatch(characters, U"PUBLIC")) {
				consume(5);
				switchToState(AFTER_DOCTYPE_PUBLIC_KEYWORD);
			} else if(caseInsensitiveMatch(characters, U"SYSTEM")) {
				consume(5);
				switchToState(AFTER_DOCTYPE_SYSTEM_KEYWORD);
			} else {
				emitParseError();
				doctype.force_quirks=true;
				switchToState(BOGUS_DOCTYPE);
			}
			break;
	}
}

// Section 8.2.4.56
void Tokenizer::afterDOCTYPEPublicKeywordState() {
	switch (consume()) {
		case '\t':
		case '\n':
		case '\f':
		case ' ':
			switchToState(BEFORE_DOCTYPE_PUBLIC_IDENTIFIER);
			break;
		case '"':
			emitParseError();
			doctype.public_identifier = U"";
			switchToState(DOCTYPE_PUBLIC_IDENTIFIER_DOUBLE_QUOTED);
			break;
		case '\'':
			emitParseError();
			doctype.public_identifier = U"";
			switchToState(DOCTYPE_PUBLIC_IDENTIFIER_SINGLE_QUOTED);
			break;
		case '>':
			emitParseError();
			doctype.force_quirks = true;
			switchToState(DATA);
			emit(doctype);
			break;
		case EOF32:
			emitParseError();
			switchToState(DATA);
			doctype.force_quirks = true;
			emit(doctype);
			unconsume();
			break;
		default:
			emitParseError();
			doctype.force_quirks = true;
			switchToState(BOGUS_DOCTYPE);
			break;
	}
}

// Section 8.2.4.57
void Tokenizer::beforeDOCTYPEPublicIdentifierState() {
	switch (consume()) {
		case '\t':
		case '\n':
		case '\f':
		case ' ':
			break;
		case '"':
			doctype.public_identifier = U"";
			switchToState(DOCTYPE_PUBLIC_IDENTIFIER_DOUBLE_QUOTED);
			break;
		case '\'':
			doctype.public_identifier = U"";
			switchToState(DOCTYPE_PUBLIC_IDENTIFIER_SINGLE_QUOTED);
			break;
		case '>':
			emitParseError();
			doctype.force_quirks = true;
			switchToState(DATA);
			emit(doctype);
			break;
		case EOF32:
			emitParseError();
			switchToState(DATA);
			doctype.force_quirks = true;
			emit(doctype);
			unconsume();
			break;
		default:
			emitParseError();
			doctype.force_quirks = true;
			switchToState(BOGUS_DOCTYPE);
			break;
	}
}

// Section 8.2.4.58
void Tokenizer::DOCTYPEPublicIdentifierDoubleQuotedState() {
	switch (char32_t buf = consume()) {
		case '"':
			switchToState(AFTER_DOCTYPE_PUBLIC_IDENTIFIER);
			break;
		case '\0':
			emitParseError();
			doctype.public_identifier.push_back(U'\U0000FFFD');
			break;
		case '>':
			emitParseError();
			doctype.force_quirks = true;
			switchToState(DATA);
			emit(doctype);
			break;
		case EOF32:
			emitParseError();
			switchToState(DATA);
			doctype.force_quirks = true;
			emit(doctype);
			unconsume();
			break;
		default:
			doctype.public_identifier.push_back(buf);
			break;
	}
}

// Section 8.2.4.59
void Tokenizer::DOCTYPEPublicIdentifierSingleQuotedState() {
	switch (char32_t buf = consume()) {
		case '\'':
			switchToState(AFTER_DOCTYPE_PUBLIC_IDENTIFIER);
			break;
		case '\0':
			emitParseError();
			doctype.public_identifier.push_back(U'\U0000FFFD');
			break;
		case '>':
			emitParseError();
			doctype.force_quirks = true;
			switchToState(DATA);
			emit(doctype);
			break;
		case EOF32:
			emitParseError();
			switchToState(DATA);
			doctype.force_quirks = true;
			emit(doctype);
			unconsume();
			break;
		default:
			doctype.public_identifier.push_back(buf);
			break;
	}
}

// Section 8.2.4.60
void Tokenizer::afterDOCTYPEPublicIdentifierState() {
	switch (consume()) {
		case '\t':
		case '\n':
		case '\f':
		case ' ':
			switchToState(BETWEEN_DOCTYPE_PUBLIC_AND_SYSTEM_IDENTIFIERS);
			break;
		case '>':
			switchToState(DATA);
			break;
		case '"':
			emitParseError();
			doctype.system_identifier = U"";
			switchToState(DOCTYPE_SYSTEM_IDENTIFIER_DOUBLE_QUOTED);
			break;
		case '\'':
			emitParseError();
			doctype.system_identifier = U"";
			switchToState(DOCTYPE_SYSTEM_IDENTIFIER_SINGLE_QUOTED);
			break;
		case EOF32:
			emitParseError();
			switchToState(DATA);
			doctype.force_quirks = true;
			emit(doctype);
			unconsume();
			break;
		default:
			emitParseError();
			doctype.force_quirks = true;
			switchToState(BOGUS_DOCTYPE);
			break;
	}
}

// Section 8.2.4.61
void Tokenizer::betweenDOCTYPEPublicAndSystemIdentifiersState() {
	switch (consume()) {
		case '\t':
		case '\n':
		case '\f':
		case ' ':
			break;
		case '>':
			switchToState(DATA);
			emit(doctype);
			break;
		case '"':
			doctype.system_identifier = U"";
			switchToState(DOCTYPE_SYSTEM_IDENTIFIER_DOUBLE_QUOTED);
			break;
		case '\'':
			doctype.system_identifier = U"";
			switchToState(DOCTYPE_SYSTEM_IDENTIFIER_SINGLE_QUOTED);
			break;
		case EOF32:
			emitParseError();
			switchToState(DATA);
			doctype.force_quirks = true;
			emit(doctype);
			unconsume();
			break;
		default:
			emitParseError();
			doctype.force_quirks = true;
			switchToState(BOGUS_DOCTYPE);
			break;
	}
}

// Section 8.2.4.62
void Tokenizer::afterDOCTYPESystemKeywordState() {
	switch (consume()) {
		case '\t':
		case '\n':
		case '\f':
		case ' ':
			switchToState(BEFORE_DOCTYPE_SYSTEM_IDENTIFIER);
			break;
		case '"':
			emitParseError();
			doctype.system_identifier = U"";
			switchToState(DOCTYPE_SYSTEM_IDENTIFIER_DOUBLE_QUOTED);
			break;
		case '\'':
			emitParseError();
			doctype.system_identifier = U"";
			switchToState(DOCTYPE_SYSTEM_IDENTIFIER_SINGLE_QUOTED);
			break;
		case '>':
			emitParseError();
			doctype.force_quirks = true;
			switchToState(DATA);
			emit(doctype);
			break;
		case EOF32:
			emitParseError();
			switchToState(DATA);
			doctype.force_quirks = true;
			emit(doctype);
			unconsume();
			break;
		default:
			emitParseError();
			doctype.force_quirks = true;
			switchToState(BOGUS_DOCTYPE);
			break;
	}
}

// Section 8.2.4.63
void Tokenizer::beforeDOCTYPESystemIdentifierState() {
	switch (consume()) {
		case '\t':
		case '\n':
		case '\f':
		case ' ':
			break;
		case '"':
			doctype.system_identifier = U"";
			switchToState(DOCTYPE_SYSTEM_IDENTIFIER_DOUBLE_QUOTED);
			break;
		case '\'':
			doctype.system_identifier = U"";
			switchToState(DOCTYPE_SYSTEM_IDENTIFIER_SINGLE_QUOTED);
			break;
		case '>':
			emitParseError();
			doctype.force_quirks = true;
			switchToState(DATA);
			emit(doctype);
			break;
		case EOF32:
			emitParseError();
			switchToState(DATA);
			doctype.force_quirks = true;
			emit(doctype);
			unconsume();
			break;
		default:
			emitParseError();
			doctype.force_quirks = true;
			switchToState(BOGUS_DOCTYPE);
			break;
	}
}

// Section 8.2.4.64
void Tokenizer::DOCTYPESystemIdentifierDoubleQuotedState() {
	switch (char32_t buf = consume()) {
		case '"':
			switchToState(AFTER_DOCTYPE_SYSTEM_IDENTIFIER);
			break;
		case '\0':
			emitParseError();
			doctype.system_identifier.push_back(U'\U0000FFFD');
			break;
		case '>':
			emitParseError();
			doctype.force_quirks = true;
			switchToState(DATA);
			emit(doctype);
			break;
		case EOF32:
			emitParseError();
			switchToState(DATA);
			doctype.force_quirks = true;
			emit(doctype);
			unconsume();
			break;
		default:
			doctype.system_identifier.push_back(buf);
			break;
	}
}

// Section 8.2.4.65
void Tokenizer::DOCTYPESystemIdentifierSingleQuotedState() {
	switch (char32_t buf = consume()) {
		case '\'':
			switchToState(AFTER_DOCTYPE_SYSTEM_IDENTIFIER);
			break;
		case '\0':
			emitParseError();
			doctype.system_identifier.push_back(U'\U0000FFFD');
			break;
		case '>':
			emitParseError();
			doctype.force_quirks = true;
			switchToState(DATA);
			emit(doctype);
			break;
		case EOF32:
			emitParseError();
			switchToState(DATA);
			doctype.force_quirks = true;
			emit(doctype);
			unconsume();
			break;
		default:
			doctype.system_identifier.push_back(buf);
			break;
	}
}

// Section 8.2.4.66
void Tokenizer::afterDOCTYPESystemIdentifierState() {
	switch (consume()) {
		case '\t':
		case '\n':
		case '\f':
		case ' ':
			break;
		case '>':
			switchToState(DATA);
			break;
		case EOF32:
			emitParseError();
			switchToState(DATA);
			doctype.force_quirks = true;
			emit(doctype);
			unconsume();
			break;
		default:
			emitParseError();
			switchToState(BOGUS_DOCTYPE);
			break;
	}
}

// Section 8.2.4.67
void Tokenizer::bogusDOCTYPEState() {
	switch (consume()) {
		case '>':
			switchToState(DATA);
			emit(doctype);
			break;
		case EOF32:
			switchToState(DATA);
			emit(doctype);
			unconsume();
			break;
		default:
			break;
	}
}

// Section 8.2.4.68
void Tokenizer::CDATASectionState() {
	std::u32string characters;
	switchToState(DATA);
	while(std::u32string buf = consume()+peek(2)) {
		if(buf == U"]]>") {
			consume(2);
			for(auto& i : characters) {
				emit(CharacterToken(i));
			}
			break;
		} else if (buf.front() == EOF32) {
			for(auto& i : characters) {
				emit(CharacterToken(i));
			}
			unconsume();
			break;
		} else {
			characters.push_back(buf.front());
		}
	}
}


} /* namespace Tokenization */
} /* namespace Parse */
} /* namespace HTML */
