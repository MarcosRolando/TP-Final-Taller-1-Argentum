//
// Created by agustin on 15/6/20.
//

#include "Storage.h"
#include "../../Items/ItemsFactory.h"
#include <utility>
#include "../../Items/Item.h"
#include "../Player.h"
#include "msgpack.hpp"
#include "../../Config/Configuration.h"

MSGPACK_ADD_ENUM(GameType::EventID)

#define UNEXISTING_ITEM_MESSAGE "The requested item is not available\n"

Storage &Storage::operator=(Storage &&other) noexcept {
    storedGold = other.storedGold;
    other.storedGold = 0;
    storedItems = std::move(other.storedItems);
    return *this;
}

Storage::Storage(Storage &&other) noexcept {
    storedGold = other.storedGold;
    other.storedGold = 0;
    storedItems = std::move(other.storedItems);
}

Storage::Storage(const std::unordered_map<std::string, unsigned int>&
                 initialItemsAmounts, unsigned int gold) {
    storedGold = gold;
    ItemsFactory& factory = ItemsFactory::getInstance();
    std::shared_ptr<Item> aux;
    for (const auto & initialItemAmount: initialItemsAmounts) {
        for (unsigned int i = 0; i < initialItemAmount.second; ++i) {
            factory.storeItemInstance(initialItemAmount.first, aux);
            storedItems[initialItemAmount.first].push_back(std::move(aux));
        }
    }
}

bool Storage::storeItem(std::shared_ptr<Item> &&item) {
    if (item) {
        storedItems[item->getName()].push_back(std::move(item));
        return true;
    }
    return false;
}

bool Storage::retreiveItem(const std::string& itemName, Player &player) {
    std::shared_ptr<Item> item;
    if (storedItems.count(itemName) == 1) {
        item = storedItems.at(itemName).front();
        if (!player.storeItem(item)) {
            return false;
        }
        storedItems[itemName].pop_front();
        if (storedItems[itemName].empty()) {
            storedItems.erase(itemName);
        }
    }
    player.addMessage(UNEXISTING_ITEM_MESSAGE);
    return false;
}

void Storage::getStorageData(Player& player, const std::unordered_map<std::string, unsigned int> &prices,
                             float priceMultiplier) const {
    _addAmmountMessageToPlayer(player, Configuration::getInstance().configGetGoldName(), storedGold);
    for (const auto & storedItem : storedItems) {
        _addAmmountMessageToPlayer(player, storedItem.second.front()->getName(),
                                   prices.at(storedItem.first) * priceMultiplier);
    }
}

void Storage::getStorageData(Player& player) const {
    _addAmmountMessageToPlayer(player, Configuration::getInstance().configGetGoldName(), storedGold);
    for (const auto & storedItem : storedItems) {
        _addAmmountMessageToPlayer(player, storedItem.second.front()->getName(),
                                   storedItem.second.size());
    }
}


bool Storage::isItemAvailable(const std::string &itemName) const {
    return storedItems.count(itemName) == 1;
}

void Storage::increaseGoldReserves(int amount) {
    storedGold += amount;
}

bool Storage::decreaseGoldReserves(int amount) {
    if (amount <= storedGold) {
        storedGold -= amount;
        return true;
    }
    return false;
}

Storage::Storage() {
    storedGold = 0;
}

///////////////////////////////PRIVATE/////////////////////////////

void Storage::_addAmmountMessageToPlayer(Player &player, const std::string &itemName,
                                         int concatenatedNumber) const {
    player.addMessage(itemName);
    player.addMessage(": ");
    player.addMessage(std::to_string(concatenatedNumber));
    player.addMessage("\n");
}
