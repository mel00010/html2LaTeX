/*******************************************************************************
 * MessageEvent.hpp
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
#ifndef SRC_HTML_DOM_MESSAGEEVENT_HPP_
#define SRC_HTML_DOM_MESSAGEEVENT_HPP_

#include "DOMString.hpp"
#include "Event.hpp"
#include "FrozenArray.hpp"
#include "MessagePort.hpp"
#include "USVString.hpp"

#include <any>
#include <list>
#include <optional>
#include <variant>

namespace HTML {
namespace DOM {

//typedef std::variant<WindowProxy, MessagePort, ServiceWorker> MessageEventSource;
typedef std::variant<MessagePort> MessageEventSource;


struct MessageEventInit;

class MessageEvent: public Event {
	public:
		MessageEvent(DOMString type);
		MessageEvent(DOMString type, MessageEventInit eventInitDict);
		const std::any data;
		const USVString origin;
		const DOMString lastEventId;
		const std::optional<MessageEventSource> source;
		const FrozenArray<MessagePort> ports;

		void initMessageEvent(DOMString type,
				std::optional<bool> bubbles = false,
				std::optional<bool> cancelable = false,
				std::optional<std::any> data = std::nullopt,
				std::optional<USVString> origin = U"",
				std::optional<DOMString> lastEventId = U"",
				std::optional<MessageEventSource> source = std::nullopt,
				std::optional<std::list<MessagePort>> ports = { });
};

struct MessageEventInit: public EventInit {
	public:
		std::any data = std::nullopt;
		USVString origin = U"";
		DOMString lastEventId = U"";
		std::optional<MessageEventSource> source = std::nullopt;
		std::list<MessagePort> ports = { };
};

}
/* namespace DOM */
} /* namespace HTML */

#endif /* SRC_HTML_DOM_MESSAGEEVENT_HPP_ */

