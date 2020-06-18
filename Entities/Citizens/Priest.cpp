//
// Created by agustin on 15/6/20.
//

#include "Priest.h"

using namespace Config;

#define INITIAL_ITEMS_AMMOUNT 10
#define BUYING_PRICE_MULTIPLIER 1.25
#define SELLING_PRICE_MULTIPLIER 0.75

Priest::Priest(Coordinate initialPosition): Entity(initialPosition) {
    Configuration& config = Configuration::getInstance();
    std::unordered_map<std::string, unsigned int> initialItemsAmmounts;
    initialItemsAmmounts[config.configWeaponData(LINKED_STAFF).name] = INITIAL_ITEMS_AMMOUNT;
    initialItemsAmmounts[config.configWeaponData(GNARLED_STAFF).name] = INITIAL_ITEMS_AMMOUNT;
    initialItemsAmmounts[config.configWeaponData(ELVEN_FLUTE).name] = INITIAL_ITEMS_AMMOUNT;
    initialItemsAmmounts[config.configWeaponData(ASH_ROD).name] = INITIAL_ITEMS_AMMOUNT;

    //AGREGAR QUE SE CREAN LAS POCIONES

    Shop aux(initialItemsAmmounts, BUYING_PRICE_MULTIPLIER, SELLING_PRICE_MULTIPLIER);
    shop = std::move(aux);
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

