/*******************************************************************************
 * GlobalEventHandlers.hpp
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
#ifndef SRC_HTML_DOM_GLOBALEVENTHANDLERS_HPP_
#define SRC_HTML_DOM_GLOBALEVENTHANDLERS_HPP_

#include "EventHandler.hpp"

namespace HTML {
namespace DOM {

/* Mixin */
class GlobalEventHandlers {
	public:
		EventHandler onabort;
		EventHandler onauxclick;
		EventHandler onblur;
		EventHandler oncancel;
		EventHandler oncanplay;
		EventHandler oncanplaythrough;
		EventHandler onchange;
		EventHandler onclick;
		EventHandler onclose;
		EventHandler oncontextmenu;
		EventHandler oncuechange;
		EventHandler ondblclick;
		EventHandler ondrag;
		EventHandler ondragend;
		EventHandler ondragenter;
		EventHandler ondragexit;
		EventHandler ondragleave;
		EventHandler ondragover;
		EventHandler ondragstart;
		EventHandler ondrop;
		EventHandler ondurationchange;
		EventHandler onemptied;
		EventHandler onended;
		OnErrorEventHandler onerror;
		EventHandler onfocus;
		EventHandler oninput;
		EventHandler oninvalid;
		EventHandler onkeydown;
		EventHandler onkeypress;
		EventHandler onkeyup;
		EventHandler onload;
		EventHandler onloadeddata;
		EventHandler onloadedmetadata;
		EventHandler onloadend;
		EventHandler onloadstart;
		EventHandler onmousedown;
		EventHandler onmouseenter;
		EventHandler onmouseleave;
		EventHandler onmousemove;
		EventHandler onmouseout;
		EventHandler onmouseover;
		EventHandler onmouseup;
		EventHandler onwheel;
		EventHandler onpause;
		EventHandler onplay;
		EventHandler onplaying;
		EventHandler onprogress;
		EventHandler onratechange;
		EventHandler onreset;
		EventHandler onresize;
		EventHandler onscroll;
		EventHandler onsecuritypolicyviolation;
		EventHandler onseeked;
		EventHandler onseeking;
		EventHandler onselect;
		EventHandler onstalled;
		EventHandler onsubmit;
		EventHandler onsuspend;
		EventHandler ontimeupdate;
		EventHandler ontoggle;
		EventHandler onvolumechange;
		EventHandler onwaiting;
};

} /* namespace DOM */
} /* namespace HTML */

#endif /* SRC_HTML_DOM_GLOBALEVENTHANDLERS_HPP_ */

