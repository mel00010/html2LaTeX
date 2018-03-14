/*******************************************************************************
 * WorkerGlobalScope.hpp
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
#ifndef SRC_HTML_WEBAPI_WORKERGLOBALSCOPE_HPP_
#define SRC_HTML_WEBAPI_WORKERGLOBALSCOPE_HPP_

#include "EventHandler.hpp"
#include "WindowOrWorkerGlobalScope.hpp"
#include "WorkerLocation.hpp"
#include "WorkerNavigator.hpp"

#include <list>

#include "../DOM/EventTarget.hpp"
#include "../DOM/USVString.hpp"

namespace HTML {
namespace WebAPI {

class WorkerGlobalScope: public DOM::EventTarget, public WindowOrWorkerGlobalScope {
	public:WindowOrWorkerGlobalScope
		const WorkerGlobalScope self;
		const WorkerLocation location;
		const WorkerNavigator navigator;
		void importScripts(std::list<DOM::USVString> urls);

		OnErrorEventHandler onerror;
		EventHandler onlanguagechange;
		EventHandler onoffline;
		EventHandler ononline;
		EventHandler onrejectionhandled;
		EventHandler onunhandledrejection;
};

} /* namespace WebAPI */
} /* namespace HTML */

#endif /* SRC_HTML_WEBAPI_WORKERGLOBALSCOPE_HPP_ */
