/*******************************************************************************
 * HTMLButtonElement.hpp
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
#ifndef SRC_HTML_DOM_HTMLBUTTONELEMENT_HPP_
#define SRC_HTML_DOM_HTMLBUTTONELEMENT_HPP_

#include "DOMString.hpp"
#include "HTMLFormElement.hpp"
#include "NodeList.hpp"
#include "USVString.hpp"
#include "ValidityState.hpp"

#include <optional>

namespace HTML {
namespace DOM {

class HTMLButtonElement: public HTMLElement {
	public:
		bool autofocus;
		bool disabled;
		const std::optional<HTMLFormElement> form;
		USVString formAction;
		DOMString formEnctype;
		DOMString formMethod;
		bool formNoValidate;
		DOMString formTarget;
		DOMString name;
		DOMString type;
		DOMString value;

		const bool willValidate;
		const ValidityState validity;
		const DOMString validationMessage;
		bool checkValidity();
		bool reportValidity();
		void setCustomValidity(DOMString error);

		const NodeList labels;
};

} /* namespace DOM */
} /* namespace HTML */

#endif /* SRC_HTML_DOM_HTMLBUTTONELEMENT_HPP_ */

