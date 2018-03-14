/*******************************************************************************
 * CanvasDrawImage.hpp
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
#ifndef SRC_HTML_DOM_CANVASDRAWIMAGE_HPP_
#define SRC_HTML_DOM_CANVASDRAWIMAGE_HPP_

#include "HTMLCanvasElement.hpp"
#include "HTMLImageElement.hpp"
#include "HTMLVideoElement.hpp"
#include "ImageBitmap.hpp"
#include "OffscreenCanvas.hpp"

#include <variant>

namespace HTML {
namespace DOM {

typedef std::variant<HTMLImageElement, SVGImageElement> HTMLOrSVGImageElement;

typedef std::variant<HTMLOrSVGImageElement, HTMLVideoElement, HTMLCanvasElement, ImageBitmap, OffscreenCanvas> CanvasImageSource;

/* Mixin */
class CanvasDrawImage {
	public:
		// drawing images
		void drawImage(CanvasImageSource image, double dx, double dy);
		void drawImage(CanvasImageSource image, double dx, double dy, double dw, double dh);
		void drawImage(CanvasImageSource image, double sx, double sy, double sw, double sh, double dx, double dy, double dw, double dh);
};

} /* namespace DOM */
} /* namespace HTML */

#endif /* SRC_HTML_DOM_CANVASDRAWIMAGE_HPP_ */
