/*******************************************************************************
 * NumbersTypes.hpp
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
#include <iostream>

namespace HTML {
namespace Microsyntaxes {

/**
 * @brief Holds functions related to parsing numbers
 */
namespace Numbers {

/**
 * @brief Exception thrown after a parse error occurs
 */
class parseException: std::exception {
	public:
		/**
		 * @brief Default constructor
		 * @details Initializes the message returned by what() to be the empty string.
		 */
		parseException();

		/**
		 * @brief Constructor with error message
		 * @details Initializes the message returned by what() to be @c error_message
		 * @param error_message Message to be returned by what()
		 */
		parseException(const char* error_message);

	public:
		/**
		 * @brief Reads the contents of @c parseException::message
		 * @return Returns the message stored in @c parseException::message
		 */
		virtual const char* what() const noexcept;
	protected:

		/**
		 * @brief Stores the message to be returned by what()
		 */
		const char* message = "";
};

::std::ostream& operator<<(::std::ostream& os, const parseException& parseException);

} /* namespace Numbers */
} /* namespace Microsyntaxes */
} /* namespace HTML */



#endif /* HTML_MICROSYNTAXES_NUMBERS_NUMBERSTYPES_HPP_ */
