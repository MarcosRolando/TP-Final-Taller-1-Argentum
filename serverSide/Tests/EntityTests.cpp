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
#include "../Entities/Citizens/Banker.h"

#include "catch.hpp"
#include "fakeit.hpp"

using namespace fakeit;


bool EntityTests::testStoreItem() {
    Mock<Game> game;
    Configuration& config = Configuration::getInstance();
    Player player(reinterpret_cast<Game &>(game), {0,0}, PlayerData());
    std::shared_ptr<Item> item(new Weapon(GameType::Weapon::LONGSWORD));
    player.storeItem(item);
    return (player.removeItem(config.configWeaponData(GameType::Weapon::LONGSWORD).name)->getName()
            == config.configWeaponData(GameType::Weapon::LONGSWORD).name);
}

bool EntityTests::testIsMonsterTarget() {
    Mock<Game> game;
    Player player(reinterpret_cast<Game &>(game), {0,0}, PlayerData());
    if (!player.isMonsterTarget()) return false;
    player.stats.currentLife = 0;
    return !player.isMonsterTarget();
}

bool EntityTests::testSpendGold() {
    Game game;
    Player player(game, GameType::HUMAN, GameType::CLERIC,
                  1, 0, {0, 0}, "ElPantuflas");
    player.receiveGold(30);
    if (player.gold != 30) return false;
    std::shared_ptr<Item> gold(new Gold(105));
    player.storeItem(std::move(gold));
    if (player.gold != 135) return false;
    player.spendGold(15);
    return (player.gold == 120);
}

bool EntityTests::testItemUse() {
    Configuration& config = Configuration::getInstance();
    Game game;
    Player player(game, GameType::HUMAN, GameType::CLERIC,
                  1, 0, {0, 0}, "ElPantuflas");
    player.useItem(0); /*No deberia hacer nada*/
    if (player.inventory.equippedWeapon->getName() !=
            config.configWeaponData(GameType::Weapon::FIST).name) return false;
    player.useItem(15); /*No deberia hacer nada*/
    if (player.inventory.equippedWeapon->getName() !=
        config.configWeaponData(GameType::Weapon::FIST).name) return false;
    std::shared_ptr<Item> item(new Weapon(GameType::Weapon::LINKED_STAFF));
    player.storeItem(std::move(item));
    player.useItem(0); /*Deberia equiparse el LinkedStaff*/
    return (player.inventory.equippedWeapon->getName() == config.configWeaponData(GameType::Weapon::LINKED_STAFF).name);
}

bool EntityTests::testPlayerNickname() {
    Game game;
    Player player(game, GameType::HUMAN, GameType::CLERIC,
                  1, 0, {0, 0}, "ElPantuflas");
    return player.getNickname() == "ElPantuflas";
}

bool EntityTests::testLifeAndManaRecovery() {
    Game game;
    Player player(game, GameType::HUMAN, GameType::CLERIC,
                  1, 0, {0, 0}, "ElPantuflas");
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
    Player player(game, GameType::HUMAN, GameType::CLERIC,
                  1, 0, {0, 0}, "ElPantuflas");
    player.unequip(); /*No deberia hacer nada*/
    if (player.inventory.items[0]) return false;
    std::shared_ptr<Item> item(new Weapon(GameType::GNARLED_STAFF));
    player.storeItem(std::move(item));
    player.useItem(0);
    if (player.inventory.items[0]) return false;
    if (!player.inventory.equippedWeapon) return false;
    player.unequip();
    if (!player.inventory.items[0]) return false;
    if (player.inventory.equippedWeapon) return false;
    return true;
}

bool EntityTests::_testUnequipClothing(Game& game) {
    Player player(game, GameType::HUMAN, GameType::CLERIC,
                  1, 0, {0, 0}, "ElPantuflas");
    player.unequip(EQUIPMENT_PLACE_CHEST); /*No deberia hacer nada*/
    if (player.inventory.items[0]) return false;
    std::shared_ptr<Item> item(new Chest(GameType::PLATE_ARMOR));
    player.storeItem(std::move(item));
    player.useItem(0);
    if (player.inventory.items[0]) return false;
    if (!player.inventory.clothingEquipment.at(EQUIPMENT_PLACE_CHEST)) return false;
    player.unequip(EQUIPMENT_PLACE_CHEST);
    if (!player.inventory.items[0]) return false;
    if (player.inventory.clothingEquipment.at(EQUIPMENT_PLACE_CHEST)) return false;
    return true;
}

