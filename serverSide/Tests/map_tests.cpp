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

TEST_CASE("Test List Items On Sale On Empty Tile") {
    REQUIRE(MapTests::testListOnEmptyTileReturnsEmptyList());
}

TEST_CASE("Test List Items On Sale On Empty Map") {
    REQUIRE(MapTests::testListOnEmptyMapReturnsEmptyList());
}

TEST_CASE("Test Get Targets On Empty Map Returns Empty List") {
    REQUIRE(MapTests::testGetTargetsOnEmptyMapReturnsEmptyList());
}

TEST_CASE("Test Get Targets On Map With Player Returns List With One Element") {
    REQUIRE(MapTests::testGetTargetsOnMapWithPlayerReturnsListWithOneElement());
}

TEST_CASE("Test Get Targets On Map With Dead Player Returns Empty List") {
    REQUIRE(MapTests::testGetTargetsOnMapWithDeadPlayerReturnsEmptyList());
}

TEST_CASE("Test Position With Player Is Occupied") {
    REQUIRE(MapTests::testPositionWithPlayerIsOccupied());
}

TEST_CASE("Test Position With Monster Is Occupied") {
    REQUIRE(MapTests::testPositionWithMonsterIsOccupied());
}


TEST_CASE("Test Withdraw On Empty Tile Gets No Item") {
    REQUIRE(MapTests::testWithdrawOnEmptyTileGetsNoItem());
}

TEST_CASE("Test Withdraw On Empty Map Gets No Item") {
    REQUIRE(MapTests::testWithdrawOnEmptyMapGetsNoItem());
}


TEST_CASE("Test Deposit Existant Item On Empty Tile Gets No Item") {
    REQUIRE(MapTests::testDepositExistentItemOnEmptyTileGetsNoItem());
}

TEST_CASE("Test Deposit Existant Item On Empty Map Gets No Item") {
    REQUIRE(MapTests::testDepositExistentItemOnEmptyMapGetsNoItem());
}

TEST_CASE("Test Buy Item From Empty Tile Gets No Item") {
    REQUIRE(MapTests::testBuyItemFromEmptyTileGetsNoItem());
}

TEST_CASE("Test Buy Item From Empty Map Gets No Item") {
    REQUIRE(MapTests::testBuyItemFromEmptyMapGetsNoItem());
}

TEST_CASE("Test Sell Existent Item To Empty Tile Gets No Item") {
    REQUIRE(MapTests::testSellExistentItemToEmptyTileGetsNoItem());
}

TEST_CASE("Test Sell Existent Item To Empty Map Gets No Item") {
    REQUIRE(MapTests::testSellExistentItemToEmptyMapGetsNoItem());
}

TEST_CASE("Test Move Entity") {
    REQUIRE(MapTests::testMoveEntity());
}

TEST_CASE("Test Remove Entity On Empty Tile Leaves No Entity") {
    REQUIRE(MapTests::testRemoveEntityOnEmptyTileLeavesNoEntity());
}