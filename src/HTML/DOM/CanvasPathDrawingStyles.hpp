/*******************************************************************************
 * CanvasPathDrawingStyles.hpp
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
#ifndef SRC_HTML_DOM_CANVASPATHDRAWINGSTYLES_HPP_
#define SRC_HTML_DOM_CANVASPATHDRAWINGSTYLES_HPP_

#include <list>

namespace HTML {
namespace DOM {

enum class CanvasLineCap {
	BUTT, ROUND, SQUARE
};

enum class CanvasLineJoin {
	ROUND, BEVEL, MITER
};

/* Mixin */
class CanvasPathDrawingStyles {
	public:
		// line caps/joins
		double lineWidth; // (default 1)
		CanvasLineCap lineCap; // (default "butt")
		CanvasLineJoin lineJoin; // (default "miter")
		double miterLimit; // (default 10)

		// dashed lines
		void setLineDash(std::list<double> segments); // default empty
		std::list<double> getLineDash();
		double lineDashOffset;
};

} /* namespace DOM */
} /* namespace HTML */



#endif /* SRC_HTML_DOM_CANVASPATHDRAWINGSTYLES_HPP_ */
