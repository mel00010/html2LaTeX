/*******************************************************************************
 * Worker.hpp
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
#ifndef SRC_HTML_WEBAPI_WORKER_HPP_
#define SRC_HTML_WEBAPI_WORKER_HPP_


namespace HTML {
namespace WebAPI {

[Constructor(USVString scriptURL, optional WorkerOptions options), Exposed=(Window,Worker)]
class Worker : EventTarget {
  void terminate();

  void postMessage(any message, optional sequence<object> transfer = []);
   EventHandler onmessage;
   EventHandler onmessageerror;
};

dictionary WorkerOptions {
  WorkerType type = "classic";
  RequestCredentials credentials = "omit"; // credentials is only used if type is "module"
  DOM::DOMString name = "";
};

enum WorkerType { "classic", "module" };

Worker includes AbstractWorker;

} /* namespace WebAPI */
} /* namespace HTML */


#endif /* SRC_HTML_WEBAPI_WORKER_HPP_ */

