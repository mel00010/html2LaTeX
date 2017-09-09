/*******************************************************************************
 * Element.hpp
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
#ifndef SRC_HTML_ELEMENTS_ELEMENT_HPP_
#define SRC_HTML_ELEMENTS_ELEMENT_HPP_

#include <string>
#include <vector>

#include <HTML/HTMLTypes.hpp>

namespace HTML {
namespace Elements {
/**
 * Base class for all other element classes.
 */
class Element {
	public:
		Element();
		Element(Element* root, Element* parent, std::vector<Element*> children = { }, bool isText = false);
		virtual ~Element();

	public:
		const Element* getRoot();
		const Element* getParent();
		const std::vector<Element*>& getChildren();

		bool isText();
		bool isRoot();
		bool isInitialized();
		bool hasChildren();

		void makeRoot();

		bool addChild(Element* element);
		bool deleteChild(Element* element);

		void setParent(Element* new_parent);
		void setRoot(Element* new_root);

	protected:
		bool text = false;
		Element* root = nullptr;
		Element* parent = nullptr;
		std::vector<Element*> children;

};

} /* namespace Elements */
} /* namespace HTML */

#endif /* SRC_HTML_ELEMENTS_ELEMENT_HPP_ */
