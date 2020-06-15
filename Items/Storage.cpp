//
// Created by agustin on 15/6/20.
//

#include "Storage.h"


Storage::Storage(std::unordered_map<std::string, std::list<Item>>&& initialProducts) noexcept {
    storedItems = std::move(initialProducts);
}
