/*******************************************************************************
 * NodeFilter.hpp
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
#ifndef SRC_HTML_DOM_NODEFILTER_HPP_
#define SRC_HTML_DOM_NODEFILTER_HPP_

//#include "Node.hpp"

namespace HTML {
namespace DOM {

class Node;

class NodeFilter {
	public:
		// Constants for acceptNode()
		const unsigned short FILTER_ACCEPT = 1;
		const unsigned short FILTER_REJECT = 2;
		const unsigned short FILTER_SKIP = 3;

		// Constants for whatToShow
		const unsigned long SHOW_ALL = 0xFFFFFFFF;
		const unsigned long SHOW_ELEMENT = 0x1;
		const unsigned long SHOW_ATTRIBUTE = 0x2;
		const unsigned long SHOW_TEXT = 0x4;
		const unsigned long SHOW_CDATA_SECTION = 0x8;
		const unsigned long SHOW_ENTITY_REFERENCE = 0x10; // historical
		const unsigned long SHOW_ENTITY = 0x20; // historical
		const unsigned long SHOW_PROCESSING_INSTRUCTION = 0x40;
		const unsigned long SHOW_COMMENT = 0x80;
		const unsigned long SHOW_DOCUMENT = 0x100;
		const unsigned long SHOW_DOCUMENT_TYPE = 0x200;
		const unsigned long SHOW_DOCUMENT_FRAGMENT = 0x400;
		const unsigned long SHOW_NOTATION = 0x800; // historical

		unsigned short acceptNode(Node node);
};

} /* namespace DOM */
} /* namespace HTML */

#endif /* SRC_HTML_DOM_NODEFILTER_HPP_ */
