//
// Created by agustin on 22/6/20.
//

#include "MapTests.h"

#include "../Map/Map.h"
#include "../Map/Tile.h"

bool MapTests::testAvailableMapHasAvailableTiles() {
    Map map;
    int mapXSize = 50;
    int mapYSize = 50;
    for (int i = 0; i < mapXSize; ++i) {
        map.tiles.emplace_back();
        for (int j = 0; j < mapYSize; ++j) {
            map.tiles[i].emplace_back(false, FLOOR_TYPE_GRASS);
        }
    }
    for (int i = 0; i < mapXSize; ++i) {
        for (int j = 0; j < mapYSize; ++j) {
            if (!map.tiles[i][j].isAvailable()) {
                return false;
            }
        }
    }
    return true;
}

bool MapTests::testCityMapHasCityTiles() {
    Map map;
    int mapXSize = 50;
    int mapYSize = 50;
    for (int i = 0; i < mapXSize; ++i) {
        map.tiles.emplace_back();
        for (int j = 0; j < mapYSize; ++j) {
            map.tiles[i].emplace_back(true, FLOOR_TYPE_GRASS);
        }
    }
    for (int i = 0; i < mapXSize; ++i) {
        for (int j = 0; j < mapYSize; ++j) {
            if (!map.tiles[i][j].isInCity()) {
                return false;
            }
        }
    }
    return true;
}

bool MapTests::testMixedCityAndUnavailableTiles() {
    Map map;
    int mapXSize = 50;
    int mapYSize = 50;
    bool isCity;
    bool isGrass;
    FloorType floorType;
    for (int i = 0; i < mapXSize; ++i) {
        map.tiles.emplace_back();
        for (int j = 0; j < mapYSize; ++j) {
            isCity = (j % 2 == 0);
            if (j % 3 == 0) {
                floorType = FLOOR_TYPE_WALL;
            } else {
                floorType = FLOOR_TYPE_GRASS;
            }
            map.tiles[i].emplace_back(isCity, floorType);
        }
    }
    for (int i = 0; i < mapXSize; ++i) {
        for (int j = 0; j < mapYSize; ++j) {
            isCity = map.tiles[i][j].isInCity();
            isGrass = map.tiles[i][j].isAvailable();
            if ((j % 2 == 0) && (!isCity)) {
                return false;
            } else {
                if (isCity) {
                    return false;
                }
            }
            if ((j % 3 == 0) && (!isGrass)) {
                return false;
            } else {
                if (isGrass) {
                    return false;
                }
            }
        }
    }
    return true;
}
