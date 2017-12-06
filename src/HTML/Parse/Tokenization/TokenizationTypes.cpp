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
	os << "\"" << (
			(doctype_token.name == U"\xFF\xFF\xFF\xFF") ?
	"\\(EOF)" : std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t>().to_bytes(doctype_token.name)) << "\":\"";
	os << ((doctype_token.public_identifier == U"\xFF\xFF\xFF\xFF") ?
	"\\(EOF)" : std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t>().to_bytes(doctype_token.public_identifier)) << "\":\"";
	os << ((doctype_token.system_identifier == U"\xFF\xFF\xFF\xFF") ?
	"\\(EOF)" : std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t>().to_bytes(doctype_token.system_identifier)) << "\":";
	os << (doctype_token.force_quirks ? "True" : "False");
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
	os << "\"" << std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t>().to_bytes(start_tag_token.tag_name) << "\":";
	os << (start_tag_token.self_closing ? "True" : "False") << ":";
	os << "{";
	for (auto v : start_tag_token.attributes) {
		os << v << ", ";
	}
	return os << "}";
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
	os << "\"" << std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t>().to_bytes(end_tag_token.tag_name) << "\":";
	os << (end_tag_token.self_closing ? "True" : "False") << ":";
	os << "{";
	for (auto v : end_tag_token.attributes) {
		os << v << ", ";
	}
	return os << "}";
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
	boost::io::ios_all_saver ias(os);

	os.setf(os.hex, os.basefield);
	os.setf(os.right, os.adjustfield);
	os.fill('0');

	os << "U+" << std::setw(8) << std::uppercase << (unsigned long) character_token.data;
	ias.restore();
	return os;
}

bool operator==(const CharacterToken& lhs, const CharacterToken& rhs) {
	if (lhs.data != rhs.data) {
		return false;
	}
	return true;
}

::std::ostream& operator<<(::std::ostream& os, const CommentToken& comment_token) {
	return os << "\"" << std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t>().to_bytes(comment_token.data) << "\"";
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
	os << token.type << ":";
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
			os << "DOCTYPE";
			break;
		case TokenType::START_TAG:
			os << "START_TAG";
			break;
		case TokenType::END_TAG:
			os << "END_TAG";
			break;
		case TokenType::COMMENT:
			os << "COMMENT";
			break;
		case TokenType::CHARACTER:
			os << "CHARACTER";
			break;
		case TokenType::END_OF_FILE:
			os << "END_OF_FILE";
			break;
		case TokenType::NO_TOKEN:
			os << "NO_TOKEN";
			break;
		default:
			os << "Error: Unknown TokenType!";
			break;
	}
	return os;
}

::std::ostream& operator<<(::std::ostream& os, const TokenPair& tokens) {
	return os << "{" << tokens.first << "}:{" << tokens.second << "}";
}
bool operator==(const TokenPair& lhs, const TokenPair& rhs) {
	if (lhs.first != rhs.first) {
		return false;
	}
	if (lhs.second != rhs.second) {
		return false;
	}
	return true;
}

