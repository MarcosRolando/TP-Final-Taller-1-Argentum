//
// Created by agustin on 15/6/20.
//

#ifndef ARGENTUM_TRADER_H
#define ARGENTUM_TRADER_H


#include "../Entity.h"
#include "Shop.h"

class EntityTests;

class Trader: public Entity {
private:
    Shop shop;

    friend EntityTests;

public:
    explicit Trader(Coordinate initialPosition);

    /*Retorna por le minichat del player los items que tiene el Priest a la venta junto con su precio*/
    void list(Player &player) override;

    /*Le vende al player el item pedido en caso de tenerlo, caso contrario no sucede nada*/
    void buy(Player& player, const std::string& itemName) override;

    /*Le compra al player el item pedido en caso de tenerlo, caso contrario no sucede nada*/
    void sell(Player& player, const std::string& itemName) override;
};


#endif //ARGENTUM_TRADER_H
