/*******************************************************************************
 * HTMLTreeElement.hpp
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
#ifndef HTML_HTMLTREEELEMENT_HPP_
#define HTML_HTMLTREEELEMENT_HPP_

#include "HTMLTreeElementInterface.hpp"
#include "HTMLTypes.hpp"

#include <string>
#include <vector>

namespace HTML {

/**
 * @brief Implements HTMLTreeElementInterface
 */
class HTMLTreeElement: public HTMLTreeElementInterface {
	public:
		HTMLTreeElement();
		explicit HTMLTreeElement(HTMLTreeElementInterface* root, HTMLTreeElementInterface* parent);
		virtual ~HTMLTreeElement();

	public:
		virtual const HTMLTreeElementInterface* getRoot();
		virtual const HTMLTreeElementInterface* getParent();
		virtual const std::vector<HTMLTreeElementInterface*>& getChildren();
		virtual const std::string& getContents();
		virtual const std::vector<Attribute*>& getAttributes();
		virtual const std::string& getTagName();
		virtual const Formatting& getFormatting();

		virtual bool isText();
		virtual bool isRoot();
		virtual bool isEmpty();
		virtual bool isInitialized();
		virtual bool hasAttributes();
		virtual bool hasChildren();

		virtual void makeRoot();

		virtual bool addChild(const HTMLTreeElementInterface* element);
		virtual bool deleteChild(HTMLTreeElementInterface* element);

		virtual bool addAttribute(const Attribute& attribute);
		virtual bool removeAttribute(Attribute& attribute);

		virtual void setContents(const std::string& contents);
		virtual void setFormatting(const Formatting& formatting);
		virtual void setParent(const HTMLTreeElementInterface* new_parent);
		virtual void setRoot(const HTMLTreeElementInterface* new_root);
		virtual void setTagName();

	protected:
		HTMLTreeElementInterface* root;
		HTMLTreeElementInterface* parent;
		std::vector<HTMLTreeElementInterface*> children;
		std::string tagName;
		std::vector<Attribute*> attributes;
		std::string contents;

};

} /* namespace HTML */

#endif /* HTML_HTMLTREEELEMENT_HPP_ */
