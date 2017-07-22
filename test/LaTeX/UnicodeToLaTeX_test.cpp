/*******************************************************************************
 * UnicodeToLaTeX_test.cpp
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
#include <LaTeX/UnicodeToLaTeX.hpp>
#include <string>



namespace LaTeX {

TEST(UnicodeToLaTeX, convert) {
	UnicodeToLaTeX unicodeToLaTeX;
	const char32_t unicodeDefined = U'\U0000019B';
	const char32_t unicodeUndefined = U'\U0000017F';
	const std::u32string unicodeString = U"\U0000019B abcdef";
	EXPECT_EQ(std::string("\\textcrlambda abcdef"), unicodeToLaTeX.convert(unicodeString));
	EXPECT_EQ(std::string("\\textcrlambda"), unicodeToLaTeX.convert(unicodeDefined));
	EXPECT_EQ(std::string("\\char\"0000017F\""), unicodeToLaTeX.convert(unicodeUndefined));

}

} /* namespace LaTeX */
