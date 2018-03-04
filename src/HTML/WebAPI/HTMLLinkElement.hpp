/*******************************************************************************
 * HTMLLinkElement.hpp
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
#ifndef SRC_HTML_WEBAPI_HTMLLINKELEMENT_HPP_
#define SRC_HTML_WEBAPI_HTMLLINKELEMENT_HPP_


namespace HTML {
namespace WebAPI {

[Exposed=Window,
 HTMLConstructor]
class HTMLLinkElement : HTMLElement {
    USVString href;
    DOM::DOMString? crossOrigin;
    DOM::DOMString rel;
    DOM::DOMString as; // (default "")
  [SameObject, PutForwards=value] const DOMTokenList relList;
    DOM::DOMString media;
    DOM::DOMString integrity;
    DOM::DOMString hreflang;
    DOM::DOMString type;
  [SameObject, PutForwards=value] const DOMTokenList sizes;
    DOM::DOMString referrerPolicy;

  // also has obsolete members
    DOM::DOMString charset;
    DOM::DOMString rev;
    DOM::DOMString target;
};
HTMLLinkElement includes LinkStyle;

} /* namespace WebAPI */
} /* namespace HTML */


#endif /* SRC_HTML_WEBAPI_HTMLLINKELEMENT_HPP_ */

