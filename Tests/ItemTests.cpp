//
// Created by agustin on 22/6/20.
//

#include "ItemTests.h"
#include "../Items/Item.h"
#include "../Items/Miscellaneous/Gold.h"
#include "../Items/Attack/Weapon.h"
#include "../Items/Defense/Chest.h"
#include "../Items/Defense/Head.h"
#include "../Items/Defense/Shield.h"
#include "../Items/Miscellaneous/HealthPotion.h"
#include "../Items/Miscellaneous/ManaPotion.h"

bool ItemTests::testInitialValues() {
    std::string name = "Mi nombre es Item!";
    //unsigned int price = 100;
    Item item(ITEM_TYPE_CLOTHING, name/*, price*/);
    bool status = (item.getName() == name);
    //status = status && (item.getPrice() == price);
    status = status && (item.type == ITEM_TYPE_CLOTHING);
    return status;
}

bool ItemTests::testAreNonGoldItemsGold() {
    Chest armour(GameType::PLATE_ARMOR);
    Head helmet(GameType::IRON_HELMET);
    Shield shield(GameType::TURTLE_SHIELD);
    bool status = armour.isGold();
    status = (status || helmet.isGold());
    status = (status || shield.isGold());
    return (!status);
}

bool ItemTests::testIsGoldItemGold() {
    Gold gold(100);
    return (gold.isGold());
}

bool ItemTests::_testCorrectItemsNamesClothing(Configuration& config) {
    Chest chest1(GameType::COMMON_CLOTHING);
    if (chest1.getName() != config.configClothingData(GameType::COMMON_CLOTHING).name) return false;
    Chest chest2(GameType::LEATHER_ARMOR);
    if (chest2.getName() != config.configClothingData(GameType::LEATHER_ARMOR).name) return false;
    Chest chest3(GameType::PLATE_ARMOR);
    if (chest3.getName() != config.configClothingData(GameType::PLATE_ARMOR).name) return false;
    Chest chest4(GameType::BLUE_TUNIC);
    return !(chest4.getName() != config.configClothingData(GameType::BLUE_TUNIC).name);
}

bool ItemTests::_testCorrectItemsNamesHelmets(Configuration& config) {
    Head helmet1(GameType::HOOD);
    if (helmet1.getName() != config.configClothingData(GameType::HOOD).name) return false;
    Head helmet2(GameType::IRON_HELMET);
    if (helmet2.getName() != config.configClothingData(GameType::IRON_HELMET).name) return false;
    Head helmet3(GameType::MAGIC_HAT);
    if (helmet3.getName() != config.configClothingData(GameType::MAGIC_HAT).name) return false;
    Head helmet4(GameType::NO_HELMET);
    return !(helmet4.getName() != config.configClothingData(GameType::NO_HELMET).name);
}

bool ItemTests::_testCorrectItemsNamesShields(Configuration& config) {
    Shield shield1(GameType::IRON_SHIELD);
    if (shield1.getName() != config.configClothingData(GameType::IRON_SHIELD).name) return false;
    Shield shield2(GameType::TURTLE_SHIELD);
    if (shield2.getName() != config.configClothingData(GameType::TURTLE_SHIELD).name) return false;
    Shield shield3(GameType::NO_SHIELD);
    return !(shield3.getName() != config.configClothingData(GameType::NO_SHIELD).name);
}

bool ItemTests::_testCorrectItemsNamesWeapons(Configuration& config) {
    Weapon weapon1(GameType::LONGSWORD);
    if (weapon1.getName() != config.configWeaponData(GameType::LONGSWORD).name) return false;
    Weapon weapon2(GameType::AXE);
    if (weapon2.getName() != config.configWeaponData(GameType::AXE).name) return false;
    Weapon weapon3(GameType::WARHAMMER);
    if (weapon3.getName() != config.configWeaponData(GameType::WARHAMMER).name) return false;
    Weapon weapon4(GameType::ASH_ROD);
    if (weapon4.getName() != config.configWeaponData(GameType::ASH_ROD).name) return false;
    Weapon weapon5(GameType::ELVEN_FLUTE);
    if (weapon5.getName() != config.configWeaponData(GameType::ELVEN_FLUTE).name) return false;
    Weapon weapon6(GameType::LINKED_STAFF);
    if (weapon6.getName() != config.configWeaponData(GameType::LINKED_STAFF).name) return false;
    Weapon weapon7(GameType::SIMPLE_BOW);
    if (weapon7.getName() != config.configWeaponData(GameType::SIMPLE_BOW).name) return false;
    Weapon weapon8(GameType::COMPOSITE_BOW);
    if (weapon8.getName() != config.configWeaponData(GameType::COMPOSITE_BOW).name) return false;
    Weapon weapon9(GameType::GNARLED_STAFF);
    if (weapon9.getName() != config.configWeaponData(GameType::GNARLED_STAFF).name) return false;
    Weapon weapon10(GameType::FIST);
    return !(weapon10.getName() != config.configWeaponData(GameType::FIST).name);
}

bool ItemTests::_testCorrectItemsNamesPotions(Configuration& config) {
    HealthPotion potion1;
    if (potion1.getName() != config.configPotionData(GameType::HEALTH_POTION).name) return false;
    ManaPotion potion2;
    return !(potion2.getName() != config.configPotionData(GameType::MANA_POTION).name);
}

bool ItemTests::testCorrectItemsNames() {
    Configuration& config = Configuration::getInstance();
    bool status = _testCorrectItemsNamesClothing(config);
    status = status && _testCorrectItemsNamesHelmets(config);
    status = status && _testCorrectItemsNamesPotions(config);
    status = status && _testCorrectItemsNamesShields(config);
    status = status && _testCorrectItemsNamesWeapons(config);
    return status;
}

bool ItemTests::testCorrectGoldAmount() {
    unsigned int amount = 504;
    Gold gold(amount);
    return (amount == gold.getamount());
}
