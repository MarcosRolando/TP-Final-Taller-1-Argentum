//
// Created by agustin on 16/6/20.
//

#include "ItemsFactory.h"

#include "../Config/Configuration.h"
#include "../Config/Calculator.h"
#include "Miscellaneous/Gold.h"
#include "Miscellaneous/ManaPotion.h"
#include "Miscellaneous/HealthPotion.h"
#include "Defense/Chest.h"
#include "Defense/Head.h"
#include "Defense/Shield.h"
#include "Attack/Weapon.h"


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
    itemsCreators[config.configWeaponData(GameType::AXE).name] = _storeAxe;

    itemsCreators[config.configPotionData(GameType::HEALTH_POTION).name] = _storeHealthPotion;
    itemsCreators[config.configPotionData(GameType::MANA_POTION).name] = _storeManaPotion;


    for (const auto & creator: itemsCreators) {
        itemsNames.push_back(&creator.first);
    }
}

void ItemsFactory::_storeBlueTunic(std::shared_ptr<Item> &item) {
    item = std::make_shared<Chest>(GameType::BLUE_TUNIC);
}

void ItemsFactory::_storeLeatherArmor(std::shared_ptr<Item> &item) {
    item = std::make_shared<Chest>(GameType::LEATHER_ARMOR);
}

void ItemsFactory::_storePlateArmor(std::shared_ptr<Item> &item) {
    item = std::make_shared<Chest>(GameType::PLATE_ARMOR);
}

void ItemsFactory::_storeHood(std::shared_ptr<Item> &item) {
    item = std::make_shared<Head>(GameType::HOOD);
}

void ItemsFactory::_storeIronHelmet(std::shared_ptr<Item> &item) {
    item = std::make_shared<Head>(GameType::IRON_HELMET);
}

void ItemsFactory::_storeMagicHat(std::shared_ptr<Item> &item) {
    item = std::make_shared<Head>(GameType::MAGIC_HAT);
}

void ItemsFactory::_storeIronShield(std::shared_ptr<Item> &item) {
    item = std::make_shared<Shield>(GameType::IRON_SHIELD);
}

void ItemsFactory::_storeTurtleShield(std::shared_ptr<Item> &item) {
    item = std::make_shared<Shield>(GameType::TURTLE_SHIELD);
}

void ItemsFactory::_storeAshRod(std::shared_ptr<Item> &item) {
    item = std::make_shared<Weapon>(GameType::ASH_ROD);
}

void ItemsFactory::_storeCompositeBow(std::shared_ptr<Item> &item) {
    item = std::make_shared<Weapon>(GameType::COMPOSITE_BOW);
}

void ItemsFactory::_storeElvenFlute(std::shared_ptr<Item> &item) {
    item = std::make_shared<Weapon>(GameType::ELVEN_FLUTE);
}

void ItemsFactory::_storeGnarledStaff(std::shared_ptr<Item> &item) {
    item = std::make_shared<Weapon>(GameType::GNARLED_STAFF);
}

void ItemsFactory::_storeLinkedStaff(std::shared_ptr<Item> &item) {
    item = std::make_shared<Weapon>(GameType::LINKED_STAFF);
}

void ItemsFactory::_storeLongsword(std::shared_ptr<Item> &item) {
    item = std::make_shared<Weapon>(GameType::LONGSWORD);
}

void ItemsFactory::_storeSimpleBow(std::shared_ptr<Item> &item) {
    item = std::make_shared<Weapon>(GameType::SIMPLE_BOW);
}

void ItemsFactory::_storeWarhammer(std::shared_ptr<Item> &item) {
    item = std::make_shared<Weapon>(GameType::WARHAMMER);
}

void ItemsFactory::_storeAxe(std::shared_ptr<Item> &item) {
    item = std::make_shared<Weapon>(GameType::AXE);
}

void ItemsFactory::_storeGold(std::shared_ptr<Item> &item, unsigned int amount) {
    if (amount > 0) {
        item = std::make_shared<Gold>(amount);
    }
}

void ItemsFactory::_storeManaPotion(std::shared_ptr<Item> &item) {
    item = std::make_shared<ManaPotion>();
}

void ItemsFactory::_storeHealthPotion(std::shared_ptr<Item> &item) {
    item = std::make_shared<HealthPotion>();
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

void ItemsFactory::storeItemInstance(const std::string& itemName, std::shared_ptr<Item> &item) {
    itemsCreators.at(itemName)(item);
}

void ItemsFactory::storeItemInstance(GameType::ItemType type, int32_t instance,
                                                    std::shared_ptr<Item> &item) {
    Configuration& config = Configuration::getInstance();
    switch (type) {
        case GameType::ITEM_TYPE_CLOTHING:
            itemsCreators.at(config.configClothingData(
                    static_cast<GameType::Clothing>(instance)).name)(item);
            break;
        case GameType::ITEM_TYPE_WEAPON:
            itemsCreators.at(config.configWeaponData(
                    static_cast<GameType::Weapon>(instance)).name)(item);
            break;
        case GameType::ITEM_TYPE_POTION:
            itemsCreators.at(config.configPotionData(
                    static_cast<GameType::Potion>(instance)).name)(item);
            break;
        default:
            //do nothing
            break;
    }
}


void ItemsFactory::storeRandomDrop(std::shared_ptr<Item> &item, unsigned int goldMultiplier) {
    int randomNumber = Calculator::getRandomInt(1, 100);
    if (randomNumber <= 40) {
        _storeGold(item, Calculator::calculateGoldDrop(goldMultiplier));
    } else if (randomNumber == 41) {
        _storeRandomPotion(item);
    } else if (randomNumber == 42) {
        const std::string& healthPotionName = Configuration::getInstance().configPotionData(GameType::HEALTH_POTION).name;
        const std::string& manaPotionName = Configuration::getInstance().configPotionData(GameType::MANA_POTION).name;
        randomNumber = Calculator::getRandomInt(0, (int)itemsNames.size() - 1);
        while ((*itemsNames[randomNumber] == healthPotionName) ||
               (*itemsNames[randomNumber] == manaPotionName)) {
            randomNumber = Calculator::getRandomInt(0, (int)itemsNames.size() - 1);
        }
        itemsCreators[*itemsNames[randomNumber]](item);
    }
}