bool EntityTests::testUnequipGear() {
    Game game;
    if (!_testUnequipWeapon(game)) return false;
    return _testUnequipClothing(game);
}

bool EntityTests::testPlayerAttacksMonster() {
    Game game;
    _fillEmptyMap(game.map, 10, 10, false);
    Player player(game, GameType::HUMAN, GameType::CLERIC,
                  1, 0, {0, 0}, "ElPantuflas");
    MonstersFactory factory;
    std::shared_ptr<Monster> monster;
    factory.storeRandomMonster(game, monster);
    monster->stats.agility = 0; /*Para que no esquive el ataque*/
    game.map.addEntity({0, 1}, std::static_pointer_cast<Entity>(monster));
    player.attack({0, 1});
    return (monster->stats.getCurrentLife() != monster->stats.getMaxLife());
}

bool EntityTests::testPlayerAttacksMonsterAndConsumesMana() {
    Game game;
    _fillEmptyMap(game.map, 10, 10, false);
    Player player(game, GameType::DWARF, GameType::CLERIC,
                  50, 0, {0, 0}, "ElPantuflas");
    MonstersFactory factory;
    std::shared_ptr<Monster> monster;
    factory.storeRandomMonster(game, monster);
    monster->stats.agility = 0; /*Para que no esquive el ataque*/
    game.map.addEntity({0, 1}, std::static_pointer_cast<Entity>(monster));
    std::shared_ptr<Item> weapon(new Weapon(GameType::ASH_ROD));
    player.storeItem(std::move(weapon));
    player.useItem(0);
    if (player.stats.getCurrentMana() != player.stats.maxMana) return false;
    player.attack({0, 1});
    if (monster->stats.getCurrentLife() == monster->stats.getMaxLife()) return false;
    return (player.stats.getCurrentMana() != player.stats.maxMana);
}

bool EntityTests::testPlayerAttacksNewbieAndViceversa() {
    Game game;
    _fillEmptyMap(game.map, 10, 10, false);
    std::shared_ptr<Player> player1(new Player(game, GameType::DWARF, GameType::CLERIC,
                  13, 0, {0, 0}, "SpicyChori"));
    std::shared_ptr<Player> player2(new Player(game, GameType::DWARF, GameType::CLERIC,
                   8, 0, {0, 1}, "CrispyBurritos"));
    std::shared_ptr<Entity> aux = player1;
    game.map.addEntity({0, 0}, std::move(aux));
    aux = player2;
    game.map.addEntity({0, 1}, std::move(aux));
    player1->stats.agility = 0; /*Para que no esquiven*/
    player2->stats.agility = 0; /*Para que no esquiven*/
    std::shared_ptr<Item> weapon(new Weapon(GameType::LONGSWORD));
    player1->storeItem(std::move(weapon));
    player1->useItem(0);
    weapon.reset(new Weapon(GameType::WARHAMMER));
    player2->storeItem(std::move(weapon));
    player2->useItem(0);
    player1->attack({0, 1});
    player2->attack({0, 0});
    if (player2->stats.getCurrentLife() != player2->stats.getMaxLife()) return false;
    return (player1->stats.getCurrentLife() == player1->stats.getMaxLife());
}

