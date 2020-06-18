//
// Created by agustin on 6/6/20.
//

#ifndef ARGENTUM_GOLD_H
#define ARGENTUM_GOLD_H


#include "Item.h"

//Clase que representa un puniado de oro en el piso
class Gold: public Item {
private:
    unsigned int amount;

public:
    explicit Gold(unsigned int amount = 0);

    EquipmentPlace use(Player& player) override;

    unsigned int getamount();
};

#endif //ARGENTUM_GOLD_H
