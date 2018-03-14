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
#ifndef SRC_HTML_DOM_HTMLINPUTELEMENT_HPP_
#define SRC_HTML_DOM_HTMLINPUTELEMENT_HPP_

#include "DOMString.hpp"
#include "FileList.hpp"
#include "HTMLFormElement.hpp"
#include "NodeList.hpp"
#include "USVString.hpp"
#include "ValidityState.hpp"

#include <any>
#include <optional>

namespace HTML {
namespace DOM {

enum class SelectionMode {
		PRESERVE
};

class HTMLInputElement: public HTMLElement {
	public:
		DOMString accept;
		DOMString alt;
		DOMString autocomplete;
		bool autofocus;
		bool defaultChecked;
		bool checked;
		DOMString dirName;
		bool disabled;
		const std::optional<HTMLFormElement> form;
		std::optional<FileList> files;
		USVString formAction;
		DOMString formEnctype;
		DOMString formMethod;
		bool formNoValidate;
		DOMString formTarget;
		unsigned long height;
		bool indeterminate;
		const std::optional<HTMLElement> list;
		DOMString max;
		long maxLength;
		DOMString min;
		long minLength;
		bool multiple;
		DOMString name;
		DOMString pattern;
		DOMString placeholder;
		bool readOnly;
		bool required;
		unsigned long size;
		USVString src;
		DOMString step;
		DOMString type;
		DOMString defaultValue;
		DOMString value = U"";
		std::optional<std::any> valueAsDate;
		double valueAsNumber;
		unsigned long width;

		void stepUp(long n = 1);
		void stepDown(long n = 1);

		const bool willValidate;
		const ValidityState validity;
		const DOMString validationMessage;
		bool checkValidity();
		bool reportValidity();
		void setCustomValidity(DOMString error);

		const std::optional<NodeList> labels;

		void select();
		std::optional<unsigned long> selectionStart;
		std::optional<unsigned long> selectionEnd;
		std::optional<DOMString> selectionDirection;
		void setRangeText(DOMString replacement);
		void setRangeText(DOMString replacement, unsigned long start, unsigned long end, SelectionMode selectionMode = SelectionMode::PRESERVE);
		void setSelectionRange(unsigned long start, unsigned long end);
		void setSelectionRange(unsigned long start, unsigned long end, DOMString direction);

		// also has obsolete members
		DOMString align;
		DOMString useMap;
};

} /* namespace DOM */
} /* namespace HTML */

#endif /* SRC_HTML_DOM_HTMLINPUTELEMENT_HPP_ */

