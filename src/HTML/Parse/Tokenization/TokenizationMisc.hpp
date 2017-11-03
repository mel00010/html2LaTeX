/*******************************************************************************
 * TokenizationMisc.hpp
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
#ifndef SRC_HTML_PARSE_TOKENIZATION_TOKENIZATIONMISC_HPP_
#define SRC_HTML_PARSE_TOKENIZATION_TOKENIZATIONMISC_HPP_

#include "TokenizationTypes.hpp"

#include <array>
#include <list>
#include <string>
#include <utility>

namespace HTML {
namespace Parse {
namespace Tokenization {

Token createDOCTYPEToken(const std::u32string& name = U"\0xFF",
const std::u32string& public_id = U"\0xFF",
const std::u32string& system_identifier = U"\0xFF",
const bool system_id = false);

Token createStartTagToken(const std::u32string& tag_name = U"",
		const bool self_closing = false,
		const std::list<Attribute>& attributes = { });
Token createEndTagToken(const std::u32string& tag_name = U"",
		const bool self_closing = false,
		const std::list<Attribute>& attributes = { });
Token createCharacterToken(const char32_t& data = EOF);
Token createCharacterToken(const unsigned int& data = EOF);
Token createCharacterToken(const int& data = EOF);

Token createCommentToken(const std::u32string& data = U"");
Token createEOFToken();


} /* namespace Tokenization */
} /* namespace Parse */
} /* namespace HTML */



#endif /* SRC_HTML_PARSE_TOKENIZATION_TOKENIZATIONMISC_HPP_ */
