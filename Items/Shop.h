//
// Created by agustin on 10/6/20.
//

#ifndef ARGENTUM_SHOP_H
#define ARGENTUM_SHOP_H

#include <unordered_map>
#include "Item.h"

class Shop {
private:
    std::unordered_map<std::string, Item> storedProducts;
public:
    //Se apropia de los contenidos de initialProducts
    explicit Shop(std::unordered_map<std::string, Item>&& initialProducts) noexcept;
};


#endif //ARGENTUM_SHOP_H
