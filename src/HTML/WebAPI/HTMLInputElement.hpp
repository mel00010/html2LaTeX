/*******************************************************************************
 * HTMLInputElement.hpp
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
#ifndef SRC_HTML_WEBAPI_HTMLINPUTELEMENT_HPP_
#define SRC_HTML_WEBAPI_HTMLINPUTELEMENT_HPP_

#include "HTMLFormElement.hpp"
#include "ValidityState.hpp"

#include <any>
#include <optional>

#include "../DOM/DOMString.hpp"
#include "../DOM/NodeList.hpp"
#include "../DOM/USVString.hpp"

namespace HTML {
namespace WebAPI {

class HTMLInputElement: public HTMLElement {
	public:
		DOM::DOMString accept;
		DOM::DOMString alt;
		DOM::DOMString autocomplete;
		bool autofocus;
		bool defaultChecked;
		bool checked;
		DOM::DOMString dirName;
		bool disabled;
		const std::optional<HTMLFormElement> form;
		std::optional<FileList> files;
		DOM::USVString formAction;
		DOM::DOMString formEnctype;
		DOM::DOMString formMethod;
		bool formNoValidate;
		DOM::DOMString formTarget;
		unsigned long height;
		bool indeterminate;
		const std::optional<HTMLElement> list;
		DOM::DOMString max;
		long maxLength;
		DOM::DOMString min;
		long minLength;
		bool multiple;
		DOM::DOMString name;
		DOM::DOMString pattern;
		DOM::DOMString placeholder;
		bool readOnly;
		bool required;
		unsigned long size;
		DOM::USVString src;
		DOM::DOMString step;
		DOM::DOMString type;
		DOM::DOMString defaultValue;
		DOM::DOMString value = "";
		std::optional<std::any> valueAsDate;
		double valueAsNumber;
		unsigned long width;

		void stepUp(long n = 1);
		void stepDown(long n = 1);

		const bool willValidate;
		const ValidityState validity;
		const DOM::DOMString validationMessage;
		bool checkValidity();
		bool reportValidity();
		void setCustomValidity(DOM::DOMString error);

		const std::optional<DOM::NodeList> labels;

		void select();
		std::optional<unsigned long> selectionStart;
		std::optional<unsigned long> selectionEnd;
		std::optional<DOM::DOMString> selectionDirection;
		void setRangeText(DOM::DOMString replacement);
		void setRangeText(DOM::DOMString replacement, unsigned long start, unsigned long end, SelectionMode selectionMode = SelectionMode::PRESERVE);
		void setSelectionRange(unsigned long start, unsigned long end);
		void setSelectionRange(unsigned long start, unsigned long end, DOM::DOMString direction);

		// also has obsolete members
		DOM::DOMString align;
		DOM::DOMString useMap;
};

} /* namespace WebAPI */
} /* namespace HTML */

#endif /* SRC_HTML_WEBAPI_HTMLINPUTELEMENT_HPP_ */

