//
// Created by agustin on 15/6/20.
//

#include "Priest.h"

#define BUYING_PRICE_MULTIPLIER 1.25
#define SELLING_PRICE_MULTIPLIER 0.75

unsigned int Priest::list(std::list<ProductData> &products) {
    return storage.getAvailableItems(products, BUYING_PRICE_MULTIPLIER);
}

void Priest::buy(Player &player, const std::string &itemName) {
    unsigned int price;
    if (storage.isItemAvailable(itemName)) {
        price = storage.getItemPrice(itemName) * BUYING_PRICE_MULTIPLIER;
        if (player.spendGold(price)) {
            storage.increaseGoldReserves(price);
            storage.retreiveItem(itemName, player);
        }
    }
}

void Priest::sell(Player &player, const std::string& itemName) {
    unsigned int price;
    if (storage.isItemAvailable(itemName)) {
        price = storage.getItemPrice(itemName) * SELLING_PRICE_MULTIPLIER;
        if (storage.decreaseGoldReserves(price)) {
            player.receiveGold(price);
            storage.retreiveItem(itemName, player);
        }
    }
}
