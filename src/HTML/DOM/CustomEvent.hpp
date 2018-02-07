/*******************************************************************************
 * CustomEvent.hpp
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
#ifndef SRC_HTML_DOM_CUSTOMEVENT_HPP_
#define SRC_HTML_DOM_CUSTOMEVENT_HPP_

#include "DOMString.hpp"
#include "Event.hpp"

#include <any>

namespace HTML {
namespace DOM {

class CustomEvent : public Event {
  const std::any detail;

  void initCustomEvent(DOMString type, bool bubbles = false, bool cancelable = false, std::any detail = nullptr);
};

struct CustomEventInit : public EventInit {
	public:
		std::any detail = nullptr;
};

} /* namespace DOM */
} /* namespace HTML */



#endif /* SRC_HTML_DOM_CUSTOMEVENT_HPP_ */
