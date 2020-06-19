//
// Created by agustin on 15/6/20.
//

#include "Banker.h"

Banker::Banker(Coordinate initialPosition): Entity(initialPosition) {

}


unsigned int Banker::list(std::list<ProductData> &products) {
    return storage.getAvailableItems(products, 0);
}

void Banker::withdraw(Player &player, const std::string &itemName) {
    storage.retreiveItem(itemName, player);

}

void Banker::deposit(Player &player, const std::string& itemName) {
    //storage.storeItem(player.removeItem(itemName));
    playersStorages.at(storage).storeItem(player.removeItem(itemName));
}

void Banker::addPlayerItems(const std::string& playerName, const std::unordered_map<std::string, unsigned int>
                            &initialItemsAmounts, unsigned int gold) {
    playersStorages.emplace(playerName, Storage(initialItemsAmounts, gold));
}

