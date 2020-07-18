//
// Created by agustin on 22/6/20.
//

#include "EntityTests.h"
#include <memory>
#include "../Items/Attack/Weapon.h"
#include "../Entities/Player.h"
#include "../Config/Configuration.h"
#include "../Items/Miscellaneous/Gold.h"
#include "../Items/Defense/Chest.h"
#include "../Entities/AttackResult.h"
#include "../Entities/Monster.h"
#include "../Entities/Citizens/Priest.h"
#include "../Entities/Citizens/Trader.h"

#include "catch.hpp"
#include "fakeit.hpp"
#include "../Entities/Citizens/Banker.h"

using namespace fakeit;


bool EntityTests::testStoreItem() {
    Mock<Game> game;
    PlayerData data;
    data.isNewPlayer = true;
    Configuration& config = Configuration::getInstance();
    Player player(game.get(), {0,0}, data);
    std::shared_ptr<Item> item(new Weapon(GameType::Weapon::LONGSWORD));
    player.storeItem(item);
    return (player.removeItem(config.configWeaponData(GameType::Weapon::LONGSWORD).name)->getName()
            == config.configWeaponData(GameType::Weapon::LONGSWORD).name);
}

bool EntityTests::testIsMonsterTarget() {
    Mock<Game> game;
    PlayerData data;
    data.isNewPlayer = true;
    Player player(game.get(), {0,0}, data);
    if (!player.isMonsterTarget()) return false;
    player.stats.currentLife = 0;
    return !player.isMonsterTarget();
}

bool EntityTests::testSpendGold() {
    Mock<Game> game;
    PlayerData data;
    data.isNewPlayer = true;
    Player player(game.get(),{0,0}, data);
    player.receiveGold(30);
    if (player.gold != 30) return false;
    std::shared_ptr<Item> gold(new Gold(105));
    player.storeItem(gold);
    if (player.gold != 135) return false;
    player.spendGold(15);
    return (player.gold == 120);
}

bool EntityTests::testItemUse() {
    Configuration& config = Configuration::getInstance();
    Mock<Game> game;
    PlayerData data;
    data.isNewPlayer = true;
    Player player(game.get(), {0,0}, data);
    player.useItem(0); /*No deberia hacer nada*/
    if (player.inventory.equippedWeapon->getName() !=
            config.configWeaponData(GameType::Weapon::FIST).name) return false;
    player.useItem(15); /*No deberia hacer nada*/
    if (player.inventory.equippedWeapon->getName() !=
        config.configWeaponData(GameType::Weapon::FIST).name) return false;
    std::shared_ptr<Item> item(new Weapon(GameType::Weapon::LINKED_STAFF));
    player.storeItem(item);
    player.useItem(0); /*Deberia equiparse el LinkedStaff*/
    return (player.inventory.equippedWeapon->getName() == config.configWeaponData(GameType::Weapon::LINKED_STAFF).name);
}

bool EntityTests::testPlayerNickname() {
    Mock<Game> game;
    PlayerData data;
    data.isNewPlayer = true;
    data.nickname = "ElPantuflas";
    Player player(game.get(), {0,0}, data);
    return player.getNickname() == "ElPantuflas";
}

bool EntityTests::testLifeAndManaRecovery() {
    Mock<Game> game;
    PlayerData data;
    data.isNewPlayer = true;
    Player player(game.get(), {0,0}, data);
    int life = player.stats.getCurrentLife();
    player.stats.currentLife -= 10;
    player.restoreLife(55);
    if (player.stats.getCurrentLife() != life) return false;
    int32_t mana = player.stats.getCurrentMana();
    player.stats.currentMana -= 10;
    player.restoreMana(55);
    return player.stats.getCurrentMana() == mana;
}

bool EntityTests::_testUnequipWeapon(Game& game) {
    PlayerData data;
    data.isNewPlayer = true;
    Player player(game, {0,0}, data);
    player.unequip(); /*No deberia hacer nada*/
    if (player.inventory.items[0]) return false;
    std::shared_ptr<Item> item(new Weapon(GameType::GNARLED_STAFF));
    player.storeItem(item);
    player.useItem(0);
    if (player.inventory.items[0]) return false;
    if (!player.inventory.equippedWeapon) return false;
    player.unequip();
    if (!player.inventory.items[0]) return false;
    return (player.inventory.equippedWeapon->getId() == GameType::FIST);
}

