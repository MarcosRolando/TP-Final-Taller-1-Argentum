//
// Created by agustin on 15/6/20.
//

#include "Trader.h"

#define BUYING_PRICE_MULTIPLIER 1.1
#define SELLING_PRICE_MULTIPLIER 0.9


unsigned int Trader::list(std::list<ProductData> &products) {
    return shop.list(products);
}

void Trader::buy(Player &player, const std::string &itemName) {
    shop.buy(player, itemName);
}

void Trader::sell(Player &player, const std::string& itemName) {
    shop.sell(player, itemName);
}
