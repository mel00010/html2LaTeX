/*******************************************************************************
 * HTMLMarqueeElement.hpp
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
#ifndef SRC_HTML_WEBAPI_HTMLMARQUEEELEMENT_HPP_
#define SRC_HTML_WEBAPI_HTMLMARQUEEELEMENT_HPP_

#include "EventHandler.hpp"
#include "HTMLElement.hpp"

#include "../DOM/DOMString.hpp"

namespace HTML {
namespace WebAPI {

class HTMLMarqueeElement: public HTMLElement {
	public:
		DOM::DOMString behavior;
		DOM::DOMString bgColor;
		DOM::DOMString direction;
		DOM::DOMString height;
		unsigned long hspace;
		long loop;
		unsigned long scrollAmount;
		unsigned long scrollDelay;
		bool trueSpeed;
		unsigned long vspace;
		DOM::DOMString width;

		EventHandler onbounce;
		EventHandler onfinish;
		EventHandler onstart;

		void start();
		void stop();
};

} /* namespace WebAPI */
} /* namespace HTML */

#endif /* SRC_HTML_WEBAPI_HTMLMARQUEEELEMENT_HPP_ */

