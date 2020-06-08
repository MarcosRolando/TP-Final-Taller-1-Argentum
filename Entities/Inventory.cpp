//
// Created by agustin on 8/6/20.
//

#include "Inventory.h"

//CAMBIAR EL 10 POR EL VALOR GUARDADO EN CONFIG
Inventory::Inventory(Player& _player): player(_player), items(10, nullptr){
    storedItemsAmmount = 0;
}

bool Inventory::addItem(std::shared_ptr<Item> &&item) {
    if ((storedItemsAmmount == items.size()) || !item) {
        return false;
    }
    for (int i = 0; i < items.size(); ++i) {
        if (!items[i]) {
            items[i] = std::move(item);
            break;
        }
    }
    storedItemsAmmount++;
    return true;
}

std::shared_ptr<Item> Inventory::removeItem(unsigned int itemPosition) {
    std::shared_ptr<Item> aux = std::move(items[itemPosition]);
    storedItemsAmmount--;
    return aux;
}

void Inventory::useItem(unsigned int itemPosition) {
    if (items[itemPosition]) {
        items[itemPosition]->use(player);
    }
}

/*
unsigned int Inventory::getSize() {
    return items.size();
}
*/