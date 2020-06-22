//
// Created by agustin on 22/6/20.
//

#include "MapTests.h"

#include "../Map/Map.h"
#include "../Map/Tile.h"

////////////////////////PUBLIC/////////////////////////

void MapTests::_fillEmptyMap(Map &map, int iSize, int jSize) {
    for (int i = 0; i < iSize; ++i) {
        map.tiles.emplace_back();
        for (int j = 0; j < jSize; ++j) {
            map.tiles[i].emplace_back(false, FLOOR_TYPE_GRASS);
        }
    }
}

////////////////////////PUBLIC/////////////////////////

bool MapTests::testAvailableMapHasAvailableTiles() {
    Map map;
    int mapXSize = 50;
    int mapYSize = 50;
    _fillEmptyMap(map, mapXSize, mapYSize);
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
    _fillEmptyMap(map, mapXSize, mapYSize);
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
            if (j % 2 == 0) {
                if (!isCity) {
                    return false;
                }
            } else {
                if (isCity) {
                    return false;
                }
            }
            if (j % 3 == 0) {
                if (isGrass) {
                    return false;
                }
            } else {
                if (!isGrass) {
                    return false;
                }
            }
        }
    }
    return true;
}

bool MapTests::testAddedItemToMap() {
    //Agrega el item al tile que se encuentra en la coordenada recibida apropiandose del shared_ptr,
    //si la coordenada es invalida tira invalid_argument y no se apropia del puntero
    void addItemsToTile(std::shared_ptr<Item>&& item, Coordinate position);

    Map map;
    int mapXSize = 50;
    int mapYSize = 50;
    _fillEmptyMap(map, mapXSize, mapYSize);


    return false;
}
