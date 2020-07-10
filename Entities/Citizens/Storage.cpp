//
// Created by agustin on 15/6/20.
//

#include "Storage.h"
#include "../../Items/ItemsFactory.h"
#include <utility>
#include "../../Items/Item.h"
#include "../Player.h"
#include "msgpack.hpp"

MSGPACK_ADD_ENUM(GameType::EventID)

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

void Storage::storeItem(std::shared_ptr<Item> &&item) {
    if (item) {
        storedItems[item->getName()].push_back(std::move(item));
    }
}

void Storage::retreiveItem(const std::string& itemName, Player &player) {
    std::shared_ptr<Item> item;
    if (storedItems.count(itemName) == 1) {
        item = storedItems.at(itemName).front();
        if (!player.storeItem(item)) {
            return;
        }
        storedItems[itemName].pop_front();
        if (storedItems[itemName].empty()) {
            storedItems.erase(itemName);
        }
    }
}

/*
unsigned int Storage::getStorageData(std::list<ProductData> &products,
                                     const std::unordered_map<std::string, unsigned int>& prices,
                                     float priceMultiplier) const{
    for (const auto & storedItem : storedItems) {
        products.emplace_back(storedItem.second.front()->getName(), storedItem.second.size(),
                              prices.at(storedItem.first) * priceMultiplier);
    }
    return storedGold;
}
*/

void Storage::getStorageData(Player& player, const std::unordered_map<std::string, unsigned int> &prices,
                             float priceMultiplier) const {
    _addAmmountMessageToPlayer(player, "Gold", storedGold);
    for (const auto & storedItem : storedItems) {
        _addAmmountMessageToPlayer(player, storedItem.second.front()->getName(),
                                   prices.at(storedItem.first) * priceMultiplier);
        /*
        msgpack::type::tuple<std::string, int32_t, int32_t> productData
                (storedItem.second.front()->getName(), storedItem.second.size(), prices.at(storedItem.first) * priceMultiplier);
        msgpack::pack(data, productData);
        */
    }
}



/*
unsigned int Storage::getStorageData(std::list<ProductData> &products) const {
    for (const auto & storedItem : storedItems) {
        products.emplace_back(storedItem.second.front()->getName(), storedItem.second.size(), 0);
    }
    return storedGold;
}
*/

void Storage::getStorageData(Player& player) const {
    _addAmmountMessageToPlayer(player, "Gold", storedGold);
    for (const auto & storedItem : storedItems) {
        _addAmmountMessageToPlayer(player, storedItem.second.front()->getName(),
                                   storedItem.second.size());
    }
}


bool Storage::isItemAvailable(const std::string &itemName) const {
    return storedItems.count(itemName) == 1;
}

/*
unsigned int Storage::getItemPrice(const std::string &itemName) const {
    return storedItems.at(itemName).front()->getPrice();
}
*/

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
