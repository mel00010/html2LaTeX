/*******************************************************************************
 * HTMLTrackElement.hpp
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
#ifndef SRC_HTML_DOM_HTMLTRACKELEMENT_HPP_
#define SRC_HTML_DOM_HTMLTRACKELEMENT_HPP_

#include "DOMString.hpp"
#include "HTMLElement.hpp"
#include "TextTrack.hpp"
#include "USVString.hpp"

namespace HTML {
namespace DOM {

class HTMLTrackElement: public HTMLElement {
	public:
		DOMString kind;
		USVString src;
		DOMString srclang;
		DOMString label;
		bool _default;

		const unsigned short NONE = 0;
		const unsigned short LOADING = 1;
		const unsigned short LOADED = 2;
		const unsigned short ERROR = 3;
		const unsigned short readyState;

		const TextTrack track;
};

} /* namespace DOM */
} /* namespace HTML */

#endif /* SRC_HTML_DOM_HTMLTRACKELEMENT_HPP_ */
