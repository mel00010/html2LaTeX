/*******************************************************************************
 * HTMLTableCellElement.hpp
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
#ifndef SRC_HTML_DOM_HTMLTABLECELLELEMENT_HPP_
#define SRC_HTML_DOM_HTMLTABLECELLELEMENT_HPP_

#include "DOMString.hpp"
#include "HTMLElement.hpp"

namespace HTML {
namespace DOM {

class HTMLTableCellElement: public HTMLElement {
	public:
		unsigned long colSpan;
		unsigned long rowSpan;
		DOMString headers;
		const long cellIndex;

		DOMString scope; // only conforming for th elements
		DOMString abbr;  // only conforming for th elements

		// also has obsolete members
		DOMString align;
		DOMString axis;
		DOMString height;
		DOMString width;

		DOMString ch;
		DOMString chOff;
		bool noWrap;
		DOMString vAlign;

		DOMString bgColor = U"";
};

} /* namespace DOM */
} /* namespace HTML */

#endif /* SRC_HTML_DOM_HTMLTABLECELLELEMENT_HPP_ */

