//
// Created by agustin on 15/6/20.
//

#include "Priest.h"

#define BUYING_PRICE_MULTIPLIER 1.25
#define SELLING_PRICE_MULTIPLIER 0.75

Priest::Priest(): shop() {

}

unsigned int Priest::list(std::list<ProductData> &products) {
    return shop.list(products);
}


void Priest::buy(Player &player, const std::string &itemName) {
    shop.buy(player, itemName);
}

void Priest::sell(Player &player, const std::string& itemName) {
    shop.sell(player, itemName);
}

