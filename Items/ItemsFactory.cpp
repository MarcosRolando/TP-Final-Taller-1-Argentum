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


///////////////////////////PRIVATE//////////////////////////////////

ItemsFactory::ItemsFactory() {
    const Configuration& config = Configuration::getInstance();

    itemsCreators[config.configClothingData(GameType::BLUE_TUNIC).name] = _storeBlueTunic;
    itemsCreators[config.configClothingData(GameType::LEATHER_ARMOR).name] = _storeLeatherArmor;
    itemsCreators[config.configClothingData(GameType::PLATE_ARMOR).name] = _storePlateArmor;

    itemsCreators[config.configClothingData(GameType::HOOD).name] = _storeHood;
    itemsCreators[config.configClothingData(GameType::IRON_HELMET).name] = _storeIronHelmet;
    itemsCreators[config.configClothingData(GameType::MAGIC_HAT).name] = _storeMagicHat;

    itemsCreators[config.configClothingData(GameType::IRON_SHIELD).name] = _storeIronShield;
    itemsCreators[config.configClothingData(GameType::TURTLE_SHIELD).name] = _storeTurtleShield;

    itemsCreators[config.configWeaponData(GameType::ASH_ROD).name] = _storeAshRod;
    itemsCreators[config.configWeaponData(GameType::COMPOSITE_BOW).name] = _storeCompositeBow;
    itemsCreators[config.configWeaponData(GameType::ELVEN_FLUTE).name] = _storeElvenFlute;
    itemsCreators[config.configWeaponData(GameType::GNARLED_STAFF).name] = _storeGnarledStaff;
    itemsCreators[config.configWeaponData(GameType::LINKED_STAFF).name] = _storeLinkedStaff;
    itemsCreators[config.configWeaponData(GameType::LONGSWORD).name] = _storeLongsword;
    itemsCreators[config.configWeaponData(GameType::SIMPLE_BOW).name] = _storeSimpleBow;
    itemsCreators[config.configWeaponData(GameType::WARHAMMER).name] = _storeWarhammer;

    itemsCreators[config.configPotionData(GameType::HEALTH_POTION).name] = _storeHealthPotion;
    itemsCreators[config.configPotionData(GameType::MANA_POTION).name] = _storeManaPotion;


    for (const auto & creator: itemsCreators) {
        itemsNames.push_back(&creator.first);
    }
}

void ItemsFactory::_storeBlueTunic(std::shared_ptr<Item> &item) {
    /*
    std::shared_ptr<Item> aux(new BlueTunic());
    item = std::move(aux);
    */
    //item.reset(new BlueTunic());
    item.reset(new Chest(GameType::BLUE_TUNIC));
}

void ItemsFactory::_storeLeatherArmor(std::shared_ptr<Item> &item) {
    /*
    std::shared_ptr<Item> aux(new LeatherArmor());
    item = std::move(aux);
    */
    //item.reset(new LeatherArmor());
    item.reset(new Chest(GameType::LEATHER_ARMOR));
}

void ItemsFactory::_storePlateArmor(std::shared_ptr<Item> &item) {
    /*
    std::shared_ptr<Item> aux(new PlateArmor());
    item = std::move(aux);
    */
    //item.reset(new PlateArmor());
    item.reset(new Chest(GameType::PLATE_ARMOR));
}

void ItemsFactory::_storeHood(std::shared_ptr<Item> &item) {
    /*
    std::shared_ptr<Item> aux(new Hood());
    item = std::move(aux);
    */
    //item.reset(new Hood());
    item.reset(new Head(GameType::HOOD));
}

void ItemsFactory::_storeIronHelmet(std::shared_ptr<Item> &item) {
    /*
    std::shared_ptr<Item> aux(new IronHelmet());
    item = std::move(aux);
    */
    //item.reset(new IronHelmet());
    item.reset(new Head(GameType::IRON_HELMET));
}

