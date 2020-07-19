//
// Created by agustin on 22/6/20.
//

#include "MapTests.h"

#include <iostream>
#include <memory>
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
#include "catch.hpp"
#include "fakeit.hpp"

using namespace fakeit;

////////////////////////PRIVATE/////////////////////////

void MapTests::_fillEmptyMap(Map &map, int iSize, int jSize, bool isCity) {
    for (int i = 0; i < iSize; ++i) {
        map.tiles.emplace_back();
        for (int j = 0; j < jSize; ++j) {
            map.tiles[i].emplace_back(true, isCity, GameType::FloorType::GRASS0,
                                      GameType::Structure::NO_STRUCTURE,
                                      std::shared_ptr<Entity>(nullptr));
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

//todo arreglar la prueba
bool MapTests::testMixedCityAndUnavailableTiles() {
    Map map;
    int mapXSize = 50;
    int mapYSize = 50;
    bool isCity;
    bool isAvailable;
    bool isOccupable;
    for (int i = 0; i < mapXSize; ++i) {
        map.tiles.emplace_back();
        for (int j = 0; j < mapYSize; ++j) {
            isCity = (j % 2 == 0);
            isOccupable = j % 3 == 0;
            map.tiles[i].emplace_back(isOccupable, isCity, GameType::FloorType::GRASS0,
                  GameType::Structure::NO_STRUCTURE,
                  nullptr);
        }
    }
    for (int i = 0; i < mapXSize; ++i) {
        for (int j = 0; j < mapYSize; ++j) {
            isCity = map.tiles[i][j].isInCity();
            isAvailable = map.tiles[i][j].isAvailable();
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
                if (!isAvailable) {
                    return false;
                }
            } else {
                if (isAvailable) {
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
    items.emplace_back(new Head(GameType::Clothing::MAGIC_HAT));
    items.emplace_back(new Head(GameType::Clothing::NO_HELMET));
    items.emplace_back(new Shield(GameType::Clothing::IRON_SHIELD));
    items.emplace_back(new Chest(GameType::Clothing::PLATE_ARMOR));
    items.emplace_back(new Chest(GameType::Clothing::COMMON_CLOTHING));
    items.emplace_back(new Weapon(GameType::Weapon::LONGSWORD));
    items.emplace_back(new Weapon(GameType::Weapon::FIST));

    Configuration& config = Configuration::getInstance();

    std::vector<std::string> itemsNames = {config.configGetGoldName(), config.configPotionData(GameType::Potion::HEALTH_POTION).name,
                                         config.configPotionData(GameType::Potion::MANA_POTION).name,
                                         config.configClothingData(GameType::Clothing::MAGIC_HAT).name,
                                         config.configClothingData(GameType::Clothing::NO_HELMET).name,
                                         config.configClothingData(GameType::Clothing::IRON_SHIELD).name,
                                         config.configClothingData(GameType::Clothing::PLATE_ARMOR).name,
                                         config.configClothingData(GameType::Clothing::COMMON_CLOTHING).name,
                                         config.configWeaponData(GameType::Weapon::LONGSWORD).name,
                                         config.configWeaponData(GameType::Weapon::FIST).name};
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
    map.getAttackTargets({25, 25}, 25, targets);
    //map.getTargets({25, 25}, 25, targets);
    return targets.empty();
}

bool MapTests::testGetTargetsOnMapWithPlayerReturnsListWithOneElement() {
    Map map;
    int mapXSize = 50;
    int mapYSize = 50;
    _fillEmptyMap(map, mapXSize, mapYSize);
    Mock<Game> game;
    PlayerData data;
    data.isNewPlayer = true;
    std::shared_ptr<Player> player(new Player(game.get(),
            {25,25}, data));
    map.addEntity({25, 25}, player);
    std::vector<Coordinate> targets;
    map.getAttackTargets({25, 25}, 25, targets);
    return (targets.size() == 1) && (targets[0].jPosition == 25) && (targets[0].iPosition == 25);
}

bool MapTests::testGetTargetsOnMapWithDeadPlayerReturnsEmptyList() {
    Map map;
    int mapXSize = 50;
    int mapYSize = 50;
    _fillEmptyMap(map, mapXSize, mapYSize);
    Mock<Game> game;
    std::shared_ptr<Player> player(new Player(game.get(),
            {25,25}, PlayerData()));
    player->stats.currentLife = 0;
    map.addEntity({25, 25}, player);
    std::vector<Coordinate> targets;
    map.getAttackTargets({25, 25}, 25, targets);
    return targets.empty();
}

bool MapTests::testPositionWithPlayerIsOccupied() {
    Map map;
    int mapXSize = 50;
    int mapYSize = 50;
    _fillEmptyMap(map, mapXSize, mapYSize);
    Mock<Game> game;
    std::shared_ptr<Player> player(new Player(game.get(),
            {25,25}, PlayerData()));
    map.addEntity({25, 25}, std::move(player));
    return !map.tiles[25][25].isAvailable();
}

bool MapTests::testPositionWithMonsterIsOccupied() {
    Map map;
    int mapXSize = 50;
    int mapYSize = 50;
    _fillEmptyMap(map, mapXSize, mapYSize);
    Mock<Game> game;
    std::shared_ptr<Monster> monster(new Monster(game.get(),
            {25, 25}, GameType::SKELETON, GameType::SKELETON_ATTACK));
    map.addEntity({25, 25}, std::move(monster));
    return !map.tiles[25][25].isAvailable();
}

bool MapTests::testListOnEmptyTileReturnsEmptyList() {
    Map map;
    int mapXSize = 50;
    int mapYSize = 50;
    _fillEmptyMap(map, mapXSize, mapYSize);
    Mock<Game> game;
    PlayerData data;
    data.isNewPlayer = true;
    std::shared_ptr<Player> player(new Player(game.get(),
                                 {0,0}, data));
    map.list(*player, {5, 5});
    return player->chat.getMessages().empty();
}

bool MapTests::testListOnEmptyMapReturnsEmptyList() {
    Map map;
    int mapXSize = 50;
    int mapYSize = 50;
    _fillEmptyMap(map, mapXSize, mapYSize);
    Mock<Game> game;
    PlayerData data;
    data.isNewPlayer = true;
    Player player(game.get(), {0, 0}, data);
    if (!player.chat.getMessages().empty()) return false;
    for (int i = 0; i < mapXSize; ++i) {
        for (int j = 0; j < mapYSize; ++j) {
            map.list(player, {i, j});
            if (!player.chat.getMessages().empty()) {
                return false;
            }
        }
    }
    return true;
}

bool MapTests::testWithdrawOnEmptyTileGetsNoItem() {
    Map map;
    int mapXSize = 50;
    int mapYSize = 50;
    _fillEmptyMap(map, mapXSize, mapYSize);
    Mock<Game> game;
    Player player(game.get(), {0, 0}, PlayerData());
    map.withdraw(player, "product", {5, 5});
    return player.inventory.storedItemsAmount == 0;
}

bool MapTests::testWithdrawOnEmptyMapGetsNoItem() {
    Map map;
    int mapXSize = 50;
    int mapYSize = 50;
    _fillEmptyMap(map, mapXSize, mapYSize);
    Mock<Game> game;
    Player player(game.get(), {0, 0}, PlayerData());
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
    Mock<Game> game;
    PlayerData data;
    data.isNewPlayer = true;
    Player player(game.get(), {0, 0}, data);
    std::shared_ptr<Item> item(new Weapon(GameType::GNARLED_STAFF));
    player.storeItem(item);
    map.deposit(player, "product", {5, 5});
    return player.inventory.storedItemsAmount == 1;
}

bool MapTests::testDepositExistentItemOnEmptyMapGetsNoItem() {
    Map map;
    int mapXSize = 50;
    int mapYSize = 50;
    _fillEmptyMap(map, mapXSize, mapYSize);
    PlayerData data;
    data.isNewPlayer = true;
    Mock<Game> game;
    Player player(game.get(), {0, 0}, data);
    std::shared_ptr<Item> item(new Weapon(GameType::GNARLED_STAFF));
    player.storeItem(item);
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
    Mock<Game> game;
    Player player(game.get(), {0, 0}, PlayerData());
    map.buy(player, "product", {5, 5});
    return player.inventory.storedItemsAmount == 0;
}

bool MapTests::testBuyItemFromEmptyMapGetsNoItem() {
    Map map;
    int mapXSize = 50;
    int mapYSize = 50;
    _fillEmptyMap(map, mapXSize, mapYSize);
    Mock<Game> game;
    Player player(game.get(), {0, 0}, PlayerData());
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
    Mock<Game> game;
    PlayerData data;
    data.isNewPlayer = true;
    Player player(game.get(), {0, 0}, data);
    std::shared_ptr<Item> item(new Weapon(GameType::GNARLED_STAFF));
    player.storeItem(item);
    map.sell(player, "product", {5, 5});
    return player.inventory.storedItemsAmount == 1;
}

bool MapTests::testSellExistentItemToEmptyMapGetsNoItem() {
    Map map;
    int mapXSize = 50;
    int mapYSize = 50;
    _fillEmptyMap(map, mapXSize, mapYSize);
    Mock<Game> game;
    PlayerData data;
    data.isNewPlayer = true;
    Player player(game.get(), {0, 0}, data);
    std::shared_ptr<Item> item(new Weapon(GameType::GNARLED_STAFF));
    player.storeItem(item);
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
    Mock<Game> game;
    std::shared_ptr<Monster> monster(new Monster(game.get(), {25, 25}, GameType::SKELETON, GameType::SKELETON_ATTACK));
    map.addEntity({25, 25}, std::move(monster));
    map.moveEntity({25, 25}, {26, 26});
    return map.isPlaceAvailable({25, 25}) && !map.isPlaceAvailable({26, 26});
}

bool MapTests::testRemoveEntityOnEmptyTileLeavesNoEntity() {
    Map map;
    int mapXSize = 50;
    int mapYSize = 50;
    _fillEmptyMap(map, mapXSize, mapYSize);
//    Mock<Game> game;
    map.removeEntity({5, 5});
    return map.isPlaceAvailable({5, 5});
}


