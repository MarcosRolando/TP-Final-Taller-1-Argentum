//
// Created by agustin on 9/6/20.
//

#ifndef ARGENTUM_CHEST_H
#define ARGENTUM_CHEST_H


#include "Clothing.h"

class ItemTests;

class Chest: public Clothing {
private:
    friend ItemTests;

public:
    explicit Chest(GameType::Clothing clothing);

    GameType::EquipmentPlace use(Player& player) override;

    bool isDefault() const override;
};


#endif //ARGENTUM_CHEST_H
