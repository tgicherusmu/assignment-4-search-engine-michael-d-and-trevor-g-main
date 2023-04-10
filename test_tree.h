#define CATCH_CONFIG_MAIN
#include "Tree.h"
// #include "catch2/catch.hpp"
// #include "utilities/DSStack_DSList.h"
// #include "utilities/DSStack_vector.h"
​
// add includes
​
TEST_CASE("Check that DSList works", "[DSList]") {
    SECTION("Testing push_back") {
        DSList<int> testList;
        REQUIRE(testList.empty() == true);
        testList.push_back(0);
        testList.push_back(1);
        testList.push_back(2);
        testList.push_back(3);
        testList.push_back(4);
​
        REQUIRE(testList.size() == 5);
        REQUIRE(testList.front() == 0);
        REQUIRE(testList.back() == 4);
    }
​
    SECTION("Testing push_front") {
        DSList<int> testList;
        REQUIRE(testList.empty() == true);
        testList.push_front(0);
        testList.push_front(1);
        testList.push_front(2);
        testList.push_front(3);
        testList.push_front(4);
​
        REQUIRE(testList.size() == 5);
        REQUIRE(testList.front() == 4);
        REQUIRE(testList.back() == 0);
        REQUIRE(testList.empty() == false);
    }
​
    SECTION("Testing clear") {
        DSList<int> testList;
        testList.push_back(0);
        testList.push_back(1);
        testList.push_back(2);
        testList.push_back(3);
        testList.push_back(4);
​
        REQUIRE(testList.size() == 5);
        REQUIRE(testList.empty() == false);
        testList.clear();
        REQUIRE(testList.size() == 0);
        REQUIRE(testList.empty() == true);
    }
​
    SECTION("Testing contains") {
        DSList<int> testList;
        testList.push_back(0);
        testList.push_back(1);
        testList.push_back(2);
        testList.push_back(3);
        testList.push_back(4);
​
        REQUIRE(testList.contains(0) == true);
        REQUIRE(testList.contains(1) == true);
        REQUIRE(testList.contains(2) == true);
        REQUIRE(testList.contains(3) == true);
        REQUIRE(testList.contains(4) == true);
        testList.clear();
        REQUIRE(testList.contains(0) == false);
        REQUIRE(testList.contains(1) == false);
        REQUIRE(testList.contains(2) == false);
        REQUIRE(testList.contains(3) == false);
        REQUIRE(testList.contains(4) == false);
    }
​
    SECTION("Testing pop_front") {
        DSList<int> testList;
        testList.push_back(0);
        testList.push_back(1);
        testList.push_back(2);
        testList.push_back(3);
        testList.push_back(4);
​
        REQUIRE(testList.contains(0) == true);
        REQUIRE(testList.contains(1) == true);
        REQUIRE(testList.contains(2) == true);
        REQUIRE(testList.contains(3) == true);
        REQUIRE(testList.contains(4) == true);
        REQUIRE(testList.size() == 5);
        testList.pop_front();
        REQUIRE(testList.contains(0) == false);
        REQUIRE(testList.contains(1) == true);
        REQUIRE(testList.contains(2) == true);
        REQUIRE(testList.contains(3) == true);
        REQUIRE(testList.contains(4) == true);
        REQUIRE(testList.front() == 1);
        REQUIRE(testList.back() == 4);
        REQUIRE(testList.size() == 4);
    }
​
    SECTION("Testing pop_back") {
        DSList<int> testList;
        testList.push_back(0);
        testList.push_back(1);
        testList.push_back(2);
        testList.push_back(3);
        testList.push_back(4);
​
        REQUIRE(testList.contains(0) == true);
        REQUIRE(testList.contains(1) == true);
        REQUIRE(testList.contains(2) == true);
        REQUIRE(testList.contains(3) == true);
        REQUIRE(testList.contains(4) == true);
        REQUIRE(testList.size() == 5);
        testList.pop_back();
        REQUIRE(testList.contains(0) == true);
        REQUIRE(testList.contains(1) == true);
        REQUIRE(testList.contains(2) == true);
        REQUIRE(testList.contains(3) == true);
        REQUIRE(testList.contains(4) == false);
        REQUIRE(testList.front() == 0);
        REQUIRE(testList.back() == 3);
        REQUIRE(testList.size() == 4);
    }
}
​