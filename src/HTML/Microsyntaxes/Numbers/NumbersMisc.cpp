/*******************************************************************************
 * NumbersMisc.cpp
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

#include "NumbersMisc.hpp"

#include "NumbersTypes.hpp"

namespace HTML {
namespace Microsyntaxes {
namespace Numbers {

unsigned int ASCIIDigitToInt(const char32_t& digit) {
	int returned = 0;
	switch (digit) {
		case '0':
			returned = 0;
			break;
		case '1':
			returned = 1;
			break;
		case '2':
			returned = 2;
			break;
		case '3':
			returned = 3;
			break;
		case '4':
			returned = 4;
			break;
		case '5':
			returned = 5;
			break;
		case '6':
			returned = 6;
			break;
		case '7':
			returned = 7;
			break;
		case '8':
			returned = 8;
			break;
		case '9':
			returned = 9;
			break;
		default:
			throw parseException();
	}
	return returned;
}
unsigned int ASCIIHexDigitToInt(const char32_t& digit) {
	int returned = 0x0;
	switch (digit) {
		case '0':
			returned = 0x0;
			break;
		case '1':
			returned = 0x1;
			break;
		case '2':
			returned = 0x2;
			break;
		case '3':
			returned = 0x3;
			break;
		case '4':
			returned = 0x4;
			break;
		case '5':
			returned = 0x5;
			break;
		case '6':
			returned = 0x6;
			break;
		case '7':
			returned = 0x7;
			break;
		case '8':
			returned = 0x8;
			break;
		case '9':
			returned = 0x9;
			break;
		case 'a':
		case 'A':
			returned = 0xA;
			break;
		case 'b':
		case 'B':
			returned = 0xB;
			break;
		case 'c':
		case 'C':
			returned = 0xC;
			break;
		case 'd':
		case 'D':
			returned = 0xD;
			break;
		case 'e':
		case 'E':
			returned = 0xE;
			break;
		case 'f':
		case 'F':
			returned = 0xF;
			break;
		default:
			throw parseException();
	}
	return returned;
}
} /* namespace Numbers */
} /* namespace Microsyntaxes */
} /* namespace HTML */
