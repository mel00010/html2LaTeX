/*******************************************************************************
 * Node.hpp
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
#ifndef SRC_HTML_DOM_NODE_HPP_
#define SRC_HTML_DOM_NODE_HPP_

//#include "Document.hpp"
#include "DOMString.hpp"

#include <list>
#include <optional>

namespace HTML {
namespace DOM {

//class Node;
class Element;
class Document;

class Node {
	public:
		enum NodeType {
			ELEMENT_NODE = 1,
			ATTRIBUTE_NODE = 2, // historical
			TEXT_NODE = 3,
			CDATA_SECTION_NODE = 4, // historical
			ENTITY_REFERENCE_NODE = 5, // historical
			ENTITY_NODE = 6, // historical
			PROCESSING_INSTRUCTION_NODE = 7,
			COMMENT_NODE = 8,
			DOCUMENT_NODE = 9,
			DOCUMENT_TYPE_NODE = 10,
			DOCUMENT_FRAGMENT_NODE = 11,
			NOTATION_NODE = 12, // historical
		};

		const NodeType nodeType;
		const DOMString nodeName;

		const std::optional<DOMString>& baseURI;

		const std::optional<Document>& ownerDocument;
		const std::optional<Node>& parentNode;
		const std::optional<Element>& parentElement;
		bool hasChildNodes();
		const std::list<Node>& childNodes;
		const std::optional<Node>& firstChild;
		const std::optional<Node>& lastChild;
		const std::optional<Node>& previousSibling;
		const std::optional<Node>& nextSibling;

		std::optional<DOMString>& nodeValue;
		std::optional<DOMString>& textContent;
		void normalize();

		Node cloneNode(bool deep = false);
		bool isEqualNode(std::optional<Node>& node);

		enum DocumentPosition {
			DOCUMENT_POSITION_DISCONNECTED = 0x01,
			DOCUMENT_POSITION_PRECEDING = 0x02,
			DOCUMENT_POSITION_FOLLOWING = 0x04,
			DOCUMENT_POSITION_CONTAINS = 0x08,
			DOCUMENT_POSITION_CONTAINED_BY = 0x10,
			DOCUMENT_POSITION_IMPLEMENTATION_SPECIFIC = 0x20,
		};

		DocumentPosition compareDocumentPosition(Node& other);
		bool contains(std::optional<Node>& other);

		std::optional<DOMString> lookupPrefix(std::optional<DOMString>& name_space);
		std::optional<DOMString> lookupNamespaceURI(std::optional<DOMString>& prefix);
		bool isDefaultNamespace(std::optional<DOMString>& name_space);

		Node& insertBefore(Node& node, std::optional<Node>& child);
		Node& appendChild(Node& node);
		Node& replaceChild(Node& node, Node& child);
		Node& removeChild(Node& child);
};

} /* namespace DOM */
} /* namespace HTML */




#endif /* SRC_HTML_DOM_NODE_HPP_ */
