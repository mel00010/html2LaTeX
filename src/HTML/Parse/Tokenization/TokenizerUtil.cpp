/*******************************************************************************
 * StatesUtil.cpp
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

#include <HTML/Microsyntaxes/ASCII/ASCII.hpp>

namespace HTML {
namespace Parse {
namespace Tokenization {

void Tokenizer::changeState(STATES new_state) {
	state = new_state;
}

char32_t Tokenizer::consume() {
	return get_character_at_position(pos++);
}

char32_t Tokenizer::get_character_at_position(size_t position) {
	if (position >= string.length()) {
		return EOF32;
	}
	return string[position];
}


char32_t Tokenizer::peek() {
	return get_character_at_position(pos + 1);
}

char32_t Tokenizer::reconsume() {
	return get_character_at_position(pos);
}

void Tokenizer::unconsume() {
	pos--;
}

void Tokenizer::unconsume(int n_chars) {
	pos -= n_chars;
}



::std::ostream& operator<<(::std::ostream& os, const Tokenizer::STATES& state) {
	switch (state) {
		case Tokenizer::STATES::NULL_STATE:
			os << "STATES::NULL_STATE";
			break;
		case Tokenizer::STATES::DATA:
			os << "STATES::DATA";
			break;
		case Tokenizer::STATES::CHARACTER_REFERENCE_IN_DATA:
			os << "STATES::CHARACTER_REFERENCE_IN_DATA";
			break;
		case Tokenizer::STATES::RCDATA:
			os << "STATES::RCDATA";
			break;
		case Tokenizer::STATES::CHARACTER_REFERENCE_IN_RCDATA:
			os << "STATES::CHARACTER_REFERENCE_IN_RCDATA";
			break;
		case Tokenizer::STATES::RAWTEXT:
			os << "STATES::RAWTEXT";
			break;
		case Tokenizer::STATES::SCRIPT_DATA:
			os << "STATES::SCRIPT_DATA";
			break;
		case Tokenizer::STATES::PLAINTEXT:
			os << "STATES::PLAINTEXT";
			break;
		case Tokenizer::STATES::TAG_OPEN:
			os << "STATES::TAG_OPEN";
			break;
		case Tokenizer::STATES::END_TAG_OPEN:
			os << "STATES::END_TAG_OPEN";
			break;
		case Tokenizer::STATES::TAG_NAME:
			os << "STATES::TAG_NAME";
			break;
		case Tokenizer::STATES::RCDATA_LESS_THAN_SIGN:
			os << "STATES::RCDATA_LESS_THAN_SIGN";
			break;
		case Tokenizer::STATES::RCDATA_END_TAG_OPEN:
			os << "STATES::RCDATA_END_TAG_OPEN";
			break;
		case Tokenizer::STATES::RCDATA_END_TAG_NAME:
			os << "STATES::RCDATA_END_TAG_NAME";
			break;
		case Tokenizer::STATES::RAWTEXT_END_TAG_OPEN:
			os << "STATES::RAWTEXT_END_TAG_OPEN";
			break;
		case Tokenizer::STATES::RAWTEXT_END_TAG_NAME:
			os << "STATES::RAWTEXT_END_TAG_NAME";
			break;
		case Tokenizer::STATES::SCRIPT_DATA_LESS_THAN_SIGN:
			os << "STATES::SCRIPT_DATA_LESS_THAN_SIGN";
			break;
		case Tokenizer::STATES::SCRIPT_DATA_END_TAG_OPEN:
			os << "STATES::SCRIPT_DATA_END_TAG_OPEN";
			break;
		case Tokenizer::STATES::SCRIPT_DATA_END_TAG_NAME:
			os << "STATES::SCRIPT_DATA_END_TAG_NAME";
			break;
		case Tokenizer::STATES::SCRIPT_DATA_ESCAPE_START:
			os << "STATES::SCRIPT_DATA_ESCAPE_START";
			break;
		case Tokenizer::STATES::SCRIPT_DATA_ESCAPE_START_DASH:
			os << "STATES::SCRIPT_DATA_ESCAPE_START_DASH";
			break;
		case Tokenizer::STATES::SCRIPT_DATA_ESCAPED:
			os << "STATES::SCRIPT_DATA_ESCAPED";
			break;
		case Tokenizer::STATES::SCRIPT_DATA_ESCAPED_DASH:
			os << "STATES::SCRIPT_DATA_ESCAPED_DASH";
			break;
		case Tokenizer::STATES::SCRIPT_DATA_ESCAPED_DASH_DASH:
			os << "STATES::SCRIPT_DATA_ESCAPED_DASH_DASH";
			break;
		case Tokenizer::STATES::SCRIPT_DATA_ESCAPED_LESS_THAN_SIGN:
			os << "STATES::SCRIPT_DATA_ESCAPED_LESS_THAN_SIGN";
			break;
		case Tokenizer::STATES::SCRIPT_DATA_ESCAPED_END_TAG_NAME:
			os << "STATES::SCRIPT_DATA_ESCAPED_END_TAG_NAME";
			break;
		case Tokenizer::STATES::SCRIPT_DATA_DOUBLE_ESCAPE_START:
			os << "STATES::SCRIPT_DATA_DOUBLE_ESCAPE_START";
			break;
		case Tokenizer::STATES::SCRIPT_DATA_DOUBLE_ESCAPED:
			os << "STATES::SCRIPT_DATA_DOUBLE_ESCAPED";
			break;
		case Tokenizer::STATES::SCRIPT_DATA_DOUBLE_ESCAPED_DASH:
			os << "STATES::SCRIPT_DATA_DOUBLE_ESCAPED_DASH";
			break;
		case Tokenizer::STATES::SCRIPT_DATA_DOUBLE_ESCAPED_DASH_DASH:
			os << "STATES::SCRIPT_DATA_DOUBLE_ESCAPED_DASH_DASH";
			break;
		case Tokenizer::STATES::SCRIPT_DATA_DOUBLE_ESCAPED_LESS_THAN_SIGN:
			os << "STATES::SCRIPT_DATA_DOUBLE_ESCAPED_LESS_THAN_SIGN";
			break;
		case Tokenizer::STATES::SCRIPT_DATA_DOUBLE_ESCAPE_END:
			os << "STATES::SCRIPT_DATA_DOUBLE_ESCAPE_END";
			break;
		case Tokenizer::STATES::BEFORE_ATTRIBUTE:
			os << "STATES::BEFORE_ATTRIBUTE";
			break;
		case Tokenizer::STATES::ATTRIBUTE_NAME:
			os << "STATES::ATTRIBUTE_NAME";
			break;
		case Tokenizer::STATES::AFTER_ATTRIBUTE_NAME:
			os << "STATES::AFTER_ATTRIBUTE_NAME";
			break;
		case Tokenizer::STATES::BEFORE_ATTRIBUTE_VALUE:
			os << "STATES::BEFORE_ATTRIBUTE_VALUE";
			break;
		case Tokenizer::STATES::ATTRIBUTE_VALUE_DOUBLE_QUOTED:
			os << "STATES::ATTRIBUTE_VALUE_DOUBLE_QUOTED";
			break;
		case Tokenizer::STATES::ATTRIBUTE_VALUE_SINGLE_QUOTED:
			os << "STATES::ATTRIBUTE_VALUE_SINGLE_QUOTED";
			break;
		case Tokenizer::STATES::ATTRIBUTE_VALUE_UNQUOTED:
			os << "STATES::ATTRIBUTE_VALUE_UNQUOTED";
			break;
		case Tokenizer::STATES::CHARACTER_REFERENCE_IN_ATTRIBUTE_VALUE:
			os << "STATES::CHARACTER_REFERENCE_IN_ATTRIBUTE_VALUE";
			break;
		case Tokenizer::STATES::AFTER_ATTRIBUTE_QUOTED:
			os << "STATES::AFTER_ATTRIBUTE_QUOTED";
			break;
		case Tokenizer::STATES::SELF_CLOSING_START_TAG:
			os << "STATES::SELF_CLOSING_START_TAG";
			break;
		case Tokenizer::STATES::BOGUS_COMMENT:
			os << "STATES::BOGUS_COMMENT";
			break;
		case Tokenizer::STATES::MARKUP_DECLARATION_OPEN:
			os << "STATES::MARKUP_DECLARATION_OPEN";
			break;
		case Tokenizer::STATES::COMMENT_START:
			os << "STATES::COMMENT_START";
			break;
		case Tokenizer::STATES::COMMENT_START_DASH:
			os << "STATES::COMMENT_START_DASH";
			break;
		case Tokenizer::STATES::COMMENT:
			os << "STATES::COMMENT";
			break;
		case Tokenizer::STATES::COMMENT_END_DASH:
			os << "STATES::COMMENT_END_DASH";
			break;
		case Tokenizer::STATES::COMMENT_END:
			os << "STATES::COMMENT_END";
			break;
		case Tokenizer::STATES::COMMENT_END_BANG:
			os << "STATES::COMMENT_END_BANG";
			break;
		case Tokenizer::STATES::DOCTYPE:
			os << "STATES::DOCTYPE";
			break;
		case Tokenizer::STATES::BEFORE_DOCTYPE_NAME:
			os << "STATES::BEFORE_DOCTYPE_NAME";
			break;
		case Tokenizer::STATES::DOCTYPE_NAME:
			os << "STATES::DOCTYPE_NAME";
			break;
		case Tokenizer::STATES::AFTER_DOCTYPE_NAME:
			os << "STATES::AFTER_DOCTYPE_NAME";
			break;
		case Tokenizer::STATES::AFTER_DOCTYPE_PUBLIC_KEYWORD:
			os << "STATES::AFTER_DOCTYPE_PUBLIC_KEYWORD";
			break;
		case Tokenizer::STATES::BEFORE_DOCTYPE_PUBLIC_IDENTIFIER:
			os << "STATES::BEFORE_DOCTYPE_PUBLIC_IDENTIFIER";
			break;
		case Tokenizer::STATES::DOCTYPE_PUBLIC_IDENTIFIER_DOUBLE_QUOTED:
			os << "STATES::DOCTYPE_PUBLIC_IDENTIFIER_DOUBLE_QUOTED";
			break;
		case Tokenizer::STATES::DOCTYPE_PUBLIC_IDENTIFIER_SINGLE_QUOTED:
			os << "STATES::DOCTYPE_PUBLIC_IDENTIFIER_SINGLE_QUOTED";
			break;
		case Tokenizer::STATES::AFTER_DOCTYPE_PUBLIC_IDENTIFIER:
			os << "STATES::AFTER_DOCTYPE_PUBLIC_IDENTIFIER";
			break;
		case Tokenizer::STATES::BETWEEN_DOCTYPE_PUBLIC_AND_SYSTEM_IDENTIFIERS:
			os << "STATES::BETWEEN_DOCTYPE_PUBLIC_AND_SYSTEM_IDENTIFIERS";
			break;
		case Tokenizer::STATES::AFTER_DOCTYPE_SYSTEM_KEYWORD:
			os << "STATES::AFTER_DOCTYPE_SYSTEM_KEYWORD";
			break;
		case Tokenizer::STATES::BEFORE_DOCTYPE_SYSTEM_IDENTIFIER:
			os << "STATES::BEFORE_DOCTYPE_SYSTEM_IDENTIFIER";
			break;
		case Tokenizer::STATES::DOCTYPE_SYSTEM_IDENTIFIER_DOUBLE_QUOTED:
			os << "STATES::DOCTYPE_SYSTEM_IDENTIFIER_DOUBLE_QUOTED";
			break;
		case Tokenizer::STATES::DOCTYPE_SYSTEM_IDENTIFIER_SINGLE_QUOTED:
			os << "STATES::DOCTYPE_SYSTEM_IDENTIFIER_SINGLE_QUOTED";
			break;
		case Tokenizer::STATES::AFTER_DOCTYPE_SYSTEM_IDENTIFIER:
			os << "STATES::AFTER_DOCTYPE_SYSTEM_IDENTIFIER";
			break;
		case Tokenizer::STATES::BOGUS_DOCTYPE:
			os << "STATES::BOGUS_DOCTYPE";
			break;
		case Tokenizer::STATES::CDATA_SECTION:
			os << "STATES::CDATA_SECTION";
			break;
		default:
			os << "Error:  Unknown state in STATES!";
			break;
	}
	return os;
}

} /* namespace Tokenization */
} /* namespace Parse */
} /* namespace HTML */

