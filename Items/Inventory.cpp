//
// Created by agustin on 8/6/20.
//

#include "Inventory.h"

#include "../Map/Coordinate.h"
#include "../Items/Attack/Weapon.h"
#include "../Items/Defense/Chest.h"
#include "../Items/Defense/Head.h"
#include "../Items/Defense/Shield.h"
#include <msgpack.hpp>
#include "../Game/Game.h"
#include "../Game/Events/Unequip.h"

MSGPACK_ADD_ENUM(GameType::ItemType)

#define INVENTORY_SIZE 16

//////////////////////////////PRIVATE/////////////////////////////
//Mueve el item al lugar de equipamiendo indicado si es que tiene uno
UseReturnData Inventory::_manageItemPlacement(GameType::EquipmentPlace equipmentPlace, unsigned int itemPosition) {
    if (equipmentPlace == GameType::EQUIPMENT_PLACE_NONE) {
        items[itemPosition] = nullptr;
        storedItemsAmount--;
        return {GameType::EQUIPMENT_PLACE_NONE, -1};
    }
    if (equipmentPlace == GameType::EQUIPMENT_PLACE_WEAPON) {
        std::shared_ptr<Weapon> weaponPtrAux;
        weaponPtrAux = std::dynamic_pointer_cast<Weapon>(items[itemPosition]);
        if (weaponPtrAux) {
            if (!equippedWeapon->isDefault()) {
                items[itemPosition] = std::move(equippedWeapon);
            } else {
                items[itemPosition] = nullptr;
                storedItemsAmount--;
            }
            equippedWeapon = std::move(weaponPtrAux);
            return {GameType::EQUIPMENT_PLACE_WEAPON, equippedWeapon->getId()};
        }
    } else {
        std::shared_ptr<Clothing> clothingPtrAux;
        clothingPtrAux = std::dynamic_pointer_cast<Clothing>(items[itemPosition]);
        if (clothingPtrAux) {
            if (!clothingEquipment.at(equipmentPlace)->isDefault()) {
                items[itemPosition] = std::move(clothingEquipment.at(equipmentPlace));
            } else {
                items[itemPosition] = nullptr;
                storedItemsAmount--;
            }
            clothingEquipment.at(equipmentPlace) = std::move(clothingPtrAux);
            return {equipmentPlace, clothingEquipment.at(equipmentPlace)->getId()};
        }
    }
    return {GameType::EQUIPMENT_PLACE_NONE, -1};
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
    _restoreDefaultEquipment();
}


void Inventory::_storeNullItemData(std::stringstream &buffer) {
    msgpack::type::tuple<GameType::ItemType, int32_t> data(GameType::ITEM_TYPE_NONE, 0);
    msgpack::pack(buffer, data);
}


void Inventory::_restoreDefaultEquipment() {
    if (!clothingEquipment.at(GameType::EQUIPMENT_PLACE_HEAD)) {
        clothingEquipment.at(GameType::EQUIPMENT_PLACE_HEAD).reset(new Head(GameType::Clothing::NO_HELMET));
    }
    if (!clothingEquipment.at(GameType::EQUIPMENT_PLACE_CHEST)) {
        clothingEquipment.at(GameType::EQUIPMENT_PLACE_CHEST).reset(new Chest(GameType::Clothing::COMMON_CLOTHING));
    }
    if (!clothingEquipment.at(GameType::EQUIPMENT_PLACE_SHIELD)) {
        clothingEquipment.at(GameType::EQUIPMENT_PLACE_SHIELD).reset(new Shield(GameType::Clothing::NO_SHIELD));
    }
    if (!equippedWeapon) {
        equippedWeapon.reset(new Weapon(GameType::Weapon::FIST));
    }
}


//////////////////////////////PUBLIC/////////////////////////////

Inventory::Inventory() : items(INVENTORY_SIZE, nullptr) {
    storedItemsAmount = 0;
    clothingEquipment.emplace(GameType::EQUIPMENT_PLACE_HEAD, new Head(GameType::Clothing::NO_HELMET));
    clothingEquipment.emplace(GameType::EQUIPMENT_PLACE_CHEST, new Chest(GameType::Clothing::COMMON_CLOTHING));
    clothingEquipment.emplace(GameType::EQUIPMENT_PLACE_SHIELD, new Shield(GameType::Clothing::NO_SHIELD));
    equippedWeapon.reset(new Weapon(GameType::Weapon::FIST));
}

bool Inventory::addItem(std::shared_ptr<Item> &item) {
    if ((storedItemsAmount == items.size()) || !item) {
        return false;
    }
    for (auto & i : items) {
        if (!i) {
            i = std::move(item);
            break;
        }
    }
    ++storedItemsAmount;
    return true;
}

std::shared_ptr<Item> Inventory::removeItem(unsigned int itemPosition) {
    std::shared_ptr<Item> aux = std::move(items[itemPosition]);
    if (aux) {
        --storedItemsAmount;
    }
    return aux;
}

UseReturnData Inventory::useItem(Player& player, unsigned int itemPosition) {
    if (items[itemPosition]) {
        return _manageItemPlacement(items[itemPosition]->use(player), itemPosition);
    }
    return {GameType::EQUIPMENT_PLACE_NONE, -1};
}

std::shared_ptr<Item> Inventory::removeItem(const std::string &itemName) {
    std::shared_ptr<Item> returnItem(nullptr);
    for (auto & item : items) {
        if (item) {
            if (itemName == item->getName()) {
                returnItem = std::move(item);
                --storedItemsAmount;
                break;
            }
        }
    }
    return returnItem;
}

int Inventory::getWeaponDamage(Coordinate currentPosition, Coordinate target,
                               int32_t& currentMana) const {
    return equippedWeapon->getDamage(currentPosition, target, currentMana);
}

unsigned int Inventory::getDefense() {
    unsigned int defense = 0;
    for (auto & armour : clothingEquipment) {
        defense += armour.second->getDefense();
    }
    return defense;
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

bool Inventory::unequip(GameType::EquipmentPlace clothing) {
    if (clothingEquipment.at(clothing)->isDefault()) {
        return false;
    }
    for (auto & item : items) {
        if (!item) {
            item = std::move(clothingEquipment.at(clothing));
            _restoreDefaultEquipment();
            return true;
        }
    }
    return false;
}

bool Inventory::unequip() {
    if (equippedWeapon->isDefault()) {
        return false;
    }
    for (auto & item : items) {
        if (!item) {
            item = std::move(equippedWeapon);
            ++storedItemsAmount;
            _restoreDefaultEquipment();
            return true;
        }
    }
    return false;
}

void Inventory::storeEquippedItems(std::stringstream &buffer) const {
    clothingEquipment.at(GameType::EQUIPMENT_PLACE_HEAD)->loadEquippedItemData(buffer);
    clothingEquipment.at(GameType::EQUIPMENT_PLACE_CHEST)->loadEquippedItemData(buffer);
    clothingEquipment.at(GameType::EQUIPMENT_PLACE_SHIELD)->loadEquippedItemData(buffer);
    equippedWeapon->loadEquippedItemData(buffer);
}

void Inventory::storeAllData(std::stringstream &buffer) const {
    storeEquippedItems(buffer);
    for (const auto & item: items) {
        if (item) {
            item->loadTypeAndId(buffer);
        } else {
            _storeNullItemData(buffer);
        }
    }
}

int32_t Inventory::getWeaponId() {
    return equippedWeapon->getId();
}

bool Inventory::hasItem(const std::string &itemName) {
    for (auto & item : items) {
        if (item) {
            if (itemName == item->getName()) {
                return true;
            }
        }
    }
    return false;
}
