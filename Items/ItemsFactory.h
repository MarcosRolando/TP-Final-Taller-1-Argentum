//
// Created by agustin on 16/6/20.
//

#ifndef ARGENTUM_ITEMSFACTORY_H
#define ARGENTUM_ITEMSFACTORY_H

#include <unordered_map>
#include <memory>
#include "Item.h"

typedef void (*objectCreator) (std::shared_ptr<Item>&&);

class ItemsFactory {
    std::unordered_map<std::string, objectCreator> itemsCreators;
};


#endif //ARGENTUM_ITEMSFACTORY_H