bool EntityTests::testPlayerAttacksPlayerWithPastLevelDifferenceAndViceversa() {
    Game game;
    _fillEmptyMap(game.map, 10, 10, false);
    std::shared_ptr<Player> player1(new Player(game, GameType::DWARF, GameType::CLERIC,
                                               26, 0, {0, 0}, "SpicyChori"));
    std::shared_ptr<Player> player2(new Player(game, GameType::DWARF, GameType::CLERIC,
                                               15, 0, {0, 1}, "CrispyBurritos"));
    std::shared_ptr<Entity> aux = player1;
    game.map.addEntity({0, 0}, std::move(aux));
    aux = player2;
    game.map.addEntity({0, 1}, std::move(aux));
    player1->stats.agility = 0; /*Para que no esquiven*/
    player2->stats.agility = 0; /*Para que no esquiven*/
    std::shared_ptr<Item> weapon(new Weapon(GameType::LONGSWORD));
    player1->storeItem(std::move(weapon));
    player1->useItem(0);
    weapon.reset(new Weapon(GameType::WARHAMMER));
    player2->storeItem(std::move(weapon));
    player2->useItem(0);
    player1->attack({0, 1});
    player2->attack({0, 0});
    if (player2->stats.getCurrentLife() != player2->stats.getMaxLife()) return false;
    return (player1->stats.getCurrentLife() == player1->stats.getMaxLife());
}

bool EntityTests::testPlayersAttackEachOther() {
    Game game;
    _fillEmptyMap(game.map, 10, 10, false);
    std::shared_ptr<Player> player1(new Player(game, GameType::DWARF, GameType::CLERIC,
                                               20, 0, {0, 0}, "SpicyChori"));
    std::shared_ptr<Player> player2(new Player(game, GameType::DWARF, GameType::CLERIC,
                                               15, 0, {0, 1}, "CrispyBurritos"));
    std::shared_ptr<Entity> aux = player1;
    game.map.addEntity({0, 0}, std::move(aux));
    aux = player2;
    game.map.addEntity({0, 1}, std::move(aux));
    player1->stats.agility = 0; /*Para que no esquiven*/
    player2->stats.agility = 0; /*Para que no esquiven*/
    std::shared_ptr<Item> weapon(new Weapon(GameType::LONGSWORD));
    player1->storeItem(std::move(weapon));
    player1->useItem(0);
    weapon.reset(new Weapon(GameType::WARHAMMER));
    player2->storeItem(std::move(weapon));
    player2->useItem(0);
    player1->attack({0, 1});
    player2->attack({0, 0});
    if (player2->stats.getCurrentLife() == player2->stats.getMaxLife()) return false;
    return (player1->stats.getCurrentLife() != player1->stats.getMaxLife());
}

bool EntityTests::testMonsterAttacksPlayer() {
    Game game;
    _fillEmptyMap(game.map, 10, 10, false);
    std::shared_ptr<Player> player(new Player(game, GameType::DWARF, GameType::CLERIC,
            1, 0, {0, 1}, "CrispyBurritos"));
    MonstersFactory factory;
    std::shared_ptr<Monster> monster;
    factory.storeRandomMonster(game, monster);
    player->stats.agility = 0; /*Para que no esquive el ataque*/
    game.map.addEntity({0, 1}, std::static_pointer_cast<Entity>(player));
    monster->attack({0, 1});
    return (player->stats.getCurrentLife() != player->stats.getMaxLife());
}

bool EntityTests::testPlayerSellsItem() {
    Game game;
    Player player(game, GameType::DWARF, GameType::CLERIC,
            1, 0, {0, 0}, "CrispyBurritos");
    Trader trader({0, 1});
    std::shared_ptr<Item> weapon(new Weapon(GameType::LONGSWORD));
    player.storeItem(std::move(weapon));
    trader.shop.storage.storedItems.at("Longsword").clear();
    if (!trader.shop.storage.storedItems.at("Longsword").empty()) return false;
    trader.sell(player, "Longsword");
    return (!trader.shop.storage.storedItems.at("Longsword").empty());
}

bool EntityTests::testPlayerDepositsAnItem() {
    Game game;
    Player player(game, GameType::DWARF, GameType::CLERIC,
                  1, 0, {0, 0}, "CrispyBurritos");
    Banker banker({0, 1});
    std::shared_ptr<Item> weapon(new Weapon(GameType::LONGSWORD));
    player.storeItem(std::move(weapon));
    std::unordered_map<std::string, unsigned int> aux;
    Banker::addPlayerItems(player.getNickname(), aux, 0);
    banker.deposit(player, "Longsword");
    banker.deposit(player, "Longsword"); /*No deberia hacer nada*/
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


