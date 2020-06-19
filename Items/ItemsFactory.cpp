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
#include "Gold.h"

using namespace Config;

///////////////////////////PRIVATE//////////////////////////////////

ItemsFactory::ItemsFactory() {
    const Configuration& config = Configuration::getInstance();

    itemsCreators[config.configClothingData(BLUE_TUNIC).name] = storeBlueTunic;
    itemsCreators[config.configClothingData(LEATHER_ARMOR).name] = storeLeatherArmor;
    itemsCreators[config.configClothingData(PLATE_ARMOR).name] = storePlateArmor;

    itemsCreators[config.configClothingData(HOOD).name] = storeHood;
    itemsCreators[config.configClothingData(IRON_HELMET).name] = storeIronHelmet;
    itemsCreators[config.configClothingData(MAGIC_HAT).name] = storeMagicHat;

    itemsCreators[config.configClothingData(IRON_SHIELD).name] = storeIronShield;
    itemsCreators[config.configClothingData(TURTLE_SHIELD).name] = storeTurtleShield;

    itemsCreators[config.configWeaponData(ASH_ROD).name] = storeAshRod;
    itemsCreators[config.configWeaponData(COMPOSITE_BOW).name] = storeCompositeBow;
    itemsCreators[config.configWeaponData(ELVEN_FLUTE).name] = storeElvenFlute;
    itemsCreators[config.configWeaponData(GNARLED_STAFF).name] = storeGnarledStaff;
    itemsCreators[config.configWeaponData(LINKED_STAFF).name] = storeLinkedStaff;
    itemsCreators[config.configWeaponData(LONGSWORD).name] = storeLongsword;
    itemsCreators[config.configWeaponData(SIMPLE_BOW).name] = storeSimpleBow;
    itemsCreators[config.configWeaponData(WARHAMMER).name] = storeWarhammer;

    //AGREGAR FUNCIONES PARA CREAR POCIONES


    for (const auto & creator: itemsCreators) {
        itemsNames.push_back(&creator.first);
    }
}

void ItemsFactory::storeBlueTunic(std::shared_ptr<Item> &item) {
    std::shared_ptr<Item> aux(new BlueTunic());
    item = std::move(aux);
}

void ItemsFactory::storeLeatherArmor(std::shared_ptr<Item> &item) {
    std::shared_ptr<Item> aux(new LeatherArmor());
    item = std::move(aux);
}

void ItemsFactory::storePlateArmor(std::shared_ptr<Item> &item) {
    std::shared_ptr<Item> aux(new PlateArmor());
    item = std::move(aux);
}

void ItemsFactory::storeHood(std::shared_ptr<Item> &item) {
    std::shared_ptr<Item> aux(new Hood());
    item = std::move(aux);
}

void ItemsFactory::storeIronHelmet(std::shared_ptr<Item> &item) {
    std::shared_ptr<Item> aux(new IronHelmet());
    item = std::move(aux);
}

void ItemsFactory::storeMagicHat(std::shared_ptr<Item> &item) {
    std::shared_ptr<Item> aux(new MagicHat());
    item = std::move(aux);
}

void ItemsFactory::storeIronShield(std::shared_ptr<Item> &item) {
    std::shared_ptr<Item> aux(new IronShield());
    item = std::move(aux);
}

void ItemsFactory::storeTurtleShield(std::shared_ptr<Item> &item) {
    std::shared_ptr<Item> aux(new TurtleShield());
    item = std::move(aux);
}

void ItemsFactory::storeAshRod(std::shared_ptr<Item> &item) {
    std::shared_ptr<Item> aux(new AshRod());
    item = std::move(aux);
}

void ItemsFactory::storeCompositeBow(std::shared_ptr<Item> &item) {
    std::shared_ptr<Item> aux(new CompositeBow());
    item = std::move(aux);
}

void ItemsFactory::storeElvenFlute(std::shared_ptr<Item> &item) {
    std::shared_ptr<Item> aux(new ElvenFlute());
    item = std::move(aux);
}

void ItemsFactory::storeGnarledStaff(std::shared_ptr<Item> &item) {
    std::shared_ptr<Item> aux(new GnarledStaff());
    item = std::move(aux);
}

void ItemsFactory::storeLinkedStaff(std::shared_ptr<Item> &item) {
    std::shared_ptr<Item> aux(new LinkedStaff());
    item = std::move(aux);
}

void ItemsFactory::storeLongsword(std::shared_ptr<Item> &item) {
    std::shared_ptr<Item> aux(new Longsword());
    item = std::move(aux);
}

void ItemsFactory::storeSimpleBow(std::shared_ptr<Item> &item) {
    std::shared_ptr<Item> aux(new SimpleBow());
    item = std::move(aux);
}

void ItemsFactory::storeWarhammer(std::shared_ptr<Item> &item) {
    std::shared_ptr<Item> aux(new Warhammer());
    item = std::move(aux);
}

void ItemsFactory::storeGold(std::shared_ptr<Item> &item, unsigned int amount) {
    std::shared_ptr<Item> aux(new Gold(amount));
    item = std::move(aux);
}

///////////////////////////PUBLIC//////////////////////////////////

ItemsFactory &ItemsFactory::getInstance() {
    static ItemsFactory factory;
    return factory;
}

void ItemsFactory::storeItemInstance(std::string itemName, std::shared_ptr<Item> &item) {
    itemsCreators.at(itemName)(item);
}

void ItemsFactory::storeRandomDrop(std::shared_ptr<Item> &item, unsigned int goldMultiplier) {
    int randomNumber = Calculator::getRandomInt(1, 100);
    if (randomNumber <= 18) {
        storeGold(item, Calculator::calculateGoldDrop(goldMultiplier));
    } else if (randomNumber == 19) {
        //LLAMAR A FUNCION PARA CREAR POCIONES
    } else if (randomNumber == 20) {
        randomNumber = Calculator::getRandomInt(0, itemsNames.size() - 1);
        itemsCreators[itemsNames[randomNumber]](item);
    }
}
