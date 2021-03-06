//
// Created by marcos on 13/7/20.
//

#include "UpdateManager.h"
#include "../../libs/TPException.h"

void UpdateManager::push(Update& update) {
    std::lock_guard<std::mutex> l(m);
    updates.emplace(std::move(update));
}

Update UpdateManager::pop() {
    std::lock_guard<std::mutex> l(m);
    if (!updates.empty()) {
        auto update = std::move(updates.front());
        updates.pop();
        return update;
    }
    throw TPException("An update was requested from an empty queue!");
}

int UpdateManager::updatesAvailable() {
    std::lock_guard<std::mutex> l(m);
    return updates.size();
}
