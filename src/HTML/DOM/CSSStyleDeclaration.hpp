/*******************************************************************************
 * CSSStyleDeclaration.hpp
 * Copyright (C) 2018  Mel McCalla <melmccalla@gmail.com>
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
#ifndef SRC_HTML_DOM_CSSSTYLEDECLARATION_HPP_
#define SRC_HTML_DOM_CSSSTYLEDECLARATION_HPP_

#include "CSSOMString.hpp"
#include "CSSRule.hpp"

#include <optional>

namespace HTML {
namespace DOM {

class CSSStyleDeclaration {
	public:
		  CSSOMString cssText;
		  const unsigned long length;
		  CSSOMString getItem(unsigned long index);
		  CSSOMString getPropertyValue(CSSOMString property);
		  CSSOMString getPropertyPriority(CSSOMString property);
		  void setProperty(CSSOMString property, CSSOMString value = "", CSSOMString priority = "");
		  void setPropertyValue(CSSOMString property, CSSOMString value = "");
		  void setPropertyPriority(CSSOMString property, CSSOMString priority = "");
		  CSSOMString removeProperty(CSSOMString property);
		  const std::optional<CSSRule> parentRule;
		  CSSOMString cssFloat = "";
};



} /* namespace DOM */
} /* namespace HTML */



#endif /* SRC_HTML_DOM_CSSSTYLEDECLARATION_HPP_ */