bool EntityTests::_testUnequipClothing(Game& game) {
    PlayerData data;
    data.isNewPlayer = true;
    Player player(reinterpret_cast<Game &>(game), {0,0}, data);
    player.unequip(GameType::EQUIPMENT_PLACE_CHEST); /*No deberia hacer nada*/
    if (player.inventory.items[0]) return false;
    std::shared_ptr<Item> item(new Chest(GameType::PLATE_ARMOR));
    player.storeItem(item);
    player.useItem(0);
    if (player.inventory.items[0]) return false;
    if (!player.inventory.clothingEquipment.at(GameType::EQUIPMENT_PLACE_CHEST)) return false;
    player.unequip(GameType::EQUIPMENT_PLACE_CHEST);
    if (!player.inventory.items[0]) return false;
    return (player.inventory.clothingEquipment.at(
            GameType::EQUIPMENT_PLACE_CHEST)->getId() == GameType::COMMON_CLOTHING);
}

bool EntityTests::testUnequipGear() {
    Mock<Game> game;
    if (!_testUnequipWeapon(game.get())) return false;
    return _testUnequipClothing(game.get());
}

bool EntityTests::testPlayerAttacksMonster() {
    Mock<Game> game;
    PlayerData data;
    data.isNewPlayer = true;
    _fillEmptyMap(game.get().map, 10, 10, false);
    Player player(game.get(), {0,0}, data);
    std::shared_ptr<Monster> monster(new Monster(game.get(), {0, 1},
                                                 GameType::SPIDER, GameType::SPIDER_ATTACK));
    monster->stats.agility = 0; /*Para que no esquive el ataque*/
    game.get().map.addEntity({0, 1}, std::static_pointer_cast<Entity>(monster));
    player.attack({0, 1});
    return (monster->stats.getCurrentLife() != monster->stats.getMaxLife());
}

bool EntityTests::testPlayerAttacksMonsterAndConsumesMana() {
    Mock<Game> game;
    PlayerData data;
    data.isNewPlayer = true;
    _fillEmptyMap(game.get().map, 10, 10, false);
    Player player(game.get(), {0,0}, data);
    std::shared_ptr<Monster> monster(new Monster(game.get(), {0, 1},
                                     GameType::SKELETON, GameType::SKELETON_ATTACK));
    monster->stats.agility = 0; /*Para que no esquive el ataque*/
    game.get().map.addEntity({0, 1}, std::static_pointer_cast<Entity>(monster));
    std::shared_ptr<Item> weapon(new Weapon(GameType::ASH_ROD));
    player.storeItem(weapon);
    player.useItem(0);
    if (player.stats.getCurrentMana() != player.stats.maxMana) return false;
    player.attack({0, 1});
    if (monster->stats.getCurrentLife() == monster->stats.getMaxLife()) return false;
    return (player.stats.getCurrentMana() != player.stats.maxMana);
}

bool EntityTests::testPlayerAttacksNewbieAndViceversa() {
    Mock<Game> game;
    Mock<Map> map;
    _fillEmptyMap(map.get(), 10, 10, false);
    std::shared_ptr<Player> player1(new Player(game.get(), {0,0}, PlayerData()));
    std::shared_ptr<Player> player2(new Player(game.get(), {0,1}, PlayerData()));
    std::shared_ptr<Entity> aux = player1;
    map.get().addEntity({0, 0}, std::move(aux));
    aux = player2;
    map.get().addEntity({0, 1}, std::move(aux));
    player1->stats.agility = 0; /*Para que no esquiven*/
    player2->stats.agility = 0; /*Para que no esquiven*/
    std::shared_ptr<Item> weapon(new Weapon(GameType::LONGSWORD));
    player1->storeItem(weapon);
    player1->useItem(0);
    weapon.reset(new Weapon(GameType::WARHAMMER));
    player2->storeItem(weapon);
    player2->useItem(0);
    player1->attack({0, 1});
    player2->attack({0, 0});
    if (player2->stats.getCurrentLife() != player2->stats.getMaxLife()) return false;
    return (player1->stats.getCurrentLife() == player1->stats.getMaxLife());
}

