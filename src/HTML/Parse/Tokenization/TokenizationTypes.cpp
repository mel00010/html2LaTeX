/*******************************************************************************
 * TokenizationTypes.cpp
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

#include "TokenizationTypes.hpp"

#include <boost/io/ios_state.hpp>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <string>

namespace HTML {
namespace Parse {
namespace Tokenization {

::std::ostream& operator<<(::std::ostream& os, const DOCTYPEToken& doctype_token) {
	os << "std::string name = " << ((doctype_token.name == "\0xFF") ? "\\(EOF)" : doctype_token.name) << "\n";
	os << "std::string public_identifier = ";
	os << ((doctype_token.public_identifier == "\0xFF") ? "\\(EOF)" : doctype_token.public_identifier) << "\n";
	os << "std::string system_identifier = ";
	os << ((doctype_token.system_identifier == "\0xFF") ? "\\(EOF)" : doctype_token.system_identifier) << "\n";
	os << "bool force_quirks = " << doctype_token.force_quirks;
	return os;
}

::std::ostream& operator<<(::std::ostream& os, const StartTagToken& start_tag_token) {
	os << "std::string tag_name = " << start_tag_token.tag_name << "\n";
	os << "bool self_closing = " << start_tag_token.self_closing << "\n";
	os << "std::list<Attribute> attributes = ";
	for (auto v : start_tag_token.attributes) {
		os << v;
	}
	return os;

}

::std::ostream& operator<<(::std::ostream& os, const EndTagToken& end_tag_token) {
	os << "std::string tag_name = " << end_tag_token.tag_name << "\n";
	os << "bool self_closing = " << end_tag_token.self_closing << "\n";
	os << "std::list<Attribute> attributes = ";
	for (auto v : end_tag_token.attributes) {
		os << v;
	}
	return os;
}

::std::ostream& operator<<(::std::ostream& os, const CharacterToken& character_token) {
	os << "char32_t data = ";

	boost::io::ios_all_saver ias(os);

	os.setf(os.hex, os.basefield);
	os.setf(os.right, os.adjustfield);
	os.fill('0');

	os << "U+" << std::setw(8) << (unsigned long) character_token.data;

	ias.restore();
	return os;
}

::std::ostream& operator<<(::std::ostream& os, const CommentToken& comment_token) {
	return os << "std::string data = " << comment_token.data;
}

::std::ostream& operator<<(::std::ostream& os, const EOFToken& eof_token) {
	return os << eof_token.string;
}

::std::ostream& operator<<(::std::ostream& os, const Token& token) {
	os << "TokenType type = " << token.type << "\n";
	os << "std::variant<DOCTYPEToken, StartTagToken, EndTagToken, CharacterToken, CommentToken, EOFToken> token = ";
	if (auto doctype_token = std::get_if<DOCTYPEToken>(&token.token)) {
		os << doctype_token;
	} else if (auto start_tag_token = std::get_if<StartTagToken>(&token.token)) {
		os << start_tag_token;
	} else if (auto end_tag_token = std::get_if<EndTagToken>(&token.token)) {
		os << end_tag_token;
	} else if (auto character_token = std::get_if<CharacterToken>(&token.token)) {
		os << character_token;
	} else if (auto comment_token = std::get_if<CommentToken>(&token.token)) {
		os << comment_token;
	} else if (auto eof_token = std::get_if<EOFToken>(&token.token)) {
		os << eof_token;
	}
	return os;
}

::std::ostream& operator<<(::std::ostream& os, const TokenType& token_type) {
	switch (token_type) {
		case TokenType::DOCTYPE:
			os << "TokenType::DOCTYPE";
			break;
		case TokenType::START_TAG:
			os << "TokenType::START_TAG";
			break;
		case TokenType::END_TAG:
			os << "TokenType::END_TAG";
			break;
		case TokenType::COMMENT:
			os << "TokenType::COMMENT";
			break;
		case TokenType::CHARACTER:
			os << "TokenType::CHARACTER";
			break;
		case TokenType::END_OF_FILE:
			os << "TokenType::END_OF_FILE";
			break;
		default:
			os << "Error: Unknown TokenType!";
			break;
	}
	return os;
}


::std::ostream& operator<<(::std::ostream& os, const STATES& state) {
	switch (state) {
		case STATES::DATA:
			os << "STATES::DATA";
			break;
		case STATES::CHARACTER_REFERENCE_IN_DATA:
			os << "STATES::CHARACTER_REFERENCE_IN_DATA";
			break;
		case STATES::RCDATA:
			os << "STATES::CHARACTER_REFERENCE_IN_RCDATA";
			break;
		case STATES::CHARACTER_REFERENCE_IN_RCDATA:
			os << "STATES::CHARACTER_REFERENCE_IN_RCDATA";
			break;
		case STATES::RAWTEXT:
			os << "STATES::RAWTEXT";
			break;
		case STATES::SCRIPT_DATA:
			os << "STATES::SCRIPT_DATA";
			break;
		case STATES::PLAINTEXT:
			os << "STATES::PLAINTEXT";
			break;
		case STATES::TAG_OPEN:
			os << "STATES::TAG_OPEN";
			break;
		case STATES::END_TAG_OPEN:
			os << "STATES::END_TAG_OPEN";
			break;
		case STATES::TAG_NAME:
			os << "STATES::TAG_NAME";
			break;
		case STATES::RCDATA_LESS_THAN_SIGN:
			os << "STATES::RCDATA_LESS_THAN_SIGN";
			break;
		case STATES::RCDATA_END_TAG_OPEN:
			os << "STATES::RCDATA_END_TAG_OPEN";
			break;
		case STATES::RCDATA_END_TAG_NAME:
			os << "STATES::RCDATA_END_TAG_NAME";
			break;
		case STATES::RAWTEXT_END_TAG_OPEN:
			os << "STATES::RAWTEXT_END_TAG_OPEN";
			break;
		case STATES::RAWTEXT_END_TAG_NAME:
			os << "STATES::RAWTEXT_END_TAG_NAME";
			break;
		case STATES::SCRIPT_DATA_LESS_THAN_SIGN:
			os << "STATES::SCRIPT_DATA_LESS_THAN_SIGN";
			break;
		case STATES::SCRIPT_DATA_END_TAG_OPEN:
			os << "STATES::SCRIPT_DATA_END_TAG_OPEN";
			break;
		case STATES::SCRIPT_DATA_END_TAG_NAME:
			os << "STATES::SCRIPT_DATA_END_TAG_NAME";
			break;
		case STATES::SCRIPT_DATA_ESCAPE_START:
			os << "STATES::SCRIPT_DATA_ESCAPE_START";
			break;
		case STATES::SCRIPT_DATA_ESCAPE_START_DASH:
			os << "STATES::SCRIPT_DATA_ESCAPE_START_DASH";
			break;
		case STATES::SCRIPT_DATA_ESCAPED:
			os << "STATES::SCRIPT_DATA_ESCAPED";
			break;
		case STATES::SCRIPT_DATA_ESCAPED_DASH:
			os << "STATES::SCRIPT_DATA_ESCAPED_DASH";
			break;
		case STATES::SCRIPT_DATA_ESCAPED_DASH_DASH:
			os << "STATES::SCRIPT_DATA_ESCAPED_DASH_DASH";
			break;
		case STATES::SCRIPT_DATA_ESCAPED_LESS_THAN_SIGN:
			os << "STATES::SCRIPT_DATA_ESCAPED_LESS_THAN_SIGN";
			break;
		case STATES::SCRIPT_DATA_ESCAPED_END_TAG_NAME:
			os << "STATES::SCRIPT_DATA_ESCAPED_END_TAG_NAME";
			break;
		case STATES::SCRIPT_DATA_DOUBLE_ESCAPE_START:
			os << "STATES::SCRIPT_DATA_DOUBLE_ESCAPE_START";
			break;
		case STATES::SCRIPT_DATA_DOUBLE_ESCAPED:
			os << "STATES::SCRIPT_DATA_DOUBLE_ESCAPED";
			break;
		case STATES::SCRIPT_DATA_DOUBLE_ESCAPED_DASH:
			os << "STATES::SCRIPT_DATA_DOUBLE_ESCAPED_DASH";
			break;
		case STATES::SCRIPT_DATA_DOUBLE_ESCAPED_DASH_DASH:
			os << "STATES::SCRIPT_DATA_DOUBLE_ESCAPED_DASH_DASH";
			break;
		case STATES::SCRIPT_DATA_DOUBLE_ESCAPED_LESS_THAN_SIGN:
			os << "STATES::SCRIPT_DATA_DOUBLE_ESCAPED_LESS_THAN_SIGN";
			break;
		case STATES::SCRIPT_DATA_DOUBLE_ESCAPE_END:
			os << "STATES::SCRIPT_DATA_DOUBLE_ESCAPE_END";
			break;
		case STATES::BEFORE_ATTRIBUTE:
			os << "STATES::BEFORE_ATTRIBUTE";
			break;
		case STATES::ATTRIBUTE_NAME:
			os << "STATES::ATTRIBUTE_NAME";
			break;
		case STATES::AFTER_ATTRIBUTE_NAME:
			os << "STATES::ATTRIBUTE_NAME";
			break;
		case STATES::BEFORE_ATTRIBUTE_VALUE:
			os << "STATES::BEFORE_ATTRIBUTE_VALUE";
			break;
		case STATES::ATTRIBUTE_VALUE_DOUBLE_QUOTED:
			os << "STATES::ATTRIBUTE_VALUE_DOUBLE_QUOTED";
			break;
		case STATES::ATTRIBUTE_VALUE_SINGLE_QUOTED:
			os << "STATES::ATTRIBUTE_VALUE_SINGLE_QUOTED";
			break;
		case STATES::ATTRIBUTE_VALUE_UNQUOTED:
			os << "STATES::ATTRIBUTE_VALUE_UNQUOTED";
			break;
		case STATES::CHARACTER_REFERENCE_IN_ATTRIBUTE_VALUE:
			os << "STATES::CHARACTER_REFERENCE_IN_ATTRIBUTE_VALUE";
			break;
		case STATES::AFTER_ATTRIBUTE_QUOTED:
			os << "STATES::AFTER_ATTRIBUTE_QUOTED";
			break;
		case STATES::SELF_CLOSING_START_TAG:
			os << "STATES::SELF_CLOSING_START_TAG";
			break;
		case STATES::BOGUS_COMMENT:
			os << "STATES::BOGUS_COMMENT";
			break;
		case STATES::MARKUP_DECLARATION_OPEN:
			os << "STATES::MARKUP_DECLARATION_OPEN";
			break;
		case STATES::COMMENT_START:
			os << "STATES::COMMENT_START";
			break;
		case STATES::COMMENT_START_DASH:
			os << "STATES::COMMENT_START_DASH";
			break;
		case STATES::COMMENT:
			os << "STATES::COMMENT";
			break;
		case STATES::COMMENT_END_DASH:
			os << "STATES::COMMENT_END_DASH";
			break;
		case STATES::COMMENT_END:
			os << "STATES::COMMENT_END";
			break;
		case STATES::COMMENT_END_BANG:
			os << "STATES::COMMENT_END_BANG";
			break;
		case STATES::DOCTYPE:
			os << "STATES::DOCTYPE";
			break;
		case STATES::BEFORE_DOCTYPE_NAME:
			os << "STATES::BEFORE_DOCTYPE_NAME";
			break;
		case STATES::DOCTYPE_NAME:
			os << "STATES::DOCTYPE_NAME";
			break;
		case STATES::AFTER_DOCTYPE_NAME:
			os << "STATES::AFTER_DOCTYPE_NAME";
			break;
		case STATES::AFTER_DOCTYPE_PUBLIC_KEYWORD:
			os << "STATES::AFTER_DOCTYPE_PUBLIC_KEYWORD";
			break;
		case STATES::BEFORE_DOCTYPE_PUBLIC_IDENTIFIER:
			os << "STATES::BEFORE_DOCTYPE_PUBLIC_IDENTIFIER";
			break;
		case STATES::DOCTYPE_PUBLIC_IDENTIFIER_DOUBLE_QUOTED:
			os << "STATES::DOCTYPE_PUBLIC_IDENTIFIER_DOUBLE_QUOTED";
			break;
		case STATES::DOCTYPE_PUBLIC_IDENTIFIER_SINGLE_QUOTED:
			os << "STATES::DOCTYPE_PUBLIC_IDENTIFIER_SINGLE_QUOTED";
			break;
		case STATES::AFTER_DOCTYPE_PUBLIC_IDENTIFIER:
			os << "STATES::AFTER_DOCTYPE_PUBLIC_IDENTIFIER";
			break;
		case STATES::BETWEEN_DOCTYPE_PUBLIC_AND_SYSTEM_IDENTIFIERS:
			os << "STATES::BETWEEN_DOCTYPE_PUBLIC_AND_SYSTEM_IDENTIFIERS";
			break;
		case STATES::AFTER_DOCTYPE_SYSTEM_KEYWORD:
			os << "STATES::AFTER_DOCTYPE_SYSTEM_KEYWORD";
			break;
		case STATES::BEFORE_DOCTYPE_SYSTEM_IDENTIFIER:
			os << "STATES::BEFORE_DOCTYPE_SYSTEM_IDENTIFIER";
			break;
		case STATES::DOCTYPE_SYSTEM_IDENTIFIER_DOUBLE_QUOTED:
			os << "STATES::DOCTYPE_SYSTEM_IDENTIFIER_DOUBLE_QUOTED";
			break;
		case STATES::DOCTYPE_SYSTEM_IDENTIFIER_SINGLE_QUOTED:
			os << "STATES::DOCTYPE_SYSTEM_IDENTIFIER_SINGLE_QUOTED";
			break;
		case STATES::AFTER_DOCTYPE_SYSTEM_IDENTIFIER:
			os << "STATES::AFTER_DOCTYPE_SYSTEM_IDENTIFIER";
			break;
		case STATES::BOGUS_DOCTYPE:
			os << "STATES::BOGUS_DOCTYPE";
			break;
		case STATES::CDATA_SECTION:
			os << "STATES::CDATA_SECTION";
			break;
		default:
			os << "Error:  Unknown state in STATES!";
			break;
	}
	return os;
}

::std::ostream& operator<<(::std::ostream& os, const StateData& state_data) {
	os << "STATES state = " << state_data.state << "\n";
	os << "std::string string = " << state_data.string << "\n";
	os << "size_t pos = " << state_data.pos << "\n";
	os << "bool parse_pause_flag = " << state_data.parser_pause_flag << "\n";
	os << "size_t script_nesting_level = " << state_data.script_nesting_level << "\n";
	os << "std::list<Token> tokens = ";
	for (auto v : state_data.tokens) {
		os << v;
	}
	return os;
}

} /* namespace Tokenization */
} /* namespace Parse */
} /* namespace HTML */
