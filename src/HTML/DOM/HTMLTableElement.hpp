/*******************************************************************************
 * HTMLTableElement.hpp
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
#ifndef SRC_HTML_DOM_HTMLTABLEELEMENT_HPP_
#define SRC_HTML_DOM_HTMLTABLEELEMENT_HPP_

#include "DOMString.hpp"
#include "HTMLCollection.hpp"
#include "HTMLTableCaptionElement.hpp"
#include "HTMLTableRowElement.hpp"
#include "HTMLTableSectionElement.hpp"

#include <optional>

namespace HTML {
namespace DOM {

class HTMLTableElement: public HTMLElement {
	public:
		std::optional<HTMLTableCaptionElement> caption;
		HTMLTableCaptionElement createCaption();
		void deleteCaption();

		std::optional<HTMLTableCaptionElement> tHead;
		HTMLTableSectionElement createTHead();
		void deleteTHead();

		std::optional<HTMLTableCaptionElement> tFoot;
		HTMLTableSectionElement createTFoot();
		void deleteTFoot();

		HTMLTableSectionElement createTBody();

		HTMLTableRowElement insertRow(long index = -1);
		void deleteRow(long index);

		// also has obsolete members
		DOMString align;
		DOMString border;
		DOMString frame;
		DOMString rules;
		DOMString summary;
		DOMString width;

		DOMString bgColor = "";
		DOMString cellPadding = "";
		DOMString cellSpacing = "";

	protected:
		const HTMLCollection rows;
		const HTMLCollection tBodies;
};

} /* namespace DOM */
} /* namespace HTML */

#endif /* SRC_HTML_DOM_HTMLTABLEELEMENT_HPP_ */

