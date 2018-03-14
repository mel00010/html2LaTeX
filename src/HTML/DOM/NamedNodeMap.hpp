/*******************************************************************************
 * NamedNodeMap.hpp
 * Copyright (C) 2018  Mel McCalla <melmccalla@gmail.com>
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
#ifndef SRC_HTML_DOM_NAMEDNODEMAP_HPP_
#define SRC_HTML_DOM_NAMEDNODEMAP_HPP_

#include "Attr.hpp"
#include "DOMString.hpp"

#include <optional>

namespace HTML {
namespace DOM {

class Attr;
class Element;
class Node;

class NamedNodeMap {
	public:
		const unsigned long length;
		std::optional<Attr> item(unsigned long index); // getter
		std::optional<Attr> getNamedItem(DOMString qualifiedName); // getter
		std::optional<Attr> getNamedItemNS(std::optional<DOMString> name_space, DOMString localName);
		std::optional<Attr> setNamedItem(Attr attr);
		std::optional<Attr> setNamedItemNS(Attr attr);
		Attr removeNamedItem(DOMString qualifiedName);
		Attr removeNamedItemNS(std::optional<DOMString> name_space, DOMString localName);
};

} /* namespace DOM */
} /* namespace HTML */

#endif /* SRC_HTML_DOM_NAMEDNODEMAP_HPP_ */
