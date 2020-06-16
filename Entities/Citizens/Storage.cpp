//
// Created by agustin on 15/6/20.
//

#include "Storage.h"

#include <utility>

Storage::Storage(std::unordered_map<std::string,
                 std::list<std::shared_ptr<Item>>>&& initialItems) noexcept {
    storedItems = std::move(initialItems);
    storedGold = 0;
}

void Storage::storeItem(std::shared_ptr<Item> &&item) {
    storedItems[item->getName()].push_back(std::move(item));
}

void Storage::retreiveItem(const std::string& itemName, Player &player) {
    if (storedItems.count(itemName) == 1) {
        if (!player.storeItem(std::move(storedItems[itemName].front()))) {
            return;
        }
        storedItems[itemName].pop_front();
        if (storedItems[itemName].empty()) {
            storedItems.erase(itemName);
        }
    }
}

unsigned int Storage::getAvailableItems(std::list<ProductData> &products,
                                        float priceMultiplier) {
    for (const auto & storedItem : storedItems) {
        products.emplace_back(storedItem.second.front()->getName(), storedItem.second.size(),
                        storedItem.second.front()->getPrice() * priceMultiplier);
    }
    return storedGold;
}
