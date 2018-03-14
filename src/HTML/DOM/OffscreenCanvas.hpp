/*******************************************************************************
 * OffscreenCanvas.hpp
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
#ifndef SRC_HTML_DOM_OFFSCREENCANVAS_HPP_
#define SRC_HTML_DOM_OFFSCREENCANVAS_HPP_

#include "DOMString.hpp"
#include "EventTarget.hpp"
#include "ImageBitmap.hpp"
#include "OffscreenCanvasRenderingContext2D.hpp"

#include <any>
#include <future>
#include <optional>
#include <variant>

namespace HTML {
namespace DOM {

typedef std::variant<OffscreenCanvasRenderingContext2D, WebGLRenderingContext> OffscreenRenderingContext;

struct ImageEncodeOptions {
	public:
		DOMString type = "image/png";
		double quality = 1.0;
};

enum OffscreenRenderingContextId {
	TWO_D, WEBGL
};

class OffscreenCanvas: public EventTarget {
	public:
		OffscreenCanvas(unsigned long long width, unsigned long long height);

		unsigned long long width;
		unsigned long long height;

		std::optional<OffscreenRenderingContext> getContext(OffscreenRenderingContextId contextId,
				std::optional<std::any> options = std::nullopt);
		ImageBitmap transferToImageBitmap();
		std::promise<Blob> convertToBlob(std::optional<ImageEncodeOptions> options);
};

}
/* namespace DOM */
} /* namespace HTML */

#endif /* SRC_HTML_DOM_OFFSCREENCANVAS_HPP_ */

