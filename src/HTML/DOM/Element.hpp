/*******************************************************************************
 * Element.hpp
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
#ifndef SRC_HTML_DOM_ELEMENT_HPP_
#define SRC_HTML_DOM_ELEMENT_HPP_

#include "Attr.hpp"
#include "DOMString.hpp"
#include "DOMTokenList.hpp"
#include "HTMLCollection.hpp"
#include "NamedNodeMap.hpp"
#include "Node.hpp"
#include "ShadowRoot.hpp"

#include <optional>
#include <vector>

namespace HTML {
namespace DOM {

struct ShadowRootInit;

class Element: public Node {
	public:
		const std::optional<DOMString> namespaceURI;
		const std::optional<DOMString> prefix;
		const DOMString localName;
		const DOMString tagName;

		DOMString id;
		DOMString className;
		DOMString slot;

		bool hasAttributes();

		std::vector<DOMString> getAttributeNames();
		std::optional<DOMString> getAttribute(DOMString qualifiedName);
		std::optional<DOMString> getAttributeNS(std::optional<DOMString> name_space, DOMString localName);
		void setAttribute(DOMString qualifiedName, DOMString value);
		void setAttributeNS(std::optional<DOMString> name_space, DOMString qualifiedName, DOMString value);
		void removeAttribute(DOMString qualifiedName);
		void removeAttributeNS(DOMString name_space, DOMString localName);
		bool hasAttribute(DOMString qualifiedName);
		bool hasAttributeNS(std::optional<DOMString> name_space, DOMString localName);

		std::optional<Attr> getAttributeNode(DOMString qualifiedName);
		std::optional<Attr> getAttributeNodeNS(std::optional<DOMString> name_space, DOMString localName);
		std::optional<Attr> setAttributeNode(Attr attr);
		std::optional<Attr> setAttributeNodeNS(Attr attr);
		Attr removeAttributeNode(Attr attr);

		ShadowRoot attachShadow(ShadowRootInit init);
		const std::optional<ShadowRoot> shadowRoot;

		std::optional<Element> closest(DOMString selectors);
		bool matches(DOMString selectors);
		bool webkitMatchesSelector(DOMString selectors); // historical alias of .matches

		HTMLCollection getElementsByTagName(DOMString qualifiedName);
		HTMLCollection getElementsByTagNameNS(std::optional<DOMString> name_space, DOMString localName);
		HTMLCollection getElementsByClassName(DOMString classNames);

		std::optional<Element> insertAdjacentElement(DOMString where, Element element); // historical
		void insertAdjacentText(DOMString where, DOMString data); // historical

	protected:
		const DOMTokenList classList;
		const NamedNodeMap attributes;
};

struct ShadowRootInit {
	public:
		ShadowRootMode mode;
};

}
/* namespace DOM */
} /* namespace HTML */

#endif /* SRC_HTML_DOM_ELEMENT_HPP_ */
