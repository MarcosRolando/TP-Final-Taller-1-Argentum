//
// Created by marcos on 13/7/20.
//

#include "UpdateManager.h"
#include "../../libs/TPException.h"

void UpdateManager::push(UpdateQueue<std::unique_ptr<UpdateEvent>>& update) {
    std::lock_guard<std::mutex> l(m);
    updates.emplace(std::move(update));
}

UpdateQueue<std::unique_ptr<UpdateEvent>> UpdateManager::pop() {
    std::lock_guard<std::mutex> l(m);
    if (!updates.empty()) {
        auto update = std::move(updates.front());
        updates.pop();
        return update;
    }
    throw TPException("Intentaron tomar un update de una cola vacia!");
}

int UpdateManager::updatesAvailable() {
    std::lock_guard<std::mutex> l(m);
    return updates.size();
}
