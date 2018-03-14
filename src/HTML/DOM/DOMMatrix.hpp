/*******************************************************************************
 * DOMMatrix.hpp
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
#ifndef SRC_HTML_DOM_DOMMATRIX_HPP_
#define SRC_HTML_DOM_DOMMATRIX_HPP_

#include "DOMMatrixReadOnly.hpp"
#include "DOMString.hpp"
#include "Float32Array.hpp"
#include "Float64Array.hpp"

#include <list>
#include <variant>

namespace HTML {
namespace DOM {

//class DOMMatrixReadOnly;

struct DOMMatrix2DInit {
	public:
		double a;
		double b;
		double c;
		double d;
		double e;
		double f;
		double m11;
		double m12;
		double m21;
		double m22;
		double m41;
		double m42;
};

struct DOMMatrixInit: public DOMMatrix2DInit {
	public:
		double m13 = 0;
		double m14 = 0;
		double m23 = 0;
		double m24 = 0;
		double m31 = 0;
		double m32 = 0;
		double m33 = 1;
		double m34 = 0;
		double m43 = 0;
		double m44 = 1;
		bool is2D;
};

class DOMMatrix: public DOMMatrixReadOnly {
	public:
		DOMMatrix();
		DOMMatrix(std::variant<DOMString, std::list<double>> init);

		static DOMMatrix fromMatrix();

		static DOMMatrix fromMatrix(DOMMatrixInit other);
		static DOMMatrix fromFloat32Array(Float32Array array32);
		static DOMMatrix fromFloat64Array(Float64Array array64);

		// Mutable transform methods
		DOMMatrix multiplySelf();
		DOMMatrix multiplySelf(DOMMatrixInit other);

		DOMMatrix preMultiplySelf();
		DOMMatrix preMultiplySelf(DOMMatrixInit other);
		DOMMatrix translateSelf(double tx = 0, double ty = 0, double tz = 0);

		DOMMatrix scaleSelf(double scaleX = 1, double scaleY = 1, double scaleZ = 1,
				double originX = 0, double originY = 0, double originZ = 0);

		DOMMatrix scale3dSelf(double scale = 1, double originX = 0, double originY = 0, double originZ = 0);
		DOMMatrix rotateSelf(double rotX = 0, double rotY = 0, double rotZ = 0);
		DOMMatrix rotateFromVectorSelf(double x = 0, double y = 0);
		DOMMatrix rotateAxisAngleSelf(double x = 0, double y = 0, double z = 0, double angle = 0);
		DOMMatrix skewXSelf(double sx = 0);
		DOMMatrix skewYSelf(double sy = 0);
		DOMMatrix invertSelf();

		DOMMatrix setMatrixValue(DOMString transformList);
};

} /* namespace DOM */
} /* namespace HTML */

#endif /* SRC_HTML_DOM_DOMMATRIX_HPP_ */
