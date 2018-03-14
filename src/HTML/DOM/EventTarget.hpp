/*******************************************************************************
 * EventTarget.hpp
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
#ifndef SRC_HTML_DOM_EVENTTARGET_HPP_
#define SRC_HTML_DOM_EVENTTARGET_HPP_

#include "DOMString.hpp"
//#include "Event.hpp"

#include <optional>
#include <variant>

namespace HTML {
namespace DOM {

class Event;

class EventListener;
struct EventListenerOptions;
struct AddEventListenerOptions;
class TextTrackCueList;

class EventTarget {
	public:
		void addEventListener(DOMString type, std::optional<EventListener> callback, std::optional<std::variant<AddEventListenerOptions, bool>> options);
		void removeEventListener(DOMString type, std::optional<EventListener> callback, std::optional<std::variant<EventListenerOptions, bool>> options);
		bool dispatchEvent(Event event);
};

class EventListener {
	public:
		void handleEvent(Event event);
};

struct EventListenerOptions {
	public:
		bool capture = false;
};

struct AddEventListenerOptions : public EventListenerOptions {
	bool passive = false;
	bool once = false;
};

} /* namespace DOM */
} /* namespace HTML */

#endif /* SRC_HTML_DOM_EVENTTARGET_HPP_ */
