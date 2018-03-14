/*******************************************************************************
 * ApplicationCache.hpp
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
#ifndef SRC_HTML_DOM_APPLICATIONCACHE_HPP_
#define SRC_HTML_DOM_APPLICATIONCACHE_HPP_

#include "EventHandler.hpp"
#include "EventTarget.hpp"

namespace HTML {
namespace DOM {

class ApplicationCache: public EventTarget {
	public:
		// update status
		const unsigned short UNCACHED = 0;
		const unsigned short IDLE = 1;
		const unsigned short CHECKING = 2;
		const unsigned short DOWNLOADING = 3;
		const unsigned short UPDATEREADY = 4;
		const unsigned short OBSOLETE = 5;
		const unsigned short status;

		// updates
		void update();
		void abort();
		void swapCache();

		// events

		EventHandler onchecking;

		EventHandler onerror;

		EventHandler onnoupdate;

		EventHandler ondownloading;

		EventHandler onprogress;

		EventHandler onupdateready;

		EventHandler oncached;

		EventHandler onobsolete;
};

} /* namespace DOM */
} /* namespace HTML */

#endif /* SRC_HTML_DOM_APPLICATIONCACHE_HPP_ */

