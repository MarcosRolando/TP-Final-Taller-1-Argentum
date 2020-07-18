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
    Item item(GameType::ITEM_TYPE_CLOTHING, name/*, price*/);
    bool status = (item.getName() == name);
    status = status && (item.type == GameType::ITEM_TYPE_CLOTHING);
    return status;
}

bool ItemTests::testAreNonGoldItemsGold() {
    Chest armour(GameType::Clothing::PLATE_ARMOR);
    Head helmet(GameType::Clothing::IRON_HELMET);
    Shield shield(GameType::Clothing::TURTLE_SHIELD);
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
    Chest chest1(GameType::Clothing::COMMON_CLOTHING);
    if (chest1.getName() != config.configClothingData(GameType::Clothing::COMMON_CLOTHING).name) return false;
    Chest chest2(GameType::Clothing::LEATHER_ARMOR);
    if (chest2.getName() != config.configClothingData(GameType::Clothing::LEATHER_ARMOR).name) return false;
    Chest chest3(GameType::Clothing::PLATE_ARMOR);
    if (chest3.getName() != config.configClothingData(GameType::Clothing::PLATE_ARMOR).name) return false;
    Chest chest4(GameType::Clothing::BLUE_TUNIC);
    return !(chest4.getName() != config.configClothingData(GameType::Clothing::BLUE_TUNIC).name);
}

bool ItemTests::_testCorrectItemsNamesHelmets(Configuration& config) {
    Head helmet1(GameType::Clothing::HOOD);
    if (helmet1.getName() != config.configClothingData(GameType::Clothing::HOOD).name) return false;
    Head helmet2(GameType::Clothing::IRON_HELMET);
    if (helmet2.getName() != config.configClothingData(GameType::Clothing::IRON_HELMET).name) return false;
    Head helmet3(GameType::Clothing::MAGIC_HAT);
    if (helmet3.getName() != config.configClothingData(GameType::Clothing::MAGIC_HAT).name) return false;
    Head helmet4(GameType::Clothing::NO_HELMET);
    return !(helmet4.getName() != config.configClothingData(GameType::Clothing::NO_HELMET).name);
}

bool ItemTests::_testCorrectItemsNamesShields(Configuration& config) {
    Shield shield1(GameType::Clothing::IRON_SHIELD);
    if (shield1.getName() != config.configClothingData(GameType::Clothing::IRON_SHIELD).name) return false;
    Shield shield2(GameType::Clothing::TURTLE_SHIELD);
    if (shield2.getName() != config.configClothingData(GameType::Clothing::TURTLE_SHIELD).name) return false;
    Shield shield3(GameType::Clothing::NO_SHIELD);
    return !(shield3.getName() != config.configClothingData(GameType::Clothing::NO_SHIELD).name);
}

bool ItemTests::_testCorrectItemsNamesWeapons(Configuration& config) {
    Weapon weapon1(GameType::Weapon::LONGSWORD);
    if (weapon1.getName() != config.configWeaponData(GameType::Weapon::LONGSWORD).name) return false;
    Weapon weapon2(GameType::Weapon::AXE);
    if (weapon2.getName() != config.configWeaponData(GameType::Weapon::AXE).name) return false;
    Weapon weapon3(GameType::Weapon::WARHAMMER);
    if (weapon3.getName() != config.configWeaponData(GameType::Weapon::WARHAMMER).name) return false;
    Weapon weapon4(GameType::Weapon::ASH_ROD);
    if (weapon4.getName() != config.configWeaponData(GameType::Weapon::ASH_ROD).name) return false;
    Weapon weapon5(GameType::Weapon::ELVEN_FLUTE);
    if (weapon5.getName() != config.configWeaponData(GameType::Weapon::ELVEN_FLUTE).name) return false;
    Weapon weapon6(GameType::Weapon::LINKED_STAFF);
    if (weapon6.getName() != config.configWeaponData(GameType::Weapon::LINKED_STAFF).name) return false;
    Weapon weapon7(GameType::Weapon::SIMPLE_BOW);
    if (weapon7.getName() != config.configWeaponData(GameType::Weapon::SIMPLE_BOW).name) return false;
    Weapon weapon8(GameType::Weapon::COMPOSITE_BOW);
    if (weapon8.getName() != config.configWeaponData(GameType::Weapon::COMPOSITE_BOW).name) return false;
    Weapon weapon9(GameType::Weapon::GNARLED_STAFF);
    if (weapon9.getName() != config.configWeaponData(GameType::Weapon::GNARLED_STAFF).name) return false;
    Weapon weapon10(GameType::Weapon::FIST);
    return !(weapon10.getName() != config.configWeaponData(GameType::Weapon::FIST).name);
}

bool ItemTests::_testCorrectItemsNamesPotions(Configuration& config) {
    HealthPotion potion1;
    if (potion1.getName() != config.configPotionData(GameType::Potion::HEALTH_POTION).name) return false;
    ManaPotion potion2;
    return !(potion2.getName() != config.configPotionData(GameType::Potion::MANA_POTION).name);
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
    return (amount == gold.getAmount());
}
