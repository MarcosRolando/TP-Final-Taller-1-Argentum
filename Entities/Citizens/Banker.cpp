//
// Created by agustin on 15/6/20.
//

#include "Banker.h"

Banker::Banker() {

}


unsigned int Banker::list(std::list<ProductData> &products) {
    return storage.getAvailableItems(products, 0);
}

void Banker::withdraw(Player &player, const std::string &itemName) {
    storage.retreiveItem(itemName, player);

}

void Banker::deposit(Player &player, const std::string& itemName) {
    storage.storeItem(player.removeItem(itemName));
}

