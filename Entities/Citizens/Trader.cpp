//
// Created by agustin on 15/6/20.
//

#include "Trader.h"

#define INITIAL_ITEMS_AMMOUNT 10

#define BUYING_PRICE_MULTIPLIER 1.1
#define SELLING_PRICE_MULTIPLIER 0.9

using namespace Config;

Trader::Trader(Coordinate initialPosition) : Entity(initialPosition) {
    Configuration& config = Configuration::getInstance();
    std::unordered_map<std::string, unsigned int> initialItemsAmmounts;

    initialItemsAmmounts[config.configWeaponData(LONGSWORD).name] = INITIAL_ITEMS_AMMOUNT;
    initialItemsAmmounts[config.configWeaponData(AXE).name] = INITIAL_ITEMS_AMMOUNT;
    initialItemsAmmounts[config.configWeaponData(WARHAMMER).name] = INITIAL_ITEMS_AMMOUNT;
    initialItemsAmmounts[config.configWeaponData(SIMPLE_BOW).name] = INITIAL_ITEMS_AMMOUNT;
    initialItemsAmmounts[config.configWeaponData(COMPOSITE_BOW).name] = INITIAL_ITEMS_AMMOUNT;

    initialItemsAmmounts[config.configClothingData(LEATHER_ARMOR).name] = INITIAL_ITEMS_AMMOUNT;
    initialItemsAmmounts[config.configClothingData(PLATE_ARMOR).name] = INITIAL_ITEMS_AMMOUNT;
    initialItemsAmmounts[config.configClothingData(BLUE_TUNIC).name] = INITIAL_ITEMS_AMMOUNT;
    initialItemsAmmounts[config.configClothingData(HOOD).name] = INITIAL_ITEMS_AMMOUNT;
    initialItemsAmmounts[config.configClothingData(IRON_HELMET).name] = INITIAL_ITEMS_AMMOUNT;
    initialItemsAmmounts[config.configClothingData(TURTLE_SHIELD).name] = INITIAL_ITEMS_AMMOUNT;
    initialItemsAmmounts[config.configClothingData(IRON_SHIELD).name] = INITIAL_ITEMS_AMMOUNT;
    initialItemsAmmounts[config.configClothingData(MAGIC_HAT).name] = INITIAL_ITEMS_AMMOUNT;

    //AGREGAR POCIONES


    Shop aux(initialItemsAmmounts, BUYING_PRICE_MULTIPLIER, SELLING_PRICE_MULTIPLIER);
    shop = std::move(aux);
}

unsigned int Trader::list(std::list<ProductData> &products) {
    return shop.list(products);
}

void Trader::buy(Player &player, const std::string &itemName) {
    shop.buy(player, itemName);
}

void Trader::sell(Player &player, const std::string& itemName) {
    shop.sell(player, itemName);
}
