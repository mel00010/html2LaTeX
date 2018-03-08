/*******************************************************************************
 * Plugin.hpp
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
#ifndef SRC_HTML_WEBAPI_PLUGIN_HPP_
#define SRC_HTML_WEBAPI_PLUGIN_HPP_

#include "MimeType.hpp"

#include <optional>

#include "../DOM/DOMString.hpp"

namespace HTML {
namespace WebAPI {

class Plugin {
	public:
		const DOM::DOMString name;
		const DOM::DOMString description;
		const DOM::DOMString filename;
		const unsigned long length;
		std::optional<MimeType> getItem(unsigned long index);
		std::optional<MimeType> getNamedItem(DOM::DOMString name);
};

} /* namespace WebAPI */
} /* namespace HTML */

#endif /* SRC_HTML_WEBAPI_PLUGIN_HPP_ */

