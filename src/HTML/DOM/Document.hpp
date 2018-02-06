/*******************************************************************************
 * Document.hpp
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
#ifndef SRC_HTML_DOM_DOCUMENT_HPP_
#define SRC_HTML_DOM_DOCUMENT_HPP_

#include <optional>
#include "../DOM/Comment.hpp"
#include "../DOM/DocumentFragment.hpp"
#include "../DOM/DocumentType.hpp"
#include "../DOM/DOMImplementation.hpp"
#include "../DOM/DOMString.hpp"
#include "../DOM/HTMLCollection.hpp"
#include "../DOM/Node.hpp"
#include "../DOM/Text.hpp"

namespace HTML {

class Document : public Node {
	public:
		const DOMImplementation implementation;
		const DOMString URL;
		const DOMString documentURI;
		const DOMString origin;
		const DOMString compatMode;
		const DOMString characterSet;
		const DOMString contentType;

		const DocumentType doctype;
		const std::optional<Element> documentElement;
		HTMLCollection getElementsByTagName(DOMString localName);
		HTMLCollection getElementsByTagNameNS(std::optional<DOMString> name_space, DOMString localName);
		HTMLCollection getElementsByClassName(DOMString classNames);

		Element createElement(DOMString localName);
		Element createElementNS(std::optional<DOMString> name_space, DOMString qualifiedName);
		DocumentFragment createDocumentFragment();
		Text createTextNode(DOMString data);
		Comment createComment(DOMString data);
		ProcessingInstruction createProcessingInstruction(DOMString target, DOMString data);

		Node importNode(Node node, bool deep = false);
		Node adoptNode(Node node);

		Event createEvent(DOMString interface);

		Range createRange();

		// NodeFilter.SHOW_ALL = 0xFFFFFFFF
		NodeIterator createNodeIterator(Node root, unsigned long whatToShow = 0xFFFFFFFF, std::optional<NodeFilter> filter = std::nullopt);
		TreeWalker createTreeWalker(Node root, unsigned long whatToShow = 0xFFFFFFFF, std::optional<NodeFilter> filter = std::nullopt);
};

class XMLDocument : public Document {

};

} /* namespace HTML */


#endif /* SRC_HTML_DOM_DOCUMENT_HPP_ */
