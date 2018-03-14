/*******************************************************************************
 * HTMLImageElement.hpp
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
#ifndef SRC_HTML_DOM_HTMLIMAGEELEMENT_HPP_
#define SRC_HTML_DOM_HTMLIMAGEELEMENT_HPP_

#include "HTMLElement.hpp"

#include <future>
#include <optional>

#include "../DOM/DOMString.hpp"
#include "../DOM/USVString.hpp"

namespace HTML {
namespace DOM {

class HTMLImageElement: public HTMLElement {
	public:
		HTMLImageElement();
		HTMLImageElement(unsigned long width, unsigned long height);

		DOMString alt;
		USVString src;
		USVString srcset;
		DOMString sizes;
		std::optional<DOMString> crossOrigin;
		DOMString useMap;
		bool isMap;
		unsigned long width;
		unsigned long height;
		const unsigned long naturalWidth;
		const unsigned long naturalHeight;
		const bool complete;
		const USVString currentSrc;
		DOMString referrerPolicy;
		DOMString decoding;

		std::promise decode();

		// also has obsolete members
		DOMString name;
		USVString lowsrc;
		DOMString align;
		unsigned long hspace;
		unsigned long vspace;
		USVString longDesc;

		DOMString border = "";
};

}
/* namespace DOM */
} /* namespace HTML */

#endif /* SRC_HTML_DOM_HTMLIMAGEELEMENT_HPP_ */

