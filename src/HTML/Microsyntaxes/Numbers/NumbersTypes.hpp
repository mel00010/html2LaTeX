/*******************************************************************************
 * NumberTypes.hpp
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
#ifndef HTML_MICROSYNTAXES_NUMBERS_NUMBERSTYPES_HPP_
#define HTML_MICROSYNTAXES_NUMBERS_NUMBERSTYPES_HPP_

#include <exception>

namespace HTML {
namespace Microsyntaxes {
namespace Numbers {

class parseException: std::exception {
	public:
		parseException() {
		}
		parseException(const char* error_message) {
			message = error_message;
		}
		virtual const char* what() const noexcept {
			return message;
		}
	protected:
		const char* message = "";
};

} /* namespace Numbers */
} /* namespace Microsyntaxes */
} /* namespace HTML */



#endif /* HTML_MICROSYNTAXES_NUMBERS_NUMBERSTYPES_HPP_ */
