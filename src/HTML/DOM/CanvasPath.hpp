/*******************************************************************************
 * CanvasPath.hpp
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
#ifndef SRC_HTML_DOM_CANVASPATH_HPP_
#define SRC_HTML_DOM_CANVASPATH_HPP_

namespace HTML {
namespace DOM {

/* Mixin */
class CanvasPath {
	public:
		// shared path API methods
		void closePath();
		void moveTo(double x, double y);
		void lineTo(double x, double y);
		void quadraticCurveTo(double cpx, double cpy, double x, double y);
		void bezierCurveTo(double cp1x, double cp1y, double cp2x, double cp2y, double x, double y);
		void arcTo(double x1, double y1, double x2, double y2, double radius);
		void rect(double x, double y, double w, double h);
		void arc(double x, double y, double radius, double startAngle, double endAngle, bool anticlockwise = false);
		void ellipse(double x, double y, double radiusX, double radiusY, double rotation, double startAngle, double endAngle, bool anticlockwise = false);
};

} /* namespace DOM */
} /* namespace HTML */

#endif /* SRC_HTML_DOM_CANVASPATH_HPP_ */
