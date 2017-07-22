/*******************************************************************************
 * HTMLTreeElement.cpp
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

#include <HTMLTreeElement.hpp>

#include <HTMLTreeElementInterface.hpp>
#include <HTMLTypes.hpp>

#include <vector>

namespace HTML {
HTMLTreeElement::HTMLTreeElement() {
	root = nullptr;
	parent = nullptr;
}
HTMLTreeElement::HTMLTreeElement(HTMLTreeElementInterface* root, HTMLTreeElementInterface* parent) {
	this->root = root;
	this->parent = parent;
}

HTMLTreeElement::~HTMLTreeElement() {
	for (HTMLTreeElementInterface* i : children) {
		delete i;
	}
}

const HTMLTreeElementInterface* HTMLTreeElement::getRoot() {
	return root;
}

const HTMLTreeElementInterface* HTMLTreeElement::getParent() {
	return parent;
}

const std::vector<HTMLTreeElementInterface*>& HTMLTreeElement::getChildren() {
	return children;
}

const std::string& HTMLTreeElement::getContents() {
	//TODO Finish function
}
const std::vector<Attribute*>& HTMLTreeElement::getAttributes() {
	//TODO Finish function
}
const std::string& HTMLTreeElement::getTagName() {
	//TODO Finish function
}
const Formatting& HTMLTreeElement::getFormatting() {
	//TODO Finish function
}

bool HTMLTreeElement::isText() {
	//TODO Finish function
}
bool HTMLTreeElement::isRoot() {
	if (root == this && parent == this) {
		return true;
	} else {
		return false;
	}
	return false;
}

bool HTMLTreeElement::isEmpty() {
	//TODO Finish function
}
bool HTMLTreeElement::isInitialized() {
	//TODO Finish function
}
bool HTMLTreeElement::hasAttributes() {
	//TODO Finish function
}
bool HTMLTreeElement::hasChildren() {
	//TODO Finish function
}

void HTMLTreeElement::makeRoot() {
	root = this;
	parent = this;
}

bool HTMLTreeElement::addChild(const HTMLTreeElementInterface* element) {
//	children.push_back(element);
	//TODO Finish function
}
bool HTMLTreeElement::deleteChild(HTMLTreeElementInterface* element) {
	//TODO Finish function
}

bool HTMLTreeElement::addAttribute(const Attribute& attribute) {
	//TODO Finish function
}
bool HTMLTreeElement::removeAttribute(Attribute& attribute) {
	//TODO Finish function
}

void HTMLTreeElement::setContents(const std::string& contents) {
	//TODO Finish function
}
void HTMLTreeElement::setFormatting(const Formatting& formatting) {
	//TODO Finish function
}
void HTMLTreeElement::setParent(const HTMLTreeElementInterface* new_parent) {
	//TODO Finish function
}
void HTMLTreeElement::setRoot(const HTMLTreeElementInterface* new_root) {
	//TODO Finish function
}
void HTMLTreeElement::setTagName() {
	//TODO Finish function
}



} /* namespace HTML */
