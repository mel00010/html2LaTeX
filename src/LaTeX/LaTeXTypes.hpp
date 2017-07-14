/*******************************************************************************
 * LaTeXTypes.hpp
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
#ifndef LATEX_LATEXTYPES_HPP_
#define LATEX_LATEXTYPES_HPP_

namespace LaTeX {

/**
 * @brief Describes the possible font sizes LaTeX supports.
 */
enum class LaTeXSizes {
	TINY, /**< @brief \\tiny @details Corresponds to \\tiny, the smallest font size LaTex supports. */
	SCRIPTSIZE, /**< @brief \\scriptsize @details Corresponds to \\scriptsize, the size of superscript and subscript text in LaTeX. */
	FOOTNOTESIZE,/**< @brief \\footnotesize @details Corresponds to \\footnotesize, the size of inline footnote numbers in LaTeX. */
	SMALL, /**< @brief \\small @details Corresponds to \\small. */
	NORMALSIZE, /**< @brief \\normalsize @details Corresponds to \\normalsize, the normal size of text in LaTeX. */
	LARGE_1, /**< @brief \\large @details Corresponds to \\large */
	LARGE_2, /**< @brief \\Large @details Corresponds to \\Large */
	LARGE_3, /**< @brief \\LARGE @details Corresponds to \\LARGE */
	HUGE_1, /**< @brief \\huge @details Corresponds to \\huge */
	HUGE_2 /**< @brief \\Huge @details Corresponds to \\Huge, the largest preset font size LaTeX includes */
};
} /* namespace LaTeX */



#endif /* LATEX_LATEXTYPES_HPP_ */
