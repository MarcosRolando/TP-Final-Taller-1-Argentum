//
// Created by agustin on 22/6/20.
//

#include "EntityTests.h"
#include <memory>
#include "../Items/Attack/Weapon.h"
#include "../Game/Game.h"
#include "../Entities/Player.h"
#include "../Config/Configuration.h"
#include "../Items/Miscellaneous/Gold.h"
#include "../Items/Defense/Chest.h"
#include "../AttackResult.h"
#include "../Entities/Monster.h"

bool EntityTests::testStoreItem() {
    Configuration& config = Configuration::getInstance();
    Game game;
    Player player(game, GameType::HUMAN, GameType::CLERIC,
            1, 0, {0, 0}, "ElPantuflas");
    std::shared_ptr<Item> item(new Weapon(GameType::LONGSWORD));
    player.storeItem(std::move(item));
    return (player.removeItem(config.configWeaponData(GameType::LONGSWORD).name)->getName()
            == config.configWeaponData(GameType::LONGSWORD).name);
}

bool EntityTests::testIsMonsterTarget() {
    Game game;
    Player player(game, GameType::HUMAN, GameType::CLERIC,
                  1, 0, {0, 0}, "ElPantuflas");
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
            config.configWeaponData(GameType::FIST).name) return false;
    player.useItem(15); /*No deberia hacer nada*/
    if (player.inventory.equippedWeapon->getName() !=
        config.configWeaponData(GameType::FIST).name) return false;
    std::shared_ptr<Item> item(new Weapon(GameType::LINKED_STAFF));
    player.storeItem(std::move(item));
    player.useItem(0); /*Deberia equiparse el LinkedStaff*/
    return (player.inventory.equippedWeapon->getName() == config.configWeaponData(GameType::LINKED_STAFF).name);
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
    unsigned int mana = player.stats.getCurrentMana();
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
    Player player(game, GameType::HUMAN, GameType::CLERIC,
                  1, 0, {0, 0}, "ElPantuflas");
    MonstersFactory factory;
    std::shared_ptr<Monster> monster;
    factory.storeRandomMonster(game, monster);
    monster->stats.agility = 0; /*Para que no esquive el ataque*/
    monster->stats.constitution = 0; /*Para que no se defienda del ataque*/
    game.map.addEntity({0, 1}, std::static_pointer_cast<Entity>(monster));
    player.attack({0, 1});
    return (monster->stats.getCurrentLife() != monster->stats.getMaxLife());
}
