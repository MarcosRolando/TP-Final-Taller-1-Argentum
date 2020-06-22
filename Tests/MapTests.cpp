//
// Created by agustin on 22/6/20.
//

#include "MapTests.h"

#include <iostream>
#include "../Map/Map.h"
#include "../Items/Miscellaneous/Gold.h"
#include "../Items/Miscellaneous/HealthPotion.h"
#include "../Items/Miscellaneous/ManaPotion.h"
#include "../Items/Defense/Head.h"
#include "../Items/Defense/Shield.h"
#include "../Items/Defense/Chest.h"
#include "../Items/Attack/Weapon.h"

////////////////////////PUBLIC/////////////////////////

void MapTests::_fillEmptyMap(Map &map, int iSize, int jSize, bool isCity) {
    for (int i = 0; i < iSize; ++i) {
        map.tiles.emplace_back();
        for (int j = 0; j < jSize; ++j) {
            map.tiles[i].emplace_back(isCity, FLOOR_TYPE_GRASS);
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
    _fillEmptyMap(map, mapXSize, mapYSize, true);
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

bool MapTests::testAddedItemsToMap() {
    Map map;
    int mapXSize = 50;
    int mapYSize = 50;
    _fillEmptyMap(map, mapXSize, mapYSize);
    std::list<std::shared_ptr<Item>> items;
    items.emplace_back(new Gold(5));
    items.emplace_back(new HealthPotion());
    items.emplace_back(new ManaPotion());
    items.emplace_back(new Head(GameType::MAGIC_HAT));
    items.emplace_back(new Head(GameType::NO_HELMET));
    items.emplace_back(new Shield(GameType::IRON_SHIELD));
    items.emplace_back(new Chest(GameType::PLATE_ARMOR));
    items.emplace_back(new Chest(GameType::COMMON_CLOTHING));
    items.emplace_back(new Weapon(GameType::LONGSWORD));
    items.emplace_back(new Weapon(GameType::FIST));

    Configuration& config = Configuration::getInstance();

    std::vector<std::string> itemsNames = {config.configGetGoldName(), config.configPotionData(GameType::HEALTH_POTION).name,
                                         config.configPotionData(GameType::MANA_POTION).name,
                                         config.configClothingData(GameType::MAGIC_HAT).name,
                                         config.configClothingData(GameType::NO_HELMET).name,
                                         config.configClothingData(GameType::IRON_SHIELD).name,
                                         config.configClothingData(GameType::PLATE_ARMOR).name,
                                         config.configClothingData(GameType::COMMON_CLOTHING).name,
                                         config.configWeaponData(GameType::LONGSWORD).name,
                                         config.configWeaponData(GameType::FIST).name};
    map.addItemsToTile(std::move(items), {1, 1});
    int i = 0;
    for (const auto & item: map.tiles[1][1].items) {
        if (itemsNames[i] != item->getName()) {
            return false;
        }
        i++;
    }
    return true;
}

bool MapTests::testAddedGoldToMap() {
    Map map;
    int mapXSize = 50;
    int mapYSize = 50;
    _fillEmptyMap(map, mapXSize, mapYSize);
    std::shared_ptr<Gold> gold(new Gold(1000));
    map.addItemsToTile(std::move(gold), {1, 1});
    return Configuration::getInstance().configGetGoldName() == map.tiles[1][1].items.front()->getName();
}
