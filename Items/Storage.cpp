//
// Created by agustin on 15/6/20.
//

#include "Storage.h"

#include <utility>

Storage::Storage(std::unordered_map<std::string,
                 std::list<std::shared_ptr<Item>>>&& initialItems) noexcept {
    storedItems = std::move(initialItems);
}

void Storage::addItem(std::shared_ptr<Item> &&item) {
    storedItems[item->getName()].push_back(std::move(item));
}

void Storage::retreiveItem(std::string itemName, Player &player) {
    if (storedItems.count(itemName) == 1) {

    }
}
