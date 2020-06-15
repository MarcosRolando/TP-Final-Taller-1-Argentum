//
// Created by agustin on 6/6/20.
//

#ifndef ARGENTUM_GOLD_H
#define ARGENTUM_GOLD_H


#include "Item.h"

//Clase que representa un puniado de oro en el piso
class Gold: public Item{
private:
    unsigned int ammount;

public:
    explicit Gold(unsigned int ammount = 0);

    EquipmentPlace use(Player& player) override;

    unsigned int getAmmount();

    std::shared_ptr<Item> getInstance() override;

    std::shared_ptr<Item> getInstance(unsigned int storedGold);
};

#endif //ARGENTUM_GOLD_H
