/*******************************************************************************
 * WindowOrWorkerGlobalScope.hpp
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
#ifndef SRC_HTML_WEBAPI_WINDOWORWORKERGLOBALSCOPE_HPP_
#define SRC_HTML_WEBAPI_WINDOWORWORKERGLOBALSCOPE_HPP_

#include "ImageBitmap.hpp"

#include <any>
#include <functional>
#include <future>
#include <list>
#include <variant>

#include "../DOM/ByteString.hpp"
#include "../DOM/DOMString.hpp"
#include "../DOM/USVString.hpp"

namespace HTML {
namespace WebAPI {

typedef std::variant<DOM::DOMString, std::function> TimerHandler;

/* Mixin */
class WindowOrWorkerGlobalScope {
	public:
		const DOM::USVString origin;

		// base64 utility methods
		DOM::DOMString btoa(DOM::DOMString data);
		DOM::ByteString atob(DOM::DOMString data);

		// timers
		long setTimeout(TimerHandler handler, long timeout = 0, std::list<std::any> arguments = { });
		void clearTimeout(long handle = 0);
		long setInterval(TimerHandler handler, long timeout = 0, std::list<std::any> arguments = { });
		void clearInterval(long handle = 0);

		// ImageBitmap
		std::promise<ImageBitmap> createImageBitmap(ImageBitmapSource image);
		std::promise<ImageBitmap> createImageBitmap(ImageBitmapSource image, ImageBitmapOptions options);

		std::promise<ImageBitmap> createImageBitmap(ImageBitmapSource image, long sx, long sy, long sw, long sh);
		std::promise<ImageBitmap> createImageBitmap(ImageBitmapSource image, long sx, long sy, long sw, long sh, ImageBitmapOptions options);
};

} /* namespace WebAPI */
} /* namespace HTML */

#endif /* SRC_HTML_WEBAPI_WINDOWORWORKERGLOBALSCOPE_HPP_ */

