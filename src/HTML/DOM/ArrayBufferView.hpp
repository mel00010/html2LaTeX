/*******************************************************************************
 * ArrayBufferView.hpp
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
#ifndef SRC_HTML_DOM_ARRAYBUFFERVIEW_HPP_
#define SRC_HTML_DOM_ARRAYBUFFERVIEW_HPP_

#include "Float32Array.hpp"
#include "Float64Array.hpp"
#include "Int16Array.hpp"
#include "Int32Array.hpp"
#include "Int8Array.hpp"
#include "Uint16Array.hpp"
#include "Uint32Array.hpp"
#include "Uint8Array.hpp"
#include "Uint8ClampedArray.hpp"

#include <variant>

namespace HTML {
namespace DOM {
using ArrayBufferView = std::variant<Int8Array, Int16Array, Int32Array,
		Uint8Array, Uint16Array, Uint32Array, Uint8ClampedArray,
		Float32Array, Float64Array>;
}
/* namespace DOM */
} /* namespace HTML */

#endif /* SRC_HTML_DOM_ARRAYBUFFERVIEW_HPP_ */
