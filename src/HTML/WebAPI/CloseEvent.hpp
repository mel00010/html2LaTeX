/*******************************************************************************
 * CloseEvent.hpp
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
#ifndef SRC_HTML_WEBAPI_CLOSEEVENT_HPP_
#define SRC_HTML_WEBAPI_CLOSEEVENT_HPP_

#include <optional>

#include "../DOM/DOMString.hpp"
#include "../DOM/Event.hpp"
#include "../DOM/USVString.hpp"

namespace HTML {
namespace WebAPI {

/* Forward Declares */
class CloseEvent;
struct CloseEventInit;

class CloseEvent: public DOM::Event {
	public:
		CloseEvent(DOM::DOMString type, std::optional<CloseEventInit> eventInitDict);
		const bool wasClean;
		const unsigned short code;
		const DOM::USVString reason;
};

struct CloseEventInit: public DOM::EventInit {
	public:
		bool wasClean = false;
		unsigned short code = 0;
		DOM::USVString reason = "";
};

}
/* namespace WebAPI */
} /* namespace HTML */

#endif /* SRC_HTML_WEBAPI_CLOSEEVENT_HPP_ */

