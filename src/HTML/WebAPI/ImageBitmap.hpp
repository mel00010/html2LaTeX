/*******************************************************************************
 * ImageBitmap.hpp
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
#ifndef SRC_HTML_WEBAPI_IMAGEBITMAP_HPP_
#define SRC_HTML_WEBAPI_IMAGEBITMAP_HPP_


namespace HTML {
namespace WebAPI {

[Exposed=(Window,Worker), Serializable, Transferable]
class ImageBitmap {
  const unsigned long width;
  const unsigned long height;
  void close();
};

typedef (CanvasImageSource or
         Blob or
         ImageData) ImageBitmapSource;

enum ImageOrientation { "none", "flipY" };
enum PremultiplyAlpha { "none", "premultiply", "default" };
enum ColorSpaceConversion { "none", "default" };
enum ResizeQuality { "pixelated", "low", "medium", "high" };

dictionary ImageBitmapOptions {
  ImageOrientation imageOrientation = "none";
  PremultiplyAlpha premultiplyAlpha = "default";
  ColorSpaceConversion colorSpaceConversion = "default";
  [EnforceRange] unsigned long resizeWidth;
  [EnforceRange] unsigned long resizeHeight;
  ResizeQuality resizeQuality = "low";
};

} /* namespace WebAPI */
} /* namespace HTML */


#endif /* SRC_HTML_WEBAPI_IMAGEBITMAP_HPP_ */

