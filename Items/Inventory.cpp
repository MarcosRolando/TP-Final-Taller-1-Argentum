//
// Created by agustin on 8/6/20.
//

#include "Inventory.h"


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
            items[itemPosition] = std::move(equippedWeapon);
            equippedWeapon = std::move(weaponPtrAux);
        }
    } else {
        std::shared_ptr<Clothing> clothingPtrAux;
        //No deberia pasar porque se recibe el equipmentPlace, pero chequea que el
        //casteo no haya fallado
        clothingPtrAux = std::dynamic_pointer_cast<Clothing>(items[itemPosition]);
        if (clothingPtrAux) {
            items[itemPosition] = std::move(clothingEquipment.at(equipmentPlace));
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

int Inventory::getWeaponDamage(Coordinate currentPosition, Coordinate target) const {
    return equippedWeapon->getDamage(currentPosition, target);
}

unsigned int Inventory::getDefense() {
    unsigned int defense = 0;
    for (auto & armour : clothingEquipment) {
        defense += armour.second->getDefense();
    }
    return defense;
}
