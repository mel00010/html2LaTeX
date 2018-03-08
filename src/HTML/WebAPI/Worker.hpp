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

#include "AbstractWorker.hpp"
#include "EventHandler.hpp"

#include <any>
#include <list>

#include "../DOM/DOMString.hpp"
#include "../DOM/USVString.hpp"

namespace HTML {
namespace WebAPI {

struct WorkerOptions;

enum class WorkerType {
	CLASSIC, MODULE
};

class Worker: public DOM::EventTarget, public AbstractWorker {
	public:
		Worker(DOM::USVString scriptURL);
		Worker(DOM::USVString scriptURL, WorkerOptions options);

		void terminate();

		void postMessage(std::any message, std::list<std::any> transfer = { });
		EventHandler onmessage;
		EventHandler onmessageerror;
};

struct WorkerOptions {
		WorkerType type = WorkerType::CLASSIC;
		RequestCredentials credentials = RequestCredentials::OMIT; // credentials is only used if type is "module"
		DOM::DOMString name = "";
};

} /* namespace WebAPI */
} /* namespace HTML */

#endif /* SRC_HTML_WEBAPI_WORKER_HPP_ */

