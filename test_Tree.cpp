//
// Created by Michael Deweese on 4/29/23.
//
#define CATCH_CONFIG_MAIN
#include "Tree.h"
#include "FilterEntry.h"
#include "catch2/catch.hpp"

TEST_CASE("Test AvlTree class with integers")
{
    AvlTree<int> tree;
    REQUIRE(tree.isEmpty() == true);
    tree.insert(10);
    REQUIRE(tree.isEmpty() == false);
    tree.insert(20);
    REQUIRE(tree.contains(20) == true);
    tree.remove(20);
    REQUIRE(tree.contains(20) == false);

    // Test persistence
    std::ofstream out("test.txt");
    out << tree;
    out.close();

    AvlTree<int> newTree;
    std::ifstream in("test.txt");
    in >> newTree;
    in.close();

    REQUIRE(newTree.contains(10) == true);
}
