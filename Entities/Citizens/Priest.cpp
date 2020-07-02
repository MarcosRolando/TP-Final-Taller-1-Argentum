//
// Created by agustin on 15/6/20.
//

#include "Priest.h"
#include "../../Config/Configuration.h"

using namespace GameType;

#define INITIAL_WEAPONS_AMOUNT 10
#define INITIAL_POTIONS_AMOUNT 30
#define BUYING_PRICE_MULTIPLIER 1.25
#define SELLING_PRICE_MULTIPLIER 0.75

Priest::Priest(Coordinate initialPosition): Entity(GameType::PRIEST, initialPosition, "Priest") {
    Configuration& config = Configuration::getInstance();
    std::unordered_map<std::string, unsigned int> initialItemsAmounts;
    initialItemsAmounts[config.configWeaponData(LINKED_STAFF).name] = INITIAL_WEAPONS_AMOUNT;
    initialItemsAmounts[config.configWeaponData(GNARLED_STAFF).name] = INITIAL_WEAPONS_AMOUNT;
    initialItemsAmounts[config.configWeaponData(ELVEN_FLUTE).name] = INITIAL_WEAPONS_AMOUNT;
    initialItemsAmounts[config.configWeaponData(ASH_ROD).name] = INITIAL_WEAPONS_AMOUNT;

    initialItemsAmounts[config.configPotionData(HEALTH_POTION).name] = INITIAL_POTIONS_AMOUNT;
    initialItemsAmounts[config.configPotionData(MANA_POTION).name] = INITIAL_POTIONS_AMOUNT;

    Shop aux(initialItemsAmounts, BUYING_PRICE_MULTIPLIER, SELLING_PRICE_MULTIPLIER);
    shop = std::move(aux);
}

/*
unsigned int Priest::list(const Player &player, std::list<ProductData> &products) {
    return shop.list(player, products);
}
*/

void Priest::list(const Player &player, std::stringstream &data) {
    shop.list(player, data);
}



void Priest::buy(Player &player, const std::string &itemName) {
    shop.buy(player, itemName);
}

void Priest::sell(Player &player, const std::string& itemName) {
    shop.sell(player, itemName);
}

