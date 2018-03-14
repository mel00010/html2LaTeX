/*******************************************************************************
 * HTMLTextAreaElement.hpp
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
#ifndef SRC_HTML_DOM_HTMLTEXTAREAELEMENT_HPP_
#define SRC_HTML_DOM_HTMLTEXTAREAELEMENT_HPP_

#include "DOMString.hpp"
#include "HTMLFormElement.hpp"
#include "NodeList.hpp"
#include "ValidityState.hpp"

#include <optional>

namespace HTML {
namespace DOM {

class HTMLTextAreaElement: public HTMLElement {
	public:
		DOMString autocomplete;
		bool autofocus;
		unsigned long cols;
		DOMString dirName;
		bool disabled;
		const std::optional<HTMLFormElement> form;
		long maxLength;
		long minLength;
		DOMString name;
		DOMString placeholder;
		bool readOnly;
		bool required;
		unsigned long rows;
		DOMString wrap;

		const DOMString type;
		DOMString defaultValue;
		DOMString value = "";
		const unsigned long textLength;

		const bool willValidate;
		const ValidityState validity;
		const DOMString validationMessage;
		bool checkValidity();
		bool reportValidity();
		void setCustomValidity(DOMString error);

		const NodeList labels;

		void select();
		unsigned long selectionStart;
		unsigned long selectionEnd;
		DOMString selectionDirection;
		void setRangeText(DOMString replacement);
		void setRangeText(DOMString replacement, unsigned long start, unsigned long end, SelectionMode selectionMode = SelectionMode::PRESERVE);
		void setSelectionRange(unsigned long start, unsigned long end);
		void setSelectionRange(unsigned long start, unsigned long end, DOMString direction);
};

} /* namespace DOM */
} /* namespace HTML */

#endif /* SRC_HTML_DOM_HTMLTEXTAREAELEMENT_HPP_ */

