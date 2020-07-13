//
// Created by agustin on 6/6/20.
//

#ifndef ARGENTUM_GOLD_H
#define ARGENTUM_GOLD_H


#include "../Item.h"

class ItemTests;

//Clase que representa un puniado de oro en el piso
class Gold: public Item {
private:
    unsigned int amount;

    friend ItemTests;

public:
    explicit Gold(unsigned int amount);

    GameType::EquipmentPlace use(Player& player) override;

    unsigned int getAmount() const;

    bool isGold() const override;
};

#endif //ARGENTUM_GOLD_H