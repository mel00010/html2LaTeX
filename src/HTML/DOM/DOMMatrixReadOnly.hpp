/*******************************************************************************
 * DOMMatrixReadOnly.hpp
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
#ifndef SRC_HTML_DOM_DOMMATRIXREADONLY_HPP_
#define SRC_HTML_DOM_DOMMATRIXREADONLY_HPP_

//#include "DOMMatrix.hpp"
#include "DOMPoint.hpp"
#include "DOMString.hpp"
#include "Float32Array.hpp"
#include "Float64Array.hpp"
#include "object.hpp"

#include <list>
#include <variant>

namespace HTML {
namespace DOM {

class DOMMatrix;
struct DOMMatrixInit;
struct DOMMatrix2DInit;

class DOMMatrixReadOnly {
	public:
		DOMMatrixReadOnly();
		DOMMatrixReadOnly(std::variant<DOMString, std::list<double>> init);

		static DOMMatrixReadOnly fromMatrix();
		static DOMMatrixReadOnly fromMatrix(DOMMatrixInit other);
		static DOMMatrixReadOnly fromFloat32Array(Float32Array array32);
		static DOMMatrixReadOnly fromFloat64Array(Float64Array array64);

		// These attributes are simple aliases for certain elements of the 4x4 matrix
		const double a;
		const double b;
		const double c;
		const double d;
		const double e;
		const double f;

		const double m11;
		const double m12;
		const double m13;
		const double m14;
		const double m21;
		const double m22;
		const double m23;
		const double m24;
		const double m31;
		const double m32;
		const double m33;
		const double m34;
		const double m41;
		const double m42;
		const double m43;
		const double m44;

		const bool is2D;
		const bool isIdentity;

		// Immutable transform methods
		DOMMatrix translate(double tx = 0,
				double ty = 0,
				double tz = 0);
		DOMMatrix scale(double scaleX = 1,
				double scaleY = 1,
				double scaleZ = 1,
				double originX = 0,
				double originY = 0,
				double originZ = 0);
		DOMMatrix scale3d(double scale = 1,
				double originX = 0,
				double originY = 0,
				double originZ = 0);
		DOMMatrix rotate(double rotX = 0,
				double rotY = 0,
				double rotZ = 0);
		DOMMatrix rotateFromVector(double x = 0,
				double y = 0);
		DOMMatrix rotateAxisAngle(double x = 0,
				double y = 0,
				double z = 0,
				double angle = 0);
		DOMMatrix skewX(double sx = 0);
		DOMMatrix skewY(double sy = 0);
		DOMMatrix multiply();
		DOMMatrix multiply(DOMMatrixInit other);
		DOMMatrix flipX();
		DOMMatrix flipY();
		DOMMatrix inverse();

		DOMPoint transformPoint();
		DOMPoint transformPoint(DOMPointInit point);
		Float32Array toFloat32Array();
		Float64Array toFloat64Array();

		object toJSON();
};

} /* namespace DOM */
} /* namespace HTML */

#endif /* SRC_HTML_DOM_DOMMATRIXREADONLY_HPP_ */
