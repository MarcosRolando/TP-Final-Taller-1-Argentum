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
