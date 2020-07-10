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
           float _buyingMultiplier, float _sellingMultiplier):
           storage(initialItemsAmounts, Configuration::getInstance().configInitialMerchantGold()) {
    Configuration& config = Configuration::getInstance();
    const auto & weaponsData = config.configAllWeaponsData();
    const auto & clothesData = config.configAllClothingData();
    const auto & potionsData = config.configAllPotionsData();

    for (const auto & weaponData: weaponsData) {
        prices[weaponData.second.name] = weaponData.second.price;
    }
    for (const auto & clothingData: clothesData) {
        prices[clothingData.second.name] = clothingData.second.price;
    }
    for (const auto & potionData: potionsData) {
        prices[potionData.second.name] = potionData.second.price;
    }
    buyingMultiplier = _buyingMultiplier;
    sellingMultiplier = _sellingMultiplier;
}

Shop &Shop::operator=(Shop &&other) noexcept {
    storage = std::move(other.storage);
    buyingMultiplier = other.buyingMultiplier;
    sellingMultiplier = other.sellingMultiplier;
    prices = std::move(other.prices);
    return *this;
}

Shop::Shop(Shop &&other) noexcept {
    storage = std::move(other.storage);
    buyingMultiplier = other.buyingMultiplier;
    sellingMultiplier = other.sellingMultiplier;
    prices = std::move(other.prices);
}


/*
unsigned int Shop::list(const Player &player, std::list<ProductData> &products) {
    return storage.getStorageData(products, prices, buyingMultiplier);
}
*/

void Shop::list(Player &player) const {
    storage.getStorageData(player, prices, buyingMultiplier);
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
