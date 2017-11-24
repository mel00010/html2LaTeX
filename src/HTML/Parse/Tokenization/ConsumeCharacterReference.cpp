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

#include "Tokenizer.hpp"

#include "TokenizationTypes.hpp"

#include <algorithm>
#include <codecvt>
#include <cstring>
#include <iterator>
#include <iostream>
#include <limits>
#include <locale>
#include <optional>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

#include <HTML/Microsyntaxes/ASCII/ASCII.hpp>
#include <HTML/Microsyntaxes/Numbers/NonNegativeInteger.hpp>

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#include "CharacterReferences.hpp"
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

namespace HTML {
namespace Parse {
namespace Tokenization {

// Section 8.2.4.69
size_t Tokenizer::consumeCharacterReference() {
	if(peek() == additional_allowed_character) {
		return 0;
	}
	additional_allowed_character = NO_CHARACTER;
	switch (peek()) {
		case '\t':
		case '\n':
		case '\f':
		case ' ':
		case '<':
		case '&':
		case EOF32:
			return 0; // Not a character reference.
		case '#': {
			return consumeCharacterReferenceCodepointHelper();
		}
		default: {
			return consumeCharacterReferenceNamedCharacterReferenceHelper();
		}
	}

}

size_t Tokenizer::consumeCharacterReferenceCodepointHelper() {
	consume_counter = 0;
	consume();

	bool (*isDigit)(const char32_t&) = &Microsyntaxes::ASCII::isASCIIDigit;
	uint32_t (*parseInteger)(const std::u32string&) = &Microsyntaxes::Numbers::parseNonNegativeInteger;
	if (peek() == 'x' || peek() == 'X') {
		consume();
		isDigit = &Microsyntaxes::ASCII::isASCIIHex;
		parseInteger = &Microsyntaxes::Numbers::parseNonNegativeHexInteger;

	}

	std::u32string digits = U"";
	while (isDigit(peek())) {
		digits += consume();
	}
	if (digits.empty()) {
		unconsume(consume_counter);
		return 0;
	}
	uint32_t id = parseInteger(digits);

	if (peek() == ';') {
		consume();
	}

	static constexpr std::pair<const uint32_t, const char32_t> conversionArray[] = {
			{ 0x00, U'\U0000FFFD' },
			{ 0x80, U'\U000020AC' },
			{ 0x82, U'\U0000201A' },
			{ 0x83, U'\U00000192' },
			{ 0x84, U'\U0000201E' },
			{ 0x85, U'\U00002026' },
			{ 0x86, U'\U00002020' },
			{ 0x87, U'\U00002021' },
			{ 0x88, U'\U000002C6' },
			{ 0x89, U'\U00002030' },
			{ 0x8A, U'\U00000160' },
			{ 0x8B, U'\U00002039' },
			{ 0x8C, U'\U00000152' },
			{ 0x8E, U'\U0000017D' },
			{ 0x91, U'\U00002018' },
			{ 0x92, U'\U00002019' },
			{ 0x93, U'\U0000201C' },
			{ 0x94, U'\U0000201D' },
			{ 0x95, U'\U00002022' },
			{ 0x96, U'\U00002013' },
			{ 0x97, U'\U00002014' },
			{ 0x98, U'\U000002DC' },
			{ 0x99, U'\U00002122' },
			{ 0x9A, U'\U00000161' },
			{ 0x9B, U'\U0000203A' },
			{ 0x9C, U'\U00000153' },
			{ 0x9E, U'\U0000017E' },
			{ 0x9F, U'\U00000178' }
	};
	for (auto i : conversionArray) {
		if (id == i.first) {
			char_tokens.push(CharacterToken(i.second));
			return 1;
		}
	}

	if (id > 0x10FFFF || (0xD800 <= id && id <= 0xDFFF)) {
		char_tokens.push(CharacterToken(U'\U0000FFFD'));
		return 1;
	}

	if ((0x0001 <= id && id <= 0x0008) || (0x000D <= id && id <= 0x001F) || (0x007F <= id && id <= 0x009F) || (0xFDD0 <= id && id <= 0xFDEF)) {
		return 0;
	}
	static constexpr uint32_t disallowedIDs[] {
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
	for (auto i : disallowedIDs) {
		if (id == i) {
			return 0;
		}
	}

	char_tokens.push(CharacterToken(id));
	return 1;
}

size_t Tokenizer::consumeCharacterReferenceNamedCharacterReferenceHelper() {
	consume_counter = 0;
	std::u32string characters = peek(std::u32string(std::get<0>(characterReferences.front())).length());
	for (auto i : characterReferences) {
		if (characters.find(std::u32string(std::get<0>(i))) == 0) {
			consume(std::u32string(std::get<0>(i)).length());

			if (std::get<2>(i) != EOF32) {
				char_tokens.push(CharacterToken(std::get<2>(i)));
				char_tokens.push(CharacterToken((std::get<1>(i))));
				return 2;
			}
			char_tokens.push(CharacterToken((std::get<1>(i))));
			return 1;
		}
	}
	return 0;
}

} /* namespace Tokenization */
} /* namespace Parse */
} /* namespace HTML */
