/*******************************************************************************
 * PromiseRejectionEvent.hpp
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
#ifndef SRC_HTML_DOM_PROMISEREJECTIONEVENT_HPP_
#define SRC_HTML_DOM_PROMISEREJECTIONEVENT_HPP_

#include "DOMString.hpp"
#include "Event.hpp"

#include <any>
#include <future>

namespace HTML {
namespace DOM {

struct PromiseRejectionEventInit;

class PromiseRejectionEvent: public Event {
	public:
		PromiseRejectionEvent(DOMString type, PromiseRejectionEventInit eventInitDict);
		const std::promise<std::any> promise;
		const std::any reason;
};

struct PromiseRejectionEventInit: public EventInit {
	public:
		std::promise<std::any> promise;
		std::any reason;
};

} /* namespace DOM */
} /* namespace HTML */

#endif /* SRC_HTML_DOM_PROMISEREJECTIONEVENT_HPP_ */

