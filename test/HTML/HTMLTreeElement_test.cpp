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

TEST(HTMLTreeElement, HTMLTreeElement) {
	HTMLTreeElement* root = new HTMLTreeElement();
	root->makeRoot();
	HTMLTreeElement* child = new HTMLTreeElement(root, root);
	delete child;
	delete root;
}
TEST(HTMLTreeElement, getRoot) {
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

TEST(HTMLTreeElement, getParent) {
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

TEST(HTMLTreeElement, getChildren) {
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
TEST(HTMLTreeElement, getContents) {
	HTMLTreeElement* root = new HTMLTreeElement();
	root->getContents();
	delete root;
}
TEST(HTMLTreeElement, getAttributes) {
	HTMLTreeElement* root = new HTMLTreeElement();
	root->getAttributes();
	delete root;
}
TEST(HTMLTreeElement, getTagName) {
	HTMLTreeElement* root = new HTMLTreeElement();
	root->getTagName();
	delete root;
}
TEST(HTMLTreeElement, getFormatting) {
	HTMLTreeElement* root = new HTMLTreeElement();
	root->getFormatting();
	delete root;
}
TEST(HTMLTreeElement, isText) {
	HTMLTreeElement* root = new HTMLTreeElement();
	root->isText();
	delete root;
}
TEST(HTMLTreeElement, isRoot) {
	HTMLTreeElement* root = new HTMLTreeElement();
	root->isRoot();
	delete root;
}
TEST(HTMLTreeElement, isEmpty) {
	HTMLTreeElement* root = new HTMLTreeElement();
	root->isEmpty();
	delete root;
}
TEST(HTMLTreeElement, isInitialized) {
	HTMLTreeElement* root = new HTMLTreeElement();
	root->isInitialized();
	delete root;
}
TEST(HTMLTreeElement, hasAttributes) {
	HTMLTreeElement* root = new HTMLTreeElement();
	root->hasAttributes();
	delete root;
}
TEST(HTMLTreeElement, hasChildren) {
	HTMLTreeElement* root = new HTMLTreeElement();
	root->hasChildren();
	delete root;
}
TEST(HTMLTreeElement, makeRoot) {
	HTMLTreeElement* root = new HTMLTreeElement();
	root->makeRoot();
	delete root;
}
TEST(HTMLTreeElement, addChild) {
	HTMLTreeElement* root = new HTMLTreeElement();
	HTMLTreeElement* child = new HTMLTreeElement(root, root);
	root->addChild(child);
	delete child;
	delete root;
}
TEST(HTMLTreeElement, deleteChild) {
	HTMLTreeElement* root = new HTMLTreeElement();
	HTMLTreeElement* child = new HTMLTreeElement(root, root);
	root->addChild(child);
	root->deleteChild(child);
	delete child;
	delete root;
}
TEST(HTMLTreeElement, addAttribute) {
	Attribute attribute;
	HTMLTreeElement* root = new HTMLTreeElement();
	root->addAttribute(attribute);
	delete root;
}
TEST(HTMLTreeElement, removeAttribute) {
	Attribute attribute;
	HTMLTreeElement* root = new HTMLTreeElement();
	root->addAttribute(attribute);
	root->removeAttribute(attribute);
	delete root;
}
TEST(HTMLTreeElement, setContents) {
	std::string contents = "contents";
	HTMLTreeElement* root = new HTMLTreeElement();
	root->setContents(contents);
	delete root;
}
TEST(HTMLTreeElement, setFormatting) {
	Formatting formatting;
	HTMLTreeElement* root = new HTMLTreeElement();
	root->setFormatting(formatting);
	delete root;
}
TEST(HTMLTreeElement, setParent) {
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
TEST(HTMLTreeElement, setRoot) {
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
TEST(HTMLTreeElement, setTagName) {
	HTMLTreeElement* root = new HTMLTreeElement();
	root->setTagName();
	delete root;
}

} /* namespace HTML */
