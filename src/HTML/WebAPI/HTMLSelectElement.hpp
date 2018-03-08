/*******************************************************************************
 * HTMLSelectElement.hpp
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
#ifndef SRC_HTML_WEBAPI_HTMLSELECTELEMENT_HPP_
#define SRC_HTML_WEBAPI_HTMLSELECTELEMENT_HPP_

#include "HTMLFormElement.hpp"
#include "HTMLOptGroupElement.hpp"
#include "HTMLOptionElement.hpp"
#include "HTMLOptionsCollection.hpp"
#include "ValidityState.hpp"

#include <optional>
#include <variant>

#include "../DOM/DOMString.hpp"
#include "../DOM/NodeList.hpp"

namespace HTML {
namespace WebAPI {

class HTMLSelectElement: public HTMLElement {
	public:
		DOM::DOMString autocomplete;
		bool autofocus;
		bool disabled;
		const std::optional<HTMLFormElement> form;
		bool multiple;
		DOM::DOMString name;
		bool required;
		unsigned long size;

		const DOM::DOMString type;

	protected:
		const HTMLOptionsCollection options;

	public:
		unsigned long length;
		std::optional<Element> getItem(unsigned long index);
		std::optional<HTMLOptionElement> namedItem(DOM::DOMString name);
		void add(std::variant<HTMLOptionElement, HTMLOptGroupElement> element,
				std::optional<std::variant<HTMLElement, long>> before = std::nullopt);
		void remove(); // ChildNode overload
		void remove(long index);
		void set(unsigned long index, std::optional<HTMLOptionElement> option);

	protected:
		const DOM::HTMLCollection selectedOptions;

	public:
		long selectedIndex;
		DOM::DOMString value;

		const bool willValidate;
		const ValidityState validity;
		const DOM::DOMString validationMessage;
		bool checkValidity();
		bool reportValidity();
		void setCustomValidity(DOM::DOMString error);

		const DOM::NodeList labels;
};

} /* namespace WebAPI */
} /* namespace HTML */

#endif /* SRC_HTML_WEBAPI_HTMLSELECTELEMENT_HPP_ */

