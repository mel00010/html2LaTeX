/*******************************************************************************
 * LaTeXOStream.cpp
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

#include "LaTeXOStream.hpp"

#include <bits/locale_conv.h>
//#include <stddef.h>
//#include <UnicodeToLaTeX.hpp>
#include <codecvt>
//#include <fstream>
//#include <iomanip>
//#include <iostream>
//#include <locale>
//#include <string>


namespace LaTeX {


LaTeXOStream::LaTeXOStream(std::ostream& output, UnicodeToLaTeX& converter) :
		ostream(output), unicodeToLaTeX(converter) {
}

LaTeXOStream::~LaTeXOStream() {
}

void LaTeXOStream::write(const char* string, __attribute__((unused))  const size_t size) {
	std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> conv32;
	std::u32string str32 = conv32.from_bytes(string);

	ostream << unicodeToLaTeX.convert(str32);
}

void LaTeXOStream::write(const char32_t& string, __attribute__((unused))   const size_t size) {
	ostream << unicodeToLaTeX.convert(string);
}

void LaTeXOStream::write(const std::string& string) {
	std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> conv32;
	std::u32string str32 = conv32.from_bytes(string);

	ostream << unicodeToLaTeX.convert(str32);
}
void LaTeXOStream::write(const std::u32string& string) {
	ostream << unicodeToLaTeX.convert(string);
}
} /* namespace LaTeX */

