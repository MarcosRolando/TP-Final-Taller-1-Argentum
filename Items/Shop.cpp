//
// Created by agustin on 10/6/20.
//

#include "Shop.h"

Shop::Shop(std::unordered_map<std::string, Item>&& initialProducts) noexcept {
    storedProducts = std::move(initialProducts);
}
