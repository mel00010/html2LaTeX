/*******************************************************************************
 * TreeWalker.hpp
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
#ifndef SRC_HTML_DOM_TREEWALKER_HPP_
#define SRC_HTML_DOM_TREEWALKER_HPP_

#include "Node.hpp"
#include "NodeFilter.hpp"

#include <optional>

namespace HTML {
namespace DOM {

class TreeWalker {
		const unsigned long whatToShow;
		const std::optional<NodeFilter> filter;
		Node currentNode;

		std::optional<Node> parentNode();
		std::optional<Node> firstChild();
		std::optional<Node> lastChild();
		std::optional<Node> previousSibling();
		std::optional<Node> nextSibling();
		std::optional<Node> previousNode();
		std::optional<Node> nextNode();

	protected:
		const Node root;
};

} /* namespace DOM */
} /* namespace HTML */

#endif /* SRC_HTML_DOM_TREEWALKER_HPP_ */
