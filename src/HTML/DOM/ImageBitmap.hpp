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
#ifndef SRC_HTML_DOM_IMAGEBITMAP_HPP_
#define SRC_HTML_DOM_IMAGEBITMAP_HPP_

#include "Blob.hpp"
#include "CanvasDrawImage.hpp"
#include "ImageData.hpp"

#include <variant>

namespace HTML {
namespace DOM {

class ImageBitmap {
	public:
		const unsigned long width;
		const unsigned long height;
		void close();
};

//typedef std::variant<CanvasImageSource, Blob, ImageData> ImageBitmapSource;
typedef std::variant<Blob, ImageData> ImageBitmapSource;

enum class ImageOrientation {
	NONE, FLIPY
};
enum class PremultiplyAlpha {
	NONE, PREMULTIPLY, DEFAULT
};
enum class ColorSpaceConversion {
	NONE, DEFAULT
};
enum class ResizeQuality {
	PIXELATED, LOW, MEDIUM, HIGH
};

struct ImageBitmapOptions {
	public:
		ImageOrientation imageOrientation = ImageOrientation::NONE;
		PremultiplyAlpha premultiplyAlpha = PremultiplyAlpha::DEFAULT;
		ColorSpaceConversion colorSpaceConversion = ColorSpaceConversion::DEFAULT;
		unsigned long resizeWidth;
		unsigned long resizeHeight;
		ResizeQuality resizeQuality = ResizeQuality::LOW;
};

} /* namespace DOM */
} /* namespace HTML */

#endif /* SRC_HTML_DOM_IMAGEBITMAP_HPP_ */

