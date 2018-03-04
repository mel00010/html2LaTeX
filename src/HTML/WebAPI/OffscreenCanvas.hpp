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
#ifndef SRC_HTML_WEBAPI_OFFSCREENCANVAS_HPP_
#define SRC_HTML_WEBAPI_OFFSCREENCANVAS_HPP_


namespace HTML {
namespace WebAPI {

typedef (OffscreenCanvasRenderingContext2D or
        WebGLRenderingContext) OffscreenRenderingContext;

dictionary ImageEncodeOptions {
  DOM::DOMString type = "image/png";
  unrestricted double quality = 1.0;
};

enum OffscreenRenderingContextId { "2d", "webgl" };

[Constructor([EnforceRange] unsigned long long width, [EnforceRange] unsigned long long height), Exposed=(Window,Worker), Transferable]
class OffscreenCanvas : EventTarget {
   unsigned long long width;
   unsigned long long height;

  OffscreenRenderingContext? getContext(OffscreenRenderingContextId contextId, optional any options = null);
  ImageBitmap transferToImageBitmap();
  Promise<Blob> convertToBlob(optional ImageEncodeOptions options);
};

} /* namespace WebAPI */
} /* namespace HTML */


#endif /* SRC_HTML_WEBAPI_OFFSCREENCANVAS_HPP_ */

