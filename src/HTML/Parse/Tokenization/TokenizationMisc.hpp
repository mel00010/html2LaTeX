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

#include <list>
#include <string>
#include <utility>

namespace HTML {
namespace Parse {
namespace Tokenization {

DOCTYPEToken createDOCTYPEToken(const std::string& name = "\0xFF",
		const std::string& public_identifier = "\0xFF",
		const std::string& system_identifier = "\0xFF",
		const bool force_quirks = false);

TagToken createTagToken(const std::string& tag_name = "",
		const bool self_closing = false,
		const std::list<Attribute>& attributes = { });
CharacterToken createCharacterToken(const char32_t& data = '\0xFF');
CommentToken createCommentToken(const std::string& data = "");
EOFToken createEOFToken();


} /* namespace Tokenization */
} /* namespace Parse */
} /* namespace HTML */



#endif /* SRC_HTML_PARSE_TOKENIZATION_TOKENIZATIONMISC_HPP_ */
