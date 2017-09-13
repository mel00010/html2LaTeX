/*******************************************************************************
 * TokenizationMisc.cpp
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

#include "TokenizationMisc.hpp"

#include "TokenizationTypes.hpp"

namespace HTML {
namespace Parse {
namespace Tokenization {
DOCTYPEToken createDOCTYPEToken(const std::string& name, const std::string& public_identifier,
		const std::string& system_identifier, const bool force_quirks) {
	return DOCTYPEToken { name, public_identifier, system_identifier, force_quirks };
}

TagToken createTagToken(const std::string& tag_name, const bool self_closing, const std::list<Attribute>& attributes) {
	return TagToken { tag_name, self_closing, attributes };
}
CharacterToken createCharacterToken(const char32_t& data) {
	return CharacterToken { data };
}
CommentToken createCommentToken(const std::string& data) {
	return CommentToken { data };
}
EOFToken createEOFToken() {
	return EOFToken { };
}


} /* namespace Tokenization */
} /* namespace Parse */
} /* namespace HTML */

