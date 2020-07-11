//
// Created by agustin on 15/6/20.
//

#include "Banker.h"

#include <memory>
#include "../Player.h"
#include "Storage.h"
#include "../../TPException.h"

std::unordered_map<std::string, Storage> Banker::playersStorages;

Banker::Banker(Coordinate initialPosition): Entity(GameType::BANKER,
                                                   initialPosition, "Banker") {

}

void Banker::list(Player &player) {
    playersStorages.at(player.getNickname()).getStorageData(player);
}


void Banker::withdraw(Player &player, const std::string &itemName) {
    try {
        playersStorages.at(player.getNickname()).retreiveItem(itemName, player);
    } catch (...) {
        throw TPException("Intentaron withdrawear un item de un player que no existia!");
    }
}

void Banker::deposit(Player &player, const std::string& itemName) {
    try {
        playersStorages.at(player.getNickname()).storeItem(player.removeItem(itemName));
    } catch(...) {
        throw TPException("Intentaron depositar un item de un player que no existia!");
    }
}

void Banker::addPlayerItems(const std::string& playerName, const std::unordered_map<std::string, unsigned int>
                            &initialItemsAmounts, unsigned int gold) {
    playersStorages.emplace(playerName, Storage(initialItemsAmounts, gold));
}

