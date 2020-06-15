//
// Created by agustin on 15/6/20.
//

#include "Storage.h"

#include <utility>

Storage::Storage(std::unordered_map<std::string,
                 std::list<std::shared_ptr<Item>>>&& initialItems) noexcept {
    storedItems = std::move(initialItems);
}

void Storage::storeItem(std::shared_ptr<Item> &&item) {
    storedItems[item->getName()].push_back(std::move(item));
}

bool Storage::retreiveItem(std::string itemName, Player &player) {
    if (storedItems.count(itemName) == 1) {
        if (!player.storeItem(std::move(storedItems[itemName].front()))) {
            return false;
        }
        storedItems[itemName].pop_front();
        if (storedItems[itemName].empty()) {
            storedItems.erase(itemName);
        }
        return true;
    }
    return false;
}
