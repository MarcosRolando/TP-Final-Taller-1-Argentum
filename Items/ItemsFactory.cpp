//
// Created by agustin on 16/6/20.
//

#include "ItemsFactory.h"

#include "../Config/Configuration.h"
#include "Defense/Chest/BlueTunic.h"
#include "Defense/Chest/LeatherArmor.h"
#include "Defense/Chest/PlateArmor.h"
#include "Defense/Head/Hood.h"
#include "Defense/Head/IronHelmet.h"
#include "Defense/Head/MagicHat.h"
#include "Defense/Shield/IronShield.h"
#include "Defense/Shield/TurtleShield.h"
#include "Attack/AshRod.h"
#include "Attack/CompositeBow.h"
#include "Attack/ElvenFlute.h"
#include "Attack/GnarledStaff.h"
#include "Attack/LinkedStaff.h"
#include "Attack/Longsword.h"
#include "Attack/SimpleBow.h"
#include "Attack/Warhammer.h"
#include "../Config/Calculator.h"
#include "Miscellaneous/Gold.h"
#include "Miscellaneous/ManaPotion.h"
#include "Miscellaneous/HealthPotion.h"

using namespace GameType;

///////////////////////////PRIVATE//////////////////////////////////

ItemsFactory::ItemsFactory() {
    const Configuration& config = Configuration::getInstance();

    itemsCreators[config.configClothingData(BLUE_TUNIC).name] = _storeBlueTunic;
    itemsCreators[config.configClothingData(LEATHER_ARMOR).name] = _storeLeatherArmor;
    itemsCreators[config.configClothingData(PLATE_ARMOR).name] = _storePlateArmor;

    itemsCreators[config.configClothingData(HOOD).name] = _storeHood;
    itemsCreators[config.configClothingData(IRON_HELMET).name] = _storeIronHelmet;
    itemsCreators[config.configClothingData(MAGIC_HAT).name] = _storeMagicHat;

    itemsCreators[config.configClothingData(IRON_SHIELD).name] = _storeIronShield;
    itemsCreators[config.configClothingData(TURTLE_SHIELD).name] = _storeTurtleShield;

    itemsCreators[config.configWeaponData(ASH_ROD).name] = _storeAshRod;
    itemsCreators[config.configWeaponData(COMPOSITE_BOW).name] = _storeCompositeBow;
    itemsCreators[config.configWeaponData(ELVEN_FLUTE).name] = _storeElvenFlute;
    itemsCreators[config.configWeaponData(GNARLED_STAFF).name] = _storeGnarledStaff;
    itemsCreators[config.configWeaponData(LINKED_STAFF).name] = _storeLinkedStaff;
    itemsCreators[config.configWeaponData(LONGSWORD).name] = _storeLongsword;
    itemsCreators[config.configWeaponData(SIMPLE_BOW).name] = _storeSimpleBow;
    itemsCreators[config.configWeaponData(WARHAMMER).name] = _storeWarhammer;

    itemsCreators[config.configPotionData(HEALTH_POTION).name] = _storeHealthPotion;
    itemsCreators[config.configPotionData(MANA_POTION).name] = _storeManaPotion;


    for (const auto & creator: itemsCreators) {
        itemsNames.push_back(&creator.first);
    }
}

void ItemsFactory::_storeBlueTunic(std::shared_ptr<Item> &item) {
    /*
    std::shared_ptr<Item> aux(new BlueTunic());
    item = std::move(aux);
    */
    item.reset(new BlueTunic());
}

void ItemsFactory::_storeLeatherArmor(std::shared_ptr<Item> &item) {
    /*
    std::shared_ptr<Item> aux(new LeatherArmor());
    item = std::move(aux);
    */
    item.reset(new LeatherArmor());
}

void ItemsFactory::_storePlateArmor(std::shared_ptr<Item> &item) {
    /*
    std::shared_ptr<Item> aux(new PlateArmor());
    item = std::move(aux);
    */
    item.reset(new PlateArmor());
}

void ItemsFactory::_storeHood(std::shared_ptr<Item> &item) {
    /*
    std::shared_ptr<Item> aux(new Hood());
    item = std::move(aux);
    */
    item.reset(new Hood());
}

void ItemsFactory::_storeIronHelmet(std::shared_ptr<Item> &item) {
    /*
    std::shared_ptr<Item> aux(new IronHelmet());
    item = std::move(aux);
    */
    item.reset(new IronHelmet());
}

void ItemsFactory::_storeMagicHat(std::shared_ptr<Item> &item) {
    /*
    std::shared_ptr<Item> aux(new MagicHat());
    item = std::move(aux);
    */
    item.reset(new MagicHat());
}

void ItemsFactory::_storeIronShield(std::shared_ptr<Item> &item) {
    /*
    std::shared_ptr<Item> aux(new IronShield());
    item = std::move(aux);
    */
    item.reset(new IronShield());
}

