/*******************************************************************************
 * TokenizerUtil.tpp
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

//#include "Tokenizer.hpp"

#include <HTML/Microsyntaxes/ASCII/ASCII.hpp>

namespace HTML {
namespace Parse {
namespace Tokenization {


template <class T> char32_t Tokenizer<T>::consume() {
	chars_consumed++;
	return getCharacterAtPosition(pos++);
}

template <class T> std::u32string Tokenizer<T>::consume(const size_t& number_of_chars) {
	std::u32string buffer = getCharactersAtPosition(pos, number_of_chars);
	pos += buffer.length();
	chars_consumed += buffer.length();
	return buffer;
}

template <class T> void Tokenizer<T>::emit(const DOCTYPEToken& token) {
	tree_constructor.dispatch(Token(token));
}
template <class T> void Tokenizer<T>::emit(const StartTagToken& token) {
	prev_start_tag = token;
	tree_constructor.dispatch(Token(token));
}
template <class T> void Tokenizer<T>::emit(const EndTagToken& token) {
	tree_constructor.dispatch(Token(token));
}
template <class T> void Tokenizer<T>::emit(const TagToken& token) {
	TagToken buf = token;
	if(attribute != Attribute() && !discard_attribute) {
		buf.attributes.push_back(attribute);
	}
	switch(token.type) {
		case TagToken::TagType::START:
			emit(static_cast<const StartTagToken&>(buf));
			break;
		case TagToken::TagType::END:
			emit(static_cast<const EndTagToken&>(buf));
			break;
		case TagToken::TagType::NONE:
			emitParseError();
			break;
		default:
			emitParseError();
			break;
	}
}
template <class T> void Tokenizer<T>::emit(const CommentToken& token) {
	tree_constructor.dispatch(Token(token));
}
template <class T> void Tokenizer<T>::emit(const CharacterToken& token) {
	tree_constructor.dispatch(Token(token));
}
template <class T> void Tokenizer<T>::emit(const EOFToken& token) {
	tree_constructor.dispatch(Token(token));
}
template <class T> void Tokenizer<T>::emit(const Token& token) {
	tree_constructor.dispatch(token);
}
template <class T> void Tokenizer<T>::emitParseError(__attribute__ ((unused)) const ParseError& error) {
}


template <class T> char32_t Tokenizer<T>::getCharacterAtPosition(const size_t& position) {
	if (position >= string.length()) {
		return EOF32;
	}
	return string[position];
}

template <class T> std::u32string Tokenizer<T>::getCharactersAtPosition(const size_t& position, const size_t& number_of_chars) {
	std::u32string characters = U"";
	for(size_t i = 0; i < number_of_chars; i++) {
		if (position + i >= string.length()) {
			characters.push_back(EOF32);
			break;
		}
		characters.push_back(string[position + i]);
	}
	return characters;
}

template <class T> bool Tokenizer<T>::isAppropriateEndTagToken() {
	if(tag.type != TagToken::TagType::END) {
		return false;
	}
	if(prev_start_tag.tag_name != tag.tag_name) {
		return false;
	}
	return true;
}
template <class T> bool Tokenizer<T>::isAttributeNameUnique() {
	for(const auto& i : tag.attributes) {
		if(attribute == i.name) {
			discard_attribute = true;
			return false;
		}
	}
	discard_attribute = false;
	return true;
}
template <class T> bool Tokenizer<T>::isAdjustedCurrentNode() {
	//TODO Finish function.  See section 8.2.3.2 in the HTML5 spec
	return false;
}

template <class T> bool Tokenizer<T>::currentNodeInHTMLNamespace() {
	//TODO Finish function.  See section 8.2.3.2 in the HTML5 spec
	return false;
}

template <class T> char32_t Tokenizer<T>::peek() {
	return getCharacterAtPosition(pos);
}

template <class T> std::u32string Tokenizer<T>::peek(const size_t& number_of_chars) {
	return getCharactersAtPosition(pos, number_of_chars);
}

template <class T> char32_t Tokenizer<T>::reconsume() {
	return getCharacterAtPosition(pos - 1);
}

template <class T> void Tokenizer<T>::switchToState(const State& new_state) {
	state = new_state;
}

template <class T> void Tokenizer<T>::unconsume() {
	pos--;
}

template <class T> void Tokenizer<T>::unconsume(const size_t& number_of_chars) {
	pos -= number_of_chars;
}

} /* namespace Tokenization */
} /* namespace Parse */
} /* namespace HTML */

