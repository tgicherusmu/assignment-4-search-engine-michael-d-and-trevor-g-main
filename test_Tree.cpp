//
// Created by Michael Deweese on 4/29/23.
//
#define CATCH_CONFIG_MAIN
#include "Tree.h"
#include "FilterEntry.h"
#include "catch2/catch.hpp"
// add includes

TEST_CASE("Test AvlTree", "[AvlTree]")
{
    AvlTree<int> t;
    REQUIRE(t.isEmpty() == true);
}
TEST_CASE("Check that AVLNode and AVLTree::Tree works", "[AVLTree::Tree]") {
// add test cases (create lists and specify what the expected output is)

SECTION("Check that AVLTree::Tree works", "[AVLTree::Tree]"){
        AvlTree<int> rhs;
        REQUIRE(rhs.isEmpty() == true);
        rhs.insert(1);
        rhs.insert(2);
        rhs.insert(3);
        rhs.insert(4);

        rhs.prettyPrintTree();
        rhs.makeEmpty();
        rhs.clearElements();
        rhs.getEntries();
}
