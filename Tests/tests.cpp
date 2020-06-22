//
// Created by marcos on 22/6/20.
//

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("Sin Mapa Test") {
    int x = 3;
    int y = 4;
    REQUIRE((x + y) == 8);
}
