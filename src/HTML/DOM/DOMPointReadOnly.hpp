/*******************************************************************************
 * DOMPointReadOnly.hpp
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
#ifndef SRC_HTML_DOM_DOMPOINTREADONLY_HPP_
#define SRC_HTML_DOM_DOMPOINTREADONLY_HPP_

//#include "DOMMatrix.hpp"
//#include "DOMPoint.hpp"
#include "object.hpp"

namespace HTML {
namespace DOM {

class DOMPoint;
struct DOMPointInit;
struct DOMMatrixInit;

class DOMPointReadOnly {
	public:
		DOMPointReadOnly(double x = 0, double y = 0, double z = 0, double w = 1);

		static DOMPointReadOnly fromPoint();
		static DOMPointReadOnly fromPoint(DOMPointInit other);

		const double x;
		const double y;
		const double z;
		const double w;

		DOMPoint matrixTransform();
		DOMPoint matrixTransform(DOMMatrixInit matrix);

		object toJSON();
};

} /* namespace DOM */
} /* namespace HTML */

#endif /* SRC_HTML_DOM_DOMPOINTREADONLY_HPP_ */
