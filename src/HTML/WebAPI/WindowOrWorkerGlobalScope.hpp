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


namespace HTML {
namespace WebAPI {

typedef (DOMString or Function) TimerHandler;

/* Mixin */
class WindowOrWorkerGlobalScope {
  [Replaceable] const USVString origin;

  // base64 utility methods
  DOM::DOMString btoa(DOMString data);
  ByteString atob(DOMString data);

  // timers
  long setTimeout(TimerHandler handler, optional long timeout = 0, any... arguments);
  void clearTimeout(optional long handle = 0);
  long setInterval(TimerHandler handler, optional long timeout = 0, any... arguments);
  void clearInterval(optional long handle = 0);

  // ImageBitmap
  Promise<ImageBitmap> createImageBitmap(ImageBitmapSource image, optional ImageBitmapOptions options);
  Promise<ImageBitmap> createImageBitmap(ImageBitmapSource image, long sx, long sy, long sw, long sh, optional ImageBitmapOptions options);
};
Window includes WindowOrWorkerGlobalScope;
WorkerGlobalScope includes WindowOrWorkerGlobalScope;

} /* namespace WebAPI */
} /* namespace HTML */


#endif /* SRC_HTML_WEBAPI_WINDOWORWORKERGLOBALSCOPE_HPP_ */

