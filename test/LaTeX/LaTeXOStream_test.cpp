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

class LaTeX_LaTeXOStream_Test: public ::testing::Test {
	public:

};

TEST_F(LaTeX_LaTeXOStream_Test, write) {
	MockUnicodeToLaTeX converter;
	MockStreamBuf ostreambuf;
	std::ostream output(&ostreambuf);
	LaTeXOStream latexOStream(output, converter);
	std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> conv32;
	std::u32string str32 = conv32.from_bytes(std::string("\\ test"));
	std::string returnString("\\textbackslash test");

	EXPECT_CALL(converter, convert(TypedEq<std::u32string>(str32)))
			.WillOnce(Return(returnString));
	EXPECT_CALL(ostreambuf, xsputn(StrEq(returnString.c_str()), 19))
			.WillOnce(ReturnArg<1>());
	latexOStream << std::string("\\ test");
}

} /* namespace LaTeX */
