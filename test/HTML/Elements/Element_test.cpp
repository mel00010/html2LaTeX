/*******************************************************************************
 * Element_test.cpp
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

#include <gtest/gtest.h>

#include <HTML/Elements/Element.hpp>

namespace HTML {
namespace Elements {
TEST(HTML_Elements_Element, Element) {
	Element* root = new Element();
	Element* parent = new Element(root, root);
	Element* child = new Element(root, parent);

	EXPECT_EQ(nullptr, root->getRoot());
	EXPECT_EQ(nullptr, root->getParent());
	EXPECT_EQ(root, child->getRoot());
	EXPECT_EQ(parent, child->getParent());

	delete child;
	delete parent;
	delete root;

}

TEST(HTML_Elements_Element, getRoot) {
	Element* root = new Element();
	Element* child = new Element(root, nullptr);

	EXPECT_EQ(nullptr, root->getRoot());
	EXPECT_EQ(root, child->getRoot());

	delete child;
	delete root;
}

TEST(HTML_Elements_Element, getParent) {
	Element* parent = new Element();
	Element* child = new Element(parent, parent);

	EXPECT_EQ(nullptr, parent->getParent());
	EXPECT_EQ(parent, child->getParent());

	delete child;
	delete parent;
}

TEST(HTML_Elements_Element, getChildren) {
	Element* child1 = new Element();
	Element* child2 = new Element();
	Element* root = new Element(nullptr, nullptr, std::vector<Element*>( { child1, child2 }));

	EXPECT_EQ(std::vector<Element*>( { child1, child2 }), root->getChildren());

	delete root;
	delete child2;
	delete child1;
}

TEST(HTML_Elements_Element, isText) {
	Element* trueCase = new Element(nullptr, nullptr, std::vector<Element*>( { }), true);
	Element* falseCase = new Element(nullptr, nullptr, std::vector<Element*>( { }), false);

	EXPECT_TRUE(trueCase->isText());
	EXPECT_FALSE(falseCase->isText());

	delete falseCase;
	delete trueCase;
}

TEST(HTML_Elements_Element, isRoot) {
	Element* root = new Element();
	Element* child = new Element(root, root);

	root->makeRoot();

	EXPECT_TRUE(root->isRoot());
	EXPECT_FALSE(child->isRoot());

	delete child;
	delete root;
}

TEST(HTML_Elements_Element, isInitialized) {
	Element* falseCase = new Element();
	Element* trueCase = new Element(falseCase, falseCase);

	EXPECT_TRUE(trueCase->isInitialized());
	EXPECT_FALSE(falseCase->isInitialized());

	delete trueCase;
	delete falseCase;
}

TEST(HTML_Elements_Element, hasChildren) {
	Element* child1 = new Element();
	Element* child2 = new Element();
	Element* trueCase = new Element(nullptr, nullptr, std::vector<Element*>( { child1, child2 }));
	Element* falseCase = new Element(nullptr, nullptr, std::vector<Element*>( { }));

	EXPECT_TRUE(trueCase->hasChildren());
	EXPECT_FALSE(falseCase->hasChildren());

	delete falseCase;
	delete trueCase;
	delete child2;
	delete child1;
}

TEST(HTML_Elements_Element, makeRoot) {
	Element* root = new Element();

	EXPECT_FALSE(root->isRoot());

	root->makeRoot();

	EXPECT_TRUE(root->isRoot());

	delete root;
}

TEST(HTML_Elements_Element, addChild) {
	Element* root = new Element();
	Element* child1 = new Element();
	Element* child2 = new Element();

	EXPECT_EQ(std::vector<Element*>( { }), root->getChildren());
	EXPECT_TRUE(root->addChild(child1));
	EXPECT_EQ(std::vector<Element*>( { child1 }), root->getChildren());
	EXPECT_TRUE(root->addChild(child2));
	EXPECT_EQ(std::vector<Element*>( { child1, child2 }), root->getChildren());
	EXPECT_FALSE(root->addChild(child1));
	EXPECT_EQ(std::vector<Element*>( { child1, child2 }), root->getChildren());

	delete child2;
	delete child1;
	delete root;
}

TEST(HTML_Elements_Element, deleteChild) {
	Element* child1 = new Element();
	Element* child2 = new Element();
	Element* root = new Element(nullptr, nullptr, std::vector<Element*>( { child1, child2 }));


	EXPECT_EQ(std::vector<Element*>( { child1, child2 }), root->getChildren());
	EXPECT_TRUE(root->deleteChild(child2));
	EXPECT_EQ(std::vector<Element*>( { child1 }), root->getChildren());
	EXPECT_TRUE(root->deleteChild(child1));
	EXPECT_EQ(std::vector<Element*>( { }), root->getChildren());
	EXPECT_FALSE(root->deleteChild(child1));

	delete root;
	delete child2;
	delete child1;
}

TEST(HTML_Elements_Element, setParent) {
	Element* old_parent = new Element();
	Element* new_parent = new Element();
	Element* child = new Element(old_parent, old_parent);

	EXPECT_EQ(old_parent, child->getParent());

	child->setParent(new_parent);

	EXPECT_EQ(new_parent, child->getParent());

	delete child;
	delete new_parent;
	delete old_parent;
}

TEST(HTML_Elements_Element, setRoot) {
	Element* old_root = new Element();
	Element* new_root = new Element();
	Element* child = new Element(old_root, old_root);

	EXPECT_EQ(old_root, child->getRoot());

	child->setRoot(new_root);

	EXPECT_EQ(new_root, child->getRoot());

	delete child;
	delete new_root;
	delete old_root;
}

} /* namespace Elements */
} /* namespace HTML */

