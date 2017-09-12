/*******************************************************************************
 * CharacterReference.cpp
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

#include "CharacterReference.hpp"

#include "TokenizationTypes.hpp"

#include <string>

#include <HTML/Microsyntaxes/ASCII/ASCII.hpp>
#include <HTML/Microsyntaxes/Numbers/NonNegativeInteger.hpp>

namespace HTML {
namespace Parse {
namespace Tokenization {

Token consumeCharacterReference(StateData& data) {
	Token token;
	// If the character after the & is any of the following, this is not a character reference.  Return.
	if (data.string[data.pos + 1] == '\t') {
		return token;
	} else if (data.string[data.pos + 1] == '\n') {
		return token;
	} else if (data.string[data.pos + 1] == '\f') {
		return token;
	} else if (data.string[data.pos + 1] == ' ') {
		return token;
	} else if (data.string[data.pos + 1] == '<') {
		return token;
	} else if (data.string[data.pos + 1] == '&') {
		return token;

		/* Are we at the end of the string?  Is this a "EOF"? */
	} else if (data.pos + 1 >= data.string.length()) {
		return token;
	} else if (data.string[data.pos + 1] == '#') {
		data.pos++;
		data.buf = data.string[data.pos];
		bool hexNumber = false;
		if (data.string[data.pos + 1] == 'x' || data.string[data.pos + 1] == 'X') {
			data.pos++;
			data.buf = data.string[data.pos];
			hexNumber = true;
		}
		std::string digits = "";
		unsigned int id = 0;
		if (hexNumber) {
			for (; data.pos < data.string.length(); data.pos++) {
				if (Microsyntaxes::ASCII::isASCIIHex(data.string[data.pos])) {
					digits += data.string[data.pos];
				}
			}
			if (digits.empty()) {
				data.pos--;
				data.pos--;
				data.pos--;
				return token;
			}
			id = Microsyntaxes::Numbers::parseNonNegativeHexInteger(digits);
		} else {
			for (; data.pos < data.string.length(); data.pos++) {
				if (Microsyntaxes::ASCII::isASCIIDigit(data.string[data.pos])) {
					digits += data.string[data.pos];
				}
			}
				if (digits.empty()) {
					data.pos--;
					data.pos--;
				return token;
				}
			id = Microsyntaxes::Numbers::parseNonNegativeInteger(digits);
		}
		if (data.string[data.pos] == ';') {
			data.pos++;
		}
		switch (id) {
			case 0x00:
				token.type = TokenType::CHARACTER;
				token.character_token.data = U'\U0000FFFD';
				token.empty = false;
				return token;
				break;
			case 0x80:
				token.type = TokenType::CHARACTER;
				token.character_token.data = U'\U000020AC';
				token.empty = false;
				return token;
				break;
			case 0x82:
				token.type = TokenType::CHARACTER;
				token.character_token.data = U'\U0000201A';
				token.empty = false;
				return token;
				break;
			case 0x83:
				token.type = TokenType::CHARACTER;
				token.character_token.data = U'\U00000192';
				token.empty = false;
				return token;
				break;
			case 0x84:
				token.type = TokenType::CHARACTER;
				token.character_token.data = U'\U0000201E';
				token.empty = false;
				return token;
				break;
			case 0x85:
				token.type = TokenType::CHARACTER;
				token.character_token.data = U'\U00002026';
				token.empty = false;
				return token;
				break;
			case 0x86:
				token.type = TokenType::CHARACTER;
				token.character_token.data = U'\U00002020';
				token.empty = false;
				return token;
				break;
			case 0x87:
				token.type = TokenType::CHARACTER;
				token.character_token.data = U'\U00002021';
				token.empty = false;
				return token;
				break;
			case 0x88:
				token.type = TokenType::CHARACTER;
				token.character_token.data = U'\U000002C6';
				token.empty = false;
				return token;
				break;
			case 0x89:
				token.type = TokenType::CHARACTER;
				token.character_token.data = U'\U00002030';
				token.empty = false;
				return token;
				break;
			case 0x8A:
				token.type = TokenType::CHARACTER;
				token.character_token.data = U'\U00000160';
				token.empty = false;
				return token;
				break;
			case 0x8B:
				token.type = TokenType::CHARACTER;
				token.character_token.data = U'\U00002039';
				token.empty = false;
				return token;
				break;
			case 0x8C:
				token.type = TokenType::CHARACTER;
				token.character_token.data = U'\U00000152';
				token.empty = false;
				return token;
				break;
			case 0x8E:
				token.type = TokenType::CHARACTER;
				token.character_token.data = U'\U0000017D';
				token.empty = false;
				return token;
				break;
			case 0x91:
				token.type = TokenType::CHARACTER;
				token.character_token.data = U'\U00002018';
				token.empty = false;
				return token;
				break;
			case 0x92:
				token.type = TokenType::CHARACTER;
				token.character_token.data = U'\U00002019';
				token.empty = false;
				return token;
				break;
			case 0x93:
				token.type = TokenType::CHARACTER;
				token.character_token.data = U'\U0000201C';
				token.empty = false;
				return token;
				break;
			case 0x94:
				token.type = TokenType::CHARACTER;
				token.character_token.data = U'\U0000201D';
				token.empty = false;
				return token;
				break;
			case 0x95:
				token.type = TokenType::CHARACTER;
				token.character_token.data = U'\U00002022';
				token.empty = false;
				return token;
				break;
			case 0x96:
				token.type = TokenType::CHARACTER;
				token.character_token.data = U'\U00002013';
				token.empty = false;
				return token;
				break;
			case 0x97:
				token.type = TokenType::CHARACTER;
				token.character_token.data = U'\U00002014';
				token.empty = false;
				return token;
				break;
			case 0x98:
				token.type = TokenType::CHARACTER;
				token.character_token.data = U'\U000002DC';
				token.empty = false;
				return token;
				break;
			case 0x99:
				token.type = TokenType::CHARACTER;
				token.character_token.data = U'\U00002122';
				token.empty = false;
				return token;
				break;
			case 0x9A:
				token.type = TokenType::CHARACTER;
				token.character_token.data = U'\U00000161';
				token.empty = false;
				return token;
				break;
			case 0x9B:
				token.type = TokenType::CHARACTER;
				token.character_token.data = U'\U0000203A';
				token.empty = false;
				return token;
				break;
			case 0x9C:
				token.type = TokenType::CHARACTER;
				token.character_token.data = U'\U00000153';
				token.empty = false;
				return token;
				break;
			case 0x9E:
				token.type = TokenType::CHARACTER;
				token.character_token.data = U'\U0000017E';
				token.empty = false;
				return token;
				break;
			case 0x9F:
				token.type = TokenType::CHARACTER;
				token.character_token.data = U'\U00000178';
				token.empty = false;
				return token;
				break;
			default:
				break;
		}
		if (0xD800 <= id || id <= 0xDFFF) {
			token.type = TokenType::CHARACTER;
			token.character_token.data = U'\U0000FFFD';
			token.empty = false;
			return token;
		} else if (id > 0x10FFFF) {
			token.type = TokenType::CHARACTER;
			token.character_token.data = U'\U0000FFFD';
			token.empty = false;
			return token;
		} else if (0x0001 <= id || id <= 0x0008) {
			token.type = TokenType::CHARACTER;
			token.character_token.data = U'\U0000FFFD';
			token.empty = false;
			return token;
		} else if (0x000D <= id || id <= 0x001F) {
			token.type = TokenType::CHARACTER;
			token.character_token.data = U'\U0000FFFD';
			token.empty = false;
			return token;
		} else if (0x007F <= id || id <= 0x009F) {
			token.type = TokenType::CHARACTER;
			token.character_token.data = U'\U0000FFFD';
			token.empty = false;
			return token;
		} else if (0xFDD0 <= id || id <= 0xFDEF) {
			token.type = TokenType::CHARACTER;
			token.character_token.data = U'\U0000FFFD';
			token.empty = false;
			return token;
		}

		constexpr unsigned int disallowedCharacters[35] {
				0x000B,
				0xFFFE,
				0xFFFF,
				0x1FFFE,
				0x1FFFF,
				0x2FFFE,
				0x2FFFF,
				0x3FFFE,
				0x3FFFF,
				0x4FFFE,
				0x4FFFF,
				0x5FFFE,
				0x5FFFF,
				0x6FFFE,
				0x6FFFF,
				0x7FFFE,
				0x7FFFF,
				0x8FFFE,
				0x8FFFF,
				0x9FFFE,
				0x9FFFF,
				0xAFFFE,
				0xAFFFF,
				0xBFFFE,
				0xBFFFF,
				0xCFFFE,
				0xCFFFF,
				0xDFFFE,
				0xDFFFF,
				0xEFFFE,
				0xEFFFF,
				0xFFFFE,
				0xFFFFF,
				0x10FFFE,
				0x10FFFF
		};
		for (auto i : disallowedCharacters) {
			if (id == i) {
				return token;
			}
		}
		token.type = TokenType::CHARACTER;
		token.character_token.data = id;
		token.empty = false;
		return token;
	}

}

Token consumeCharacterReference(StateData& data, const char& additional_allowed_character) {
	Token token;
	if (data.string[data.pos + 1] == additional_allowed_character) {
		return token;
	}
	return consumeCharacterReference(data);
}

} /* namespace Tokenization */
} /* namespace Parse */
} /* namespace HTML */
