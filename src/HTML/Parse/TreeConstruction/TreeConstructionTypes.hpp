/*******************************************************************************
 * TreeConstructionTypes.hpp
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
#ifndef SRC_HTML_PARSE_TREECONSTRUCTION_TREECONSTRUCTIONTYPES_HPP_
#define SRC_HTML_PARSE_TREECONSTRUCTION_TREECONSTRUCTIONTYPES_HPP_

namespace HTML {
namespace Parse {
namespace TreeConstruction {

enum class InsertionMode {
	INITIAL,
	BEFORE_HTML,
	BEFORE_HEAD,
	IN_HEAD,
	IN_HEAD_NOSCRIPT,
	AFTER_HEAD,
	IN_BODY,
	TEXT,
	IN_TABLE,
	IN_TABLE_TEXT,
	IN_CAPTION,
	IN_COLUMN_GROUP,
	IN_TABLE_BODY,
	IN_ROW,
	IN_CELL,
	IN_SELECT,
	IN_SELECT_IN_TABLE,
	IN_TEMPLATE,
	AFTER_BODY,
	IN_FRAMESET,
	AFTER_FRAMESET,
	AFTER_AFTER_BODY,
	AFTER_AFTER_FRAMESET
};

} /* namespace TreeConstruction */
} /* namespace Parse */
} /* namespace HTML */


#endif /* SRC_HTML_PARSE_TREECONSTRUCTION_TREECONSTRUCTIONTYPES_HPP_ */
