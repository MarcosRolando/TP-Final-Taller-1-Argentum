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
    unsigned int price = 100;
    Item item(ITEM_TYPE_CLOTHING, name, price);
    bool status = (item.getName() == name);
    status = status && (item.getPrice() == price);
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

bool ItemTests::_testCorrectItemsNamesClothing() {
    Chest chest1(GameType::COMMON_CLOTHING);
    if (chest1.getName() != "CommonClothing") return false;
    Chest chest2(GameType::LEATHER_ARMOR);
    if (chest2.getName() != "LeatherArmor") return false;
    Chest chest3(GameType::PLATE_ARMOR);
    if (chest3.getName() != "PlateArmor") return false;
    Chest chest4(GameType::BLUE_TUNIC);
    return !(chest4.getName() != "BlueTunic");
}

bool ItemTests::_testCorrectItemsNamesHelmets() {
    Head helmet1(GameType::HOOD);
    if (helmet1.getName() != "Hood") return false;
    Head helmet2(GameType::IRON_HELMET);
    if (helmet2.getName() != "IronHelmet") return false;
    Head helmet3(GameType::MAGIC_HAT);
    if (helmet3.getName() != "MagicHat") return false;
    Head helmet4(GameType::NO_HELMET);
    return !(helmet4.getName() != "NoHelmet");
}

bool ItemTests::_testCorrectItemsNamesShields() {
    Shield shield1(GameType::IRON_SHIELD);
    if (shield1.getName() != "IronShield") return false;
    Shield shield2(GameType::TURTLE_SHIELD);
    if (shield2.getName() != "TurtleShield") return false;
    Shield shield3(GameType::NO_SHIELD);
    return !(shield3.getName() != "NoShield");
}

bool ItemTests::_testCorrectItemsNamesWeapons() {
    Weapon weapon1(GameType::LONGSWORD);
    if (weapon1.getName() != "Longsword") return false;
    Weapon weapon2(GameType::AXE);
    if (weapon2.getName() != "Axe") return false;
    Weapon weapon3(GameType::WARHAMMER);
    if (weapon3.getName() != "Warhammer") return false;
    Weapon weapon4(GameType::ASH_ROD);
    if (weapon4.getName() != "AshRod") return false;
    Weapon weapon5(GameType::ELVEN_FLUTE);
    if (weapon5.getName() != "ElvenFlute") return false;
    Weapon weapon6(GameType::LINKED_STAFF);
    if (weapon6.getName() != "LinkedStaff") return false;
    Weapon weapon7(GameType::SIMPLE_BOW);
    if (weapon7.getName() != "SimpleBow") return false;
    Weapon weapon8(GameType::COMPOSITE_BOW);
    if (weapon8.getName() != "CompositeBow") return false;
    Weapon weapon9(GameType::GNARLED_STAFF);
    if (weapon9.getName() != "GnarledStaff") return false;
    Weapon weapon10(GameType::FIST);
    return !(weapon10.getName() != "Fist");
}

bool ItemTests::_testCorrectItemsNamesPotions() {
    HealthPotion potion1;
    if (potion1.getName() != "HealthPotion") return false;
    ManaPotion potion2;
    return !(potion2.getName() != "ManaPotion");
}

bool ItemTests::testCorrectItemsNames() {
    bool status = _testCorrectItemsNamesClothing();
    status = status && _testCorrectItemsNamesHelmets();
    status = status && _testCorrectItemsNamesPotions();
    status = status && _testCorrectItemsNamesShields();
    status = status && _testCorrectItemsNamesWeapons();
    return status;
}
