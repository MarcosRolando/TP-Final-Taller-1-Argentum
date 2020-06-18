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
    ItemsFactory();

    void storeBlueTunic(std::shared_ptr<Item>& item);
    void storeLeatherArmor(std::shared_ptr<Item>& item);
    void storePlateArmor(std::shared_ptr<Item>& item);

    void storeHood(std::shared_ptr<Item>& item);
    void storeIronHelmet(std::shared_ptr<Item>& item);
    void storeMagicHat(std::shared_ptr<Item>& item);

    void storeIronShield(std::shared_ptr<Item>& item);
    void storeTurtleShield(std::shared_ptr<Item>& item);

    void storeAshRod(std::shared_ptr<Item>& item);
    void storeCompositeBow(std::shared_ptr<Item>& item);
    void storeElvenFlute(std::shared_ptr<Item>& item);
    void storeGnarledStaff(std::shared_ptr<Item>& item);
    void storeLinkedStaff(std::shared_ptr<Item>& item);
    void storeLongsword(std::shared_ptr<Item>& item);
    void storeSimpleBow(std::shared_ptr<Item>& item);
    void storeWarhammer(std::shared_ptr<Item>& item);

    //VER COMO SE TRATA EL CASO ESPECIAL DE GOLD
    void storeGold(std::shared_ptr<Item>& item, unsigned int ammount);

public:

    static ItemsFactory& getInstance();

    //Guarda una instancia del item pedido en item, si el nombre del item pasado
    //no existe entonces tira la exepcion out_of_range
    void storeItemInstance(std::string itemName, std::shared_ptr<Item>& item);
};


#endif //ARGENTUM_ITEMSFACTORY_H
