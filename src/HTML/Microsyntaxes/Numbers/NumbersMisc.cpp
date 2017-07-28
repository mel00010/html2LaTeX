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

#include <NumbersMisc.hpp>
#include <NumbersTypes.hpp>

namespace HTML {
namespace Microsyntaxes {
namespace Numbers {

unsigned int ASCIIDigitToInt(const char& digit) {
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
} /* namespace Numbers */
} /* namespace Microsyntaxes */
} /* namespace HTML */
