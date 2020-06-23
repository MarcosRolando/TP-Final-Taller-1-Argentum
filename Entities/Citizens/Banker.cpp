//
// Created by agustin on 15/6/20.
//

#include "Banker.h"
#include <memory>
#include "../../Items/Item.h"
#include "Storage.h"
#include "../../TPException.h"

std::unordered_map<std::string, Storage> Banker::playersStorages;

class Player {
public:
    const std::string& getNickname() const;
    std::shared_ptr<Item> removeItem(const std::string& itemName);
};


Banker::Banker(Coordinate initialPosition): Entity(initialPosition) {

}

unsigned int Banker::list(const Player &player, std::list<ProductData> &products) {
    return playersStorages.at(player.getNickname()).getStorageData(products);
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

