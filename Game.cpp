//
// Created by agustin on 7/6/20.
//

#include "Game.h"
#include "AttackResult.h"

AttackResult Game::attackPosition(int damage, unsigned int level,
                                    Coordinate coordinate) {
    return map.attackTile(damage, level, coordinate);
}

void Game::dropItems(std::list<std::shared_ptr<Item>>&& items, Coordinate position) {
    map.addItemsToTile(std::move(items), position);
}

void Game::dropItems(std::shared_ptr<Item> &&item, Coordinate position) {
    map.addItemsToTile(std::move(item), position);
}
