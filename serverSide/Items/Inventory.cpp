//
// Created by agustin on 8/6/20.
//

#include "Inventory.h"

#include "../Map/Coordinate.h"
#include "Attack/Weapon.h"
#include "Defense/Chest.h"
#include "Defense/Head.h"
#include "Defense/Shield.h"
#include <msgpack.hpp>
#include "../Game/Game.h"
#include "../Game/Events/Unequip.h"
#include "ItemsFactory.h"
#include "../Entities/PlayerStats.h"
#include "../Entities/Minichat.h"

#define EMPTY_INVENTORY_MESSAGE "Your inventory is empty\n"

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
        clothingEquipment.at(GameType::EQUIPMENT_PLACE_HEAD) = std::make_shared<Head>(GameType::Clothing::NO_HELMET);
    }
    if (!clothingEquipment.at(GameType::EQUIPMENT_PLACE_CHEST)) {
        clothingEquipment.at(GameType::EQUIPMENT_PLACE_CHEST) = std::make_shared<Chest>(GameType::Clothing::COMMON_CLOTHING);
    }
    if (!clothingEquipment.at(GameType::EQUIPMENT_PLACE_SHIELD)) {
        clothingEquipment.at(GameType::EQUIPMENT_PLACE_SHIELD) = std::make_shared<Shield>(GameType::Clothing::NO_SHIELD);
    }
    if (!equippedWeapon) {
        equippedWeapon = std::make_shared<Weapon>(GameType::Weapon::FIST);
    }
}

void Inventory::_loadInitialInventory(const PlayerData& data) {
    ItemsFactory& iFactory = ItemsFactory::getInstance();
    storedItemsAmount = 0;
    for (int i = 0; i < INVENTORY_SIZE; ++i) {
        iFactory.storeItemInstance(std::get<0>(data.inventory.at(i)),
                std::get<1>(data.inventory.at(i)), items.at(i));
        if (items.at(i) != nullptr) {
            ++storedItemsAmount;
        }
    }
}


//////////////////////////////PUBLIC/////////////////////////////

Inventory::Inventory(const PlayerData& data) : items(INVENTORY_SIZE, nullptr) {
    _loadInitialInventory(data);
    clothingEquipment.emplace(GameType::EQUIPMENT_PLACE_HEAD,
                    std::make_shared<Head>(static_cast<GameType::Clothing>(data.equipment.at(
                            GameType::EQUIPMENT_PLACE_HEAD))));
    clothingEquipment.emplace(GameType::EQUIPMENT_PLACE_CHEST,
                    std::make_shared<Chest>(static_cast<GameType::Clothing>(data.equipment.at(
                    GameType::EQUIPMENT_PLACE_CHEST))));
    clothingEquipment.emplace(GameType::EQUIPMENT_PLACE_SHIELD,
                    std::make_shared<Shield>(static_cast<GameType::Clothing>(data.equipment.at(
                    GameType::EQUIPMENT_PLACE_SHIELD))));
    equippedWeapon = std::make_shared<Weapon>(static_cast<GameType::Weapon>(data.equipment.at(
                                    GameType::EQUIPMENT_PLACE_WEAPON)));
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

int Inventory::getWeaponDamage(Coordinate currentPosition, Coordinate target, PlayerStats& stats) const {
    return equippedWeapon->getDamage(currentPosition, target, stats);
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

void Inventory::getData(PlayerData &pData) const {
    Item* item;
    for (int i = 0; i < INVENTORY_SIZE; ++i) {
        item = items.at(i).get();
        if (item) {
            pData.inventory.at(i) = std::make_tuple(item->getType(), item->getId());
        }
    }
    pData.equipment.at(GameType::EQUIPMENT_PLACE_HEAD) =
            clothingEquipment.at(GameType::EQUIPMENT_PLACE_HEAD)->getId();
    pData.equipment.at(GameType::EQUIPMENT_PLACE_CHEST) =
            clothingEquipment.at(GameType::EQUIPMENT_PLACE_CHEST)->getId();
    pData.equipment.at(GameType::EQUIPMENT_PLACE_SHIELD) =
            clothingEquipment.at(GameType::EQUIPMENT_PLACE_SHIELD)->getId();
    pData.equipment.at(GameType::EQUIPMENT_PLACE_WEAPON) = equippedWeapon->getId();
}

void Inventory::getInventoryNames(Minichat& chat) {
    bool hasItems = false;
    for (unsigned int i = 0; i < items.size(); ++i) {
        if (items.at(i)) {
            chat.addMessage(std::to_string(i) + ": " + items.at(i)->getName() + "\n");
            hasItems = true;
        }
    }
    if (!hasItems) {
        chat.addMessage(EMPTY_INVENTORY_MESSAGE);
    }
}

