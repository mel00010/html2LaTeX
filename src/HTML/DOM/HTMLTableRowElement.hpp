/*******************************************************************************
 * HTMLTableRowElement.hpp
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
#ifndef SRC_HTML_DOM_HTMLTABLEROWELEMENT_HPP_
#define SRC_HTML_DOM_HTMLTABLEROWELEMENT_HPP_

#include "DOMString.hpp"
#include "HTMLCollection.hpp"
#include "HTMLTableCellElement.hpp"

namespace HTML {
namespace DOM {

class HTMLTableRowElement: public HTMLElement {
	public:
		const long rowIndex;
		const long sectionRowIndex;

		HTMLTableCellElement insertCell(long index = -1);
		void deleteCell(long index);

		// also has obsolete members
		DOMString align;
		DOMString ch;
		DOMString chOff;
		DOMString vAlign;

		DOMString bgColor = U"";

	protected:
		const HTMLCollection cells;
};

} /* namespace DOM */
} /* namespace HTML */

#endif /* SRC_HTML_DOM_HTMLTABLEROWELEMENT_HPP_ */