void ItemsFactory::_storeTurtleShield(std::shared_ptr<Item> &item) {
    /*
    std::shared_ptr<Item> aux(new TurtleShield());
    item = std::move(aux);
    */
    item.reset(new TurtleShield());
}

void ItemsFactory::_storeAshRod(std::shared_ptr<Item> &item) {
    /*
    std::shared_ptr<Item> aux(new AshRod());
    item = std::move(aux);
    */
    item.reset(new AshRod());
}

void ItemsFactory::_storeCompositeBow(std::shared_ptr<Item> &item) {
    /*
    std::shared_ptr<Item> aux(new CompositeBow());
    item = std::move(aux);
    */
    item.reset(new CompositeBow());
}

void ItemsFactory::_storeElvenFlute(std::shared_ptr<Item> &item) {
    /*
    std::shared_ptr<Item> aux(new ElvenFlute());
    item = std::move(aux);
    */
    item.reset(new ElvenFlute());
}

void ItemsFactory::_storeGnarledStaff(std::shared_ptr<Item> &item) {
    /*
    std::shared_ptr<Item> aux(new GnarledStaff());
    item = std::move(aux);
    */
    item.reset(new GnarledStaff());
}

void ItemsFactory::_storeLinkedStaff(std::shared_ptr<Item> &item) {
    /*
    std::shared_ptr<Item> aux(new LinkedStaff());
    item = std::move(aux);
    */
    item.reset(new LinkedStaff());
}

void ItemsFactory::_storeLongsword(std::shared_ptr<Item> &item) {
    /*
    std::shared_ptr<Item> aux(new Longsword());
    item = std::move(aux);
    */
    item.reset(new Longsword());
}

void ItemsFactory::_storeSimpleBow(std::shared_ptr<Item> &item) {
    /*
    std::shared_ptr<Item> aux(new SimpleBow());
    item = std::move(aux);
    */
    item.reset(new SimpleBow());
}

void ItemsFactory::_storeWarhammer(std::shared_ptr<Item> &item) {
    /*
    std::shared_ptr<Item> aux(new Warhammer());
    item = std::move(aux);
     */
    item.reset(new Warhammer());
}

void ItemsFactory::_storeGold(std::shared_ptr<Item> &item, unsigned int amount) {
    /*
    std::shared_ptr<Item> aux(new Gold(amount));
    item = std::move(aux);
    */
    item.reset(new Gold(amount));
}

void ItemsFactory::_storeManaPotion(std::shared_ptr<Item> &item) {
    item.reset(new ManaPotion());
}

void ItemsFactory::_storeHealthPotion(std::shared_ptr<Item> &item) {
    item.reset(new HealthPotion());
}

void ItemsFactory::_storeRandomPotion(std::shared_ptr<Item> &item) {
    if (Calculator::getRandomInt(0, 1) == 0) {
        _storeHealthPotion(item);
    } else {
        _storeManaPotion(item);
    }
}

///////////////////////////PUBLIC//////////////////////////////////

ItemsFactory &ItemsFactory::getInstance() {
    static ItemsFactory factory;
    return factory;
}

void ItemsFactory::storeItemInstance(std::string itemName, std::shared_ptr<Item> &item) {
    /*
    if (itemsCreators.count(itemName) == 1) {
        itemsCreators.at(itemName)(item);
    } else if (itemName == Configuration::getInstance().configPotionData(HEALTH_POTION).name) {
        _storeHealthPotion(item);
    } else if (itemName == Configuration::getInstance().configPotionData(MANA_POTION).name) {
        _storeManaPotion(item);
    } else {
        throw(std::out_of_range);
    }
    */
    itemsCreators.at(itemName)(item);
}

void ItemsFactory::storeRandomDrop(std::shared_ptr<Item> &item, unsigned int goldMultiplier) {
    int randomNumber = Calculator::getRandomInt(1, 100);
    if (randomNumber <= 18) {
        _storeGold(item, Calculator::calculateGoldDrop(goldMultiplier));
    } else if (randomNumber == 19) {
        _storeRandomPotion(item);
    } else if (randomNumber == 20) {
        const std::string& healthPotionName = Configuration::getInstance().configPotionData(HEALTH_POTION).name;
        const std::string& manaPotionName = Configuration::getInstance().configPotionData(MANA_POTION).name;
        randomNumber = Calculator::getRandomInt(0, (int)itemsNames.size() - 1);
        while ((*itemsNames[randomNumber] == healthPotionName) ||
               (*itemsNames[randomNumber] == manaPotionName)) {
            randomNumber = Calculator::getRandomInt(0, (int)itemsNames.size() - 1);
        }
        //randomNumber = Calculator::getRandomInt(0, (int)itemsNames.size() - 1);
        itemsCreators[*itemsNames[randomNumber]](item);
    }
}
