//
// Created by agustin on 22/6/20.
//

#include "EntityTests.h"
#include <memory>
#include "../Items/Attack/Weapon.h"
#include "../Game/Game.h"
#include "../Entities/Player.h"
#include "../Config/Configuration.h"


bool EntityTests::testStoreItem() {
    Configuration& config = Configuration::getInstance();
    Game game;
    Player player(game, GameType::HUMAN, GameType::CLERIC,
            1, 0, {0, 0}, "Rolito");
    std::shared_ptr<Item> item(new Weapon(GameType::LONGSWORD));
    player.storeItem(std::move(item));
    return (player.removeItem(config.configWeaponData(GameType::LONGSWORD).name)->getName()
                            == config.configWeaponData(GameType::LONGSWORD).name);
}