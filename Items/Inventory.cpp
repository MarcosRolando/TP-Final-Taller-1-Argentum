//
// Created by agustin on 8/6/20.
//

#include "Inventory.h"

//////////////////////////////PRIVATE/////////////////////////////

//Mueve el item al lugar de equipamiendo indicado si es que tiene uno
void Inventory::manageItemPlacement(EquipmentPlace equipmentPlace, unsigned int itemPosition) {
    std::shared_ptr<Clothing> clothingPtrAux;
    if (equipmentPlace == EQUIPMENT_PLACE_NONE) {
        return;
    }
    //No deberia pasar porque se recibe el equipmentPlace, pero chequea que el
    //casteo no haya fallado
    clothingPtrAux = std::dynamic_pointer_cast<Clothing>(items[itemPosition]);
    if (clothingPtrAux) {
        items[itemPosition] = std::move(equipment[equipmentPlace]);
        equipment[equipmentPlace] = std::move(clothingPtrAux);
    }
}


//////////////////////////////PUBLIC/////////////////////////////

//CAMBIAR EL 10 POR EL VALOR GUARDADO EN CONFIG
Inventory::Inventory(/*Player& _player*/): /*player(_player), */items(10, nullptr){
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

void Inventory::useItem(Player& player, unsigned int itemPosition) {
    //EquipmentPlace equipmentPlace;
    if (items[itemPosition]) {
        //equipmentPlace = items[itemPosition]->use(player);
        manageItemPlacement(items[itemPosition]->use(player), itemPosition);
    }
}
