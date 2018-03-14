/*******************************************************************************
 * CanvasDrawPath.hpp
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
#ifndef SRC_HTML_DOM_CANVASDRAWPATH_HPP_
#define SRC_HTML_DOM_CANVASDRAWPATH_HPP_

#include "Path2D.hpp"

namespace HTML {
namespace DOM {

enum class CanvasFillRule {
	NON_ZERO, EVEN_ODD
};

/* Mixin */
class CanvasDrawPath {
	public:
		// path API (see also CanvasPath)
		void beginPath();
		void fill(CanvasFillRule fillRule = CanvasFillRule::NON_ZERO);
		void fill(Path2D path, CanvasFillRule fillRule = CanvasFillRule::NON_ZERO);
		void stroke();
		void stroke(Path2D path);
		void clip(CanvasFillRule fillRule = CanvasFillRule::NON_ZERO);
		void clip(Path2D path, CanvasFillRule fillRule = CanvasFillRule::NON_ZERO);
		void resetClip();
		bool isPointInPath(double x, double y, CanvasFillRule fillRule = CanvasFillRule::NON_ZERO);
		bool isPointInPath(Path2D path, double x, double y, CanvasFillRule fillRule = CanvasFillRule::NON_ZERO);
		bool isPointInStroke(double x, double y);
		bool isPointInStroke(Path2D path, double x, double y);
};

} /* namespace DOM */
} /* namespace HTML */

#endif /* SRC_HTML_DOM_CANVASDRAWPATH_HPP_ */
