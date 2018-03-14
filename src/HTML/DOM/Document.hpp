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

#include "Comment.hpp"
#include "DocumentFragment.hpp"
#include "DocumentOrShadowRoot.hpp"
#include "DocumentType.hpp"
#include "DOMImplementation.hpp"
#include "DOMString.hpp"
#include "Element.hpp"
#include "Event.hpp"
#include "EventHandler.hpp"
#include "HTMLAllCollection.hpp"
#include "HTMLCollection.hpp"
#include "HTMLHeadElement.hpp"
#include "HTMLScriptElement.hpp"
#include "Location.hpp"
#include "NodeFilter.hpp"
#include "NodeIterator.hpp"
#include "NodeList.hpp"
#include "object.hpp"
#include "ProcessingInstruction.hpp"
#include "Range.hpp"
#include "Text.hpp"
#include "TreeWalker.hpp"
#include "USVString.hpp"

#include <list>
#include <optional>
#include <variant>

namespace HTML {
namespace DOM {

enum class DocumentReadyState {
	LOADING, INTERACTIVE, COMPLETE
};

//typedef std::variant<HTMLScriptElement, SVGScriptElement> HTMLOrSVGScriptElement;
typedef std::variant<HTMLScriptElement> HTMLOrSVGScriptElement;

class Element;
class Node;

class Document: public Node,
		public DocumentOrShadowRoot,
		public ParentNode,
		public GlobalEventHandlers,
		public DocumentAndElementEventHandlers {
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

	public:
		// resource metadata management
		const std::optional<Location> location;
		USVString domain;
		const USVString referrer;
		USVString cookie;
		const DOMString lastModified;
		const DocumentReadyState readyState;

		// DOM tree accessors
		object getObject(DOMString name);
		DOMString title;
		DOMString dir;
		std::optional<HTMLElement> body;
		const std::optional<HTMLHeadElement> head;

	protected:
		const HTMLCollection images;
		const HTMLCollection embeds;
		const HTMLCollection plugins;
		const HTMLCollection links;
		const HTMLCollection forms;
		const HTMLCollection scripts;

	public:
		NodeList getElementsByName(DOMString elementName);
		const std::optional<HTMLOrSVGScriptElement> currentScript; // classic scripts in a document tree onlys

		// dynamic markup insertion
		Document open(DOMString type = U"text/html", DOMString replace = U"");
//		WindowProxy open(USVString url, DOMString name, DOMString features);
		void close();
		void write(std::list<DOMString> text);
		void writeln(std::list<DOMString> text);

		// user interaction
//		const std::optional<WindowProxy> defaultView;
		const std::optional<Element> activeElement;
		bool hasFocus();
		DOMString designMode;
		bool execCommand(DOMString commandId, bool showUI = false, DOMString value = U"");
		bool queryCommandEnabled(DOMString commandId);
		bool queryCommandIndeterm(DOMString commandId);
		bool queryCommandState(DOMString commandId);
		bool queryCommandSupported(DOMString commandId);
		DOMString queryCommandValue(DOMString commandId);

		// special event handler IDL attributes that only apply to Document objects
		EventHandler onreadystatechange;
		DOMString fgColor;
		DOMString linkColor;
		DOMString vlinkColor;
		DOMString alinkColor;
		DOMString bgColor;

	protected:
		const HTMLCollection anchors;
		const HTMLCollection applets;

	public:
		void clear();
		void captureEvents();
		void releaseEvents();

	protected:
		const HTMLAllCollection all;
};

class XMLDocument: public Document {

};

} /* namespace DOM */
} /* namespace HTML */

#endif /* SRC_HTML_DOM_DOCUMENT_HPP_ */
