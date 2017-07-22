/*******************************************************************************
 * LaTeXOStream_test.cpp
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

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <LaTeX/LaTeXOStream.hpp>
#include <iostream>
#include <fstream>
#include <locale>
#include <iomanip>
#include <codecvt>

using namespace testing;

namespace LaTeX {

class MockUnicodeToLaTeX: public UnicodeToLaTeX {
	public:
		virtual ~MockUnicodeToLaTeX() {
		}
	public:
		MOCK_METHOD1(convert, const std::string (const char32_t codePoint));
		MOCK_METHOD1(convert, const std::string (const std::u32string string));
	};


class MockStreamBuf: public std::streambuf {
	public:
		MOCK_METHOD2(xsputn, std::streamsize(const char_type* s, std::streamsize n));
		MOCK_METHOD1(overflow, int_type(int_type c));
	};

TEST(LaTeX, LaTeXOStream) {

	MockUnicodeToLaTeX converter;
	MockStreamBuf ostreambuf;
	std::ostream output(&ostreambuf);
	LaTeXOStream latexOStream(output, converter);

	LaTeXOStream* latexOStreamPtr = new LaTeXOStream(output, converter);
	delete latexOStreamPtr;

	EXPECT_CALL(converter, convert(TypedEq<std::u32string>(std::u32string(U"\\ test"))))
			.Times(3)
			.WillRepeatedly(Return(std::string("\\textbackslash test")));
	EXPECT_CALL(converter, convert(TypedEq<char32_t>(U'\\')))
			.WillOnce(Return(std::string("\\textbackslash")));
	EXPECT_CALL(ostreambuf, xsputn(StrEq("\\textbackslash test"), 19))
			.Times(3)
			.WillRepeatedly(ReturnArg<1>());
	EXPECT_CALL(ostreambuf, xsputn(StrEq("\\textbackslash"), 14))
			.WillOnce(ReturnArg<1>());
	latexOStream << std::u32string(U"\\ test");
	latexOStream << std::string("\\ test");
	latexOStream << "\\ test";
	latexOStream << U'\\';
}

} /* namespace LaTeX */
