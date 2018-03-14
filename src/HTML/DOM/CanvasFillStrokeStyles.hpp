/*******************************************************************************
 * CanvasFillStrokeStyles.hpp
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
#ifndef SRC_HTML_DOM_CANVASFILLSTROKESTYLES_HPP_
#define SRC_HTML_DOM_CANVASFILLSTROKESTYLES_HPP_

#include "CanvasDrawImage.hpp"
#include "CanvasGradient.hpp"
#include "CanvasPattern.hpp"
#include "DOMString.hpp"

#include <optional>
#include <variant>

namespace HTML {
namespace DOM {

/* Mixin */
class CanvasFillStrokeStyles {
	public:
		// colors and styles (see also the CanvasPathDrawingStyles and CanvasTextDrawingStyles interfaces)
		std::variant<DOMString, CanvasGradient, CanvasPattern> strokeStyle; // (default black)
		std::variant<DOMString, CanvasGradient, CanvasPattern> fillStyle; // (default black)
		CanvasGradient createLinearGradient(double x0, double y0, double x1, double y1);
		CanvasGradient createRadialGradient(double x0, double y0, double r0, double x1, double y1, double r1);
		std::optional<CanvasPattern> createPattern(CanvasImageSource image, DOMString repetition);

};

} /* namespace DOM */
} /* namespace HTML */

#endif /* SRC_HTML_DOM_CANVASFILLSTROKESTYLES_HPP_ */
