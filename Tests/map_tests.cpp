//
// Created by agustin on 22/6/20.
//

#include "catch.hpp"
#include "MapTests.h"

TEST_CASE("Test Available Map Has Available Tiles") {
    REQUIRE(MapTests::testAvailableMapHasAvailableTiles());
}

TEST_CASE("Test City Map Has City Tiles") {
    REQUIRE(MapTests::testCityMapHasCityTiles());
}

TEST_CASE("Test Mixed City And Unavailable Tiles") {
    REQUIRE(MapTests::testMixedCityAndUnavailableTiles());
}

TEST_CASE("Test Added Items To Map") {
    REQUIRE(MapTests::testAddedItemsToMap());
}

TEST_CASE("Test Added Gold To Map") {
    REQUIRE(MapTests::testAddedGoldToMap());
}

TEST_CASE("Test Added Multiple Golds To Map With List") {
    REQUIRE(MapTests::testAddedMultipleGoldsToMapWithList());
}

TEST_CASE("Test Added Multiple Golds To Map Without List") {
    REQUIRE(MapTests::testAddedMultipleGoldsToMapWithoutList());
}

TEST_CASE("Test Added Multiple Items Lists To Map") {
    REQUIRE(MapTests::testAddedMultipleItemsListsToMap());
}