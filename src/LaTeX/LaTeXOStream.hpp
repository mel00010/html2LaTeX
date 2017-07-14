/*******************************************************************************
 * LaTeXOStream.hpp
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
#ifndef LATEX_LATEXOSTREAM_HPP_
#define LATEX_LATEXOSTREAM_HPP_

#include <LaTeX/UnicodeToLaTeX.hpp>
#include <iostream>
#include <locale>
#include <gtest/gtest.h>


namespace LaTeX {

class LaTeXOStream {
	public:
		LaTeXOStream(std::ostream& output, UnicodeToLaTeX& converter);
		virtual ~LaTeXOStream();
	public:
		/**
		 * Typedef defining the LaTeXOStreamManipulator type for use by the stream operators.
		 */
		typedef LaTeXOStream& (*LaTeXOStreamManipulator)(LaTeXOStream&);
		/**
		 * Typedef defining the CoutType type for use by the stream operators.
		 */
		typedef std::basic_ostream<char, std::char_traits<char> > CoutType;
		/**
		 * Typedef defining the StandardEndLine type for use by the stream operators.
		 * @param
		 * @return
		 */
		typedef CoutType& (*StandardEndLine)(CoutType&);

		template<typename T>
		/**
		 * Stream insertion operator.
		 * @param x
		 * @return
		 */
		inline LaTeXOStream& operator<<(const T& x) {
			write(x, sizeof(x));
			return *this;
		}
		/**
		 * Stream insertion operator handling std::string.
		 * @param x
		 * @return
		 */
		inline LaTeXOStream& operator<<(const std::string& x) {
			write(x.c_str(), x.size());
			return *this;
		}
		/**
		 * Stream insertion operator.
		 * @param in
		 * @return
		 */
		inline std::istream& operator>>(std::istream &in) {
			std::string s(std::istreambuf_iterator<char>(in), { });
			write(s.c_str(), s.size());
			return in;
		}
		/**
		 * Stream insertion operator handling std::endl.
		 * @param manip
		 * @return
		 */
		inline LaTeXOStream& operator<<(__attribute__((unused))  StandardEndLine manip) {
			// Call the function, but we cannot return it's value
			write("\n", sizeof("\n"));
			return *this;
		}

	protected:
		void write(const char* string, __attribute__((unused))  const size_t size);

	protected:

		std::ostream& ostream;
		UnicodeToLaTeX& unicodeToLaTeX;
};

} /* namespace LaTeX */

#endif /* LATEX_LATEXOSTREAM_HPP_ */
