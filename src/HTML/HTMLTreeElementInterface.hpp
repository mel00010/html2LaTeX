/*******************************************************************************
 * HTMLTreeElementInterface.hpp
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
#ifndef HTML_HTMLTREEELEMENTINTERFACE_HPP_
#define HTML_HTMLTREEELEMENTINTERFACE_HPP_

#include "HTMLTypes.hpp"

#include <string>
#include <vector>


namespace HTML {

/**
 * @brief Interface for HTMLTreeElement classes
 */
class HTMLTreeElementInterface {
	public:
		HTMLTreeElementInterface() { // LCOV_EXCL_LINE
		}							 // LCOV_EXCL_LINE
		virtual ~HTMLTreeElementInterface() { // LCOV_EXCL_LINE
		}									  // LCOV_EXCL_LINE

	public:
		virtual const HTMLTreeElementInterface* getRoot() = 0;
		virtual const HTMLTreeElementInterface* getParent() = 0;
		virtual const std::vector<HTMLTreeElementInterface*>& getChildren() = 0;
		virtual const std::string& getContents() = 0;
		virtual const std::vector<Attribute*>& getAttributes() = 0;
		virtual const std::string& getTagName() = 0;
		virtual const Formatting& getFormatting() = 0;

		virtual bool isText() = 0;
		virtual bool isRoot() = 0;
		virtual bool isEmpty() = 0;
		virtual bool isInitialized() = 0;
		virtual bool hasAttributes() = 0;
		virtual bool hasChildren() = 0;

		virtual void makeRoot() = 0;

		virtual bool addChild(const HTMLTreeElementInterface* element) = 0;
		virtual bool deleteChild(HTMLTreeElementInterface* element) = 0;

		virtual bool addAttribute(const Attribute& attribute) = 0;
		virtual bool removeAttribute(Attribute& attribute) = 0;

		virtual void setContents(const std::string& contents) = 0;
		virtual void setFormatting(const Formatting& formatting) = 0;
		virtual void setParent(const HTMLTreeElementInterface* new_parent) = 0;
		virtual void setRoot(const HTMLTreeElementInterface* new_root) = 0;
		virtual void setTagName() = 0;

};

} /* namespace HTML */

#endif /* HTML_HTMLTREEELEMENTINTERFACE_HPP_ */
