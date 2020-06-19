//
// Created by agustin on 16/6/20.
//

#ifndef ARGENTUM_ITEMSFACTORY_H
#define ARGENTUM_ITEMSFACTORY_H

#include <unordered_map>
#include <memory>
#include <vector>
#include "Item.h"

typedef void (*objectCreator) (std::shared_ptr<Item>&);

class ItemsFactory {
private:
    std::unordered_map<std::string, objectCreator> itemsCreators;
    std::vector<const std::string*> itemsNames;
private:
    ItemsFactory();

    static void storeBlueTunic(std::shared_ptr<Item>& item);
    static void storeLeatherArmor(std::shared_ptr<Item>& item);
    static void storePlateArmor(std::shared_ptr<Item>& item);

    static void storeHood(std::shared_ptr<Item>& item);
    static void storeIronHelmet(std::shared_ptr<Item>& item);
    static void storeMagicHat(std::shared_ptr<Item>& item);

    static void storeIronShield(std::shared_ptr<Item>& item);
    static void storeTurtleShield(std::shared_ptr<Item>& item);

    static void storeAshRod(std::shared_ptr<Item>& item);
    static void storeCompositeBow(std::shared_ptr<Item>& item);
    static void storeElvenFlute(std::shared_ptr<Item>& item);
    static void storeGnarledStaff(std::shared_ptr<Item>& item);
    static void storeLinkedStaff(std::shared_ptr<Item>& item);
    static void storeLongsword(std::shared_ptr<Item>& item);
    static void storeSimpleBow(std::shared_ptr<Item>& item);
    static void storeWarhammer(std::shared_ptr<Item>& item);

    //AGREGAR FUNCIONES PARA CREAR POCIONES

    static void storeGold(std::shared_ptr<Item>& item, unsigned int amount);

public:

    static ItemsFactory& getInstance();

    //Guarda una instancia del item pedido en item, si el nombre del item pasado
    //no existe entonces tira la exepcion out_of_range
    void storeItemInstance(std::string itemName, std::shared_ptr<Item>& item);

    //Almacena un item aleatorio en item, goldMultiplier es el valor por el que se
    //multiplica el porcentaje de oro a generar (del 0 al 20%)
    void storeRandomDrop(std::shared_ptr<Item>& item, unsigned int goldMultiplier);
};


#endif //ARGENTUM_ITEMSFACTORY_H
