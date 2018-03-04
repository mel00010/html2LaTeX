/*******************************************************************************
 * HTMLInputElement.hpp
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
#ifndef SRC_HTML_WEBAPI_HTMLINPUTELEMENT_HPP_
#define SRC_HTML_WEBAPI_HTMLINPUTELEMENT_HPP_


namespace HTML {
namespace WebAPI {

[Exposed=Window,
 HTMLConstructor]
class HTMLInputElement : HTMLElement {
    DOM::DOMString accept;
    DOM::DOMString alt;
    DOM::DOMString autocomplete;
    bool autofocus;
    bool defaultChecked;
   bool checked;
    DOM::DOMString dirName;
    bool disabled;
  const HTMLFormElement? form;
   FileList? files;
    USVString formAction;
    DOM::DOMString formEnctype;
    DOM::DOMString formMethod;
    bool formNoValidate;
    DOM::DOMString formTarget;
    unsigned long height;
   bool indeterminate;
  const HTMLElement? list;
    DOM::DOMString max;
    long maxLength;
    DOM::DOMString min;
    long minLength;
    bool multiple;
    DOM::DOMString name;
    DOM::DOMString pattern;
    DOM::DOMString placeholder;
    bool readOnly;
    bool required;
    unsigned long size;
    USVString src;
    DOM::DOMString step;
    DOM::DOMString type;
    DOM::DOMString defaultValue;
    [TreatNullAs=EmptyString] DOM::DOMString value;
   object? valueAsDate;
   unrestricted double valueAsNumber;
    unsigned long width;

  void stepUp(optional long n = 1);
  void stepDown(optional long n = 1);

  const bool willValidate;
  const ValidityState validity;
  const DOM::DOMString validationMessage;
  bool checkValidity();
  bool reportValidity();
  void setCustomValidity(DOMString error);

  const NodeList? labels;

  void select();
   unsigned long? selectionStart;
   unsigned long? selectionEnd;
   DOM::DOMString? selectionDirection;
  void setRangeText(DOMString replacement);
  void setRangeText(DOMString replacement, unsigned long start, unsigned long end, optional SelectionMode selectionMode = "preserve");
  void setSelectionRange(unsigned long start, unsigned long end, optional DOM::DOMString direction);

  // also has obsolete members
    DOM::DOMString align;
    DOM::DOMString useMap;
};

} /* namespace WebAPI */
} /* namespace HTML */


#endif /* SRC_HTML_WEBAPI_HTMLINPUTELEMENT_HPP_ */

