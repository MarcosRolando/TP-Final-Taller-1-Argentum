//
// Created by agustin on 15/6/20.
//

#include "Trader.h"
#include "../../Config/Configuration.h"

#define INITIAL_ITEMS_AMOUNT 10
#define BUYING_PRICE_MULTIPLIER 1.1
#define SELLING_PRICE_MULTIPLIER 0.9

using namespace GameType;

Trader::Trader(Coordinate initialPosition) : Entity(GameType::TRADER, initialPosition, "Trader") {
    std::unordered_set<std::string> acceptedProducts;
    Configuration& config = Configuration::getInstance();
    std::unordered_map<std::string, unsigned int> initialItemsAmounts;

    initialItemsAmounts[config.configWeaponData(LONGSWORD).name] = INITIAL_ITEMS_AMOUNT;
    initialItemsAmounts[config.configWeaponData(AXE).name] = INITIAL_ITEMS_AMOUNT;
    initialItemsAmounts[config.configWeaponData(WARHAMMER).name] = INITIAL_ITEMS_AMOUNT;
    initialItemsAmounts[config.configWeaponData(SIMPLE_BOW).name] = INITIAL_ITEMS_AMOUNT;
    initialItemsAmounts[config.configWeaponData(COMPOSITE_BOW).name] = INITIAL_ITEMS_AMOUNT;

    initialItemsAmounts[config.configClothingData(LEATHER_ARMOR).name] = INITIAL_ITEMS_AMOUNT;
    initialItemsAmounts[config.configClothingData(PLATE_ARMOR).name] = INITIAL_ITEMS_AMOUNT;
    initialItemsAmounts[config.configClothingData(KING_ARMOR).name] = INITIAL_ITEMS_AMOUNT;
    initialItemsAmounts[config.configClothingData(BLUE_TUNIC).name] = INITIAL_ITEMS_AMOUNT;
    initialItemsAmounts[config.configClothingData(HOOD).name] = INITIAL_ITEMS_AMOUNT;
    initialItemsAmounts[config.configClothingData(IRON_HELMET).name] = INITIAL_ITEMS_AMOUNT;
    initialItemsAmounts[config.configClothingData(TURTLE_SHIELD).name] = INITIAL_ITEMS_AMOUNT;
    initialItemsAmounts[config.configClothingData(IRON_SHIELD).name] = INITIAL_ITEMS_AMOUNT;
    initialItemsAmounts[config.configClothingData(MAGIC_HAT).name] = INITIAL_ITEMS_AMOUNT;

    initialItemsAmounts[config.configPotionData(MANA_POTION).name] = INITIAL_ITEMS_AMOUNT;
    initialItemsAmounts[config.configPotionData(HEALTH_POTION).name] = INITIAL_ITEMS_AMOUNT;

    for (const auto & item: initialItemsAmounts) {
        acceptedProducts.emplace(item.first);
    }

    Shop aux(initialItemsAmounts, std::move(acceptedProducts), BUYING_PRICE_MULTIPLIER, SELLING_PRICE_MULTIPLIER);
    shop = std::move(aux);
}

void Trader::list(Player &player) {
    shop.list(player);
}


void Trader::buy(Player &player, const std::string &itemName) {
    shop.buy(player, itemName);
}

void Trader::sell(Player &player, const std::string& itemName) {
    shop.sell(player, itemName);
}

