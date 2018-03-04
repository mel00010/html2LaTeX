/*******************************************************************************
 * Location.hpp
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
#ifndef SRC_HTML_WEBAPI_LOCATION_HPP_
#define SRC_HTML_WEBAPI_LOCATION_HPP_


namespace HTML {
namespace WebAPI {


class Location { // but see also additional creation steps and overridden internal methods
  [Unforgeable] stringifier  USVString href;
  [Unforgeable] const USVString origin;
  [Unforgeable]  USVString protocol;
  [Unforgeable]  USVString host;
  [Unforgeable]  USVString hostname;
  [Unforgeable]  USVString port;
  [Unforgeable]  USVString pathname;
  [Unforgeable]  USVString search;
  [Unforgeable]  USVString hash;

  [Unforgeable] void assign(USVString url);
  [Unforgeable] void replace(USVString url);
  [Unforgeable] void reload();

  [Unforgeable, SameObject] const DOM::DOMStringList ancestorOrigins;
};

} /* namespace WebAPI */
} /* namespace HTML */


#endif /* SRC_HTML_WEBAPI_LOCATION_HPP_ */

