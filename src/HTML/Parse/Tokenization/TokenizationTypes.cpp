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
#include <codecvt>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <locale>
#include <string>

namespace HTML {
namespace Parse {
namespace Tokenization {

::std::ostream& operator<<(::std::ostream& os, const DOCTYPEToken& doctype_token) {
	os << "std::string name = " << ((doctype_token.name == "\xFF") ? "\\(EOF)" : doctype_token.name) << "\n";
	os << "std::string public_identifier = ";
	os << ((doctype_token.public_identifier == "\xFF") ? "\\(EOF)" : doctype_token.public_identifier) << "\n";
	os << "std::string system_identifier = ";
	os << ((doctype_token.system_identifier == "\xFF") ? "\\(EOF)" : doctype_token.system_identifier) << "\n";
	os << "bool force_quirks = " << doctype_token.force_quirks;
	return os;
}
bool operator==(const DOCTYPEToken& lhs, const DOCTYPEToken& rhs) {
	if (lhs.name != rhs.name) {
		return false;
	}
	if (lhs.public_identifier != rhs.public_identifier) {
		return false;
	}
	if (lhs.system_identifier != rhs.system_identifier) {
		return false;
	}
	if (lhs.force_quirks != rhs.force_quirks) {
		return false;
	}
	return true;
}

::std::ostream& operator<<(::std::ostream& os, const StartTagToken& start_tag_token) {
	os << "std::string tag_name = " << start_tag_token.tag_name << "\n";
	os << "bool self_closing = " << start_tag_token.self_closing << "\n";
	os << "std::list<Attribute> attributes = ";
	for (auto v : start_tag_token.attributes) {
		os << v << ", ";
	}
	return os;
}

bool operator==(const StartTagToken& lhs, const StartTagToken& rhs) {
	if (lhs.tag_name != rhs.tag_name) {
		return false;
	}
	if (lhs.self_closing != rhs.self_closing) {
		return false;
	}
	if (lhs.attributes != rhs.attributes) {
		return false;
	}
	return true;
}

::std::ostream& operator<<(::std::ostream& os, const EndTagToken& end_tag_token) {
	os << "std::string tag_name = " << end_tag_token.tag_name << "\n";
	os << "bool self_closing = " << end_tag_token.self_closing << "\n";
	os << "std::list<Attribute> attributes = ";
	for (auto v : end_tag_token.attributes) {
		os << v << ", ";
	}
	return os;
}

bool operator==(const EndTagToken& lhs, const EndTagToken& rhs) {
	if (lhs.tag_name != rhs.tag_name) {
		return false;
	}
	if (lhs.self_closing != rhs.self_closing) {
		return false;
	}
	if (lhs.attributes != rhs.attributes) {
		return false;
	}
	return true;
}

::std::ostream& operator<<(::std::ostream& os, const CharacterToken& character_token) {
	os << "char32_t first_character = ";

	boost::io::ios_all_saver ias(os);

	os.setf(os.hex, os.basefield);
	os.setf(os.right, os.adjustfield);
	os.fill('0');

	os << "U+" << std::setw(8) << std::uppercase << (unsigned long) character_token.first_character << std::endl;
	ias.restore();
	os << "char32_t second_character = ";

	os.setf(os.hex, os.basefield);
	os.setf(os.right, os.adjustfield);
	os.fill('0');
	os << "U+" << std::setw(8) << std::uppercase << (unsigned long) character_token.second_character;
	ias.restore();
	return os;
}

bool operator==(const CharacterToken& lhs, const CharacterToken& rhs) {
	if (lhs.first_character != rhs.first_character) {
		return false;
	}
	if (lhs.second_character != rhs.second_character) {
		return false;
	}
	return true;
}

::std::ostream& operator<<(::std::ostream& os, const CommentToken& comment_token) {
	return os << "std::string data = \"" << comment_token.data << "\"";
}

bool operator==(const CommentToken& lhs, const CommentToken& rhs) {
	if (lhs.data != rhs.data) {
		return false;
	}
	return true;

}

::std::ostream& operator<<(::std::ostream& os, const EOFToken& eof_token) {
	return os << eof_token.string;
}

bool operator==(__attribute__ ((unused)) const EOFToken& lhs, __attribute__ ((unused)) const EOFToken& rhs) {
	return true;
}

::std::ostream& operator<<(::std::ostream& os, const NoToken& no_token) {
	return os << no_token.string;
}

bool operator==(__attribute__ ((unused)) const NoToken& lhs, __attribute__ ((unused)) const NoToken& rhs) {
	return true;
}

::std::ostream& operator<<(::std::ostream& os, const Token& token) {
	os << "TokenType type = " << token.type << "\n";
	os << "TokenVariant token = ";
	return std::visit([&os](auto&& arg) {os << arg;}, token.token), os;
}

bool operator==(const Token& lhs, const Token& rhs) {
	if (lhs.type != rhs.type) {
		return false;
	}
	if (lhs.token != rhs.token) {
		return false;
	}
	return true;
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
		case TokenType::NO_TOKEN:
			os << "TokenType::NO_TOKEN";
			break;
		default:
			os << "Error: Unknown TokenType!";
			break;
	}
	return os;
}

::std::ostream& operator<<(::std::ostream& os, const STATES& state) {
	switch (state) {
		case STATES::NULL_STATE:
			os << "STATES::NULL_STATE";
			break;
		case STATES::DATA:
			os << "STATES::DATA";
			break;
		case STATES::CHARACTER_REFERENCE_IN_DATA:
			os << "STATES::CHARACTER_REFERENCE_IN_DATA";
			break;
		case STATES::RCDATA:
			os << "STATES::RCDATA";
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
			os << "STATES::AFTER_ATTRIBUTE_NAME";
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
	;
	os << "STATES state = " << state_data.state << "\n";
	os << "std::u32string string = \"" << std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t>().to_bytes(state_data.string) << "\"\n";
	os << "size_t pos = " << state_data.pos << "\n";
	os << "char buf = '" << std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t>().to_bytes(state_data.buf) << "'\n";
	os << "bool parser_pause_flag = " << state_data.parser_pause_flag << "\n";
	os << "size_t script_nesting_level = " << state_data.script_nesting_level << "\n";
	os << "std::list<Token> tokens = ";
	os << "{\n";
	for (auto v : state_data.tokens) {
		os << "Token { " << v << "}, \n";
	}
	os << "}";
	return os;
}

bool operator==(const StateData& lhs, const StateData& rhs) {
	if (lhs.state != rhs.state) {
		return false;
	}
	if (lhs.string != rhs.string) {
		return false;
	}
	if (lhs.pos != rhs.pos) {
		return false;
	}
	if (lhs.buf != rhs.buf) {
		return false;
	}
	if (lhs.parser_pause_flag != rhs.parser_pause_flag) {
		return false;
	}
	if (lhs.script_nesting_level != rhs.script_nesting_level) {
		return false;
	}
	if (lhs.tokens != rhs.tokens) {
		return false;
	}
	return true;
}

} /* namespace Tokenization */
} /* namespace Parse */
} /* namespace HTML */
