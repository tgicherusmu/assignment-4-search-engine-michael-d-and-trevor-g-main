//
// Created by Michael Deweese on 4/30/23.
//
#define CATCH_CONFIG_MAIN
#include "IndexHandler.h"
#include "FilterEntry.h"
#include "catch2/catch.hpp"
// add includes

    TEST_CASE("Check that AvlTree<IndexEntry> TreeIndex works", "[TreeIndex]"){
        AvlTree<IndexEntry> TreeIndex;
        REQUIRE(TreeIndex.isEmpty() == true);

        TreeIndex.prettyPrintTree();
        TreeIndex.makeEmpty();
        TreeIndex.clearElements();
        TreeIndex.getEntries();

    SECTION("Check that AvlTree<FilterEntry> PeopleTree works", "[PeopleTree]"){
        AvlTree<FilterEntry> PeopleTree;
        REQUIRE(PeopleTree.isEmpty() == true);
        
        PeopleTree.prettyPrintTree();
        PeopleTree.makeEmpty();
        PeopleTree.clearElements();
        PeopleTree.getEntries();
    }
    
    SECTION("Check that AvlTree<FilterEntry> OrgsTree; works", "[OrgsTree]"){
        AvlTree<FilterEntry> OrgsTree;
        REQUIRE(OrgsTree.isEmpty() == true);
        
        OrgsTree.prettyPrintTree();
        OrgsTree.makeEmpty();
        OrgsTree.clearElements();
        OrgsTree.getEntries();
    }
    }

