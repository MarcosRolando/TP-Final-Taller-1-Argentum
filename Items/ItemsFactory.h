//
// Created by agustin on 16/6/20.
//

#ifndef ARGENTUM_ITEMSFACTORY_H
#define ARGENTUM_ITEMSFACTORY_H

#include <unordered_map>
#include <memory>
#include "Item.h"

typedef void (*objectCreator) (std::shared_ptr<Item>&);

class ItemsFactory {
private:
    std::unordered_map<std::string, objectCreator> itemsCreators;
private:

public:
    ItemsFactory();

    //Guarda una instancia del item pedido en item, si el nombre del item pasado
    //no existe entonces tira la exepcion out_of_range
    void storeItemInstance(std::string itemName, std::shared_ptr<Item>& item);
};


#endif //ARGENTUM_ITEMSFACTORY_H
