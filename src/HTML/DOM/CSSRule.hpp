/*******************************************************************************
 * CSSRule.hpp
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
#ifndef SRC_HTML_DOM_CSSRULE_HPP_
#define SRC_HTML_DOM_CSSRULE_HPP_

#include "CSSOMString.hpp"
#include "CSSStyleSheet.hpp"

#include <optional>

namespace HTML {
namespace DOM {

class CSSRule {
	public:
		const unsigned short STYLE_RULE = 1;
		const unsigned short CHARSET_RULE = 2; // historical
		const unsigned short IMPORT_RULE = 3;
		const unsigned short MEDIA_RULE = 4;
		const unsigned short FONT_FACE_RULE = 5;
		const unsigned short PAGE_RULE = 6;
		const unsigned short MARGIN_RULE = 9;
		const unsigned short NAMESPACE_RULE = 10;
		const unsigned short type;
		CSSOMString cssText;
		const std::optional<CSSRule> parentRule;
		const std::optional<CSSStyleSheet> parentStyleSheet;
};

} /* namespace DOM */
} /* namespace HTML */

#endif /* SRC_HTML_DOM_CSSRULE_HPP_ */
