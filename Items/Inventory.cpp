//
// Created by agustin on 8/6/20.
//

#include "Inventory.h"


#define INVENTORY_SIZE 10


//////////////////////////////PRIVATE/////////////////////////////
//Mueve el item al lugar de equipamiendo indicado si es que tiene uno
void Inventory::manageItemPlacement(EquipmentPlace equipmentPlace, unsigned int itemPosition) {
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
            items[itemPosition] = std::move(clothingEequipment.at(equipmentPlace));
            clothingEequipment.at(equipmentPlace) = std::move(clothingPtrAux);
        }
    }
}

//////////////////////////////PUBLIC/////////////////////////////

Inventory::Inventory(): items(INVENTORY_SIZE, nullptr){
    storedItemsAmmount = 0;

}



bool Inventory::addItem(std::shared_ptr<Item> &&item) {
    if ((storedItemsAmmount == items.size()) || !item) {
        return false;
    }
    for (int i = 0; i < (int)items.size(); ++i) {
        if (!items[i]) {
            items[i] = std::move(item);
            break;
        }
    }
    storedItemsAmmount++;
    return true;
}

std::shared_ptr<Item> Inventory::removeItem(unsigned int itemPosition) {
    std::shared_ptr<Item> aux = std::move(items[itemPosition]);
    storedItemsAmmount--;
    return aux;
}

void Inventory::useItem(Player& player, unsigned int itemPosition) {
    if (items[itemPosition]) {
        manageItemPlacement(items[itemPosition]->use(player), itemPosition);
    }
}

std::shared_ptr<Item> Inventory::removeItem(const std::string &itemName) {
    std::shared_ptr<Item> returnItem(nullptr);
    std::hash<std::string> stringHash;
    unsigned int itemNameHash = stringHash(itemName);
    for (int i = 0; i < items.size(); ++i) {
        if ((stringHash(items[i]->getName()) == itemNameHash) &&
            (itemName == items[i]->getName())) {
            returnItem = std::move(items[i]);
            storedItemsAmmount--;
            break;
        }
    }
    return returnItem;
}
