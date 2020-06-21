//
// Created by agustin on 7/6/20.
//

#include "Game.h"
#include "AttackResult.h"

/////////////////////////////////PRIVATE//////////////////////////

void Game::_repopulateMap(double timePassed) {
    spawnTimer += timePassed;
    if (spawnTimer >= spawnInterval) {
        unsigned int monstersToCreate = monsterCreationRate;
        std::shared_ptr<Monster> monster;
        spawnTimer = 0;
        if ((monstersToCreate + monsters.size()) > maxNumberOfMonsters) {
            monstersToCreate = maxNumberOfMonsters - monsters.size();
        }
        for (unsigned int i = 0; i < monstersToCreate; ++i) {
            Coordinate monsterPosition = map.getMonsterCoordinate();
            monstersFactory.storeRandomMonster(*this, map, monster, monsterPosition);
            monsters.push_back(monster);
            //map.addMonster(std::move(monster));
            map.addEntity(monsterPosition, std::static_pointer_cast<Entity>(monster));
        }
    }
}


/////////////////////////////////PUBLIC//////////////////////////

AttackResult Game::attackPosition(int damage, unsigned int level, bool isAPlayer,
                                    Coordinate coordinate) {
    return map.attackTile(damage, level, isAPlayer, coordinate);
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
