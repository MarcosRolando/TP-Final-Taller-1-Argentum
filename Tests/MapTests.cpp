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
#include "../Entities/Player.h"
#include "../Entities/Monster.h"
#include "../Game/Game.h"
#include "../Entities/Citizens/Storage.h"

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

bool MapTests::testAddedMultipleGoldsToMapWithList() {
    Map map;
    int mapXSize = 50;
    int mapYSize = 50;
    _fillEmptyMap(map, mapXSize, mapYSize);
    std::list<std::shared_ptr<Item>> items;
    items.emplace_back(new Gold(1000));
    items.emplace_back(new Gold(1000));
    map.addItemsToTile(std::move(items), {1, 1});
    return (Configuration::getInstance().configGetGoldName() == map.tiles[1][1].items.front()->getName()) &&
           (Configuration::getInstance().configGetGoldName() == map.tiles[1][1].items.back()->getName());
}

bool MapTests::testAddedMultipleGoldsToMapWithoutList() {
    Map map;
    int mapXSize = 50;
    int mapYSize = 50;
    _fillEmptyMap(map, mapXSize, mapYSize);
    std::shared_ptr<Gold> gold(new Gold(1000));
    map.addItemsToTile(std::move(gold), {1, 1});
    gold.reset(new Gold(1000));
    map.addItemsToTile(std::move(gold), {1, 1});
    return (Configuration::getInstance().configGetGoldName() == map.tiles[1][1].items.front()->getName()) &&
           (Configuration::getInstance().configGetGoldName() == map.tiles[1][1].items.back()->getName());
}

bool MapTests::testAddedMultipleItemsListsToMap() {
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
                                           config.configWeaponData(GameType::FIST).name,
                                           config.configGetGoldName(), config.configPotionData(GameType::HEALTH_POTION).name,
                                           config.configPotionData(GameType::MANA_POTION).name,
                                           config.configClothingData(GameType::MAGIC_HAT).name,
                                           config.configClothingData(GameType::NO_HELMET).name,
                                           config.configClothingData(GameType::IRON_SHIELD).name,
                                           config.configClothingData(GameType::PLATE_ARMOR).name,
                                           config.configClothingData(GameType::COMMON_CLOTHING).name,
                                           config.configWeaponData(GameType::LONGSWORD).name,
                                           config.configWeaponData(GameType::FIST).name};

    map.addItemsToTile(std::move(items), {1, 1});

    items.clear();
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


bool MapTests::testGetTargetsOnEmptyMapReturnsEmptyList() {
    Map map;
    int mapXSize = 50;
    int mapYSize = 50;
    _fillEmptyMap(map, mapXSize, mapYSize);
    std::vector<Coordinate> targets;
    map.getTargets({25, 25}, 25, targets);
    return targets.empty();
}

bool MapTests::testGetTargetsOnMapWithPlayerReturnsListWithOneElement() {
    Map map;
    int mapXSize = 50;
    int mapYSize = 50;
    _fillEmptyMap(map, mapXSize, mapYSize);
    Game game;
    std::shared_ptr<Player> player(new Player(game, GameType::HUMAN, GameType::WIZARD, 1, 0,
                                          {25, 25}, "Name"));
    map.addEntity({25, 25}, player);
    std::vector<Coordinate> targets;
    map.getTargets({25, 25}, 25, targets);
    return (targets.size() == 1) && (targets[0].jPosition == 25) && (targets[0].iPosition == 25);
}

bool MapTests::testGetTargetsOnMapWithDeadPlayerReturnsEmptyList() {
    Map map;
    int mapXSize = 50;
    int mapYSize = 50;
    _fillEmptyMap(map, mapXSize, mapYSize);
    Game game;
    std::shared_ptr<Player> player(new Player(game, GameType::HUMAN, GameType::WIZARD, 1, 0,
                                              {25, 25}, "Name"));
    player->stats.currentLife = 0;
    map.addEntity({25, 25}, player);
    std::vector<Coordinate> targets;
    map.getTargets({25, 25}, 25, targets);
    return targets.empty();
}

bool MapTests::testPositionWithPlayerIsOccupied() {
    Map map;
    int mapXSize = 50;
    int mapYSize = 50;
    _fillEmptyMap(map, mapXSize, mapYSize);
    Game game;
    std::shared_ptr<Player> player(new Player(game, GameType::HUMAN, GameType::WIZARD, 1, 0,
                                              {25, 25}, "Name"));
    map.addEntity({25, 25}, std::move(player));
    return !map.tiles[25][25].isAvailable();
}

bool MapTests::testPositionWithMonsterIsOccupied() {
    Map map;
    int mapXSize = 50;
    int mapYSize = 50;
    _fillEmptyMap(map, mapXSize, mapYSize);
    Game game;
    std::shared_ptr<Monster> monster(new Monster(game, {25, 25}, GameType::SKELETON));
    map.addEntity({25, 25}, std::move(monster));
    return !map.tiles[25][25].isAvailable();
}

bool MapTests::testListOnEmptyTileReturnsEmptyList() {
    Map map;
    int mapXSize = 50;
    int mapYSize = 50;
    _fillEmptyMap(map, mapXSize, mapYSize);
    std::list<ProductData> products;
    Game game;
    Player player(game, GameType::HUMAN, GameType::WIZARD, 1, 0,
                  {0, 0}, "Name");
    map.list(player, products, {5, 5});
    return products.empty();
}

