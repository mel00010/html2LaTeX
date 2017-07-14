/*******************************************************************************
 * ConcreteUnicodeToLaTeX.hpp
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
#ifndef LATEX_CONCRETEUNICODETOLATEX_HPP_
#define LATEX_CONCRETEUNICODETOLATEX_HPP_

#include <LaTeX/UnicodeToLaTeX.hpp>
#include <string>
#include <locale>
#include <utility>

namespace LaTeX {
using Item = std::pair<char32_t, const char*>;

class ConcreteUnicodeToLaTeX: public UnicodeToLaTeX {
	public:
		virtual const std::string convert(const char32_t codePoint);
		virtual const std::string convert(const std::u32string string);
	protected:
#include <LaTeX/ConcreteUnicodeToLaTeXConversionArray.hpp>
		static constexpr size_t map_size = sizeof(unicodeToLaTeX) / sizeof(unicodeToLaTeX[0]);

	protected:
		const constexpr char* findValue(const char32_t key, int range = map_size);
		constexpr char32_t findKey(const char* value, int range = map_size);

};

} /* namespace LaTeX */



#endif /* LATEX_CONCRETEUNICODETOLATEX_HPP_ */
