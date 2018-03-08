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
#ifndef SRC_HTML_WEBAPI_MESSAGEEVENT_HPP_
#define SRC_HTML_WEBAPI_MESSAGEEVENT_HPP_

#include "MessagePort.hpp"

#include <any>
#include <list>
#include <optional>
#include <variant>

#include "../DOM/DOMString.hpp"
#include "../DOM/Event.hpp"
#include "../DOM/USVString.hpp"

namespace HTML {
namespace WebAPI {

typedef std::variant<WindowProxy, MessagePort, ServiceWorker> MessageEventSource;

struct MessageEventInit;

class MessageEvent: public DOM::Event {
	public:
		MessageEvent(DOM::DOMString type);
		MessageEvent(DOM::DOMString type, MessageEventInit eventInitDict);
		const std::any data;
		const DOM::USVString origin;
		const DOM::DOMString lastEventId;
		const std::optional<MessageEventSource> source;
		const FrozenArray<MessagePort> ports;

		void initMessageEvent(DOM::DOMString type,
				std::optional<bool> bubbles = false,
				std::optional<bool> cancelable = false,
				std::optional<std::any> data = std::nullopt,
				std::optional<DOM::USVString> origin = "",
				std::optional<DOM::DOMString> lastEventId = "",
				std::optional<MessageEventSource> source = std::nullopt,
				std::optional<std::list<MessagePort>> ports = { });
};

struct MessageEventInit: public DOM::EventInit {
	public:
		std::any data = std::nullopt;
		DOM::USVString origin = "";
		DOM::DOMString lastEventId = "";
		std::optional<MessageEventSource> source = std::nullopt;
		std::list<MessagePort> ports = { };
};

}
/* namespace WebAPI */
} /* namespace HTML */

#endif /* SRC_HTML_WEBAPI_MESSAGEEVENT_HPP_ */