bool MapTests::testListOnEmptyMapReturnsEmptyList() {
    Map map;
    int mapXSize = 50;
    int mapYSize = 50;
    _fillEmptyMap(map, mapXSize, mapYSize);
    std::list<ProductData> products;
    Game game;
    Player player(game, GameType::HUMAN, GameType::WIZARD, 1, 0,
                  {0, 0}, "Name");
    for (int i = 0; i < mapXSize; ++i) {
        for (int j = 0; j < mapYSize; ++j) {
            map.list(player, products, {i, j});
            if (!products.empty()) {
                return false;
            }
            products.clear();
        }
    }
    return true;
}

bool MapTests::testWithdrawOnEmptyTileGetsNoItem() {
    Map map;
    int mapXSize = 50;
    int mapYSize = 50;
    _fillEmptyMap(map, mapXSize, mapYSize);
    Game game;
    Player player(game, GameType::HUMAN, GameType::WIZARD, 1, 0,
                  {0, 0}, "Name");
    map.withdraw(player, "product", {5, 5});
    return player.inventory.storedItemsAmount == 0;
}

bool MapTests::testWithdrawOnEmptyMapGetsNoItem() {
    Map map;
    int mapXSize = 50;
    int mapYSize = 50;
    _fillEmptyMap(map, mapXSize, mapYSize);
    Game game;
    Player player(game, GameType::HUMAN, GameType::WIZARD, 1, 0,
                  {0, 0}, "Name");
    for (int i = 0; i < mapXSize; ++i) {
        for (int j = 0; j < mapYSize; ++j) {
            map.withdraw(player, "product", {i, j});
            if (player.inventory.storedItemsAmount != 0) {
                return false;
            }
        }
    }
    return true;
}

bool MapTests::testDepositExistentItemOnEmptyTileGetsNoItem() {
    Map map;
    int mapXSize = 50;
    int mapYSize = 50;
    _fillEmptyMap(map, mapXSize, mapYSize);
    Game game;
    Player player(game, GameType::HUMAN, GameType::WIZARD, 1, 0,
                  {0, 0}, "Name");
    std::shared_ptr<Item> item(new Weapon(GameType::GNARLED_STAFF));
    player.storeItem(std::move(item));
    map.deposit(player, "product", {5, 5});
    return player.inventory.storedItemsAmount == 1;
}

bool MapTests::testDepositExistentItemOnEmptyMapGetsNoItem() {
    Map map;
    int mapXSize = 50;
    int mapYSize = 50;
    _fillEmptyMap(map, mapXSize, mapYSize);
    Game game;
    Player player(game, GameType::HUMAN, GameType::WIZARD, 1, 0,
                  {0, 0}, "Name");
    std::shared_ptr<Item> item(new Weapon(GameType::GNARLED_STAFF));
    player.storeItem(std::move(item));
    for (int i = 0; i < mapXSize; ++i) {
        for (int j = 0; j < mapYSize; ++j) {
            map.deposit(player, "product", {5, 5});
            if (player.inventory.storedItemsAmount != 1) {
                return false;
            }
        }
    }
    return true;
}


bool MapTests::testBuyItemFromEmptyTileGetsNoItem() {
    Map map;
    int mapXSize = 50;
    int mapYSize = 50;
    _fillEmptyMap(map, mapXSize, mapYSize);
    Game game;
    Player player(game, GameType::HUMAN, GameType::WIZARD, 1, 0,
                  {0, 0}, "Name");
    map.buy(player, "product", {5, 5});
    return player.inventory.storedItemsAmount == 0;
}

bool MapTests::testBuyItemFromEmptyMapGetsNoItem() {
    Map map;
    int mapXSize = 50;
    int mapYSize = 50;
    _fillEmptyMap(map, mapXSize, mapYSize);
    Game game;
    Player player(game, GameType::HUMAN, GameType::WIZARD, 1, 0,
                  {0, 0}, "Name");
    for (int i = 0; i < mapXSize; ++i) {
        for (int j = 0; j < mapYSize; ++j) {
            map.buy(player, "product", {5, 5});
            if (player.inventory.storedItemsAmount != 0) {
                return false;
            }
        }
    }
    return true;
}

bool MapTests::testSellExistentItemToEmptyTileGetsNoItem() {
    Map map;
    int mapXSize = 50;
    int mapYSize = 50;
    _fillEmptyMap(map, mapXSize, mapYSize);
    Game game;
    Player player(game, GameType::HUMAN, GameType::WIZARD, 1, 0,
                  {0, 0}, "Name");
    std::shared_ptr<Item> item(new Weapon(GameType::GNARLED_STAFF));
    player.storeItem(std::move(item));
    map.sell(player, "product", {5, 5});
    return player.inventory.storedItemsAmount == 1;
}

bool MapTests::testSellExistentItemToEmptyMapGetsNoItem() {
    Map map;
    int mapXSize = 50;
    int mapYSize = 50;
    _fillEmptyMap(map, mapXSize, mapYSize);
    Game game;
    Player player(game, GameType::HUMAN, GameType::WIZARD, 1, 0,
                  {0, 0}, "Name");
    std::shared_ptr<Item> item(new Weapon(GameType::GNARLED_STAFF));
    player.storeItem(std::move(item));
    for (int i = 0; i < mapXSize; ++i) {
        for (int j = 0; j < mapYSize; ++j) {
            map.sell(player, "product", {5, 5});
            if (player.inventory.storedItemsAmount != 1) {
                return false;
            }
        }
    }
    return true;
}

bool MapTests::testMoveEntity() {
    Map map;
    int mapXSize = 50;
    int mapYSize = 50;
    _fillEmptyMap(map, mapXSize, mapYSize);
    Game game;
    std::shared_ptr<Monster> monster(new Monster(game, {25, 25}, GameType::SKELETON));
    map.addEntity({25, 25}, std::move(monster));
    map.moveEntity({25, 25}, {26, 26});
    return map.isPlaceAvailable({25, 25}) && !map.isPlaceAvailable({26, 26});
}


