//
// Created by marcos on 22/6/20.
//

#include "catch.hpp"
#include "ItemTests.h"

TEST_CASE("Initial Item Values Test") {
    REQUIRE(ItemTests::testInitialValues());
}

TEST_CASE("It Is Not Gold Test") {
    REQUIRE(ItemTests::testAreNonGoldItemsGold());
}

TEST_CASE("It Is Gold Test") {
    REQUIRE(ItemTests::testIsGoldItemGold());
}

TEST_CASE("Load All Items Names Correctly Test") {
    REQUIRE(ItemTests::testCorrectItemsNames());
}

TEST_CASE("Correct Gold Amount Test") {
    REQUIRE(ItemTests::testCorrectGoldAmount());
}