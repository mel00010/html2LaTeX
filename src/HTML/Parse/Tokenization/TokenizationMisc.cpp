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

Token createDOCTYPEToken(const std::string& name, const std::string& public_id, const std::string& system_id, const bool force_quirks) {
	return Token { TokenType::DOCTYPE, DOCTYPEToken { name, public_id, system_id, force_quirks } };
}

Token createStartTagToken(const std::string& tag_name, const bool self_closing, const std::list<Attribute>& attributes) {
	return Token { TokenType::START_TAG, StartTagToken { tag_name, self_closing, attributes } };
}
Token createEndTagToken(const std::string& tag_name, const bool self_closing, const std::list<Attribute>& attributes) {
	return Token { TokenType::END_TAG, EndTagToken { tag_name, self_closing, attributes } };
}
Token createCharacterToken(const char32_t& data) {
	return Token { TokenType::CHARACTER, CharacterToken { data } };
}
Token createCharacterToken(const unsigned int& data) {
	return Token { TokenType::CHARACTER, CharacterToken { static_cast<char32_t>(data) } };
}
Token createCommentToken(const std::string& data) {
	return Token { TokenType::COMMENT, CommentToken { data } };
}
Token createEOFToken() {
	return Token { TokenType::END_OF_FILE, EOFToken { } };
}

} /* namespace Tokenization */
} /* namespace Parse */
} /* namespace HTML */

