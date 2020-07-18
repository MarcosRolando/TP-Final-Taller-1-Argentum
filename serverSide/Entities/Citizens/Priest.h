//
// Created by agustin on 15/6/20.
//

#ifndef ARGENTUM_PRIEST_H
#define ARGENTUM_PRIEST_H


#include "Shop.h"
#include "../Entity.h"

class EntityTests;

class Priest: public Entity {
private:
    Shop shop;

    friend EntityTests;

public:
    explicit Priest(Coordinate initialPosition);

    /*Retorna por le minichat del player los items que tiene el Priest a la venta junto con su precio*/
    void list(Player &player) override;

    /*Le vende al player el item pedido en caso de tenerlo, caso contrario no sucede nada*/
    void buy(Player& player, const std::string& itemName) override;

    /*Le compra al player el item pedido en caso de tenerlo, caso contrario no sucede nada*/
    void sell(Player& player, const std::string& itemName) override;

    /*Cura al Player toda su vida y le recupera la totalidad del mana tambien (no le carga mana al Warrior)*/
    void requestHeal(Player& player) override;
};


#endif //ARGENTUM_PRIEST_H
