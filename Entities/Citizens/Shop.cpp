//
// Created by agustin on 16/6/20.
//

#include "Shop.h"
#include "../Player.h"
#include "../../Config/Configuration.h"

Shop::Shop() {
    sellingMultiplier = 1;
    buyingMultiplier = 1;
}

Shop::Shop(const std::unordered_map<std::string, unsigned int> &initialItemsAmounts,
           float buyingMultiplier, float sellingMultiplier):
           storage(initialItemsAmounts, Configuration::getInstance().configInitialMerchantGold()) {
    Configuration& config = Configuration::getInstance();
    for (const auto & weaponData: config.configAllWeaponsData()) {
        prices[weaponData.second.name] = weaponData.second.price;
    }
    for (const auto & clothingData: config.configAllClothingData()) {
        prices[clothingData.second.name] = clothingData.second.price;
    }
    for (const auto & potionData: config.configAllPotionsData()) {
        prices[potionData.second.name] = potionData.second.price;
    }
}

Shop &Shop::operator=(Shop &&other) noexcept {
    storage = std::move(other.storage);
    buyingMultiplier = other.buyingMultiplier;
    sellingMultiplier = other.sellingMultiplier;
    return *this;
}

Shop::Shop(Shop &&other) noexcept {
    storage = std::move(other.storage);
    buyingMultiplier = other.buyingMultiplier;
    sellingMultiplier = other.sellingMultiplier;
}


/*
unsigned int Shop::list(const Player &player, std::list<ProductData> &products) {
    return storage.getStorageData(products, prices, buyingMultiplier);
}
*/

void Shop::list(const Player &player, std::stringstream &data) {
    storage.getStorageData(data, prices, buyingMultiplier);
}



void Shop::buy(Player &player, const std::string &itemName) {
    unsigned int price;
    if (storage.isItemAvailable(itemName)) {
        price = static_cast<unsigned int>(static_cast<float>(prices[itemName])
                                                            * buyingMultiplier);
        if (player.spendGold(price)) {
            storage.increaseGoldReserves(price);
            storage.retreiveItem(itemName, player);
        }
    }
}

void Shop::sell(Player &player, const std::string& itemName) {
    unsigned int price;
    price = static_cast<unsigned int>(static_cast<float>(prices[itemName])
                                      * sellingMultiplier);
    if (storage.decreaseGoldReserves(price)) {
        player.receiveGold(price);
        storage.storeItem(player.removeItem(itemName));
    }
}
