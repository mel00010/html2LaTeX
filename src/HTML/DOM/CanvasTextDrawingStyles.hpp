/*******************************************************************************
 * CanvasTextDrawingStyles.hpp
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
#ifndef SRC_HTML_DOM_CANVASTEXTDRAWINGSTYLES_HPP_
#define SRC_HTML_DOM_CANVASTEXTDRAWINGSTYLES_HPP_

#include "DOMString.hpp"

namespace HTML {
namespace DOM {

enum class CanvasTextAlign {
	START, END, LEFT, RIGHT, CENTER
};

enum class CanvasTextBaseline {
	TOP, HANGING, MIDDLE, ALPHABETIC, IDEOGRAPHIC, BOTTOM
};

enum class CanvasDirection {
	LTR, RTL, INHERIT
};

/* Mixin */
class CanvasTextDrawingStyles {
	public:
		// text
		DOMString font; // (default 10px sans-serif)
		CanvasTextAlign textAlign; // (default: "start")
		CanvasTextBaseline textBaseline; // (default: "alphabetic")
		CanvasDirection direction; // (default: "inherit")
};

} /* namespace DOM */
} /* namespace HTML */



#endif /* SRC_HTML_DOM_CANVASTEXTDRAWINGSTYLES_HPP_ */