bool EntityTests::testPlayerAttacksPlayerWithPastLevelDifferenceAndViceversa() {
    Mock<Game> game;
    Mock<Map> map;
    _fillEmptyMap(map.get(), 10, 10, false);
    std::shared_ptr<Player> player1(new Player(game.get(), {0,0}, PlayerData()));
    std::shared_ptr<Player> player2(new Player(game.get(), {0,1}, PlayerData()));
    std::shared_ptr<Entity> aux = player1;
    map.get().addEntity({0, 0}, std::move(aux));
    aux = player2;
    map.get().addEntity({0, 1}, std::move(aux));
    player1->stats.agility = 0; /*Para que no esquiven*/
    player2->stats.agility = 0; /*Para que no esquiven*/
    std::shared_ptr<Item> weapon(new Weapon(GameType::LONGSWORD));
    player1->storeItem(weapon);
    player1->useItem(0);
    weapon.reset(new Weapon(GameType::WARHAMMER));
    player2->storeItem(weapon);
    player2->useItem(0);
    player1->attack({0, 1});
    player2->attack({0, 0});
    if (player2->stats.getCurrentLife() != player2->stats.getMaxLife()) return false;
    return (player1->stats.getCurrentLife() == player1->stats.getMaxLife());
}

bool EntityTests::testPlayersAttackEachOther() {
    Mock<Game> game;
    Configuration& config = Configuration::getInstance();
    _fillEmptyMap(game.get().map, 10, 10, false);
    PlayerData data;
    data.isNewPlayer = true;
    data.level = config.configNewbieLevel() + 1;
    std::shared_ptr<Player> player1(new Player(game.get(), {0,0}, data));
    std::shared_ptr<Player> player2(new Player(game.get(), {0,1}, data));
    std::shared_ptr<Entity> aux = player1;
    game.get().map.addEntity({0, 0}, std::move(aux));
    aux = player2;
    game.get().map.addEntity({0, 1}, std::move(aux));
    player1->stats.agility = 0; //Para que no esquiven
    player2->stats.agility = 0; //Para que no esquiven
    std::shared_ptr<Item> weapon(new Weapon(GameType::LONGSWORD));
    player1->storeItem(weapon);
    player1->useItem(0);
    weapon.reset(new Weapon(GameType::WARHAMMER));
    player2->storeItem(weapon);
    player2->useItem(0);
    player1->attack({0, 1});
    player2->attack({0, 0});
    if (player2->stats.getCurrentLife() == player2->stats.getMaxLife()) return false;
    return (player1->stats.getCurrentLife() != player1->stats.getMaxLife());
}

bool EntityTests::testMonsterAttacksPlayer() {
    Mock<Game> game;
    _fillEmptyMap(game.get().map, 10, 10, false);
    PlayerData data;
    data.isNewPlayer = true;
    std::shared_ptr<Player> player(new Player(game.get(), {0,0}, data));
    MonstersFactory factory;
    std::shared_ptr<Monster> monster;
    factory.storeRandomMonster(game.get(), monster);
    player->stats.agility = 0; /*Para que no esquive el ataque*/
    game.get().map.addEntity({0, 1}, std::static_pointer_cast<Entity>(player));
    monster->attack({0, 1});
    return (player->stats.getCurrentLife() != player->stats.getMaxLife());
}

bool EntityTests::testPlayerSellsItem() {
    Mock<Game> game;
    PlayerData data;
    data.isNewPlayer = true;
    Player player(game.get(), {0,0}, data);
    Trader trader({0, 1});
    std::shared_ptr<Item> weapon(new Weapon(GameType::LONGSWORD));
    player.storeItem(weapon);
    trader.shop.storage.storedItems.at("Longsword").clear();
    if (!trader.shop.storage.storedItems.at("Longsword").empty()) return false;
    trader.sell(player, "Longsword");
    return (!trader.shop.storage.storedItems.at("Longsword").empty());
}

bool EntityTests::testPlayerDepositsAnItem() {
    Mock<Game> game;
    PlayerData data;
    data.isNewPlayer = true;
    Player player(game.get(), {0,0}, data);
    Banker banker({0, 1});
    std::shared_ptr<Item> weapon(new Weapon(GameType::LONGSWORD));
    player.storeItem(weapon);
    std::unordered_map<std::string, unsigned int> aux;
    data = player.getData();
    Banker::addPlayerItems(data);
    banker.deposit(player, "Longsword");
    banker.deposit(player, "Longsword"); //No deberia hacer nada
    if (player.inventory.items[0]) return false;
    banker.withdraw(player, "Longsword");
    return (player.inventory.items[0]->getName() == "Longsword");
}

void EntityTests::_fillEmptyMap(Map &map, int iSize, int jSize, bool isCity) {
    for (int i = 0; i < iSize; ++i) {
        map.tiles.emplace_back();
        for (int j = 0; j < jSize; ++j) {
            map.tiles[i].emplace_back(true, isCity, GameType::FloorType::GRASS0,
                                      GameType::Structure::NO_STRUCTURE,
                                      std::shared_ptr<Entity>(nullptr));
        }
    }
}


