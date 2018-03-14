/*******************************************************************************
 * DataTransfer.hpp
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
#ifndef SRC_HTML_DOM_DATATRANSFER_HPP_
#define SRC_HTML_DOM_DATATRANSFER_HPP_

#include "DataTransferItemList.hpp"
#include "DOMString.hpp"
#include "Element.hpp"

#include <optional>

namespace HTML {
namespace DOM {

class DataTransfer {
	public:
		DataTransfer();
		DOMString dropEffect;
		DOMString effectAllowed;

	protected:
		const DataTransferItemList items;

	public:
		void setDragImage(Element image, long x, long y);

		/* old class */
		const FrozenArray<DOMString> types;
		DOMString getData(DOMString format);
		void setData(DOMString format, DOMString data);
		void clearData(std::optional<DOMString> format);

	protected:
		const FileList files;
};

} /* namespace DOM */
} /* namespace HTML */

#endif /* SRC_HTML_DOM_DATATRANSFER_HPP_ */

