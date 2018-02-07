/*******************************************************************************
 * MutationObserver.hpp
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
#ifndef SRC_HTML_DOM_MUTATIONOBSERVER_HPP_
#define SRC_HTML_DOM_MUTATIONOBSERVER_HPP_

#include "DOMString.hpp"
#include "MutationRecord.hpp"
#include "Node.hpp"

#include <optional>
#include <vector>

namespace HTML {
namespace DOM {

struct MutationObserverInit;

class MutationObserver {
		void observe(Node target, std::optional<MutationObserverInit> options);
		void disconnect();
		std::vector<MutationRecord> takeRecords();
};

using MutationCallback = void (*)(std::vector<MutationRecord> mutations, MutationObserver observer);

struct MutationObserverInit {
	public:
		bool childList = false;
		bool attributes;
		bool characterData;
		bool subtree = false;
		bool attributeOldValue;
		bool characterDataOldValue;
		std::vector<DOMString> attributeFilter;
};

} /* namespace DOM */
} /* namespace HTML */

#endif /* SRC_HTML_DOM_MUTATIONOBSERVER_HPP_ */
