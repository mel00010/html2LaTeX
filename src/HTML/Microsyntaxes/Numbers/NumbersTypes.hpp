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

#include <algorithm>
#include <cmath>
#include <exception>
#include <iostream>
#include <limits>

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

/**
 * @brief Stream operator overload to allow printing of parseException objects to streams.
 * @param os Stream to print to.
 * @param parseException parseException object to print.
 * @return Returns a reference to @c os.
 */
::std::ostream& operator<<(::std::ostream& os, const parseException& parseException);

/**
 * @brief Represents the possible different types of a dimension value.
 */
enum class DimensionType {
	UNKNOWN, //!< Indicates that the type of the dimension value is unknown
	PERCENTAGE, //!< Indicates that the dimension value is a percentage
	LENGTH,     //!< Indicates that the dimension value is a length
	RELATIVE, //!< Indicates that the dimension value is relative
	ABSOLUTE //!< Indicates that the dimension value is absolute
};
/**
 * @brief Holds a dimension value
 */
struct Dimension {
		Dimension(double value, DimensionType type) :
				value(value), type(type) {
		}

		/**
		 * @brief Holds the value for the dimension.
		 */
		double value = NAN;
		/**
		 * @brief Indicates whether the dimension is a percentage or a length.
		 */
		DimensionType type = DimensionType::UNKNOWN;
};
/**
 * @brief Tests two Dimension objects for equality
 * @param rhs The Dimension object on the right hand side of the comparison
 * @param lhs The Dimension object on the left hand side of the comparison
 * @return Returns @c true if both the value fields and the type fields of both objects are equal.
 * 		   Otherwise, the function returns @c false.
 */
inline bool operator==(const Dimension& rhs, const Dimension& lhs) {
	if (rhs.type != lhs.type) {
		return false;
	}
	return std::fabs(rhs.value - lhs.value) <= (
			std::numeric_limits<double>::epsilon() * (
					std::max(std::fabs(rhs.value), std::fabs(lhs.value))
					)
			);
}

/**
 * @brief Tests two Dimension objects for inequality
 * @param rhs The Dimension object on the right hand side of the comparison
 * @param lhs The Dimension object on the left hand side of the comparison
 * @return Returns @c true if the value fields or the type fields of both objects are not equal.
 * 		   Otherwise, the function returns @c false.
 */
inline bool operator!=(const Dimension& rhs, const Dimension& lhs) {
	return !(rhs == lhs);
}
/**
 * @brief Allows printing of Dimension objects to streams
 * @param os Stream to write to
 * @param dimension Dimension object to write
 * @return Returns @c os
 */
::std::ostream& operator<<(::std::ostream& os, const Dimension& dimension);

/**
 * @brief Allows printing of DimensionType enum values to streams
 * @param os Stream to write to
 * @param dimensionType DimensionType enum value to write
 * @return Returns @c os
 */
::std::ostream& operator<<(::std::ostream& os, const DimensionType& dimensionType);
} /* namespace Numbers */
} /* namespace Microsyntaxes */
} /* namespace HTML */



#endif /* HTML_MICROSYNTAXES_NUMBERS_NUMBERSTYPES_HPP_ */
