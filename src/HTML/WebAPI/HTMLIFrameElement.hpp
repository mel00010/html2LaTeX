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
#ifndef SRC_HTML_WEBAPI_HTMLIFRAMEELEMENT_HPP_
#define SRC_HTML_WEBAPI_HTMLIFRAMEELEMENT_HPP_

#include "HTMLElement.hpp"

#include <optional>

#include "../DOM/Document.hpp"
#include "../DOM/DOMString.hpp"
#include "../DOM/DOMTokenList.hpp"
#include "../DOM/USVString.hpp"

namespace HTML {
namespace WebAPI {

class HTMLIFrameElement: public HTMLElement {
	public:
		DOM::USVString src;
		DOM::DOMString srcdoc;
		DOM::DOMString name;

	protected:
		const DOM::DOMTokenList sandbox;

	public:
		bool allowFullscreen;
		bool allowPaymentRequest;
		bool allowUserMedia;
		DOM::DOMString width;
		DOM::DOMString height;
		DOM::DOMString referrerPolicy;
		const std::optional<DOM::Document> contentDocument;
		const std::optional<WindowProxy> contentWindow;
		std::optional<DOM::Document> getSVGDocument();

		// also has obsolete members
		DOM::DOMString align;
		DOM::DOMString scrolling;
		DOM::DOMString frameBorder;
		DOM::USVString longDesc;

		DOM::DOMString marginHeight = "";
		DOM::DOMString marginWidth = "";
};

} /* namespace WebAPI */
} /* namespace HTML */

#endif /* SRC_HTML_WEBAPI_HTMLIFRAMEELEMENT_HPP_ */

