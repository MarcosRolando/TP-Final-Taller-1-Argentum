//
// Created by agustin on 15/6/20.
//

#include "Trader.h"

void Trader::list(std::list<ProductData> &products) {
    Entity::list(products);
}

void Trader::buy(Player &player, const std::string &itemName, unsigned int gold) {
    Entity::buy(player, itemName, gold);
}

void Trader::sell(Player &player, unsigned int itemPosition) {
    Entity::sell(player, itemPosition);
}