void ItemsFactory::_storeMagicHat(std::shared_ptr<Item> &item) {
    /*
    std::shared_ptr<Item> aux(new MagicHat());
    item = std::move(aux);
    */
    //item.reset(new MagicHat());
    item.reset(new Head(GameType::MAGIC_HAT));
}

void ItemsFactory::_storeIronShield(std::shared_ptr<Item> &item) {
    /*
    std::shared_ptr<Item> aux(new IronShield());
    item = std::move(aux);
    */
    //item.reset(new IronShield());
    item.reset(new Shield(GameType::IRON_SHIELD));
}

void ItemsFactory::_storeTurtleShield(std::shared_ptr<Item> &item) {
    /*
    std::shared_ptr<Item> aux(new TurtleShield());
    item = std::move(aux);
    */
    item.reset(new Shield(GameType::TURTLE_SHIELD));
}

void ItemsFactory::_storeAshRod(std::shared_ptr<Item> &item) {
    /*
    std::shared_ptr<Item> aux(new AshRod());
    item = std::move(aux);
    */
    //item.reset(new AshRod());
    item.reset(new Weapon(GameType::ASH_ROD));
}

void ItemsFactory::_storeCompositeBow(std::shared_ptr<Item> &item) {
    /*
    std::shared_ptr<Item> aux(new CompositeBow());
    item = std::move(aux);
    */
    //item.reset(new CompositeBow());
    item.reset(new Weapon(GameType::COMPOSITE_BOW));
}

void ItemsFactory::_storeElvenFlute(std::shared_ptr<Item> &item) {
    /*
    std::shared_ptr<Item> aux(new ElvenFlute());
    item = std::move(aux);
    */
    //item.reset(new ElvenFlute());
    item.reset(new Weapon(GameType::ELVEN_FLUTE));
}

void ItemsFactory::_storeGnarledStaff(std::shared_ptr<Item> &item) {
    /*
    std::shared_ptr<Item> aux(new GnarledStaff());
    item = std::move(aux);
    */
    //item.reset(new GnarledStaff());
    item.reset(new Weapon(GameType::GNARLED_STAFF));
}

void ItemsFactory::_storeLinkedStaff(std::shared_ptr<Item> &item) {
    /*
    std::shared_ptr<Item> aux(new LinkedStaff());
    item = std::move(aux);
    */
    //item.reset(new LinkedStaff());
    item.reset(new Weapon(GameType::LINKED_STAFF));
}

void ItemsFactory::_storeLongsword(std::shared_ptr<Item> &item) {
    /*
    std::shared_ptr<Item> aux(new Longsword());
    item = std::move(aux);
    */
    //item.reset(new Longsword());
    item.reset(new Weapon(GameType::LONGSWORD));
}

void ItemsFactory::_storeSimpleBow(std::shared_ptr<Item> &item) {
    /*
    std::shared_ptr<Item> aux(new SimpleBow());
    item = std::move(aux);
    */
    //item.reset(new SimpleBow());
    item.reset(new Weapon(GameType::SIMPLE_BOW));
}

void ItemsFactory::_storeWarhammer(std::shared_ptr<Item> &item) {
    /*
    std::shared_ptr<Item> aux(new Warhammer());
    item = std::move(aux);
     */
    //item.reset(new Warhammer());
    item.reset(new Weapon(GameType::WARHAMMER));
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
        const std::string& healthPotionName = Configuration::getInstance().configPotionData(GameType::HEALTH_POTION).name;
        const std::string& manaPotionName = Configuration::getInstance().configPotionData(GameType::MANA_POTION).name;
        randomNumber = Calculator::getRandomInt(0, (int)itemsNames.size() - 1);
        while ((*itemsNames[randomNumber] == healthPotionName) ||
               (*itemsNames[randomNumber] == manaPotionName)) {
            randomNumber = Calculator::getRandomInt(0, (int)itemsNames.size() - 1);
        }
        //randomNumber = Calculator::getRandomInt(0, (int)itemsNames.size() - 1);
        itemsCreators[*itemsNames[randomNumber]](item);
    }
}
