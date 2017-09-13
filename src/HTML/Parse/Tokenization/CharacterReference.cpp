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

#include "TokenizationMisc.hpp"
#include "TokenizationTypes.hpp"

#include <algorithm>
#include <cstring>
#include <iterator>
#include <string>
#include <utility>
#include <vector>

#include <HTML/Microsyntaxes/ASCII/ASCII.hpp>
#include <HTML/Microsyntaxes/Numbers/NonNegativeInteger.hpp>

#ifndef DOXYGEN_SHOULD_SKIP_THIS
#include <CharacterReferences.ipp>
#endif /* DOXYGEN_SHOULD_SKIP_THIS */

namespace HTML {
namespace Parse {
namespace Tokenization {

Token consumeCharacterReference(StateData& data) {
	Token token;

	static constexpr char notACharacterReferenceChars[] {
			'\t',
			'\n',
			'\f',
			' ',
			'<',
			'&',
			EOF
	};

	for (auto i : notACharacterReferenceChars) {
		if (data.string[data.pos + 1] == i) {
			return token;
		}
	}

	if (data.string[data.pos + 1] == '#') {
		data.pos++;

		bool (*isDigit)(const char&) = &Microsyntaxes::ASCII::isASCIIDigit;
		unsigned long (*parseInteger)(const std::string&) = &Microsyntaxes::Numbers::parseNonNegativeInteger;
		bool isHex = false;
		if (data.string[data.pos + 1] == 'x' || data.string[data.pos + 1] == 'X') {
			data.pos++;
			isHex = true;
			isDigit = &Microsyntaxes::ASCII::isASCIIHex;
			parseInteger = &Microsyntaxes::Numbers::parseNonNegativeHexInteger;

		}

		std::string digits = "";
		for (; data.pos < data.string.length(); data.pos++) {
			if (isDigit(data.string[data.pos])) {
				digits += data.string[data.pos];
			}
		}

		if (digits.empty()) {
			data.pos -= 2;
			if (isHex) {
				data.pos--;
			}
			return token;
		}

		unsigned int id = parseInteger(digits);

		if (data.string[data.pos] == ';') {
			data.pos++;
		}

		using Item = std::pair<unsigned int, char32_t>;

		static constexpr Item conversionArray[] = {
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
				return createCharacterToken(i.second);

			}
		}

		if ((id > 0x10FFFF) ||
				(0xD800 <= id && id <= 0xDFFF) ||
				(0x0001 <= id && id <= 0x0008) ||
				(0x000D <= id && id <= 0x001F) ||
				(0x007F <= id && id <= 0x009F) ||
				(0xFDD0 <= id && id <= 0xFDEF)) {
			return createCharacterToken(U'\U0000FFFD');
		}

		static constexpr unsigned int disallowedIDs[] {
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
				return token;
			}
		}

		return createCharacterToken(id);
	}
	std::string characters = "";
	std::vector<std::pair<const char*, const char32_t*>> characterReferenceList(
			std::begin(characterReferences), std::end(characterReferences));
	auto matchSubStr = [&characters] (std::pair<const char*, const char32_t*> pair) {
		if(characters == std::string(pair.first).substr(0, characters.length() - 1)) {
			return false;
		}
		return true;
	};
	for (; data.pos < data.string.length(); data.pos++) {
		characters += data.string[data.pos];
		std::vector<std::pair<const char*, const char32_t*>>::iterator it =
				std::remove_if(characterReferenceList.begin(), characterReferenceList.end(), matchSubStr);
		if (characterReferenceList.size() == 1 && characters == std::string((*it).first)) {
			return createCharacterToken((*it).second[0]);
		}
	}
	return token;
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
