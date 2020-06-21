//
// Created by agustin on 8/6/20.
//

#include "Inventory.h"
#include "Defense/Head/NoHelmet.h"
#include "Attack/Fist.h"
#include "../Map/Coordinate.h"
#include "Defense/Chest/CommonClothing.h"
#include "Defense/Shield/NoShield.h"

#define INVENTORY_SIZE 16

//////////////////////////////PRIVATE/////////////////////////////
//Mueve el item al lugar de equipamiendo indicado si es que tiene uno
void Inventory::_manageItemPlacement(EquipmentPlace equipmentPlace, unsigned int itemPosition) {
    if (equipmentPlace == EQUIPMENT_PLACE_NONE) {
        return;
    }
    if (equipmentPlace == EQUIPMENT_PLACE_WEAPON) {
        std::shared_ptr<Weapon> weaponPtrAux;
        weaponPtrAux = std::dynamic_pointer_cast<Weapon>(items[itemPosition]);
        if (weaponPtrAux) {
            if (!equippedWeapon->isDefault()) {
                items[itemPosition] = std::move(equippedWeapon);
            }
            equippedWeapon = std::move(weaponPtrAux);
        }
    } else {
        std::shared_ptr<Clothing> clothingPtrAux;
        clothingPtrAux = std::dynamic_pointer_cast<Clothing>(items[itemPosition]);
        if (clothingPtrAux) {
            if (!clothingEquipment.at(equipmentPlace)->isDefault()) {
                items[itemPosition] = std::move(clothingEquipment.at(equipmentPlace));
            }
            clothingEquipment.at(equipmentPlace) = std::move(clothingPtrAux);
        }
    }
}

//////////////////////////////PUBLIC/////////////////////////////

Inventory::Inventory(): items(INVENTORY_SIZE, nullptr){
    storedItemsamount = 0;
}

bool Inventory::addItem(std::shared_ptr<Item> &&item) {
    if ((storedItemsamount == items.size()) || !item) {
        return false;
    }
    for (auto & i : items) {
        if (!i) {
            i = std::move(item);
            break;
        }
    }
    ++storedItemsamount;
    return true;
}

std::shared_ptr<Item> Inventory::removeItem(unsigned int itemPosition) {
    std::shared_ptr<Item> aux = std::move(items[itemPosition]);
    --storedItemsamount;
    return aux;
}

void Inventory::useItem(Player& player, unsigned int itemPosition) {
    if (items[itemPosition]) {
        _manageItemPlacement(items[itemPosition]->use(player), itemPosition);
    }
}

std::shared_ptr<Item> Inventory::removeItem(const std::string &itemName) {
    std::shared_ptr<Item> returnItem(nullptr);
    std::hash<std::string> stringHash;
    unsigned int itemNameHash = stringHash(itemName);
    for (auto & item : items) {
        if ((stringHash(item->getName()) == itemNameHash) &&
            (itemName == item->getName())) {
            returnItem = std::move(item);
            --storedItemsamount;
            break;
        }
    }
    return returnItem;
}

int Inventory::getWeaponDamage(Coordinate currentPosition, Coordinate target,
                                unsigned int& currentMana) const {
    return equippedWeapon->getDamage(currentPosition, target, currentMana);
}

unsigned int Inventory::getDefense() {
    unsigned int defense = 0;
    for (auto & armour : clothingEquipment) {
        defense += armour.second->getDefense();
    }
    return defense;
}

void Inventory::_dropEquippedItems(std::list<std::shared_ptr<Item>>& droppedItems) {
    for (auto & armour : clothingEquipment) {
        if (!armour.second->isDefault()) {
            droppedItems.push_back(std::move(armour.second));
        }
    }
    if (!equippedWeapon->isDefault()) {
        droppedItems.push_back(std::move(equippedWeapon));
    }
    clothingEquipment.emplace(EQUIPMENT_PLACE_HEAD, new NoHelmet());
    clothingEquipment.emplace(EQUIPMENT_PLACE_CHEST, new CommonClothing());
    clothingEquipment.emplace(EQUIPMENT_PLACE_SHIELD, new NoShield());
    equippedWeapon.reset(new Fist());
}

std::list<std::shared_ptr<Item>> Inventory::dropAllItems() {
    std::list<std::shared_ptr<Item>> droppedItems;
    for (int i = 0; i < INVENTORY_SIZE; ++i) {
        if (items[i]) {
            droppedItems.push_back(std::move(items[i]));
        }
    }
    _dropEquippedItems(droppedItems);
    return droppedItems;
}

void Inventory::unequip(EquipmentPlace clothing) {
    if (clothingEquipment.at(clothing)->isDefault()) return;
    for (auto & item : items) {
        if (!item) {
            item = std::move(clothingEquipment.at(clothing));
            break;
        }
    }
}

void Inventory::unequip() {
    if (equippedWeapon->isDefault()) return;
    for (auto & item : items) {
        if (!item) {
            item = std::move(equippedWeapon);
            break;
        }
    }
}
