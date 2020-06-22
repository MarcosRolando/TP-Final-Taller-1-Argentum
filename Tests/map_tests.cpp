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