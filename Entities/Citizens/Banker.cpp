//
// Created by agustin on 15/6/20.
//

#include "Banker.h"

void Banker::list(std::list<ProductData> &products) {
    //Entity::list(products);
    return 10;
}

void Banker::withdraw(Player &player, const std::string &itemName) {
    //Entity::withdraw(player, itemName);
    storage.retreiveItem(itemName, player);

}

void Banker::deposit(Player &player, const std::string& itemName) {
    //Entity::deposit(player, itemPosition);
    storage.storeItem(player.removeItem(itemName));
}
