/*******************************************************************************
 * HTMLElement.hpp
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
#ifndef SRC_HTML_WEBAPI_HTMLELEMENT_HPP_
#define SRC_HTML_WEBAPI_HTMLELEMENT_HPP_

#include <optional>

#include "../DOM/DOMString.hpp"
#include "../DOM/Element.hpp"

namespace HTML {
namespace WebAPI {

class HTMLElement: public DOM::Element, public GlobalEventHandlers, public DocumentAndElementEventHandlers, public ElementContentEditable, public NoncedElement {
	public:
		// metadata attributes
		DOM::DOMString title;
		DOM::DOMString lang;
		bool translate;
		DOM::DOMString dir;


		// user interaction
		bool hidden;
		void click();
		long tabIndex;
		void focus(std::optional<FocusOptions> options);
		void blur();
		DOM::DOMString accessKey;
		const DOM::DOMString accessKeyLabel;
		bool draggable;
		bool spellcheck;
		DOM::DOMString autocapitalize;

		DOM::DOMString innerText;

	protected:
		const DOMStringMap dataset;
};

class HTMLUnknownElement: public HTMLElement {
};

} /* namespace WebAPI */
} /* namespace HTML */

#endif /* SRC_HTML_WEBAPI_HTMLELEMENT_HPP_ */
