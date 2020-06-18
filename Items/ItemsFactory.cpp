//
// Created by agustin on 16/6/20.
//

#include "ItemsFactory.h"

#include "../Config/Configuration.h"

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
}

///////////////////////////PUBLIC//////////////////////////////////

ItemsFactory &ItemsFactory::getInstance() {
    static ItemsFactory factory;
    return factory;
}
