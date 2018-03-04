/*******************************************************************************
 * HTMLSelectElement.hpp
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
#ifndef SRC_HTML_WEBAPI_HTMLSELECTELEMENT_HPP_
#define SRC_HTML_WEBAPI_HTMLSELECTELEMENT_HPP_


namespace HTML {
namespace WebAPI {

[Exposed=Window,
 HTMLConstructor]
class HTMLSelectElement : HTMLElement {
    DOM::DOMString autocomplete;
    bool autofocus;
    bool disabled;
  const HTMLFormElement? form;
    bool multiple;
    DOM::DOMString name;
    bool required;
    unsigned long size;

  const DOM::DOMString type;

  [SameObject] const HTMLOptionsCollection options;
    unsigned long length;
  getter Element? item(unsigned long index);
  HTMLOptionElement? namedItem(DOMString name);
   void add((HTMLOptionElement or HTMLOptGroupElement) element, optional (HTMLElement or long)? before = null);
   void remove(); // ChildNode overload
   void remove(long index);
   setter void (unsigned long index, HTMLOptionElement? option);

  [SameObject] const HTMLCollection selectedOptions;
   long selectedIndex;
   DOM::DOMString value;

  const bool willValidate;
  const ValidityState validity;
  const DOM::DOMString validationMessage;
  bool checkValidity();
  bool reportValidity();
  void setCustomValidity(DOMString error);

  const NodeList labels;
};

} /* namespace WebAPI */
} /* namespace HTML */


#endif /* SRC_HTML_WEBAPI_HTMLSELECTELEMENT_HPP_ */

