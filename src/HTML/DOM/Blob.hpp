/*******************************************************************************
 * Blob.hpp
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
#ifndef SRC_HTML_DOM_BLOB_HPP_
#define SRC_HTML_DOM_BLOB_HPP_

#include "BufferSource.hpp"
#include "DOMString.hpp"
#include "USVString.hpp"

#include <list>
#include <variant>

namespace HTML {
namespace DOM {

class Blob;

typedef std::variant<BufferSource, Blob, USVString> BlobPart;

enum class EndingType {
	TRANSPARENT, NATIVE
};

struct BlobPropertyBag {
	public:
		DOMString type = U"";
		EndingType endings = EndingType::TRANSPARENT;
};

class Blob {
	public:

		Blob();
		Blob(std::list<BlobPart> blobParts);
		Blob(BlobPropertyBag options);
		Blob(std::list<BlobPart> blobParts, BlobPropertyBag options);
		const unsigned long long size;
		const DOMString type;

		// slice Blob into byte-ranged chunks
		Blob slice();
		Blob slice(long long start);
		Blob slice(long long start, long long end);
		Blob slice(long long start, DOMString contentType);
		Blob slice(long long start, long long end, DOMString contentType);
		Blob slice(DOMString contentType);
};

}
/* namespace DOM */
} /* namespace HTML */

#endif /* SRC_HTML_DOM_BLOB_HPP_ */
