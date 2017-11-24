/*******************************************************************************
 * Element.cpp
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
#include "Element.hpp"

#include <algorithm>
#include <vector>

namespace HTML {
namespace Elements {

Element::Element() :
		root(nullptr), parent(nullptr) {
}

Element::Element(Element* root, Element* parent,
		std::vector<Element*> children,
		std::vector<Attribute*> attributes, bool isText) :
		text(isText), root(root), parent(parent), children(children), attributes(attributes) {
}

Element::~Element() {

}

const Element* Element::getRoot() {
	return root;
}

const Element* Element::getParent() {
	return parent;
}

const std::vector<Element*>& Element::getChildren() {
	return children;
}

const std::vector<Attribute*>& Element::getAttributes() {
	return attributes;
}


bool Element::isText() {
	return text;
}

bool Element::isRoot() {
	return (root == this);
}


bool Element::isInitialized() {
	return !((root == nullptr) || (parent == nullptr));
}

bool Element::hasChildren() {
	return !children.empty();
}

bool Element::hasAttributes() {
	return !attributes.empty();
}

void Element::makeRoot() {
	setParent(this);
	setRoot(this);
}

bool Element::addChild(Element* element) {
	if (std::find(children.begin(), children.end(), element) != children.end()) {
		return false;
	}
	children.push_back(element);
	return true;
}

bool Element::deleteChild(Element* element) {
	std::vector<Element*>::iterator it = std::find(children.begin(), children.end(), element);
	if (it == children.end()) {
		return false;
	}
	children.erase(it);
	return true;
}

bool Element::addAttribute(Attribute* attribute) {
	if (std::find(attributes.begin(), attributes.end(), attribute) != attributes.end()) {
		return false;
	}
	attributes.push_back(attribute);
	return true;
}

bool Element::deleteAttribute(Attribute* attribute) {
	std::vector<Attribute*>::iterator it = std::find(attributes.begin(), attributes.end(), attribute);
	if (it == attributes.end()) {
		return false;
	}
	attributes.erase(it);
	return true;
}

void Element::setParent(Element* new_parent) {
	parent = new_parent;
}

void Element::setRoot(Element* new_root) {
	root = new_root;
}


} /* namespace Elements */
} /* namespace HTML */
