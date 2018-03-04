/*******************************************************************************
 * Range.hpp
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
#ifndef SRC_HTML_DOM_RANGE_HPP_
#define SRC_HTML_DOM_RANGE_HPP_

#include "DocumentFragment.hpp"

namespace HTML {
namespace DOM {

class Range {
	public:
		const Node startContainer;
		const unsigned long startOffset;
		const Node endContainer;
		const unsigned long endOffset;
		const bool collapsed;
		const Node commonAncestorContainer;

		void setStart(Node node, unsigned long offset);
		void setEnd(Node node, unsigned long offset);
		void setStartBefore(Node node);
		void setStartAfter(Node node);
		void setEndBefore(Node node);
		void setEndAfter(Node node);
		void collapse(bool toStart = false);
		void selectNode(Node node);
		void selectNodeContents(Node node);

		const unsigned short START_TO_START = 0;
		const unsigned short START_TO_END = 1;
		const unsigned short END_TO_END = 2;
		const unsigned short END_TO_START = 3;
		short compareBoundaryPoints(unsigned short how, Range sourceRange);

		void deleteContents();
		DocumentFragment extractContents();
		DocumentFragment cloneContents();
		void insertNode(Node node);
		void surroundContents(Node newParent);

		Range cloneRange();
		void detach();

		bool isPointInRange(Node node, unsigned long offset);
		short comparePoint(Node node, unsigned long offset);

		bool intersectsNode(Node node);

//  stringifier;
};

} /* namespace DOM */
} /* namespace HTML */

#endif /* SRC_HTML_DOM_RANGE_HPP_ */
