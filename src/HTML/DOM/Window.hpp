/*******************************************************************************
 * Window.hpp
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
#ifndef SRC_HTML_DOM_WINDOW_HPP_
#define SRC_HTML_DOM_WINDOW_HPP_

#include "ApplicationCache.hpp"
#include "BarProp.hpp"
#include "CustomElementRegistry.hpp"
#include "Document.hpp"
#include "DOMHighResTimeStamp.hpp"
#include "DOMString.hpp"
#include "Element.hpp"
#include "External.hpp"
#include "History.hpp"
#include "Location.hpp"
#include "Navigator.hpp"
#include "USVString.hpp"
#include "WindowEventHandlers.hpp"
#include "WindowLocalStorage.hpp"
#include "WindowOrWorkerGlobalScope.hpp"
#include "WindowProxy.hpp"
#include "WindowSessionStorage.hpp"

#include <any>
#include <list>
#include <optional>

namespace HTML {
namespace DOM {

class Element;

using FrameRequestCallback = void (*)(DOMHighResTimeStamp time);

class Window: public EventTarget, public GlobalEventHandlers, public WindowEventHandlers, public WindowLocalStorage, public WindowSessionStorage, public WindowOrWorkerGlobalScope {
	public:
		// the current browsing context
		const WindowProxy window;
		const WindowProxy self;
		const Document document;
		DOMString name;
		const Location location;
		const History history;
		const CustomElementRegistry customElements;
		const BarProp locationbar;
		const BarProp menubar;
		const BarProp personalbar;
		const BarProp scrollbars;
		const BarProp statusbar;
		const BarProp toolbar;
		DOMString status;
		void close();
		const bool closed;
		void stop();
		void focus();
		void blur();

		// other browsing contexts
		const WindowProxy frames;
		const unsigned long length;
		const std::optional<WindowProxy> top;
		std::any opener;
		const std::optional<WindowProxy> parent;
		const std::optional<Element> frameElement;
		std::optional<WindowProxy> open(USVString url = U"about:blank", DOMString target = U"_blank", DOMString features = U"");
		Window getObject(DOMString name);
		// Since this is the global object, the IDL named getter adds a NamedPropertiesObject exotic
		// object on the prototype chain. Indeed, this does not make the global object an exotic object.
		// Indexed access is taken care of by the WindowProxy exotic object.

		// the user agent
		const Navigator navigator;
		const ApplicationCache applicationCache;

		// user prompts
		void alert();
		void alert(DOMString message);
		bool confirm(DOMString message = U"");
		std::optional<DOMString> prompt(DOMString message = U"", DOMString _default = U"");
		void print();

		unsigned long requestAnimationFrame(FrameRequestCallback callback);
		void cancelAnimationFrame(unsigned long handle);

		void postMessage(std::any message, USVString targetOrigin, std::list<std::any> transfer = { });

		// also has obsolete members
		void captureEvents();
		void releaseEvents();

	protected:
		const External external;
};

} /* namespace DOM */
} /* namespace HTML */

#endif /* SRC_HTML_DOM_WINDOW_HPP_ */
