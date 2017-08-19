/*******************************************************************************
 * ListsOfIntegers.hpp
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
#ifndef HTML_MICROSYNTAXES_NUMBERS_LISTSOFINTEGERS_HPP_
#define HTML_MICROSYNTAXES_NUMBERS_LISTSOFINTEGERS_HPP_

#include <list>
#include <string>

namespace HTML {
namespace Microsyntaxes {
namespace Numbers {

/**
 * @brief Tests if @c string represents a list of integers
 * @param string String to test
 * @return Returns @c true if @c string represents a list of integers,
 * 		   @c false if it does not.
 */
bool isListOfIntegers(const std::string& string);

/**
 * @brief Retrieves the list of integers from @c string
 * @param string String to parse
 * @return Returns a std::list of integers retrieved from @c string.
 */
std::list<int> parseListOfIntegers(const std::string& string);

} /* namespace Numbers */
} /* namespace Microsyntaxes */
} /* namespace HTML */




#endif /* HTML_MICROSYNTAXES_NUMBERS_LISTSOFINTEGERS_HPP_ */