::std::ostream& operator<<(::std::ostream& os, const State& state) {
	switch (state) {
		case NULL_STATE:
			os << "NULL_STATE";
			break;
		case DATA:
			os << "DATA";
			break;
		case CHARACTER_REFERENCE_IN_DATA:
			os << "CHARACTER_REFERENCE_IN_DATA";
			break;
		case RCDATA:
			os << "RCDATA";
			break;
		case CHARACTER_REFERENCE_IN_RCDATA:
			os << "CHARACTER_REFERENCE_IN_RCDATA";
			break;
		case RAWTEXT:
			os << "RAWTEXT";
			break;
		case SCRIPT_DATA:
			os << "SCRIPT_DATA";
			break;
		case PLAINTEXT:
			os << "PLAINTEXT";
			break;
		case TAG_OPEN:
			os << "TAG_OPEN";
			break;
		case END_TAG_OPEN:
			os << "END_TAG_OPEN";
			break;
		case TAG_NAME:
			os << "TAG_NAME";
			break;
		case RCDATA_LESS_THAN_SIGN:
			os << "RCDATA_LESS_THAN_SIGN";
			break;
		case RCDATA_END_TAG_OPEN:
			os << "RCDATA_END_TAG_OPEN";
			break;
		case RCDATA_END_TAG_NAME:
			os << "RCDATA_END_TAG_NAME";
			break;
		case RAWTEXT_END_TAG_OPEN:
			os << "RAWTEXT_END_TAG_OPEN";
			break;
		case RAWTEXT_END_TAG_NAME:
			os << "RAWTEXT_END_TAG_NAME";
			break;
		case SCRIPT_DATA_LESS_THAN_SIGN:
			os << "SCRIPT_DATA_LESS_THAN_SIGN";
			break;
		case SCRIPT_DATA_END_TAG_OPEN:
			os << "SCRIPT_DATA_END_TAG_OPEN";
			break;
		case SCRIPT_DATA_END_TAG_NAME:
			os << "SCRIPT_DATA_END_TAG_NAME";
			break;
		case SCRIPT_DATA_ESCAPE_START:
			os << "SCRIPT_DATA_ESCAPE_START";
			break;
		case SCRIPT_DATA_ESCAPE_START_DASH:
			os << "SCRIPT_DATA_ESCAPE_START_DASH";
			break;
		case SCRIPT_DATA_ESCAPED:
			os << "SCRIPT_DATA_ESCAPED";
			break;
		case SCRIPT_DATA_ESCAPED_DASH:
			os << "SCRIPT_DATA_ESCAPED_DASH";
			break;
		case SCRIPT_DATA_ESCAPED_DASH_DASH:
			os << "SCRIPT_DATA_ESCAPED_DASH_DASH";
			break;
		case SCRIPT_DATA_ESCAPED_LESS_THAN_SIGN:
			os << "SCRIPT_DATA_ESCAPED_LESS_THAN_SIGN";
			break;
		case SCRIPT_DATA_ESCAPED_END_TAG_NAME:
			os << "SCRIPT_DATA_ESCAPED_END_TAG_NAME";
			break;
		case SCRIPT_DATA_DOUBLE_ESCAPE_START:
			os << "SCRIPT_DATA_DOUBLE_ESCAPE_START";
			break;
		case SCRIPT_DATA_DOUBLE_ESCAPED:
			os << "SCRIPT_DATA_DOUBLE_ESCAPED";
			break;
		case SCRIPT_DATA_DOUBLE_ESCAPED_DASH:
			os << "SCRIPT_DATA_DOUBLE_ESCAPED_DASH";
			break;
		case SCRIPT_DATA_DOUBLE_ESCAPED_DASH_DASH:
			os << "SCRIPT_DATA_DOUBLE_ESCAPED_DASH_DASH";
			break;
		case SCRIPT_DATA_DOUBLE_ESCAPED_LESS_THAN_SIGN:
			os << "SCRIPT_DATA_DOUBLE_ESCAPED_LESS_THAN_SIGN";
			break;
		case SCRIPT_DATA_DOUBLE_ESCAPE_END:
			os << "SCRIPT_DATA_DOUBLE_ESCAPE_END";
			break;
		case BEFORE_ATTRIBUTE_NAME:
			os << "BEFORE_ATTRIBUTE";
			break;
		case ATTRIBUTE_NAME:
			os << "ATTRIBUTE_NAME";
			break;
		case AFTER_ATTRIBUTE_NAME:
			os << "AFTER_ATTRIBUTE_NAME";
			break;
		case BEFORE_ATTRIBUTE_VALUE:
			os << "BEFORE_ATTRIBUTE_VALUE";
			break;
		case ATTRIBUTE_VALUE_DOUBLE_QUOTED:
			os << "ATTRIBUTE_VALUE_DOUBLE_QUOTED";
			break;
		case ATTRIBUTE_VALUE_SINGLE_QUOTED:
			os << "ATTRIBUTE_VALUE_SINGLE_QUOTED";
			break;
		case ATTRIBUTE_VALUE_UNQUOTED:
			os << "ATTRIBUTE_VALUE_UNQUOTED";
			break;
		case CHARACTER_REFERENCE_IN_ATTRIBUTE_VALUE:
			os << "CHARACTER_REFERENCE_IN_ATTRIBUTE_VALUE";
			break;
		case AFTER_ATTRIBUTE_QUOTED:
			os << "AFTER_ATTRIBUTE_QUOTED";
			break;
		case SELF_CLOSING_START_TAG:
			os << "SELF_CLOSING_START_TAG";
			break;
		case BOGUS_COMMENT:
			os << "BOGUS_COMMENT";
			break;
		case MARKUP_DECLARATION_OPEN:
			os << "MARKUP_DECLARATION_OPEN";
			break;
		case COMMENT_START:
			os << "COMMENT_START";
			break;
		case COMMENT_START_DASH:
			os << "COMMENT_START_DASH";
			break;
		case COMMENT:
			os << "COMMENT";
			break;
		case COMMENT_END_DASH:
			os << "COMMENT_END_DASH";
			break;
		case COMMENT_END:
			os << "COMMENT_END";
			break;
		case COMMENT_END_BANG:
			os << "COMMENT_END_BANG";
			break;
		case DOCTYPE:
			os << "DOCTYPE";
			break;
		case BEFORE_DOCTYPE_NAME:
			os << "BEFORE_DOCTYPE_NAME";
			break;
		case DOCTYPE_NAME:
			os << "DOCTYPE_NAME";
			break;
		case AFTER_DOCTYPE_NAME:
			os << "AFTER_DOCTYPE_NAME";
			break;
		case AFTER_DOCTYPE_PUBLIC_KEYWORD:
			os << "AFTER_DOCTYPE_PUBLIC_KEYWORD";
			break;
		case BEFORE_DOCTYPE_PUBLIC_IDENTIFIER:
			os << "BEFORE_DOCTYPE_PUBLIC_IDENTIFIER";
			break;
		case DOCTYPE_PUBLIC_IDENTIFIER_DOUBLE_QUOTED:
			os << "DOCTYPE_PUBLIC_IDENTIFIER_DOUBLE_QUOTED";
			break;
		case DOCTYPE_PUBLIC_IDENTIFIER_SINGLE_QUOTED:
			os << "DOCTYPE_PUBLIC_IDENTIFIER_SINGLE_QUOTED";
			break;
		case AFTER_DOCTYPE_PUBLIC_IDENTIFIER:
			os << "AFTER_DOCTYPE_PUBLIC_IDENTIFIER";
			break;
		case BETWEEN_DOCTYPE_PUBLIC_AND_SYSTEM_IDENTIFIERS:
			os << "BETWEEN_DOCTYPE_PUBLIC_AND_SYSTEM_IDENTIFIERS";
			break;
		case AFTER_DOCTYPE_SYSTEM_KEYWORD:
			os << "AFTER_DOCTYPE_SYSTEM_KEYWORD";
			break;
		case BEFORE_DOCTYPE_SYSTEM_IDENTIFIER:
			os << "BEFORE_DOCTYPE_SYSTEM_IDENTIFIER";
			break;
		case DOCTYPE_SYSTEM_IDENTIFIER_DOUBLE_QUOTED:
			os << "DOCTYPE_SYSTEM_IDENTIFIER_DOUBLE_QUOTED";
			break;
		case DOCTYPE_SYSTEM_IDENTIFIER_SINGLE_QUOTED:
			os << "DOCTYPE_SYSTEM_IDENTIFIER_SINGLE_QUOTED";
			break;
		case AFTER_DOCTYPE_SYSTEM_IDENTIFIER:
			os << "AFTER_DOCTYPE_SYSTEM_IDENTIFIER";
			break;
		case BOGUS_DOCTYPE:
			os << "BOGUS_DOCTYPE";
			break;
		case CDATA_SECTION:
			os << "CDATA_SECTION";
			break;
		default:
			os << "Error:  Unknown state!";
			break;
	}
	return os;
}

} /* namespace Tokenization */
} /* namespace Parse */
} /* namespace HTML */
