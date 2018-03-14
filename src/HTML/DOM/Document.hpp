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

#include "../WebAPI/Document.hpp"

#include "Comment.hpp"
#include "DocumentFragment.hpp"
#include "DocumentOrShadowRoot.hpp"
#include "DocumentType.hpp"
#include "DOMImplementation.hpp"
#include "DOMString.hpp"
#include "Event.hpp"
#include "HTMLCollection.hpp"
#include "NodeFilter.hpp"
#include "NodeIterator.hpp"
#include "NodeList.hpp"
#include "ProcessingInstruction.hpp"
#include "Range.hpp"
#include "Text.hpp"
#include "TreeWalker.hpp"
#include "USVString.hpp"

#include <list>
#include <optional>
#include <variant>

#include "../WebAPI/EventHandler.hpp"
#include "../WebAPI/HTMLAllCollection.hpp"
#include "../WebAPI/HTMLHeadElement.hpp"
#include "../WebAPI/HTMLScriptElement.hpp"
#include "../WebAPI/Location.hpp"

namespace HTML {
namespace WebAPI {

enum class DocumentReadyState {
	LOADING, INTERACTIVE, COMPLETE
};

typedef std::variant<HTMLScriptElement, SVGScriptElement> HTMLOrSVGScriptElement;

} /* namespace WebAPI */
} /* namespace HTML */

namespace HTML {
namespace DOM {

class Document: public Node,
		public DocumentOrShadowRoot,
		public ParentNode,
		public WebAPI::GlobalEventHandlers,
		public WebAPI::DocumentAndElementEventHandlers {
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
		const std::optional<WebAPI::Location> location;
		USVString domain;
		const USVString referrer;
		USVString cookie;
		const DOMString lastModified;
		const WebAPI::DocumentReadyState readyState;

		// DOM tree accessors
		object getObject(DOMString name);
		DOMString title;
		DOMString dir;
		std::optional<WebAPI::HTMLElement> body;
		const std::optional<WebAPI::HTMLHeadElement> head;

	protected:
		const HTMLCollection images;
		const HTMLCollection embeds;
		const HTMLCollection plugins;
		const HTMLCollection links;
		const HTMLCollection forms;
		const HTMLCollection scripts;

	public:
		NodeList getElementsByName(DOMString elementName);
		const std::optional<WebAPI::HTMLOrSVGScriptElement> currentScript; // classic scripts in a document tree onlys

		// dynamic markup insertion
		Document open(DOMString type = "text/html", DOMString replace = "");
		WindowProxy open(USVString url, DOMString name, DOMString features);
		void close();
		void write(std::list<DOMString> text);
		void writeln(std::list<DOMString> text);

		// user interaction
		const std::optional<WindowProxy> defaultView;
		const std::optional<Element> activeElement;
		bool hasFocus();
		DOMString designMode;
		bool execCommand(DOMString commandId, bool showUI = false, DOMString value = "");
		bool queryCommandEnabled(DOMString commandId);
		bool queryCommandIndeterm(DOMString commandId);
		bool queryCommandState(DOMString commandId);
		bool queryCommandSupported(DOMString commandId);
		DOMString queryCommandValue(DOMString commandId);

		// special event handler IDL attributes that only apply to Document objects
		WebAPI::EventHandler onreadystatechange;
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
		const WebAPI::HTMLAllCollection all;
};

class XMLDocument: public Document {

};

} /* namespace DOM */
} /* namespace HTML */

#endif /* SRC_HTML_DOM_DOCUMENT_HPP_ */