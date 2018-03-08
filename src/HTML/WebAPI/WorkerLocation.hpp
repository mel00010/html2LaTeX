/*******************************************************************************
 * WorkerLocation.hpp
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
#ifndef SRC_HTML_WEBAPI_WORKERLOCATION_HPP_
#define SRC_HTML_WEBAPI_WORKERLOCATION_HPP_

#include "../DOM/USVString.hpp"

namespace HTML {
namespace WebAPI {

class WorkerLocation {
	public:
		const DOM::USVString href;
		const DOM::USVString origin;
		const DOM::USVString protocol;
		const DOM::USVString host;
		const DOM::USVString hostname;
		const DOM::USVString port;
		const DOM::USVString pathname;
		const DOM::USVString search;
		const DOM::USVString hash;
};

} /* namespace WebAPI */
} /* namespace HTML */

#endif /* SRC_HTML_WEBAPI_WORKERLOCATION_HPP_ */

