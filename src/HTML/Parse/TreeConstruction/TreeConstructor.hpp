/*******************************************************************************
 * TreeConstructor.hpp
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
#ifndef SRC_HTML_PARSE_TREECONSTRUCTION_TREECONSTRUCTOR_HPP_
#define SRC_HTML_PARSE_TREECONSTRUCTION_TREECONSTRUCTOR_HPP_

#include <HTML/Parse/Tokenization/TokenizationTypes.hpp>

namespace HTML {
namespace Parse {
namespace TreeConstruction {

class TreeConstructor {
	public:
		void dispatch(Tokenization::Token token);
		void dispatchParseError(ParseError error);

};

} /* namespace TreeConstruction */
} /* namespace Parse */
} /* namespace HTML */



#endif /* SRC_HTML_PARSE_TREECONSTRUCTION_TREECONSTRUCTOR_HPP_ */
