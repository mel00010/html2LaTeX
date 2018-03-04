/*******************************************************************************
 * HTMLImageElement.hpp
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
#ifndef SRC_HTML_WEBAPI_HTMLIMAGEELEMENT_HPP_
#define SRC_HTML_WEBAPI_HTMLIMAGEELEMENT_HPP_


namespace HTML {
namespace WebAPI {

[Exposed=Window,
 HTMLConstructor,
 NamedConstructor=Image(optional unsigned long width, optional unsigned long height)]
class HTMLImageElement : HTMLElement {
    DOM::DOMString alt;
    USVString src;
    USVString srcset;
    DOM::DOMString sizes;
    DOM::DOMString? crossOrigin;
    DOM::DOMString useMap;
    bool isMap;
    unsigned long width;
    unsigned long height;
  const unsigned long naturalWidth;
  const unsigned long naturalHeight;
  const bool complete;
  const USVString currentSrc;
    DOM::DOMString referrerPolicy;
    DOM::DOMString decoding;

  Promise<void> decode();

  // also has obsolete members
    DOM::DOMString name;
    USVString lowsrc;
    DOM::DOMString align;
    unsigned long hspace;
    unsigned long vspace;
    USVString longDesc;

    [TreatNullAs=EmptyString] DOM::DOMString border;
};

} /* namespace WebAPI */
} /* namespace HTML */


#endif /* SRC_HTML_WEBAPI_HTMLIMAGEELEMENT_HPP_ */

