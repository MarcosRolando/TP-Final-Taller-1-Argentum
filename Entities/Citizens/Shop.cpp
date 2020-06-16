//
// Created by agustin on 16/6/20.
//

#include "Shop.h"


unsigned int Shop::list(std::list<ProductData> &products) {
    return storage.getAvailableItems(products, BUYING_PRICE_MULTIPLIER);
}

void Shop::buy(Player &player, const std::string &itemName) {
    unsigned int price;
    if (storage.isItemAvailable(itemName)) {
        price = storage.getItemPrice(itemName) * BUYING_PRICE_MULTIPLIER;
        if (player.spendGold(price)) {
            storage.increaseGoldReserves(price);
            storage.retreiveItem(itemName, player);
        }
    }
}

void Shop::sell(Player &player, const std::string& itemName) {
    unsigned int price;
    if (storage.isItemAvailable(itemName)) {
        price = storage.getItemPrice(itemName) * SELLING_PRICE_MULTIPLIER;
        if (storage.decreaseGoldReserves(price)) {
            player.receiveGold(price);
            storage.retreiveItem(itemName, player);
        }
    }
}
