/*******************************************************************************
 * HTMLIFrameElement.hpp
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
#ifndef SRC_HTML_DOM_HTMLIFRAMEELEMENT_HPP_
#define SRC_HTML_DOM_HTMLIFRAMEELEMENT_HPP_

#include "Document.hpp"
#include "DOMString.hpp"
#include "DOMTokenList.hpp"
#include "HTMLElement.hpp"
#include "USVString.hpp"
#include "WindowProxy.hpp"

#include <optional>

namespace HTML {
namespace DOM {

class HTMLIFrameElement: public HTMLElement {
	public:
		USVString src;
		DOMString srcdoc;
		DOMString name;

	protected:
		const DOMTokenList sandbox;

	public:
		bool allowFullscreen;
		bool allowPaymentRequest;
		bool allowUserMedia;
		DOMString width;
		DOMString height;
		DOMString referrerPolicy;
		const std::optional<Document> contentDocument;
		const std::optional<WindowProxy> contentWindow;
		std::optional<Document> getSVGDocument();

		// also has obsolete members
		DOMString align;
		DOMString scrolling;
		DOMString frameBorder;
		USVString longDesc;

		DOMString marginHeight = U"";
		DOMString marginWidth = U"";
};

} /* namespace DOM */
} /* namespace HTML */

#endif /* SRC_HTML_DOM_HTMLIFRAMEELEMENT_HPP_ */

