/*******************************************************************************
 * CharacterData.hpp
 * Copyright (C) 2017  Mel McCalla <melmccalla@gmail.com>
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
#ifndef SRC_HTML_DOM_CHARACTERDATA_HPP_
#define SRC_HTML_DOM_CHARACTERDATA_HPP_

#include "ChildNode.hpp"
#include "DOMString.hpp"
#include "Node.hpp"

#include <stddef.h>

namespace HTML {
namespace DOM {

class CharacterData : public Node, public ChildNode {
	public:
		DOMString data = U"";
		const size_t length;
		DOMString substringData(size_t offset, size_t count);
		void appendData(DOMString data);
		void insertData(size_t offset, DOMString data);
		void deleteData(size_t offset, size_t count);
		void replaceData(size_t offset, size_t count, DOMString data);
};

} /* namespace DOM */
} /* namespace HTML */




#endif /* SRC_HTML_DOM_CHARACTERDATA_HPP_ */
