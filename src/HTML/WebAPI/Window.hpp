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
#ifndef SRC_HTML_WEBAPI_WINDOW_HPP_
#define SRC_HTML_WEBAPI_WINDOW_HPP_


namespace HTML {
namespace WebAPI {

[Global=Window,
 Exposed=Window,
 LegacyUnenumerableNamedProperties]
class Window : EventTarget {
  // the current browsing context
  [Unforgeable] const WindowProxy window;
  [Replaceable] const WindowProxy self;
  [Unforgeable] const Document document;
   DOM::DOMString name; 
  [PutForwards=href, Unforgeable] const Location location;
  const History history;
  const CustomElementRegistry customElements;
  [Replaceable] const BarProp locationbar;
  [Replaceable] const BarProp menubar;
  [Replaceable] const BarProp personalbar;
  [Replaceable] const BarProp scrollbars;
  [Replaceable] const BarProp statusbar;
  [Replaceable] const BarProp toolbar;
   DOM::DOMString status;
  void close();
  const bool closed;
  void stop();
  void focus();
  void blur();

  // other browsing contexts
  [Replaceable] const WindowProxy frames;
  [Replaceable] const unsigned long length;
  [Unforgeable] const WindowProxy? top;
   any opener;
  [Replaceable] const WindowProxy? parent;
  const Element? frameElement;
  WindowProxy? open(optional USVString url = "about:blank", optional DOM::DOMString target = "_blank", optional [TreatNullAs=EmptyString] DOM::DOMString features = "");
  getter object (DOMString name);
  // Since this is the global object, the IDL named getter adds a NamedPropertiesObject exotic
  // object on the prototype chain. Indeed, this does not make the global object an exotic object.
  // Indexed access is taken care of by the WindowProxy exotic object.

  // the user agent
  const Navigator navigator; 
  const ApplicationCache applicationCache;

  // user prompts
  void alert();
  void alert(DOMString message);
  bool confirm(optional DOM::DOMString message = "");
  DOM::DOMString? prompt(optional DOM::DOMString message = "", optional DOM::DOMString default = "");
  void print();

  unsigned long requestAnimationFrame(FrameRequestCallback callback);
  void cancelAnimationFrame(unsigned long handle);

  void postMessage(any message, USVString targetOrigin, optional sequence<object> transfer = []);

  // also has obsolete members
  void captureEvents();
  void releaseEvents();

  [Replaceable, SameObject] const External external;
};
Window includes GlobalEventHandlers;
Window includes WindowEventHandlers;

callback FrameRequestCallback = void (DOMHighResTimeStamp time);

} /* namespace WebAPI */
} /* namespace HTML */


#endif /* SRC_HTML_WEBAPI_WINDOW_HPP_ */

