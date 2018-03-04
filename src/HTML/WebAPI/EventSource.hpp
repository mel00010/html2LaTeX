/*******************************************************************************
 * EventSource.hpp
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
#ifndef SRC_HTML_WEBAPI_EVENTSOURCE_HPP_
#define SRC_HTML_WEBAPI_EVENTSOURCE_HPP_

#include "EventHandler.hpp"

namespace HTML {
namespace WebAPI {

class EventSource: public EventTarget {
	public:
		EventSource(USVString url);

		EventSource(USVString url, EventSourceInit eventSourceInitDict);
		const USVString url;
		const bool withCredentials;

		// ready state
		const unsigned short CONNECTING = 0;
		const unsigned short OPEN = 1;
		const unsigned short CLOSED = 2;
		const unsigned short readyState;

		// networking
		EventHandler onopen;
		EventHandler onmessage;
		EventHandler onerror;
		void close();
};

struct EventSourceInit {
	public:
		bool withCredentials = false;
};

} /* namespace WebAPI */
} /* namespace HTML */

#endif /* SRC_HTML_WEBAPI_EVENTSOURCE_HPP_ */

