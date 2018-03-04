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


namespace HTML {
namespace WebAPI {

[Constructor(DOMString type, optional MessageEventInit eventInitDict), Exposed=(Window,Worker,AudioWorklet)]
class MessageEvent : Event {
  const any data;
  const USVString origin;
  const DOM::DOMString lastEventId;
  const MessageEventSource? source;
  const FrozenArray<MessagePort> ports;

  void initMessageEvent(DOMString type, optional bool bubbles = false, optional bool cancelable = false, optional any data = null, optional USVString origin = "", optional DOM::DOMString lastEventId = "", optional MessageEventSource? source = null, optional sequence<MessagePort> ports = []);
};

dictionary MessageEventInit : EventInit {
  any data = null;
  USVString origin = "";
  DOM::DOMString lastEventId = "";
  MessageEventSource? source = null;
  sequence<MessagePort> ports = [];
};

typedef (WindowProxy or MessagePort or ServiceWorker) MessageEventSource;

} /* namespace WebAPI */
} /* namespace HTML */


#endif /* SRC_HTML_WEBAPI_MESSAGEEVENT_HPP_ */

