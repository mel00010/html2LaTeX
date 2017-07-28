/*******************************************************************************
 * NumbersMisc.hpp
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
#ifndef HTML_MICROSYNTAXES_NUMBERS_NUMBERSMISC_HPP_
#define HTML_MICROSYNTAXES_NUMBERS_NUMBERSMISC_HPP_

namespace HTML {
namespace Microsyntaxes {
namespace Numbers {

/**
 * @brief Converts an ASCII digit to its numerical equivalent.
 * @param digit Digit to convert
 * @return Returns an unsigned int with a value in the range 0 to 9.
 * @exception parseException @c digit was not an ASCII digit
 *
 * @test HTML::Microsyntaxes::Numbers::TEST(HTML_Microsyntaxes_Numbers_NumbersMisc, ASCIIDigitToInt)
 */
unsigned int ASCIIDigitToInt(const char& digit);

} /* namespace Numbers */
} /* namespace Microsyntaxes */
} /* namespace HTML */



#endif /* HTML_MICROSYNTAXES_NUMBERS_NUMBERSMISC_HPP_ */
