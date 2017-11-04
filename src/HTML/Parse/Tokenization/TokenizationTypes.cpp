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
	os << "std::u32string name = " << (
			(doctype_token.name == U"\xFF\xFF\xFF\xFF") ?
	"\\(EOF)" : std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t>().to_bytes(doctype_token.name)) << "\n";
	os << "std::u32string public_identifier = ";
	os << ((doctype_token.public_identifier == U"\xFF\xFF\xFF\xFF") ?
			"\\(EOF)" : std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t>().to_bytes(doctype_token.public_identifier)) << "\n";
	os << "std::u32string system_identifier = ";
	os << ((doctype_token.system_identifier == U"\xFF\xFF\xFF\xFF") ?
			"\\(EOF)" : std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t>().to_bytes(doctype_token.system_identifier)) << "\n";
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
	os << "std::u32string tag_name = " << std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t>().to_bytes(start_tag_token.tag_name) << "\n";
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
	os << "std::u32string tag_name = " << std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t>().to_bytes(end_tag_token.tag_name) << "\n";
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
	os << "char32_t data = ";

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
	return os << "std::u32string data = \"" << std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t>().to_bytes(comment_token.data) << "\"";
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

::std::ostream& operator<<(::std::ostream& os, const EmmittedTokens& tokens) {
	return os << "Token first = " << tokens.first << std::endl
			<< "Token second = " << tokens.second;
}
bool operator==(const EmmittedTokens& lhs, const EmmittedTokens& rhs) {
	if (lhs.first != rhs.first) {
		return false;
	}
	if (lhs.second != rhs.second) {
		return false;
	}
	return true;
}

} /* namespace Tokenization */
} /* namespace Parse */
} /* namespace HTML */
