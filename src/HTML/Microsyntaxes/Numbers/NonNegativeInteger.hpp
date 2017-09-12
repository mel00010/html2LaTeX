/*******************************************************************************
 * NonNegativeInteger.hpp
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
#ifndef HTML_MICROSYNTAXES_NUMBERS_NONNEGATIVEINTEGER_HPP_
#define HTML_MICROSYNTAXES_NUMBERS_NONNEGATIVEINTEGER_HPP_

#include <string>

namespace HTML {
namespace Microsyntaxes {
namespace Numbers {

/**
 * @brief Tests if a string represents a valid non-negative integer
 * @param string String to test
 * @return Returns @c true if @c string represents a non-negative integer, @c false if it does not.
 *
 * @test HTML::Microsyntaxes::Numbers::TEST(HTML_Microsyntaxes_Numbers_NonNegativeInteger, isNonNegativeInteger)
 */
bool isNonNegativeInteger(const std::string& string);

/**
 * @brief Tests if a string represents a valid hexadecimal non-negative integer
 * @param string String to test
 * @return Returns @c true if @c string represents a hexadecimal non-negative integer, @c false if it does not.
 *
 * @test HTML::Microsyntaxes::Numbers::TEST(HTML_Microsyntaxes_Numbers_NonNegativeInteger, isNonNegativeHexInteger)
 */
bool isNonNegativeHexInteger(const std::string& string);

/**
 * @brief Retrieves the non-negative integer a std::string holds
 * @param string String to parse
 * @return Returns the non-negative integer the string holds.
 * @exception parseException The algorithm failed to parse @c string.
 *
 * @test HTML::Microsyntaxes::Numbers::TEST(HTML_Microsyntaxes_Numbers_NonNegativeInteger, parseNonNegativeInteger)
 */
unsigned int parseNonNegativeInteger(const std::string& string);

/**
 * @brief Retrieves the hexadecimal non-negative integer a std::string holds
 * @param string String to parse
 * @return Returns the non-negative hexadecimal integer the string holds.
 * @exception parseException The algorithm failed to parse @c string.
 *
 * @test HTML::Microsyntaxes::Numbers::TEST(HTML_Microsyntaxes_Numbers_NonNegativeInteger, parseNonNegativeHexInteger)
 */
unsigned long parseNonNegativeHexInteger(const std::string& string);

} /* namespace Numbers */
} /* namespace Microsyntaxes */
} /* namespace HTML */


#endif /* HTML_MICROSYNTAXES_NUMBERS_NONNEGATIVEINTEGER_HPP_ */
