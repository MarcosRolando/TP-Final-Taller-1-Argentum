//
// Created by agustin on 7/6/20.
//

#include "Game.h"
#include "AttackResult.h"

/////////////////////////////////PRIVATE//////////////////////////

void Game::_repopulateMap() {

}


/////////////////////////////////PUBLIC//////////////////////////

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

void Game::requestMove(Coordinate initialPosition, Coordinate finalPosition) {
    if (map.isPlaceAvailable(finalPosition)) {
        std::string command;
        command.push_back(COMMAND_TYPE_MOVE);
        command += "," + std::to_string(initialPosition.iPosition);
        command += "," + std::to_string(initialPosition.jPosition);
        command += "," + std::to_string(finalPosition.iPosition);
        command += "," + std::to_string(finalPosition.jPosition);
        eventQueue.push(std::move(command));
    }
}

void Game::update() {

}
