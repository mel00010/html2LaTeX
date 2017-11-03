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

Token createDOCTYPEToken(const std::string& name = "\0xFF",
		const std::string& public_id = "\0xFF",
		const std::string& system_identifier = "\0xFF",
		const bool system_id = false);

Token createStartTagToken(const std::string& tag_name = "",
		const bool self_closing = false,
		const std::list<Attribute>& attributes = { });
Token createEndTagToken(const std::string& tag_name = "",
		const bool self_closing = false,
		const std::list<Attribute>& attributes = { });
Token createCharacterToken(const std::array<const char32_t, 2> data);
Token createCharacterToken(const char32_t& first_character = EOF, const char32_t& second_character = EOF);
Token createCharacterToken(const unsigned int& first_character = EOF, const unsigned int& second_character = EOF);

Token createCommentToken(const std::string& data = "");
Token createEOFToken();


} /* namespace Tokenization */
} /* namespace Parse */
} /* namespace HTML */



#endif /* SRC_HTML_PARSE_TOKENIZATION_TOKENIZATIONMISC_HPP_ */
