//
// Created by agustin on 15/6/20.
//

#include "Storage.h"
#include "../../Items/ItemsFactory.h"
#include <utility>

Storage::Storage(const std::unordered_map<std::string, unsigned int>&
                 initialItemsAmounts, unsigned int initialGold) {
    storedGold = initialGold;
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
    storedItems[item->getName()].push_back(std::move(item));
}

void Storage::retreiveItem(const std::string& itemName, Player &player) {
    if (storedItems.count(itemName) == 1) {
        if (!player.storeItem(std::move(storedItems[itemName].front()))) { //todo VER SI ACA NO DEBERIAMOS USAR AT EN VEZ DE []
            return;
        }
        storedItems[itemName].pop_front();
        if (storedItems[itemName].empty()) {
            storedItems.erase(itemName);
        }
    }
}

unsigned int Storage::getStorageData(std::list<ProductData> &products,
                                        float priceMultiplier) const{
    for (const auto & storedItem : storedItems) {
        products.emplace_back(storedItem.second.front()->getName(), storedItem.second.size(),
                        storedItem.second.front()->getPrice() * priceMultiplier);
    }
    return storedGold;
}

bool Storage::isItemAvailable(const std::string &itemName) const {
    return storedItems.count(itemName) == 1;
}

unsigned int Storage::getItemPrice(const std::string &itemName) const {
    return storedItems.at(itemName).front()->getPrice();
}

void Storage::increaseGoldReserves(unsigned int amount) {
    storedGold += amount;
}

bool Storage::decreaseGoldReserves(unsigned int amount) {
    if (amount <= storedGold) {
        storedGold -= amount;
        return true;
    }
    return false;
}
