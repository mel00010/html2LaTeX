/*******************************************************************************
 * HTMLTreeElement_test.cpp
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



#include <HTML/HTMLTreeElement.hpp>
#include <gtest/gtest.h>

namespace HTML {

TEST(HTML_HTMLTreeElement, HTMLTreeElement) {
	HTMLTreeElement* root = new HTMLTreeElement();
	root->makeRoot();
	HTMLTreeElement* child = new HTMLTreeElement(root, root);
	delete child;
	delete root;
}
TEST(HTML_HTMLTreeElement, getRoot) {
	HTMLTreeElement* root = new HTMLTreeElement();
	root->makeRoot();
	HTMLTreeElement* child1 = new HTMLTreeElement(root, root);
	HTMLTreeElement* child2 = new HTMLTreeElement(nullptr, nullptr);
	EXPECT_EQ(root, child1->getRoot());
	EXPECT_NE(root, child2->getRoot());
	delete child1;
	delete child2;
	delete root;
}

TEST(HTML_HTMLTreeElement, getParent) {
	HTMLTreeElement* root = new HTMLTreeElement();
	root->makeRoot();
	HTMLTreeElement* parent = new HTMLTreeElement(root, root);
	HTMLTreeElement* child = new HTMLTreeElement(root, parent);

	EXPECT_EQ(root, root->getParent());
	EXPECT_EQ(root, parent->getParent());
	EXPECT_EQ(parent, child->getParent());

	delete child;
	delete parent;
	delete root;
}

TEST(HTML_HTMLTreeElement, getChildren) {
	HTMLTreeElement* root = new HTMLTreeElement();
	root->makeRoot();
	HTMLTreeElement* parent = new HTMLTreeElement(root, root);
	HTMLTreeElement* child = new HTMLTreeElement(root, parent);
	root->addChild(parent);
	parent->addChild(child);
	root->getChildren();

	delete child;
	delete parent;
	delete root;
}
TEST(HTML_HTMLTreeElement, getContents) {
	HTMLTreeElement* root = new HTMLTreeElement();
	root->getContents();
	delete root;
}
TEST(HTML_HTMLTreeElement, getAttributes) {
	HTMLTreeElement* root = new HTMLTreeElement();
	root->getAttributes();
	delete root;
}
TEST(HTML_HTMLTreeElement, getTagName) {
	HTMLTreeElement* root = new HTMLTreeElement();
	root->getTagName();
	delete root;
}
TEST(HTML_HTMLTreeElement, getFormatting) {
	HTMLTreeElement* root = new HTMLTreeElement();
	root->getFormatting();
	delete root;
}
TEST(HTML_HTMLTreeElement, isText) {
	HTMLTreeElement* root = new HTMLTreeElement();
	root->isText();
	delete root;
}
TEST(HTML_HTMLTreeElement, isRoot) {
	HTMLTreeElement* root = new HTMLTreeElement();
	root->isRoot();
	delete root;
}
TEST(HTML_HTMLTreeElement, isEmpty) {
	HTMLTreeElement* root = new HTMLTreeElement();
	root->isEmpty();
	delete root;
}
TEST(HTML_HTMLTreeElement, isInitialized) {
	HTMLTreeElement* root = new HTMLTreeElement();
	root->isInitialized();
	delete root;
}
TEST(HTML_HTMLTreeElement, hasAttributes) {
	HTMLTreeElement* root = new HTMLTreeElement();
	root->hasAttributes();
	delete root;
}
TEST(HTML_HTMLTreeElement, hasChildren) {
	HTMLTreeElement* root = new HTMLTreeElement();
	root->hasChildren();
	delete root;
}
TEST(HTML_HTMLTreeElement, makeRoot) {
	HTMLTreeElement* root = new HTMLTreeElement();
	root->makeRoot();
	delete root;
}
TEST(HTML_HTMLTreeElement, addChild) {
	HTMLTreeElement* root = new HTMLTreeElement();
	HTMLTreeElement* child = new HTMLTreeElement(root, root);
	root->addChild(child);
	delete child;
	delete root;
}
TEST(HTML_HTMLTreeElement, deleteChild) {
	HTMLTreeElement* root = new HTMLTreeElement();
	HTMLTreeElement* child = new HTMLTreeElement(root, root);
	root->addChild(child);
	root->deleteChild(child);
	delete child;
	delete root;
}
TEST(HTML_HTMLTreeElement, addAttribute) {
	Attribute attribute;
	HTMLTreeElement* root = new HTMLTreeElement();
	root->addAttribute(attribute);
	delete root;
}
TEST(HTML_HTMLTreeElement, removeAttribute) {
	Attribute attribute;
	HTMLTreeElement* root = new HTMLTreeElement();
	root->addAttribute(attribute);
	root->removeAttribute(attribute);
	delete root;
}
TEST(HTML_HTMLTreeElement, setContents) {
	std::string contents = "contents";
	HTMLTreeElement* root = new HTMLTreeElement();
	root->setContents(contents);
	delete root;
}
TEST(HTML_HTMLTreeElement, setFormatting) {
	Formatting formatting;
	HTMLTreeElement* root = new HTMLTreeElement();
	root->setFormatting(formatting);
	delete root;
}
TEST(HTML_HTMLTreeElement, setParent) {
	HTMLTreeElement* root = new HTMLTreeElement();
	root->makeRoot();
	HTMLTreeElement* newParent = new HTMLTreeElement();
	newParent->makeRoot();
	HTMLTreeElement* child = new HTMLTreeElement(root, root);
	child->setParent(newParent);
	delete child;
	delete newParent;
	delete root;
}
TEST(HTML_HTMLTreeElement, setRoot) {
	HTMLTreeElement* root = new HTMLTreeElement();
	root->makeRoot();
	HTMLTreeElement* newRoot = new HTMLTreeElement();
	newRoot->makeRoot();
	HTMLTreeElement* child = new HTMLTreeElement(root, root);
	child->setRoot(newRoot);
	delete child;
	delete newRoot;
	delete root;
}
TEST(HTML_HTMLTreeElement, setTagName) {
	HTMLTreeElement* root = new HTMLTreeElement();
	root->setTagName();
	delete root;
}

} /* namespace HTML */
