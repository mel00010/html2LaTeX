/*******************************************************************************
 * HTMLObjectElement.hpp
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
#ifndef SRC_HTML_WEBAPI_HTMLOBJECTELEMENT_HPP_
#define SRC_HTML_WEBAPI_HTMLOBJECTELEMENT_HPP_

#include "HTMLFormElement.hpp"
#include "ValidityState.hpp"

#include <optional>

#include "../DOM/Document.hpp"
#include "../DOM/DOMString.hpp"
#include "../DOM/USVString.hpp"

namespace HTML {
namespace WebAPI {

class HTMLObjectElement: public HTMLElement {
	public:
		DOM::USVString data;
		DOM::DOMString type;
		bool typeMustMatch;
		DOM::DOMString name;
		DOM::DOMString useMap;
		const std::optional<HTMLFormElement> form;
		DOM::DOMString width;
		DOM::DOMString height;
		const std::optional<DOM::Document> contentDocument;
		const std::optional<WindowProxy> contentWindow;
		std::optional<DOM::Document> getSVGDocument();

		const bool willValidate;
		const ValidityState validity;
		const DOM::DOMString validationMessage;
		bool checkValidity();
		bool reportValidity();
		void setCustomValidity(DOM::DOMString error);

		// also has obsolete members
		DOM::DOMString align;
		DOM::DOMString archive;
		DOM::DOMString code;
		bool declare;
		unsigned long hspace;
		DOM::DOMString standby;
		unsigned long vspace;
		DOM::DOMString codeBase;
		DOM::DOMString codeType;

		DOM::DOMString border = "";
};

} /* namespace WebAPI */
} /* namespace HTML */

#endif /* SRC_HTML_WEBAPI_HTMLOBJECTELEMENT_HPP_ */

