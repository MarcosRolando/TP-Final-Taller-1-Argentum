//
// Created by agustin on 16/6/20.
//

#ifndef ARGENTUM_ITEMSFACTORY_H
#define ARGENTUM_ITEMSFACTORY_H

#include <unordered_map>
#include <memory>
#include <vector>
#include "../Config/GameEnums.h"

class Item;
class ItemTests;

typedef void (*objectCreator) (std::shared_ptr<Item>&);

class ItemsFactory {
private:
    std::unordered_map<std::string, objectCreator> itemsCreators;
    std::vector<const std::string*> itemsNames;

    friend ItemTests;

private:
    ItemsFactory();

    static void _storeBlueTunic(std::shared_ptr<Item>& item);
    static void _storeLeatherArmor(std::shared_ptr<Item>& item);
    static void _storePlateArmor(std::shared_ptr<Item>& item);

    static void _storeHood(std::shared_ptr<Item>& item);
    static void _storeIronHelmet(std::shared_ptr<Item>& item);
    static void _storeMagicHat(std::shared_ptr<Item>& item);

    static void _storeIronShield(std::shared_ptr<Item>& item);
    static void _storeTurtleShield(std::shared_ptr<Item>& item);

    static void _storeAshRod(std::shared_ptr<Item>& item);
    static void _storeCompositeBow(std::shared_ptr<Item>& item);
    static void _storeElvenFlute(std::shared_ptr<Item>& item);
    static void _storeGnarledStaff(std::shared_ptr<Item>& item);
    static void _storeLinkedStaff(std::shared_ptr<Item>& item);
    static void _storeLongsword(std::shared_ptr<Item>& item);
    static void _storeSimpleBow(std::shared_ptr<Item>& item);
    static void _storeWarhammer(std::shared_ptr<Item>& item);
    static void _storeAxe(std::shared_ptr<Item>& item);

    static void _storeManaPotion(std::shared_ptr<Item>& item);
    static void _storeHealthPotion(std::shared_ptr<Item>& item);

    static void _storeRandomPotion(std::shared_ptr<Item>& item);

    static void _storeGold(std::shared_ptr<Item>& item, unsigned int amount);

public:

    static ItemsFactory& getInstance();

    //Guarda una instancia del item pedido en item, si el nombre del item pasado
    //no existe entonces tira la exepcion out_of_range
    void storeItemInstance(const std::string& itemName, std::shared_ptr<Item>& item);

    //Guarda una instancia del item pedido en item, si el nombre del item pasado
    //no existe entonces tira la exepcion out_of_range
    void storeItemInstance(GameType::ItemType type, int32_t instance,
                                         std::shared_ptr<Item> &item);

    //Almacena un item aleatorio en item, goldMultiplier es el valor por el que se
    //multiplica el porcentaje de oro a generar (del 0 al 20%)
    void storeRandomDrop(std::shared_ptr<Item>& item, unsigned int goldMultiplier);
};


#endif //ARGENTUM_ITEMSFACTORY_H
