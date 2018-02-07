/*******************************************************************************
 * DOMTokenList.hpp
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
#ifndef SRC_HTML_DOM_DOMTOKENLIST_HPP_
#define SRC_HTML_DOM_DOMTOKENLIST_HPP_

#include "DOMString.hpp"

#include <optional>

namespace HTML {
namespace DOM {

class DOMTokenList {
	public:
		const unsigned long length;
		std::optional<DOMString> item(unsigned long index); // getter
		bool contains(DOMString token);
		void add(DOMString... tokens);
		void remove(DOMString... tokens);
		bool toggle(DOMString token, std::optional<bool> force);
		void replace(DOMString token, DOMString newToken);
		bool supports(DOMString token);
		DOMString value;
//		iterable<DOMString>;
};

} /* namespace DOM */
} /* namespace HTML */




#endif /* SRC_HTML_DOM_DOMTOKENLIST_HPP_ */
